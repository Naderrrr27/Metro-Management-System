#include "Statistics.h"


Statistics::Statistics() {

}
// Definition of static member variable
map<pair<string, string>, pair<int, pair<int, int>>> Statistics::stat;

void Statistics::incrementPassengers(string date,string stationName)
{
    // will be called in the checkin function in user's class
    stat[{date, stationName}].first++;

}


void Statistics::incrementIncome(string date, string stationName, int income)
{
    //will be called in the subscription related function
    stat[{date, stationName}].second.first += income;
}

void Statistics::incrementSoldTicket(string date,string stationName)
{
    stat[{date, stationName}].second.second++; // in case of wallet chekin
}


bool Statistics::showStatisticsDay(string date, string stationName){
    pair<string, string> key = {date, stationName};
    cout<<stat.count(key)<<"\n";
    if(stat.count(key)) {
        cout << "Number of passenger in " << date << " for the station" << stationName << " is: "
             << stat[{date, stationName}].first << endl;
        cout << "The total income in " << date << " for the station " << stationName << " is: "
             << stat[{date, stationName}].second.first << endl;
        cout << "The no. of sold tickets in " << date << " for the station " << stationName << " is: "
             << stat[{date, stationName}].second.second<< endl;
        return true;
    }
    return false;
}

void Statistics::showStatisticsMonth(string month, string stationName)
{
    int totalIncome = 0, totalPass = 0,totalSoldTickets=0;
    auto it = stat.begin();


    for (; it != stat.end(); it++)
    {

        int counter = 0;

        string str1 = stationName;
        string str2 = it->first.second;

        transform(str1.begin(), str1.end(), str1.begin(), ::tolower); // convert station Name to lower case, to avoid case-sensitive errors
        transform(str2.begin(), str2.end(), str2.begin(), ::tolower);

        if (str1 == str2)
        {
            for (int i = 0; i < 3; i++) // check about the targeted month in the dates of the map with key name = station name .
            {
                char c1 = std::tolower(it->first.first[i]); // make both char lowercase, to avoid case-sensitive errors
                char c2 = std::tolower(month[i]);
                if (c1 == c2)
                    counter++;
            }
        }
        else
        {
            continue;
        }


        if (counter == 3) // the month matches
        {
            totalPass += it->second.first;
            totalIncome += it->second.second.first;
            totalSoldTickets+=it->second.second.second;
        }


    }


    cout << " the total number of passengers in " << month << " for the station " << stationName << " is: " << totalPass << endl;
    cout << " the total income in " << month << " for the station " << stationName << " is " << totalIncome << endl;
    cout << " the no. of sold  tickets in " << month << " for the station " << stationName << " is " << totalSoldTickets << endl;
}
void Statistics::showStatisticsYear(string year, string stationName)
{

    int totalIncome = 0, totalPass = 0,totalSoldTickets=0;
    auto it = stat.begin();

    for (; it != stat.end(); it++)
    {
        int counter = 0;
        string str1 = stationName;
        string str2 = it->first.second;

        transform(str1.begin(), str1.end(), str1.begin(), ::tolower);
        transform(str2.begin(), str2.end(), str2.begin(), ::tolower);

        if (str1==str2)
        {
            int size = it->first.first.size();

            //starts from the Enddate to check the year at the Enddate of the date string
            for (int i = size - 1, j=3 ; i >= size - 4; i--,j--) // check about the targeted year in the dates of the map with key name = station name .
            {
                if (it->first.first[i] == year[j])
                {
                    counter++;
                }

            }
        }

        else
        {
            continue;
        }

        if (counter == 4) // year matches
        {
            totalPass += it->second.first;
            totalIncome += it->second.second.first;
            totalSoldTickets+=it->second.second.second;
        }

    }

    cout << " the total number of passengers in " << year << " for the station " << stationName << " is: " << totalPass << endl;
    cout << " the total income in " << year << " for the station " << stationName << " is " << totalIncome << endl;
    cout << " the no. of sold tickets in  " << year << " for the station " << stationName << " is " << totalSoldTickets << endl;
}




