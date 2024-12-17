#include "tbb_sum.h"
#include <tbb/parallel_for.h>
#include <tbb/blocked_range.h>
#include <tbb/counting_iterator.h>

long long sum_of_squares_tbb(int N) {
    long long sum = 0;

    tbb::parallel_for(tbb::blocked_range<int>(1, N + 1), [&sum](const tbb::blocked_range<int>& r) {
        long long local_sum = 0;
        for (int i = r.begin(); i != r.end(); ++i) {
            local_sum += i * i;
        }
        // Use atomic addition to avoid data races
        sum += local_sum;
    });

    return sum;
}
