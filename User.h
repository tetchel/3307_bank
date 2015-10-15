#ifndef USER_H
#define USER_H

#include "Admin.h"

#include <iostream>
#include <algorithm>
#include <limits>
#include <sstream>
#include <string>
#include <vector>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

class User
{
public:
    User();
    User(std::string, std::string, int chq, int sav);
    //used by standardUserOperations
    void modifyBalance(bool, int);
    //used by manager
    void setPassword(std::string);
    void message(std::string msg);
    void printMessages();
    //getters
    std::string getUsername() const;
    std::string getPassword() const;
    int getChequing() const;
    int getSavings() const;
private:
    std::string username;
    std::string password;
    int chq_bal;
    int sav_bal;
    std::vector<std::string> msgs;

    //code required to serialize User
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & username;
        ar & password;
        ar & chq_bal;
        ar & sav_bal;
        ar & msgs;
    }
};

#endif // USER_H
