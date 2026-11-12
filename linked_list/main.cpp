#include "h/list_handlers.h"
#include "h/list_dumpers.h"
#include "unit-tests/h/tests.h"
#include "unit-tests/h/test_info.h"

int main() {

    test_params frst = RunRundomPushPopTest();
    const char * command1 = "dot -Tpng graph.dot -o scheme1.png";
    int status1 = system(command1);
    test_params secnd = RunRandomInsertByIdxTest();
    const char * command2 = "dot -Tpng graph.dot -o scheme2.png";
    int status2 = system(command2);
    GenerateTestsHtmlFile(frst, secnd);


}
