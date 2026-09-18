#include <stdio.h>
#include <math.h>
#define PRINT_LINE puts("_______________________________________________");

int printSquareMatrix(int * matrix, size_t size) {
    for (size_t y = 0; y < size; y++) {
        for (size_t x = 0; x < size; x++) {
            printf("%*d", 4, matrix[y*size + x]);
        }
        printf("%c",'\n');
    }
    return 0;
}

int printRectangle(int * matrix, size_t size_x, size_t size_y) {
    for (size_t y = 0; y < size_y; y++) {
        for (size_t x = 0; x< size_x; x++) {
            printf("%*d", 4, matrix[y*size_x + x]);
        }
        printf("%c",'\n');
    }
    return 0;
}

int printUpLeftTriangle(int * matrix, size_t cathetus) {
    for (size_t i = 0; i < cathetus; i++) {
        for (size_t j = 0; j < cathetus-i; j++) {

                printf("%*d", 4, matrix[j+(2*cathetus -i + 1)*i/2]);
        }
        printf("%c",'\n');

    }
    return 0;
}

int printDownLeftTriangle(int * matrix, size_t cathetus) {
    for (size_t i = 0; i < cathetus; i++) {
        for (size_t j = 0; j < i+1; j++) {
                printf("%*d", 4, matrix[j+(2 + i - 1)*i/2]);
        }
        printf("%c",'\n');
    }
    return 0;
}

int printUpRightTriangle(int * matrix, size_t cathetus) {
    for (size_t i = 0; i < cathetus; i++) {
        for (size_t j = 0; j < i; j++) {
                printf("%*s", 4, " ");
            }
        for (size_t j = 0; j < cathetus-i; j++) {
                printf("%*d", 4, matrix[j+(2*cathetus -i + 1)*i/2]);
            }
        printf("%c",'\n');
    }
    return 0;
}

int printDownRightTriangle(int * matrix, size_t cathetus) {
    for (size_t i = 0; i < cathetus; i++) {
        for (size_t j = 0; j < cathetus-i-1; j++) {
                printf("%*s", 4, " ");
            }
        for (size_t j = 0; j < i+1; j++) {
                printf("%*d", 4, matrix[j+(2 + i - 1)*i/2]);
            }
        printf("%c",'\n');
    }
    return 0;
}

int * printChristmasTreeMatrix(int * matrix, size_t side) {
    int maxline = 1 + (side - 1) * 2;
    int * index = matrix;
    for (size_t i = 0; i < side; i++) {
        for (size_t j = 0; j < (maxline - i*2)/2; j++) {
            printf("%*s", 4, " ");
        }
        for (size_t j = 0; j < 1+2*i; j++) {
            printf("%*d", 4, matrix[(1 + (i-1))*i + j]);
            index ++;
        }
        printf("%c",'\n');
    }
    return index;
}

int printFunnelMatrix(int * matrix, size_t side, int tab) {
    int maxline = 1 + (side - 1) * 2;
    for (size_t i = 0; i < side; i++) {
        for (size_t j = 0; j < i+tab; j++) {
            printf("%*s", 4, " ");
        }
        for (size_t j = 0; j < maxline - (i * 2); j++) {
            printf("%*d", 4, matrix[(2 * maxline -2 * (i-1)) * i/2 + j]);
        }
        printf("%c",'\n');
    }
    return 0;
}

int printRhombusMatrix(int * matrix, size_t side) {
    int *  index = printChristmasTreeMatrix(matrix, side);
    printFunnelMatrix(index, side-1, 1);
    return 0;
}

int printUpLeftArbitraryTriangle(int * matrix, size_t a, size_t b) {
    size_t index = 0;
    for (size_t i = 0; i < a; i++) {
        for (size_t j = 0; j < (int)(a-i)*b/a; j++){
            printf("%*d", 4, matrix[index]);
            index++;
        }
        printf("%c",'\n');
    }
    return 0;
}

int printDownLeftArbitraryTriangle(int * matrix, size_t a, size_t b) {
    size_t index = 0;
    for (size_t i = a-1; i >0;) {
        i--;
        for (size_t j = 0; j < (int)(a-i)*b/a; j++){
            printf("%*d", 4, matrix[index]);
            index++;
        }
        printf("%c",'\n');
    }
    return 0;
}

int printUpRightArbitraryTriangle(int * matrix, size_t a, size_t b) {
    size_t index = 0;
    for (size_t i = 0; i < a; i++) {
        for (size_t j = 0; j < b - (int)(a-i)*b/a; j++) {
            printf("%*s", 4, " ");
        }
        for (size_t j = 0; j < (int)(a-i)*b/a; j++){
            printf("%*d", 4, matrix[index]);
            index++;
        }
        printf("%c",'\n');
    }
    return 0;
}

int printDownRightArbitraryTriangle(int * matrix, size_t a, size_t b) {
    size_t index = 0;
    for (size_t i = a-1; i >0;) {
        i--;
        for (size_t j = 0; j < b - (int)(a-i)*b/a; j++) {
            printf("%*s", 4, " ");
        }
        for (size_t j = 0; j < (int)(a-i)*b/a; j++){
            printf("%*d", 4, matrix[index]);
            index++;
        }
        printf("%c",'\n');
    }
    return 0;
}

int rhombus_matrix[41] = {
             1,
          2, 3, 4,
       5, 6, 7, 8, 9,
   10,11,12,13,14,15,16,
17,18,19,20,21,22,23,24,25,
   26,27,28,29,30,31,32,
      33,34,35,36,37,
         38,39,40,
            41,
};

int triangle_matrix[15] = {
    1, 2, 3, 4, 5,
    6, 7, 8, 9,
    10,11,12,
    13,14,
    15,
};

int square_matrix[25] = {
    1, 2, 3, 4, 5,
    6, 7, 8, 9, 10,
    11,12,13,14,15,
    16,17,18,19,20,
    21,22,23,24,25
};

int rectangle_matrix[35] = {
    1, 2, 3, 4, 5,
    6, 7, 8, 9, 10,
    11,12,13,14,15,
    16,17,18,19,20,
    21,22,23,24,25,
    26,27,28,28,29,
    30,31,32,33,34
};


int main() {
    PRINT_LINE
    printSquareMatrix(square_matrix, 5);
    PRINT_LINE
    printRectangle(rectangle_matrix, 5, 7);
    PRINT_LINE
    printUpLeftTriangle(triangle_matrix, 5);
    PRINT_LINE
    printDownLeftTriangle(triangle_matrix, 5);
    PRINT_LINE
    printUpRightTriangle(triangle_matrix, 5);
    PRINT_LINE
    printDownRightTriangle(triangle_matrix, 5);
    PRINT_LINE
    printChristmasTreeMatrix(rhombus_matrix , 5);
    PRINT_LINE
    printFunnelMatrix(rhombus_matrix, 5, 0);
    PRINT_LINE
    printRhombusMatrix(rhombus_matrix, 5);
    PRINT_LINE
    printUpLeftArbitraryTriangle(rhombus_matrix, 6, 13);
    PRINT_LINE
    printDownLeftArbitraryTriangle(rhombus_matrix, 8, 13);
    PRINT_LINE
    printUpRightArbitraryTriangle(rhombus_matrix, 7, 9);
    PRINT_LINE
    printDownRightArbitraryTriangle(rhombus_matrix, 7, 9);
    return 0;
}
