#include <iostream>
#include "graph.h"
#include <vector>
#include "airport.h"
#include "vertex.h"
#include "arc.h"
#include <fstream>
#include <string>
#include "node.h"
#include <algorithm>

using namespace std;
int main() {
    //intialize graph and parse data
    Graph graph;
    graph.initAirports("data/airports.dat");
    graph.initGraph("data/routes.dat");
    vector<int> vertexs;
    //traverse the graph with given start airport's ID
    graph.BFS(1, vertexs);
    ofstream outFile("output/BFS.txt");
    for (const auto &e : vertexs) outFile << e << "->";
    //travese and show other properties
    // by modifing the getters
    ofstream out("output/BFS_byIATA.txt");
    for (const auto &e : vertexs) {
        Airport* a = graph.getAirportById(e);
        out << a->getIata() << "->";
    }
    std::cout << "BFS starts from 1 information is storede in the output folder" << std::endl;
    std::cout << "if you want to see traversals that start from another airport, you can modify in the main.cpp" << std::endl;
    std::cout << "\n" << std::endl;

    //algorithms need BFS as prerequisite
    //CHECK HERE
    if(vertexs.size() == 0) {
        return 0;
    }
    bool next = true;
    while(next) {
        std::cout << "press 1 to search for Dijkstra's shortest path between two airports" << std::endl;
        std::cout << "press 2 to search for A* best path between two airports" << std::endl;

        int algorithm;
        cin >> algorithm;
        switch (algorithm)
        {
            case 1: {
                std::cout << "ready for Dijkstra's shortest path" << std::endl;
                std::cout << "which airport would you like to set as the start?" << std::endl;
                int source = 0;
                vector<int> vertices;
                while(true) {
                    cin >> source;
                    graph.BFS(source, vertices);
                    if(graph.getVertexMap().find(source) != graph.getVertexMap().end() && !vertices.empty()) {
                        std::cout << graph.getAirportById(source)->getIata() << " has been set to your start point" << "\n";
                        break;
                    }
                    std::cout << "your input is not valid, please enter another one" << std::endl;   
                }
                std::cout << "a moment..." << std::endl; 
                map<int, int> path;
                graph.shortestPath(vertices, source, path);
                std::cout << "which airport would you like to set as the destination?" << std::endl;
                int destination = 0;
                while(true) {
                    std::cin >> destination;
                    auto vbegin = vertices.begin();
                    auto vend = vertices.end();
                    if(std::find(vbegin, vend, destination) != vertices.end()) {
                        std::cout << graph.getAirportById(destination)->getIata() << " has been set to your destination point" << std::endl;
                        break;
                    }
                    std::cout << "your input is not valid, please enter another one" << std::endl;   
                }
                std::cout << "---- path begin---" << std::endl;
                std::cout << "the shortest path from " << graph.getAirportById(source)->getIata() << " to " << graph.getAirportById(destination)->getIcao() << " is" << std::endl;
                std::cout << graph.getAirportById(destination)->getIata() << "<-";
                int pre = destination;
                while (true) {
                    pre = path.find(pre)->second;
                        if (pre == 0) {
                            std::cout << "" << "\n";
                            std::cout << "---- path end---" << std::endl;
                            break;
                        }
                    std::cout << graph.getAirportById(pre)->getIata() << "<-";
                }
                std::cout << "\n" << std::endl;
                next = false;
                break;
            }
            case 2: {
                std::cout << "ready for A* path seaching" << std::endl;
                vector<int> aStarPath;
                std::cout << "which airport would you like to set as the start?" << std::endl;
                int source = 0;
                vector<int> vertices;
                while(true) {
                    cin >> source;
                    graph.BFS(source, vertices);
                    if(graph.getVertexMap().find(source) != graph.getVertexMap().end() && !vertices.empty()) {
                        std::cout << graph.getAirportById(source)->getIata() << " has been set to your start point" << "\n";
                        break;
                    }
                    std::cout << "your input is not valid, please enter another one" << std::endl;   
                }
                std::cout << "a moment..." << std::endl;
                map<int, int> path;
                graph.shortestPath(vertices, source, path);
                std::cout << "which airport would you like to set as the destination?" << std::endl; 
                int destination = 0;
                while(true) {
                    std::cin >> destination;
                    auto vbegin = vertices.begin();
                    auto vend = vertices.end();
                    if(std::find(vbegin, vend, destination) != vertices.end()) {
                        std::cout << graph.getAirportById(destination)->getIata() << " has been set to your destination point" << std::endl;
                        break;
                    }
                    std::cout << "your input is not valid, please enter another one" << std::endl;   
                }
                std::cout << "please allow a moment for the A* to run..." << std::endl;
                graph.Astar(source, destination, aStarPath);
                std::cout << "---- A* path begin---" << std::endl;
                std::cout << "the A* path from " << graph.getAirportById(source)->getIata() << " to " << graph.getAirportById(destination)->getIata() << " is" << std::endl;
                for (unsigned long i = 0; i < aStarPath.size(); i++) {
                    std::cout << graph.getAirportById(aStarPath[i])->getIata() << "<-";
                }
                std::cout << "" << "\n";
                std::cout << "---- A* path end---" << std::endl;
                next = false;
                break;
            }
        }
    }
    return 0;
}
