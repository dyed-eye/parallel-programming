#ifndef BARBER_H
#define BARBER_H

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

class Barber {
public:
    void cutHair();
};

#endif // BARBER_H
