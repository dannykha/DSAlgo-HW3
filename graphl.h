#pragma once

#include <iostream>
#include "limits.h"
#include "iomanip"
#include "nodedata.h"

class GraphL
{
    public:
        // Default constructor
        GraphL();

        // Destructor
        ~GraphL();

        // Function that builds a graph based on input file
        void buildGraph(ifstream &inFile);

        // Function that utizlies depth first search to go through the graph
        void depthFirstSearch();

        // Function that diplays the graph
        void displayGraph() const;
    
    private:
        // Constant max value of nodes in the array
        static const int MAXNODES = 101;

        struct EdgeNode;      // forward reference for the compiler

        struct GraphNode {    // structs used for simplicity, use classes if desired
            EdgeNode* edgeHead; // head of the list of edges
            NodeData* data;     // data information about each node
            bool visited;                
        };
        struct EdgeNode {
            int adjGraphNode;  // subscript of the adjacent graph node
            EdgeNode* nextEdge;
        };

        // Declaring an array of graphnodes
        GraphNode nodeArray[MAXNODES];

        // Declaring a variable for the size of the nodes in the graph
        int size;

        // Helper function that helps destroy the graph
        void destroyGraph();

        // Helper function to preform depth first search
        void depthFirstSearchHelper(int v);
};