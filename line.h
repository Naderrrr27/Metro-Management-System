#pragma once
#include <string>
#include <unordered_map>
#include <map>
#include "Station.h"
#include <vector>

using namespace std;

class Station;

class Line {
private:
    string color;
    unordered_map<string,vector<Station>> stations;

public:

    Line();

    Line(string& color);

    ~Line();

    void add_new_station(string name, vector<Station>& stations);
    unordered_map<string, vector<Station>>& get_stations();
    string get_color();

};
