#include <iostream>
#include "skiplist.h"

int main() {
    // Example usage

    SkipList<int> skipList;

    // Insert elements
    skipList.insert(3);
    skipList.insert(1);
    skipList.insert(4);
    skipList.insert(1);
    skipList.insert(5);

    // Print elements using iterators
    std::cout << "Elements in sorted order: ";
    for (const auto& value : skipList) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    // Find an element
    int key = 4;
    auto it = skipList.find(key);
    if (it != skipList.end()) {
        std::cout << "Element " << key << " found in the list." << std::endl;
    } else {
        std::cout << "Element " << key << " not found in the list." << std::endl;
    }

    // Erase an element
    skipList.erase(it);

    // Print elements after erasing
    std::cout << "Elements after erasing: ";
    for (const auto& value : skipList) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    return 0;
}
