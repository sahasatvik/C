#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "Graph.h"

int main(int argc, const char *argv[]) {
        int n_nodes = 9;
        int n_edges = 8;
        int edges[][2] = {
                {0, 1},
                {1, 2},
                {2, 3},
                {3, 1},
                {4, 5},
                {5, 6},
                {6, 4},
                {7, 8}
        };
        Graph *g = graph_create(n_nodes, n_edges, edges);

        printf("Adjacent nodes in graph :\n");
        graph_show_adj(g, "%2d -> ", "%2d ");

        for (int start = 0; start < n_nodes; start++) {
                bool *visited = calloc(n_nodes, sizeof(bool));
                int cycle = graph_cycle_elem(g, start, -1, visited);
                printf("\nCycle with %2d : %d, ", start, cycle);
                printf("Visited nodes : ");
                for (int i = 0; i < n_nodes; i++)
                        if (visited[i])
                                printf("%2d ", i);
                free(visited);
        }

        printf("\n\nAny cycle : %d\n", graph_cycle(g));

        graph_free(g);
        return 0;
}
