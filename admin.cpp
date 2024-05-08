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
void admin::Subscription(Users &user,map<string, personalInformation> &usrData,map<std::string, Plan> &plan) {
    subscription s;
    auto it = usrData.find(user.GetEmail());
    int adminoperation;
    while(adminoperation!=5) {
        cout << "1: Add Plan\n2: Remove Plan\n3: Modify plan\n4:Display Plans\n5:Exsit";
        cin >> adminoperation;
        switch(adminoperation){
            case 1 :    {
                cout << "Plan name: \n";
                string newname;
                cin >> newname;
                cout << "Trips allowed: \n";
                int trips;
                cin >> trips;
                cout << "Duration: \n";
                int duration;
                cin >> duration;
                map<int, int> prices;
                for (int i = 1; i <= 4; i++) {
                    cout << "Stage " << i << "price: \n";
                    int x;
                    cin >> x;
                    prices[i] = x;
                }
                it->second.plan.Addplan(newname, trips, duration, prices, plan);
            }
            case 2: {
                cout << "Plan name: \n";
                string planamee;
                cin >> planamee;
                it->second.plan.Removeplan(planamee, plan);
            }
            case 3: {
                cout << "Plan name: ";
                string planname;cin >> planname;
                int op = 0;
                while (true) {
                    cout << "choose what you want to change:\n"
                         << "1: Plan Name\n"
                         << "2: Plan Duration\n"
                         << "3: Plan Trips allowed\n"
                         << "4: Plan Prices\n"
                         << "5:Exist Modify\n";
                    cin >> op;
                    switch(op) {
                        case 1:{
                            cout << "New Name\n";
                            string namee;
                            cin >> namee;
                            it->second.plan.Modifyplan(plan, planname, namee, -1, -1, {});
                        }
                        case 2: {
                            cout << "New Duration\n";
                            int durationn;
                            cin >> durationn;
                            it->second.plan.Modifyplan(plan, planname, "", durationn, -1, {});
                        }
                        case 3: {
                            cout << "New trips allowed\n";
                            int trips;
                            cin >> trips;
                            it->second.plan.Modifyplan(plan, planname, "", -1, trips, {});
                        }
                        case 4:{
                        map<int, int> pricess;
                        for (int i = 1; i <= 4; i++) {
                            cout << "Stage " << i << "price: \n";
                            int x;
                            cin >> x;
                            pricess[i] = x;
                        }
                        it->second.plan.Modifyplan(plan, planname, "", -1, -1, pricess);
                    }
                        default:
                             break;
                    }
                }
            }
            case 4:
                it->second.plan.DisplaySubscriptionPlan(plan);
        }

    }
}
admin::~admin()
{

}



