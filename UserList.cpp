#include "UserList.h"

#define SERIAL_NAME "users.ser"
#define XOR_KEY

/**
*   This is a data type class which holds the vector containing pointers to all users.
*   This vector is serialized after any relevant operation is performed using saveUsers(), and loads the data in the constructor.
*   Implements some vector operations so that the vector itself is hidden from other classes.
**/

//main feature of this class; the data
std::vector<User*> users;

UserList::UserList() {
    //list of users - size of 1000 is plenty.
    users.reserve(1000*sizeof(User*));
    //see if there is saved data
    if(access(SERIAL_NAME, F_OK ) != -1) {
        //if so, load it
        loadUsers();
    }
    //if not, create some sample data so the system is usable.
    else {
        std::cout << "No saved user data found. Creating superusers and a sample regular user with usernames 'manager', 'admin', and 'jsmith'. Passwords match lowercase usernames." << std::endl;
        //create superusers
        users.push_back(new User(Manager::getManagerName(), Manager::getManagerName(), -1, -1));
        users.push_back(new User(Admin::getAdminName(), Admin::getAdminName(), -1, -1));
        //create a demo user
        users.push_back(new User("jsmith", "jsmith", 500000, 200000));
        saveUsers();
    }
}

//free memory held by vector pointers
UserList::~UserList() {
	for (std::vector<User*>::iterator it = users.begin(); it != users.end(); ++it)
        delete *it;

    users.clear();
}

//serializes the vector to file
void UserList::saveUsers() {
    std::ofstream ofs(SERIAL_NAME);
    boost::archive::binary_oarchive oa(ofs);
    oa << users;
}

//loads serialized data into vector
void UserList::loadUsers() {
	std::ifstream ifs(SERIAL_NAME);
    boost::archive::binary_iarchive ia(ifs);
    ia >> users;
}

//handles a user logging in
//returns a pointer to the user who is logged in
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

        //if the user exists, prompt for a password
		if((currentUser = getUser(username)) != NULL) {
            int attempts = -1;
			while(!logged_in && attempts++ < 4) {
                if(attempts > 0)
                    std::cout << "[" << attempts << "] " << "Password: ";
                else
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
			if(attempts >= 5) {
                std::cout << "Maximum number of attempts exceeded." << std::endl;
			}
		}
		else {
			std::cout 	<< "Username not found, please re-enter or type \"exit\" to leave the application." << std::endl
						<< "Usernames are not case sensitive." << std::endl;
		}
	}

	return currentUser;
}

//add a user with the specified info to the system
void UserList::addUser(std::string username, std::string password) {
	users.push_back(new User(username, password, -1, -1));
}

//removes the user with the given username from the system
void UserList::removeUser(std::string username) {
    int index = getIndexOf(getUser(username));
    delete users[index];
    users.erase(users.begin()+index);
}

//how many users are in the list
int UserList::countUsers() const {
    return users.size();
}

//returns the user at index i - useful for looping through all users
User* UserList::getUser(int index) const {
    return users.at(index);
}

//helper for removeUser
//returns the index of the passed user
int UserList::getIndexOf(User* user) {
    return find(users.begin(), users.end(), user) - users.begin();
}

//returns the user* to the user with the given username
User* UserList::getUser(std::string username) {
	for(std::vector<User*>::iterator it = users.begin(); it != users.end(); ++it) {
		if((*it)->getUsername().compare(username) == 0) {
			return *it;
		}
	}
	//user was not found :(
	return NULL;
}
