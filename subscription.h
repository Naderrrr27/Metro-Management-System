//
// Created by pc on 01/05/2024.
//

#ifndef UPDATED_SUBSCRIPTION_H
#define UPDATED_SUBSCRIPTION_H




#include<iostream>
#include<cmath>
#include<map>
#include<chrono>
#include<ctime>
#include "metro.h"
#include "Ride.h"


using namespace std;
struct Plan {
    string PlanName="";
    int tripsallowed=0;
    int Duration=0;
   map<int, int>stageprices = {};
};
class subscription
{
public:
    string firstDestination, secondDestination;
    int remainingtrips;
    int stage;
    int Price;
    string StartDate;
    string Enddate;

    Plan plan;


//methods
    subscription();
    void Addplan(string name, int trips, int duration, map<int, int> prices, map<string, Plan> &plans);
    void Removeplan(string planname, map<string, Plan> &plans);
    void Modifyplan(std::map<string, Plan>& plans,string planname, string newname="", int newduration=-1, int newtripsallowed=-1, map<int, int> newprices={});
    void chooseplan(map<string, Plan>& plans,Metro &metro);
    void Renewplan();
    void Upgrade(map<string, Plan> &plans,Metro metro);
    bool Isplanactive(subscription s);
    bool IsStationValidInPlan(Metro &metro,string fdest,string ldest);
    void DisplaySubscriptionPlan(map<string, Plan>& plans);
    int Stage(Metro &metro);
    string Date(chrono::time_point<chrono::system_clock> start);
    string formatstring(int day, int month, int year);
    string getStationName(Metro& metro, Ride& ride, const string& stationName);

    string getPlanName()
    {
        return plan.PlanName;
    }
    int getTrips()
    {
        return remainingtrips;
    }
    int getDuration()
    {
        return plan.Duration;
    }


};











#endif //UPDATED_SUBSCRIPTION_H
