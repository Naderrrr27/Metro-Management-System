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
int wallet::Addbalance(int amount) {
        int check =Balance+amount;
        if(check <=400) {
            Balance = check;
            return 1;
        }
        else {
            cout << "Balance limit can't exceed 400";
        }
    return 0;
}
void wallet::Deduct(int stations) {
int amount = Ticketprice(stations);
    if (Balance >= amount)
        Balance -= amount;
    else
        return;
        //cout << "Recharge your balance\n";
}
int wallet::Ticketprice(int stations) {
    if (stations >= 1 && stations <= 9)
        return 6;
    if (stations > 9 && stations <= 16)
        return 8;
    if (stations > 16 && stations <= 23)
        return 12;
    return 15;
}