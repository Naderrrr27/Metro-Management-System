//
// Created by pc on 03/05/2024.
//

#ifndef METRO_ADMIN_H
#define METRO_ADMIN_H
#include "Users.h"
#include "subscription.h"
#include "Users.h"
using namespace std;
class admin: public Users
{
    subscription plan;
public:
    admin();
    void begin(Users &user, map<string, personalInformation> &usrData, map<string, Plan> &plans);
    void users(map<string, personalInformation> &usrData, map<string, Plan> &plans);
    void DisplayUserData(map<string, personalInformation> &usrData);
    ~admin();
};












#endif //METRO_ADMIN_H
