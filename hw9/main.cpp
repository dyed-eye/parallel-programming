#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <limits.h>

#define N 10000000 // array size
#define TRIALS 10  // number of trials


double reduction_atomic(int *arr, int n) {
    double sum = 0.0;

    #pragma omp parallel
    {
        double local_sum = 0.0;

        #pragma omp for
        for (int i = 0; i < n; i++) {
            local_sum += arr[i];
        }

        #pragma omp atomic
        sum += local_sum; // however atomic cannot be used with local_sum
    }

    return sum;
}

double reduction_critical(int *arr, int n) {
    double sum = 0.0;

    #pragma omp parallel
    {
        double local_sum = 0.0;

        #pragma omp for
        for (int i = 0; i < n; i++) {
            local_sum += arr[i];
        }

        #pragma omp critical
        {
            sum += local_sum;
        }
    }

    return sum;
}

double reduction_lock(int *arr, int n) {
    double sum = 0.0;
    omp_lock_t lock;
    omp_init_lock(&lock);

    #pragma omp parallel
    {
        double local_sum = 0.0;

        #pragma omp for
        for (int i = 0; i < n; i++) {
            local_sum += arr[i];
        }

        omp_set_lock(&lock);
        sum += local_sum;
        omp_unset_lock(&lock);
    }

    omp_destroy_lock(&lock);
    return sum;
}

double reduction_openmp(int *arr, int n) {
    double sum = 0.0;

    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }

    return sum;
}

int main() {
    int *arr = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        arr[i] = rand() % 100; // random
    }

    double total_time_atomic = 0.0;
    double total_time_critical = 0.0;
    double total_time_lock = 0.0;
    double total_time_openmp = 0.0;

    for (int trial = 0; trial < TRIALS; trial++) {
        double start_time = omp_get_wtime();
        double sum = reduction_atomic(arr, N);
        double end_time = omp_get_wtime();
        total_time_atomic += (end_time - start_time);
    }

    for (int trial = 0; trial < TRIALS; trial++) {
        double start_time = omp_get_wtime();
        double sum = reduction_critical(arr, N);
        double end_time = omp_get_wtime();
        total_time_critical += (end_time - start_time);
    }

    for (int trial = 0; trial < TRIALS; trial++) {
        double start_time = omp_get_wtime();
        double sum = reduction_lock(arr, N);
        double end_time = omp_get_wtime();
        total_time_lock += (end_time - start_time);
    }

    for (int trial = 0; trial < TRIALS; trial++) {
        double start_time = omp_get_wtime();
        double sum = reduction_openmp(arr, N);
        double end_time = omp_get_wtime();
        total_time_openmp += (end_time - start_time);
    }

    printf("Average Execution time (Atomic): %f seconds\n", total_time_atomic / TRIALS);
    printf("Average Execution time (Critical): %f seconds\n", total_time_critical / TRIALS);
    printf("Average Execution time (Lock): %f seconds\n", total_time_lock / TRIALS);
    printf("Average Execution time (OpenMP Reduction): %f seconds\n", total_time_openmp / TRIALS);

    free(arr);
    return 0;
}
