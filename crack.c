#define _XOPEN_SOURCE
#include <cs50.h>
#include <crypt.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

//TO DO: Create recursive version of program to reduce length

//Test function slightly slower:
//bool test(string posspass, string salt, string hash);

int main(int argc, string argv[])
{
    //Ensure user inputs exactly two aruments, issue instructions upon failure to do so
    if (argc != 2)
    {
        printf("Please input hash\n");
        return 1;
    }

    //Create Salt
    //Store argv[1] as string hash, create array s with first three chars of hash to get salt, create string salt from array s
    string hash = argv[1];
    char s[3] = {hash[0], hash[1], '\0'};
    string salt = s;

    //Create library of possible password characters to cycle trhough, define its length to an integer
    char lib[54] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
                    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
                    '\0'};
    int liblen = strlen(lib);

    //Create array posspass, fill laterr char by char with password combos
    char posspass[6] = {'\0', '\0', '\0', '\0', '\0'};
    //Set last element to null identifier
    posspass[5] = '\0';
    //Declare password character testing ints
    int i, j, k, l, m;

    //Use brute force to break password:

    //Password length 1 test: A to z
    //Initialize variable m and move into loop if value is below liblen
    for (m = 0; m < liblen; m++)
        {
            //Put lib[m] (the element of array lib currently being tested) into element zero of array posspass
            posspass[0] = lib[m];
            //Crypt posspass using the salt found aboce and create string posshash with the hash produced
            string posshash = crypt(posspass, salt);
            //Use funtion strcmp to compare if posshash matches original hash, 0 = true, !0 = false
            int sc = strcmp(posshash, hash);
            //If true, print the password found, if false return to for loop above and increment
            if (sc == 0)
            {
                printf("Password: %s\n", posspass);
                return 0;
            }
        }
    //Password length 2 test: AA to zz
    //The process described here will be repeated below, just with more loops
    //Initialize variable l to 0 go into bracket
    for (l = 0; l < liblen; l++)
        {
            //Initialize variable m to 0 and go into bracket
            for (m = 0; m < liblen; m++)
            {
                //Code executes as described in password length 1 until m == liblen; when m == liblen, the program moves up a level and incriments l + 1,
                //then moves back to m and starts from zero, continuing to move up and down the loop until l && m == liblen, then moves to pass length 3
                posspass[0] = lib[m];
                posspass[1] = lib[l];
                string posshash = crypt(posspass, salt);
                int sc = strcmp(posshash, hash);
                if (sc == 0)
                {
                    printf("Password: %s\n", posspass);
                    return 0;
                }
            }
        }

    //Password length 3 test: AAA to zzz
    //Functions as described in pass length 2 with extra layer(s)
    for (k = 0; k < liblen; k++)
    {
        for (l = 0; l < liblen; l++)
        {

            for (m = 0; m < liblen; m++)
            {
                posspass[0] = lib[m];
                posspass[1] = lib[l];
                posspass[2] = lib[k];
                string posshash = crypt(posspass, salt);
                int sc = strcmp(posshash, hash);
                if (sc == 0)
                {
                    printf("Password: %s\n", posspass);
                    return 0;
                }
            }
        }
    }

    //Password length 4 test: AAAA to zzzz
    //Functions as described in pass length 2 with extra layer(s)
    for (j = 0; j < liblen; j++)
    {
        for (k = 0; k < liblen; k++)
        {

            for (l = 0; l < liblen; l++)
            {

                for (m = 0; m < liblen; m++)
                {
                    posspass[0] = lib[m];
                    posspass[1] = lib[l];
                    posspass[2] = lib[k];
                    posspass[3] = lib[j];
                    string posshash = crypt(posspass, salt);
                    int sc = strcmp(posshash, hash);
                    if (sc == 0)
                    {
                        printf("Password: %s\n", posspass);
                        return 0;
                    }
                }
            }
        }
    }

    //Password length 5 test: AAAAA to zzzzz
    //Functions as described in pass length 2 with extra layer(s)
    for (i = 0; i < liblen; i++)
    {
        for (j = 0; j < liblen; j++)
        {

            for (k = 0; k < liblen; k++)
            {

                for (l = 0; l < liblen; l++)
                {

                    for (m = 0; m < liblen; m++)
                    {
                        posspass[0] = lib[m];
                        posspass[1] = lib[l];
                        posspass[2] = lib[k];
                        posspass[3] = lib[j];
                        posspass[4] = lib[i];
                        string posshash = crypt(posspass, salt);
                        int sc = strcmp(posshash, hash);
                        if (sc == 0)
                        {
                            printf("Password: %s\n", posspass);
                            return 0;
                        }
                    }
                }
            }
        }
    }
}

//Test function, proved to be slightly slower, removed

//bool test(string posspass, string salt, string hash)
//{
//    string posshash = crypt(posspass, salt);
//    if (strcmp(posshash, hash) == 0)
//    {
//        return true;
//    }
//    return false;
//}


