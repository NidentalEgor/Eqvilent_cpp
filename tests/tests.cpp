#include "../src/solution.h"

#include <fstream>
#include <gtest/gtest.h>

void readOutputs(const std::string& filename, std::vector<Angles>& data)
{
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file: " + filename);
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string xStr, yStr;

        if (!std::getline(ss, xStr, ',') || !std::getline(ss, yStr)) {
            throw std::runtime_error("Invalid file format");
        }

        try {
            double x = std::stod(xStr);
            double y = std::stod(yStr);
            data.emplace_back(Angles{x, y});
        } catch (const std::exception& e) {
            throw std::runtime_error("Error parsing line: " + line);
        }
    }
}

TEST(Tests, RealDataTest1) {
    std::vector<double> input;
    input.push_back(11384.96);
    input.push_back(11373.01);

    std::vector<Angles> output;
    calculate(input, output, 10);

    const std::vector<Angles> expected = {{0.0, 0.0}, {1.48731,1.48731}};

    ASSERT_EQ(expected.size(), output.size());
    for(int i = 0; i < output.size(); i++){
        EXPECT_NEAR(output[i].alpha, expected[i].alpha, 1e-5);
        EXPECT_NEAR(output[i].beta, expected[i].beta, 1e-5);
    }
}

TEST(Tests, RealDataTest2) {
    std::vector<double> input;
    input.push_back(11384.96);
    input.push_back(11373.01);
    input.push_back(11324);
    std::vector<Angles> output;
    calculate(input, output, 100);

    const std::vector<Angles> expected =
        {{0.0, 0.0}, {1.48731, 1.48731}, {1.5504, 1.538}};

    ASSERT_EQ(expected.size(), output.size());
    for(int i = 0; i < output.size(); i++){
        EXPECT_NEAR(output[i].alpha, expected[i].alpha, 1e-5);
        EXPECT_NEAR(output[i].beta, expected[i].beta, 1e-5);
    }
}

TEST(Tests, RealDataTestAllWindow10) {
    std::vector<double> input;
    readInputs("/Users/egornidental/Repositories/Eqvilent_cpp/data/input.csv", input);

    std::vector<Angles> output;
    calculate(input, output, 10);

    ASSERT_EQ(input.size(), output.size());

    std::vector<Angles> expected;
    expected.reserve(input.size());
    readOutputs("/Users/egornidental/Repositories/Eqvilent_cpp/data/window_10.csv", expected);

    ASSERT_EQ(expected.size(), output.size());
    for(int i = 0; i < output.size(); i++){
        const double outputAlpha = output[i].alpha;
        const double outputBeta = output[i].beta;
        const double expectedAlpha = expected[i].alpha;
        const double expectedBeta = expected[i].beta;

        EXPECT_NEAR(outputAlpha, expectedAlpha, 1e-5);
        EXPECT_NEAR(outputBeta, expectedBeta, 1e-5);
    }
}

TEST(Tests, RealDataTestAllWindow100) {
    std::vector<double> input;
    readInputs("/Users/egornidental/Repositories/Eqvilent_cpp/data/input.csv", input);

    std::vector<Angles> output;
    calculate(input, output, 100);

    std::vector<Angles> expected;
    expected.reserve(input.size());
    readOutputs("/Users/egornidental/Repositories/Eqvilent_cpp/data/window_100.csv", expected);

    ASSERT_EQ(expected.size(), output.size());
    for(int i = 0; i < output.size(); i++){
        const double outputAlpha = output[i].alpha;
        const double outputBeta = output[i].beta;
        const double expectedAlpha = expected[i].alpha;
        const double expectedBeta = expected[i].beta;

        EXPECT_NEAR(outputAlpha, expectedAlpha, 1e-5);
        EXPECT_NEAR(outputBeta, expectedBeta, 1e-5);
    }
}

TEST(Tests, RealDataTestAllWindow1000) {
    std::vector<double> input;
    readInputs("/Users/egornidental/Repositories/Eqvilent_cpp/data/input.csv", input);

    std::vector<Angles> output;
    calculate(input, output, 1000);

    std::vector<Angles> expected;
    expected.reserve(input.size());
    readOutputs("/Users/egornidental/Repositories/Eqvilent_cpp/data/window_1000.csv", expected);

    ASSERT_EQ(expected.size(), output.size());
    for(int i = 0; i < output.size(); i++){
        const double outputAlpha = output[i].alpha;
        const double outputBeta = output[i].beta;
        const double expectedAlpha = expected[i].alpha;
        const double expectedBeta = expected[i].beta;

        EXPECT_NEAR(outputAlpha, expectedAlpha, 1e-5);
        EXPECT_NEAR(outputBeta, expectedBeta, 1e-5);
    }
}

TEST(CalculateAngleTests, DISABLED_Test1) {
    const Point leftPoint(0.0, 1.0);
    const Point rightPoint(1.0, 0.0);
    double angle = calculateAngle(leftPoint, rightPoint);
    EXPECT_NEAR(angle, -0.785398, 1e-5);
}

TEST(CalculateAngleTests, DISABLED_Test2) {
    const Point leftPoint(0.0, -1.0);
    const Point rightPoint(1.0, 0.0);
    double angle = calculateAngle(leftPoint, rightPoint);
    EXPECT_NEAR(angle, 0.785398, 1e-5);
}
