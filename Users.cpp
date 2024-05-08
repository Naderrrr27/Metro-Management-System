//
// Created by DELL on 4/25/2024.
//

#include "Users.h"
#include <string>
#include <cctype>
#include <iomanip>

#include "admin.h"
#include "subscription.h"

Users::Users(): Data()
{
    this->Data.id = -1;
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
        cout << "Password: ";
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
void Users::begin(map<string, personalInformation>& usrData, map<string, Plan>& plans) {
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
            cout << "1: Subscriptions\n2: Profile\n3: Log out\n";
            cin >> operation;

            switch (operation) {
            case 1:
                Subscribtions(*this, usrData, plans);
                break;
            case 2:
                Profile(*this, usrData);
                break;
            case 3:
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
            Admin.begin(*this,usrData, plans);
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
void Users::Subscribtions(Users &user,map<string, personalInformation> &usrData, map<string, Plan> &plan)
{
    subscription s;
    auto it = usrData.find(user.GetEmail());
        s.DisplaySubscriptionPlan(plan);
        int operation = 0;
        while (operation != 5) {
            cout << "1: Make Subscription\n2: Manage Subscribtions\n" << endl;
            cin >> operation;

            if (operation == 1) {
                it->second.plan.chooseplan(plan);
            } else if (operation == 2) {
                cout << left << setw(20) << "Name"
                     << setw(15) << "From"
                     << setw(15) << "To"
                     << setw(15) << "Trips"
                     << setw(15) << "Stage"
                     << setw(15) << "Start Date"
                     << setw(15) << "End Date"
                     << endl;

                // Displaying plan information in a formatted table
                cout << setw(20) << it->second.plan.plan.PlanName
                     << setw(15) << it->second.plan.firstDestination
                     << setw(15) << it->second.plan.secondDestination
                     << setw(15) << it->second.plan.getTrips()
                     << setw(15) << it->second.plan.stage
                     << setw(15) << it->second.plan.StartDate
                     << setw(15) << it->second.plan.Enddate << endl;
                cout << "1: Renew Plan\n2: Upgrade Plan\n";
                int n;
                cin >> n;
                if (n == 1)
                    it->second.plan.Renewplan();
                else if (n == 2)
                    it->second.plan.Upgrade(plan);
            }


        }
    }


Users::~Users()
{

}