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
void wallet::Deduct(int amount) {

    if (Balance >= amount)
        Balance -= amount;
    else
        cout << "Recharge your balance";
}
void wallet::Ticketprice(int stations) {
    if (stations >= 1 && stations <= 9)
        Deduct(6);
    else if (stations > 9 && stations <= 16)
        Deduct(8);
    else if (stations > 16 && stations <= 23)
        Deduct(12);
    else
        Deduct(15);
}