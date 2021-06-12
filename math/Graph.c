#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "Graph.h"

Graph *graph_create(unsigned int n_nodes, unsigned int n_edges, int edges[][2]) {
        Graph *g = malloc(sizeof(Graph));
        g->n_nodes = n_nodes;
        g->adjacency = calloc(n_nodes, sizeof(bool *));
        for (unsigned int i = 0; i < n_nodes; i++)
                g->adjacency[i] = calloc(n_nodes, sizeof(bool));
        /* For every pair of nodes constituting an edge, mark them adjacent to one another */
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

int graph_cycle_elem(Graph *g, unsigned int current, unsigned int previous, bool *visited) {
        /* Mark the current element as visited */
        visited[current] = 1;
        for (unsigned int i = 0; i < g->n_nodes; i++) {
                /* Ignore the current node and the previous node */
                if (i == current || i == previous)
                        continue;
                /* Ignore nodes not adjacent to the current one */
                if (!g->adjacency[current][i])
                        continue;
                /* If the new node is visited, but not the one visited just prior,
                   we have found a cycle */
                if (visited[i])
                        return 1;
                /* We have an unvisited node not completing a cycle. Recursively check
                   whether it completes a cycle. */
                if (graph_cycle_elem(g, i, current, visited))
                        return 1;
        }
        return 0;
}

int graph_cycle(Graph *g) {
        bool *visited = calloc(g->n_nodes, sizeof(bool));
        for (unsigned int i = 0; i < g->n_nodes; i++)
                /* Ignore already visited nodes */
                if (!visited[i] && graph_cycle_elem(g, i, -1, visited)) {
                        free(visited);
                        return 1;
                }
        free(visited);
        return 0;
}

void graph_show_adj(Graph *g, char *format_node, char *format_others) {
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
