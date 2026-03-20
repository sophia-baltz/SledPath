#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "TrailGraph.h"

using namespace tinyxml2;

TEST_CASE("GPX Parsed Correctly (file with one track)", "[GPX]") {
    TrailGraph graph = parseGPXFile("../tests/UP_1.gpx");
    REQUIRE(graph.edges.size() == 1);
    
    Edge e = graph.edges[0];
    REQUIRE(e.TrailId == "UP1");
    REQUIRE(e.startNode.lon == -89.76654392250093);
    REQUIRE(e.startNode.lat == 46.80352591942095);
}

/*
TEST_CASE("individual tracks parsed correctly", "[trk]") {
    
    REQUIRE ()
}
*/


