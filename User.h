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
        virtual ~User();
        std::string getUsername() const;
        std::string getPassword() const;
        int getChequing() const;
        int getSavings() const;
        int getId() const;
        void modifyBalance(bool, int);
        static int getMaxUsers() ;
    private:
        static int next_id;
        std::string username;
        std::string password;
        int id;
        int chq_bal;
        int sav_bal;
        //code required to serialize User
    	friend class boost::serialization::access;
    	template<class Archive>
    	void serialize(Archive & ar, const unsigned int version) {
    		ar & id;
    		ar & username;
    		ar & password;
    		ar & chq_bal;
    		ar & sav_bal;
    	}
};

#endif // USER_H
