#include "h/performer.h"
#include "h/descriptor.h"


int CreateTargetFile() {
    uint32_t arr[2500] = {};
    GetColorArray(arr, "chel.png");
    GetTargetFile(arr, "test-data/commands.txt");
    return 0;
}

int main(void) {
    CreateTargetFile();
    Descript();
    Perform();
    return 0;
}
