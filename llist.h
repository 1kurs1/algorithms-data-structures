#pragma once

#define LINKED_LIST_IMPLEMENTATION
#define LINKED_LIST_CAPACITY 256

typedef struct linked_list_t linked_list_t;

struct linked_list_t {
    size_t count;
    int value;
    linked_list_t* next;
};

linked_list_t* list_alloc(){
    linked_list_t* list = malloc(sizeof(linked_list_t));
    list->count = 0;
    list->value = 0;
    list->next = NULL;
    return list;
}

void list_free(linked_list_t* list){
    linked_list_t* current = list;
    linked_list_t* next;
    while (current != NULL){
        next = current->next;
        free(current);
        current = next;
    }
}

void list_print(linked_list_t* list){
    linked_list_t* current = list->next;
    while (current != NULL){
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");
}

void list_add(linked_list_t* list, int value){
    linked_list_t* current = list;
    while (current->next != NULL) current = current->next;

    current->next = malloc(sizeof(linked_list_t));
    current->next->value = value;
    current->next->next = NULL;
    list->count++;
}

void list_remove_value(linked_list_t* list, int value){
    linked_list_t* current = list;
    while (current->next != NULL){
        if (current->next->value == value){
            linked_list_t* temp = current->next;
            current->next = current->next->next;
            free(temp);
            list->count--;
            return;
        }
        current = current->next;
    }
}

int list_remove_last(linked_list_t* list){
    int value = -1;
    if (list->next == NULL){
        value = list->value;
        free(list);
    }

    linked_list_t* current = list;
    while (current->next->next != NULL) current = current->next;
    value = current->next->value;
    free(current->next);
    current->next = NULL;
    list->count--;

    return value;
}

int list_at(linked_list_t* list, int index){
    if (index < 0 || index >= list->count){
        fprintf(stderr, "Index out of bounds!\n");
        return -1;
    }
    int idx = 0;
    linked_list_t* current = list->next;
    while (idx++ != index) current = current->next;
    return current->value;
}

void list_reverse(linked_list_t* list){
    if (list->next == NULL) return;

    linked_list_t* prev = NULL, *current = list->next, *next = NULL;
    while (current != NULL){
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    list->next = prev;
}

int list_find(linked_list_t* list, int value){
    if (list->value == value) return 0;

    int idx = 0;
    linked_list_t* current = list;
    while (current->next != NULL){
        if (current->next->value == value) return idx;
        current = current->next;
        idx++;
    }

    return -1;
}