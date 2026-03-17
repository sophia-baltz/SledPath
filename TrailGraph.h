#ifndef TRAIL_GRAPH_H
#define TRAIL_GRAPH_H

#include <string>
#include <vector>
#include <unordered_map>

struct Coordinate{
    double lat;
    double lon;
};

struct Node{
    int id;
    Coordinate point;
};

struct Edge{
    int id;
    int startNodeId;
    int endNodeId;

    std::string TrailId;
    std::string TrailName;

    std::vector<Coordinate> trailShape;
    
    double distance;
    //double estimatedMPH;
    double weight;

    bool isOpen;
    bool snowmobileLegal;
    bool roadConnects;

    std::string roadType;
    std::string surface; //maybe use for speed later unclear right now
    std::string sourceOfData;
};

#endif
