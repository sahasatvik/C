#include <stdlib.h>
#include <stdio.h>
#include "Graph.h"

int main(int argc, const char *argv[]) {
        int edges[][2] = {
                {0, 1},
                {0, 2},
                {0, 3},
                {2, 3},
                {3, 1}
        };
        Graph *g = graph_create(4, 5, edges);
        graph_show(g, "%2d -> ", "%2d ");
        graph_free(g);

        return 0;
}
