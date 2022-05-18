#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

#include "../cs225/catch/catch.hpp"
#include "../airport.h"
#include "../graph.h"
#include "../vertex.h"
#include "../arc.h"

TEST_CASE("Store Airports Correctly") {
	Graph g;
    g.initAirports("data/airports.dat");
    g.initGraph("data/routes.dat");
	map<int, Airport*> airports = g.getAirportMap();

	REQUIRE(airports.size() == 7676);   
	
	// test whether the information of a specific airport is correct.
	// 3406: Shanghai Pudong International Airport
	REQUIRE(airports[3406]->getAirportId() == 3406);
	REQUIRE(airports[3406]->getName() == "Shanghai Pudong International Airport");
	REQUIRE(airports[3406]->getIata() == "PVG");
	REQUIRE(airports[3406]->getIcao() == "ZSPD");

	// invalid airport
	// ID 2946 is not defined in the airport.dat
	REQUIRE(airports.find(2946) == airports.end());
}

TEST_CASE("Graph initialization") {
	Graph g;
    g.initAirports("data/airports.dat");
    g.initGraph("data/routes.dat");
	map<int, Vertex*> vertices = g.getVertexMap();
	//EDGE CASE:
	//airport that mentioned in route.dat but not recorded in airport
	//is not stored into vertexes
	REQUIRE(vertices.find(7167) == vertices.end());   
	//reading route infomation of a vertex;
	//airport 1941 is the source airport of 10 routes(manually checked)
	vector<Arc> arcs = vertices[1941]->getArcs();
	REQUIRE(arcs.size() == 10);
	//first route that starts from 1941 has 3533 as destination airport(manually checked)
	REQUIRE(arcs[0].getTail() == 3533);  
}

TEST_CASE("BFS traversal") {
	Graph g;
    g.initAirports("data/airports.dat");
    g.initGraph("data/routes.dat");
	vector<int> bfs1;
	vector<int> bfs2;
	vector<int> bfs3;
	//since we implement the BFS within one single function in graph.cpp
	//we expect that no matter where we start to travese, we will traverse all
	g.BFS(3, bfs1);
	g.BFS(1941,bfs2);
	g.BFS(3406,bfs3);
	REQUIRE(bfs1.size() == bfs2.size());
	REQUIRE(bfs3.size() == bfs2.size());
}

TEST_CASE("test Dijkstra") {
	Graph g;
    g.initAirports("data/airports.dat");
    g.initGraph("data/routes.dat");
	vector<int> vertices;
	map<int, int> path;
	g.BFS(1, vertices);
	g.shortestPath(vertices, 1234, path);
	vector<int> shortestPath = {1229, 1234};
	vector<int> ourShortestPath1;
	ourShortestPath1.push_back(1229);
	//manually checked that there are only routes from 1234 to 1229
	int pre = 1229;
	while (true)
	{
		pre = path.find(pre)->second;
		if(pre == 0) {
			break;
		}
		ourShortestPath1.push_back(pre);
	}
	REQUIRE(ourShortestPath1 == shortestPath);
	REQUIRE(ourShortestPath1.size() == 2);

	//shortest path 2
	//two paths from 11051 to 4284(1 of 5 world smallests aiport)
	//1:11051->3714->4284->5730->4284
	//2:11051->3714->4284
	//manually checked
	vector<int> shortestPath2 = {4284, 3714, 11051};
	vector<int> ourShortestPath2;
	map<int, int> path2;
	g.shortestPath(vertices, 11051, path2);
	ourShortestPath2.push_back(4284);
	int pre2 = 4284;
	while (true)
	{
		pre2 = path2.find(pre2)->second;
		if(pre2 == 0) {
			break;
		}
		ourShortestPath2.push_back(pre2);
	}
	REQUIRE(ourShortestPath2 == shortestPath2);
	REQUIRE(ourShortestPath2.size() == 3);
}

TEST_CASE("test A* search") {
	Graph g;
    g.initAirports("data/airports.dat");
    g.initGraph("data/routes.dat");
	vector<int> vertices;
	vector<int> path;

	int start = 1;
	int dest = 90;
	//run BFS
	g.BFS(start, vertices);

	//get A* path
	g.Astar(start, dest, path);
	map<int, int> dij;
	vector<int> dijPath;

	//get dijkstra path
	g.shortestPath(vertices, start, dij);
	int pre = dest;
	dijPath.push_back(pre);
	while(true) {
		pre = dij.find(pre)->second;
		if(pre == 0) {
			break;
		}
		dijPath.push_back(pre);
	}
	//reverse the path to get the right order
	reverse(dijPath.begin(), dijPath.end());
	reverse(path.begin(), path.end());
	//A* path choose to go NRT instead of NAN since NRT's distance to dest is strictly shorter than NAN
	//check how A* pick the next node differently from Dijkstra here
	//we mainly test how the A* handle the estimated value, which contributes to the difference to Dijkstra's here
	//user can also construct a smaller graph with longtitude and latitude for airports and distances for edges to test the A*
	REQUIRE(g.getDisTest(path[2], dest) < g.getDisTest(dijPath[2], dest));
	
	//A* always take the next node with smallest dis to destination
	//given our heuristic function, A* at most of the time is shorter or equal long to Dijkstra's path
	//considering our dataset contains about 67,000 routes, the case that our heuristic function lead the path
	//to somewhere that is close to the destination but has no route lead to it is relatively few
	//so we decided to keep the test below for the case 1->90, which we manually checked
	//Dijkstra's traversed the graph to get the real shortest path in distance 
	//but A* takes the nodes' distance to destination into consideration
	REQUIRE(dijPath.size() >= path.size());
	//not necessarily true for all case but for 1->90
	for(unsigned long i = 0; i < path.size(); i++) {
		double A_dis = g.getDisTest(path[i], dest);
		double dij_dis = g.getDisTest(dijPath[i],dest);
		REQUIRE(A_dis <= dij_dis);
	}

}