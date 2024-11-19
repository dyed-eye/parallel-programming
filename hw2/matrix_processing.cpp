#include "matrix_processing.h"
#include <random>
#include <iostream>

DWORD WINAPI GenerateAndProcessRow(LPVOID lpParam) {
    ThreadData* data = (ThreadData*)lpParam;
    std::vector<int>& row = data->row;

    long long product = 1;
    bool hasOdd = false;

    for (int& num : row) {
        if (num % 2 != 0) {
            product *= num;
            hasOdd = true;
        }
    }

    // If no odd elements, set product to 0
    if (!hasOdd) {
        product = 0;
    }

    data->product = product;
    return 0;
}
