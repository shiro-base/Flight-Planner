#include "vertex.h"

Vertex::Vertex(int id) {
    this->id = id;
}

void Vertex::addArc(Arc arc) {
    arcs.push_back(arc);
}

int Vertex::getId() {
    return id;
}

vector<Arc>& Vertex::getArcs() {
    return arcs;
}
