#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int swap(int * first, int * second) {
    int buffer = * first;
    * first = * second;
    * second = buffer;
    return 0;
}

int partition_Lamuto(int * arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if(arr[j] < pivot) {
            i++;
            swap(&arr[j], &arr[i]);
        }
    }
    swap(&arr[i+1], &arr[high]);
    return i+1;
}

int QuickSort_Lamuto(int * arr, int low, int high) {
    if (low < high) {
        int pivot = partition_Lamuto(arr, low, high);
        QuickSort_Lamuto(arr,       low, pivot - 1);
        QuickSort_Lamuto(arr, pivot + 1,      high);
    }
    return 0;
}

int partition_Hoare(int * arr, int low, int high) {
    int pivot = arr[(high+low)/2];
    int left = low;
    int right = high;
    while (1) {
        while (arr[left] < pivot) {
            left++;
        }
        while(arr[right] > pivot) {
            right--;
        }
        if(left >= right) {
            return right;
        }
        swap(&arr[left], &arr[right]);
    }
    return right;
}

int QuickSort_Hoare(int * arr, int low, int high) {
    if (low < high) {
        int pivot = partition_Hoare(arr, low, high);
        QuickSort_Hoare(arr,       low, pivot);
        QuickSort_Hoare(arr, pivot + 1,  high);
    }
    return 0;
}




int compare_ints(const void *a, const void *b) {
    int arg1 = *(const int *)a;
    int arg2 = *(const int *)b;

    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

int main(void) {
    int arr[] = {6,7,6,7,6, 6, 67, 67};
    size_t n = sizeof(arr) / sizeof(arr[0]);

    QuickSort_Hoare(arr, 0, n - 1);

    for (size_t i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
