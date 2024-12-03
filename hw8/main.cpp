#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <limits.h>

#define N 100000000

/*void find_min_max_atomic(int *arr, int n, int *min, int *max) {
    *min = INT_MAX;
    *max = INT_MIN;

    #pragma omp parallel
    {
        int local_min = INT_MAX;
        int local_max = INT_MIN;

        #pragma omp for
        for (int i = 0; i < n; i++) {
            if (arr[i] < local_min) local_min = arr[i];
            if (arr[i] > local_max) local_max = arr[i];
        }
        
        if (local_min < *min) {
			#pragma omp atomic
			*min = local_min;
		}

        if (local_max > *max) {
			#pragma omp atomic
			*max = local_max;
		}
    }
}*/

void find_min_max_critical(int *arr, int n, int *min, int *max) {
    *min = INT_MAX;
    *max = INT_MIN;

    #pragma omp parallel
    {
        int local_min = INT_MAX;
        int local_max = INT_MIN;

        #pragma omp for
        for (int i = 0; i < n; i++) {
            if (arr[i] < local_min) local_min = arr[i];
            if (arr[i] > local_max) local_max = arr[i];
        }

        #pragma omp critical
        {
            if (local_min < *min) *min = local_min;
            if (local_max > *max) *max = local_max;
        }
    }
}

void find_min_max_lock(int *arr, int n, int *min, int *max) {
    *min = INT_MAX;
    *max = INT_MIN;
    omp_lock_t lock;
    omp_init_lock(&lock);

    #pragma omp parallel
    {
        int local_min = INT_MAX;
        int local_max = INT_MIN;

        #pragma omp for
        for (int i = 0; i < n; i++) {
            if (arr[i] < local_min) local_min = arr[i];
            if (arr[i] > local_max) local_max = arr[i];
        }

        omp_set_lock(&lock);
        if (local_min < *min) *min = local_min;
        if (local_max > *max) *max = local_max;
        omp_unset_lock(&lock);
    }

    omp_destroy_lock(&lock);
}

int main() {
    int *arr = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        arr[i] = rand() % 1000; // random
    }

    int min, max;

    //find_min_max_atomic(arr, N, &min, &max);
    //printf("Min: %d, Max: %d (Atomic)\n", min, max);

	omp_set_num_threads(4);
    printf("Using 4 threads\n");
	
    // Measure execution time for critical section method
    double start_time = omp_get_wtime();
    find_min_max_critical(arr, N, &min, &max);
    double end_time = omp_get_wtime();
    printf("Min: %d, Max: %d (Critical)\n", min, max);
    printf("Execution time (Critical): %f seconds\n", end_time - start_time);

    // Measure execution time for lock method
    start_time = omp_get_wtime();
    find_min_max_lock(arr, N, &min, &max);
    end_time = omp_get_wtime();
    printf("Min: %d, Max: %d (Lock)\n", min, max);
    printf("Execution time (Lock): %f seconds\n\n", end_time - start_time);

	omp_set_num_threads(8);
    printf("Using 8 threads\n");
	
    // Measure execution time for critical section method
    start_time = omp_get_wtime();
    find_min_max_critical(arr, N, &min, &max);
    end_time = omp_get_wtime();
    printf("Min: %d, Max: %d (Critical)\n", min, max);
    printf("Execution time (Critical): %f seconds\n", end_time - start_time);

    // Measure execution time for lock method
    start_time = omp_get_wtime();
    find_min_max_lock(arr, N, &min, &max);
    end_time = omp_get_wtime();
    printf("Min: %d, Max: %d (Lock)\n", min, max);
    printf("Execution time (Lock): %f seconds\n\n", end_time - start_time);

	omp_set_num_threads(16);
    printf("Using 16 threads\n");
	
    // Measure execution time for critical section method
    start_time = omp_get_wtime();
    find_min_max_critical(arr, N, &min, &max);
    end_time = omp_get_wtime();
    printf("Min: %d, Max: %d (Critical)\n", min, max);
    printf("Execution time (Critical): %f seconds\n", end_time - start_time);

    // Measure execution time for lock method
    start_time = omp_get_wtime();
    find_min_max_lock(arr, N, &min, &max);
    end_time = omp_get_wtime();
    printf("Min: %d, Max: %d (Lock)\n", min, max);
    printf("Execution time (Lock): %f seconds\n\n", end_time - start_time);

    free(arr);
    return 0;
}
