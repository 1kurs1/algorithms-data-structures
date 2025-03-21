#include "pch.h"
#include "stack.h"
#include "queue.h"

int main(){
    #ifdef STACK_IMPLEMENTATION
    srand(time(NULL));
    // initialize:
    stack_t* stack = stack_alloc();

    // demonstration:
    printf("stack numbers: ");
    for(int i = 0; i < 10; i++)
        stack_push(stack, rand() % (100) + 1);
    stack_print(stack);

    int lastFromStack = stack_pop(stack);
    printf("stack last number is %d\n", lastFromStack);

    int firstFromStack;
    while(!stack_is_empty(stack)) firstFromStack = stack_pop(stack);
    printf("stack first number is %d\n\n", firstFromStack);

    // clean up
    stack_free(stack);
    #endif

    #ifdef QUEUE_IMPLEMENTATION
    // initialization:
    queue_t* queue = queue_alloc();

    // demontration:
    printf("queue numbers: ");
    for(int i = 0; i < 10; i++)
        queue_enqueue(queue, rand()%(100) + 1);
    queue_print(queue);

    int firstFromQueue = queue_dequeue(queue);
    printf("queue first number: %d\n", firstFromQueue);

    int lastFromQueue;
    while(!queue_is_empty(queue)) lastFromQueue = queue_dequeue(queue);
    printf("queue last number: %d\n\n", lastFromQueue);

    // clean up:
    queue_free(queue);
    #endif

    return EXIT_SUCCESS;
}