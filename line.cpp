#pragma once
#include "Station.h"
#include "Line.h"

using namespace std;

Line::Line(string& color) {
    this->color = color;
}

Line::~Line() {}

string Line::get_color() {
    return this->color;
}

void Line::add_new_station(string name, vector<Station>& stations) {
    this->stations[name] = stations;
}

Line::Line() {
}

unordered_map<string,vector<Station>> &Line::get_stations() {
    return this->stations;
}
