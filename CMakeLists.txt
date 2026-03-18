cmake_minimum_required(VERSION 3.10.0)
project(SledPath VERSION 0.1.0 LANGUAGES C CXX)

include_directories(include)

add_executable(SledPath 
    main.cpp 
    src/TrailGraph.cpp 
    src/tinyxml2.cpp
)

include(CTest)
enable_testing()

# Include tinyxml2.cpp along with your main file
# This ensures the compiler builds the library logic into your app

