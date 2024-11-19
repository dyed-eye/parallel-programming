#ifndef MATRIX_PROCESSING_H
#define MATRIX_PROCESSING_H

#include <vector>
#include <windows.h>

// Constants for random number generation
const int MIN_RANDOM = 1; // Minimum value for generation
const int MAX_RANDOM = 100; // Maximum value for generation

struct ThreadData {
    int rowIndex;
    std::vector<int> row;
    long long product;
};

DWORD WINAPI GenerateAndProcessRow(LPVOID lpParam);

#endif // MATRIX_PROCESSING_H
