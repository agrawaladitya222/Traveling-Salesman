#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Stack {
    uint32_t top; //index of next empty slot
    uint32_t capacity; //number of items that can be pushed
    uint32_t *items; //array of items, each of type int64_t
} Stack;

Stack *stack_create(uint32_t capacity) { //code from Eugene's section/Prof Long in assignment pdf
    Stack *s = (Stack *) malloc(sizeof(Stack));
    if (s) {
        s->top = 0;
        s->capacity = capacity;
        s->items = (uint32_t *) calloc(capacity, sizeof(uint32_t));
        if (!s->items) {
            free(s);
            s = NULL;
        }
    }
    return s;
}

void stack_delete(Stack **s) { //code from prof Long in assignment pdf
    if (*s && (*s)->items) {
        free((*s)->items);
        free(*s);
        *s = NULL;
    }
    return;
}

bool stack_empty(Stack *s) {
    return (s->top == 0);
}

bool stack_full(Stack *s) { //code from Eugene's section
    return s->top == s->capacity;
}

uint32_t stack_size(Stack *s) {
    return (s->top);
}

bool stack_push(Stack *s, uint32_t x) { //code from Eugene's section
    if (stack_full(s)) {
        return false;
    }
    s->items[s->top] = x;
    s->top += 1;
    return true;
}

bool stack_pop(Stack *s, uint32_t *x) { //modified code from Eugene's section
    if (stack_empty(s)) {
        return false;
    }
    s->top -= 1;
    *x = s->items[s->top];
    return true;
}

bool stack_peek(Stack *s, uint32_t *x) {
    if (stack_empty(s)) {
        return false;
    }
    *x = s->items[s->top - 1];
    return true;
}

void stack_copy(Stack *dst, Stack *src) {
    dst->top = src->top;
    for (uint32_t i = 0; i < src->top; i += 1) {
        uint32_t temp = src->items[i];
        dst->items[i] = temp;
    }
}

void stack_print(Stack *s, FILE *outfile, char *cities[]) { // code from prof Long in asgn4.pdf
    for (uint32_t i = 0; i < s->top; i += 1) {
        fprintf(outfile, "%s", cities[s->items[i]]);
        if (i + 1 != s->top) {
            fprintf(outfile, " -> ");
        }
    }
    fprintf(outfile, "\n");
}
