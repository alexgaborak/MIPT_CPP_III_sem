//
// Created by alexg on 11/18/2023.
//

#include <iostream>
#include "grid.h"

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
