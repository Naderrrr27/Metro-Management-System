//
// Created by DELL on 4/25/2024.
//

#include "Users.h"
#include <string>
#include <cctype>

#include "subscription.h"

Users::Users()
{
    this->Data.id = -1;
}
Users::Users(string fname, string lname,string password, string email)
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
    return newUser;
}
void Users::begin(map<string, personalInformation> &usrData, map<string, Plan> &plans)
{
    Users user;
    int operation = 0;
    cout << "Welcome To Metro Mate\n";


    while (operation != 3)
    {

        cout << "Please choose an operation\n";
        cout << "1: Login\n2: Register\n3: Exit\n";
        cin >> operation;
        if (operation == 1)
        {
            user =  user.Login(usrData);
        }
        else if (operation == 2)
        {
            user = user.Register(usrData);
        }
        if (operation != 3)
        {
            cout << "1: Subscribtions\n2: Profile\n3: Log out\n";
            operation = 0; cin >> operation;
            if (operation == 1) Subscribtions(user, plans);
            else if (operation == 2) Profile(user,usrData);
            else if (operation == 3) LogOut(user);
        }
    }
}
void Users::clear(Users &user)
{
    user = Users();
}
void Users::LogOut(Users &user)
{
    clear(user);
    cout <<"Logged out\n";

}

void Users::Profile(Users &user, map<string, personalInformation> &usrData)
{

    int op = 0;
    auto users = usrData.find(user.GetEmail());
    while(op != 5)
    {
        cout << "Email\t\t\t\tFirst Name\tLast Name\tPassword\n";
        cout << user.Data.email << "\t" << user.Data.fname << "\t\t" << user.Data.lname<< "\t\t" << user.Data.password;
        cout << "\n1: Modify first name\n2: Modify last name\n3: Modify e-mail\n4: Modify Password\n";
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
void Users::Subscribtions(Users &user, map<string, Plan> &plan)
{
    subscription s;
    s.Displayplandetails("student", plan);
    cout << endl;
    cout << "1: Make Subscription\n2: Remove Subscription\n3:Modify Subscription" << endl;
    int operation; cin >> operation;
}
Users::~Users()
{

}