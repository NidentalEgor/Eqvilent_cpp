#include <gtest/gtest.h>
// #include </Users/egornidental/Repositories/Eqvilent_cpp/build/Debug/_deps/googletest-src/googletest/include/gtest/gtest.h>
#include "../src/task.h"

// Test for surface area and volume calculation of a cube
TEST(Tests, DISABLED_Test1) {
    std::vector<double> input;
    input.push_back(0.0);
    input.push_back(1.0);
    std::vector<std::pair<double, double>> output;
    Process(input, output);

    for(const auto& angles : output){
        std::cout << "alpha = " << angles.first << " beta = " << angles.second << std::endl;
    }
}

TEST(Tests, DISABLED_Test2) {
    std::vector<double> input;
    input.push_back(0.0);
    input.push_back(1.0);
    input.push_back(1.5);
    std::vector<std::pair<double, double>> output;
    Process(input, output);

    for(const auto& angles : output){
        std::cout << "alpha = " << angles.first << " beta = " << angles.second << std::endl;
    }
}

TEST(Tests, DISABLED_Test3) {
    std::vector<double> input;
    input.push_back(0.0);
    input.push_back(1.0);
    input.push_back(1.5);
    input.push_back(0.5);
    std::vector<std::pair<double, double>> output;
    Process(input, output);

    for(const auto& angles : output){
        std::cout << "alpha = " << angles.first << " beta = " << angles.second << std::endl;
    }
}

TEST(Tests, DISABLED_Test11) {
    std::vector<double> input;
    input.push_back(2.0);
    input.push_back(0.5);
    input.push_back(0.0);

    std::vector<std::pair<double, double>> output;
    Process(input, output);

    std::vector<std::pair<double, double>> expected = {{0.0, 0.0}, {0.392699, 0.0}, {0.785398, 0.0}};
    ASSERT_EQ(expected.size(), output.size());
    for(int i = 0; i < output.size(); i++){
        EXPECT_NEAR(output[i].first, expected[i].first, 1e-5);
        // EXPECT_NEAR(output[i].second, expected[i].second, 1e-5);
    }
}

TEST(Tests, DISABLED_Test12) {
    std::vector<double> input;
    input.push_back(1.5);
    input.push_back(1.0);
    input.push_back(0.0);

    std::vector<std::pair<double, double>> output;
    Process(input, output);

    std::vector<std::pair<double, double>> expected = {{0.0, 0.0}, {0.785398, 0.0}, {0.785398, 0.0}};
    ASSERT_EQ(expected.size(), output.size());
    for(int i = 0; i < output.size(); i++){
        EXPECT_NEAR(output[i].first, expected[i].first, 1e-5);
        // EXPECT_NEAR(output[i].second, expected[i].second, 1e-5);
    }
}

TEST(Tests, DISABLED_RealDataTest1) {
    std::vector<double> input;
    input.push_back(11384.96);
    input.push_back(11373.01);
    std::vector<std::pair<double, double>> output;
    Process(input, output);

    for(const auto& angles : output){
        std::cout << "alpha = " << angles.first << " beta = " << angles.second << std::endl;
    }
    std::vector<std::pair<double, double>> expected = {{0.0, 0.0}, {1.48731,1.48731}};

    ASSERT_EQ(expected.size(), output.size());
    for(int i = 0; i < output.size(); i++){
        EXPECT_NEAR(output[i].first, expected[i].first, 1e-5);
        EXPECT_NEAR(output[i].second, expected[i].second, 1e-5);
    }
}

TEST(Tests, RealDataTest2) {
    std::vector<double> input;
    input.push_back(11384.96);
    input.push_back(11373.01);
    input.push_back(11324);
    std::vector<std::pair<double, double>> output;
    Process(input, output);

    for(const auto& angles : output){
        std::cout << "alpha = " << angles.first << " beta = " << angles.second << std::endl;
    }
    std::vector<std::pair<double, double>> expected =
        {{0.0, 0.0}, {1.48731, 1.48731}, {1.5504, 1.538}};

    // 0,0
    // 1.48731,1.48731
    // 1.5504,1.538

    ASSERT_EQ(expected.size(), output.size());
    for(int i = 0; i < output.size(); i++){
        EXPECT_NEAR(output[i].first, expected[i].first, 1e-5);
        EXPECT_NEAR(output[i].second, expected[i].second, 1e-5);
    }
}

TEST(CalculateAngleTests, DISABLED_Test1) {
    const Point leftPoint(0.0, 1.0);
    const Point rightPoint(1.0, 0.0);
    double angle = calculateAngle(leftPoint, rightPoint);
    EXPECT_NEAR(angle, 0.785398, 1e-5);
}

TEST(CalculateAngleTests, DISABLED_Test2) {
    const Point leftPoint(0.0, -1.0);
    const Point rightPoint(1.0, 0.0);
    double angle = calculateAngle(leftPoint, rightPoint);
    EXPECT_NEAR(angle, 0.785398, 1e-5);
}

// Main function to run all tests
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
