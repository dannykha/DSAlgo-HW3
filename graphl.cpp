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

GraphL::GraphL()
{
    this->size = 0;

    for (int i = 0; i < MAXNODES; i++)
    {
        nodeArray[i].visited = false;
        nodeArray[i].edgeHead = nullptr;
        nodeArray[i].data = nullptr;
    }
}

GraphL::~GraphL()
{
    destroyGraph();
}

void GraphL::destroyGraph()
{
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
}

void GraphL::buildGraph(ifstream &inFile)
{
    inFile >> this->size;
    string name = "";
    getline(inFile, name);

    for (int i = 1; i <= size; i++)
    {
        getline(inFile, name);
        NodeData *temp = new NodeData(name);
        nodeArray[i].data = temp;
        temp = nullptr;
    }

    	int from, to;

	while (inFile >> from >> to)
	{
		if (from == 0)
		{
			break;
		}

		if (nodeArray[from].edgeHead == nullptr)
		{
            EdgeNode *newData = new EdgeNode;
		    newData->adjGraphNode = to;
		    newData->nextEdge = nullptr;
			nodeArray[from].edgeHead = newData;
		}
		else
		{
            EdgeNode *newData= new EdgeNode;
            newData->adjGraphNode = to;
			newData->nextEdge = nodeArray[from].edgeHead;
			nodeArray[from].edgeHead = newData;
		}
	}
}

void GraphL::depthFirstSearch()
{
    cout << endl << "Depth-fisrt ordering:";  

    for (int v = 1; v <= size; ++v)
    {
        if (!nodeArray[v].visited)  
        {
            depthFirstSearchHelper(v); 
            cout << endl; 
        }
    }
    cout << endl;
}

void GraphL::depthFirstSearchHelper(int v)
{
    cout << setw(2) << v;  
    nodeArray[v].visited = true;   
    EdgeNode* curr = nodeArray[v].edgeHead;

    while (curr != nullptr) 
    {
        if (!(nodeArray[curr->adjGraphNode].visited)) 
        {
            depthFirstSearchHelper(curr->adjGraphNode);  
        }

        curr = curr->nextEdge;   
    }
}

void GraphL::displayGraph() const
{
    cout << "Graph:" << endl;

    for (int i = 1; i <= size; i++) 
    {
        cout << "Node" << i << "      " << *nodeArray[i].data << endl << endl;

        EdgeNode* curr = nodeArray[i].edgeHead; 

        while (curr != nullptr) 
        {
            cout << setw(7) << "edge " << i << setw(2) << curr->adjGraphNode << endl;
            curr = curr->nextEdge; 
        }
    }
}