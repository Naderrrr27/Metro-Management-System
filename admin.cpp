//
// Created by pc on 03/05/2024.
//

#include "admin.h"

#include <iomanip>
#include "Statistics.h"
#include "metro.h"
using namespace std;
admin::admin()
{

}
void checkDayMonth(int &num, bool dayOrNot){
    int again, endRange ;
    string text ;
    bool valid = false;
    if (dayOrNot == true) {
        endRange = 31;
        text = "Valid day\n";
    }else{
        endRange = 12;
        text = "Valid month\n";
    }
    while(!valid){
        if(num <= 0 || num > endRange){
            cout<<"invalid data please try again:\n";
            cin>>again;
            num = again;
            valid = false;
        }else
            valid = true;
    }
    if(valid)
        cout<<text;
}
void checkYear(int &year){
    int again;
    bool valid = false;
    while(!valid){
        if(year < 2024){
            cout<<"invalid year please try again:\n";
            cin>>again;
            year = again;
            valid = false;
        }else
            valid = true;
    }
    if(valid)
        cout<<"Valid year \n";
}
string maintainFormat(int num){
    string date;
    if(num < 10){
        char convertt = num + '0';
        date.push_back('0');
        date.push_back(convertt);
    }else{
        date.append(to_string(num));
    }
    return date;
}
void admin::begin(Users &user,map<string, personalInformation>& usrData, map<string, Plan>& plans,Metro &metro,unordered_map<string, vector<Ride>> &rides,vector<vector<string>>&lines)
{
    int operation;
    cout << "1: Users\n2: Subscriptions\n3: Statistics\n4: Metro\n5: Log out\n";
    cin >> operation;

    switch (operation) {
    case 1:
        users(usrData, plans,metro,rides,user);
        break;
    case 2:
        Subscription(user, usrData, plans);
        break;
    case 3 :
        cout<<"1: Statistical Reports\n";
        cout<<"2: Ride History\n";
        int input;
        cin>>input;
        if(input == 1){
            int choisee;
            cout<<"1: Statistical Reports for Each Day\n";
            cin>>choisee;
            if(choisee == 1){
                bool check = false;
                while (!check){
                    int exit ;
                    int day, month, year;
                    string date, stationName;
                    cout<<"Please fill in the following date: \n";
                    cout<<"Please enter the day of the date  : \n";
                    cin>>day;
                    checkDayMonth(day, true);
                    cout<<"Please enter the month  of the date  : \n";
                    cin>>month;
                    checkDayMonth(month, false);
                    cout<<"Please enter the year of the date   : \n";
                    cin>>year;
                    checkYear(year);
                    date.append(maintainFormat(day)),date.push_back('/');
                    date.append(maintainFormat(month)) ,date.push_back('/');
                    date.append(maintainFormat(year));
                    cout<<"Please enter the name of the station \n";
                    cin>>stationName;
                    check = Statistics::showStatisticsDay(date,stationName);
                    if(check == false){
                        cout<<"This date is not found \n";
                        cout<<"1. enter new date\n";
                        cout<<"2. exit\n";
                        cin>>exit;
                        if(exit == 2)
                            check = true;
                    }
                }
            }

        }else {
            AllRidesHistory(rides, user);
        }
            break;
    case 4:
        cout<<"1: Add Station\n";
        cout<<"2: Remove Station\n";
        cout<<"3: Rename Station\n";

        int op;
        cin>>op;

        if(op==1){
            addStation(lines,metro);
        }
        else if(op==2){
            removeStation(lines,metro);
        }
        else if(op==3){
            renameStation(lines,metro);
        }

        break;
    case 5:
        LogOut(user);
        break;
    default:
        cout << "Invalid choice. Please try again.\n";
        break;
    }
}
void admin::users(map<string, personalInformation>& usrData, map<string, Plan>& plans,Metro &metro,unordered_map<string, vector<Ride>> &rides, Users &users)
{
    int op;
    while (true)
    {
        cout << "1: Display Users Data" << endl;
        cout << "2: Add User" << endl;
        cout << "3: Delete User" << endl;
        cout << "4: Modify User Data" << endl;
        cout << "5: Ride History"<<endl;
        cout << "6: Home\n";
        cin >> op;
        switch(op)
        {
        case 1:
            DisplayUserData(usrData);
            break;
        case 2:
            AddUser(usrData);
            break;
        case 3:
            DeleteUser(usrData);
            break;
        case 4:
            ModifyUser(usrData, plans,metro);
            break;
        case 5:
            return;
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
        << setw(30) << it.second.plan.plan.PlanName <<
            setw(30) << it.second.balance.Balance;
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
                    cout << "Stage " << i << "Price: \n";
                    int x;
                    cin >> x;
                    prices[i] = x;
                }
                it->second.plan.Addplan(newname, trips, duration, prices, plan);
                    break;
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
                            break;
                        }
                        case 2: {
                            cout << "New Duration\n";
                            int durationn;
                            cin >> durationn;
                            it->second.plan.Modifyplan(plan, planname, "", durationn, -1, {});
                            break;

                        }
                        case 3: {
                            cout << "New trips allowed\n";
                            int trips;
                            cin >> trips;
                            it->second.plan.Modifyplan(plan, planname, "", -1, trips, {});
                            break;

                        }
                        case 4:{
                        map<int, int> pricess;
                        for (int i = 1; i <= 4; i++) {
                            cout << "Stage " << i << "Price: \n";
                            int x;
                            cin >> x;
                            pricess[i] = x;
                        }
                        it->second.plan.Modifyplan(plan, planname, "", -1, -1, pricess);
                            break;
                        }
                        default:
                             break;
                    }
                }
            }
            case 4:
                it->second.plan.DisplaySubscriptionPlan(plan);
                break;
            case 5:
                return;
        }

    }
}
void admin::AddUser(map<string, personalInformation> &usrData)
{
    Users newUser;
    string fname, lname, password, email;
    cout << "First Name:";
    cin >> fname;

    cout << "Last Name:";
    cin >> lname;

    cout << "Email:";
    cin >> email;

    cout << "Password:";
    cin >> password;
    newUser.Data.password = password;
    newUser.Data.fname = fname;
    newUser.Data.lname = lname;
    newUser.Data.email = email;
    usrData.emplace(email, newUser.getData());
}
void admin::DeleteUser(map<string, personalInformation> &usrData)
{
    cout << "Enter Email\n";

    string email; cin >> email;
    if (usrData.find(email) != usrData.end())
    {
        usrData.erase(email);
    }
}
void admin::ModifyUser(map<string, personalInformation> &usrData, map<string, Plan> &plan,Metro &metro)
{
    cout << "Enter Email\n";
    string email; cin >> email;
    auto user = usrData.find(email);
    if (user == usrData.end())
    {
        cout << "This User can not be found\n";
    }
    else
    {


        while (true)
        {
            cout << "1: Modify First Name\n";
            cout << "2: Modify Last Name\n";
            cout << "3: Modify E-mail\n";
            cout << "4: Modify Password\n";
            cout << "5: Modify Subscription Plan\n";
            cout << "6: Modify Balance\n";
            cout << "7: Back\n";
            int op; cin >> op;
            string s;
            if (op == 1)
            {
                cout << "First Name\n";
                cin >> s;
                user->second.fname = s;
            }
            else if (op == 2)
            {
                cout << "Last Name:";
                cin >> s;
                user->second.lname = s;
            }
            else if (op == 3)
            {
                cout << "E-mail";
                cin >> s;
                user->second.email = s;
                usrData.insert({user->second.email, user->second});
                usrData.erase(user);
                user = usrData.find(s);
            }
            else if (op == 4)
            {
                cout << "Password:";
                cin >> s;
                user->second.password = s;
            }
            else if (op == 7) return;
            else if (op == 5)
            {
                subscription s;
                s.chooseplan(plan,metro);
                user->second.plan = s;
            }
            else if (op == 6)
            {
                cout << "Balance:";
                int balance; cin >> balance;
                user->second.balance.Balance = balance;
            }
        }
    }
}
void admin:: AllRidesHistory(unordered_map<string, vector<Ride>> &rides,Users &users) {


    cout << left << setw(15) << "User" << setw(15) << "Type" << setw(15) << "From" << setw(15) << "To" << setw(15)
         << "Price" <<setw(15) << "stations" << setw(15) << "Date" << setw(15) << "Time" << endl;

    map<string, personalInformation> usrData;
    for (const auto &user: rides) {
        auto usrHistory = rides.find(user.first);
        for (const auto &ride: usrHistory->second) {

            cout << left << setw(15) <<user.first << setw(15) << ride.getSubscriptionType() << setw(15)
                 << ride.getFirstD() << setw(15) << ride.getFinalD() << setw(15) << ride.getFare() <<
                 setw(15) << ride.getRidePath().size() << setw(15) << ride.getDate() << setw(15) << ride.getTime()
                 << endl;
        }
    }


}

admin::~admin()
{

}

void admin::addStation(vector<vector<string>> &line,Metro&metro) {


    cout << "Enter The Line Color For The Station: " << endl;

    string color;
    getline(cin, color);

    while (color != "Green" && color != "Red" && color != "Blue") {
        cout << "Please Enter A Valid Color: " << endl;
        getline(cin, color);
    }

    cout << "Enter The Station Name: " << endl;

    string stationName;
    getline(cin, stationName);

    cout << "Enter The Number Of Connected Stations: " << endl;

    int neighbors;
    cin >> neighbors;
    cin.ignore();

    while (neighbors != 1 && neighbors != 2) {
        cout << "Please Enter A Valid Number Of Connected Stations: " << endl;
        cin >> neighbors;
        cin.ignore();
    }

    int lineIdx = -1;

    if (color == "Green") {
        lineIdx = 0;
    } else if (color == "Red") {
        lineIdx = 1;
    } else if (color == "Blue") {
        lineIdx = 2;
    }

    if (neighbors == 1) {
        cout << "Enter The Name Of Connected Station: " << endl;

        string nextStation;
        getline(cin, nextStation);

        while (nextStation != line[lineIdx][0] && nextStation != line[lineIdx].back()) {
            cout << "The Station Should Be A Tail" << endl;
            getline(cin, nextStation);
        }

        if (nextStation == line[lineIdx][0]) {
            line[lineIdx].insert(line[lineIdx].begin(), stationName);
            cout << "Added The Station" << endl;
            metro.delete_line(color);
            Metro::build_line(metro,color,line[lineIdx]);
            return;
        } else if (nextStation == line[lineIdx].back()) {
            line[lineIdx].push_back(stationName);
            metro.delete_line(color);
            Metro::build_line(metro,color,line[lineIdx]);
            cout << "Added The Station" << endl;
            return;
        }

    } else {
        string firstStation, secondStation;

        cout << "Enter The Name Of 1st Connected Station: " << endl;
        getline(cin, firstStation);
        cout << "Enter The Name Of 2nd Connected Station: " << endl;
        getline(cin, secondStation);

        while (true) {
            for (int i = 0; i < line[lineIdx].size() - 1; i++) {
                if ((line[lineIdx][i] == firstStation && line[lineIdx][i + 1] == secondStation) ||
                    (line[lineIdx][i] == secondStation && line[lineIdx][i + 1] == firstStation)) {
                    line[lineIdx].insert(line[lineIdx].begin() + i + 1, stationName);
                    metro.delete_line(color);
                    Metro::build_line(metro,color,line[lineIdx]);
                    cout << "Added The Station" << endl;
                    return;
                }
            }
            cout << "Make Sure To Add Valid Station Names (Consecutive)" << endl;
            cout << "Enter The Name Of 1st Connected Station: " << endl;
            getline(cin, firstStation);
            cout << "Enter The Name Of 2nd Connected Station: " << endl;
            getline(cin, secondStation);
        }
    }

}

void admin::removeStation(vector<vector<string>> &line,Metro&metro) {

    cout << "Enter The Line Color For The Station: " << endl;

    string color;
    getline(cin, color);

    while (color != "Green" && color != "Red" && color != "Blue") {
        cout << "Please Enter A Valid Color: " << endl;
        getline(cin, color);
    }

    int lineIdx = -1;

    if (color == "Green") {
        lineIdx = 0;
    } else if (color == "Red") {
        lineIdx = 1;
    } else if (color == "Blue") {
        lineIdx = 2;
    }

    cout << "Enter The Station Name To Delete: " << endl;

    string stationToDelete;
    getline(cin, stationToDelete);


    while(true){
        for (auto it = line[lineIdx].begin(); it != line[lineIdx].end(); ++it) {
            if (*it == stationToDelete) {
                line[lineIdx].erase(it);
                cout << "Station '" << stationToDelete << "' Deleted Successfully" << endl;
                metro.delete_line(color);
                Metro::build_line(metro,color,line[lineIdx]);
                return;
            }
        }

        cout << "Station '" << stationToDelete << "' Not Found in Line " << color << endl;

        cout << "Enter The Station Name To Delete: " << endl;
        getline(cin, stationToDelete);


    }

}

void admin::renameStation(vector<vector<string>> &line,Metro&metro) {
    cout << "Enter The Line Color For The Station: " << endl;

    string color;
    getline(cin, color);


    while (color != "Green" && color != "Red" && color != "Blue") {
        cout << "Please Enter A Valid Color: " << endl;
        getline(cin, color);
    }

    int lineIdx = -1;

    if (color == "Green") {
        lineIdx = 0;
    } else if (color == "Red") {
        lineIdx = 1;
    } else if (color == "Blue") {
        lineIdx = 2;
    }


    cout << "Enter The Current Station Name: " << endl;

    string currentStationName;
    getline(cin, currentStationName);


    cout << "Enter The New Station Name: " << endl;

    string newStationName;
    getline(cin, newStationName);

    while(true){

        for (auto& station : line[lineIdx]) {
            if (station == currentStationName) {
                station = newStationName;
                metro.delete_line(color);
                Metro::build_line(metro,color,line[lineIdx]);
                cout << "Station '" << currentStationName << "' Renamed to '" << newStationName << "' Successfully" << endl;
                return;
            }
        }
        cout << "Station '" << currentStationName << "' Not Found in Line " << color << endl;

        cout << "Enter The Current Station Name: " << endl;
        getline(cin, currentStationName);

        cout << "Enter The New Station Name: " << endl;
        getline(cin, newStationName);

    }

}



