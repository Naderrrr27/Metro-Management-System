//
// Created by Roaa Hazem on 20/04/2024.
//

#ifndef UNTITLED4_RIDE_H
#define UNTITLED4_RIDE_H

#include <string>
#include <queue>
#include "Station.h"
#include "metro.h"
#include <unordered_map>
#include <unordered_set>
using namespace std;
class Ride {
private:
    ///To use in DFS
    struct PathExplorer{
        unordered_map<string,bool> visited;
        vector<vector<string>> allPaths;
        vector<string> path;
    };
    PathExplorer pathHandler;
    string firstD,finalD;
    string rideDate,rideTime;

    void prepareAllPaths(Metro &metro, string firstDestination, string &secondDestination);
    void printAllPaths(Metro &metro,string &firstDestination, string &secondDestination);
    string sameLineOrNot(Metro &metro,string &firstDestination,string &secDestination);
    string linkTwoStations(Metro &metro,string &firstDestination,string &secDestination,string &after,string &lineName, string &change);
    void setColor(string &lineName,string &color);
    void colorText(string &color, string text);
    bool checkTransformationPointOrNot(string &satationn);
    static bool compare (const vector<string>&v1, const vector<string>&v2);
public:
    Ride(string,string);
    Ride();
    ~Ride();
    void calculateRideDateTime();
    bool isExisted(string &first_station,string &second_station,Metro &metro);
    pair<int,int>getStationNumber(unordered_map<string, vector<Station>>& graphstring ,string ,string);
    vector<string>bfsShortestPath(unordered_map<string, vector<Station>>&graph ,string ,string);
    void getAllPaths(Metro &metro, string &firstDestination, string &);
    string getTime();
    string getDate();

};


#endif //UNTITLED4_RIDE_H