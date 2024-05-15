//
// Created by pc on 01/05/2024.
//
#include "subscription.h"
#include "wallet.h"

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
    newplan.stageprices = prices;
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
    chrono::time_point<chrono::system_clock> start, end;
    start = chrono::system_clock::now();
    chrono::hours hoursInDays(plan.Duration * 24 * 30);
    end = start + hoursInDays;
    this->StartDate = Date(start);
    this->Enddate = Date(end);
}
void subscription::Upgrade(map<string, Plan> &plans,Metro metro) {

    DisplaySubscriptionPlan(plans);
    chooseplan(plans,metro);

}
void subscription::DisplaySubscriptionPlan(map<string, Plan> &plans)
{
    cout << left << setw(30) << "Name"
            << setw(30) << "Duration"
            << setw(30) << "Trips Allowed"
            /*<<setw(17)<<"Stage 1 Price"
            <<setw(17)<<"Stage 2 Price"
            <<setw(17)<<"Stage 3 Price"
            <<setw(17)<<"Stage 4 Price"*/
            << endl;

    // Print each plan
    for (const auto &it : plans) {
        std::cout << std::left << std::setw(30) << it.second.PlanName
                  << std::setw(30) << it.second.Duration
                  << std::setw(30) << it.second.tripsallowed;
        /*for (const auto &it2 : it.second.stageprices) {
            std::cout << std::setw(17) << it2.second;
        }*/
        std::cout << std::endl;
    }

        //remaining trips not trips allowed

}
//class methodes
int subscription::Stage(Metro &metro) {
    Ride ride;
     vector<string> v = ride.bfsShortestPath(firstDestination,secondDestination,metro);
     int stations =v.size();
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
void subscription::chooseplan(map<string, Plan> &plans,Metro &metro)
{
    Ride r;
    wallet wallett;
    cout << "Enter Plan Name:";
    string name;
    cin >> name;
auto it = plans.find(name);
    if (it != plans.end()) {
        plan = plans.find(name)->second;
        string first, last;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        while(true) {
            firstDestination = getStationName(metro, r, "From");
            secondDestination = getStationName(metro, r, "To");
            if(firstDestination!= secondDestination)
                break;
            else
                cout<<"Please enter the names of two different stations\n";
        }
        //set the plan for the user
        int stagee = Stage(metro);
        Price = this->plan.stageprices[stagee];
        cout << "the best stage for you is " << stagee;
        cout << " for " << Price << " LE" << endl;
        cout<<"Confirm subscription\n1:Yes\n2:No\n";
        int confirm;cin>>confirm;
        if(confirm==1) {
            plan.PlanName = plans[name].PlanName;
            plan.Duration = plans[name].Duration;
            plan.tripsallowed = plans[name].tripsallowed;
            stage = stagee;
            remainingtrips = plan.tripsallowed;
            Price=plans[name].stageprices[stage];
            chrono::time_point<chrono::system_clock> start, end;
            start = chrono::system_clock::now();
            chrono::hours hoursInDays(it->second.Duration * 24 * 30);
            end = start + hoursInDays;
            this->StartDate = Date(start);
            this->Enddate = Date(end);
        }
        else
            plan.PlanName={};
    }
    else
        cout << "Invalid plan name\n";
}
bool subscription::Isplanactive(subscription s) {
    chrono::time_point<chrono::system_clock> current;
    current = chrono::system_clock::now();
    string now=Date(current);
    if(s.remainingtrips>0 && now != s.Enddate)
        return true;
    else
        return false;
}
bool subscription::IsStationValidInPlan(Metro &metro, Ride &ride,std::string fdest, std::string ldest) {
    bool fcheck=false,lcheck=false;

    if(plan.PlanName.empty())
        return false;
    vector<string> check=ride.bfsShortestPath(firstDestination,secondDestination,metro);

    for (auto &str : check){
            if(str==fdest)
                fcheck=true;
            if(str==ldest)
                lcheck=true;
    }
    return fcheck&lcheck;
}
string subscription::Date(chrono::time_point<chrono::system_clock> start) {
    time_t start_t = chrono::system_clock::to_time_t(start);
    tm *local = localtime(&start_t);
    int year = 1900 + local->tm_year;
    int month = 1 + local->tm_mon;
    int day = local->tm_mday;
    return formatstring(day, month, year);
}
string subscription::formatstring(int day, int month, int year) {
    string formatted_day = (day < 10) ? "0" + to_string(day) : to_string(day);
    string formatted_month = (month < 10) ? "0" + to_string(month) : to_string(month);
    string formatted_year = to_string(year);

    return formatted_day + "/" + formatted_month + "/" + formatted_year;
}
string subscription::getStationName(Metro& metro, Ride& ride, const string &stationName)
{
    string station;

    while (true)
    {

        cout << stationName;

        getline(cin, station);
        if(!ride.exists(station, metro))
            cout << "Invalid\n";
        else
            return station;
       /* if (ride.exists(station, metro))
        {
            return station;
        }
        cout << "Invalid\n";*/
    }

}


