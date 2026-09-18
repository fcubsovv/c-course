#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "matrix_printer.cpp"

#define PRINT_LINE puts("_______________________________________________");


const unsigned int STRING_SIZE = 256;

int index_of(char ** arr, unsigned int arr_size, char * name) {
    for (unsigned int i = 0; i< arr_size; i++) {
        if (strcmp(name, arr[i]) == 0) {
            return i;
        }
    }
        return -1;
}


int main(){
    PRINT_LINE
    unsigned int number = 0;
    puts("Enter how many teams: ");
    scanf("%d", &number);
    PRINT_LINE
    char ** names = (char**)calloc(number, sizeof(char*));
    assert(names);
    char teamname[STRING_SIZE] = {};
    int mostlongword = 0;
    for (int i = 0; i < number; i++) {
        printf("Enter team number %d name: ", i+1);
        scanf("%255s", teamname);
        unsigned int length = strnlen(teamname, STRING_SIZE);
        names[i] = (char *)calloc((length + 1), sizeof(char));
        assert(names[i] != NULL);
        if (length > mostlongword) {
            mostlongword = length;
        }
        names[i] = strdup(teamname);
    }
    PRINT_LINE
    const unsigned int tab = mostlongword+2;
    int **results = (int**)calloc(number, sizeof(int*));
    assert(results != NULL);
    for (int i = 0; i < number; i++) {
        results[i] = (int*)calloc(number, sizeof(int));
        (results[i] != NULL);
    }

    printf("%*s", tab,  "");
    for (int i = 0; i < number; i++) {
        printf("%*s", tab, names[i]);
    }
    printf("%c", '\n');

    for (int i = 0; i < number; i++) {
        printf("%*s", tab, names[i]);

        for (int j = 0; j < i ; j++) {
            printf("%*d", tab, results[i][j]);
        }
        printf("%c", '\n');
    }



    while (1) {
        char frst[STRING_SIZE] = {};
        char secnd[STRING_SIZE] = {};
        unsigned int count;
        puts("Entr first team, then second, then count");
        scanf("%s",frst);
        scanf("%s",secnd);
        scanf("%d", &count);
        unsigned int frst_index = index_of(names, number, frst);
        unsigned int secnd_index = index_of(names, number, secnd);

        if (frst_index >= 0 && secnd_index >= 0 && count >= 0) {

            if (frst_index >= secnd_index) {
                results[frst_index][secnd_index] = count;
            } else {
                results[secnd_index][frst_index] = count;
            }
                for (int i = 0; i < number; i++) {
                    printf("%11s ", names[i]);
                }
                printf("%c", '\n');
                for (int i = 0; i < number; i++) {
                    printf("%s", names[i]);
                    for (int j = 0; j < i ; j++) {
                        printf("%11d", results[i][j]);
                    }
                    printf("%c", '\n');
                }
        } else {
            puts ("INVALID INPUT");
        }
    }
    for (int i = 0; i < number; i++) {
        free(names[i]);
    }
    free(names);
    free(results);
    return 0;

}



