//
// Created by alexg on 9/9/2023.
//
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>


class Vector{
private:
    int* data;       // Dynamic array to store elements
    size_t capacity; // Total capacity of the vector
    size_t length;   // Current number of elements in the vector

public:
    // Constructor
    Vector() : data(nullptr), capacity(0), length(0) {}

    // Copy constructor for deep copy
    Vector(const Vector& other) : capacity(other.capacity), length(other.length) {
        data = new int[capacity];
        for (size_t i = 0; i < length; ++i) {
            data[i] = other.data[i];
        }
    }

    // Destructor to free memory
    ~Vector() {
        delete[] data;
    }

    // Shrink the capacity to match the current number of elements
    void shrink_to_fit() {
        if (length < capacity) {
            size_t newCapacity = length;
            int *newData = new int[newCapacity];

            for (size_t i = 0; i < length; ++i) {
                newData[i] = data[i];
            }

            delete[] data;
            data = newData;
            capacity = newCapacity;
        }
    }

    // Push an element to the back of the vector
    void push_back(int element) {
        if (length >= capacity) {
            // If the vector is full, double the capacity
            size_t newCapacity = (capacity == 0) ? 1 : 2 * capacity;
            int* newData = new int[newCapacity];

            for (size_t i = 0; i < length; ++i) {
                newData[i] = data[i];
            }

            delete[] data;
            data = newData;
            capacity = newCapacity;
        }

        data[length++] = element;
    }

    // Access an element at a specific index with bounds checking
    int at(size_t index) const {
        if (index < length) {
            return data[index];
        } else {
            // Handle out-of-bounds access
            throw std::out_of_range("Index out of bounds");
        }
    }

    // Get the current size of the vector
    size_t size() const {
        return length;
    }

    // Remove an element at a specific index
    void remove(size_t index) {
        if (index < length) {
            for (size_t i = index; i < length - 1; ++i) {
                data[i] = data[i + 1];
            }
            length--;
            if ( 5 * length < capacity) {
                size_t newCapacity = length;
                int *newData = new int[newCapacity];

                for (size_t i = 0; i < length; ++i) {
                    newData[i] = data[i];
                }

                delete[] data;
                data = newData;
                capacity = newCapacity;
            }
        } else {
            // Handle out-of-bounds removal
            throw std::out_of_range("Index out of bounds");
        }
    }

    // Overload the [] operator for element access
    int& operator[](size_t index) {
        if (index < length) {
            return data[index];
        } else {
            // Handle out-of-bounds access
            throw std::out_of_range("Index out of bounds");
        }
    }

    // Overload the = operator for assignment
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            // Avoid self-assignment
            delete[] data;

            capacity = other.capacity;
            length = other.length;
            data = new int[capacity];

            for (size_t i = 0; i < length; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }
};

int main() {
    Vector vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    // Access elements
    std::cout << "vec[0]: " << vec[0] << std::endl;
    std::cout << "vec[1]: " << vec[1] << std::endl;
    std::cout << "vec[2]: " << vec[2] << std::endl;

    // Modify an element
    vec[1] = 99;
    std::cout << "After modifying vec[1]: " << vec[1] << std::endl;

    // Remove an element
    vec.remove(0);
    std::cout << "After removing vec[0]: " << vec[0] << std::endl;

    // Copy constructor
    Vector vec2 = vec;
    std::cout << "vec2[0]: " << vec2[0] << std::endl;
    return 0;
}
