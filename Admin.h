#ifndef ADMIN_H_
#define ADMIN_H_

#include "IOUtils.h"

#include <iostream>
#include <limits>
#include <fstream>
#include <ctime>
#include <sstream>
#include <vector>
#include <string>

class Admin {
public:
	static void adminOperations();
	static void logExecutionTrace(std::string s);
private:
	static bool execTrace;
};

#endif /* ADMIN_H_ */
