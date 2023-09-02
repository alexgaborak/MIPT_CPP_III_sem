//
// Created by alexg on 9/2/2023.
//
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

// Define the Point3D structure
struct Point3D {
    double x;
    double y;
    double z;
};

// Function to calculate the midpoint between two Point3D points (Task 1)
Point3D middle(const Point3D& p1, const Point3D& p2) {
    Point3D result;
    result.x = (p1.x + p2.x) / 2.0;
    result.y = (p1.y + p2.y) / 2.0;
    result.z = (p1.z + p2.z) / 2.0;
    return result;
}


// Function to calculate the distance between two Point3D points (Task 2)
double distance(const Point3D& p1, const Point3D& p2) {
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    double dz = p1.z - p2.z;
    return sqrt(dx * dx + dy * dy + dz * dz);
}


// Function to calculate the center of mass for an array of Point3D points (Task 3)
Point3D center_of_mass(const std::vector<Point3D>& points) {
    Point3D center = {0.0, 0.0, 0.0};
    double totalMass = static_cast<double>(points.size());

    for (const Point3D& point : points) {
        center.x += point.x;
        center.y += point.y;
        center.z += point.z;
    }

    center.x /= totalMass;
    center.y /= totalMass;
    center.z /= totalMass;

    return center;
}

// Function to read an array of Point3D points from a file
std::vector<Point3D> read_points_from_file(const std::string& filename) {
    std::vector<Point3D> points;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return points;
    }

    double x, y, z;
    while (file >> x >> y >> z) {
        Point3D point = {x, y, z};
        points.push_back(point);
    }

    file.close();
    return points;
}


int main() {
    // Create two Point3D points manually
    Point3D point1 = {1.0, 2.0, 3.0};
    Point3D point2 = {3.0, 5.0, 9.0};

    // Calculate the distance between the two points (for tasks 1, 2)
    double dist = distance(point1, point2);
    Point3D mid = middle(point1, point2);

    // Specify the filename containing the Point3D data
    std::string filename = "points.txt";

    // Read the array of Point3D points from the file
    std::vector<Point3D> points = read_points_from_file(filename);

    // Calculate the center of mass (for task 3)
    Point3D center = center_of_mass(points);

    // Display the results
    std::cout << "Center of Mass: (" << center.x << ", " << center.y << ", " << center.z << ")" << std::endl;
    std::cout << "Distance between point1 and point2: " << dist << std::endl;
    std::cout << "Midpoint between point1 and point2: (" << mid.x << ", " << mid.y << ", " << mid.z << ")" << std::endl;

    // Create matrices for distances and midpoints (Task 4)
    int numPoints = points.size();
    std::vector<std::vector<double>> distanceMatrix(numPoints, std::vector<double>(numPoints));
    std::vector<std::vector<Point3D>> midpointMatrix(numPoints, std::vector<Point3D>(numPoints));

    // Fill in the distance and midpoint matrices (for task 4)
    for (int i = 0; i < numPoints; ++i) {
        for (int j = 0; j < numPoints; ++j) {
            distanceMatrix[i][j] = distance(points[i], points[j]);
            midpointMatrix[i][j] = middle(points[i], points[j]);
        }
    }

    // Display the distance matrix
    std::cout << "Distance Matrix:" << std::endl;
    for (int i = 0; i < numPoints; ++i) {
        for (int j = 0; j < numPoints; ++j) {
            std::cout << distanceMatrix[i][j] << "\t";
        }
        std::cout << std::endl;
    }

    // Display the midpoint matrix
    std::cout << "Midpoint Matrix:" << std::endl;
    for (int i = 0; i < numPoints; ++i) {
        for (int j = 0; j < numPoints; ++j) {
            std::cout << "(" << midpointMatrix[i][j].x << ", " << midpointMatrix[i][j].y << ", " << midpointMatrix[i][j].z << ")\t";
        }
        std::cout << std::endl;
    }

    return 0;
}


