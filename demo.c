#include "pch.h"
#include "stack.h"
#include "queue.h"
#include "llist.h"
#include "mathematics.h"

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

    #ifdef LINKED_LIST_IMPLEMENTATION
    // initialization:
    linked_list_t* list = list_alloc();
    
    // demonstration:
    for (size_t i = 0; i < 10; i++) list_add(list, i);
    printf("size of the list: %zu\n", list->count);
    list_print(list);
    
    printf("removing 1: \n");
    list_remove_value(list, 1);
    list_print(list);
    
    printf("first element: %d\n", list_at(list, 0));
    int last = list_remove_last(list);
    printf("last element: %d\n", last);
    printf("%d has been removed: \n", last);
    list_print(list);
    
    printf("number 3 is at index %d\n", list_find(list, 3));
    
    printf("reversed list: \n");
    list_reverse(list);
    list_print(list);
    
    printf("number 3 is at index %d\n\n", list_find(list, 3));
    
    // clean up:
    list_free(list);
    #endif

    #ifdef MATH_IMPLEMENTATION
    int a = -17, b = 6, c = 3;

    printf("ABS(%d) = %d\n", a, abs(a));
    printf("[iterative] GCD(%d, %d) = %d\n", b, c, gcd_iterative(b, c));
    printf("[recursive] GCD(%d, %d) = %d\n", b, c, gcd_recursive(b, c));
    printf("LCM(%d, %d) = %d\n\n", b, c, lcm(b, c));
    #endif

    return EXIT_SUCCESS;
}