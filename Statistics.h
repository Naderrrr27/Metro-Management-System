#pragma once
#include<map>
#include<iostream>
#include<algorithm>
#include<string>
using namespace std;

class Statistics {

private:
    //      date   stationName    pass   income  noOfTickets
    static map<pair<string, string>, pair<int,pair<int,int>>> stat;

public:

    Statistics();

   static void incrementPassengers(string date,string stationName);
   static void incrementIncome(string date,string stationName,int income);
   static void incrementSoldTicket(string date,string stationName);

   static bool showStatisticsDay(string date,string stationName);
   static void showStatisticsMonth(string month, string stationName);
   static void showStatisticsYear(string year, string stationName);

};
