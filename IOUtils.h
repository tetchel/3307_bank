#ifndef IOUTILS_H_
#define IOUTILS_H_

#include "Admin.h"
#include "UserList.h"

#include <iostream>
#include <limits>
#include <string>
#include <vector>

class UserList;

class IOUtils {
public:
    static bool getUserResponse(std::string, const char, const char);
    static int getUserAction(std::vector<std::string>*);
    static std::string centsToString(int amount);
    static void changePassword(std::string, UserList*);
};

#endif /* IOUTILS_H_ */
