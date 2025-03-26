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