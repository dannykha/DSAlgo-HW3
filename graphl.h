// ------------------------------------------------ graphl.h ------------------------------------------------------
// Danny Kha
// CSS 343
// Professor Dong Si
// Creation Date: 4/26/22
// Date of Last Modification: 5/7/22
// --------------------------------------------------------------------------------------------------------------------
// Purpose - The purpose of graphl is to display graph information using adjancey list of graphs.
// Reading in an input from a text file can be done and then depth first search is implemented.
// -------------------------------------------------------------------------------------------------------------------- 
// Notes - All inputs are assumed valid.
// graphl.h is the decleration of all the functions that are implemented in graphl.cpp.
// iostream, iomanip, and limits.h were used to implement input, input manipulation, and integer maxs.
// -------------------------------------------------------------------------------------------------------------------- 

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