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
    vector<string> ridePath;
    string firstD,finalD;
    string rideDate,rideTime;
    string subscriptionType;
    int fare;


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
    bool exists(string &station,Metro &metro);
    pair<int,int>getStationNumber(unordered_map<string, vector<Station>>& graphstring ,string ,string);
    vector<string> bfsShortestPath(string &first_station,string &second_station,Metro &metro);
    void fill_path(unordered_map<string,string>&parent,vector<string>&path,string root);
    void printShortestPath(vector<string>& path, Metro& metro);
    void getAllPaths(Metro &metro, string &firstDestination, string &);
    string getTime();
    string getDate();
    int getFare();
    void SetRideData(int pathNumber, string& fdest, string& ldest, const string& type, Metro& metro);
    void setFirstDestination(string &fdest);
    string getFirstDestination();
    int GetAllPathsSize();
    void DisplayRideData();
    void DisplayHistory();
    int getPathSize();
};


#endif //UNTITLED4_RIDE_H