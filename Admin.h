#ifndef ADMIN_H_
#define ADMIN_H_

#include "IOUtils.h"
#include "UserList.h"

#include <iostream>
#include <limits>
#include <fstream>
#include <ctime>
#include <sstream>
#include <vector>
#include <string>

class Admin {
public:
	static void adminOperations(UserList* users);
	static void logExecutionTrace(std::string s);
	static std::string getAdminName();
private:
	static bool execTrace;
};

#endif /* ADMIN_H_ */
