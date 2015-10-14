#include "User.h"

#define MAX_USERS 1000

//at least some IDs must be precreated for an initial login
//static
int User::next_id = 1;

User::User() {}

User::User(std::string usern, std::string passw, int chq, int sav) {
    if(next_id <= MAX_USERS) {
        id = next_id++;
    }
    else {
    	Admin::logExecutionTrace("Max users reached!");
        std::cout << "Max number of users reached, could not create new user." << std::endl;
    }

    if(usern.compare("exit") == 0) {
        //this is illegal
        std::cout << "Nice try! You can't be named exit. Your username will be user" << id;
        std::ostringstream oss;
        oss << "user" << id;
        usern = oss.str();
    }

	std::ostringstream oss;
    oss << "Creating a new user with data: " << usern << ", " << passw;
    Admin::logExecutionTrace(oss.str());

    //all user names are stored lowercase so they are case insenstive
    username = usern;
    transform(username.begin(), username.end(), username.begin(), ::tolower);
    password = passw;
    //-1 indicates the account has not been opened/initialized/is closed
    //balances are in cents
    chq_bal = chq;
    sav_bal = sav;
}

User::~User() {
    //destruct
}

void User::modifyBalance(bool isChq, int amount) {
	std::ostringstream oss;
	oss <<"Modifying balance of " << getUsername() << (isChq ? " chequing" : " savings") << " by " << amount;
	Admin::logExecutionTrace(oss.str());
	if(isChq)
		chq_bal += amount;
	else
		sav_bal += amount;
}

std::ostream & operator<<(std::ostream &os, const User &u)
{
	return os << u;
}

std::istream & operator>>(std::istream &is, const User &u)
{
    return is >> u;
}

////////// GETTERS //////////

std::string User::getUsername() const {
    return username;
}

std::string User::getPassword() const {
    return password;
}

int User::getChequing() const {
	return chq_bal;
}

int User::getSavings() const {
	return sav_bal;
}

int User::getMaxUsers() {
    return MAX_USERS;
}

int User::getId() const {
	return id;
}
