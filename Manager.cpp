#include "Manager.h"

#define NUM_OPTIONS 8
#define MANAGER_NAME "manager"
/**
*   This class handles all operations performed by the Bank Manager.
*   Includes viewing user details, adding a user, or viewing bank funds.
**/
void Manager::managerOperations(UserList* userlist) {
	std::vector<std::string> actions;
	actions.push_back("View data for a user");
	actions.push_back("View data for all users");
	actions.push_back("View total bank funds");
	actions.push_back("Add a user to the system");
	actions.push_back("Remove a user from the system");
	actions.push_back("Change your password");
	actions.push_back("Send a message to a user");

	int input = 0;

	while(input != NUM_OPTIONS) {
		input = IOUtils::getUserAction(&actions);

		switch(input) {
		    //view data 1 user
			case 1: {
				bool enterUserAgain = true;
				//wait for a real username
				while(enterUserAgain) {
					std::cout << "Enter the username: ";
					std::string username;
					std::cin >> username;
					transform(username.begin(), username.end(), username.begin(), ::tolower);

                    if(userlist->getUser(username) != NULL) {
                        outputUserInfo(userlist->getUser(username));
                        enterUserAgain = false;
                    }
                    else {
                        std::cout << "Username was not found in the system." << std::endl;
                        enterUserAgain = IOUtils::getUserResponse("Try a new username?", 'y', 'n');
                    }
				}
				break;
			}
			//view info for all users
			case 2: {
                int i;
                //start at 2 because 0 and 1 are the superusers, who don't have any money.
                for (i = 2; i < userlist->countUsers(); i++) {
                    outputUserInfo(userlist->getUser(i));
                }
				break;
			}
			//view total bank funds
			case 3: {
                int chq_sum = 0,
                    sav_sum = 0,
                    i = 0;
                //loop through users, keep a running total of their cash
                for (i = 2; i < userlist->countUsers(); i++) {
                    int chq = userlist->getUser(i)->getChequing(),
                        sav = userlist->getUser(i)->getSavings();
                    if(chq != -1)
                        chq_sum += chq;
                    if(sav != -1)
                        sav_sum += sav;
                }
                std::cout   << "Total Funds: "    << IOUtils::centsToString(chq_sum + sav_sum)  << std::endl
                            << "Chequing Funds: " << IOUtils::centsToString(chq_sum)            << std::endl
                            << "Savings Funds: "  << IOUtils::centsToString(sav_sum)            << std::endl;
				break;
			}
			//add a user
			case 4: {
			    bool again = true;
			    while(again) {
                    std::cout << "Enter the username to create: ";
                    std::string username;
                    std::cin >> username;
                    transform(username.begin(), username.end(), username.begin(), ::tolower);

                    if(userlist->getUser(username) != NULL) {
                        std::cout << "User " << username << " already exists." << std::endl;
                        again = IOUtils::getUserResponse("Enter a different username?", 'y', 'n');
                    }
                    else {
                        std::cout << "Enter the password: ";
                        std::string password;
                        std::cin >> password;
                        userlist->addUser(username, password);
                        std::cout << "User " << username << " created with password " << password << std::endl;
                        //save the new user into the .ser
                        userlist->saveUsers();
                        again = false;
                        Admin::logExecutionTrace(username + " was added");
                    }
                }
                break;
			}
			//remove a user
			case 5: {
                bool again = true;
			    while(again) {
                    std::cout << "Enter the username to remove: ";
                    std::string username;
                    std::cin >> username;
                    transform(username.begin(), username.end(), username.begin(), ::tolower);

                    if(username.compare("admin") == 0 || username.compare("manager") == 0) {
                        std::cout << "You can't delete that user!" << std::endl;
                    }
                    else if(userlist->getUser(username) == NULL) {
                        std::cout << "User " << username << " doesn't exist." << std::endl;
                        again = IOUtils::getUserResponse("Enter a different username?", 'y', 'n');
                    }
                    else {
                        userlist->removeUser(username);
                        std::cout << "User " << username << " removed" << std::endl;
                        //update .ser
                        userlist->saveUsers();
                        again = false;
                        Admin::logExecutionTrace(username + " was removed");
                    }
                }
                break;
            }
            case 6: {
                if(!IOUtils::getUserResponse("Are you sure you want to change your password?", 'y', 'n'))
                    break;

                IOUtils::changePassword(MANAGER_NAME, userlist);

                break;
			}
			//send a message to a user
			case 7: {
                bool again = true;
			    while(again) {
                    std::cout << "Enter the user to message: ";
                    std::string username;
                    std::cin >> username;
                    transform(username.begin(), username.end(), username.begin(), ::tolower);

                    if(username.compare("admin") == 0 || username.compare("manager") == 0) {
                        std::cout << "You can't message that user!" << std::endl;
                    }
                    else if(userlist->getUser(username) == NULL) {
                        std::cout << "User " << username << " doesn't exist." << std::endl;
                        again = IOUtils::getUserResponse("Enter a different username?", 'y', 'n');
                    }
                    else {
                        std::cout << "Enter the message on one line, press RETURN twice to finish: " << std::endl;
                        std::string msg;
                        std::cin.ignore();
                        //get message
                        std::getline(std::cin, msg);

                        //add it to the user's list
                        userlist->getUser(username)->message(msg);
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        userlist->saveUsers();
                        std::cout << "Successfully messaged " << username << std::endl;
                        std::ostringstream oss;
                        oss << "Messaged " << username << " \"" << msg << "\"";
                        Admin::logExecutionTrace(oss.str());
                        again = false;
                    }
                }
                break;
			}
		}
	}
}

//outputs formatted info for the parameter user.
//returns whether or not the user exists.
void Manager::outputUserInfo(User* user) {
    std::cout 	<< "Data for " << user->getUsername() << ": " << std::endl;
    int chq = user->getChequing();
    int sav = user->getSavings();

    if(chq != -1)
        std::cout << "Chequing Balance: " << IOUtils::centsToString(chq) << std::endl;
    else
        std::cout << "No chequing account." << std::endl;
    if(sav != -1)
        std::cout << "Savings Balance: " << IOUtils::centsToString(sav)  << std::endl;
    else
        std::cout << "No savings account." << std::endl;
}

std::string Manager::getManagerName() {
    return MANAGER_NAME;
}
