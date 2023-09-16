//
// Created by alexg on 9/16/2023.
//
#include <iostream>

struct Point {
public:
    // Constructors
    Point() : x(0), y(0) {} // Default constructor
    Point(int a, int b) : x(a), y(b) {} // Constructor with two parameters

    // Public methods
    Point minx(const Point& other) const {
        return Point(std::min(x, other.x), y);
    }

    Point maxx(const Point& other) const {
        return Point(std::max(x, other.x), y);
    }

    Point miny(const Point& other) const {
        return Point(x, std::min(y, other.y));
    }

    Point maxy(const Point& other) const {
        return Point(x, std::max(y, other.y));
    }

    const int x;
    const int y;
};