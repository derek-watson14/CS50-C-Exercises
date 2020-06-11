#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    //Check command line argument
    if (argc != 2)
    {
        printf("k\n");
        return 1;
    }

    //Change key input to int
    int k = atoi(argv[1]);

    //Get plaintext
    string p = get_string("plaintext: ");

    //Print ciphertext
    printf("ciphertext: ");

    //Encode message
    for (int i = 0; i < strlen(p); i++)
    {
        //Check uppercase
        if (isupper(p[i]))
        {
            p[i] = p[i] - 65;
            p[i] = (p[i] + k) % 26;
            p[i] = p[i] + 65;
            printf("%c", (char) p[i]);
        }
        //Check lowercase
        else if (islower(p[i]))
        {
            p[i] = p[i] - 97;
            p[i] = (p[i] + k) % 26;
            p[i] = p[i] + 97;
            printf("%c", (char) p[i]);
        }
        //Print other chars
        else
        {
            printf("%c", (char) p[i]);
        }
    }
    printf("\n");
}