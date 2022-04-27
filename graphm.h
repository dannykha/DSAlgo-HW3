#pragma once

#include "nodedata.h"
#include <iostream>


using namespace std;

class GraphM
{
public:
    GraphM();

    void buildGraph(ifstream &inFile);

    bool insertEdge(int &from, int &to, int &weight);

    bool removeEdge(int &from, int &to);

    void findShortestPath();

    void displayAll() const;

    void display(const int &from, const int &to) const;



private:
    struct TableType
    {
        bool visited;
        int dist;
        int path;
    };

    const static int MAXNODES = 101;

    NodeData data[MAXNODES];

    int C[MAXNODES][MAXNODES];

    int size;

    TableType T[MAXNODES][MAXNODES];

    void printPath(int &from, int &to) const;

    void printPathDisplay(int &from, int &to) const;
};