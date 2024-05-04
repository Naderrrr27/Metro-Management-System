//
// Created by pc on 01/05/2024.
//
#include "subscription.h"


subscription::subscription() {

    plan.Duration = 0;

}
//Admin methodes
void subscription::Addplan(string name, int trips, int duration, map<int, int> prices, map<string, Plan> &plans) {
    Plan newplan;
    newplan.PlanName = name;
    newplan.tripsallowed = trips;
    newplan.Duration = duration;
    newplan.stageprices = prices;

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
        if (!newprices.empty())
            key->second.stageprices = newprices;
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
    cout << "plan remaining trips" << " " << it->second.Remainingtrips <<  endl;
    //calcenddate();
    time_t start_time = chrono::system_clock::to_time_t(it->second.Startdate);
    time_t end_time = chrono::system_clock::to_time_t(it->second.Enddate);
#pragma warning(suppress : 4996)
    tm* start_tm = localtime(&start_time);
#pragma warning(suppress : 4996)
    tm* end_tm = localtime(&end_time);
    // Output the start and end dates
#pragma warning(suppress : 4996)
    cout << "Subscription start date: " << start_tm->tm_mday << "/" << start_tm->tm_mon + 1 << "/" << start_tm->tm_year + 1900 << endl;
#pragma warning(suppress : 4996)
    cout << "Subscription end date  : " << end_tm->tm_mday << "/" << end_tm->tm_mon + 1 << "/" << end_tm->tm_year + 1900 << endl;

}
void subscription::Upgrade() {



}
//class methodes
int subscription::Stage() {
    int stations = shortestpath(plan.firstdestination, plan.finaldestination);
    if (stations >= 1 && stations <= 9)
        return 1;
    else if (stations > 9 && stations <= 16)
        return 2;
    else if (stations > 16 && stations <= 23)
        return 3;
    else
        return 4;
}
void subscription::chooseplan(map<string, Plan> &plans) {

    for (auto it : plans) {
        if (plan.PlanName != it.second.PlanName) {
            cout << "Plan name " << it.second.PlanName << endl;
            cout << "Trips allowed " << it.second.tripsallowed << endl;
            cout << "Duration " << it.second.Duration << " months" << endl;
            for (int i = 1; i <= it.second.stageprices.size(); i++)
                cout << "stage " << i << " = " << it.second.stageprices[i] << endl;
        }
    }
    //plan name
    string name;
    cin >> name;
    //set first and last dis
    string first, last;
    cin >> first >> last;
    //set the plan for the useer

    plan.firstdestination = first;
    plan.finaldestination = last;
    cout << "the best stage for you is " << Stage()<<endl;

    plan.Startdate = std::chrono::system_clock::now();
    //calcenddate(name);
    plan.PlanName = plans[name].PlanName;
    plan.Duration = plans[name].Duration;
    plan.tripsallowed = plans[name].tripsallowed;
    plan.Remainingtrips = plan.tripsallowed;
    plan.stage = Stage();


}
void subscription::calcenddate(std::string planname, map<string, Plan> &plans) {

    int duration = plans[planname].Duration;
    plan.Enddate= plan.Startdate + chrono::hours(duration * 30 * 24);

}
bool subscription::Isplanactive() {
    chrono::system_clock::time_point now = std::chrono::system_clock::now();

    if (plan.Remainingtrips > 0 || now<plan.Enddate)
        return true;

    else
        return false;
}


//feha klam ayza akhod object mn class tane
void subscription::Remainingtrips() {
    plan.Remainingtrips = plan.tripsallowed;
}


//3lshan elpro
int subscription::shortestpath(std::string first, std::string last) {
    return 1;
}



