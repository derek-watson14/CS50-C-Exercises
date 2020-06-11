#include <stdio.h>
#include <math.h>

#include "cs50.h"
#include "cs50.c"

int calculate(float change);

int main(void)
{
    char yorn;
    do
    {
        yorn = get_char("Type 'c' to calculate change: ");
        if (tolower(yorn) == 'c')
        {
            //Get user input and convert
            float n;
            do
            {
                n = get_float("Change owed: ");
                n = (n * 100);
                n = round(n);
            }
            while (n < 0);
            int c = calculate(n);

            //Dispay count
            printf("%i\n", c);
        }
        else if (tolower(yorn) != 'c')
        {
            return 1;
        }  
    }
    while (tolower(yorn) == 'c');
}

int calculate(float change)
{
    //Set counter to 0
    int c = 0;

    //Check Quarters
    do
        while (change >= 25)
        {
            change = (change - 25);
            c++;
        }
    while (change >= 25);

    //Check Dimes
    do
        while (change >= 10)
        {
            change = (change - 10);
            c++;
        }
    while (change >= 10);

    //Check Nickels
    do
        while (change >= 5)
        {
            change = (change - 5);
            c++;
        }
    while (change >= 5);

    //Check Pennies
    do
        while (change >= 1)
        {
            change = (change - 1);
            c++;
        }
    while (change >= 1);

    return c;
}