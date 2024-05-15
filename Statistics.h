#pragma once
#include<map>
#include<iostream>
#include<algorithm>
#include<string>
using namespace std;

class Statistics {

private:
    //      date   stationName    pass   income  noOfTickets
    map<pair<string, string>, pair<int,pair<int,int>>> stat;

public:

    Statistics();

    void incrementPassengers(string stationName,int income);
    void incrementIncome(string stationName,int income);
    void incrementSoldTicket(string stationName);
    void showStatisticsDay(string date,string stationName);
    void showStatisticsMonth(string month, string stationName);
    void showStatisticsYear(string year, string stationName);

};
