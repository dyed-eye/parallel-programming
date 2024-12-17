#include "sequential_sum.h"
#include <vector>
#include <numeric>
#include <algorithm>

long long sum_of_squares_sequential(int N) {
    std::vector<int> numbers(N);
    std::iota(numbers.begin(), numbers.end(), 1); // Fill with 1, 2, ..., N

    long long sum = 0;
    std::for_each(numbers.begin(), numbers.end(), [&sum](int x) {
        sum += x * x;
    });

    return sum;
}
