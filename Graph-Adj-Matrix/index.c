#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

/******************************************************************************
 * @author Jake Brockbank
 * Jan 16th, 2024
 * This tests an adjacency matrix approach to making a graph.
******************************************************************************/
int main()
{
    graph *g1 = createGraph(5);

    addEdge(g1, 0, 1);
    addEdge(g1, 0, 2);
    addEdge(g1, 0, 0);
    addEdge(g1, 1, 2);
    addEdge(g1, 1, 3);
    addEdge(g1, 3, 4);
    addEdge(g1, 4, 1);
    addEdge(g1, 4, 0);

    printGraph(g1);
    destroyGraph(g1);

    return 0;
}