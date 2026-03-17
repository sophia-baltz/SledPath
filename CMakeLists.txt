cmake_minimum_required(VERSION 3.10.0)
project(SledPath VERSION 0.1.0 LANGUAGES C CXX)

add_executable(SledPath main.cpp)

# Include tinyxml2.cpp along with your main file
# This ensures the compiler builds the library logic into your app
add_executable(GPXParser main.cpp tinyxml2.cpp)

include(CTest)
enable_testing()

