#ifndef _GRAPH_H
#define _GRAPH_H

#include <stdbool.h>

typedef struct {
        int n_nodes;
        bool **adjacency;
} Graph;

/* Create an undirected graph with nodes numbered 0 ... n - 1 */
Graph *graph_create(int, int, int [][2]);

/* Free the memory used by a graph */
void graph_free(Graph *);

/* Get a copy of a graph */
Graph *graph_copy(Graph *);

/* Returns whether a given element is part of or connected to a cycle */
bool graph_cycle_elem(Graph *g, int, int, bool *);
/* Returns whether the given graph contains a cycle of elements */
bool graph_cycle(Graph *g);

/* Display the graph nodes and their adjacencies */
void graph_show_adj(Graph *, const char *, const char *);

#endif
