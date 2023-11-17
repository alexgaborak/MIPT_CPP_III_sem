//
// Created by alexg on 11/15/2023.
//

#include <iostream>
#include <string>
#include <vector>
#include "comparator.h"

// PriorityQueue class
template <typename T>
class PriorityQueue {
private:
    std::vector<T> heap;
    const Comparator<T>& comparator;

    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (!comparator(heap[index], heap[parent])) {
                break;  // Correct position
            }
            std::swap(heap[index], heap[parent]);
            index = parent;
        }
    }

    void heapifyDown(int index) {
        int leftChild, rightChild, minIndex;
        while (true) {
            leftChild = 2 * index + 1;
            rightChild = 2 * index + 2;
            minIndex = index;

            if (leftChild < heap.size() && comparator(heap[leftChild], heap[minIndex])) {
                minIndex = leftChild;
            }

            if (rightChild < heap.size() && comparator(heap[rightChild], heap[minIndex])) {
                minIndex = rightChild;
            }

            if (minIndex == index) {
                break;  // Correct position
            }

            std::swap(heap[index], heap[minIndex]);
            index = minIndex;
        }
    }

public:
    // Constructor
    PriorityQueue(const Comparator<T>& comp) : comparator(comp) {}

    // Destructor
    ~PriorityQueue() {
        free();
    }

    // Push method to add a new value to the queue
    void push(const T& value) {
        heap.push_back(value);
        heapifyUp(heap.size() - 1);
    }

    // Peek method to read the top element of the queue
    const T& peek() const {
        if (is_empty()) {
            throw std::out_of_range("Queue is empty");
        }
        return heap[0];
    }

    // Poll method to delete the top element of the queue
    void poll() {
        if (is_empty()) {
            throw std::out_of_range("Queue is empty");
        }
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);
    }

    // Is_empty method to check if the queue is empty
    bool is_empty() const {
        return heap.empty();
    }

    // Free method to free up all previously allocated memory
    void free() {
        heap.clear();
    }
};

// Test function for PriorityQueue with integers
void testIntPriorityQueue() {
    std::cout << "Testing PriorityQueue with integers...\n";

    // Create a comparator for the PriorityQueue
    IntComparator intComparator;

    // Instantiate the PriorityQueue with the comparator
    PriorityQueue<int> priorityQueue(intComparator);

    // Test push method
    priorityQueue.push(3);
    priorityQueue.push(1);
    priorityQueue.push(4);
    priorityQueue.push(1);
    priorityQueue.push(5);

    // Test peek method
    std::cout << "Peek: " << priorityQueue.peek() << "\n";

    // Test poll method
    while (!priorityQueue.is_empty()) {
        std::cout << "Poll: " << priorityQueue.peek() << "\n";
        priorityQueue.poll();
    }

    // Test is_empty method
    std::cout << "Is empty: " << (priorityQueue.is_empty() ? "true" : "false") << "\n";
}

// Test function for PriorityQueue with strings
void testStringPriorityQueue() {
    std::cout << "Testing PriorityQueue with strings...\n";

    // Create a comparator for the PriorityQueue
    StringComparator stringComparator;

    // Instantiate the PriorityQueue with the comparator
    PriorityQueue<std::string> priorityQueue(stringComparator);

    // Test push method
    priorityQueue.push("banana");
    priorityQueue.push("apple");
    priorityQueue.push("kiwi");
    priorityQueue.push("orange");

    // Test peek method
    std::cout << "Peek: " << priorityQueue.peek() << "\n";

    // Test poll method
    while (!priorityQueue.is_empty()) {
        std::cout << "Poll: " << priorityQueue.peek() << "\n";
        priorityQueue.poll();
    }

    // Test is_empty method
    std::cout << "Is empty: " << (priorityQueue.is_empty() ? "true" : "false") << "\n";
}

int main() {
    // Test with integers
    testIntPriorityQueue();

    std::cout << "\n";

    // Test with strings
    testStringPriorityQueue();

    std::cout << "\n";

    // Add more tests for different types as needed

    return 0;
}
