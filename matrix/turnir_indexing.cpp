#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define PRINT_LINE puts("_______________________________________________");

const unsigned int STRING_SIZE = 256;


int index_of(char ** arr, size_t arr_size, char * name) {
    for (size_t i = 0; i< arr_size; i++) {
        if (strcmp(name, arr[i]) == 0) {
            return i;
        }
    }
    return -1;
}
int printResultsSquare(char ** names, int * square_results, const unsigned TAB, const unsigned number_of_teams) {
    printf("%*s", TAB, "");

    for (int i = 0; i < number_of_teams; i++) {

        printf("%*s", TAB, names[i]);

    }
    printf("%c", '\n');

    for (int i = 0; i < number_of_teams; i++) {

        printf("%*s", TAB, names[i]);

        for (int j = 0; j < number_of_teams; j++) {
            if (j == i) {
                printf("%*c", TAB, '#');
                continue;
            }
            printf("%*d", TAB, square_results[i * number_of_teams + j]);
        }

        printf("%c", '\n');
    }
    return 0;
}
int printResultsTriangle(char ** names, int * triangle_results, const unsigned TAB, const unsigned number_of_teams) {
    printf("%*s", TAB, "");

    for (int i = 0; i < number_of_teams; i++) {

        printf("%*s", TAB, names[i]);

    }
    printf("%c", '\n');

    for (int i = 0; i < number_of_teams; i++) {

        printf("%*s", TAB, names[i]);

        for (int j = 0; j < i; j++) {
            printf("%*d", TAB, triangle_results[(i-1)*i/2 + j]);
        }
        printf("%c", '\n');
    }
    return 0;
}


int main(){
    PRINT_LINE
    unsigned int number_of_teams = 0;
    char team_name[STRING_SIZE] = {};
    int longest_name = 0;

    puts("Enter how many teams: ");
    scanf("%d", &number_of_teams);

    PRINT_LINE

    char ** teams_names = (char **)calloc(1, number_of_teams*sizeof(char*) + STRING_SIZE*sizeof(char));
    assert(teams_names);

    for (int i = 0; i < number_of_teams; i++){
        printf("Enter team number %d name: ", i+1);
        scanf("%255s", team_name);
        unsigned int length = strlen(team_name);
        if (i == 0) {
            teams_names[i] = (char*)(teams_names + number_of_teams);
            strcpy(teams_names[i], team_name);
        } else {
            teams_names[i] = (char*)(teams_names[i-1] + strlen(teams_names[i-1]) + 1);
            strcpy(teams_names[i], team_name);
        }
        if (length > longest_name) {
            longest_name = length;
        }
    }

    PRINT_LINE

    const unsigned TAB = longest_name + 3;

    int *results = (int*)calloc(number_of_teams * number_of_teams, sizeof(int));

    assert(results != NULL);

    int *triangle_results = (int*)calloc(2 *(number_of_teams-1) * number_of_teams/2, sizeof(int));

    assert(triangle_results != NULL);


    printResultsSquare(teams_names, results, TAB, number_of_teams);

    printResultsTriangle(teams_names, triangle_results, TAB, number_of_teams);

    while (1) {
        char first_team [STRING_SIZE] = {};
        char second_team[STRING_SIZE] = {};
        unsigned int count = 0;
        puts("Entr first team, then second, then count");
        scanf("%s", first_team);
        if (strcmp(first_team, "q") == 0) {
            return 0;
        }
        scanf("%s", second_team);
        scanf("%d", &count);

        size_t first_team_index  = index_of(teams_names, number_of_teams, first_team);
        size_t second_team_index = index_of(teams_names, number_of_teams, second_team);

        if (first_team_index >= 0 && second_team_index >= 0 && count != 0 && first_team_index != second_team_index) {

            results[first_team_index  *number_of_teams + second_team_index] = count;
            results[second_team_index *number_of_teams + first_team_index]  = -count;

            if(first_team_index > second_team_index) {
                triangle_results[(first_team_index-1)*(first_team_index)/2 + second_team_index] =  count;
            } else {
                triangle_results[(second_team_index-1)*(second_team_index)/2 + first_team_index] =  -count;
            }

            printResultsSquare(teams_names, results, TAB, number_of_teams);
            PRINT_LINE
            printResultsTriangle(teams_names, triangle_results, TAB, number_of_teams);

        } else {
            puts ("INVALID INPUT");
            return 0;
        }
    }

    free(teams_names);
    free(results);
    return 0;

}



