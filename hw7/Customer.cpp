#include "Customer.h"
#include "BarberShop.h"

Customer::Customer(int id, BarberShop& shop) : id(id), shop(shop) {}

void Customer::enterShop()
{
    std::cout << "Customer " << id << " enters the shop." << std::endl;
    getHaircut();
}

void Customer::getHaircut()
{
    shop.requestHaircut(id);
}
