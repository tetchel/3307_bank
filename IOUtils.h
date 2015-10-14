#ifndef IOUTILS_H_
#define IOUTILS_H_

#include "Admin.h"

#include <iostream>
#include <limits>
#include <string>
#include <vector>

class IOUtils {
public:
    static bool getUserResponse(std::string, const char, const char);
    static int getUserAction(std::vector<std::string>*);
};

#endif /* IOUTILS_H_ */
