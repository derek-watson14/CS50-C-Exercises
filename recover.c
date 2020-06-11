#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef uint8_t  BYTE;

int main(int argc, char *argv[])
{
    //Return error for incorrect number of arguments
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image.file\n");
        return 1;
    }

    //Create pointer to card file name
    char *mCard = argv[1];

    //Open file with the input name
    FILE *mCardptr = fopen(mCard, "r");
    //Print error if file could not be opened
    if (!mCardptr)
    {
        fprintf(stderr, "Could not open '%s'.\n", mCard);
        return 2;
    }

    int blockSize = 512;
    int totalBytesRead;

    int imgCounter = 0;

    //Array to store each file name and null terminator
    char filename[8];
    filename[7] = '\0';

    //Initialize img ptr to null (meaning nothing is open)
    FILE *imgptr = NULL;

    do
    {
        //Buffer to hold blocks
        BYTE block[blockSize];

        //Read block, save size of block to variable
        totalBytesRead = fread(&block, sizeof(char), blockSize, mCardptr);

        //What to do if JPEG signature found
        if (block[0] == 0xff && block[1] == 0xd8 &&
            block[2] == 0xff && (block[3] & 0xf0) == 0xe0)
        {
            if (imgCounter == 0) //Instructions for first JPEG
            {
                sprintf(filename, "%03i.jpg", imgCounter);
                imgptr = fopen(filename, "a");

                fwrite(&block, (blockSize * sizeof(char)), 1, imgptr);
            }
            else if (imgCounter > 0) //Instructions for subsequent JPEGs
            {
                fclose(imgptr);

                sprintf(filename, "%03i.jpg", imgCounter);
                imgptr = fopen(filename, "a");

                fwrite(&block, (blockSize * sizeof(char)), 1, imgptr);
            }
            imgCounter++; //Increment image counter
        }
        else //When no signature found
        {
            //If file is open and current block fills the buffer
            if (imgptr != NULL && totalBytesRead == blockSize)
            {
                fwrite(&block, (blockSize * sizeof(char)), 1, imgptr);
            }
        }

    }
    while (totalBytesRead == blockSize);

    //Close open files
    fclose(imgptr);
    fclose(mCardptr);
}
