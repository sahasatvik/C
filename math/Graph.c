#include <stdlib.h>
#include <stdio.h>
#include "Graph.h"

Graph *graph_create(unsigned int n_nodes, unsigned int n_edges, int edges[][2]) {
        Graph *g = malloc(sizeof(Graph));
        g->n_nodes = n_nodes;
        g->adjacency = calloc(n_nodes, sizeof(unsigned char *));
        for (unsigned int i = 0; i < n_nodes; i++)
                g->adjacency[i] = calloc(n_nodes, sizeof(unsigned char));
        for (unsigned int i = 0; i < n_edges; i++) {
                g->adjacency[edges[i][0]][edges[i][1]] = 1;
                g->adjacency[edges[i][1]][edges[i][0]] = 1;
        }
        return g;
}

void graph_free(Graph *g) {
        if (g == NULL)
                return;
        for (unsigned int i = 0; i < g->n_nodes; i++)
                free(g->adjacency[i]);
        free(g->adjacency);
        free(g);
}

Graph *graph_copy(Graph *g) {
        if (g == NULL)
                return NULL;
        Graph *gc = graph_create(g->n_nodes, 0, NULL);
        for (unsigned int i = 0; i < g->n_nodes; i++)
                for(unsigned int j = 0; j < g->n_nodes; j++)
                        gc->adjacency[i][j] = g->adjacency[i][j];
        return gc;
}

void graph_show(Graph *g, char *format_node, char *format_others) {
        if (g == NULL) {
                printf("NULL\n");
                return;
        }
        for (unsigned int i = 0; i < g->n_nodes; i++) {
                printf(format_node, i);
                for (unsigned int j = 0; j < g->n_nodes; j++)
                        if (g->adjacency[i][j])
                                printf(format_others, j);
                printf("\n");
        }
}
