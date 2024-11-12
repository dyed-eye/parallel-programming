#include <emmintrin.h> // For SSE2
#include <math.h>     // For sqrt
#include "sse_functions.h"

void sse_sqrt(float* a, float* b, int N) {
    int i;
    for (i = 0; i < N - 3; i += 4) {
        __m128 vec = _mm_loadu_ps(&a[i]);
        vec = _mm_sqrt_ps(vec);
        _mm_storeu_ps(&b[i], vec);
    }
    for (; i < N; ++i) {
        b[i] = sqrt(a[i]);
    }
}

float sse_inner(float* x, float* y, int n) {
    __m128 sum_vec = _mm_setzero_ps();
    int i;

    for (i = 0; i < n - 3; i += 4) {
        __m128 x_vec = _mm_loadu_ps(&x[i]);
        __m128 y_vec = _mm_loadu_ps(&y[i]);
        __m128 mul_vec = _mm_mul_ps(x_vec, y_vec);
        sum_vec = _mm_add_ps(sum_vec, mul_vec);
    }

    float sum[4];
    _mm_storeu_ps(sum, sum_vec);
    float result = sum[0] + sum[1] + sum[2] + sum[3];

    for (; i < n; ++i) {
        result += x[i] * y[i];
    }

    return result;
}
