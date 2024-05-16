#pragma once
#include "Station.h"
#include "Line.h"
#include "Metro.h"

using namespace std;

Metro::Metro(string country_name) {
    this->country = country_name;
}

void Metro::add_new_line(Line& new_line) {
    this->lines[new_line.get_color()] = new_line;
}



Line &Metro::get_line(string &color) {
    return lines[color];
}

Metro::~Metro() {}

void Metro::build_line(Metro& metro, string color, vector<string>& station_names) {
    vector<Station> stations;

    for (auto& station_name : station_names) {
        Station station(station_name);
        stations.push_back(station);
    }
///////
    Line line(color);

    for (int i = 0; i < stations.size() - 1; i++) {
        stations[i].can_go_to(stations[i + 1]);
        stations[i + 1].can_go_to(stations[i]);
    }
///////
    for (auto& station : stations) {
        line.add_new_station(station.get_name(), station.get_neighbors());
    }

    metro.add_new_line(line);
}

unordered_map<string, Line> &Metro::get_lines() {
    return this->lines;
}

void Metro::delete_line(string color) {
    lines.erase(color);
}

//