#pragma once
#include<map>
#include<iostream>
#include<algorithm>

using namespace std;

class Statistics {

private:

    map<pair<string, string>, pair<int, int>> stat;

public:

    Statistics();

    void incrementPassengers(string stationName,int income);
    void incrementIncome(string stationName,int income);
    void showStatisticsDay(string date,string stationName);
    void showStatisticsMonth(string month, string stationName);
    void showStatisticsYear(string year, string stationName);

};
