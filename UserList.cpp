#include "UserList.h"

#define SERIAL_NAME "users.ser"

std::vector<User*> users;

UserList::UserList() {
    //list of users
    users.reserve(User::getMaxUsers()*sizeof(User*));
    //see if there is saved data
    if(access(SERIAL_NAME, F_OK ) != -1) {
        //if so, load it
        loadUsers();
    }
    //if not, create some sample data so the system is usable.
    else {
        std::cout << "No saved user data found. Creating superusers and a sample regular user with usernames 'manager', 'admin', and 'jsmith'. Passwords match lowercase usernames." << std::endl;
       //precreate superusers
        users.push_back(new User("Manager", "manager", -1, -1));
        //admin knows better, so he has a secure password
        users.push_back(new User("Admin", "admin", -1, -1));
        //create a demo user
        users.push_back(new User("jsmith", "jsmith", 500000, 200000));
    }
}

UserList::~UserList() {
	//free(&users);
}

void UserList::saveUsers() {
    std::ofstream ofs(SERIAL_NAME);
    boost::archive::text_oarchive oa(ofs);
    oa << users;
}

void UserList::loadUsers() {
	std::ifstream ifs(SERIAL_NAME);
    boost::archive::text_iarchive ia(ifs);
    ia >> users;
}

User* UserList::login() {
	bool logged_in = false;
	User* currentUser;
	//following section loops until a successful login
	while(!logged_in) {
		//prompt and grab username
		std::cout << "Username: ";
		std::string username;
		std::cin >> username;

		transform(username.begin(), username.end(), username.begin(), ::tolower);

		//can quit by typing "exit" as a username
		if(username.compare("exit") == 0) {
			//null indicates user wants to exit
			return NULL;
		}

		if((currentUser = getUser(username)) != NULL) {
			while(!logged_in) {
				std::cout << "Password: ";
				std::string password;
				std::cin >> password;

				if(currentUser->getPassword().compare(password) == 0) {
					logged_in = true;
					std::cout << "Welcome, " << currentUser->getUsername() << "." << std::endl;
				}
				else {
					std::cout << "Incorrect password. Passwords are case-sensitive." << std::endl;
					Admin::logExecutionTrace("Failed login by " + username);
				}
			}
		}
		else {
			std::cout 	<< "Username not found, please re-enter or type \"exit\" to leave the application." << std::endl
						<< "Usernames are not case sensitive." << std::endl;
		}
	}

	return currentUser;
}

void UserList::addUser(std::string username, std::string password) {
	users.push_back(new User(username, password, -1, -1));
}

User* UserList::getUser(std::string username) {
	for(std::vector<User*>::iterator it = users.begin(); it != users.end(); ++it) {
		if((*it)->getUsername().compare(username) == 0) {
			return *it;
		}
	}
	return NULL;
}
