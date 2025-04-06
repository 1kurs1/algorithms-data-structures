#pragma once

#include "mathematics.h"

#define QUEUE_AVL_INIT_CAP 256
#define QUEUE_AVL_IMPLEMENTATION

typedef struct avl_node_t {
    int value;
    int height;
    struct avl_node_t* left;
    struct avl_node_t* right;
} avl_node_t;

typedef struct avl_queue {
    size_t count;
    size_t capacity;
    avl_node_t** items;
    int front;
    int rear;
} avl_queue_t;

avl_queue_t* avl_queue_alloc();

void avl_queue_enqueue(avl_queue_t* queue, avl_node_t* item);
bool avl_queue_is_empty(avl_queue_t* queue);
avl_node_t* avl_queue_dequeue(avl_queue_t* queue);
void avl_queue_print(avl_queue_t* queue);
void avl_queue_free(avl_queue_t* queue);

#ifdef QUEUE_AVL_IMPLEMENTATION
avl_queue_t* avl_queue_alloc(){
    avl_queue_t* queue = (avl_queue_t*)malloc(sizeof(avl_queue_t));
    queue->count = 0;
    queue->capacity = QUEUE_AVL_INIT_CAP;
    queue->items = (avl_node_t**)malloc(sizeof(avl_node_t*) * queue->capacity);
    queue->front = 0;
    queue->rear = -1;
    return queue;
}

void avl_queue_enqueue(avl_queue_t* queue, avl_node_t* item){
    if (queue->rear == queue->capacity - 1){
        queue->capacity *= 2;
        queue->items = (avl_node_t**)realloc(queue->items, queue->capacity * sizeof(avl_node_t*));
    }
    if (queue->front == -1) queue->front = 0;
    queue->rear++;
    queue->items[queue->rear] = item;
    queue->count++;
}

bool avl_queue_is_empty(avl_queue_t* queue){
    return queue->front > queue->rear;
}

avl_node_t* avl_queue_dequeue(avl_queue_t* queue){
    if (queue->front == -1 || avl_queue_is_empty(queue)){
        fprintf(stderr, "can't dequeue from an empty queue!\n");
        exit(1);
    }
    return queue->items[queue->front++];
}

void avl_queue_print(avl_queue_t* queue){
    for (size_t i = queue->front; i <= queue->rear; i++){
        printf("%d ", queue->items[i]->value);
    }
    printf("\n");
}

void avl_queue_free(avl_queue_t* queue){
    free(queue->items);
    free(queue);
}
#endif

#define AVL_TREE_IMPLEMENTATION

avl_node_t* avl_node_alloc(int value){
    avl_node_t* node = (avl_node_t*)malloc(sizeof(avl_node_t));
    node->value = value;
    node->height = 1;
    node->left = node->right = NULL;
    return node;
}

int avl_get_height(avl_node_t* node){
    return (node == nullptr) ? 0 : node->height;
}

int avl_get_balance(avl_node_t* node){
    return (node == nullptr) ? 0 : avl_get_height(node->left) - avl_get_height(node->right);
}

avl_node_t* avl_rotate_right(avl_node_t* node){
    avl_node_t* newRoot = node->left;
    avl_node_t* right = newRoot->right;

    newRoot->right = node;
    node->left = right;

    node->height = 1 + max(avl_get_height(node->left), avl_get_height(node->right));
    newRoot->height = 1 + max(avl_get_height(newRoot->left), avl_get_height(newRoot->right));

    return newRoot;
}

avl_node_t* avl_rotate_left(avl_node_t* node){
    avl_node_t* newRoot = node->right;
    avl_node_t* left = newRoot->left;

    newRoot->left = node;
    node->right = left;

    node->height = 1 + max(avl_get_height(node->left), avl_get_height(node->right));
    newRoot->height = 1 + max(avl_get_height(node->left), avl_get_height(newRoot->right));

    return newRoot;
}

avl_node_t* avl_insert(avl_node_t* node, int value){
    if (node == nullptr)
        return avl_node_alloc(value);

    if (value < node->value)
        node->left = avl_insert(node->left, value);
    if (value > node->value)
        node->right = avl_insert(node->right, value);
    else
        return node;

    node->height = 1 + max(avl_get_height(node->left), avl_get_height(node->right));

    int balance = avl_get_balance(node);

    if (balance > 1 && value < node->left->value) return avl_rotate_right(node);
    if (balance < -1 && value > node->right->value) return avl_rotate_left(node);
    if (balance > 1 && value > node->left->value){
        node->left = avl_rotate_left(node->left);
        return avl_rotate_right(node);
    }
    if (balance < -1 && value < node->right->value){
        node->right = avl_rotate_right(node->right);
        return avl_rotate_left(node);
    }

    return node;
}

avl_node_t* avl_delete(avl_node_t* node, int value){
    if(node == nullptr)
        return node;

    if(value < node->value)
        node->left = avl_delete(node->left, value);
    else if(value > node->value)
        node->right = avl_delete(node->right, value);
    else{
        if(node->left == nullptr || node->right == nullptr){
            avl_node_t* tmp = node->left ? node->left : node->right;
            free(node);
            return tmp;
        }

        avl_node_t* tmp = node->right;
        while(tmp->left != nullptr) tmp = tmp->left;

        node->value = tmp->value;
        node->right = avl_delete(node->right, tmp->value);
    }

    node->height = 1 + max(avl_get_height(node->left), avl_get_height(node->right));

    int balance = avl_get_balance(node);
    int balance_left = avl_get_balance(node->left);
    int balance_right = avl_get_balance(node->right);

    if(balance > 1 && balance_left >= 0)
        return avl_rotate_right(node);
    if(balance > 1 && balance_left < 0){
        node->left = avl_rotate_left(node->left);
        return avl_rotate_right(node);
    }

    if(balance < -1 && balance_right <= 0)
        return avl_rotate_right(node);
    if(balance < -1 && balance_right > 0){
        node->right = avl_rotate_right(node->right);
        return avl_rotate_left(node);
    }

    return node;
}

void avl_free(avl_node_t* node){
    if(node){
        avl_free(node->left);
        avl_free(node->right);
        free(node);
    }
}

void avl_inorder_traversal(avl_node_t* root){
    if(root){
        avl_inorder_traversal(root->left);
        printf("%d ", root->value);
        avl_inorder_traversal(root->right);
    }
}

void avl_preorder_traversal(avl_node_t* root){
    if(root){
        printf("%d ", root->value);
        avl_preorder_traversal(root->left);
        avl_preorder_traversal(root->right);
    }
}

void avl_breadth_first_search(avl_node_t* root){
    if (!root) return;

    avl_queue_t* q = avl_queue_alloc();

    avl_queue_enqueue(q, root);

    while (!avl_queue_is_empty(q)){
        avl_node_t* current = avl_queue_dequeue(q);
        printf("%d ", current->value);
        
        if (current->left) avl_queue_enqueue(q, current->left);
        if (current->right) avl_queue_enqueue(q, current->right);
    }
}

void avl_postorder_traversal(avl_node_t* root){
    if(root){
        avl_postorder_traversal(root->left);
        avl_postorder_traversal(root->right);
        printf("%d ", root->value);
    }
}