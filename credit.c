#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

//Function that seperates two place values in a 2 digit number and adds them together
int add_places(int x);

//Function that takes a base of 10 to the power of x - 1
long long ten_to(int x);

int main(void)
{
    //0. GET CARD NUMBER FROM USER
    long long cardnum = get_long_long("Enter Credit Card Number: ");

    //1. DETERMINE LENGTH OF CARD NUMBER
    //Create variables for while loop to measure the number of digits in the card number
    long long len_val = cardnum;
    int cardlen = 0;

    //Use iterate through each place in cardnum using integer division and counter varaible cardlen to determine number of digits
    while (len_val > 0)
    {
        len_val /= 10;
        cardlen++;
    }

    //Use ten_to function and integer division to get only the first two digits of cardnum; store for use later in validation
    int firsttwo = cardnum / (ten_to(cardlen));

    //2. CREATE ARRAY
    //Initialize array that will store one card number per element, in order from [0] to [x]
    int cardary[cardlen + 1];

    //Reset temporary variables for use in iteration function below
    len_val = cardnum;
    int cltemp = cardlen - 1;

    //Iterate through each place in card num again, this time adding each digit to cardary before moving on
    while (len_val > 0)
    {
        cardary[cltemp] = len_val % 10;
        len_val /= 10;
        cltemp--;
    }
    //Add null terminator to end of array
    cardary[cardlen] = '\0';

    //Set iteration variable and total to 0
    int counter = 0;
    int total = 0;

    //3. DETERMINE SUM OF CARD NUMBERS
    //Set i to cardlen - 1 (as to not iterate null term.), iterate through until counter equals 0 and we reach element [0]
    for (int i = cardlen - 1; i >= 0; i--)
    {
        counter++;
        //% counter by 2 to determine if odd or even, counter begins at 1, so even numbers will always be * by 2
        if (counter % 2 == 0)
        {

            total += add_places(cardary[i] * 2);
        }
        else
        {
            total += (cardary[i]);
        }
    }

    //4. CHECK VALIDITY OF SUM, LENGTH AND TYPE
    //If number is valid, use a switch to check length validity, then check first 1 - 2 places to determine card brand
    if (total % 10 == 0)
    {
        switch (cardlen)
        {
            case 13:
                if (cardary[0] == 4)
                {
                    printf("VISA\n");
                }
                else
                {
                    printf("INVALID\n");
                }
                break;
            case 15:
                if (firsttwo == 34 || firsttwo == 37)
                {
                    printf("AMEX\n");
                }
                else
                {
                    printf("INVALID\n");
                }
                break;
            case 16:
                if (cardary[0] == 4)
                {
                    printf("VISA\n");
                }
                else if (firsttwo > 50 && firsttwo < 56)
                {
                    printf("MASTERCARD\n");
                }
                else
                {
                    printf("INVALID\n");
                }
                break;
            default:
                printf("INVALID\n");
                break;
        }
    }
    else
    {
        printf("INVALID\n");
    }
}

//FUNCTIONS: see description above main
int add_places(int x)
{
    //i is number in the 1s place, j is the number in the 10s place
    int i = x % 10;
    int j = (x / 10) % 10;
    int k = i + j;
    return k;
}

long long ten_to(int y)
{
    long long n = 10;
    for (int m = 3; m < y; m++)
    {
        n = (m < y) ? n *= 10 : n;
    }
    return n;
}