#include "graph.h"

#include "vertices.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Graph {
    uint32_t vertices; // number of vertices
    bool undirected; // undirected graph?
    bool visited[VERTICES]; // where have we gone?
    uint32_t matrix[VERTICES][VERTICES]; // adjacency matrix
} Graph;

Graph *graph_create(uint32_t vertices, bool undirected) {
    Graph *G = (Graph *) malloc(sizeof(Graph));
    G->vertices = vertices; // set number of vertics
    G->undirected = undirected; // set if undirectd or not
    for (int i = 0; i < VERTICES; i += 1) { // set visited to false
        G->visited[i] = false;
    }
    for (int j = 0; j < VERTICES; j += 1) { // set matrix to 0
        for (int k = 0; k < VERTICES; k += 1) {
            G->matrix[j][k] = 0;
        }
    }
    return G;
}

void graph_delete(Graph **G) {
    if (*G) {
        free(*G);
        *G = NULL;
    }
    return;
}

uint32_t graph_vertices(Graph *G) {
    return (G->vertices);
}

bool graph_add_edge(Graph *G, uint32_t i, uint32_t j, uint32_t k) {
    if (i > 25 || j > 25) {
        return false;
    }
    if (G->undirected) {
        G->matrix[i][j] = k;
        G->matrix[j][i] = k;
    } else {
        G->matrix[i][j] = k;
    }
    return true;
}

bool graph_has_edge(Graph *G, uint32_t i, uint32_t j) {
    if (i > 25 || j > 25) {
        return false;
    }
    if (G->matrix[i][j] != 0) {
        return true;
    } else {
        return false;
    }
}

uint32_t graph_edge_weight(Graph *G, uint32_t i, uint32_t j) {
    if (i > 25 || j > 25 || !graph_has_edge(G, i, j)) {
        return 0;
    }
    return (G->matrix[i][j]);
}

bool graph_visited(Graph *G, uint32_t v) {
    return (G->visited[v]);
}

void graph_mark_visited(Graph *G, uint32_t v) {
    if (v <= 25) {
        G->visited[v] = true;
    }
}

void graph_mark_unvisited(Graph *G, uint32_t v) {
    if (v <= 25) {
        G->visited[v] = false;
    }
}

void graph_print(Graph *G) {
    printf("vertices: %" PRIu32 "\n", G->vertices);
    return;
}
