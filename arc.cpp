#include "arc.h"
#include <iostream>

Arc::Arc(int tail, double distance) {
    this->tail = tail;
    this->distance = distance;
}


int Arc::getTail() {
    return tail;
}

double Arc::getDistance() {
    return distance;
}
