#include "solution.h"

#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <utility>
#include <cmath>
#include <limits>

void readInput(const std::string& filePath, std::vector<double>& inputs)
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

void writeOutput(const std::string& filePath, std::vector<Angles>& output)
{
    std::ofstream outFile(filePath);
    
    if (!outFile.is_open()) {
        throw std::runtime_error("Unable to open file: " + filePath);
    }

    for (const auto& angles : output) {
        outFile << std::fixed << std::setprecision(5) << angles.alpha << "," << angles.beta << "\n";
    }
}

// Calculates slope angle of a line relative to the horizontal
double calculateAngle(const Point& leftPoint, const Point& rightPoint)
{
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
int classifyPointPosition(const Point& point1, const Point& point2, const Point& toCheck)
{
    const double D = (toCheck.x - point1.x) * (point2.y - point1.y) - (toCheck.y - point1.y) * (point2.x - point1.x);

    if(D > 0.0){
        return -1; // on the left
    } else if(D < 0.0){
        return 1; // on the right
    } else{
        return 0;
    }
}

void fullRecalcAlpha(const std::vector<double>& inputs, int left, int right, const Point& rightPoint,
    int& prevStepLeftPointIndexAlpha, std::vector<Angles>& result)
{
    // if(left == 0){
    //     std::cout << "Full recalc window[" << left << ", " << right << "]. Left border = " << left << " right border = " << rightPoint.x << " prevStepLeftPointIndexAlpha = " << prevStepLeftPointIndexAlpha << std::endl;
    // }
    Point leftPointAlpha(static_cast<double>(right), -std::numeric_limits<double>::max());
    for(int i = right - 1; i >= left; i--){
        const Point toCheck(static_cast<double>(i), inputs[i]);
        if(classifyPointPosition(leftPointAlpha, rightPoint, toCheck) >= 0){
            leftPointAlpha = toCheck;
            prevStepLeftPointIndexAlpha = i;
            result[right].alpha = calculateAngle(leftPointAlpha, rightPoint);
        }
    }
}

void fullRecalcBeta(const std::vector<double>& inputs, int left, int right,
    int& prevStepLeftPointIndexBeta, std::vector<Angles>& result)
{
    Point rightPoint(static_cast<double>(right), inputs[right]);
    Point leftPointBeta(static_cast<double>(right), std::numeric_limits<double>::max());
    for(int i = right - 1; i >= left; i--){
        const Point toCheck(static_cast<double>(i), inputs[i]);
        if(classifyPointPosition(leftPointBeta, rightPoint, toCheck) <= 0){
            leftPointBeta = toCheck;
            prevStepLeftPointIndexBeta = i;
            result[right].beta = calculateAngle(leftPointBeta, rightPoint);
        }
    }
}

// Calculates angles alpha and beta for the position of right based on the values [inputs[left], inputs[right]]
void processWindow(const std::vector<double>& inputs, int left, int right,
    int& prevStepLeftPointIndexAlpha, int& prevStepLeftPointIndexBeta,
    std::vector<Angles>& result)
{
    if(left > right) {
        throw std::runtime_error("Invalid window borders");
    }

    const int prevStepRightIndex = right - 1;
    const Point prevStepRightPoint(static_cast<double>(prevStepRightIndex), inputs[prevStepRightIndex]);
    Point rightPoint(static_cast<double>(right), inputs[right]);

    const Point prevStepLeftPointAlpha(static_cast<double>(prevStepLeftPointIndexAlpha), inputs[prevStepLeftPointIndexAlpha]);
    if(classifyPointPosition(prevStepLeftPointAlpha, prevStepRightPoint, rightPoint) < 0) {
        result[right].alpha = calculateAngle(prevStepRightPoint, rightPoint);
        prevStepLeftPointIndexAlpha = prevStepRightIndex;
    } else {
        // const int rightBorder = prevStepLeftPointIndexAlpha >= left ? prevStepLeftPointIndexAlpha + 1 : right;
        fullRecalcAlpha(inputs, left, /*rightBorder*/right, rightPoint, prevStepLeftPointIndexAlpha, result);
    }

    const Point prevStepLeftPointBeta(static_cast<double>(prevStepLeftPointIndexBeta), inputs[prevStepLeftPointIndexBeta]);
    if(classifyPointPosition(prevStepLeftPointBeta, prevStepRightPoint, rightPoint) > 0) {
        result[right].beta = calculateAngle(prevStepRightPoint, rightPoint);
        prevStepLeftPointIndexBeta = prevStepRightIndex;
    } else {
        fullRecalcBeta(inputs, left, right, prevStepLeftPointIndexBeta, result);
    }
}

// Calculates the angles alpha and beta for each window in inputs of size window
void calculate(const std::vector<double>& inputs, std::vector<Angles>& result, int window)
{
    if(window <= 0) {
        throw std::runtime_error("Invalid window size");
    }
    
    result.resize(inputs.size());
    result.front().alpha = 0.0;
    result.front().beta = 0.0;

    int prevStepLeftPointIndexAlpha = -1;
    int prevStepLeftPointIndexBeta = -1;
    for(int i = 1; i < inputs.size(); i++) {
        if(i < 10){
            std::cout << "window #" << i << std::endl;
        }
        int left = std::max(0, i - window + 1);
        int right = i;
        processWindow(inputs, left, right, prevStepLeftPointIndexAlpha, prevStepLeftPointIndexBeta, result);
    }
}
 