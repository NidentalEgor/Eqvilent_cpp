#include <string>
#include <limits>

#pragma once

struct Angles {
    double alpha{0.0};
    double beta{0.0};
};

struct Point {
    Point(double _x, double _y) :
        x(_x), y(_y){}

    Point(const Point& other){
        x = other.x;
        y = other.y;
    }

    const Point& operator=(const Point& other){
        x = other.x;
        y = other.y;

        return *this;
    }

    double x = 0.0;
    double y = 0.0;
};

double calculateAngle(const Point& leftPoint, const Point& rightPoint);

void readInput(const std::string& filePath, std::vector<double>& inputs);

void writeOutput(const std::string& filePath, std::vector<Angles>& output);

void calculate(const std::vector<double>& inputs, std::vector<Angles>& result, int window);