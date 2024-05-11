//
// Created by Roaa Hazem on 20/04/2024.
//
//
#include <iostream>
#include <algorithm>
#include "Ride.h"

#include <iomanip>

#include "Station.h"
#include "metro.h"
#include "wallet.h"

Ride::Ride(string firstD, string finalD) {
    this->firstD=firstD;
    this->finalD=finalD;

}
Ride::Ride() {}
Ride::~Ride() {
}

///Shortest path
bool Ride::exists(string &station,Metro &metro) {
    for(auto &line : metro.get_lines()) {
        if(line.second.get_stations().count(station)){
            return true;
        }
    }
    return false;
}
vector<string> Ride::bfsShortestPath(string& first_station, string& second_station, Metro& metro) {

        queue<string>q;
        q.push(first_station);

        unordered_map<string,bool>visited;

        visited[first_station]=true;

        unordered_map<string,string>parent;
        parent[first_station]="-1";

        while(!q.empty()){

            string current_parent=q.front();
            q.pop();

            if(current_parent==second_station){
                break;
            }

            for(auto &line:metro.get_lines()){
                if(line.second.get_stations().count(current_parent)){
                    for(auto &child:line.second.get_stations()[current_parent]){
                        if(!visited[child.get_name()]){
                            visited[child.get_name()]=true;
                            parent[child.get_name()]=current_parent;
                            q.push(child.get_name());
                        }
                    }
                }
            }

        }
        vector<string> path;
        fill_path(parent,path,second_station);
        return path;
    }
void Ride::fill_path(unordered_map<string,string>&parent,vector<string>&path,string root) {
    if(root=="-1"){
        return;
    }
    else{
        fill_path(parent,path,parent[root]);
        path.push_back(root);
    }
}
void Ride::printShortestPath(vector<string>&path,Metro &metro){
    string lineNamee ,color , empty = "", change = "";
    if(!checkTransformationPointOrNot(path[0]))
        lineNamee = sameLineOrNot(metro,path[0],empty);
    else
        lineNamee = linkTwoStations(metro,path[1],path[0],empty,lineNamee,change);
    setColor(lineNamee,color);
    cout<<"\nPlease take the  \n";
    cout<<"                "<<"\\";
    colorText(color,"                 "+lineNamee + " line\n                  \\");
    cout<<"then take the following stations"<<" - ["<<path.size()<<"]stations";
    for (int i = 0 ; i < path.size() ; ++i) {
        if(i != 0){
            if(i != path.size()-1)
                color = linkTwoStations(metro,path[i-1],path[i],path[i+1],lineNamee,change);
            else
                color = linkTwoStations(metro,path[i-1],path[i],empty,lineNamee,change);
        }
        if(!change.empty()){
            cout<<"\n";
            cout<<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>_>>";
            system("echo \033[0m");
            cout<<change;
        }
        setColor(lineNamee,color);
        system(color.c_str());
        if(!change.empty()){
            cout<<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>_>>\n\n";
            change.clear();
        }
        cout<<path[i];
        if(i != path.size()-1)
            cout<<"\n|\n";
    }
    system("echo \033[0m");
    cout<<"_\n\n";
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
    wallet Fare;
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
        cout<<"then take the following stations (path "<<pathCount <<" - ["<<path.size()<<"]stations" << " - ["  << Fare.Ticketprice(path.size()) <<"]LE) :";
        for (int i = 0 ; i < path.size() ; ++i) {
            if(i != 0){
                if(i != path.size()-1)
                    color = linkTwoStations(metro,path[i-1],path[i],path[i+1],lineNamee,change);
                else
                    color = linkTwoStations(metro,path[i-1],path[i],empty,lineNamee,change);
            }
            if(!change.empty()){
                cout<<"\n";
                cout<<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>_>>";
                system("echo \033[0m");
                cout<<change;
            }
            setColor(lineNamee,color);
            system(color.c_str());
            if(!change.empty()){
                cout<<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>_>>\n\n";
                change.clear();
            }
            cout<<path[i];
            if(i != path.size()-1)
                cout<<"\n|\n";
        }
        system("echo \033[0m");
        cout<<"\n\n";
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
////stuffs to handle Ride date
int Ride::getFare(){
    return fare;
}
void Ride::SetRideData(int pathNumber, string &fdest, string &ldest, const string &type, Metro &metro){
    wallet ticketPrice;
    subscriptionType = type;
    if (subscriptionType == "Subscription")
    {
        fare = 0;
        ridePath = bfsShortestPath(fdest, ldest, metro);

    }


    else
    {
        fare = ticketPrice.Ticketprice((int)ridePath.size());
        ridePath = pathHandler.allPaths[pathNumber - 1];
    }
    firstD = fdest;
    finalD = ldest;
    calculateRideDateTime();
}
int Ride::GetAllPathsSize(){
    return (int)pathHandler.allPaths.size();
}
void Ride::DisplayRideData()
{
    cout << left << setw(15)<< "Type" << setw(15) << "From" << setw(15) << "To" << setw(15) << "Price" <<
       setw(15) << "stations" <<setw(15) << "Date" << setw(15) << "Time" << endl;
    cout << left << setw(15)<< subscriptionType << setw(15) << firstD << setw(15) << finalD << setw(15) << fare <<
   setw(15) << ridePath.size() <<setw(15) << rideDate << setw(15) << rideTime << endl;
}






