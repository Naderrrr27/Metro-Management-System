//
// Created by pc on 01/05/2024.
//

#include "wallet.h"
#include "wallet.h"
#include <iostream>
wallet::wallet() {
    Balance = 0;
}
int wallet::getbalance() {
    return Balance;
}
void wallet::Addbalance(int amount) {
    if (amount % 10 == 0 && amount + Balance <= 400)
        Balance += amount;
}
void wallet::Deduct(int ticketprice) {

    if (Balance >= ticketprice)
        Balance -= ticketprice;
    else
        cout << "recharge your balance";
}
void wallet::Ticketprice() {
    int c=6;

    int stations = c;//shortestpath(firstdestination, finaldestination);
    if (stations >= 1 && stations <= 9)
        Deduct(6);
    else if (stations > 9 && stations <= 16)
        Deduct(8);
    else if (stations > 16 && stations <= 23)
        Deduct(12);
    else
        Deduct(15);
}