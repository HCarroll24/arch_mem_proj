/******************************************************************************
 * @file matrix_mult_no_prefetch.cpp
 * @author Hunter Carroll
 * @date 2025-12-28
 * @version 1.0
 *
 * @brief This file contains the implementation of a matrix multiplication program
 * that does not use software prefetching. It multiplies two matrices and prints
 * the result.
 * @note This file is part of the Computer Arhitecture Memory Project
******************************************************************************/
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <cstdint>
#include <fstream>
#include <cstdlib>
#include <cmath>

/**
 * @brief main function
 * @return 0 if successful
*/
int main() {
    const int size = 1 << 30;
    const int sqrt_size = std::sqrt(size);
    // Set and allocate all matrices
    uint8_t* matrix_a = static_cast<uint8_t*>(aligned_alloc(64, size));
    uint8_t* matrix_b = static_cast<uint8_t*>(aligned_alloc(64, size));
    uint8_t* result = static_cast<uint8_t*>(aligned_alloc(64, size));
    if (matrix_a == nullptr || matrix_b == nullptr || result == nullptr) {
        std::cerr << "Error allocating matrices" << std::endl;
        return 1;
    }

    // populate matrices a and b
    std::mt19937 gen(42);
    std::uniform_int_distribution<uint8_t> dist(0, 100);
    for (int i = 0; i < sqrt_size; i++) {
        for (int j = 0; j < sqrt_size; j++) {
            matrix_a[i * sqrt_size + j] = dist(gen);
            matrix_b[i * sqrt_size + j] = dist(gen);
        }
    }

    // Conduct matrix multiplication
    for (int i = 0; i < sqrt_size; i++) {
        for (int j = 0 ; j < sqrt_size; j++) {
            result[i * sqrt_size + j] = 0;
            for(int k = 0; k < sqrt_size; k++) {
                result[i * sqrt_size + j] += matrix_a[i * sqrt_size + k] * matrix_b[k * sqrt_size + j];
            }
        }
    }

    // free memory
    free(matrix_a);
    free(matrix_b);
    free(result);

    // Return successful
    return 0;
}