#pragma once

#define SORTIONS_IMPLEMENTATION
#define length(arr) (sizeof(arr) / sizeof(arr[0]))

void merge(int* a, int left, int right, int end, int* b){
    int i = left, j = right;
    for(size_t k = left; k < end; k++){
        if(i < right && (j >= end || a[i] <= a[j])){
            b[k] = a[i];
            i++;
        }
        else{
            b[k] = a[j];
            j++;
        }
    }
}

void merge_sort(int* a, int* b, int n){
    int* src = a;
    int* dest = b;

    for(size_t width = 1; width < n; width *= 2){
        for(size_t i = 0; i < n; i += 2 * width){
            merge(src, i, fmin(i + width, n), fmin(i+2*width, n), dest);
        }

        int* tmp = src;
        src = dest;
        dest = tmp;
    }

    if(src != a) memcpy(a, src, n * sizeof(int));
}

void swap(int* a, int* b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void cocktail_shaker(int* arr, int n){
    bool swapped = true;
    int begin = 0;
    int end = n-1;

    while(swapped){
        swapped = false;

        for(size_t i = begin; i < end; i++){
            if(arr[i] > arr[i+1]){
                swap(&arr[i], &arr[i+1]);
                swapped = true;
            }
        }
        end--;

        for(size_t i = end; i > begin; i--){
            if(arr[i-1] > arr[i]){
                swap(&arr[i-1], &arr[i]);
                swapped = true;
            }
        }
        begin++;
    }
}

void heapify(int* arr, int n, int i){
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if(left < n && arr[left] > arr[largest])
        largest  = left;

    if(right < n && arr[right] > arr[largest])
        largest = right;

    if(largest != i){
        int tmp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = tmp;
    
        heapify(arr, n, largest);
    }
}

void heapsort(int* arr, int n){
    for(int i = n/2-1; i>= 0; i--)
        heapify(arr, n, i);

    for(int i = n-1; i > 0; i--){
        int tmp = arr[0];
        arr[0] = arr[i];
        arr[i] = tmp;
        heapify(arr, i, 0);
    }
}