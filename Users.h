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

#include "wallet.h"
using namespace std;
struct personalInformation
{
    int id;
    string email, fname,  lname, password;
    subscription plan;
    vector<Ride> usrHistory;
    wallet balance;
    personalInformation() = default;
    personalInformation(int user_id, const string& email, const string& string, const std::string& fname, const std::string& lname);
};

class Users {
public:
    personalInformation Data;
    bool isLogged_In = false;
    bool isAdmin = false;
private:
    string Email(map<string, personalInformation> &usrData);
    bool CheckTemplate(string email);
    string Password();
    bool CheckPassword(string email);
    string ToLower(string s);
    void clear(Users &user);
    void WalletTrip(Users& user, map<string, personalInformation>& usrData, string& fdest, string& ldest, Metro& metro, Ride& ride, unordered_map
                    <string, vector<Ride>>& rides);
    void DisplayRideData(Ride& ride);
    void SubscriptionTrip(Users& user, map<string, personalInformation>& usrData, string& fdest, string& ldest,
                          Metro& metro,
                          Ride& ride, unordered_map<string, vector<Ride>>& rides);

public:
    Users();
    Users(string fname, string lname, string password, string email);
    void Wallet( Users& users, map<string, personalInformation>& map);
    void begin(map<string, personalInformation>& usrData, map<string, Plan>& plans, Metro& metro, unordered_map<string, vector<Ride>>&
               rides);
    void Subscribtions(Users& user, map<string, personalInformation>& usrData, map<string, Plan>& plan,Metro &metro);
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
    void Charge(Users& user, map<string, personalInformation>& usrData);
    void CheckIn(Metro& metro, Users& user, map<string, personalInformation>& usrData, unordered_map<string, vector<Ride>>& rides);
    string getStationName(Metro& metro, Ride& ride, const string& stationName);
    bool CheckGraphs(Metro& metro, Ride& ride, string fdest, string ldest, Users& user);

    ~Users();
};



#endif //USERS_H
