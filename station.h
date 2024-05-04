#pragma once
#include "Line.h"
#include <string>
#include <vector>

using namespace std;

class Line;

class Station {
private:
    string name;
    vector<Station> to;

public:

    Station(std::string name);
    ~Station();

    string get_name();
    vector<Station>& get_neighbors();
    void can_go_to(Station& to);
};

//