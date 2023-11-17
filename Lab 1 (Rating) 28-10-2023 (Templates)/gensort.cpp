//
// Created by alexg on 11/15/2023.
//
#include <iostream>
#include <vector>
#include <string>
#include "comparator.h"


// Hoare quicksort implementation
template <typename T>
void quickSort(std::vector<T>& arr, const Comparator<T>& comparator, int low, int high) {
    if (low < high) {
        // Partition the array and get the pivot index
        int pivotIndex = partition(arr, comparator, low, high);

        // Recursively sort the subarrays
        quickSort(arr, comparator, low, pivotIndex);
        quickSort(arr, comparator, pivotIndex + 1, high);
    }
}

// Partitioning function for Hoare quicksort
template <typename T>
int partition(std::vector<T>& arr, const Comparator<T>& comparator, int low, int high) {
    T pivot = arr[low];
    int i = low - 1;
    int j = high + 1;

    while (true) {
        do {
            i++;
        } while (comparator(arr[i], pivot));

        do {
            j--;
        } while (comparator(pivot, arr[j]));

        if (i >= j) {
            return j;
        }

        // Swap arr[i] and arr[j]
        std::swap(arr[i], arr[j]);
    }
}

// Test function
template <typename T>
void testSort(std::vector<T>& arr, const Comparator<T>& comparator) {
    int n = arr.size();

    std::cout << "Original Array: ";
    for (const T& elem : arr) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    quickSort(arr, comparator, 0, n - 1);

    std::cout << "Sorted Array: ";
    for (const T& elem : arr) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

int main() {
    // Test with integers
    std::vector<int> intArr = {5, 2, 9, 1, 5, 6};
    IntComparator intComparator;
    testSort(intArr, intComparator);

    std::cout << "\n";

    // Test with strings
    std::vector<std::string> strArr = {"apple", "orange", "banana", "grape", "kiwi"};
    StringComparator strComparator;
    testSort(strArr, strComparator);

    std::cout << "\n";

    // Test with floating-point numbers
    std::vector<float> floatArr = {3.14, 1.1, 2.2, 0.5, 4.0};
    FloatComparator floatComparator;
    testSort(floatArr, floatComparator);

    return 0;
}
