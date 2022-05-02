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
    // Default Constructor
    GraphM();
    
    // Graph builder with input stream from data file and uses an adjancey matrix
    void buildGraph(ifstream &inFile);

    // Function that inserts edges between from and to nodes with weights
    bool insertEdge(int from, int to, int weight);

    // Function that froms an edge between from and to nodes
    bool removeEdge(int from, int to);

    // Function that implements Dijkstra's shortest path algorithm
    void findShortestPath();

    // Function that uses couts to display the algorithm is working
    void displayAll() const;

    // Function taht uses couts to display the path between nodes
    void display(const int from, const int to) const;



private:
    struct TableType
    {
        bool visited; // whether node has been visite
        int dist; // shortest distance from source known so far
        int path; // previous node in path of min dist
    };

    // Constant that sets the array size to a maximum value
    const static int MAXNODES = 101; 

    NodeData data[MAXNODES]; // data for graph nodes

    int C[MAXNODES][MAXNODES]; // cost array, the adjancy matrix
 
    int size; // number of nodes in the graph

    TableType T[MAXNODES][MAXNODES]; // stores visited, distance, path

    // Helper function of findShortestPath that initializes everything to not visited yet
    void initialize();

    // Helper function that finds the next smallest next node in the table
    int findNext(TableType temp[]);	

    // Helper function that finds the path between from and to nodes
    void findPath(int from, int to) const;

    // Helper function that displays the nodes data between from and to nodes
    void findData(int from, int to) const;
};