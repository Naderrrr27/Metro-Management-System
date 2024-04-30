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
class subscription
{
public:

    struct Plan {
        string PlanName="";
        int tripsallowed=0;
        int Remainingtrips=0;
        int Duration=0;
        int stage;
        map<int, int>stageprices = {};
        string firstdestination, finaldestination;

        //time
        chrono::system_clock::time_point Startdate;
        chrono::system_clock::time_point Enddate;


    }plan;//oblect for the user


    //map to store plans
    map<string, Plan> plans;

//methods
    subscription();
    void Addplan(string name, int trips, int duration, map<int, int> prices);
    void Removeplan(string planname);
    void Modifyplan(string name, string newname = {}, int newduration = -1, int newtripsallowed = -1, map<int, int> newprices = {});
    int Stage();
    void chooseplan();
    void calcenddate(string planname);
    bool Isplanactive();
    void Renewplan();
    void Upgrade();
    void Displayplandetails();
    void Remainingtrips();//msh 3arfa ahot name wala la



    //from another class Ride
    int shortestpath(string first, string last);








};











#endif //UPDATED_SUBSCRIPTION_H
