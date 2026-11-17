#include "../h/test_dumpers.h"

LIST_ERRORS GenerateTestsHtmlFile(test_params push_pop_test, test_params insert_pull_test) {
    FILE * fileopen = fopen("results.html", "w");
    if(fileopen == NULL) return cannot_open_file;

    fprintf(fileopen, "<h1> LIST DUMP RESULTS </h1>\n");
    fprintf(fileopen, "<h2> TESTS' DUMP </h2>\n");

    fprintf(fileopen, "<h3> RANDOM PUSH-POP-TEST result: %d</h3>\n", push_pop_test.res_code);
    fprintf(fileopen, "<h3> RANDOM PUSH-POP-TEST expected: %s</h3>\n", push_pop_test.expected_result);
    fprintf(fileopen, "<h3> RANDOM PUSH-POP-TEST LIST DUMP: </h3>\n");
    fprintf(fileopen, "<img src=\"%s\"/>\n", push_pop_test.filename);

    fprintf(fileopen, "<h3> RANDOM INSERT_PULL-TEST result: %d</h3>\n", insert_pull_test.res_code);
    fprintf(fileopen, "<h3> RANDOM INSERT_PULL-TEST expected: %s</h3>\n", insert_pull_test.expected_result);
    fprintf(fileopen, "<h3> RANDOM INSERT_PULL-TEST LIST DUMP: </h3>\n");
    fprintf(fileopen, "<img src=\"%s\"/>\n", insert_pull_test.filename);


    fclose(fileopen);

    return allright_list;
}
