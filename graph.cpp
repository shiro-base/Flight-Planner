#include "graph.h"
#include "airport.h"
#include "vertex.h"
#include "arc.h"
#include "node.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <queue>
#include <set>
#include <limits>


Graph::~Graph() {
    auto begin = airportMap.begin();
    auto end = airportMap.end();
    
    while (begin != end) {
        delete begin->second;
        begin->second = nullptr;
        begin++;
    }
    
    auto vbegin = vertexs.begin();
    auto vend = vertexs.end();
    
    while (vbegin != vend) {
        delete vbegin->second;
        vbegin->second = nullptr;
        vbegin++;
    }
}

bool Graph::initAirports(string dataPath) {
    ifstream fin;
    fin.open(dataPath);
    if (fin.fail()) {
        return false;
    }
    
    // parse the data line by line
    string line;
    while(getline(fin, line)) {
        // use the information from the line
        //construct an airport using constructor
        //see airport.cpp
        Airport *airport = new Airport(line);
        //EDGE CASES
        //give up the data if we cannot get one of the necessary info
        if (line.empty()) {
            continue;
        }
        if (airport->getAirportId() == 0 || airport->getLatitude() == 0.0 || airport->getLongitude() == 0.0) {
            delete airport;
            continue;
        }
        //map the id to the airport pointer
        //it is more convenient
        airportMap.insert(make_pair(airport->getAirportId(), airport));
    }
    fin.close();
    return true;
}

//dataPath contains all information about routes
bool Graph::initGraph(string dataPath) {
    ifstream fin;
    fin.open(dataPath);

    if (fin.fail()) {
        return false;
    }
    
    //read line by line
    string line;
    while(getline(fin, line)) {
        //use "," as delimiter to segment and parse data
        istringstream iss(line);
        // convert from string to int to store the data
        stringstream ss;
        string buffer;
        
        getline(iss, buffer, ',');
        getline(iss, buffer, ',');
        getline(iss, buffer, ',');
        getline(iss, buffer, ',');
        ss << buffer;
        int sourceAirportId = 0;
        ss >> sourceAirportId;
        ss.clear();
        
        getline(iss, buffer, ',');
        getline(iss, buffer, ',');
        ss << buffer;
        int destinationAirportId = 0;
        ss >> destinationAirportId;
        ss.clear();
        
        
        Airport *fromAirport = nullptr;
        if (airportMap.find(sourceAirportId) != airportMap.end()) {
            fromAirport = airportMap.find(sourceAirportId)->second;
        }
        
        Airport *toAirport = nullptr;
        if (airportMap.find(destinationAirportId) != airportMap.end()) {
            toAirport = airportMap.find(sourceAirportId)->second;
        }
        //SINCE SOME AIRPORT ID COULD BE FOUND IN ROUTE FILE
        //AIRPORT AS SOURCE OR DESTINATION IN ROUTE.DAT
        //MAY NOT BE FOUND IN AIRPORT.DAT
        if (toAirport == nullptr || fromAirport == nullptr) {
            continue;
        }
        Vertex *from = nullptr;
        Vertex *to = nullptr;
        
        //find source vertex
        auto iter = vertexs.find(sourceAirportId);
        // vertex not exist
        if (iter == vertexs.end()) {
            // generate one
            from = new Vertex(sourceAirportId);
            vertexs.insert(make_pair(sourceAirportId, from));
        }
        else {
            from = iter->second;
        }
        
        // find destination vertex
        iter = vertexs.find(destinationAirportId);
        if (iter == vertexs.end()) {
            to = new Vertex(destinationAirportId);
            vertexs.insert(make_pair(destinationAirportId, to));
        }
        else { 
            to = iter->second;
        }
        
        //get the distance between two airports
        double distance = getDistance(fromAirport->getLatitude(), fromAirport->getLongitude(), toAirport->getLatitude(), toAirport->getLongitude());
        
        // construct a directed edge
        Arc arc(destinationAirportId, distance);
        from->addArc(arc);
    }
    fin.close();
    return true;
}

//BFS
void Graph::BFS(int airportId, vector<int>& vertexList) {
    //seach the vertex using its ID
    //from our vertex vector of the graph
    Vertex *vertex = nullptr;
    auto iter = vertexs.find(airportId);
    
    if (iter == vertexs.end()) {
        std::cout << "Sorry, airport not found" << "\n";
        return;
    }
    else {
        vertex = iter->second;
    }

    queue<Vertex*> searchQueue;
    //store and track the searched airports' id
    set<int> alreadySearchSet;
    //store and track the added airports' id
    set<int> alreadyAddSet;
    
    // push the start point to the queue
    searchQueue.push(vertex);
    // update the set
    //already pushed into queue
    alreadySearchSet.insert(vertex->getId());
    
    while (!searchQueue.empty()) {
        vertex = searchQueue.front();
        searchQueue.pop();
        

        //if could be inserted, then current vertex have not be added to the output vector
        if (alreadyAddSet.insert(vertex->getId()).second) {
            vertexList.push_back(vertex->getId());
        }
        
        // directed edges starts from the current 
        vector<Arc>& arcs = vertex->getArcs();
        
        // traverse all the directed edge
        for (unsigned long i = 0; i < arcs.size(); i++) {
            if (alreadySearchSet.insert(arcs[i].getTail()).second) {
                searchQueue.push(vertexs.find(arcs[i].getTail())->second);
            }
        }
    }
    BFSset = alreadyAddSet;
}

Airport* Graph::getAirportById(int airportId) {
 
    auto iter = airportMap.find(airportId);
    // airport not exist
    if (iter == airportMap.end()) {
        std::cout << "airport not found" << std::endl;
        return nullptr;
    }
    else {
        return iter->second;
    }
}

map<int, Airport*> Graph::getAirportMap() {
    return airportMap;
}

map<int, Vertex*> Graph::getVertexMap() {
    return vertexs;
}

//Dijkstras' algorithm
void Graph::shortestPath(vector<int>& vertexList, int from, map<int, int>& path) {
    //track if the vertex has been passed in calculation
    map<int, bool> state;
    //track the minimum distance from from to the vertex
    //key: vertex id
    //value: shortest distance from from to key
    map<int, double> minDistance;
    
    double max = std::numeric_limits<double>::max();
    for (unsigned long i = 0; i < vertexList.size(); i++) {
        //initialization
        state.insert(make_pair(vertexList[i], false));
        // intialize the current minDistance from each vertex to from
        // to max.
        minDistance.insert(make_pair(vertexList[i], max));
        //no airport, intialize the id to all 0
        path.insert(make_pair(vertexList[i], 0));
    }
    
    // update and set up
    state.find(from)->second = true;
    minDistance.find(from)->second = 0;
    
    // get all directed edges from the start airport
    vector<Arc>& arcs = vertexs.find(from)->second->getArcs();
    // set distance to all vertices
    for (unsigned long i = 0; i < arcs.size(); i++) {
        minDistance.find(arcs[i].getTail())->second = arcs[i].getDistance();
        // set preceding vertex
        path.find(arcs[i].getTail())->second = from;
    }
    
    for (unsigned long i = 1; i < vertexList.size(); i++) {
        //initialize to max
        double min = std::numeric_limits<double>::max();

        auto begin = minDistance.begin();
        auto end = minDistance.end();
        
        
        //store the id of the next vertex
        int next = 0;
        
        while (begin != end) {
            //if current vertex hasn't been calculated and distance to start smaller than minumum
            if (state.find(begin->first)->second == false && begin->second < min) {
                min = begin->second;
                // update next
                next = begin->first;
            }
            begin++;
        }
        
        // set to calculated
        state.find(next)->second = true;
        
        // update
        vector<Arc>& currentArcs = vertexs.find(next)->second->getArcs();
        for (unsigned long i = 0; i < currentArcs.size(); i++) {
            // if shorter than previous one, update
            if (state.find(currentArcs[i].getTail())->second == false && min + currentArcs[i].getDistance() < minDistance.find(currentArcs[i].getTail())->second) {
                minDistance.find(currentArcs[i].getTail())->second = min + currentArcs[i].getDistance();
                path.find(currentArcs[i].getTail())->second = next;
            }
        }
    }
}


double Graph::rad(double value) {
    return value * M_PI / 180.0;
}


//Astar
void Graph::Astar(int from, int to, vector<int>& path) {
    vector<Node> openList;
    vector<Node> closeList;
    bool success = false;
    
    Airport *toAirport = airportMap.find(to)->second;
    
    // initialize open list
    // get edges of the fromAirport vertex
    vector<Arc>& fromArcs = vertexs.find(from)->second->getArcs();
    
    for (unsigned long i = 0; i < fromArcs.size(); i++) {
        Node node;
        node.setId(fromArcs[i].getTail());
        node.setParent(from);
        node.setDistance(fromArcs[i].getDistance());
        Airport *cur = airportMap.find(fromArcs[i].getTail())->second;
        //calculate the distance to destination
        //store as the estimated value
        double dis = getDistance(cur->getLatitude(), cur->getLongitude(), toAirport->getLatitude(), toAirport->getLongitude());
        node.setEstiatedValue(dis);
        openList.push_back(node);
    }
    
    //add the start airport to the close list
    Node fromNode;
    fromNode.setId(from);
    fromNode.setParent(0);
    closeList.push_back(fromNode);
    
    // start A* while loop
    while (!openList.empty()) {
        // find the best next node in the open list
        // F(to minimize) = G(distance) + H(estimated value)
        auto begin = openList.begin();
        auto end = openList.end();
        int target = 0;
        int index = 0;
        double min = numeric_limits<double>::max();
        while (begin != end) {
            if (begin->getDistance() + begin->getEstiatedValue() < min) {
                min = begin->getDistance() + begin->getEstiatedValue();
                target = index;
            }
            begin++;
            index++;
        }
        
        // get the next node
        Node node = openList[target];
        openList.erase(openList.begin() + target);
        // add the node to the close list
        closeList.push_back(node);
        
        // if we have arrived, break
        if (node.getId() == to) {
            success = true;
            break;
        }
        
        //traverse all node that current node can arrive
        vector<Arc>& arcs = vertexs.find(node.getId())->second->getArcs();
        
        for (unsigned long i = 0; i < arcs.size(); i++) {
            //check if the node is already in the close list
            bool alreadyExists = false;
            for (unsigned long j = 0; j < closeList.size(); j++) {
                if (closeList[j].getId() == arcs[i].getTail()) {
                    alreadyExists = true;
                    break;
                }
            }
            
            if (alreadyExists) {
                continue;
            }
            
            //check if the node is already in the open list
            alreadyExists = false;
            for (unsigned long j = 0; j < openList.size(); j++) {
                if (openList[j].getId() == arcs[i].getTail()) {
                    alreadyExists = true;
                    //check if it needs update
                    if (arcs[i].getDistance() < openList[j].getDistance()) {
                        openList[i].setDistance(arcs[i].getDistance());
                        openList[i].setParent(node.getId());
                    }
                    break;
                }
            }
            
            if (alreadyExists) {
                continue;
            }

            Node newNode;
            newNode.setId(arcs[i].getTail());
            newNode.setParent(node.getId());
            newNode.setDistance(arcs[i].getDistance());
            Airport *cur = airportMap.find(arcs[i].getTail())->second;
            // calcute the distance to destination
            // store it as estimated value
            double dis = getDistance(cur->getLatitude(), cur->getLongitude(), toAirport->getLatitude(), toAirport->getLongitude());
            newNode.setEstiatedValue(dis);
            openList.push_back(newNode);
        }
    }
    
    // if we have arrived the destination
    if (success) {
        int target = to;
        while (true) {
            if (target == 0) {
                break;
            }
            
            auto begin = closeList.begin();
            auto end = closeList.end();
            while (begin != end) {
                if (begin->getId() == target) {
                    path.push_back(target);
                    target = begin->getParent();
                    closeList.erase(begin);
                    break;
                }
                begin++;
            }
        }
    }
}

double Graph::getDistance(double fromLat,double fromLng,double toLat,double toLng) {
    double EARTH_RADIUS = 6378.137;
    double radLatOne = rad(fromLat);
    double radLatTwo = rad(toLat);
    double a = radLatOne - radLatTwo;
    double b = rad(fromLng) - rad(toLng);
    
    double dis = 2 * asin(sqrt(pow(sin(a/2),2) + cos(radLatOne) * cos(radLatTwo) * pow(sin(b/2),2)));
    dis = dis * EARTH_RADIUS;
    dis = round(dis * 10000) / 10000;
    return dis;
}

set<int> Graph::getBFSset() {
    return BFSset;
}

//test A*
double Graph::getDisTest(int from, int to) {
    Airport* fromAirport = airportMap.find(from)->second;
    Airport* toAirport = airportMap.find(to)->second;
    return getDistance(fromAirport->getLatitude(), fromAirport->getLongitude(), toAirport->getLatitude(), toAirport->getLongitude());
}