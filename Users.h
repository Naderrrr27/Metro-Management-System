//
// Created by DELL on 4/25/2024.
//

#ifndef USERS_H
#define USERS_H
#include <map>
#include <iostream>
#include <set>
#include <regex>
#include <map>
#include "subscription.h"
#include <fstream>
using namespace std;
struct personalInformation
{
    int id;
    string email, fname,  lname, password;
    subscription plan;
    //Rides usrHistory;
    personalInformation() = default;
    personalInformation(int user_id, const string& email, const string& string, const std::string& fname, const std::string& lname);
};

class Users {
    personalInformation Data;

private:
    string Email(map<string, personalInformation> &usrData);
    bool CheckTemplate(string email);
    string Password();
    bool CheckPassword(string email);
    string ToLower(string s);
    void clear(Users &user);
public:
    Users();
    Users(string fname, string lname, string password, string email);
    void begin(map<string, personalInformation>& usrData, map<string, Plan>& plans);
    void Subscribtions(Users& user, map<string, personalInformation>& usrData, map<string, Plan>& plan);
    personalInformation getData()
    {
        return Data;
    }
    Users Login(map<string, personalInformation> &usrData);
    Users Register(map<string, personalInformation> &usrData);
    int GetId();
    Users GetUser();
    string GetFirstName()
    {
        return Data.fname;
    }
    string GetEmail()
    {
        return Data.email;
    }
    personalInformation GetUsers()
    {
        return Data;
    }
    void LogOut(Users &user);
    void Profile(Users &user, map<string, personalInformation> &usrData);
    ~Users();
};



#endif //USERS_H
