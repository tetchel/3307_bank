#include "Manager.h"

#define NUM_OPTIONS 5

void Manager::managerOperations(UserList* userlist) {
	std::vector<std::string> actions;
	actions.push_back("View data for a user");
	actions.push_back("View data for all users");
	actions.push_back("View total bank funds");
	actions.push_back("Add a user to the system");

	int input = 0;

	while(input != NUM_OPTIONS) {
		input = IOUtils::getUserAction(&actions);

		switch(input) {
			case 1: {
				bool enterUserAgain = true;
				while(enterUserAgain) {
					std::cout << "Enter the username: ";
					std::string username;
					std::cin >> username;
					transform(username.begin(), username.end(), username.begin(), ::tolower);

					User* user = userlist->getUser(username);
					if(user != NULL) {
						std::cout 	<< "Data for " << username << ", ID " << user->getId() << ": " << std::endl
									<< "Chequing Balance: " << user->getChequing() << std::endl
									<< "Savings Balance: " << user->getSavings()  << std::endl;
						enterUserAgain = false;
					}
					else {
						std::cout << "Username was not found in the system." << std::endl;
						enterUserAgain = IOUtils::getUserResponse("Try a new username?", 'y', 'n');
					}
				}
				break;
			}
			case 2: {

				break;
			}
			case 3: {

				break;
			}
			case 4: {
                std::cout << "Enter the username to create: ";
				std::string username;
				std::cin >> username;
				transform(username.begin(), username.end(), username.begin(), ::tolower);

				std::cout << "Enter the password: ";
				std::string password;
				std::cin >> password;
				userlist->addUser(username, password);
				std::cout << "User " << username << " created with password " << password << std::endl;
			}
		}
	}
}
