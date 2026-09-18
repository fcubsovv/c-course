#include <stdlib.h>
#include <assert.h>

void mergeArrays(int * array, int * buffer, int low, int high, int mid) {
    for (int i = 0; i <= high; i++) {
        buffer[i] = array[i];
    }
    int i = low;
    int j = mid+1;
    int k = 0;
    while(i <= mid && j <= high) {
        if (buffer[i] < buffer[j]) {
            array[k] = buffer[i];
            i++;
        } else {
            array[k] = buffer[j];
            j++;
        }
        k++;
    }
    while (i <= mid) {
        array[k] = buffer[i];
        k++;
        i++;
    }

}

void mergeSortWithoutMemory(int * array, int * buffer, int low, int high) {
    if (low < high) {
        int mid = (low+high)/2;

        mergeSortWithoutMemory(array, buffer,     low,  mid);
        mergeSortWithoutMemory(array, buffer, mid + 1, high);

        mergeArrays(array, buffer, low, high, mid);
    }
}

void mergeSort(int * array, int len) {

    int * buffer = (int *)calloc(len, sizeof(int));
    assert(buffer);

    mergeSortWithoutMemory(array, buffer, 0, len-1);

    free(buffer);
}
