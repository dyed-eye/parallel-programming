#include <iostream>
#include <fstream>
#include <omp.h>

#define N 5 // Number of vectors
#define M 5 // Size of each vector

void read_vectors(double vectors[N][M]) {
    std::ifstream file("vectors.txt");
    if (!file) {
        std::cerr << "Error opening file." << std::endl;
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            file >> vectors[i][j];
        }
    }

    file.close();
}

double dot_product(double *a, double *b, int m) {
    double result = 0.0;

    #pragma omp parallel for reduction(+:result)
    for (int i = 0; i < m; i++) {
        result += a[i] * b[i];
    }

    return result;
}

int main() {
    double vectors[N][M];
    double total_dot_product = 0.0;

    // Read vectors in parallel using sections
    #pragma omp parallel
    {
        #pragma omp single
        {
            #pragma omp task
            {
                read_vectors(vectors);
                std::cout << "Vectors have been read." << std::endl;
            }
        }
    }

    #pragma omp parallel for reduction(+:total_dot_product)
    for (int i = 0; i < N; i++) {
        total_dot_product += dot_product(vectors[i], vectors[i], M); // Dot product of each vector with itself
    }

    // Output the total dot product
    std::cout << "Total dot product of all vectors: " << total_dot_product << std::endl;

    return 0;
}
