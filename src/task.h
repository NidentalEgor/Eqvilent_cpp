#include <string>
#include <limits>

#pragma once

struct Angles {
    double alpha = -std::numeric_limits<double>::max();
    double beta = std::numeric_limits<double>::max();
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

void readOutputs(const std::string& filename, std::vector<Angles>& data);

void Process(const std::vector<double>& input, std::vector<std::pair<double, double>>& output);
 
 void calculate(const std::vector<double>& inputs, std::vector<Angles>& result, int window);