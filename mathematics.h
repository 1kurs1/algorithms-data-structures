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