#pragma once
#include <iostream>
#include <vector>
#include "Metro.h"
#include "Users.h"
#include <fstream>
using namespace std;
//
void dfs(string root, unordered_map<string,vector<Station>> &gr_line, unordered_map<string,vector<Station>> &rd_line, unordered_map<string,vector<Station>> &blu_line, unordered_map<string, bool>& visited) {

    visited[root] = true;
    cout << "\n"<<root << "\n    |\n";

    for (auto& station : gr_line[root]) {
        string s = station.get_name();
        if (!visited[s]) {
            dfs(s, gr_line,rd_line,blu_line, visited);
        }
    }
}
int write(map<string, personalInformation> &usrData)
{
    ofstream outputFile("users.txt");

    if (outputFile.is_open()) {
        for (const auto& pair : usrData) {
            const personalInformation& user = pair.second;
            outputFile << user.id << ' '
                       << user.email << ' '
                       << user.password <<
                               ' ' << user.fname <<
                                       ' '<<user.lname<< '\n';
        }
        outputFile.close();
    } else {
        cerr << "Error: Unable to open file for writing." << endl;
        return 1;
    }
    return 0;
}

int read(map<string, personalInformation>& usrData) {
    ifstream inputFile("users.txt");
    if (!inputFile.is_open()) {
        cerr << "Error: Unable to open file for reading." << endl;
        return 1;
    }
    int userId;
    string email, password, fname, lname;
    while(inputFile >> userId >> email >> password >> fname >> lname) {
        personalInformation temp;
        temp.id = userId;
        temp.email = email;
        temp.password = password;
        temp.fname =fname;
        temp.lname = lname;
        usrData.emplace(email, temp);
    }

    inputFile.close();
    return 0;
}

int main() {
    map<string, personalInformation>mapp;
    read(mapp);
    Users user;
    for (auto it: mapp)
        cout << it.first << endl;
    user.begin(mapp);
    for (auto it: mapp)
        cout << it.first << endl;
    Metro egypt_metro("Egypt");

    vector<string> green_line_stations = {
            "Adly Mansour", "El Haykesteb", "Omar Ibn El Khatab", "Qubaa", "Hesham Barakat",
            "El Nozha", "El Shams Club", "Alf Maskan", "Heliopolis", "Haroun", "El Ahram",
            "Kolleyet El Banat", "Stadium", "Fair Zone", "El Abassya", "Abdo Basha",
            "El Geish", "Bab El Shaarya", "Attaba", "Gamal Abd El Nasser", "Maspero",
            "Safaa Hegazy", "Kit Kat", "Sudan", "Imbaba", "El Bohy", "EL Qawmia",
            "Ring Road", "Rod El Farag"
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

    string color = "Green";

    unordered_map<string, bool>visited;

    string green="Green",red="Red",blue="Blue";

    unordered_map<string,vector<Station>> gr_line=egypt_metro.get_line(green).get_stations();
    unordered_map<string,vector<Station>> rd_line=egypt_metro.get_line(red).get_stations();
    unordered_map<string,vector<Station>> blu_line=egypt_metro.get_line(blue).get_stations();

    string root = gr_line.begin()->first;



    dfs(root, gr_line,rd_line,blu_line, visited);
    write(mapp);
    return 0;
}
