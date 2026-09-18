#include <stdio.h>
#include "swap.cpp"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#define DEBUG

//DONE swap without xor
//DONE validation through the original qsort
//??   time in table
//DONE qsort without buffer
//DONE bubble sort using voids
//DONE indexing using size_t

int compare_ints(const void * a, const void * b) {
    int arg1 = * (const int * )a;
    int arg2 = * (const int * )b;

    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

int user_Lamuto_partition(void * arr, int low, int high, size_t size, int (*comfunc)(const void *, const void *)) {
    unsigned char * char_arr = (unsigned char *)arr;
    unsigned char pivot[size];
    unsigned char * pivot_pointer = &char_arr[high*size];
    memcpy(pivot, &char_arr[high*size], size);
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if(comfunc(&char_arr[j*size], pivot) < 0) {
            i++;
            swap(&char_arr[j*size], &char_arr[i*size], size);
        }
    }
    swap(&char_arr[(i+1)*size], &char_arr[high*size], size);
    return i+1;
}

void user_inner_Lamuto_qsort(void * arr, int low, int high, size_t size,  int (*comfunc)(const void *, const void *)) {
    if (low < high) {
        int pivot = user_Lamuto_partition(arr, low, high, size, comfunc);
        user_inner_Lamuto_qsort(arr,       low, pivot - 1, size, comfunc);
        user_inner_Lamuto_qsort(arr, pivot + 1,      high, size, comfunc);
    }
}



int user_Hoare_partition(void * arr, size_t low, size_t high, size_t size, int (*comfunc)(const void *, const void *)) {
    unsigned char * char_arr = (unsigned char *) arr;
    unsigned char * pivot_pointer = &char_arr[((high+low)/2)*size];
    size_t left = low;
    size_t right = high;
    while (1) {
        while (comfunc(char_arr + left * size, pivot_pointer) < 0) {
            left++;
        }
        while(comfunc(char_arr + size * right, pivot_pointer) > 0) {
            right--;
        }
        if(left >= right) {
            return right;
        }
        if(pivot_pointer == &char_arr[size*left]) {
            pivot_pointer  = &char_arr[size*right];
        } else if (pivot_pointer == &char_arr[size*right]) {
            pivot_pointer = &char_arr[size*left];
        }
        swap(&char_arr[size*left], &char_arr[size*right], size);
        left++;
        right--;
    }
    return right;
}

int user_inner_Hoare_qsort (void * arr, size_t low, size_t high, size_t size,  int (*comfunc)(const void *, const void *))  {
    if (low < high) {
        size_t pivot = user_Hoare_partition(arr, low, high, size, comfunc);
        user_inner_Hoare_qsort(arr,       low, pivot, size, comfunc);
        user_inner_Hoare_qsort(arr, pivot + 1,  high, size, comfunc);
    }
    return 0;
}

void user_Hoare_qsort(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void *)) {
    user_inner_Hoare_qsort(base, 0, nitems-1, size, compar);
};

void user_Lamuto_qsort(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void *)) {
    user_inner_Lamuto_qsort(base, 0, nitems-1, size, compar);
};

double runTest(void (*sorter_fnc)(void *, size_t , size_t , int (*compar)(const void *, const void *)), unsigned int number) {//читаемое время
    int * arr =     (int*)calloc(number, sizeof(int));
    int * copyarr = (int*)calloc(number, sizeof(int));
    for (size_t i = 0; i < number; i++) {
        arr[i] = (rand() % (1000 + 1));
        copyarr[i] = arr[i];
    }
    clock_t start = clock();
    sorter_fnc(arr, number, sizeof(int), compare_ints);
    clock_t end = clock();
    qsort(copyarr, number, sizeof(int) , compare_ints);
    for (size_t i = 0; i < number; i++) {
        if(arr[i]!=copyarr[i]) {
            printf("INVALID RESULT");
            return -1;
        }
    }
    double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    return cpu_time_used;
}

// int main(void) {
//     double timeused1 = 0;
//     double timeused2 = 0;
//     srand(time(NULL));
//     unsigned int number_of_tests = 13;
//     unsigned int started_num_of_elements = 1000;
//     int * arr = (int *) calloc(number_of_tests, sizeof(int));
//     printf("%10s %9s %9s delta = Lamuto-Hoare\n", "", "Hoare", "Lamuto");
//     for(size_t i = 0; i < number_of_tests; i++) {
//         timeused1 = runTest(user_Hoare_qsort, started_num_of_elements);
//         timeused2 = runTest(user_Lamuto_qsort, started_num_of_elements);
//         printf("%*d %*lg %*lg %lg\n", 10, started_num_of_elements, 9, timeused1, 9, timeused2, timeused2 - timeused1);
//         started_num_of_elements *= 2;
//     }
//     return 0;
// }
