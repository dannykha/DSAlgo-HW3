#pragma once

#include "nodedata.h"
#include <iostream>
#include <iomanip>
#include "limits.h"


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