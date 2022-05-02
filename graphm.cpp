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


// GOOD
GraphM::GraphM()
{
    this->size = 0;

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
}

// GOOD ish
void GraphM::buildGraph(ifstream &inFile)
{
    inFile >> this->size;
    string temp = "";
    getline(inFile, temp);

    for (int i = 1; i <= size; i++)
    {
        data[i].setData(inFile);
    }

    int from;
    int to;
    int weight;
    while (inFile >> from >> to >> weight)
    {
        if (from == 0)
        {
            break;
        }
       this->C[from][to] = weight;
    }
}

// GOOD
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
}

// GOOD
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
}

// GOOD
void GraphM::findShortestPath()
{
	int v = 0;
	int counter = 1;

    initialize();

	for (int source = 1; source <= size; source++)
	{
		T[source][source].dist = 0;

		while (counter != size)
		{
			v = findNext(T[source]);

			T[source][v].visited = true;

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
		counter = 1;
	}
}

// GOOD
void GraphM::initialize()
{
	for (int i = 1; i <= size; i++)
	{
		for (int j = 1; j <= size; j++)
		{
			T[i][j].visited = false;
		}
	}
}

// GOOD
int GraphM::findNext(TableType temp[])
{
	int nextNode = 1;
	int min = INT_MAX;

	for (int i = 1; i <= size; i++)
	{
		if (temp[i].dist < min && !(temp[i].visited))
		{
			nextNode = i;
			min = temp[i].dist;
		}
	}
	return nextNode;
}

// need work?
void GraphM::displayAll() const
{
    cout << "Description" << setw(20) << "From Node" << setw(12) << "To Node";
	cout << setw(14) << "Dijkstra's" << setw(8) << "Path" << endl;

	for (int i = 1; i <= size; i++)
	{
		cout << this->data[i] << endl;
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
				cout << setw(12) << "----" << endl;
			}
		}
	}
}

// need work?
void GraphM::display(int from, int to) const
{
    if ((from > size || from < 1) || (to > size || to < 1))	
	{
		cout << setw(7) << from << setw(9) << to;
		cout << setw(11) << "----" << endl;
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
		cout << setw(11) << "----" << endl;
	}
	cout << endl;
}

// need work
void GraphM::findPath(int from, int to) const
{
    if (T[from][to].dist == INT_MAX)
    {
        return; 
    }

    if (from == to)
    {
        cout << to << " ";  

        return;
    }

    int pathData = to; 
    findPath(from, to = T[from][to].path);

    cout << pathData << " ";   
}

// need work?
void GraphM::findData(int from, int to) const
{
    if (T[from][to].dist == INT_MAX)
    {
        return; 
    }

    if (from == to)
    {
        cout << data[to] << endl;   

        return;
    }

    int nodeData = to;

    findData(from, to = T[from][to].path); 

    cout << data[nodeData] << endl << endl;    
}