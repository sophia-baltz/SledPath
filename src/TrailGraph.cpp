#include "TrailGraph.h"
#include <cmath>
#include <stdexcept>
#include <iostream>

using namespace tinyxml2;


//1. open the xml file
//2. find each <trk>
//3. convert each trail to an edge
//4. collect all edges and nodes
//5. turn into graph


//Potentiall dumb ahh variable (static?)
int count = 0;

TrailGraph parseGPXFile(const std::string& filename){
    XMLDocument doc;
    XMLError err = doc.LoadFile(filename.c_str());
    
    if (err != XML_SUCCESS) {
        throw(std::runtime_error("Cannot open file"));
    }

    XMLElement* element = doc.RootElement();
    XMLElement* child = element->FirstChildElement() ;

    std::cout << child->Value() << std::endl;

    TrailGraph graph;
    return graph;
}


Edge parseTrk(XMLElement* trk, int& count) {
    XMLElement* name = trk->FirstChildElement("name");

    std::cout << name->GetText() << std::endl;
    Edge newEdge;
    newEdge.id = count++;

    newEdge.TrailId = name->GetText();

    XMLElement* trkseg = trk->FirstChildElement("trkseg");
    XMLElement* trkpt = trkseg->FirstChildElement("trkpt");

    const char* latAttr = trkpt->Attribute("lat");
    const char* lonAttr = trkpt->Attribute("lon");

        if (latAttr && lonAttr) {
        double lat = std::stod(latAttr);
        double lon = std::stod(lonAttr);

        Coordinate point{lat, lon}; 
    }

    //newEdge.startNodeId = 
    return newEdge;
}
