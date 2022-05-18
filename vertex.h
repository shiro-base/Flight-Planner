#pragma once
#include <vector>
#include <iostream>
#include "arc.h"

using namespace std;

class Vertex {
public:
    //construct an airport with airport id
    Vertex(int id);
    
    //add directed edge
    void addArc(Arc arc);
    
    
    /// get id of the airport
    int getId();
    
    /// get ALL directed edges of the current vertex
    vector<Arc>& getArcs();
    
private:
    int id;
    // all possible routes from the start airport
    vector<Arc> arcs;
};


