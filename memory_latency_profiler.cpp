/******************************************************************************
 * @file memory_latency_profiler.cpp
 * @author Hunter Carroll
 * @date 2025-12-24
 * @version 1.0
 *
 * @brief This file contains the implementation of a memory latency profiler
 * for the raspberry pi 5 that allocates memory buffers, uses a controlled
 * access pattern, and measure the average memory latency. Sweeps from 1kb to
 * 1gb by powers of 2.
 * @note This file is part of the Computer Arhitecture Memory Project
******************************************************************************/
#include <iostream>
#include <cstdlib>

/**
 * @brief main function
 * @return 0 if successful
*/
int main() {
    // Loop to go from 1kb to 1gb by powers of 2
    for (size_t size = 1 << 10; size <= 1 << 30; size = size << 1) {
        // initialize memory access buffer
        uint8_t* buffer = (uint8_t*)aligned_alloc(64, size);

        // check for error in allocation
        if (buffer == NULL) {
            std::cout << "Error allocating memory buffer" << std::endl;
            return 1;
        }

        // free memory
        free(buffer);
    }

    return 0;
}