#include <stdio.h>
#include <math.h>

//write hello world
int main(void)
{
    printf("hello, world\n");

    float number = 16;
    float half = 0.5;

    float result = round(number * half);

    printf("%.2f\n", result);

}