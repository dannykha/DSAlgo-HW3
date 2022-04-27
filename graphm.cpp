#include "graphm.h"


GraphM::GraphM()
{
    size = 0;

    for (int i = 1; i < MAXNODES; i++)
    {
        for (int j = 0; j < MAXNODES; j++)
        {
            C[i][j] = 0;

            T[i][j].visited = false;
            T[i][j].path = 0;
            T[i][j].dist = 0;
        }
    }
}

void GraphM::buildGraph(ifstream &inFile)
{
    inFile >> size;
    string nodeName = "";
    getline(inFile, nodeName);

    for (int i = 1; i <= size; i++)
    {
        data[i].setData(inFile);
    }

    int from, to, dist;

    while (inFile >> from >> to >> dist)
    {
        if (from ==0)
        {
            break;
        }
        C[from][to] = dist;
    }
}

bool GraphM::insertEdge(int &from, int &to, int &weight)
{

}

bool GraphM::removeEdge(int &from, int &to)
{

}

void GraphM::findShortestPath()
{

}

void GraphM::displayAll() const
{

}

void GraphM::display(const int &from, const int &to) const
{

}

void GraphM::printPath(int &from, int &to) const
{

}

void GraphM::printPathDisplay(int &from, int &to) const
{

}