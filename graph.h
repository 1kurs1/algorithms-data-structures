#pragma once

#define GRAPH_IMPLEMENTATION

#include "pch.h"
#include "mathematics.h"
#include "queue.h"

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

void graph_bsf(graph_t* g, int start){
    bool* visited = calloc(g->size, sizeof(bool));
    queue_t* q = queue_alloc();

    visited[start] = true;
    queue_enqueue(q, start);
    while(!queue_is_empty(q)){
        int node = queue_dequeue(q);
        printf("%c ", node + 65);
        
        for(size_t i = 0; i < g->size; i++){
            if(matrix_at(g->nodes, node, i) && !visited[i]){
                visited[i] = true;
                queue_enqueue(q, i);
            }
        }
    }
    printf("\n");

    queue_free(q);
    free(visited);
}

void graph_dfs_inner(graph_t* g, int node, bool* visited){
    visited[node] = true;
    printf("%c ", node+65);
    for(size_t i = 0; i < g->size; i++){
        if(matrix_at(g->nodes, node, i) && !visited[i])
            graph_dfs_inner(g, i, visited);
    }
}

void graph_dfs(graph_t* g, int start){
    bool* visited = calloc(g->size, sizeof(bool));
    graph_dfs_inner(g, start, visited);
    printf("\n");
    free(visited);
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
    printf("adjacency matrix:\n");
    printf("   ");

    int c = 65;
    for(size_t i = 0; i < g->size; i++) printf("%c ", c++);
    printf("\n");
   
    c = 65;
    for(size_t i = 0; i < g->nodes->rows; i++){
        for(size_t j = 0; j < g->nodes->columns; j++){
            if(j == 0) printf("%c ", c++);
            printf("%d ", matrix_at(g->nodes, i, j));
            if(j == g->nodes->columns - 1) printf("\n");
        }
    }
}