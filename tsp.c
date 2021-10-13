#include "graph.h"
#include "path.h"
#include "stack.h"
#include "vertices.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define OPTIONS "hvui:o:"
#define BLOCK   4096

int recursive_calls = 1;

void dfs(
    Graph *G, uint32_t v, Path *curr, Path *shortest, char *cities[], FILE *outfile, bool verbose) {
    graph_mark_visited(G, v); //mark visited
    if (path_length(curr) < path_length(shortest) || path_length(shortest) == 0) {
        for (uint32_t w = 0; w < graph_vertices(G);
             w += 1) { //loop thru all edges (v,w) with w unvisited
            if (graph_has_edge(G, v, w) && !graph_visited(G, w)) {
                path_push_vertex(curr, w, G);
                recursive_calls += 1;
                dfs(G, w, curr, shortest, cities, outfile, verbose); //recursively call dfs
                uint32_t dummyvar; // dummy variable to store popped vertex
                path_pop_vertex(curr, &dummyvar, G);
            }
        }
    }
    // if theres no where to go, check if its a hamiltonian path
    // loop that checks number of visited vertices in graph

    if ((path_vertices(curr) + 1) == graph_vertices(G) && graph_has_edge(G, v, START_VERTEX)) {
        // if (vertices in path+1) == (total vertices) because origin not added to path at beginning
        // and there is an edge to beginning
        // then it is a hamiltonian path and we need to add connection to origin at end

        path_push_vertex(curr, START_VERTEX, G);

        if (path_length(curr) < path_length(shortest) || path_length(shortest) == 0) {
            path_copy(shortest, curr);
            if (verbose) {
                path_print(shortest, outfile, cities);
            }
        }
        uint32_t dummyvar2;
        path_pop_vertex(curr, &dummyvar2, G);
    }

    // we have now printed the hamiltonian path if verbose is enabled
    // if not the current path has been copied to shortest if it is shorter than shortest
    graph_mark_unvisited(G, v);
}

int main(int argc, char **argv) {
    int opt = 0;
    bool undirected = false;
    bool verbose = false;
    FILE *infile = stdin;
    FILE *outfile = stdout;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h':
            //pring help message
            fprintf(outfile, "SYNOPSIS\n\tTraveling Salesman Problem using DFS.\n\n");
            fprintf(outfile, "USAGE\n\t./tsp [-u] [-v] [-h] [-i infile] [-o outfile]\n\n");
            fprintf(outfile,
                "OPTIONS\n\t-u\t\t\tUse undirected graph.\n\t-v\t\t\tEnable verbose printing.");
            fprintf(outfile, "\n\t-h\t\t\tProgram usage and help.\n\t-i infile\t\t");
            fprintf(outfile, "Input containing graph (default: stdin)\n\t-o outfile\t\t");
            fprintf(outfile, "Output of computed path (default: stdout)\n");
            return 0;
            break;
        case 'v': verbose = true; break;
        case 'u': undirected = true; break;
        case 'i':
            //specifies input file path
            infile = fopen(optarg, "r");
            if (infile == NULL) {
                printf("Error, invalid file or something.\n");
                return 0;
            }
            break;
        case 'o':
            //specifies output file path
            outfile = fopen(optarg, "w");
            break;
        default: break;
        }
    }
    int vertices;
    fscanf(infile, "%d\n", &vertices); //scan file for vertices
    if (vertices > VERTICES) {
        fprintf(outfile, "Error too many vertices.\n");
        exit(1);
    }

    char *cities[vertices];
    char buffer[BLOCK];
    for (int i = 0; i < vertices; i += 1) {
        fgets(buffer, BLOCK, infile); //get cities from input file
        buffer[strcspn(buffer, "\n")] = 0;
        cities[i] = strdup(buffer);
    }

    //print cities for testing only
    //    for (int i = 0; i < vertices; i += 1) {
    //        printf("%s\n", cities[i]);
    //    }

    Graph *G = graph_create(vertices, undirected);

    int c;
    int i, j, k;
    while ((c = fscanf(infile, "%d %d %d\n", &i, &j, &k)) != EOF) {
        //print i,j,k for testing only
        //printf("%d\n", c);
        //printf("i= %d, j= %d, k= %d\n", i, j, k);
        if (!graph_add_edge(G, i, j, k) || c != 3) {
            fprintf(outfile, "Error: malformed edge.\n");
            exit(1);
        }
    }

    Path *current = path_create();
    Path *shortest = path_create();

    dfs(G, START_VERTEX, current, shortest, cities, outfile, verbose);
    if (path_length(shortest) == 0) {
        fprintf(outfile, "There's nowhere to go.\n");
    } else {
        path_print(shortest, outfile, cities);
        fprintf(outfile, "Total recursive calls: %d\n", recursive_calls);
    }

    fclose(infile);
    fclose(outfile);
    path_delete(&shortest);
    path_delete(&current);
    graph_delete(&G);
    for (int i = 0; i < vertices; i += 1) {
        free(cities[i]);
    }

    return 0;
}
