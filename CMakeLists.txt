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

#adding catch2 to makefile
add_subdirectory(Catch2)

add_executable(tests
    tests/tests_helper.cpp
    src/TrailGraph.cpp
    src/tinyxml2.cpp
)

target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

include(CTest)
enable_testing()

include(Catch)
catch_discover_tests(tests)
