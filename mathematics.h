#pragma once

#define MATH_IMPLEMENTATION
#define matrix_at(matrix, i, j) ((matrix)->data[j * (matrix)->columns + i])

int abs(int n){
    return n > 0 ? n : -n;
}

int max(int a, int b){
    return a > b ? a : b;
}

int min(int a, int b){
    return a < b ? a : b;
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

typedef struct matrix{
    size_t rows;
    size_t columns;
    int* data;
} matrix_t;

matrix_t* matrix_alloc(size_t rows, size_t cols){
    matrix_t* res = (matrix_t*)malloc(sizeof(matrix_t));
    res->rows = rows;
    res->columns = cols;
    res->data = calloc(res->rows*res->columns, sizeof(int));
    return res;
}

bool matrix_is_square(matrix_t* mat){
    return mat->rows == mat->columns;
}

int matrix_rang(matrix_t* mat){
    if(matrix_is_square(mat)) return mat->rows;
    return -1;
}

void matrix_multiply_scalar(matrix_t* mat, int n){
    for(size_t i = 0; i < mat->rows; i++){
        for(size_t j = 0; j < mat->columns; j++){
            mat->data[i*mat->columns + j] *= n;
        }
    }
}

matrix_t* matrix_multiply_matrix(matrix_t* a, matrix_t* b){
    if(a->columns != b->rows){
        fprintf(stderr, "failed to multiply to matrices\n");
        exit(1);
    }

    matrix_t* res = matrix_alloc(a->rows, b->columns);
    for(size_t i = 0; i < res->rows; i++){
        for(size_t j = 0; j < res->columns; j++){
            res->data[i*res->columns + j] = 0;
            for(size_t k = 0; k < a->columns; k++){
                res->data[i*res->columns + j] += a->data[i*a->columns + k] * b->data[k*b->columns + j];
            }
        }
    }

    return res;
}

void matrix_multiply_in_place(matrix_t* a, matrix_t* b){
    if(!matrix_is_square(a) || !matrix_is_square(b) || a->rows != b->rows){
        fprintf(stderr, "error: wrong dimenions!\n");
        exit(1);
    }

    size_t n = a->rows;
    int tmp[n][n];

    for(size_t i = 0; i < a->rows; i++){
        for(size_t j = 0; j < a->columns; j++){
            tmp[i][j] = 0;
            for(size_t k = 0; k < n; k++)
                tmp[i][j] += matrix_at(a, k, j) * matrix_at(b, i, k);
        }
    }

    for(size_t i = 0; i < a->rows; i++){
        for(size_t j = 0; j < a->columns; j++){
            matrix_at(a, i, j) = tmp[i][j];
        }
    }
}

matrix_t* matrix_identity(size_t size){
    matrix_t* res = matrix_alloc(size, size);
    for(size_t i = 0; i < res->rows; i++){
        for(size_t j = 0; j < res->columns; j++){
            if(i == j) matrix_at(res, i, j) = 1;
            else matrix_at(res, i, j) = 0;
        }
    }
    return res;
}

matrix_t* matrix_exponent(matrix_t* mat, int n){
    if(n < 0){
        fprintf(stderr, "exponent must be  >= 0\n");
        exit(1);
    }

    matrix_t* res = matrix_identity(mat->columns);

    if(n == 0) return res;

    while(n){
        if(n & 1) matrix_multiply_in_place(res, mat);
        matrix_multiply_in_place(mat, mat);
        n>>=1;
    }

    return res;
}

matrix_t* matrix_sum(matrix_t* a, matrix_t* b){
    if(a->columns != b->columns || a->rows != b->rows){
        fprintf(stderr, "failed to sum different by size matricies\n");
        exit(1);
    }

    matrix_t* res = matrix_alloc(a->rows, b->columns);
    for(size_t i = 0; i < res->rows; i++){
        for(size_t j = 0; j < res->columns; j++)
            res->data[i*res->columns + j] = a->data[i*res->columns + j] + b->data[i*res->columns + j];
    }

    return res;
}

matrix_t* matrix_from_array(int* arr, int rows, int cols){
    matrix_t* res = matrix_alloc(rows, cols);
    memcpy(res->data, arr, rows * cols * sizeof(int));
    return res;
}

void matrix_print(matrix_t* mat){
    for(size_t i = 0; i < mat->rows; i++){
        for(size_t j = 0; j < mat->columns; j++){
            printf("%d ", mat->data[i*mat->columns + j]);
        }
        printf("\n");
    }
}

void matrix_free(matrix_t* mat){
    free(mat->data);
    free(mat);
}