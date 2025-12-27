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
#include <ctime>
#include <fstream>
#include <chrono>
#include <random>
#include <cstdint>
#include <vector>

// Node structure for pointer chasing
struct PointerChaseNode {
    uint32_t next;
    unsigned char pad[64 - sizeof(uint32_t)];
};

/**
 * @brief Fisher-Yates shuffle to iterate through indices and swap each element
 * with a random element from remaining unsorted
*/
void shuffle(uint32_t *index, uint32_t n, std::mt19937& gen) {
    for(uint32_t i = n - 1; i > 0; i--) {
        std::uniform_int_distribution<uint32_t> dist(0, i);
        uint32_t j = dist(gen);
        uint32_t temp = index[i];
        index[i] = index[j];
        index[j] = temp;
    }
}

/**
 * @brief main function
 * @return 0 if successful
*/
int main() {
    // seed random number generator
    std::mt19937 gen(42);

    // open csv file for keeping data
    std::ofstream file("output.csv");
    file << "Size,Latency\n";

    // Define number of traversals
    const uint32_t passes = 100;

    // Loop to go from 1kb to 1gb by powers of 2
    for (size_t size = 1 << 10; size <= 1 << 30; size = size << 1) {
        // initialize memory access buffer
        PointerChaseNode* buffer = static_cast<PointerChaseNode*>(aligned_alloc(64, size));

        // check for error in allocation
        if (buffer == NULL) {
            std::cout << "Error allocating memory buffer" << std::endl;
            return 1;
        }

        uint32_t num_nodes = size / sizeof(PointerChaseNode);
        uint32_t iterations = num_nodes * passes;

        // initialize indexes of the buffer
        std::vector<uint32_t> index(num_nodes);
        for (uint32_t i = 0; i < num_nodes; i++) {
            index[i] = i;
        }

        // Shuffle the indices of the buffer
        shuffle(&index[0], num_nodes, gen);

        // Pointer chase chaining
        for (uint32_t i = 0; i < num_nodes - 1; i++) {
            buffer[index[i]].next = index[i + 1];
        }
        buffer[index[num_nodes - 1]].next = index[0];

        // start timing
        auto start = std::chrono::high_resolution_clock::now();

        // Pointer Chase Loop
        uint32_t current = index[0];
        for (int i = 0; i < iterations; i++) {
            current = buffer[current].next;
        }

        // prevent optimization
        volatile uint32_t dummy = current;

        // Stop timing
        auto end = std::chrono::high_resolution_clock::now();

        // Calculate latency
        auto duration = end - start;
        auto latency_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();
        double latency = static_cast<double>(latency_ns);

        // Save latency for each working set size to csv
        file << size << "," << latency << "\n";

        // free memory
        free(buffer);
    }

    // close file
    file.close();

    // Return successful
    return 0;
}