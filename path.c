#include "path.h"

#include "graph.h"
#include "stack.h"
#include "vertices.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct Path {
    Stack *vertices; // vertices comprising the path
    uint32_t length; // total length of the path
} Path;

Path *path_create(void) {
    Path *p = (Path *) malloc(sizeof(Path));
    p->vertices = stack_create(VERTICES);
    p->length = 0;
    return p;
}

void path_delete(Path **p) {
    if (*p) {
        stack_delete(&(*p)->vertices);
        free(*p);
        *p = NULL;
    }
}

bool path_push_vertex(Path *p, uint32_t v, Graph *G) {
    uint32_t x; //variable to store top of stack
    if (stack_empty(p->vertices)) {
        if (!stack_push(p->vertices, v)) {
            return false;
        }
        p->length += graph_edge_weight(G, START_VERTEX, v); //if stack empty add from origin
    } else {
        stack_peek(p->vertices, &x);
        if (!stack_push(p->vertices, v)) {
            return false;
        }
        p->length += graph_edge_weight(G, x, v);
    }

    return true;
}

bool path_pop_vertex(Path *p, uint32_t *v, Graph *G) {
    uint32_t x; // variable to hold vertex before popped vertex
    if (stack_pop(p->vertices, v)) {
        if (stack_empty(p->vertices)) {
            p->length -= graph_edge_weight(
                G, START_VERTEX, *v); //if last on stack subtract edge from origin
        } else {
            stack_peek(p->vertices, &x);
            p->length -= graph_edge_weight(G, x, *v);
        }
    } else {
        return false;
    }

    return true;
}

uint32_t path_vertices(Path *p) {
    return stack_size(p->vertices);
}

uint32_t path_length(Path *p) {
    return p->length;
}

void path_copy(Path *dst, Path *src) {
    dst->length = src->length;
    stack_copy(dst->vertices, src->vertices);
    return;
}

void path_print(Path *p, FILE *outfile, char *cities[]) {
    fprintf(outfile, "Path length: %" PRIu32 "\n", path_length(p));
    fprintf(outfile, "Path: %s -> ", cities[START_VERTEX]);
    stack_print(p->vertices, outfile, cities);
    return;
}
