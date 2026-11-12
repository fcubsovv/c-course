#ifndef TEST_INFO
#define TEST_INFO
enum LIST_TEST_RESULTS {
    list_test_allright = 0,
    list_test_unexpected_res = -1,
    error_in_push_pop = -2,
};


struct test_params {
    int res_code;
    const char * expected_result;
    const char * filename;
};

#endif
