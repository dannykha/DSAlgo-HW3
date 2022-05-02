// ------------------------------------------------ graphl.h ------------------------------------------------------
// Danny Kha
// CSS 343
// Professor Dong Si
// Creation Date: 4/26/22
// Date of Last Modification: 5/7/22
// --------------------------------------------------------------------------------------------------------------------
// Purpose - The purpose of graphl.h is to declare the functions implemented in graphl.cpp.
// graphl is a class that reads in a text file, builds a graph, and preforms depth first search 
// on the built graph from the inptuted text file. 
// -------------------------------------------------------------------------------------------------------------------- 
// Notes - graphl.h is the declaration of the declared class for graphl.cpp.
// all the inputs are assumed valid.
// iostream, iomanip, and limits.h were used to implement input, input manipulation, and integer maxs.
// -------------------------------------------------------------------------------------------------------------------- 

#pragma once

#include "nodedata.h" 
#include <iostream> // input output include
#include <iomanip> // manipulating the input and output
#include "limits.h" // used for integer max

class GraphL
{
    public:
        GraphL();

        ~GraphL();

        void buildGraph(ifstream &inFile);

        void displayGraph() const;

        void depthFirstSearch();
    
    private:
        static const int MAXNODES = 100;

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

        void destroyGraph();

        void depthFirstSearchHelper(int v);

        GraphNode nodeArray[MAXNODES];

        int size;
};