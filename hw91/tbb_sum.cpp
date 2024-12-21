#include "tbb_sum.h"
#include <tbb/tbb.h>

long long sum_of_squares_tbb(int N) {
    return tbb::parallel_reduce(
        tbb::blocked_range<int>(1, N+1),
        0LL,
        [](const tbb::blocked_range<int>& r, long long init) {
            for (int i = r.begin(); i!=r.end(); ++i){
                init+=static_cast<long long>(i) * i;
            }
            return init;
        },
        std::plus<long long>()
    );
}
