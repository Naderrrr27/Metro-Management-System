//
// Created by pc on 03/05/2024.
//

#ifndef METRO_ADMIN_H
#define METRO_ADMIN_H
#include "Users.h"
#include "subscription.h"
#include "Users.h"
#include "metro.h"
using namespace std;
class admin: public Users
{
    subscription plan;
public:
    admin();
    void begin(Users &user, map<string, personalInformation> &usrData, map<string, Plan> &plans,Metro &metro,unordered_map<string, vector<Ride>> &rides,vector<vector<string>>&lines);
    void users(map<string, personalInformation> &usrData, map<string, Plan> &plans,Metro &metro,unordered_map<string, vector<Ride>> &rides, Users &users);
    void DisplayUserData(map<string, personalInformation> &usrData);
    void Subscription(Users &user,map<string, personalInformation> &usrData,map<string, Plan> &plans);
    void AddUser(map<string, personalInformation> &usrData);
    void DeleteUser(map<string, personalInformation> &usrData);
    void ModifyUser(map<string, personalInformation>& usrData, map<string, Plan>& plan,Metro &metro);
    void AllRidesHistory(unordered_map<string, vector<Ride>> &rides, Users &users);
    void addStation(vector<vector<string>>&line,Metro&metro);
    void removeStation(vector<vector<string>>&line,Metro&metro);
    void renameStation(vector<vector<string>>&line,Metro&metro);


    ~admin();
};












#endif //METRO_ADMIN_H
