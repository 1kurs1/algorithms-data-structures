#include "pch.h"
#include "stack.h"
#include "queue.h"
#include "llist.h"
#include "mathematics.h"
#include "hashmap.h"
#include "sort.h"

int main(int argc, char* argv[]){
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

    const char* perform_options = "[--dynamic | --memory | --recursive]";
    if(argc < 3){
        fprintf(stderr, "usage: %s <n> %s\n", argv[0], perform_options);
        return EXIT_FAILURE;
    }

    uint64_t (*fibonacci)(int n);
    int n = atoi(argv[1]);

    if(n > 92){
        fprintf(stderr, "fibonacci(%d) overflows if n is greater than 92\n", n);
        return EXIT_FAILURE;
    }

    if(strcmp(argv[2], "--memory") == 0){
        printf("memorized version: ");
        fibonacci = &fibonacci_memory;
    }
    else if(strcmp(argv[2], "--dynamic") == 0){
        printf("dynamic version: ");
        fibonacci = &fibonacci_dynamic;
    }
    else if(strcmp(argv[2], "--recursive") == 0){
        printf("recursive version: ");
        fibonacci = &fibonacci_recursive;
    }
    else{
        fprintf(stderr, "invalid perfomance option specified, valid options are: %s\n", perform_options);
        return EXIT_FAILURE;
    }

    printf("fibanacci(%d) = %llu\n\n", n, fibonacci(n));
    #endif

    #ifdef HASHMAP_IMPLEMENTATION
    hashmap_t* map = hashmap_alloc();

    const char* arr[5] = {"Apple", "Banana", "Grape", "Pineapple", "Orange"};
    for(int i = 0; i < 5; i++) hashmap_insert(map, arr[i], i+1);
    printf("hashmap:\n");
    hashmap_print(map);
    
    printf("hashmap about grape: %d\n", hashmap_get(map, "Grape")->value);
    printf("hashmap delete grape: \n");
    hashmap_delete(map, "Grape");
    hashmap_print(map);
    printf("\n");

    hashmap_free(map);
    #endif

    #ifdef SORTIONS_IMPLEMENTATION
    int* merge_sort_arr = (int*)malloc(500 * sizeof(int));
    int* after_sort_arr = (int*)malloc(500 * sizeof(int));

    printf("array before sort: ");
    for(int i = 0; i < 500; i++) {
        merge_sort_arr[i] = rand()%100 + 1;
        printf("%d ", merge_sort_arr[i]);
    }
    
    printf("\nlist after merge sortion: ");
    merge_sort(merge_sort_arr, after_sort_arr, 500);
    for(int i = 0; i < 500; i++) printf("%d ", after_sort_arr[i]);
    printf("\n\n");

    free(merge_sort_arr);
    free(after_sort_arr);
    #endif

    return EXIT_SUCCESS;
}