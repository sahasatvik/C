#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "Graph.h"

Graph *graph_create(int n_nodes, int n_edges, int edges[][2]) {
        Graph *g = malloc(sizeof(Graph));
        g->n_nodes = n_nodes;
        g->adjacency = calloc(n_nodes, sizeof(bool *));
        for (int i = 0; i < n_nodes; i++)
                g->adjacency[i] = calloc(n_nodes, sizeof(bool));
        /* For every pair of nodes constituting an edge, mark them adjacent to one another */
        for (int i = 0; i < n_edges; i++) {
                g->adjacency[edges[i][0]][edges[i][1]] = true;
                g->adjacency[edges[i][1]][edges[i][0]] = true;
        }
        return g;
}

void graph_free(Graph *g) {
        if (g == NULL)
                return;
        for (int i = 0; i < g->n_nodes; i++)
                free(g->adjacency[i]);
        free(g->adjacency);
        free(g);
}

Graph *graph_copy(Graph *g) {
        if (g == NULL)
                return NULL;
        Graph *gc = graph_create(g->n_nodes, 0, NULL);
        for (int i = 0; i < g->n_nodes; i++)
                for(int j = 0; j < g->n_nodes; j++)
                        gc->adjacency[i][j] = g->adjacency[i][j];
        return gc;
}

bool graph_cycle_elem(Graph *g, int current, int previous, bool *visited) {
        /* Mark the current element as visited */
        visited[current] = true;
        for (int i = 0; i < g->n_nodes; i++) {
                /* Ignore the current node and the previous node */
                if (i == current || i == previous)
                        continue;
                /* Ignore nodes not adjacent to the current one */
                if (!g->adjacency[current][i])
                        continue;
                /* If the new node is visited, but not the one visited just prior,
                   we have found a cycle */
                if (visited[i])
                        return true;
                /* We have an unvisited node not completing a cycle. Recursively check
                   whether it completes a cycle. */
                if (graph_cycle_elem(g, i, current, visited))
                        return true;
        }
        return false;
}

bool graph_cycle(Graph *g) {
        bool *visited = calloc(g->n_nodes, sizeof(bool));
        for (int i = 0; i < g->n_nodes; i++)
                /* Ignore already visited nodes */
                if (!visited[i] && graph_cycle_elem(g, i, -1, visited)) {
                        free(visited);
                        return true;
                }
        free(visited);
        return false;
}

void graph_show_adj(Graph *g, char *format_node, char *format_others) {
        if (g == NULL) {
                printf("NULL\n");
                return;
        }
        for (int i = 0; i < g->n_nodes; i++) {
                printf(format_node, i);
                for (int j = 0; j < g->n_nodes; j++)
                        if (g->adjacency[i][j])
                                printf(format_others, j);
                printf("\n");
        }
}
