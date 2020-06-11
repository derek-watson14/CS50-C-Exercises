#include "cs50.h"
#include "cs50.c"
#include <stdio.h>

int main(void)
{
    //Height input
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 0 || n >= 24);


    //Print rows
    int j;
    for (int i = 0; i < n; i++)
    {
        //Print spaces
        for (j = 0; j <= (n - (i + 2)); j++)
        {
            printf(" ");
        }
        //Print hashes
        for (int k = 0; k <= (n - j); k++)
        {
            printf("#");
        }
        printf("\n");
    }
}