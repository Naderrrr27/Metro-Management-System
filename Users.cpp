//
// Created by DELL on 4/25/2024.
//

#include "Users.h"
#include <string>
#include <cctype>
#include <iomanip>
#include  <bits/stdc++.h>
#include "admin.h"
#include "subscription.h"
#include "Statistics.h"
Users::Users(): Data()
{
    this->Data.id = 1;
}

Users::Users(string fname, string lname,string password, string email): Data()
{
    this->Data.email = email;
    this->Data.password = password;
    this->Data.fname = fname;
    this->Data.lname = lname;

    //usrData.insert({email, Data});
}

Users Users::Register(map<string, personalInformation> &usrData)
{
    string fname, lname, email, password;
    cout << "First Name:";
    cin >> fname;
    cout << "Last Name:";
    cin >> lname;
    email = Email(usrData);
    password = Password();

    Users newUser(fname, lname, password, email);
    usrData.insert({email, newUser.Data});
    isLogged_In = true;
    return newUser;
}
string Users::Email(map<string, personalInformation> &usrData)
{
    string email;
    bool check = 0;
    while (!check)
    {
        cout << "E-mail:";
        cin >>  email;
        email = ToLower(email);
        if (usrData.find(email) == usrData.end())
        {
            if (CheckTemplate(email))
            {
                check = true;
            }
            else cout << "Please Enter A valid E-mail\n";

        }
         else cout << "This email has already an account\n";

     }
    return email;
}
string Users::ToLower(string s)
{
    for (char &c: s)
    {
        tolower(c);
    }
    return s;
}
string Users::Password()
{
    bool check = false;
    string password;
    while(!check)
    {
        cout << "Password:";
         cin >> password;
        if (CheckPassword(password)) check = true;
        else cout << "Please enter a strong password\n";
    }
        return password;
}
bool Users::CheckTemplate(string email)
{
    regex templatee("^[A-Za-z]+[\\w | \\d]+@[a-z]+\\.[com | net]+");
    return regex_match(email, templatee);
}
bool Users::CheckPassword(string password)
{
    regex templatee("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d).{8,}$"
);

    if (password.length() < 4) return false;
    return regex_match(password, templatee);
}
Users Users::Login(map<string, personalInformation> &usrData)
{
    string email, password;
    bool check = false;
    Users newUser;
    while(!check)
    {
        cout << "Email:";
        cin >> email;
        email = ToLower(email);
        cout << "Password:"; cin >> password;
        if (email == "admin" && password == "admin")
        {
            isAdmin = true;
            isLogged_In = true;
            check  = true;
            return *this;
        }
            map<string, personalInformation>::iterator it = usrData.find(email);
            if (it == usrData.end()) cout << "This account doesn't exist\n";
            else
            {
                if (password == it->second.password)
                {
                    newUser.Data = it->second;
                    check = true;
                    cout << "User has logged in successfully\n";
                }
                else cout << "Username or password are wrong\n";
            }
        }
        isLogged_In = true;
    return newUser;
}
void Users::begin(map<string, personalInformation>& usrData, map<string, Plan>& plans, Metro& metro, unordered_map<string, vector<Ride>>& rides) {
    int operation = 0;

    cout << "Welcome To Metro Mate\n";

    while (true) {
        if (!isLogged_In) {
            cout << "Please choose an operation\n";
            cout << "1: Login\n2: Register\n3: Exit\n";
            cin >> operation;

            if (operation == 1) {
                *this = Login(usrData);
                isLogged_In = true;
            } else if (operation == 2) {
                *this = Register(usrData);
                isLogged_In = true;
            } else if (operation == 3) {
                break; // Exit the loop and terminate the program
            } else {
                cout << "Invalid choice. Please try again.\n";
                continue;
            }
        }

        if (isLogged_In && !isAdmin) {
            cout << "1: Check In\n2: Subscriptions\n3: Wallet\n4: Profile\n5: Ride History\n6: Log out\n";
            cin >> operation;

            switch (operation) {
            case 1:
                cout << endl;
                CheckIn(metro, *this, usrData, rides);
                break;
            case 2:
                cout << endl;
                Subscribtions(*this, usrData, plans,metro);
                break;
            case 3:
                cout << endl;
                Wallet(*this, usrData);
                break;
            case 4:
                cout << endl;
                Profile(*this, usrData);
                break;
            case 5:
                cout << endl;
                RideHistoryy(rides, usrData, *this);
                break;
            case 6:
                cout << endl;
                LogOut(*this);
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
            }
        }
        if (isLogged_In && isAdmin)
        {
            admin Admin;
            Admin.begin(*this,usrData, plans,metro,rides);
        }

    }

    cout << "Exiting Metro Mate. Goodbye!\n";
}
void Users::clear(Users &user)
{
    user = Users();
}
void Users::LogOut(Users &user)
{
    clear(user);
    this->isAdmin = false;
    this->isLogged_In = false;
    cout <<"Logged out\n";

}

void Users::Profile(Users &user, map<string, personalInformation> &usrData)
{

    int op = 0;
    map<string, personalInformation>::iterator users;
    while(op != 5)
    {
        users = usrData.find(user.GetEmail());
        cout << left << setw(30) << "Email"
            << setw(20) << "First Name"
            << setw(20) << "Last Name"
            << "Password" << endl;

        // Print user data
        cout << setw(30) << users->second.email
             << setw(20) << users->second.fname
             << setw(20) << users->second.lname
             << users->second.password << endl;
        cout << "1: Modify first name\n"
        << "2: Modify last name\n"
        << "3: Modify e-mail\n"
        << "4: Modify Password\n";
        cin >> op;
        if (op == 1)
        {
            cout << "First Name:";
            string fname; cin >> fname;
             users->second.fname = fname;
        }
        else if (op == 2)
        {
            cout << "Last Name:";
            string lname; cin >> lname;
            users->second.lname = lname;
        }
        else if (op == 3)
        {
            user.Data.email = Email(usrData);
            usrData.insert({user.Data.email, user.Data});
            usrData.erase(users);
            users = usrData.find(user.Data.email);
        }
        else if (op == 4)
        {
            string pass;
            bool check = false;
            while (!check)
            {
                cout << "Old password:";
                string pass; cin >> pass;
                if (pass == user.Data.password) check = 1;
                else cout << "Wrong Password\n";
            }
            pass = Password();
            users->second.password = pass;
        }
    }
}
void Users::Subscribtions(Users &user,map<string, personalInformation> &usrData, map<string, Plan> &plan,Metro &metro)
{
    subscription s;
    auto it = usrData.find(user.GetEmail());
        s.DisplaySubscriptionPlan(plan);
        cout << endl;
        int operation = 0;
        while (operation != 5) {
            if (it->second.plan.plan.PlanName.empty()) {
                cout << "1: Make Subscription\n2: Exist" << endl;
                cin >> operation;
                if (operation == 1) {
                    it->second.plan.chooseplan(plan,metro);
                    ///handelling stat
                    Statistics::incrementIncome( it->second.plan.StartDate, it->second.plan.firstDestination,it->second.plan.Price);
                } else if (operation == 2)
                    break;
            }
            else {
                cout << "1:Display your plan details\n2:Renew your plan\n3:Upgrade your plan\n4:Exit\n";
                cin >> operation;
                switch (operation) {
                    case 1:
                        cout << left << setw(15) << "Name"
                        << setw(20) << "From"
                        << setw(20) << "To"
                        << setw(10) << "Trips"
                        << setw(10) << "Stage"
                    << setw(10) << "Price"
                    << setw(15) << "Start Date"
                    << setw(15) << "End Date"
                    << endl;

                    // Displaying plan information in a formatted table
                    cout << setw(15) << it->second.plan.plan.PlanName
                         << setw(20) << it->second.plan.firstDestination
                         << setw(20) << it->second.plan.secondDestination
                         << setw(10) << it->second.plan.getTrips()
                         << setw(10) << it->second.plan.stage
                         << setw(10) << it->second.plan.Price
                         << setw(15) << it->second.plan.StartDate
                         << setw(15) << it->second.plan.Enddate << endl;
                    break;
                    case 2:
                        cout<<it->second.plan.Price<<" LE will be Deducted from your wallet\n";
                        cout<<"confirm\n1:Yes\n2:No";
                        int n;cin>>n;
                        if(n==1) {
                            it->second.plan.Renewplan();
                            cout << "Your plan is Renewed\n";
                            Statistics::incrementIncome( it->second.plan.StartDate, it->second.plan.firstDestination,it->second.plan.Price);
                        }
                        else
                            return;
                        break;
                    case 3:
                        it->second.plan.Upgrade(plan,metro);
                        cout << "Your plan is Upgraded\n";
                        Statistics::incrementIncome( it->second.plan.StartDate, it->second.plan.firstDestination,it->second.plan.Price);
                        break;
                    case 4:
                        return;
                }
            }
        }
    }
void Users::Charge(Users &user, map<string, personalInformation> &usrData){
    cout << "Balance:\n";
    auto currentUser = usrData.find(user.GetEmail());
    wallet wallett;
    int amount;
    while(true)
    {
         cin >> amount;
        if (amount % 10 == 0) {
            if( currentUser->second.balance.Addbalance(amount)==1)
                break;
        }
        else
          cout << "Invalid input please try again\n";

        }
        cout << "Successfull operation\n";
        cout << "Your current balance: " << currentUser->second.balance.getbalance() << endl;
}
void Users::Wallet(Users &user, map<string, personalInformation> &usrData)
{
    int op;
    auto currentUser = usrData.find(user.GetEmail());
    while (true)
    {
        cout << "1: Charge wallet\n";
        cout << "2: Check Balance\n";
        cout << "3: Back\n";
        cin >> op;
        if (op == 1) Charge(user, usrData);
        else if (op == 2)
        {
            cout << "Your Balance is " << currentUser->second.balance.Balance << endl;
        }
        if (op == 3) return;
    }
}
void Users::CheckIn(Metro& metro, Users& user, map<string, personalInformation> &usrData, unordered_map<string, vector<Ride>> &rides)
{
    wallet walet;
    Ride ride;
    string fstation,lstation;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    while(true) {
         fstation = getStationName(metro, ride, "Check in station:");
         lstation = getStationName(metro, ride, "Check out station:");
        if (fstation != lstation)
            break;
        else
            cout<<"Please enter the names of two different stations\n";
    }
    auto it = usrData.find(user.GetEmail());
    user.Data = it->second;
    bool involveInSubscription = user.Data.plan.IsStationValidInPlan(metro,ride,fstation,lstation);
    if (involveInSubscription && it->second.plan.Isplanactive(it->second.plan))
    {
        int choice;
        cout << "This Path is included in your subscription\n";
        cout << "1: Subscription\n";
        cout << "2: Buy A ticket\n";
        cout << "3: Exit\n";
        cin >> choice;
        if (choice == 1)
        {
            SubscriptionTrip(user, usrData, fstation, lstation, metro, ride, rides);
        }
        else if (choice == 2)
        {
            WalletTrip(user, usrData, fstation, lstation, metro, ride, rides);
        }
        else return;
    }
    else
    {
        WalletTrip(user, usrData, fstation, lstation, metro, ride, rides);
    }
}
string Users::getStationName(Metro& metro, Ride& ride, const string &stationName)
{
    string station;

    while (true)
    {

        cout << stationName;

        getline(cin, station);
        if (ride.exists(station, metro))
        {
            return station;
        }
        cout << "Invalid\n";
    }

}

void Users::WalletTrip(Users& user, map<string, personalInformation> &usrData, string &fdest, string &ldest, Metro& metro, Ride& ride, unordered_map<string, vector<Ride>> &rides)
{
    map<string, personalInformation>::iterator person = usrData.find(user.GetEmail());
    /*vector<int> sizes = ride.GetPathsSize(metro, fdest, ldest);
    for (int index: sizes)
    {
        int fare = person->second.plan.Stage(metro);
        cout << fare << endl;
    }*/
    user.Data = person->second;
    ride.getAllPaths(metro, fdest, ldest);

    cout << "1: Choose Path\n";
    cout << "7: Exit\n";
    int op; cin >> op;
    if (op == 1)
    {
        int numberOfPaths = ride.GetAllPathsSize();
        int path;
        while(true)
        {
            cout << "Path:";
            cin >> path;
            if (path <= numberOfPaths && path >= 1)
            {
                break;
            }
            if (path == 7) return;
            cout << "Invalid data\n";
        }

        ride.SetRideData(path, fdest, ldest, "Ticket", metro);
        if (person->second.balance.getbalance() < ride.getFare())
        {
            cout << "Your Balance is insufficent\n";
            return;
        }
        person->second.balance.Deduct(ride.getPathSize());
        auto rideMap = rides.find(person->first);
        if (rideMap == rides.end())
        {
            rides[person->first] = {ride};
        }
        else rideMap->second.push_back(ride);
        cout << "Your ticket has been reserved\n";
        ride.DisplayRideData();
        Statistics::incrementPassengers(ride.getDate(),fdest);
        Statistics::incrementIncome(ride.getDate(),fdest,ride.getFare());
        cout << endl;
    }
    }

void Users::SubscriptionTrip(Users& user, map<string, personalInformation> &usrData, string &fdest, string &ldest, Metro& metro, Ride& ride, unordered_map<string, vector<Ride>> &rides)
{
    auto person = usrData.find(user.GetEmail());
    int operation;
    vector<string> path = ride.bfsShortestPath(fdest, ldest, metro);
    cout << left << setw(20) << "From" << setw(20) << "To" << setw(20) << "Number of stations" << setw(20)
    << "Remaining Trips" << endl;
    cout << left << setw(20) << fdest << setw(20) << ldest << setw(20) << path.size() << setw(20) << person->second.plan.remainingtrips;
    cout << endl;
    ride.printShortestPath(path, metro);
    cout << "1: Reserve\n";
    cout << "2: Return\n";
    cin >> operation;
    if (operation == 1)
    {
        ride.SetRideData(1, fdest, ldest, "Subscription", metro);
        person->second.plan.remainingtrips--;
        auto personride = rides.find(person->first);
        if (personride == rides.end())
        {
            rides[person->first] = {ride};
        }
        else
            personride->second.push_back(ride);
        cout << "Your Ticket has been Reserved\n";
        ride.DisplayRideData();
        Statistics::incrementPassengers(ride.getDate(),fdest);
    }
}
void Users::RideHistoryy(unordered_map<string, vector<Ride>> &rides, map<string, personalInformation> &usrData, Users &users)
{
    auto usrHistory = rides.find(users.GetEmail());
    if (usrHistory != rides.end())
    {
        if (!usrHistory->second.empty())
        {
            cout << left << setw(15)<< "Type" << setw(15) << "From" << setw(15) << "To" << setw(15) << "Price" <<
            setw(15) << "stations" <<setw(15) << "Date" << setw(15) << "Time" << endl;

            for (auto ride: usrHistory->second)
            {
                ride.DisplayHistory();
                cout << endl;
            }
        }
    }
    else cout << "No Previous Rides\n\n";
}
Users::~Users()
{

}

