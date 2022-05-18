#pragma once

#include "Route.h"
#include "Airport.h"
#include "Graph.h"
#include <cmath>
#include <iostream>
#include <limits>
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Dijkstra
{
public:
  Dijkstra::Dijkstra(Graph graph);
  
  double getDistance(const Airport& a1, const Airport& a2);
  
  vector<Airport> shortestPath(int source, int destination)

  double distanceTravelled(int source, int destination);

  void DijkstraSSSP(int source);
  
private:
  
  Graph graph;
  vector<double> distance;
  vector<int> previous;
};