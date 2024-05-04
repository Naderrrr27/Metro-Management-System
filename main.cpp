#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include "Metro.h"
#include "Users.h"
#include "subscription.h"
#include <fstream>
using namespace std;
//


void testDFS(Metro &metro, string first, string second,unordered_map<string,bool> &visited,vector<string> &path,vector<vector<string>> &allPaths) {
    visited[first] = true;
    path.push_back(first);
    if (first == second) {
        allPaths.push_back(path);
    } else {
        for (auto &line: metro.get_lines()) {
            for (auto &station: line.second.get_stations()[first]) {
                if (!visited[station.get_name()]) {
                    testDFS(metro, station.get_name(), second, visited, path, allPaths);
                }
            }
        }
    }
    path.pop_back();
    visited[first] = false;
}

void print_all_paths(vector<vector<string>> &allPaths) {
    for (auto &path: allPaths) {
        cout << "Path : ";
        for (auto &station: path) {
            cout << station << " ";
        }
        cout << "\n";
    }
}
void get_all_paths(Metro &metro, string first, string second) {
    unordered_map<string,bool> visited;
    vector<string>path;
    vector<vector<string>> allPaths;
    testDFS(metro, first, second, visited, path, allPaths);

    print_all_paths(allPaths);

}


int write(map<string, personalInformation> &usrData) {
    ofstream outputFile("users.txt");

    if (outputFile.is_open()) {
        for (const auto &pair: usrData) {
            const personalInformation &user = pair.second;
            outputFile << user.id << ' '
                       << user.email << ' '
                       << user.password <<
                       ' ' << user.fname <<
                       ' ' << user.lname << '\n';
        }
        outputFile.close();
    } else {
        cerr << "Error: Unable to open file for writing." << endl;
        return 1;
    }
    return 0;
}

int read(map<string, personalInformation> &usrData) {
    ifstream inputFile("users.txt");
    if (!inputFile.is_open()) {
        cerr << "Error: Unable to open file for reading." << endl;
        return 1;
    }
    int userId;
    string email, password, fname, lname;
    while (inputFile >> userId >> email >> password >> fname >> lname) {
        personalInformation temp;
        temp.id = userId;
        temp.email = email;
        temp.password = password;
        temp.fname = fname;
        temp.lname = lname;
        usrData.emplace(email, temp);
    }

    inputFile.close();
    return 0;
}


int main() {
//    subscription sub;
//    map<string, Plan> plans;
//    //student plan
//    map<int, int> prices;
//    prices = {{1, 33},
//              {2, 41},
//              {3, 50},
//              {4, 65}};
//    sub.Addplan("student", 180, 3, prices, plans);
//    //public monthly plan
//    prices = {{1, 230},
//              {2, 290},
//              {3, 340},
//              {4, 450}};
//    sub.Addplan("publicmonthly", 60, 1, prices, plans);
//    // public yearly plan
//    prices = {{1, 1500},
//              {2, 2500},
//              {3, 3500},
//              {4, 4500}};
//    sub.Addplan("publicyearly", 730, 12, prices, plans);
//    map<string, personalInformation> mappp;
//
//    subscription plan;
//    read(mappp);
//    Users user;
//    for (auto it: mappp)
//        cout << it.first << endl;
//    user.begin(mappp, plans);
//    for (auto it: mappp)
//        cout << it.first << endl;


    Metro egypt_metro("Egypt");

    vector<string> green_line_stations = {
            "Adly Mansour", "El Haykesteb", "Omar Ibn El Khatab", "Qubaa", "Hesham Barakat",
            "El Nozha", "El Shams Club", "Alf Maskan", "Heliopolis", "Haroun", "El Ahram",
            "Kolleyet El Banat", "Stadium", "Fair Zone", "El Abassya", "Abdo Basha",
            "El Geish", "Bab El Shaarya", "Attaba", "Gamal Abd El Nasser", "Maspero",
            "Safaa Hegazy", "Kit Kat", "Sudan", "Imbaba", "El Bohy", "EL Qawmia",
            "Ring Road", "Mehwar Rod El Farag"
    };


    Metro::build_line(egypt_metro, "Green", green_line_stations);

    vector<string> red_line_stations = {
            "Shubra El Kheima", "Koleyet El Zeraa", "El Mazalat", "El Khalafawy",
            "Saint Threasa", "Rod El Farag", "Massara", "El Shohada", "Attaba",
            "Nageeb", "El Sadat", "Opera", "El Dokki", "El Behoos", "Cairo University",
            "Faysal", "El Giza", "Om El Masryeen", "Sakyet Mekky", "El Moneeb"
    };

    Metro::build_line(egypt_metro, "Red", red_line_stations);

    vector<string> blue_line_stations = {
            "New El Marg", "El Marg", "Ezbet El Nakhl", "Ain Shams", "Mattareya",
            "Helmeyet El Zaytoun", "Hadayek El Zaytoun", "Saraya El Qubba",
            "Hamamat El Qubba", "Kobry El Qubba", "Manshyet El Sadr", "El Demerdash",
            "Ghamra", "El Shohada", "Oraby", "Gamal Abd El Nasser", "El Sadat",
            "Saad Zaghloul", "Sayeda Zainab", "El Malek Saleh", "Mar Girgis",
            "El Zahraa", "Dar El Salam", "Hadayek El Maadi", "El Maadi",
            "Sakarat El Maadi", "Tura El Balad", "Kozzika", "Tura El Asmant",
            "El Maasara", "Hadayek Helwan", "Wadi Hof", "Helwan University",
            "Ain Helwan", "Helwan"
    };


    Metro::build_line(egypt_metro, "Blue", blue_line_stations);


    ///

    int cases=1;
//    cin >> cases;

    while (cases--) {
        string start="Attaba", final="Opera";
//        cin >> start >> final;
        get_all_paths(egypt_metro, start, final);

        cout << "\n\n\n";
    }

    ///



//    write(mappp);
    return 0;
}
