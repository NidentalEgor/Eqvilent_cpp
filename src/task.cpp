#include "task.h"

#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <utility>
#include <cmath>
#include <limits>

void printPoint(const std::string& title, const Point& p){
    std::cout << title << " x = "<< p.x << " y = " << p.y << std::endl;
}

void readInputs2(const std::string& filePath, std::vector<double>& inputs)
{
    std::ifstream file(filePath);
    std::string line;

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filePath);
    }

    while (std::getline(file, line)) {
        try {
            // std::cout << line << std::endl;

            double value = std::stod(line);

            // std::cout << std::fixed << std::setprecision(10) << value << std::endl;

            inputs.push_back(/*std::stod(line)*/value); // Convert each line to a double
        } catch (const std::invalid_argument &e) {
            std::cerr << "Invalid number in file: " << line << "\n";
        }
    }
}

double calculateAngle(const Point& leftPoint, const Point& rightPoint) {
    // double dx = rightPoint.x - leftPoint.x;  // Разница по x
    // double dy = rightPoint.y - leftPoint.y; // Разница по y

    // // atan2 автоматически учитывает знак dx и dy
    // double angle = std::atan2(dy, dx); // Угол в радианах

    // // Нормализация в диапазон [0, 2π)
    // if (angle < 0) {
    //     angle += 2 * M_PI;
    // }

    // return angle; // Угол в радианах

    // Векторы для прямых
    double v1x = rightPoint.x - leftPoint.x;
    double v1y = rightPoint.y - leftPoint.y;
    double v2x = rightPoint.x - leftPoint.x;
    double v2y = 0.0;

    // Скалярное произведение
    double dotProduct = v1x * v2x + v1y * v2y;

    // Длины векторов
    double lengthV1 = std::hypot(v1x, v1y);
    double lengthV2 = std::hypot(v2x, v2y);

    // Косинус угла
    double cosTheta = dotProduct / (lengthV1 * lengthV2);

    // Ограничиваем значение косинуса в диапазоне [-1, 1] для избежания ошибок из-за погрешностей
    cosTheta = std::clamp(cosTheta, -1.0, 1.0);

    // Вычисляем угол через арккосинус
    double angle = std::acos(cosTheta);

    return angle; // Угол в радианах
}

// Comment
int isPointOutside(const Point& point1, const Point& point2, const Point& toCheck){
    double D = (toCheck.x - point1.x) * (point2.y - point1.y) - (toCheck.y - point1.y) * (point2.x - point1.x);

    if(D > 0.0){
        return -1; // слева
    } else if(D < 0.0){
        return 1; // справа
    } else{
        return 0;
    }
}

void recalcAngles(const std::vector<double>& inputs, const std::pair<int, int>& newInputIndexes,
    const std::pair<int, int>& outdatedInputIndexes, std::vector<Angles>& result)
{
    std::cout << "recalcAngles" << std::endl;
}

void processWindow(const std::vector<double>& inputs, int left, int right,
    std::vector<Angles>& result)
{
    // std::cout << "left = " << left << " right = " << right << std::endl;

    if(left == right){
        result[right].alpha = 0.0;
        result[right].beta = 0.0;
        return;
    }

    Point leftPoint(static_cast<double>(right - 1), inputs[right - 1]);
    Point rightPoint(static_cast<double>(right), inputs[right]);

// нужно справа налево идти и искать максимум и только для него пересчитывать прямую

    // for(int i = left + 1; i < right - 1; i++){
    //     Point toCheck(static_cast<double>(i), inputs[i]);
    //     if(isPointOutside(leftPoint, rightPoint, toCheck)){
    //         leftPoint = toCheck;
    //     }
    // }

    double currentMax = /*inputs[right];*/std::numeric_limits<double>::min();
    double currentMin = /*inputs[right];*/std::numeric_limits<double>::max();
    Point maxPoint(static_cast<double>(right), std::numeric_limits<double>::min());
    Point minPoint(static_cast<double>(right), std::numeric_limits<double>::max());
    for(int i = right - 1; i >= left; i--){
        const double currentY = inputs[i];
        if(currentY > currentMax){
            Point toCheck(static_cast<double>(i), inputs[i]);
            if(isPointOutside(leftPoint, rightPoint, toCheck) >= 0){
                maxPoint = toCheck;
                double alpha = calculateAngle(maxPoint, rightPoint);
                result[right].alpha = std::max(alpha, result[right].alpha);
            }
            // currentMax = inputs[i];
        }

        if(currentY < currentMin){
            Point toCheck(static_cast<double>(i), inputs[i]);
            if(isPointOutside(leftPoint, rightPoint, toCheck) <= 0){
                minPoint = toCheck;
                double beta = calculateAngle(minPoint, rightPoint);
                result[right].beta = std::max(beta, result[right].beta); // ???
            }
            // currentMin = inputs[i];
        }
    }

    // printPoint("Left", leftPoint);
    // printPoint("Right", rightPoint);
    // double alpha = calculateAngle(leftPoint, rightPoint);
    // double beta = 0.0;

    // calculate alpha and beta!

    // result[right].alpha = alpha;
    // result[right].beta = beta;

    // std::cout << result[right].alpha << std::endl;
}

void calculate(const std::vector<double>& inputs, std::vector<Angles>& result, int window)
{
    //  recalcAngles(inputs, std::make_pair(0, window), std::make_pair(-1, -1), result);
    //  for(int i = window; i < inputs.size(); i++){
    //      recalcAngles(inputs, std::make_pair(i, i + 1), std::make_pair(i - window, i - window + 1), result);
    //  }

    for(int i = 0; i < inputs.size(); i++){
        int left = std::max(0, i - window);
        int right = i;
        processWindow(inputs, left, right, result);
    }
}

void readInput(){
    std::vector<double> inputs;
    inputs.reserve(100000);
    
    readInputs2("/Users/egornidental/Repositories/Eqvilent_cpp/data/input.csv", inputs);

    std::vector<Angles> outputs;
    outputs.reserve(inputs.size());
    calculate(inputs, outputs, 10);
    // write outputs
}

void readInputTest1(){
    std::vector<double> inputs;
    inputs.reserve(100000);
    
    readInputs2("/Users/egornidental/Repositories/Eqvilent_cpp/data/input.csv", inputs);

    std::vector<Angles> outputs;
    outputs.reserve(inputs.size());
    calculate(inputs, outputs, 10);
    // write outputs
}

void Process(const std::vector<double>& input, std::vector<std::pair<double, double>>& output){
    std::vector<Angles> tempOutput;
    tempOutput.resize(input.size());
    calculate(input, tempOutput, 10);

    output.clear();
    output.reserve(input.size());
    for(const auto& angle : tempOutput){
        output.push_back(std::make_pair(angle.alpha, angle.beta));
    }
}
 