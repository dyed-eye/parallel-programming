#include "Barber.h"

void Barber::cutHair()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Simulate hair cutting time
    std::cout << "Barber is cutting hair." << std::endl;
}
