// ------------------------------------------------ graphm.cpp ------------------------------------------------------
// Danny Kha
// CSS 343
// Professor Dong Si
// Creation Date: 4/26/22
// Date of Last Modification: 5/7/22
// --------------------------------------------------------------------------------------------------------------------
// Purpose - The purpose of graphm is to implement Dijkstra shortest path algorithm upon a graph matrix
// that is inputted from text files that will be read in.
// -------------------------------------------------------------------------------------------------------------------- 
// Notes - all inputs are assumed valid
// graphm.cpp is the implementation of the declared class from graphm.h. 
// iostream, iomanip, and limits.h were used to implement input, input manipulation, and integer maxs.
// -------------------------------------------------------------------------------------------------------------------- 

#include "graphm.h"

// ------------------------------------Constructor-----------------------------------------------  
// Description: Constructor for an empty matrix table and initializes all the values
// ----------------------------------------------------------------------------------------------
GraphM::GraphM()
{   
    // set size to 0
    this->size = 0;

    // double for loop for the matrix table and setting them to max value (infinity) and visited false
    for (int i = 1; i < MAXNODES; i++)
    {
        for (int j = 1; j < MAXNODES; j++)
        {
            C[i][j] = INT_MAX;
            T[i][j].visited = false;
            T[i][j].dist = INT_MAX;
            T[i][j].path = 0;
        }
    }
} // end of constructor

// ------------------------------------buildGraph()-----------------------------------------------  
// Description: Builds a graph from a text file input and sets the weight of each node
// ---------------------------------------------------------------------------------------------------  
void GraphM::buildGraph(ifstream &inFile)
{
    int from, to, weight; // declaring from, to and weight for nodes
    string line; // declaring a string variable line
    inFile >> this->size; // setting the size
    getline(inFile, line); // getting the first line of the file

    // for loop that sets the data from the file
    for (int i = 1; i <= size; i++)
    {
        data[i].setData(inFile);
    }

    // while infile has the next three inputs of from to and weight of that node
    while (inFile >> from >> to >> weight)
    {
        // if statement breaks when the node is at 0
        if (from == 0)
        {
            break; 
        }
       this->C[from][to] = weight; // setting the C table up
    }
} // end of buildGraph()

// ------------------------------------insertEdge()-----------------------------------------
// Description: Creates and inserts an edge between two nodes and the specificed weight of that edge
// ---------------------------------------------------------------------------------------------------  
bool GraphM::insertEdge(int from, int to, int weight)
{
    if (from > this->size || from < 1)
    {
        return false;
    }
    else if (to > this->size || to < 1)
    {
        return false;
    }
    else if (from == to && weight != 0)
    {
        return false;
    }
    else if (weight < 0)
    {
        return false;
    }
    else 
    {
        this->C[from][to] = weight;
        return true;
    }
} // end of insertEdge()

// ------------------------------------removeEdge()-----------------------------------  
// Description: Removes an edge from a given from and to nodes
// ---------------------------------------------------------------------------------------------------  
bool GraphM::removeEdge(const int from, const int to)
{
    if (from < 1 || from > this->size)
    {
        return false;
    }
    else if (to < 1 || to > this->size)
    {
        return false;
    }
    else if (this->C[from][to] == INT_MAX)
    {
        return false;
    }
    else
    {
        this->C[from][to] = INT_MAX;
        return true;
    } 
} // end of removeEdge()

// ------------------------------------findShortestPath()-----------------------------------  
// Description: Function to find the shortest path between nodes using Dijkstra's algorithm throughout
// the entire graph.
// ---------------------------------------------------------------------------------------------------  
void GraphM::findShortestPath()
{
	int v = 0;
	int counter = 1;

    // first initializing the graph to make evrything not visited
    initialize();

    // first loop sets the distance of the source to 0
	for (int source = 1; source <= size; source++)
	{
		T[source][source].dist = 0;

        // main loop
		while (counter != size)
		{
			v = findNext(T[source]); // searching to find that source node

			T[source][v].visited = true; // source node

            // for loop that goes through everything and does the Dijkastra algorithm
            // uses "v" that found the source node location
			for (int i = 1; i <= size; i++)
			{
				if (!T[source][i].visited && C[v][i] != INT_MAX)
				{
					if (T[source][i].dist > T[source][v].dist + C[v][i])
					{
						T[source][i].dist = T[source][v].dist + C[v][i];
						T[source][i].path = v;
					}
				}
			}
			counter++;
		}
        counter = 1; // resets the counter back to 1
	}
} // end of findShortestPath

// ------------------------------------initialize()-----------------------------------  
// Description: Helper function to findShortestPath() by initializing everything to not being visited yet.
// ---------------------------------------------------------------------------------------------------  
void GraphM::initialize()
{
    // intiailizes everything in the T table to false
	for (int i = 1; i <= size; i++)
	{
		for (int j = 1; j <= size; j++)
		{
			T[i][j].visited = false;
		}
	}
} // end of initialize()

// ------------------------------------findNext()-----------------------------------  
// Description: Used to find the next node in the graph and returns the next node once found.
// ---------------------------------------------------------------------------------------------------  
int GraphM::findNext(TableType temp[])
{
	int nextNode = 1;
	int min = INT_MAX;

    // for loop that searches for the next node
	for (int i = 1; i <= size; i++)
	{
		if (temp[i].dist < min && !(temp[i].visited))
		{
			nextNode = i;
			min = temp[i].dist;
		}
	}
	return nextNode;
} // end of findNext()

// ------------------------------------displayAll()-----------------------------------  
// Description: Used to display all the inforamtion with couts and displays the shortest path between each node
// ---------------------------------------------------------------------------------------------------  
void GraphM::displayAll() const
{
    cout << "Description" << setw(20) << "From Node" << setw(12) << "To Node";
	cout << setw(14) << "Dijkstra's" << setw(8) << "Path" << endl;

	for (int i = 1; i <= size; i++)
	{
		cout << this->data[i];
        cout << endl;
		for (int j = 1; j <= size; j++)
		{
			if (T[i][j].dist > 0 && T[i][j].dist < INT_MAX)
			{
                cout << setw(27) << i << setw(12) << j;
				cout << setw(12) << T[i][j].dist << setw(10);
				findPath(i, j);
				cout << endl;
			}
			else if (i != j)
			{
                cout << setw(27) << i << setw(12) << j;
				cout << setw(12) << "----";
                cout << endl;
			}
		}
	}
} // end of displayAll()

// ------------------------------------display()-----------------------------------  
// Description: Uses couts to display the shortest distance with info of the path from and to nodes
// ---------------------------------------------------------------------------------------------------  
void GraphM::display(int from, int to) const
{
    if ((from > size || from < 1) || (to > size || to < 1))	
	{
		cout << setw(7) << from << setw(9) << to;
		cout << setw(11) << "----";
        cout << endl;
	}
	else if (T[from][to].dist != INT_MAX)
	{
		cout << setw(7) << from << setw(9) << to;
		cout << setw(11) << T[from][to].dist << setw(15);

		findPath(from, to);
		cout << endl;
		findData(from, to);
	}
	else
	{
		cout << setw(7) << from << setw(9) << to;							
		cout << setw(11) << "----";
        cout << endl;
	}
	cout << endl;
} // end of display()

// ------------------------------------findPath()-----------------------------------  
// Description: Helper function to find paths between from and to nodes, used in displayAll and display
// ---------------------------------------------------------------------------------------------------  
void GraphM::findPath(int from, int to) const
{
    if (T[from][to].dist == INT_MAX)
    {
        return; 
    }
    else if (from == to)
    {
        cout << to << " ";  
        return;
    }
    else 
    {
        int pathData = to; 
        findPath(from, to = T[from][to].path);
        cout << pathData << " ";   
    }
} // end of findPath()

// ------------------------------------findData()-----------------------------------  
// Description: Helper function to find the specific data between the from and to nodes. 
// Used in display()
// ---------------------------------------------------------------------------------------------------  
void GraphM::findData(int from, int to) const
{
    if (T[from][to].dist == INT_MAX)
    {
        return; 
    } 
    else if (from == to)
    {
        cout << data[to] << endl;   
        return;
    }
    else
    {
        int nodeData = to;
        findData(from, to = T[from][to].path); 
        cout << data[nodeData];
        cout << endl << endl;
    }
} // end of findData()