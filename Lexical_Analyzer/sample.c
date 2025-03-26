#ifndef SAMPLE
#define SAMPLE /*Hello world*/

#include <stdio.h> //header files
#include"lexer.h" //header

#define CONST 15

int fun_mul(int num1, int num2);

int main() {

    int z[10] = {0};
    int x = 0;
    float _y = 10.15;
    int a_10 = 012345678;
    char *str = "Hello; world";

    y=1+2+3+4+12+16/x+CONST;
    x=x<<1;
    x >>= y;
    
    int sum = fun_mul((int)y++,~x);

    float sum = (float) x+y;

    printf("Sum of x and"" y is %f\n", sum);

    return 0;
}

int fun_mul(int num1, int num2) {

    return num1 * num2;
}

#endif