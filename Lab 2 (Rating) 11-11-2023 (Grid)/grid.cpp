//
// Created by alexg on 11/18/2023.
//
#include <algorithm> // For std::copy

template <typename T>
class Grid final {
public:
    using valuetype = T;
    using size_type = unsigned;

    // Rule of Five: Destructor
    ~Grid() {
        delete[] data;
    }

    // Rule of Five: Default Constructor
    Grid() : data(nullptr), y_size(0), x_size(0) {}

    // Rule of Five: Copy Constructor
    Grid(const Grid<T>& other) : data(new T[other.y_size * other.x_size]), y_size(other.y_size), x_size(other.x_size) {
        std::copy(other.data, other.data + y_size * x_size, data);
    }

    // Rule of Five: Move Constructor
    Grid(Grid<T>&& other) noexcept : data(other.data), y_size(other.y_size), x_size(other.x_size) {
        other.data = nullptr;
        other.y_size = 0;
        other.x_size = 0;
    }

    // Rule of Five: Copy Assignment Operator
    Grid<T>& operator=(const Grid<T>& other) {
        if (this != &other) {
            delete[] data; // Release existing resources

            // Allocate new resources
            data = new T[other.y_size * other.x_size];
            y_size = other.y_size;
            x_size = other.x_size;

            // Copy data from other to this
            std::copy(other.data, other.data + y_size * x_size, data);
        }
        return *this;
    }

    // Rule of Five: Move Assignment Operator
    Grid<T>& operator=(Grid<T>&& other) noexcept {
        if (this != &other) {
            delete[] data; // Release existing resources

            // Take ownership of the resources from 'other'
            data = other.data;
            y_size = other.y_size;
            x_size = other.x_size;

            // Reset 'other' to a valid state
            other.data = nullptr;
            other.y_size = 0;
            other.x_size = 0;
        }
        return *this;
    }

    // Constructor with one parameter for implicit type conversion
    Grid(const T& t) : data(new T[1]), y_size(1), x_size(1) {
        data[0] = t;
    }

    // Constructor with two parameters
    Grid(size_type y_size, size_type x_size) : data(new T[y_size * x_size]), y_size(y_size), x_size(x_size) {
        std::fill(data, data + y_size * x_size, T{}); // Default initialize elements
    }

    // Constructor with three parameters
    Grid(size_type y_size, size_type x_size, const T& t) : data(new T[y_size * x_size]), y_size(y_size), x_size(x_size) {
        std::fill(data, data + y_size * x_size, t); // Fill with copies of 't'
    }

    T operator()(size_type y_idx, size_type x_idx) const {
        return data[y_idx * x_size + x_idx];
    }

    T& operator()(size_type y_idx, size_type x_idx) {
        return data[y_idx * x_size + x_idx];
    }

    // Rule of Five: Move Constructor
    size_type get_y_size() const { return y_size; }
    size_type get_x_size() const { return x_size; }

private:
    T* data;
    size_type y_size, x_size;
};

#include <iostream>

int main() {
    // Test default constructor
    Grid<int> defaultGrid;
    std::cout << "Default Grid: " << defaultGrid.get_y_size() << "x" << defaultGrid.get_x_size() << std::endl;

    // Test constructor with one parameter for implicit type conversion
    Grid<int> singleElementGrid(42);
    std::cout << "Single Element Grid: " << singleElementGrid.get_y_size() << "x" << singleElementGrid.get_x_size() << std::endl;

    // Test constructor with two parameters
    Grid<int> gridSize2x3(2, 3);
    std::cout << "Grid 2x3: " << gridSize2x3.get_y_size() << "x" << gridSize2x3.get_x_size() << std::endl;

    // Test constructor with three parameters
    Grid<int> filledGrid(3, 3, 99);
    std::cout << "Filled Grid 3x3 with 99: " << std::endl;
    for (unsigned i = 0; i < filledGrid.get_y_size(); ++i) {
        for (unsigned j = 0; j < filledGrid.get_x_size(); ++j) {
            std::cout << filledGrid(i, j) << " ";
        }
        std::cout << std::endl;
    }

    // Test copy constructor
    Grid<int> copyGrid(filledGrid);
    std::cout << "Copy of Filled Grid: " << std::endl;
    for (unsigned i = 0; i < copyGrid.get_y_size(); ++i) {
        for (unsigned j = 0; j < copyGrid.get_x_size(); ++j) {
            std::cout << copyGrid(i, j) << " ";
        }
        std::cout << std::endl;
    }

    // Test move constructor
    Grid<int> moveGrid(std::move(copyGrid));
    std::cout << "After Move Constructor: " << copyGrid.get_y_size() << "x" << copyGrid.get_x_size() << std::endl;
    std::cout << "After Move Constructor (New Grid): " << moveGrid.get_y_size() << "x" << moveGrid.get_x_size() << std::endl;

    // Test copy assignment operator
    Grid<int> assignedGrid = gridSize2x3;
    std::cout << "After Copy Assignment: " << assignedGrid.get_y_size() << "x" << assignedGrid.get_x_size() << std::endl;

    // Test move assignment operator
    Grid<int> movedGrid;
    movedGrid = std::move(filledGrid);
    std::cout << "After Move Assignment: " << filledGrid.get_y_size() << "x" << filledGrid.get_x_size() << std::endl;
    std::cout << "After Move Assignment (New Grid): " << movedGrid.get_y_size() << "x" << movedGrid.get_x_size() << std::endl;

    return 0;
}
