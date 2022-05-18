#pragma once 
#include <iostream>
#include <map>
#include "airport.h"
#include "vertex.h"
#include "arc.h"
#include <set>


using namespace std;

class Graph {
public:
    ~Graph();
    /// @param dataPath file that constains the info of all routes
    bool initAirports(string dataPath);
    
    /// @param dataPath file that contains the info of all routes
    bool initGraph(string dataPath);
    
    
    //BFS, given an airport ID, find a connected subgraph 
    //vertexList contains all connected airports' id in the subgraph
    void BFS(int airportId, vector<int>& vertexList);
    
    
    /// dijkstra's algorithm
    /// @param vertexList must use the output of BFS traversal
    void shortestPath(vector<int>& vertexList, int from, map<int, int>& path);
    
    /// @param airportId return a pointer to the correpsonding ID
    Airport* getAirportById(int airportId);
    
    //for test cases
    map<int, Airport*> getAirportMap();
    map<int, Vertex*> getVertexMap();
    set<int> getBFSset();
    void Astar(int from, int to, vector<int>& path);
    double getDistance(double fromLat,double fromLng,double toLat,double toLng);
    double getDisTest(int from, int to);
private:
    
    
    double rad(double value);
    set<int> BFSset;

    
    //map the id to the airport pointer
    //since the unique id for the airport will not be incomplete or missing
    map<int, Airport*> airportMap;
    //map the id to the vertex in the graph
    map<int, Vertex*> vertexs;
};


