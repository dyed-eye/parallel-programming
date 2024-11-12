#include <math.h>     // For sqrt
#include "normal_functions.h"

void normal_sqrt(float* a, float* b, int N) {
    for (int i = 0; i < N; ++i) {
        b[i] = sqrt(a[i]);
    }
}

float normal_inner(float* x, float* y, int n) {
    float s = 0.0f;
    for (int i = 0; i < n; i++) {
        s += x[i] * y[i];
    }
    return s;
}
