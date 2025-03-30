#pragma once

#define GRAPH_IMPLEMENTATION

#include "pch.h"
#include "mathematics.h"

typedef struct graph{
    matrix_t* nodes;
    size_t size;
} graph_t;

graph_t* graph_alloc(size_t size){
    graph_t* res = (graph_t*)malloc(sizeof(graph_t));
    res->size = size;
    res->nodes = matrix_alloc(res->size, res->size);
    return res;
}

void graph_add_edge(graph_t* g, size_t u, size_t v){
    if(u >= g->size || v >= g->size){
        fprintf(stderr, "invalid node index\n");
        return;
    }

    matrix_at(g->nodes, u, v) = 1;
    matrix_at(g->nodes, v, u) = 1;
}

void graph_remove_edge(graph_t* g, size_t u, size_t v){
    if(u >= g->size || v >= g->size){
        fprintf(stderr, "invalid node index\n");
        return;
    }

    matrix_at(g->nodes, u, v) = 0;
    matrix_at(g->nodes, v, u) = 0;
}

bool graph_has_edge(graph_t* g, size_t u, size_t v){
    if(u >= g->size || v >= g->size) return false;
    return matrix_at(g->nodes, u, v) == 1;
}

void graph_free(graph_t* g){
    matrix_free(g->nodes);
    free(g);
}

void graph_print(graph_t* g){
    printf("matrix of nodes:\n");
    matrix_print(g->nodes);
}