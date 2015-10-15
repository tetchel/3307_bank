#ifndef USERLIST_H_
#define USERLIST_H_

#include "User.h"
#include "Admin.h"
#include "Manager.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/vector.hpp>

class User;

class UserList {
public:
	UserList();
	virtual ~UserList();
	void removeUser(std::string username);
	int countUsers() const;
	void addUser(std::string, std::string);
	void saveUsers();

    User* login();
	User* getUser(std::string);
	User* getUser(int index) const;
private:
	std::vector<User*> users;
	static int next_id;
	void loadUsers();
	int getIndexOf(User* user);
};

#endif /* USERLIST_H_ */
