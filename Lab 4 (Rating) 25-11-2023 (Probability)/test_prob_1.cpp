//
// Created by alexg on 12/9/2023.
//
#include <iostream>
#include <fstream>
#include <iomanip>
#include <set>
#include <random>
#include "probability.h"

int main() {
    std::ofstream outFile;

    // Probability test parameters
    unsigned seed = 10;
    int test_min = 0;
    int test_max = 100;
    int testCountMin = 10;
    int testCountMax = 100000;
    int testCountStep = 10;

    // Open the output file
    outFile.open("probability_results.txt");

    if (!outFile.is_open()) {
        std::cerr << "Error: Unable to open the output file." << std::endl;
        return 1;
    }

    // Perform probability tests for SegmentState
    outFile << "SegmentState Probability Results:" << std::endl;
    for (int testCount = testCountMin; testCount <= testCountMax; testCount += testCountStep) {
        ProbabilityTest pt(seed, test_min, test_max, testCount);
        SegmentState segmentState(0, 10);
        float probability = pt(segmentState);
        outFile << testCount << " " << std::fixed << std::setprecision(6) << probability << std::endl;
    }

    // Perform probability tests for SetState
    outFile << "\nSetState Probability Results:" << std::endl;
    std::set<int> arbitrarySet = {1, 3, 5, 7, 23, 48, 57, 60, 90, 99};
    SetState setState(arbitrarySet);
    for (int testCount = testCountMin; testCount <= testCountMax; testCount += testCountStep) {
        ProbabilityTest pt(seed, test_min, test_max, testCount);
        float probability = pt(setState);
        outFile << testCount << " " << std::fixed << std::setprecision(6) << probability << std::endl;
    }

    // Close the output file
    outFile.close();

    std::cout << "Probability results have been written to 'probability_results.txt'" << std::endl;

    return 0;
}