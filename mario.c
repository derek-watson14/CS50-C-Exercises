#include "cs50.h"
#include "cs50.c"
#include <stdio.h>

int main(void)
{
    //Height input
    int desiredHeight;
    do
    {
        desiredHeight = get_int("Height: ");
    }
    while (desiredHeight <= 0 || desiredHeight > 8);

    //Print rows
    for (int i = 0; i < desiredHeight; i++)
    {
        int hashCounter = 0;

        //Print spaces
        int j;
        for (j = 0; j < (desiredHeight - (i + 1)); j++)
        {
            printf(" ");
        }
        //Print hashes
        for (int k = 0; k < (desiredHeight - j); k++)
        {
            printf("#");
            hashCounter++;
        }

        printf("  ");

        for (int m = 0; m < hashCounter; m++)
        {
            printf("#");
        }

        printf("\n");
    }
}
