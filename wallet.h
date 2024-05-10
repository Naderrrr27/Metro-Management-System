//
// Created by pc on 01/05/2024.
//

#ifndef METRO_WALLET_H
#define METRO_WALLET_H

#pragma once
#include <string>
using namespace std;
class wallet
{
public:
    int Balance;

    wallet();
    int Addbalance(int amount);
    void Deduct(int ticketprice);
    int Ticketprice(int stations);
    int getbalance();

};





#endif //METRO_WALLET_H
