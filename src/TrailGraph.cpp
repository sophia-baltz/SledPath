#include "TrailGraph.h"
#include <cmath>
#include <stdexcept>
#include <iostream>
#include <algorithm>

using namespace tinyxml2;


//1. open the xml file
//2. find each <trk>
//3. convert each trail to an edge
//4. collect all edges and nodes
//5. turn into graph


//unclear
int countEdge = 0;
int countNode = 0;

TrailGraph parseGPXFile(const std::string& filename){
    XMLDocument doc;
    XMLError err = doc.LoadFile(filename.c_str());
    
    if (err != XML_SUCCESS) {
        throw(std::runtime_error("Cannot open file"));
    }

    tinyxml2::XMLElement* element = doc.RootElement();
    XMLElement* child = element->FirstChildElement("trk");
    TrailGraph graph;

    while (child != nullptr) {
        std::cout << child->Value() << std::endl;
        Edge tmp = parseTrk(child, countEdge, countNode);
        graph.edges.push_back(tmp);
        child = child->NextSiblingElement("trk");
    }

    return graph;
}


//assign trail name based on <trk><name>
//asign first coordinate to node
//give that node id and put id into starNodeId
//go through all coordinates, make coordinate out of
//put each coordinate into vector in order
//reach last coordinate because next <trk><name>
//give that coordinate node
//asign that node to lastNode in edge


/*
gpx
    trk
        name
        trkseg
            trkpt
            
  while trkname -> getText() == cuurname  
  */
        
/*
This is the Haversine formula!
we are using haversine because accurately depicts earth as sphere.
we are not making own haversine because that would be stupid! :))))))
*/

double toRadians(double degree) {
    return degree * DEG_TO_RAD;
}

double calculateDistance(double lat1, double lon1, double lat2, double lon2) {
    // Convert degrees to radians
    lat1 = toRadians(lat1);
    lon1 = toRadians(lon1);
    lat2 = toRadians(lat2);
    lon2 = toRadians(lon2);

    // Haversine formula
    double dLon = lon2 - lon1;
    double dLat = lat2 - lat1;
    double a = std::sin(dLat / 2.0) * std::sin(dLat / 2.0) +
               std::cos(lat1) * std::cos(lat2) * 
               std::sin(dLon / 2.0) * std::sin(dLon / 2.0);
    double c = 2.0 * std::asin(std::sqrt(a));
    double distance = EARTH_RADIUS_KM * c;

    return distance;
}

double distanceHelper(std::vector<Coordinate> trailShape) {  
    double totalDistance = 0;  
    //iterate through vector
    //find distance between each point call helper haversine
    //add distance between each vector
    //return distance

    //add edge case for if size less than 2
    for (unsigned i = 0; i < trailShape.size() - 2; i ++) {
        double lat1 = trailShape[i].lat;
        double lon1 = trailShape[i].lon;
        double lat2 = trailShape[i + 1].lat;
        double lon2 = trailShape[i + 1].lon;
        totalDistance += calculateDistance(lat1, lon1, lat2, lon2);
    }
    return totalDistance;
}



Edge parseTrk(XMLElement* trk, int& edgeCount, int& nodeCount) {
    XMLElement* name = trk->FirstChildElement("name");

    //td::cout << name->GetText() << std::endl;
    Edge newEdge;
    newEdge.id = edgeCount++;

    newEdge.TrailId = name->GetText();

    XMLElement* trkseg = trk->FirstChildElement("trkseg");
    XMLElement* trkpt = trkseg->FirstChildElement("trkpt");
    bool isFirst = true;
    

    while (trkpt != NULL) {
    Coordinate point; 
    const char* latAttr = trkpt->Attribute("lat");
    const char* lonAttr = trkpt->Attribute("lon");

        if (latAttr && lonAttr) {
        double lat = std::stod(latAttr);
        double lon = std::stod(lonAttr);

        point = {lat, lon}; 

        if (isFirst) {
            newEdge.startNode = point;
            isFirst = false;
        }
    }

    Node newNode;
    newNode.id = nodeCount++;
    newNode.point = point;

    newEdge.trailShape.push_back(point);

    trkpt = trkpt->NextSiblingElement("trkpt");
    }
    newEdge.endNode = newEdge.trailShape.back();
    newEdge.distance = distanceHelper(newEdge.trailShape);
    return newEdge;
}
