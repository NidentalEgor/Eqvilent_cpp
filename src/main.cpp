#include "task.h"
#include <vector>
#include <iostream>
#include <utility>

int main() {
    std::vector<double> input;
    input.push_back(11384.96);
    input.push_back(11373.01);
    std::vector<std::pair<double, double>> output;
    // readInputs2("/Users/egornidental/Repositories/Eqvilent_cpp/data/input.csv", inputs)
    Process(input, output);

    for(const auto& angles : output){
        std::cout << "alpha = " << angles.first << " beta = " << angles.second << std::endl;
    }

    return 0;
}