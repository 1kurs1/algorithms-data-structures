#pragma once

#define HASHMAP_IMPLEMENTATION
#define HASHMAP_INIT_CAPACITY 256

typedef struct hashmap_node_t hashmap_node_t;
struct hashmap_node_t{
    const char* key;
    int value;
    hashmap_node_t* next;
};

typedef struct hashmap{
    size_t count;
    size_t capacity;
    hashmap_node_t** data;
} hashmap_t;

uint64_t hash(hashmap_t* map, const char* str){
    uint64_t hash = 1029;
    int c;
    while(c = *str++) hash = 35 * hash + c;
    return hash % map->capacity;
}

hashmap_node_t* hashmap_node_alloc(const char* key, int value){
    hashmap_node_t* res = (hashmap_node_t*)malloc(sizeof(hashmap_node_t));
    res->key = strdup(key);
    res->value = value;
    return res;
}

void hashmap_node_print(hashmap_node_t* node){
    printf("[%s, %d]\n", node->key, node->value);
}

hashmap_t* hashmap_alloc(){
    hashmap_t* map = (hashmap_t*)malloc(sizeof(hashmap_t));
    map->capacity = HASHMAP_INIT_CAPACITY;
    map->count = 0;
    map->data = calloc(map->capacity, sizeof(hashmap_node_t*));
    return map;
}

void hashmap_insert(hashmap_t* map, const char* key, int value){
    if(map->count >= map->capacity){
        map->capacity *= 2;
        map->data = realloc(map->data, map->capacity * sizeof(hashmap_node_t));
    }


    uint64_t idx = hash(map, key);
    hashmap_node_t* node = hashmap_node_alloc(key, value);
    node->next = map->data[idx];
    map->data[idx] = node;
    map->count++;
}

hashmap_node_t* hashmap_get(hashmap_t* map, const char* key){
    uint64_t idx = hash(map, key);
    hashmap_node_t* current = map->data[idx];

    while(current != NULL){
        if(strcmp(key, current->key) == 0) return current;
        current = current->next;
    }

    return NULL;
}

void hashmap_delete(hashmap_t* map, const char* key){
    uint64_t idx = hash(map, key);
    hashmap_node_t* current = map->data[idx];
    hashmap_node_t* previous = NULL;

    while(current != NULL){
        if(strcmp(key, current->key) == 0){
            if(previous == NULL) map->data[idx] = current->next;
            else previous->next = current->next;
            free((void*)current->key);
            free(current);
            return;
        }
        
        previous = current;
        current = current->next;;
    }
    
    map->count--;
}

void hashmap_free(hashmap_t* map){
    for(size_t i = 0; i < map->capacity; i++){
        hashmap_node_t* current = map->data[i];
        while(current != NULL){
            hashmap_node_t* next = current->next;
            free((void*)current->key);
            free(current);
            current = next;
        }
    }

    free(map->data);
    free(map);
}

void hashmap_print(hashmap_t* map){
    for (size_t i = 0; i < map->capacity; i++){
        hashmap_node_t* current = map->data[i];
        while (current != NULL){
            hashmap_node_print(current);
            current = current->next;
        }
    }
    printf("\n");
}