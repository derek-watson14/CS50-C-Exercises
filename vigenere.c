#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Get keyword in argv[1]
int main(int argc, string argv[])
{
    //Check command line argument
    if (argc != 2)
    {
        printf("k\n");
        return 1;
    }
    else
    {
        for (int i = 0; i < strlen(argv[1]); i++)
        {
            if (!isalpha(argv[1][i]))
            {
                printf("k\n");
                return 1;
            }
        }
    }

    //Define string and string length
    string keyword = argv[1];
    int klen = strlen(keyword);

    //Get plaintext
    string p = get_string("plaintext: ");
    int plen = strlen(p);


    //Print ciphertext
    printf("ciphertext: ");

    //Encode message:

    //1. Set counter variables i and j to 0
    //2. Check Boolean expression: is i < the number of characters in the given plaintext (plen)?
        //2a. If i is less than plen, execute code in curly brackets
        //2b. If i is equal to or greater than plen, skip code in curly brackets
    //3. After code is executed, increase counter and return to step 2
    for (int i = 0, j = 0; i < plen; i++)
    {
        //Determine adjustment caused by the first character of the keyword, call it key
        //Because both Upr and Lwr case letters cause same adjustment (ie. B = +1; b = +1), move all to lower to simplify adjustment
        //1. Mod the value of j with the length of the keyword so it cycles through the keyword even if j becomes greater than klen
        //2. Move j mod klen to the lower case
        //3. Subtract 'a' (97) from the new lower char to get a 0 to 26 adjustment value (ie. b (98) - a (97) = 1), call that value key
        int key = tolower(keyword[j % klen]) - 'a';

        //If plaintext character number i is uppercase, execute this equation and print, using key (determined above)
        //Increase j by one to continue cycling through keyword with each new plaintext letter
        if (isupper(p[i]))
        {
            printf("%c", (((p[i] - 'A' + key) % 26) + 'A'));
            j++;
        }
        //If plaintext character number i is lowercase, execute this equation and print, using key (determined above)s
        //Increase j by one to continue cycling through keyword with each new plaintext letter
        else if (islower(p[i]))
        {
            printf("%c", (((p[i] - 'a' + key) % 26) + 'a'));
            j++;
        }
        //If character is not alhabetical, print as is; do NOT increase j to hold current position for next alphabetical character
        else
        {
            printf("%c", p[i]);
        }
    }
    printf("\n");
}