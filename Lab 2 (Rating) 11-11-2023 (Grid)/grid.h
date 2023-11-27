//
// Created by alexg on 11/25/2023.
//

#ifndef MIPT_CPP_III_SEM_GRID_H
#define MIPT_CPP_III_SEM_GRID_H

#endif //MIPT_CPP_III_SEM_GRID_H

#include <algorithm>
#include <cassert>

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

    // Indexing operator for accessing rows
    class Row {
    public:
        Row(T* row, size_type x_size) : row(row), x_size(x_size) {}

        // Indexing operator for accessing elements in a row
        T& operator[](size_type x_idx) {
            return row[x_idx];
        }

        const T& operator[](size_type x_idx) const {
            return row[x_idx];
        }

    private:
        T* row;
        size_type x_size;
    };

    // Indexing operator for accessing rows
    Row operator[](size_type y_idx) {
        assert(y_idx < y_size);
        return Row(data + y_idx * x_size, x_size);
    }

    const Row operator[](size_type y_idx) const {
        assert(y_idx < y_size);
        return Row(data + y_idx * x_size, x_size);
    }

    size_type get_y_size() const { return y_size; }
    size_type get_x_size() const { return x_size; }

private:
    T* data;
    size_type y_size, x_size;
};
