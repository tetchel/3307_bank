#ifndef MANAGER_H_
#define MANAGER_H_

#include "User.h"
#include "UserList.h"
#include "IOUtils.h"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include <sstream>

class UserList;
class User;

class Manager {
public:
	static void managerOperations(UserList*);
	static std::string getManagerName();
private:
    static void outputUserInfo(User*);
};

#endif /* MANAGER_H_ */
