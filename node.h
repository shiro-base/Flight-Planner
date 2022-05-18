#pragma once
class Node {
    
public:
    void setId(int id);
    void setParent(int parent);
    void setDistance(double distance);
    void setEstiatedValue(double estimatedValue);
    int getId();
    int getParent();
    double getDistance();
    double getEstiatedValue();
    
private:
    int id;
    int parent;
    double distance;
    double estimatedValue;
};


