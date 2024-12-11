#include "solution.h"

#include <vector>
#include <iostream>
#include <utility>

int main() {
    try{
        std::vector<double> input;
        readInput("../../../data/input.csv", input);

        std::vector<Angles> output;
        calculate(input, output, 10);

        writeOutput("../../../data/result_window_10.csv", output);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}