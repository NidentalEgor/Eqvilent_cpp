#include "solution.h"

#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <utility>
#include <cmath>
#include <limits>

void readInputs(const std::string& filePath, std::vector<double>& inputs)
{
    std::ifstream file(filePath);
    std::string line;

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filePath);
    }

    size_t lineIndex = 0;
    while (std::getline(file, line)) {
        try {
            inputs.push_back(std::stod(line));
        } catch (const std::invalid_argument &e) {
            std::cerr << "Invalid line # " << lineIndex << " format in file: " << line << "\n";
        }
        lineIndex++;
    }
}

void writeOutput(const std::string& filePath, std::vector<Angles>& output){
    std::ofstream outFile(filePath);
    
    if (!outFile.is_open()) {
        throw std::runtime_error("Unable to open file: " + filePath);
    }

    for (const auto& angles : output) {
        outFile << std::fixed << std::setprecision(5) << angles.alpha << "," << angles.beta << "\n";
    }
}

// Calculates slope angle of a line relative to the horizontal
double calculateAngle(const Point& leftPoint, const Point& rightPoint) {
    const double dx = rightPoint.x - leftPoint.x;
    const double dy = rightPoint.y - leftPoint.y;
    const double angle = std::atan2(dy, dx);
    // invert the sign so that the angle above the horizontal axis is positive
    return -angle;
}

// Determines the position of a point relative to a line formed by two other points.
// return -1 if the point is to the left of the line,
// return  1 if the point is to the right of the line,
// return  0 if the point lies on the line.
int classifyPointPosition(const Point& point1, const Point& point2, const Point& toCheck){
    const double D = (toCheck.x - point1.x) * (point2.y - point1.y) - (toCheck.y - point1.y) * (point2.x - point1.x);

    if(D > 0.0){
        return -1; // on the left
    } else if(D < 0.0){
        return 1; // on the right
    } else{
        return 0;
    }
}

// Calculates angles alpha and beta for the position of right based on the values [inputs[left], inputs[right]]
void processWindow(const std::vector<double>& inputs, int left, int right,
    std::vector<Angles>& result)
{
    if(left > right) {
        throw std::runtime_error("Invalid window");
    }

    if(left == right){
        result[right].alpha = 0.0;
        result[right].beta = 0.0;
        return;
    }

    Point rightPoint(static_cast<double>(right), inputs[right]);
    Point leftPointAlpha(static_cast<double>(right), -std::numeric_limits<double>::max());
    Point leftPointBeta(static_cast<double>(right), std::numeric_limits<double>::max());
    for(int i = right - 1; i >= left; i--){
        const Point toCheck(static_cast<double>(i), inputs[i]);
        if(classifyPointPosition(leftPointAlpha, rightPoint, toCheck) >= 0){
            leftPointAlpha = toCheck;
            result[right].alpha = calculateAngle(leftPointAlpha, rightPoint);
        }

        if(classifyPointPosition(leftPointBeta, rightPoint, toCheck) <= 0){
            leftPointBeta = toCheck;
            result[right].beta = calculateAngle(leftPointBeta, rightPoint);
        }
    }
}

// Calculates the angles alpha and beta for each window in inputs of size window
void calculate(const std::vector<double>& inputs, std::vector<Angles>& result, int window)
{
    result.resize(inputs.size());
    for(int i = 0; i < inputs.size(); i++){
        int left = std::max(0, i - window + 1);
        int right = i;
        processWindow(inputs, left, right, result);
    }
}
 