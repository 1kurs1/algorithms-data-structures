#pragma once

#define BINARY_SEARCH_TREE_IMPLEMENTATION

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define QUEUE_BST_INIT_CAP 256
#define QUEUE_BST_IMPLEMENTATION

typedef struct bst_node_t {
    int value;
    struct bst_node_t* left;
    struct bst_node_t* right;
} bst_node_t;

typedef struct bst_queue {
    size_t count;
    size_t capacity;
    bst_node_t** items;
    int front;
    int rear;
} bst_queue_t;

bst_queue_t* bst_queue_alloc();
void bst_queue_enqueue(bst_queue_t* queue, bst_node_t* item);
bool bst_queue_is_empty(bst_queue_t* queue);
bst_node_t* bst_queue_dequeue(bst_queue_t* queue);
void bst_queue_print(bst_queue_t* queue);
void bst_queue_free(bst_queue_t* queue);

#ifdef QUEUE_BST_IMPLEMENTATION
bst_queue_t* bst_queue_alloc(){
    bst_queue_t* queue = (bst_queue_t*)malloc(sizeof(bst_queue_t));
    queue->count = 0;
    queue->capacity = QUEUE_BST_INIT_CAP;
    queue->items = (bst_node_t**)malloc(sizeof(bst_node_t*) * queue->capacity);
    queue->front = 0;
    queue->rear = -1;
    return queue;
}

void bst_queue_enqueue(bst_queue_t* queue, bst_node_t* item){
    if (queue->rear == queue->capacity - 1){
        queue->capacity *= 2;
        queue->items = (bst_node_t**)realloc(queue->items, queue->capacity * sizeof(bst_node_t*));
    }

    if (queue->front == -1) queue->front = 0;
    queue->rear++;
    queue->items[queue->rear] = item;
    queue->count++;
}

bool bst_queue_is_empty(bst_queue_t* queue){
    return queue->front > queue->rear;
}

bst_node_t* bst_queue_dequeue(bst_queue_t* queue){
    if (queue->front == -1 || bst_queue_is_empty(queue)){
        fprintf(stderr, "can't dequeue from an empty queue!\n");
        exit(1);
    }
    return queue->items[queue->front++];
}

void bst_queue_print(bst_queue_t* queue){
    for (size_t i = queue->front; i <= queue->rear; i++){
        printf("%d ", queue->items[i]->value);
    }
    printf("\n");
}

void bst_queue_free(bst_queue_t* queue){
    free(queue->items);
    free(queue);
}
#endif

bst_node_t* bst_node_alloc(int value){
    bst_node_t* res = (bst_node_t*)malloc(sizeof(bst_node_t));
    res->value = value;
    res->left = res->right = NULL;
    return res;
}

bst_node_t* bst_node_insert(bst_node_t* root, int value){
    if(root == NULL) return bst_node_alloc(value);

    if(value < root->value)
        root->left = bst_node_insert(root->left, value);
    else if(value > root->value)
        root->right = bst_node_insert(root->right, value);
    return root;
}

bst_node_t* bst_node_delete(bst_node_t* root, int value){
    if(!root) return NULL;

    if(value < root->value)
        root->left = bst_node_delete(root->left, value);
    else if(value > root->value)
        root->right = bst_node_delete(root->right, value);
    else{
        if(!root->left && !root->right){
            free(root);
            return NULL;
        }
        if(!root->left){
            bst_node_t* tmp = root->right;
            free(root);
            return tmp;
        }
        
        while(root->right->left) root->right = root->right->left;
        bst_node_t* tmp = root->right;
        root->value = tmp->value;
        root->right = bst_node_delete(root->right, tmp->value);
    }

    return root;
}

int bst_arity(bst_node_t* root){
    int ar = 0;

    if(root->left) ar++;
    if(root->right) ar++;
    return ar; 
}

int bst_height(bst_node_t* root){
    if(!root) return 0;
    int left = bst_height(root->left);
    int right = bst_height(root->right);
    return (left > right ? left : right) + 1;
}

void bst_inorder_traversal(bst_node_t* root){
    if(root){
        bst_inorder_traversal(root->left);
        printf("%d ", root->value);
        bst_inorder_traversal(root->right);
    }
}

void bst_preorder_traversal(bst_node_t* root){
    if(root){
        printf("%d ", root->value);
        bst_preorder_traversal(root->left);
        bst_preorder_traversal(root->right);
    }
}

void breadth_first_search(bst_node_t* root){
    if (!root) return;

    bst_queue_t* q = bst_queue_alloc();

    bst_queue_enqueue(q, root);

    while (!bst_queue_is_empty(q)){
        bst_node_t* current = bst_queue_dequeue(q);
        printf("%d ", current->value);
        
        if (current->left) bst_queue_enqueue(q, current->left);
        if (current->right) bst_queue_enqueue(q, current->right);
    }
}

void bst_postorder_traversal(bst_node_t* root){
    if(root){
        bst_postorder_traversal(root->left);
        bst_postorder_traversal(root->right);
        printf("%d ", root->value);
    }
}

void bst_node_free(bst_node_t* node){
    if(node){
        bst_node_free(node->left);
        bst_node_free(node->right);
        free(node);
    }
}