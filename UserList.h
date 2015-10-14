#ifndef USERLIST_H_
#define USERLIST_H_

#include "User.h"
#include "Admin.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>

class UserList {
public:
	UserList();
	virtual ~UserList();
	User* login();
	User* getUser(std::string);
	void addUser(std::string, std::string);
	void saveUsers();
	void loadUsers();
private:
	std::vector<User*> users;
};

#endif /* USERLIST_H_ */
