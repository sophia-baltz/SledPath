#ifndef TRAIL_GRAPH_H
#define TRAIL_GRAPH_H

#include <string>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <stdexcept>
#include "tinyxml2.h"

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
    //std::string TrailName;

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

struct TrailGraph {
    std::vector<Node> nodes;
    std::vector<Edge> edges;
};

//functions


//this file should go through the large gpx file
//1. open the xml file
//2. find each <trk>
//3. convert each trail to an edge
//4. collect all edges and nodes
//5. turn into graph
TrailGraph parseGPXFile(const std::string& filename);


//functions
//assign trail name based on <trk><name>
//asign first coordinate to node
//give that node id and put id into starNodeId
//go through all coordinates, make coordinate out of
//put each coordinate into vector in order
//reach last coordinate because next <trk><name>
//give that coordinate node
//asign that node to lastNode in edge

#endif
