#ifndef _GRAPH_H
#define _GRAPH_H

typedef struct {
        unsigned int n_nodes;
        unsigned char **adjacency;
} Graph;

/* Create an undirected graph with nodes numbered 0 ... n - 1 */
Graph *graph_create(unsigned int, unsigned int, int [][2]);

/* Free the memory used by a graph */
void graph_free(Graph *);

/* Get a copy of a graph */
Graph *graph_copy(Graph *);

/* Display the graph nodes and their adjacencies */
void graph_show(Graph *, char *, char *);

#endif
