//
// Created by pc on 03/05/2024.
//

#include "admin.h"

#include <iomanip>
using namespace std;
admin::admin()
{

}
void admin::begin(Users &user,map<string, personalInformation>& usrData, map<string, Plan>& plans)
{
    int operation;
    cout << "1: Users\n2: Subscriptions\n3: Log out\n";
    cin >> operation;

    switch (operation) {
    case 1:
        users(usrData, plans);
        break;
    case 2:
        Profile(*this, usrData);
        break;
    case 3:
        LogOut(user);
        break;
    default:
        cout << "Invalid choice. Please try again.\n";
        break;
    }
}
void admin::users(map<string, personalInformation>& usrData, map<string, Plan>& plans)
{
    int op; cin >> op;
    while (op != 5)
    {
        cout << "1: Display Users Data" << endl;
        cout << "2: Add User" << endl;
        cout << "3: Delete User" << endl;
        cout << "4: Modify User Data" << endl;
        cout << "5: Home\n";
        cin >> op;
        switch(op)
        {
        case 1:
            DisplayUserData(usrData);
            break;
        default:
            break;
        }
    }


}
void admin::DisplayUserData(map<string, personalInformation> &usrData)
{
    int colWidth = 20;
    cout << left << setw(colWidth) << "First Name"
             << setw(colWidth) << "Last Name"
             << setw(30) << "Email"
             << setw(30) << "Password"
             << setw(30) << "Subscription Type" << endl;
    for (auto &it: usrData)
    {
        cout << left << setw(colWidth) << it.second.fname
        << setw(colWidth) << it.second.lname
        << setw(30) << it.second.email
        << setw(30) << it.second.password
        << setw(30) << it.second.plan.plan.PlanName << endl;
    }
}

admin::~admin()
{

}



