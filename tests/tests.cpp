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

TEST(RealDataTest, FirstTwoPoints) {
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

TEST(RealDataTest, FirstThreePoints) {
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

TEST(RealDataTest, Window10) {
    std::vector<double> input;
    readInput("../../../data/input.csv", input);

    std::vector<Angles> output;
    calculate(input, output, 10);

    ASSERT_EQ(input.size(), output.size());

    std::vector<Angles> expected;
    expected.reserve(input.size());
    readOutputs("../../../data/window_10.csv", expected);

    ASSERT_EQ(expected.size(), output.size());
    for(int i = 0; i < output.size(); i++){
        const double outputAlpha = output[i].alpha;
        const double outputBeta = output[i].beta;
        const double expectedAlpha = expected[i].alpha;
        const double expectedBeta = expected[i].beta;

        EXPECT_NEAR(outputAlpha, expectedAlpha, 1e-5) << "element #" << i;
        EXPECT_NEAR(outputBeta, expectedBeta, 1e-5) << "element #" << i;
    }
}

TEST(RealDataTest, Window100) {
    std::vector<double> input;
    readInput("../../../data/input.csv", input);

    std::vector<Angles> output;
    calculate(input, output, 100);

    std::vector<Angles> expected;
    expected.reserve(input.size());
    readOutputs("../../../data/window_100.csv", expected);

    ASSERT_EQ(expected.size(), output.size());
    for(int i = 0; i < output.size(); i++){
        const double outputAlpha = output[i].alpha;
        const double outputBeta = output[i].beta;
        const double expectedAlpha = expected[i].alpha;
        const double expectedBeta = expected[i].beta;

        EXPECT_NEAR(outputAlpha, expectedAlpha, 1e-5) << "element #" << i;
        EXPECT_NEAR(outputBeta, expectedBeta, 1e-5) << "element #" << i;
    }
}

TEST(RealDataTest, Window1000) {
    std::vector<double> input;
    readInput("../../../data/input.csv", input);

    std::vector<Angles> output;
    calculate(input, output, 1000);

    std::vector<Angles> expected;
    expected.reserve(input.size());
    readOutputs("../../../data/window_1000.csv", expected);

    ASSERT_EQ(expected.size(), output.size());
    for(int i = 0; i < output.size(); i++){
        const double outputAlpha = output[i].alpha;
        const double outputBeta = output[i].beta;
        const double expectedAlpha = expected[i].alpha;
        const double expectedBeta = expected[i].beta;

        EXPECT_NEAR(outputAlpha, expectedAlpha, 1e-5) << "element #" << i;
        EXPECT_NEAR(outputBeta, expectedBeta, 1e-5) << "element #" << i;
    }
}

TEST(CalculateAngleTests, UnitCircleSecondQuadrant) {
    const Point leftPoint(-1.0, 1.0);
    const Point rightPoint(0.0, 0.0);
    double angle = calculateAngle(leftPoint, rightPoint);
    EXPECT_NEAR(angle, 0.785398, 1e-5);
}

TEST(CalculateAngleTests, UnitCircleThirdQuadrant) {
    const Point leftPoint(-1.0, -1.0);
    const Point rightPoint(0.0, 0.0);
    double angle = calculateAngle(leftPoint, rightPoint);
    EXPECT_NEAR(angle, -0.785398, 1e-5);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    ::testing::GTEST_FLAG(break_on_failure) = true;

    return RUN_ALL_TESTS();
}