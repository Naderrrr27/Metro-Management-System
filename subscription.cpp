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
        plans.erase(planname);
}
void subscription::Modifyplan(map<string, Plan> &plans,std::string planname, string newname, int newduration, int newtripsallowed, map<int, int> newprices) {
    auto key = plans.find(planname);
        if (!newname.empty())
            key->second.PlanName = newname;
        if (newduration != -1)
            key->second.Duration = newduration;
        if (newtripsallowed != -1)
            key->second.tripsallowed = newtripsallowed;
        if(!newprices.empty())
            key->second.stageprices=newprices;
}
//User methodes
void subscription::Renewplan() {
    remainingtrips = plan.tripsallowed;
    //renew time
}
void subscription::Upgrade(map<string, Plan> &plans) {

    DisplaySubscriptionPlan(plans);
    chooseplan(plans);

}
void subscription::DisplaySubscriptionPlan(map<string, Plan> &plans)
{
    cout << left << setw(30) << "Name"
            << setw(30) << "Duration"
            << setw(30) << "Trips Allowed"
           /* <<setw(17)<<"Stage 1 Price"
            <<setw(17)<<"Stage 2 Price"
            <<setw(17)<<"Stage 3 Price"
            <<setw(17)<<"Stage 4 Price"*/
            << endl;

    // Print each plan
    for (const auto &it : plans) {
        cout << setw(30) << it.second.PlanName
             << setw(30) << it.second.Duration
             << setw(30) << it.second.tripsallowed<<endl ;
            /* for(auto &it2 : it.second.stageprices)
                    cout <<setw(15)<<it2.second;*/
             cout<< endl;
        //remaining trips not trips allowed
    }

}
//class methodes
int subscription::Stage() {
    int stations = shortestpath(firstDestination, secondDestination);
    if (stations >= 1 && stations <= 9) {
        return 1;
    }
    else if (stations > 9 && stations <= 16) {
        return 2;
    }
    else if (stations > 16 && stations <= 23){
        return 3;
    }
    else{
        return 4;
    }
}
void subscription::chooseplan(map<string, Plan> &plans)
{
    cout << "Enter Plan Name:";
    string name;
    cin >> name;
auto it =plans.find(name);
    if (it != plans.end()) {
        plan = plans.find(name)->second;
        string first, last;
        cout << "From:";
        cin >> first;
        cout << "To:";
        cin >> last;
        //set the plan for the user
        firstDestination = first;
        secondDestination = last;
        cout << "the best stage for you is " << Stage() << endl;

        plan.PlanName = plans[name].PlanName;
        plan.Duration = plans[name].Duration;
        plan.tripsallowed = plans[name].tripsallowed;
        stage = Stage();
        remainingtrips = plan.tripsallowed;
    }
    else
        cout<<"invalid plan name\n";
}

/*void subscription::Date() {
    //chrono::system_clock::time_point Startdate;
    std::time_t start_time = std::time(0);
     start_tm = std::localtime(&start_time);
    chrono::hours durationToAdd(24 * 30*plan.Duration);
    chrono::system_clock::time_point end_time_point = std::chrono::system_clock::from_time_t(start_time)+ durationToAdd;
    time_t end_time_t = std::chrono::system_clock::to_time_t(end_time_point);
    // Convert end time to tm structure for formatting
     end_tm = std::localtime(&end_time_t);
}*/
bool subscription::Isplanactive() {
    chrono::system_clock::time_point now = std::chrono::system_clock::now();

  if (remainingtrips > 0 )
        return true;

    else
       return false;
}


//feha klam ayza akhod object mn class tane
void subscription::Remainingtrips() {
    //plan.Remainingtrips = plan.tripsallowed;
}


//3lshan elpro
int subscription::shortestpath(std::string first, std::string last) {
    return 1;
}



