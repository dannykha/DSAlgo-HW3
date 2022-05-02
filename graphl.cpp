// ------------------------------------------------ graphl.cpp ------------------------------------------------------
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
// graphl.cpp is the implementation of the declared class from graphl.h. 
// iostream, iomanip, and limits.h were used to implement input, input manipulation, and integer maxs.
// -------------------------------------------------------------------------------------------------------------------- 

#include "graphl.h"

// ------------------------------------Constructor-----------------------------------  
// Description: Constructor for a GraphL matrix and sets the array of the graph to nullptr
// ---------------------------------------------------------------------------------------------------  
GraphL::GraphL()
{
    this->size = 0;

    for (int i = 0; i < MAXNODES; i++)
    {
        nodeArray[i].visited = false;
        nodeArray[i].edgeHead = nullptr;
        nodeArray[i].data = nullptr;
    }
} // end of constructor

// ------------------------------------Destructor-----------------------------------  
// Description: Destructor for the graphl, destroys everything!
// ---------------------------------------------------------------------------------------------------  
GraphL::~GraphL()
{
    destroyGraph();
} // end of destructor

// ------------------------------------destroyGraph()-----------------------------------  
// Description: Helper function to the destructor.
// Legit destroys everything.
// ---------------------------------------------------------------------------------------------------  
void GraphL::destroyGraph()
{
    // loops through the entire array
    // then does checks and deletes and setting to nullptrs etc.
    for (int i = 0; i <= size; i++)
    {
        nodeArray[i].visited = false; 
        if (nodeArray[i].data != nullptr)
        {
            delete nodeArray[i].data;
            nodeArray[i].data = nullptr;
        }
        if (nodeArray[i].edgeHead != nullptr)
        {
            EdgeNode* temp = nodeArray[i].edgeHead;

            while (temp != nullptr)
            {
                nodeArray[i].edgeHead = nodeArray[i].edgeHead->nextEdge;
                delete temp;
                temp = nullptr;
                temp = nodeArray[i].edgeHead;
            }
        }
    }
} // end of destroyGraph()

// ------------------------------------buildGraph()-----------------------------------  
// Description: Builds graph using input stream from an input file with an adjacency list
// ---------------------------------------------------------------------------------------------------  
void GraphL::buildGraph(ifstream &inFile)
{
    int from, to; // declaring from and to node variables
    string line; // declaring a string variable line
    inFile >> this->size; // setting the size
    getline(inFile, line); // getting the first line of the file

    // Setting the edge names
    for (int i = 1; i <= size; i++)
    {
        getline(inFile, line);
        NodeData *temp = new NodeData(line);
        nodeArray[i].data = temp;
        temp = nullptr;
    }

    // Filling up the adjacency list
	while (inFile >> from >> to)
	{
		if (from == 0)
		{
			break;
		}
        // Setting the first node
		if (nodeArray[from].edgeHead == nullptr) 
		{
            EdgeNode *newData = new EdgeNode;
		    newData->adjGraphNode = to;
		    newData->nextEdge = nullptr;
			nodeArray[from].edgeHead = newData;
		}
        // Any extra nodes are set in the list
		else
		{
            EdgeNode *newData= new EdgeNode;
            newData->adjGraphNode = to;
			newData->nextEdge = nodeArray[from].edgeHead;
			nodeArray[from].edgeHead = newData;
		}
	}
} // end of buildGraph()

// ------------------------------------depthFirstSearch()-----------------------------------  
// Description: Preforms depth first search on the graph and then calls the helper to display
// the nodes in depth first order
// ---------------------------------------------------------------------------------------------------  
void GraphL::depthFirstSearch()
{
    cout << endl;
    cout << "Depth-fisrt ordering:";  

    // Looping through the entire graph
    for (int i = 1; i <= size; i++)
    {
        // checking as long as the node hasn't been visited yet, continue
        if (!nodeArray[i].visited)  
        {
            depthFirstSearchHelper(i); // helper call
            cout << endl; 
        }
    }
    cout << endl;
} // end of depthFirstSearch()

// ------------------------------------depthFirstSearchHelper-----------------------------------  
// Description: Helper function to depthFirstSearch that recursively finds the nodes with depth
// first search order
// ---------------------------------------------------------------------------------------------------  
void GraphL::depthFirstSearchHelper(int v)
{
    // printing the first node and setting the first node to visited, then moves on to next
    cout << setw(2) << v;  
    nodeArray[v].visited = true;   
    EdgeNode* curr = nodeArray[v].edgeHead;

    // Recursively going until the end of the adjacency list
    while (curr != nullptr) 
    {
        if (!(nodeArray[curr->adjGraphNode].visited)) 
        {
            depthFirstSearchHelper(curr->adjGraphNode); // recurisve call  
        }
        // Moving pointer to the next on the adjacency list
        curr = curr->nextEdge;   
    }
} // end of depthFirstSearchHelper()

// ------------------------------------displayGraph()-----------------------------------  
// Description: Function that displays the graph including the edge of the nodes in the graph
// ---------------------------------------------------------------------------------------------------  
void GraphL::displayGraph() const
{
    cout << "Graph:";
    cout << endl;

    // Looping through the enitre array
    for (int i = 1; i <= size; i++) 
    {
        // printing all the information in order
        cout << "Node" << i << "      " << *nodeArray[i].data;
        cout << endl << endl;

        EdgeNode* curr = nodeArray[i].edgeHead; 

        // loop to check in the adjacency list
        while (curr != nullptr) 
        {
            // printing information in order
            cout << setw(7) << "edge " << i << setw(2) << curr->adjGraphNode;
            cout << endl;
            curr = curr->nextEdge;  // moving the pointer
        }
    }
} // end of displayGraph()