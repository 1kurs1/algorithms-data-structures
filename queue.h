#pragma once

#define QUEUE_IMPLEMENTATION
#define QUEUE_INIT_CAPACITY 256

typedef struct queue{
    size_t count;
    size_t capacity;
    int* data;

    int begin;
    int end;
} queue_t;

queue_t* queue_alloc(){
    queue_t* res = (queue_t*)malloc(sizeof(queue_t));
    res->count = 0;
    res->capacity = QUEUE_INIT_CAPACITY;
    res->data = (int*)malloc(QUEUE_INIT_CAPACITY * sizeof(int));
    res->begin = 0;
    res->end = -1;
    return res;
}

bool queue_is_empty(queue_t* queue){
    return queue->begin > queue->end;
}

void queue_enqueue(queue_t* queue, int item){
    if(queue->end == queue->capacity-1){
        queue->capacity *= 2;
        queue->data = (int*)realloc(queue->data, queue->capacity * sizeof(int));
    }
    if(queue->begin == -1) queue->begin = 0;
    
    queue->end++;
    queue->count++;
    queue->data[queue->end] = item;
}

int queue_dequeue(queue_t* queue){
    if(queue->begin == -1 || queue_is_empty(queue)){
        fprintf(stderr, "you can't call dequeue() on an empty queue!");
        return EXIT_FAILURE;
    }

    return queue->data[queue->begin++];
}

void queue_free(queue_t* queue){
    free(queue->data);
    free(queue);
}

void queue_print(queue_t* queue){
    for(size_t i = 0; i < queue->count; i++)
        printf("%d ", queue->data[i]);
    printf("\n");
}