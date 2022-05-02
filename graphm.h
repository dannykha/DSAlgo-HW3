// ------------------------------------------------ graphm.h ------------------------------------------------------
// Danny Kha
// CSS 343
// Professor Dong Si
// Creation Date: 4/26/22
// Date of Last Modification: 5/7/22
// --------------------------------------------------------------------------------------------------------------------
// Purpose - The purpose of graphm.h is to declare the functions used in graphm.cpp.
// graphm is a class that uses dijkstra's shortest path algorithm to find the shortest path between nodes in a graph.
// Once the shortest path is found starting at a single node, the algorithm stops and outputs the optimal path.
// -------------------------------------------------------------------------------------------------------------------- 
// Notes - graphm.h is the declaration of the declared class for graphm.cpp.
// all the inputs are assumed valid.
// iostream, iomanip, and limits.h were used to implement input, input manipulation, and integer maxs.
// -------------------------------------------------------------------------------------------------------------------- 

#pragma once

#include "nodedata.h" 
#include <iostream> // input output include
#include <iomanip> // manipulating the input and output
#include "limits.h" // used for integer max


using namespace std;

class GraphM
{
public:
    GraphM();

    void buildGraph(ifstream &inFile);

    bool insertEdge(int from, int to, int weight);

    bool removeEdge(int from, int to);

    void findShortestPath();

    void displayAll() const;

    void display(const int from, const int to) const;



private:
    struct TableType
    {
        bool visited; // whether node has been visite
        int dist; // shortest distance from source known so far
        int path; // previous node in path of min dist
    };

    const static int MAXNODES = 101; 

    NodeData data[MAXNODES]; // data for graph nodes

    int C[MAXNODES][MAXNODES]; // cost array, the adjancy matrix
 
    int size; // number of nodes in the graph

    TableType T[MAXNODES][MAXNODES]; // stores visited, distance, path

    void initialize();

    int findNext(TableType temp[]);	

    void findPath(int from, int to) const;

    void findData(int from, int to) const;
};