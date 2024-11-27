#include "solution.h"

#include <vector>
#include <iostream>
#include <utility>

int main() {
    std::vector<double> input;
    readInput("../../../data/input.csv", input);

    std::vector<Angles> output;
    calculate(input, output, 10);

    writeOutput("../../../data/result_window_10.csv", output);

    return 0;
}