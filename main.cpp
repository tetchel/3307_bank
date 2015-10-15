#include "User.h"
#include "Admin.h"
#include "Manager.h"
#include "UserList.h"
#include "StandardUser.h"

#include <iostream>
#include <string>

int main() {
	std::cout << "Welcome to the bank. Please sign in:" << std::endl;

	Admin::logExecutionTrace("********** NEW SESSION **********");

	UserList users;
    User* currentUser;

    while((currentUser = users.login()) != NULL) {
    	std::string username = currentUser->getUsername();
    	Admin::logExecutionTrace(username + " successfully logged in");
		//now a user is logged in. call the appropriate static "operations" method
    	//after the call returns, their session is finished
		if(username.compare(Manager::getManagerName()) == 0) {
			Manager::managerOperations(&users);
		}
		else if(username.compare(Admin::getAdminName()) == 0) {
			Admin::adminOperations(&users);
		}
		else {
			//normal
			StandardUser::standardUserOperations(currentUser, &users);
		}
		std::cout << "Logging you out..." << std::endl;
		Admin::logExecutionTrace(username + " logged out");
    }
    users.saveUsers();
    std::cout << "Exiting the program..." << std::endl;
    Admin::logExecutionTrace("Program exited normally");
    return 0;
}
