#include <iostream>
#include "sequential_sum.h"
#include "parallel_sum.h"
#include "tbb_sum.h"

int main() {
    int N = 1000000; // Example size

    long long sum_seq = sum_of_squares_sequential(N);
    long long sum_par = sum_of_squares_parallel(N);
    long long sum_tbb = sum_of_squares_tbb(N);

    std::cout << "Sequential Sum of Squares: " << sum_seq << std::endl;
    std::cout << "Parallel Sum of Squares (STL): " << sum_par << std::endl;
    std::cout << "Parallel Sum of Squares (TBB): " << sum_tbb << std::endl;

    // Check if all sums are equal
    if (sum_seq == sum_par && sum_seq == sum_tbb) {
        std::cout << "All sums are equal." << std::endl;
    } else {
        std::cout << "Sums are not equal!" << std::endl;
    }

    return 0;
}
