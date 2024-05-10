#pragma once
#include "Station.h"
#include "Line.h"

using namespace std;

Station::Station(string name) : name(name){}

Station::~Station() {}

void Station::can_go_to(Station& to) {
    this->to.push_back(to);
}

string Station::get_name() {
    return this->name;
}

vector<Station> & Station::get_neighbors() {
    return this->to;
}
//