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
    tm* start_tm;
    tm* end_tm;

    Plan plan;

    //
    Ride ride;

//methods
    subscription();
    subscription(Plan plan, string firstDestination, string secondDestination);
    void Addplan(string name, int trips, int duration, map<int, int> prices, map<string, Plan> &plans);
    void Removeplan(string planname, map<string, Plan> &plans);
    void Modifyplan(std::map<string, Plan>& plans,string planname, string newname="", int newduration=-1, int newtripsallowed=-1, map<int, int> newprices={});
    int Stage();
    void chooseplan(map<string, Plan>& plans);
    void Date();
    bool Isplanactive();
    void Renewplan();
    void Upgrade(map<string, Plan> &plans);
    void DisplaySubscriptionPlan(map<string, Plan>& plans);
    void Remainingtrips();//msh 3arfa ahot name wala la
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




    //from another class Ride
    int shortestpath(string first, string last);








};











#endif //UPDATED_SUBSCRIPTION_H
