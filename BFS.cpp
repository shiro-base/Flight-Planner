#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "BFS.h" //yet to be made atm...
#include "Graph.H"

using namespace std;
                BFS:BFS(const string &fileAP, const string &fileR){
                    string A, R;
                    A = fileAP;
                    R = fileR;
                    Graph::buildGraph(A, R);
                }
vector<string>  BFS::BFS_twoAirports(int start, int dest){ //input is gonna be airport id from 1 to 14110
    vector<string> path;
    queue<int> bfsQ;
    int curr = start;
    int totalAirports = 14110;

    vector<bool> visited(totalAirports);

    bfsQ.push(curr);

    for (int i=0; i<totalAirports; i++ ){
        visited[i] = false;
    }

    queue<int> pathQ;
    pathQ.push(curr);

    while(!pathQ.empty()){
        curr = bfsQ.front();
        for ( ){    //this part doesn't have the necessary data to be written. need to...
                    //...iterate through all the possible departures from that airport...
                    //...without visiting an airport twice.
            if(!visited[something.somethingElse]){ //placeholder EVENTUALLY FIX !!!!!!!!!!!!!
                auto nextAirport = something.somethingElse
                bfsQ.push(nextAirport);
                pathQ.push(nextAirport);
                visited[nextAirport] = true;

            }
            if (curr == dest) break;
        }
        bfsQ.pop();

    }
    if (curr != dest) return // empty string. blanking on how to do this

    while(!pathQ.empty()){
        int bruh = pathQ.front();
        path.push_back(something); //push airport name to vector. just need a way to get airport name of the #"curr" airport
        pathQ.pop();
    }
    return path;

        
}