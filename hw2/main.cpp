#include <windows.h>
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include "matrix_processing.h"

const int MAX_SIZE = 100; // Maximum size of the matrix

int main() {
    int rows, cols;

    std::cout << "Amount of rows: ";
    std::cin >> rows;
    std::cout << "Amount of columns: ";
    std::cin >> cols;

    if (rows > MAX_SIZE || cols > MAX_SIZE) {
        std::cerr << "Matrix size cannot exceed " << MAX_SIZE << std::endl;
        return 1;
    }

    std::vector<std::vector<int>> matrix(rows, std::vector<int>(cols));
    std::vector<ThreadData> threadData(rows);
    std::vector<HANDLE> threads(rows);

    // Seed the random number generator with the current time
    unsigned seed = static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count());
    std::mt19937 gen(seed); // Initialize the random number generator
    std::uniform_int_distribution<> dis(MIN_RANDOM, MAX_RANDOM);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = dis(gen); // Generate random number for the current element
        }
        threadData[i].rowIndex = i;
        threadData[i].row = matrix[i];
        threads[i] = CreateThread(NULL, 0, GenerateAndProcessRow, &threadData[i], 0, NULL);
    }

    // Wait for all threads to finish
    WaitForMultipleObjects(rows, threads.data(), TRUE, INFINITE);

    // Output results
    for (const auto& data : threadData) {
        std::cout << "Row " << data.rowIndex << ": ";
        for (const int& num : data.row) {
            std::cout << num << " ";
        }
        std::cout << "| Multiplication of odd elements: " << data.product << std::endl;
    }

    // Release resources
    for (HANDLE thread : threads) {
        CloseHandle(thread);
    }

    return 0;
}
