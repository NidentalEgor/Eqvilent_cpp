#include <string>

#pragma once

struct Angles {
    double alpha = 0.0;
    double beta = 0.0;
};

struct Point {
    Point(double _x, double _y) :
        x(_x), y(_y){}

    // Point(const Point& other){
    //     x = other.x;
    //     y = other.y;
    // }

    // const Point& operator=(const Point& other){
    //     x = other.x;
    //     y = other.y;

    //     return *this;
    // }

    double x = 0.0;
    double y = 0.0;
};

double calculateAngle(const Point& leftPoint, const Point& rightPoint);

void readInputs2(const std::string& filePath, std::vector<double>& inputs);

void Process(const std::vector<double>& input, std::vector<std::pair<double, double>>& output);
 