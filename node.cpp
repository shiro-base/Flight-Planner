#include "node.h"

void Node::setId(int id) {
    this->id = id;
}

void Node::setParent(int parent) {
    this->parent = parent;
}

void Node::setDistance(double distance) {
    this->distance = distance;
}

void Node::setEstiatedValue(double estimatedValue) {
    this->estimatedValue = estimatedValue;
}

int Node::getId() {
    return id;
}

int Node::getParent() {
    return parent;
}

double Node::getDistance() {
    return distance;
}

double Node::getEstiatedValue() {
    return estimatedValue;
}

