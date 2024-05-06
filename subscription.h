//
// Created by pc on 01/05/2024.
//

#ifndef UPDATED_SUBSCRIPTION_H
#define UPDATED_SUBSCRIPTION_H




#include<iostream>
#include<map>
#include<chrono>
#include<ctime>


using namespace std;
struct Plan {
    string PlanName="";
    int tripsallowed=0;
    //int Remainingtrips=0;
    int Duration=0;
    //int stage;
    //map<int, int>stageprices = {};
   // string firstdestination, finaldestination;

    //time
    //chrono::system_clock::time_point Startdate;
    //chrono::system_clock::time_point Enddate;
};
class subscription
{


    chrono::system_clock::time_point Startdate;
    chrono::system_clock::time_point Enddate;


public:
    string firstDestination, secondDestination;
    Plan plan;
  ;//oblect for the user
    //map to store plans

//methods
    subscription();
    subscription(Plan plan, string firstDestination, string secondDestination);
    void Addplan(string name, int trips, int duration, map<int, int> prices, map<string, Plan> &plans);
    void Removeplan(string planname, map<string, Plan> &plans);
    void Modifyplan(std::string planname, string newname, int newduration, int newtripsallowed, map<int, int> newprices,
                    map<string, Plan>& plans);
    //    void Modifyplan(string name, string newname, int newduration = -1, int newtripsallowed = -1, map<int, int> newprices = {}, map<string, Plan> &plans);
    int Stage();
    void chooseplan(map<string, Plan>& plans);
    void calcenddate(string planname, map<string, Plan> &plans);
    bool Isplanactive();
    void Renewplan();
    void Upgrade();
    void DisplaySubscriptionPlan(map<string, Plan>& plans);
    void Displayplandetails(string planName, map<string, Plan>& plans);
    void Remainingtrips();//msh 3arfa ahot name wala la
    string getPlanName()
    {
        return plan.PlanName;
    }
    int getTrips()
    {
        return plan.tripsallowed;
    }
    int getDuration()
    {
        return plan.Duration;
    }




    //from another class Ride
    int shortestpath(string first, string last);








};











#endif //UPDATED_SUBSCRIPTION_H
