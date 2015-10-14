#include "Manager.h"

#define NUM_OPTIONS 5

/**
*   This class handles all operations performed by the Bank Manager.
*   Includes viewing user details, adding a user, or viewing bank funds.
**/
void Manager::managerOperations(UserList* userList) {
	std::vector<std::string> actions;
	actions.push_back("View data for a user");
	actions.push_back("View data for all users");
	actions.push_back("View total bank funds");
	actions.push_back("Add a user to the system");

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

                    if(userList->getUser(username) != NULL) {
                        outputUserInfo(userList->getUser(username));
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
                for (i = 2; i < userList->countUsers(); i++) {
                    outputUserInfo(userList->getUser(i));
                }
				break;
			}
			//view total bank funds
			case 3: {
                int chq_sum = 0,
                    sav_sum = 0,
                    i = 0;
                //loop through users, keep a running total of their cash
                for (i = 2; i < userList->countUsers(); i++) {
                    int chq = userList->getUser(i)->getChequing(),
                        sav = userList->getUser(i)->getSavings();
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

                    if(userList->getUser(username) != NULL) {
                        std::cout << "User " << username << " already exists." << std::endl;
                    }
                    else {
                        std::cout << "Enter the password: ";
                        std::string password;
                        std::cin >> password;
                        userList->addUser(username, password);
                        std::cout << "User " << username << " created with password " << password << std::endl;
                        //save the new user into the .ser
                        userList->saveUsers();
                        again = false;
                    }
                }
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
