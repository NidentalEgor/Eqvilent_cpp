
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <utility>
#include <cmath>
#include <limits>

static constexpr int NotFound = -1;

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
            throw std::runtime_error("Parsing error at line " + std::to_string(lineIndex) + ": " + line);
        }
        lineIndex++;
    }

    if (inputs.empty()) {
        throw std::runtime_error("Input data is empty.");
    }
}

void writeOutput(const std::string& filePath, const std::vector<Angles>& output)
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

// Calculates the maximum angle Alpha or Beta for lines passing through the rightPoint and one of the points in the window [left, right]
std::pair<double, int> recalcAngleForWindow(const std::vector<double>& inputs,
    int left, int right, const Point& rightPoint, const bool isAlpha)
{
    double angle = 0.0;
    int anchorPointIndex = NotFound;

    Point leftAnchorPoint(static_cast<double>(right),
        isAlpha ? -std::numeric_limits<double>::max() : std::numeric_limits<double>::max());

    for(int i = right; i >= left; i--){
        const Point toCheck(static_cast<double>(i), inputs[i]);
        const int classificationResult = classifyPointPosition(leftAnchorPoint, rightPoint, toCheck);
        if((isAlpha && classificationResult >= 0) || (!isAlpha && classificationResult <= 0)) {
            leftAnchorPoint = toCheck;
            anchorPointIndex = i;
            angle = calculateAngle(leftAnchorPoint, rightPoint);
        }
    }

    return {angle, anchorPointIndex};
}

// Calculates angles alpha and beta for window [left, right]
void processWindow(const std::vector<double>& inputs, const int windowLeftIndex, const int windowRightIndex,
    int& prevWindowLeftAnchorPointIndexAlpha, int& prevWindowLeftAnchorPointIndexBeta, Angles& angles)
{
    if(windowLeftIndex > windowRightIndex) {
        throw std::runtime_error("Invalid window borders");
    }

    if(prevWindowLeftAnchorPointIndexAlpha < 0 || prevWindowLeftAnchorPointIndexAlpha >= inputs.size()) {
        throw std::runtime_error("Invalid index for prevWindowLeftAnchorPointIndexAlpha.");
    }

    if(prevWindowLeftAnchorPointIndexBeta < 0 || prevWindowLeftAnchorPointIndexBeta >= inputs.size()) {
        throw std::runtime_error("Invalid index for prevWindowLeftAnchorPointIndexBeta.");
    }

    const int prevWindowRightIndex = windowRightIndex - 1;
    const Point prevWindowRightPoint(static_cast<double>(prevWindowRightIndex), inputs[prevWindowRightIndex]);
    const Point rightPoint(static_cast<double>(windowRightIndex), inputs[windowRightIndex]);

    const Point prevStepLeftPointAlpha(static_cast<double>(prevWindowLeftAnchorPointIndexAlpha), inputs[prevWindowLeftAnchorPointIndexAlpha]);
    if(classifyPointPosition(prevStepLeftPointAlpha, prevWindowRightPoint, rightPoint) < 0) {
        // If current last point is below the previous tangent, the new tangent will pass through the last two points of the window
        angles.alpha = calculateAngle(prevWindowRightPoint, rightPoint);
        prevWindowLeftAnchorPointIndexAlpha = prevWindowRightIndex;
    } else {
        // Otherwise, we need to check some or all points in the window. If the left anchor point of the previous tangent is still
        // within the window, only the points to its left need to be checked.
        const int optimizedRightWindowIndex = prevWindowLeftAnchorPointIndexAlpha >= windowLeftIndex ? prevWindowLeftAnchorPointIndexAlpha : windowRightIndex - 1;
        std::tie(angles.alpha, prevWindowLeftAnchorPointIndexAlpha) = recalcAngleForWindow(inputs, windowLeftIndex, optimizedRightWindowIndex, rightPoint, true);
    }

    const Point prevStepLeftPointBeta(static_cast<double>(prevWindowLeftAnchorPointIndexBeta), inputs[prevWindowLeftAnchorPointIndexBeta]);
    if(classifyPointPosition(prevStepLeftPointBeta, prevWindowRightPoint, rightPoint) > 0) {
        // If current last point is above the previous tangent, the new tangent will pass through the last two points of the window
        angles.beta = calculateAngle(prevWindowRightPoint, rightPoint);
        prevWindowLeftAnchorPointIndexBeta = prevWindowRightIndex;
    } else {
        // Otherwise, we need to check some or all points in the window. If the left anchor point of the previous tangent is still
        // within the window, only the points to its left need to be checked.
        const int optimizedRightWindowIndex = prevWindowLeftAnchorPointIndexBeta >= windowLeftIndex ? prevWindowLeftAnchorPointIndexBeta : windowRightIndex - 1;
        std::tie(angles.beta, prevWindowLeftAnchorPointIndexBeta) = recalcAngleForWindow(inputs, windowLeftIndex, optimizedRightWindowIndex, rightPoint, false);
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

    int prevWindowLeftAnchorPointIndexAlpha = 0;
    int prevWindowLeftAnchorPointIndexBeta = 0;
    for(int i = 1; i < inputs.size(); i++) {
        int left = std::max(0, i - window + 1);
        int right = i;
        processWindow(inputs, left, right, prevWindowLeftAnchorPointIndexAlpha, prevWindowLeftAnchorPointIndexBeta, result[right]);
    }
}
 

int main() {
    try{
        std::vector<double> input;
        readInput("data/input.csv", input);

        std::vector<Angles> output;
        calculate(input, output, 10);

        writeOutput("data/result_window_10.csv", output);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}