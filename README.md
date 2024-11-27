There are two ways to build and run the solution:

The first method builds the version written in a single file and runs it. The result will appear in the  folder "data" with the name "result_window_10.csv". The commands may vary for your compiler. Use the following commands for clang:

clang++ -std=c++14 main.cpp -o main
./main

The second method runs tests for all three window size options for which there are correct answers. CMake version 3 or higher must be installed. Use the following commands:

./build.sh [Debug/Release]
cd build/[Debug/Release]/bin
./tests