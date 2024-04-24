#pragma once
#include <string>
#include <unordered_map>
#include "Line.h"

using namespace std;

class Metro {
private:
    string country;
    unordered_map<string, Line> lines;

public:
    Metro(string country_name);

    ~Metro();

    Line& get_line(string& color);

    void add_new_line(Line& new_line);

    static void build_line(Metro& metro, string color, vector<string>& stationNames);

};

