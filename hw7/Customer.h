#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

class BarberShop; // Forward declaration

class Customer {
public:
    Customer(int id, BarberShop& shop);
    void enterShop();
    void getHaircut();

private:
    int id;
    BarberShop& shop;
};

#endif // CUSTOMER_H
