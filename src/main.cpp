#include "solution.h"

#include <vector>
#include <iostream>
#include <utility>

int main() {
    std::vector<double> input;
    readInputs("/Users/egornidental/Repositories/Eqvilent_cpp/data/input.csv", input);

    std::vector<Angles> output;
    calculate(input, output, 10);

    writeOutput("/Users/egornidental/Repositories/Eqvilent_cpp/data/result_window_10.csv", output);

    return 0;
}