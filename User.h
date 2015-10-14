#ifndef USER_H
#define USER_H

#include "Admin.h"

#include <iostream>
#include <algorithm>
#include <limits>
#include <sstream>
#include <string>
#include <vector>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

class User
{
public:
    User();
    User(std::string, std::string, int chq, int sav);
//    virtual ~User();
    void modifyBalance(bool, int);
    static int getMaxUsers() ;
    void setPassword(std::string);

    std::string getUsername() const;
    std::string getPassword() const;
    int getChequing() const;
    int getSavings() const;
private:
    std::string username;
    std::string password;
    int chq_bal;
    int sav_bal;
    //code required to serialize User
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & username;
        ar & password;
        ar & chq_bal;
        ar & sav_bal;
    }
};

#endif // USER_H
