#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include "Metro.h"
#include "Users.h"
#include "subscription.h"
#include <fstream>
#include "Ride.h"
#include "admin.h"
#include <iostream>
#include <fstream>
#include <map>
#include <string>
using namespace std;





int write(const map<std::string, personalInformation> &usrData, const unordered_map<string, vector<Ride>> &rides) {
   ofstream outputFile("users.txt");
    if (!outputFile.is_open()) {
        std::cerr << "Error: Unable to open file for writing." << std::endl;
        return 1;
    }

    for (const auto &pair : usrData) {
        const personalInformation &user = pair.second;
        outputFile
            << user.email << '|'
            << user.password << '|'
            << user.fname << '|'
            << user.lname << '|'
            << user.plan.plan.PlanName << '|'
            << user.plan.firstDestination << '|'
            << user.plan.secondDestination << '|'
            << user.plan.StartDate << '|'
            << user.plan.Enddate << '|'
            << user.plan.remainingtrips << '|'
        << user.plan.plan.tripsallowed << '|' << user.plan.plan.Duration <<
            '|' << user.plan.Price << '|' << user.plan.stage << '|' << user.balance.Balance
            << '\n';
    }

    outputFile.close();
    ofstream ridesoutput("rides.txt");
    if (!ridesoutput.is_open()) {
        std::cerr << "Error: Unable to open file for writing." << endl;
        return 1;
    }
    for (const auto &pair : rides)
    {
        for (const auto &rid: pair.second)
        {
            ridesoutput << pair.first << '|'
            << rid.getFirstD() << '|' << rid.getFinalD()
            << '|' << rid.getDate() << '|' << rid.getTime() << '|'
            << rid.getFare() << '|' << rid.getSubscriptionType() << endl;
        }

    }



    ridesoutput.close();
    return 0;
}

int read(map<string, personalInformation> &usrData, unordered_map<string, vector<Ride>> &rides) {
    ifstream inputFile("users.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open file for reading." << std::endl;
        return 1;
    }

    std::string line;
    while (getline(inputFile, line)) {
        personalInformation temp;
        istringstream ss(line);
        string token, token2, token3, token4, token5, token6;
        getline(ss, temp.email, '|');
        getline(ss, temp.password, '|');
        getline(ss, temp.fname, '|');
        getline(ss, temp.lname, '|');
        getline(ss, temp.plan.plan.PlanName, '|');
        getline(ss, temp.plan.firstDestination, '|');
        getline(ss, temp.plan.secondDestination, '|');
        getline(ss, temp.plan.StartDate, '|');
        getline(ss, temp.plan.Enddate, '|');

        getline(ss, token, '|');
        getline(ss, token2, '|');
        getline(ss, token3, '|');
        getline(ss, token4, '|');
        getline(ss, token5, '|');
        getline(ss, token6, '|');
        temp.plan.remainingtrips = stoi(token);
        temp.plan.plan.tripsallowed = stoi(token2);
        temp.plan.plan.Duration = stoi(token3);
        temp.plan.Price = stoi(token4);
        temp.plan.stage = stoi(token5);
        temp.balance.Balance = stoi(token6);
        usrData.emplace(temp.email, temp);
    }

    inputFile.close();

    ifstream ridesInput("rides.txt");
    if (!ridesInput.is_open()) {
        std::cerr << "Error: Unable to open file for reading." << std::endl;
        return 1;
    }

    string ride;
    while (getline(ridesInput, ride)) {
        Ride temp;
        istringstream ss(ride); // Use 'ride' instead of 'line'
        string token, token2, token3, token4, token5, token6, email;
        getline(ss, email, '|');
        getline(ss, token, '|');
        temp.setFirstDestination(token);
        getline(ss, token2, '|');
        temp.setLastDestination(token2);
        getline(ss, token3, '|');
        temp.setDate(token3);
        getline(ss, token4, '|');
        temp.setTime(token4);
        // Uncomment and handle the fare data if needed
         getline(ss, token5, '|');
         temp.setFare(stoi(token5));
        getline(ss, token6, '|');
        temp.setType(token6);
        if (rides.find(email) == rides.end()) {
            rides[email] = {temp};
        } else {
            rides[email].push_back(temp); // Add ride to existing user's rides
        }
    }

    ridesInput.close();
    return 0;
}
int main() {
    unordered_map<string, vector<Ride>> rides;
    Metro egypt_metro("Egypt");

    vector<vector<string>>colored_line_stations;

    colored_line_stations.push_back(vector<string>());
    colored_line_stations[0] = {
            "Adly Mansour", "El Haykesteb", "Omar Ibn El Khatab", "Qubaa", "Hesham Barakat",
            "El Nozha", "El Shams Club", "Alf Maskan", "Heliopolis", "Haroun", "El Ahram",
            "Kolleyet El Banat", "Stadium", "Fair Zone", "El Abassya", "Abdo Basha",
            "El Geish", "Bab El Shaarya", "Attaba", "Gamal Abd El Nasser", "Maspero",
            "Safaa Hegazy", "Kit Kat", "Sudan", "Imbaba", "El Bohy", "EL Qawmia",
            "Ring Road", "Mehwar Rod El Farag"
    };


    Metro::build_line(egypt_metro, "Green", colored_line_stations[0]);

    colored_line_stations.push_back(vector<string>());
    colored_line_stations[1] = {
            "Shubra El Kheima", "Koleyet El Zeraa", "El Mazalat", "El Khalafawy",
            "Saint Threasa", "Rod El Farag", "Massara", "El Shohada", "Attaba",
            "2w", "El Sadat", "Opera", "El Dokki", "El Behoos", "Cairo University",
            "Faysal", "El Giza", "Om El Masryeen", "Sakyet Mekky", "El Moneeb"
    };

    Metro::build_line(egypt_metro, "Red", colored_line_stations[1]);

    colored_line_stations.push_back(vector<string>());
    colored_line_stations[2] = {
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



    Metro::build_line(egypt_metro, "Blue", colored_line_stations[2]);







    subscription sub;

    map<string, Plan> plans;
    //student plan
    map<int, int> prices;    prices = {{1, 33},
                                       {2, 41},
                                       {3, 50},
                                       {4, 65}};
    sub.Addplan("student", 180, 3, prices, plans);
    //public monthly plan
    prices = {{1, 230},
              {2, 290},
              {3, 340},
              {4, 450}};
    sub.Addplan("publicmonthly", 60, 1, prices, plans);
    // public yearly plan
    prices = {{1, 1500},
              {2, 2500},
              {3, 3500},
              {4, 4500}};
    sub.Addplan("publicyearly", 730, 12, prices, plans);
    map<string, personalInformation> mappp;
    //write(mappp);
    subscription plan;
    read(mappp, rides);
    Users user;

    for (auto it: mappp)
        cout << it.first << endl;
    user.begin(mappp, plans,egypt_metro, rides,colored_line_stations);
    //user = mappp.find(user.GetEmail());
    for (auto it: mappp)
        cout << it.first << endl;
    write(mappp, rides);
    return 0;
}