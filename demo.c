#include "pch.h"
#include "stack.h"
#include "queue.h"
#include "llist.h"
#include "mathematics.h"
#include "hashmap.h"
#include "sort.h"
#include "graph.h"
#include "bst.h"
#include "avl.h"

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

    int mat_x[] = {
        1, 2, 
        3, 4,
        5, 6
    };

    int mat_y[] = {
        1, 10,
        2, 13
    };

    int mat_z[] = {
        1, 2,
        3, 4
    };

    matrix_t* mat_a = matrix_from_array(mat_x, 3, 2);
    matrix_t* mat_b = matrix_from_array(mat_y, 2, 2);
    matrix_t* mat_c = matrix_from_array(mat_z, 2, 2);

    printf("A:\n");
    matrix_print(mat_a);
    printf("B:\n");
    matrix_print(mat_b);
    printf("C:\n");
    matrix_print(mat_c);

    printf("matrix \'a\' rang: %d\n", matrix_rang(mat_a));
    printf("matrix \'b\' rang: %d\n", matrix_rang(mat_b));
    printf("matrix \'c\' rang: %d\n", matrix_rang(mat_c));

    printf("matricies multiplication A x B: \n");
    matrix_t* mat_mul = matrix_multiply_matrix(mat_a, mat_b);
    matrix_print(mat_mul);
    
    printf("matricies sum B + C:\n");
    matrix_t* mat_sum = matrix_sum(mat_b, mat_c);
    matrix_print(mat_sum);

    printf("matrix on scalar A x 2:\n");
    matrix_multiply_scalar(mat_a, 2);
    matrix_print(mat_a);

    int mat_arr1[] = {
        4, 2,
        1, 7
    };

    int mat_arr2[] = {
        5, 3,
        6, 1
    };

    matrix_t* mat_d = matrix_from_array(mat_arr1, 2, 2);
    matrix_t* mat_e = matrix_from_array(mat_arr2, 2, 2);

    printf("mat D:\n");
    matrix_print(mat_d);
    printf("mat E:\n");
    matrix_print(mat_e);

    printf("D x E (in place):\n");
    matrix_multiply_in_place(mat_d, mat_e);
    matrix_print(mat_d);
    
    printf("D^4:\n");
    matrix_t* mat_exp = matrix_exponent(mat_d, 4);
    matrix_print(mat_exp);

    printf("\n");

    matrix_free(mat_mul);
    matrix_free(mat_sum);
    matrix_free(mat_a);
    matrix_free(mat_b);
    matrix_free(mat_c);
    matrix_free(mat_d);
    matrix_free(mat_e);
    matrix_free(mat_exp);
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
    int* after_cocktail_shaker_sort = (int*)malloc(500 * sizeof(int));

    printf("array before sort: ");
    for(int i = 0; i < 500; i++) {
        merge_sort_arr[i] = rand()%100 + 1;
        after_cocktail_shaker_sort[i] = merge_sort_arr[i];
        printf("%d ", merge_sort_arr[i]);
    }
    
    printf("\nlist after merge sortion: ");
    merge_sort(merge_sort_arr, after_sort_arr, 500);
    for(int i = 0; i < 500; i++) printf("%d ", after_sort_arr[i]);
    printf("\n");

    printf("\nlist after cocktail-shaker sortion: ");
    cocktail_shaker(after_cocktail_shaker_sort, 500);
    for(int i = 0; i < 500; i++) printf("%d ", after_cocktail_shaker_sort[i]);
    printf("\n\n");

    free(merge_sort_arr);
    free(after_sort_arr);
    free(after_cocktail_shaker_sort);

    printf("heapsort:\n");

    int heap[500];
    for(size_t i = 0; i < 500; i++) heap[i] = rand() % 100 + 1;

    heapsort(heap, 500);
    for(size_t i = 0; i < 500; i++) printf("%d ", heap[i]);
    printf("\n");
    #endif

    #ifdef GRAPH_IMPLEMENTATION
    graph_t* g = graph_alloc(6);

    graph_add_edge(g, 0, 1);
    graph_add_edge(g, 0, 4);

    graph_add_edge(g, 1, 2);
    graph_add_edge(g, 1, 4);

    graph_add_edge(g, 2, 3);
    graph_add_edge(g, 2, 4);
    graph_add_edge(g, 2, 5);

    graph_add_edge(g, 3, 4);
    graph_add_edge(g, 3, 5);

    graph_add_edge(g, 4, 5);

    graph_print(g);

    // graph_t* graph_g = graph_alloc(8);

    // graph_add_edge(graph_g, 'A', 'B');
    // graph_add_edge(graph_g, 'A', 'E');
    // graph_add_edge(graph_g, 'A', 'F');

    // graph_add_edge(graph_g, 'C', 'E');

    // graph_add_edge(graph_g, 'D', 'E');
    // graph_add_edge(graph_g, 'D', 'F');
    // graph_add_edge(graph_g, 'D', 'H');
    // graph_add_edge(graph_g, 'F', 'G');

    // graph_add_edge(graph_g, 'G', 'H');

    // graph_print(graph_g);

    // printf("------dijkstra------\n");
    // graph_dijkstra(g, 'A', 'C');
    // graph_dijkstra(g, 'A', 'B');
    // graph_dijkstra(g, 'F', 'B');
    // graph_dijkstra(g, 'H', 'A');
    // graph_dijkstra(g, 'E', 'H');

    // graph_free(g);

    printf("BFS:\n");
    graph_bsf(g, 0);

    printf("DFS:\n");
    graph_dfs(g, 0);

    graph_free(g);
    #endif

    #ifdef BINARY_SEARCH_TREE_IMPLEMENTATION
    bst_node_t* bst_root = NULL;

    for(int i = 0; i < 7; i++)
        bst_root = bst_node_insert(bst_root, rand()%10+1);

    printf("binary search tree arity: %d\n", bst_arity(bst_root));
    printf("binary search tree height: %d\n", bst_height(bst_root));

    bst_node_delete(bst_root, 3);
    printf("bst after delete 3\n");

    printf("binary search tree arity: %d\n", bst_arity(bst_root));
    printf("binary search tree height: %d\n", bst_height(bst_root));

    printf("BFS: ");
    breadth_first_search(bst_root);
    printf("\n");

    printf("postorder traversal: ");
    bst_postorder_traversal(bst_root);
    printf("\n");

    printf("preorder traversal: ");
    bst_preorder_traversal(bst_root);
    printf("\n");

    printf("inorder traversal: ");
    bst_inorder_traversal(bst_root);
    printf("\n\n");

    bst_node_free(bst_root);
    #endif

    #ifdef AVL_TREE_IMPLEMENTATION
    avl_node_t* avl_node = nullptr;
    avl_node = avl_insert(avl_node, 4);
    avl_node = avl_insert(avl_node, 2);
    avl_node = avl_insert(avl_node, 27);
    avl_node = avl_insert(avl_node, 34);
    avl_node = avl_insert(avl_node, 97);
    avl_node = avl_insert(avl_node, 8);
    avl_node = avl_insert(avl_node, 65);
    avl_node = avl_insert(avl_node, 43);
    
    printf("avl height: %d\n", avl_get_height(avl_node));
    avl_node = avl_delete(avl_node, 27);
    printf("avl height after deletion \'27\': %d\n", avl_get_height(avl_node));

    printf("avl bfs: \n");
    avl_breadth_first_search(avl_node);
    printf("\n");

    printf("avl postorder traversal: \n");
    avl_postorder_traversal(avl_node);
    printf("\n");

    printf("avl preorder traversal: \n");
    avl_preorder_traversal(avl_node);
    printf("\n");

    printf("avl inorder traversal: \n");
    avl_inorder_traversal(avl_node);
    printf("\n");

    avl_free(avl_node);
    #endif

    return EXIT_SUCCESS;
}