//
// Created by pc on 01/05/2024.
//
#include "subscription.h"

#include <iomanip>




subscription::subscription() {

    plan.Duration = 0;

}
//Admin methodes
void subscription::Addplan(string name, int trips, int duration, map<int, int> prices, map<string, Plan> &plans) {
    Plan newplan;
    newplan.PlanName = name;
    newplan.tripsallowed = trips;
    newplan.Duration = duration;
    //newplan.stageprices = prices;

    plans[name] = newplan;

}
void subscription::Removeplan(std::string planname, map<string, Plan> &plans) {
    auto it = plans.find(planname);
    if (it != plans.end())
        plans.erase(it);
}
void subscription::Modifyplan(std::string planname, string newname, int newduration, int newtripsallowed, map<int, int> newprices, map<string, Plan> &plans) {
    auto key = plans.find(planname);
    if (key != plans.end()) {
        if (!newname.empty())
            key->second.PlanName = newname;
        if (newduration != -1)
            key->second.Duration = newduration;
        if (newtripsallowed != -1)
            key->second.tripsallowed = newtripsallowed;
        else
            cout << "plan is not found";


    }



}
//User methodes
/*
void subscription::Renewplan() {
    plan.Startdate = std::chrono::system_clock::now();
    calcenddate(plan.PlanName);
    plan.Remainingtrips = plan.tripsallowed;
}
*/
void subscription::Displayplandetails(string planName, map<string, Plan> &plans) {
    auto it = plans.find(planName);
    cout << "plan name: " << " " << it->second.PlanName <<endl;
    cout << "plan Duration: " << " " << it->second.Duration <<  endl;
    cout << "plan Trips Allowed" << " " << it->second.tripsallowed <<  endl;
  //  cout << "plan remaining trips" << " " << it->second.Remainingtrips <<  endl;
    //calcenddate();
    //time_t start_time = chrono::system_clock::to_time_t(it->second.Startdate);
    //time_t end_time = chrono::system_clock::to_time_t(it->second.Enddate);
#pragma warning(suppress : 4996)
    //tm* start_tm = localtime(&start_time);
#pragma warning(suppress : 4996)
    //tm* end_tm = localtime(&end_time);
    // Output the start and end dates
#pragma warning(suppress : 4996)
    //cout << "Subscription start date: " << start_tm->tm_mday << "/" << start_tm->tm_mon + 1 << "/" << start_tm->tm_year + 1900 << endl;
#pragma warning(suppress : 4996)
    //cout << "Subscription end date  : " << end_tm->tm_mday << "/" << end_tm->tm_mon + 1 << "/" << end_tm->tm_year + 1900 << endl;

}
void subscription::Upgrade() {



}
void subscription::DisplaySubscriptionPlan(map<string, Plan> &plans)
{
    cout << left << setw(30) << "Name"
            << setw(30) << "Duration"
            << setw(30) << "Trips Allowed" << endl;

    // Print each plan
    for (const auto &it : plans) {
        cout << setw(30) << it.second.PlanName
             << setw(30) << it.second.Duration
             << setw(30) << it.second.tripsallowed << endl;
    }

}
//class methodes
int subscription::Stage() {
    int stations = shortestpath(firstDestination, secondDestination);
    if (stations >= 1 && stations <= 9)
        return 1;
    else if (stations > 9 && stations <= 16)
        return 2;
    else if (stations > 16 && stations <= 23)
        return 3;
    else
        return 4;
}
void subscription::chooseplan(map<string, Plan> &plans)
{

    /*for (auto it : plans) {
        /*if (plan.PlanName != it.second.PlanName) {
            cout << "Plan name " << it.second.PlanName << endl;
            cout << "Trips allowed " << it.second.tripsallowed << endl;
            cout << "Duration " << it.second.Duration << " months" << endl;

            /*for (int i = 1; i <= it.second.stageprices.size(); i++)
                cout << "stage " << i << " = " << it.second.stageprices[i] << endl;#2#
        }
    }#1#*/
    //plan name
    cout << "Enter Plan Name:";
    string name;
    // show number of plans
    cin >> name;
    //set first and last dis

    plan = plans.find(name)->second;
    string first, last;
    cout << "From:";
    cin >> first;
    cout << "To:";
    cin >> last;
    //set the plan for the useer
    firstDestination = first;
    secondDestination = last;
    cout << "the best stage for you is " << Stage()<<endl;

   // plan.Startdate = std::chrono::system_clock::now();
    //calcenddate(name);
    plan.PlanName = plans[name].PlanName;
    plan.Duration = plans[name].Duration;
    plan.tripsallowed = plans[name].tripsallowed;
   // plan.Remainingtrips = plan.tripsallowed;
    // plan.stage = Stage();
}
void subscription::calcenddate(std::string planname, map<string, Plan> &plans) {

    int duration = plans[planname].Duration;
    //plan.Enddate= plan.Startdate + chrono::hours(duration * 30 * 24);

}
bool subscription::Isplanactive() {
    /*chrono::system_clock::time_point now = std::chrono::system_clock::now();

    if (plan.Remainingtrips > 0 || now<plan.Enddate)
        return true;

    else
        return false;*/
}


//feha klam ayza akhod object mn class tane
void subscription::Remainingtrips() {
    //plan.Remainingtrips = plan.tripsallowed;
}


//3lshan elpro
int subscription::shortestpath(std::string first, std::string last) {
    return 1;
}



