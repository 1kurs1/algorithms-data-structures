#pragma once

#define MATH_IMPLEMENTATION

int abs(int n){
    return n > 0 ? n : -n;
}

int gcd_iterative(int a, int b){
    while(b != 0){
        int r = b;
        b = a%b;
        a = r;
    }
    return a;
}

int gcd_recursive(int a, int b){
    if(b == 0) return a;
    return gcd_recursive(b, a%b);
}

int lcm(int a, int b){
    return abs(a*b)/gcd_iterative(a, b);
}

uint64_t fibonacci_recursive(int n){
    if(n < 2) return n;
    return fibonacci_recursive(n-1) + fibonacci_recursive(n-2);
}

uint64_t fibonacci_memory(int n){
    uint64_t* arr = (uint64_t*)malloc((n+1) * sizeof(uint64_t));
    arr[0] = 0;
    arr[1] = 1;
    for(int i = 2; i <= n; i++) arr[i] = arr[i-1] + arr[i-2];
    uint64_t res = arr[n];
    free(arr);
    return res;
}

uint64_t fibonacci_dynamic(int n){
    if(n < 2) return n;
    
    uint64_t a = 0, b = 1, temp;
    for(int i = 2; i <= n; i++){
        temp = a+b;
        a = b;
        b = temp;
    }
    return b;
}