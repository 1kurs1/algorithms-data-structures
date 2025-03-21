#include <time.h>

#include "stack.h"

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

    int lastNum = stack_pop(stack);
    printf("stack last number is %d\n", lastNum);

    // clean up
    stack_free(stack);
    #endif

    return EXIT_SUCCESS;
}