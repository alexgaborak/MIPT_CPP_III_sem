//
// Created by alexg on 11/29/2023.
//
#include <iostream>
#include <fstream>
#include <chrono>
#include <random>
#include "SkipList.h"  // Include the SkipList class definition

int main() {
    // Open the output file
    std::ofstream outputFile("search_p_0.5.txt");

    // Seed for random number generation
    std::random_device rd;
    std::mt19937 gen(rd());

    // Range of elements to test
    int start = 10;
    int end = 20000;
    int increment = 10;

    for (int numElements = start; numElements <= end; numElements += increment) {
        // Create a SkipList
        SkipList<int> skipList;

        // Fill the list with random numbers
        std::uniform_int_distribution<> dis(1, numElements * 10);
        for (int i = 0; i < numElements; ++i) {
            skipList.insert(dis(gen));
        }

        // Choose a random element to delete
        int keyToDelete = dis(gen);

        // Measure the time taken to erase the chosen element
        auto startTime = std::chrono::high_resolution_clock::now();
        auto it = skipList.find(keyToDelete);
        if (it != skipList.end()) {
            skipList.erase(it);
        }
        auto endTime = std::chrono::high_resolution_clock::now();

        // Calculate the deletion time in nanoseconds
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();

        // Record the results in the output file
        outputFile << numElements << " " << duration << std::endl;

        // Output progress to console
        std::cout << "Processed: " << numElements << " elements" << std::endl;
    }

    // Close the output file
    outputFile.close();

    return 0;
}
