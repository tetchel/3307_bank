#include "User.h"

/**
*   This class is a data type to hold user information, including username, password, account balances, and a unique ID.
*   Also implements some functions to make this class serializable, and consequently the UserList which contains these.
**/

//empty constructor so that this class is serializable
User::User() {}

User::User(std::string usern, std::string passw, int chq, int sav) {
	std::ostringstream oss;
    oss << "Creating a new user with data: " << usern << ", " << passw;
    Admin::logExecutionTrace(oss.str());

    //all user names are stored lowercase so they are case insenstive
    transform(usern.begin(), usern.end(), usern.begin(), ::tolower);
    username = usern;
    password = passw;
    //-1 indicates the account has not been opened/initialized/is closed
    //balances are in cents
    chq_bal = chq;
    sav_bal = sav;
}

//changes the user's balance by amount, positive or negative.
//isChq determines whether to edit chq or sav account
void User::modifyBalance(bool isChq, int amount) {
	std::ostringstream oss;
	oss <<"Modifying balance of " << getUsername() << (isChq ? " chequing" : " savings") << " by " << amount;
	Admin::logExecutionTrace(oss.str());
	if(isChq)
		chq_bal += amount;
	else
		sav_bal += amount;
}

//overload & operator for serialization out
std::ostream & operator<<(std::ostream &os, const User &u)
{
	return os << u;
}

//overload & operator for serialization in
std::istream & operator>>(std::istream &is, const User &u)
{
    return is >> u;
}

//used by Manager class to change password
void User::setPassword(std::string pw) {
    password = pw;
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
