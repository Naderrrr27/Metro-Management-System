//
// Created by Roaa Hazem on 20/04/2024.
//
//
#include <iostream>
#include <algorithm>
#include "Ride.h"
#include "Station.h"
#include "metro.h"
Ride::Ride(string firstD, string finalD) {
    this->firstD=firstD;
    this->finalD=finalD;

}
Ride::Ride() {}
Ride::~Ride() {
}

vector<string> Ride::bfsShortestPath(unordered_map<string, vector<Station>>& graph, string firstD, string finalD) {

    if(!graph.count(firstD)||!graph.count(finalD)){
        cout<<"change the Destination ";
        return {};
    }
    else{
        queue<pair<string, vector<string>>> q;
        unordered_set<string> visited;

        q.push({firstD, {firstD}});
        visited.insert(firstD);

        while (!q.empty()) {
            auto current = q.front();
            q.pop();
            string currentNode = current.first;
            vector<string> pathSoFar = current.second;

            if (currentNode == finalD) {
                return pathSoFar;
            }

            for (Station neighbor: graph.at(currentNode)) {
                if (visited.find(neighbor.get_name()) == visited.end()) {
                    visited.insert(neighbor.get_name());
                    vector<string> newPath = pathSoFar;
                    newPath.push_back(neighbor.get_name());
                    q.push({neighbor.get_name(), newPath});
                }
            }
        }
    }

}
///Get All paths
bool Ride::compare(const vector<string>&v1, const vector<string>&v2){
    return v1.size() < v2.size(); /// false v2 before v1..
}
void Ride::prepareAllPaths(Metro &metro, string firstDestination, string &secondDestination){

    pathHandler.visited[firstDestination] = true;
    pathHandler.path.push_back(firstDestination);
    if (firstDestination == secondDestination) {
        pathHandler.allPaths.push_back(pathHandler.path);
    } else {
        for (auto &line: metro.get_lines()) {
            if(line.second.get_stations().count(firstDestination)) {
                for (auto &station: line.second.get_stations()[firstDestination]) {
                    if (!pathHandler.visited[station.get_name()]) {
                        prepareAllPaths(metro, station.get_name(), secondDestination);
                    }
                }
            }
        }
    }
    pathHandler.path.pop_back();
    pathHandler.visited[firstDestination] = false;
}
string Ride::sameLineOrNot(Metro &metro,string &firstDestination,string &secDestination){
    string lineName;
    vector<string>colors = {"Green", "Red", "Blue"};
    vector<pair<int,int>>checkLines(4,{0,0});
    unordered_map<string,vector<Station>>check;
    for (int i = 0; i < colors.size(); ++i) {
        check = metro.get_line(colors[i]).get_stations();
        checkLines[i+1].first = check.count(firstDestination);
        if(secDestination != "")
            checkLines[i+1].second = check.count(secDestination);

    }
    for (int i = 1; i <= 3 ; ++i) {
        if(secDestination != ""){
            if(checkLines[i].first == 1 && checkLines[i].first == checkLines[i].second){
                lineName = colors[i-1];
            }
        }else{
            if(checkLines[i].first == 1)
                lineName = colors[i-1];;
        }
    }
    return lineName;
}
void Ride::setColor(string &lineName, string &color){
    if(lineName == "Green")
        color = "echo  \033[32m";
    else if(lineName == "Red")
        color = "echo  \033[31m";
    else
        color = "echo  \033[34m";
}
void Ride::colorText(string &color ,string text){
    system(color.c_str());
    cout << text;
    system("echo \033[0m");
}
bool Ride::checkTransformationPointOrNot(string &satationn){
    if(satationn == "El Shohada" || satationn == "Gamal Abd El Nasser" || satationn == "El Sadat" || satationn == "Attaba" ){
        return true;
    }
    return false;
}
string Ride::linkTwoStations(Metro &metro,string &firstDestination,string &secDestination,string &after,string &lineName,string &change){
    string coloeur = sameLineOrNot(metro,firstDestination,secDestination);
    if(coloeur == lineName)
        return lineName;
    else{
        if(!checkTransformationPointOrNot(secDestination) || after.empty()){
            lineName = coloeur;
            change = firstDestination + " is a transformation point ,please change to "+lineName+"line";
            return coloeur;
        }else{
            string coloeur2 = sameLineOrNot(metro,secDestination,after);
            lineName = coloeur2;
            change = firstDestination + " is a transformation point , please change to "+lineName+"line";
            return coloeur2;
        }
    }
}
void Ride::printAllPaths(Metro &metro,string &firstDestination, string &secondDestination){
    string lineNamee ,color , empty = "", change = "";
    int pathCount = 1;
    cout << "All Paths from " << firstDestination << " to " << secondDestination<<" : ";
    for (auto &path: pathHandler.allPaths) {
        if(!checkTransformationPointOrNot(path[0]))
            lineNamee = sameLineOrNot(metro,path[0],empty);
        else
            lineNamee = linkTwoStations(metro,path[1],path[0],empty,lineNamee,change);
        setColor(lineNamee,color);
        cout<<"\nPlease take the  \n";
        cout<<"                "<<"\\";
        colorText(color,"                 "+lineNamee + " line\n                  \\");
        cout<<"then take the following stations (path "<<pathCount <<" -["<<path.size()<<"]stations"<<") :";;
        for (int i = 0 ; i < path.size() ; ++i) {
            if(i != 0){
                if(i != path.size()-1)
                    color = linkTwoStations(metro,path[i-1],path[i],path[i+1],lineNamee,change);
                else
                    color = linkTwoStations(metro,path[i-1],path[i],empty,lineNamee,change);
            }
            if(!change.empty()){
                cout<<"\n";
                cout<<"_>_>__>_>_>_>_>_>_>_>_>_>_>_>";
                system("echo \033[0m");
                cout<<change;
            }
            setColor(lineNamee,color);
            system(color.c_str());
            if(!change.empty()){
                cout<<"_>_>__>_>_>_>_>_>_>_>_>_>_>_>\n\n";
                change.clear();
            }
            cout<<path[i];
            if(i != path.size()-1)
                cout<<"\n|\n";
        }
        system("echo \033[0m");
        cout<<"________________________________________\n\n";
        pathCount++;
    }
}
void Ride::getAllPaths(Metro &metro, string &firstDestination, string &secondDestination){
    prepareAllPaths(metro,firstDestination,secondDestination);
    sort(pathHandler.allPaths.begin(),pathHandler.allPaths.end(), Ride::compare);
    printAllPaths(metro, firstDestination, secondDestination);
}
////Handel time and date
void Ride::calculateRideDateTime(){
    time_t t = time(0);
    tm* now = localtime(&t);
    rideDate.append(to_string(now->tm_mon + 1));
    rideDate.append("-");
    rideDate.append(to_string(now->tm_mday));
    rideDate.append("-");
    rideDate.append(to_string(now->tm_year + 1900));

    rideTime.append(to_string(now->tm_hour));
    rideTime.append(":");
    rideTime.append(to_string(now->tm_min));
    rideTime.append(":");
    rideTime.append(to_string(now->tm_sec));
}
string Ride::getTime(){
    return rideTime;
}
string Ride::getDate(){
    return rideDate;
}