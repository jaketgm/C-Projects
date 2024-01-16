#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

typedef struct Graph 
{
    int numOfNodes;
    bool **edges;
} graph;

/******************************************************************************
 * Method: destroyGraph: 
 * 
 * - This method methodically release the memory allocated to the graph data 
 * structure, thereby preventing memory leaks. Initially, it checks if the edges 
 * pointer within the graph is non-NULL, indicating that memory was allocated. 
 * If not NULL, the function proceeds to iterate through each 'row' of the 
 * graph's adjacency matrix, which is represented as a 2D array, and frees 
 * each row. These rows are essentially arrays themselves, holding boolean 
 * values that indicate the presence of edges between nodes in the graph. 
 * Once all rows are freed, the function then releases the memory allocated 
 * to the edges array, which contains pointers to these rows. In the final 
 * step, the memory allocated for the graph structure itself is freed. 
 *
 * Input: graph *g.
 *
 * Output: Freed graph.
 *
******************************************************************************/
void destroyGraph(graph *g) 
{
    if (g->edges != NULL)
    {
        for (int i = 0; i < g->numOfNodes; i++)
        {
            free(g->edges[i]); // Free each row of the adjacency matrix
        }
        free(g->edges); // Then free the array of pointers
    }
    free(g); // Finally, free the graph structure
}

/******************************************************************************
 * Method: createGraph: 
 * 
 * - This method dynamically allocates memory for a new graph structure and 
 * initialize its adjacency matrix. It starts by allocating memory for a 
 * graph structure, and if successful, it proceeds to set the number of 
 * nodes (numOfNodes) in the graph. Next, the function allocates memory 
 * for an array of pointer-to-boolean (bool*) variables, with each pointer 
 * representing a row in the graph's adjacency matrix. This matrix is used 
 * to store boolean values indicating the presence or absence of edges 
 * between nodes. If the allocation for the edges array fails, the function 
 * frees the already allocated graph structure and returns NULL, 
 * indicating a failure in memory allocation. The function then iterates 
 * over the number of nodes, allocating memory for each row in the 
 * adjacency matrix and checking for successful allocation. If any 
 * row allocation fails, the previously allocated memory for the graph 
 * and its components is freed using the destroyGraph function to prevent
 * memory leaks, and NULL is returned. On successful allocation and 
 * initialization of the entire adjacency matrix, a pointer to the 
 * newly created graph is returned. 
 *
 * Input: int numOfNodes.
 *
 * Output: Graph g.
 *
******************************************************************************/
graph *createGraph(int numOfNodes)
{
    graph *g = (graph*) malloc(sizeof(graph));
    if (g == NULL)
        return NULL;

    g->numOfNodes = numOfNodes;
    g->edges = (bool**) calloc(numOfNodes, sizeof(bool*));
    if (g->edges == NULL)
    {
        free(g);
        return NULL;
    }

    for (int i = 0; i < numOfNodes; i++)
    {
        g->edges[i] = (bool*) calloc(numOfNodes, sizeof(bool));
        if (g->edges[i] == NULL)
        {
            destroyGraph(g);
            return NULL;
        }
    }
    return g;    
}

/******************************************************************************
 * Method: printGraph: 
 * 
 * - This method visualizes the structure of a graph in a simple text-based 
 * format, specifically in the form of a directed graph notation. It begins 
 * by printing the opening brace of a directed graph declaration, digraph 
 * {. The function then iterates over each node (from) in the graph, and 
 * for each node, it iterates over all possible destination nodes (to). 
 * Within this nested loop, the function checks if an edge exists between 
 * the from node and the to node by examining the boolean value in the 
 * graph's adjacency matrix (g->edges[from][to]). If an edge exists 
 * (indicated by a true value), the function prints a line representing 
 * this edge in the format "from -> to;", showing a directed edge from 
 * the from node to the to node. After iterating through all possible
 * edges in the graph, the function prints a closing brace, }, to denote 
 * the end of the graph.
 *
 * Input: graph *g.
 *
 * Output: None.
 *
******************************************************************************/
void printGraph(graph *g)
{
    printf("digraph {\n");
    int from, to;
    for (from = 0; from < g->numOfNodes; from++)
    {
        for (to = 0; to < g->numOfNodes; to++)
        {
            if (g->edges[from][to])
                printf("%d -> %d;\n", from, to);
        }
    }
    printf("}\n");
}

/******************************************************************************
 * Method: hasEdge: 
 * 
 * - A query function for a graph data structure, designed to check if an edge 
 * exists between two specified nodes in the graph. It takes three 
 * parameters: a pointer to a graph (g), and two unsigned integers 
 * (fromNode and toNode) representing the source and destination nodes, 
 * respectively. The function begins with a series of assertions to ensure 
 * the validity of its input: it checks that the graph pointer is not 
 * NULL and that both the source and destination node indices are within 
 * the bounds of the graph's node count. These assertions help to prevent 
 * out-of-bounds access and ensure the function operates on a valid graph. 
 * After passing these checks, the function returns the boolean value at 
 * the specified position in the graph's adjacency matrix (g->edges
 * [fromNode][toNode]). This value indicates whether an edge exists (true) 
 * or does not exist (false) between the fromNode and toNode.
 *
 * Input: graph *g, unsigned int fromNode, unsigned int toNode.
 *
 * Output: boolean.
 *
******************************************************************************/
bool hasEdge(graph *g, unsigned int fromNode, unsigned int toNode)
{
    assert(g != NULL);
    assert(fromNode < g->numOfNodes);
    assert(toNode < g->numOfNodes);

    return g->edges[fromNode][toNode];
}

/******************************************************************************
 * Method: addEdge: 
 * 
 * - This method adds a directed edge to a graph data structure. This 
 * function takes three parameters: a pointer to a graph (g), and two 
 * unsigned integers (fromNode and toNode) that represent the source 
 * and destination nodes of the edge being added. Initially, the 
 * function employs assertions to ensure that the graph pointer is not 
 * NULL and that the node indices provided are within the valid range 
 * of the graph's nodes. These checks are crucial for maintaining the 
 * integrity of the function and preventing invalid memory access. Once 
 * the input validity is confirmed, the function uses the hasEdge method to 
 * check if an edge already exists between fromNode and toNode. If such an 
 * edge exists, the function returns false, indicating that adding a 
 * duplicate edge is not permissible. If the edge does not exist, the 
 * function sets the corresponding value in the graph's adjacency matrix 
 * (g->edges[fromNode][toNode]) to true, effectively adding the edge to the 
 * graph. The function then returns true to indicate that the edge has been 
 * successfully added.
 *
 * Input: graph *g, unsigned int fromNode, unsigned int toNode.
 *
 * Output: boolean.
 *
******************************************************************************/
bool addEdge(graph *g, unsigned int fromNode, unsigned int toNode)
{
    assert(g != NULL);
    assert(fromNode < g->numOfNodes);
    assert(toNode < g->numOfNodes);
    
    if (hasEdge(g, fromNode, toNode))
        return false;
    
    g->edges[fromNode][toNode] = true;
    return true;
}