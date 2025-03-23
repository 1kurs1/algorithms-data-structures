#pragma once

#define STACK_IMPLEMENTATION
#define STACK_INIT_CAPACITY 256

typedef struct stack{
    size_t count;
    size_t capacity;
    int* data;
} stack_t;

stack_t* stack_alloc(){
    stack_t* res = (stack_t*)malloc(sizeof(stack_t));
    res->count = 0;
    res->capacity = STACK_INIT_CAPACITY;
    res->data = (int*)malloc(res->capacity * sizeof(int));
    return res;
}

bool stack_is_empty(stack_t* stack){
    return stack->count == 0;
}


void stack_push(stack_t* stack, int item){
    if(stack->count >= stack->capacity){
        stack->capacity *= 2;
        stack->data = (int*)realloc(stack->data, stack->capacity * sizeof(int));
    }
    
    stack->data[stack->count++] = item;
}

int stack_pop(stack_t* stack){
    if(stack_is_empty(stack)){
        fprintf(stderr, "you can't call pop() on an empty stack!");
        return EXIT_FAILURE;
    }

    return stack->data[--stack->count];
}

void stack_free(stack_t* stack){
    free(stack->data);
    free(stack);
}

void stack_print(stack_t* stack){
    for(size_t i = 0; i < stack->count; i++)
        printf("%d ", stack->data[i]);
    printf("\n");
}