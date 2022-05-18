# CS 225 Fall 2020 Final Project
Contributor: Tianxin Zhou

## how to run our project
1. download our code and cd into the project directory
2. make main to check the main functionality of the code
3. ./main and follow the instruction in the terminal to see the outputs
4. BFS traversal outputs are located in the output folder
5. make test to run test cases
6. ./test to see the test result

## major file descriptions:
- airport.cpp/h: every airport stores the information that is given in airports.dat
- vertex.cpp/h: the class stores the airport ID and directed edges of the airports that will be eventually used for our graph
- arc.cpp/h: where we define directed route edge that contains the information of its source airport and destination airport
- graph.cpp/h: where we initialize our graph. Pointers of Airports and vertices are mapped to the airport ID.
- main.cpp: where users can run and check our code's output. 
- node.cpp/node: used for A* search algorithm

most of the results will be shown in the terminal, while given the large output of the BFS traversal, we decided to store it in the .txt files that your can find in the output folder. To select the appropriate input, you could search the airport's name in the airport.dat file, and take its unique airport ID (the first column) as the int input.

## data
our project was implemented based on the openflights dataset where you can find here -> https://openflights.org/data.html. Specifically, to build our graph and run the three algorithms, we looked at the airports.dat and routes.dat (located in the data folder). You can download other data files on this website to further your implementations. you can run the code and check the outputs in the output folder.

## Major function code: all located in Graph.cpp/h
**Breadth First Search Traversal** :The BFS traversal code is located in Graph.cpp. In the Graph class, we mappeed the Airport with its unique ID given in airport.dat. All information of a specific airport including all its incident edges (routes) could be retrived by the gettered defined in airport.cpp/h.
**Dijkstra's algorithm**: based on the BFS traversal, we further implemented the Dijkstra's algorithm to find the shortest path between two airports.  Example usage could be find in the main.cpp.
**A* search**: Based on the Dijkstra's shortest path, we implemented another path finding algorithm. The estimated value of the function was set to be the distance from the next adjacent node to the destination node. it can be changed to your preferred property in the graph.cpp. 

## Test cases:
all test cases are stored in test.cpp in the test folder. 
the test cases can be run with:
```
{
    make test
    ./test
}
```

to generate your own test cases, we provided various getters that allow you to access the attributes of each class. Example test cases could be found in the tests folder, possible additional test cases are mentioned in the comment.
