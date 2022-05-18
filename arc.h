#pragma once

class Arc {
public:
    /// @param tail destination airport id
    /// @param distance distance of the directed edge
    Arc(int tail, double distance);
    
    /// get information of the destination airport
    int getTail();
    
    // get distance of the directed edge
    double getDistance();
private:
    // desination airportID
    int tail;
    // weight of the directed edge
    double distance;
};


