//
// Created by pc on 01/05/2024.
//

#ifndef METRO_WALLET_H
#define METRO_WALLET_H

#pragma once
#include"subscription.h"
class wallet
{
public:
    int Balance;

    //Ride ride take shortestpath
    //from another classes
    int shortestpath(string firstdist, string lastdist);


    wallet();
    void Addbalance(int amount);
    int getbalance();
    void Deduct(int ticketprice);
    void Ticketprice();

    //take first and last distantion from check out and checkin
    //User user
};





#endif //METRO_WALLET_H
