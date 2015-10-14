#ifndef STANDARDUSER_H_
#define STANDARDUSER_H_

#include "User.h"
#include "UserList.h"
#include "IOUtils.h"

#include <iostream>
#include <limits>
#include <sstream>
#include <cmath>
#include <algorithm>

class StandardUser {
public:
	static void standardUserOperations(User*, UserList*);
private:
	static int getDollarAmount();
//	static int processWithdraw(int);
	static int processDeduction(User*, bool);
	static void printBalances(User*);
	static std::string centsToString(int);
	static bool selectAccount(int, int, std::string);
};

#endif /* STANDARDUSER_H_ */
