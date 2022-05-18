#pragma once
#include <string>
#include <queue>
#include <fstream>
#include <vector>
#include "Graph.h"
// #include < >
// #include < >
// #include < >

#include //insert the airport data h file here

class BFS{
    public:
        BFS(const string &fileAP, const string &fileR);    //constructor
                                                                    //change the items in the function. anytime you...
                                                                    //see "something", it's a placeholder that is to be replaced.
        vector<string> BFS_twoAirports(int start, int dest);


    private:
            //don't know what to put here yet 🤔

}