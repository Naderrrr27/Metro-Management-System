#include "Statistics.h"


Statistics::Statistics() {

}

void Statistics::incrementPassengers(string stationName, int income=0)
{
    // will be called in the checkin function in user's class
    stat[{__DATE__, stationName}].first++;
    stat[{__DATE__, stationName}].second+=income; //in case of wallet subscription

}

void Statistics::incrementIncome(string stationName, int income)
{
    //will be called in the user's subscribe related function
    stat[{__DATE__, stationName}].second += income;
}

void Statistics::showStatisticsDay(string date, string stationName)
{
    cout << "Number of passeneger in "<< date << "for the station"<< stationName<< "is: " << stat[{date, stationName}].first << endl;
    cout << "The total income in " << date << "for the station" << stationName << "is: " << stat[{date, stationName}].second << endl;
}

void Statistics::showStatisticsMonth(string month, string stationName)
{
    int totalIncome = 0, totalPass = 0;
    auto it = stat.begin();


    for (; it != stat.end(); it++)
    {

        int counter = 0;

        string str1 = stationName;
        string str2 = it->first.second;

        transform(str1.begin(), str1.end(), str1.begin(), ::tolower); // convert station Name to lower case, to avoid case sensetive errors
        transform(str2.begin(), str2.end(), str2.begin(), ::tolower);

        if (str1 == str2)
        {
            for (int i = 0; i < 3; i++) // check about the targted month in the dates of the map with key name = station name .
            {
                char c1 = std::tolower(it->first.first[i]); // make both char lowercase, to avoid case sensetive errors
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
            totalIncome += it->second.second;
        }


    }

    cout << " the total number of passengers in " << month << " for the station " << stationName << " is: " << totalPass << endl;
    cout << " the total income in " << month << " for the station " << stationName << " is " << totalIncome << endl;
}

void Statistics::showStatisticsYear(string year, string stationName)
{

    int totalIncome = 0, totalPass = 0;
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

            //starts from the end to check the year at the end of the date string
            for (int i = size - 1, j=3 ; i >= size - 4; i--,j--) // check about the targted year in the dates of the map with key name = station name .
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
            totalIncome += it->second.second;
        }

    }

    cout << " the total number of passengers in " << year << " for the station " << stationName << " is: " << totalPass << endl;
    cout << " the total income in " << year << " for the station " << stationName << " is " << totalIncome << endl;

}


