#pragma once
#include <iostream>
#include <vector>
#include "Metro.h"

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

int main() {

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

    return 0;
}
