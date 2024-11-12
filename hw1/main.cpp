#include <iostream>
#include <chrono>
#include <vector>
#include <cstdlib> // For std::atoi
#include "sse_functions.h"
#include "normal_functions.h"

int main(int argc, char* argv[]) {
    // Check if the user provided the size of the array
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <size_of_array>\n";
        return 1;
    }

    // Convert the command line argument to an integer
    int N = std::atoi(argv[1]);
    if (N <= 0) {
        std::cerr << "Please provide a positive integer for the size of the array.\n";
        return 1;
    }

    std::vector<float> a(N), b(N), x(N), y(N);

    // Initialize arrays
    for (int i = 0; i < N; ++i) {
        a[i] = static_cast<float>(i);
        x[i] = static_cast<float>(i);
        y[i] = static_cast<float>(i + 1);
    }

    // Normal square root
    auto start = std::chrono::high_resolution_clock::now();
    normal_sqrt(a.data(), b.data(), N);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> normal_sqrt_time = end - start;
    std::cout << "Normal sqrt time: " << normal_sqrt_time.count() << " seconds\n";

    // SSE square root
    start = std::chrono::high_resolution_clock::now();
    sse_sqrt(a.data(), b.data(), N);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> sse_sqrt_time = end - start;
    std::cout << "SSE sqrt time: " << sse_sqrt_time.count() << " seconds\n";

    // Normal inner product
    start = std::chrono::high_resolution_clock::now();
    float normal_result = normal_inner(x.data(), y.data(), N);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> normal_inner_time = end - start;
    std::cout << "Normal inner product time: " << normal_inner_time.count() << " seconds\n";

    // SSE inner product
    start = std::chrono::high_resolution_clock::now();
    float sse_result = sse_inner(x.data(), y.data(), N);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> sse_inner_time = end - start;
    std::cout << "SSE inner product time: " << sse_inner_time.count() << " seconds\n";

    return 0;
}
