// Copies a BMP file

#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize f infile outfile\n");
        return 1;
    }

    // ensure resize factor is acceptable and store it
    if (atof(argv[1]) > 100 || atof(argv[1]) < 0)
    {
        fprintf(stderr, "Resize value must be an 0.0 to 100.0\n");
        return 1;
    }

    // initialize reszie factor based on user input
    double resizeFactor;
    if (atof(argv[1]) < 1)
    {
        double temp = atof(argv[1]);
        resizeFactor = (round(temp * 10) / 10);
    }
    else
    {
        resizeFactor = round(atoi(argv[1]));
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (!inptr)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 1;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (!outptr)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 1;
    }

    // read infile's BITMAPFILEHEADER & BITMAPINFOHEADER
    BITMAPFILEHEADER infilebf;
    fread(&infilebf, sizeof(BITMAPFILEHEADER), 1, inptr);

    BITMAPINFOHEADER infilebi;
    fread(&infilebi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (infilebf.bfType != 0x4d42 || infilebf.bfOffBits != 54 || infilebi.biSize != 40 ||
        infilebi.biBitCount != 24 || infilebi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 1;
    }

    // adjust then write header values using resize factor
    BITMAPINFOHEADER outfilebi = infilebi;
    outfilebi.biWidth *= resizeFactor;
    outfilebi.biHeight *= resizeFactor;

    int inpadding = (4 - (infilebi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int outpadding = (4 - (outfilebi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    outfilebi.biSizeImage = ((outfilebi.biWidth * sizeof(RGBTRIPLE)) + outpadding) * (abs(outfilebi.biHeight));

    BITMAPFILEHEADER outfilebf = infilebf;
    outfilebf.bfSize = outfilebi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    fwrite(&outfilebf, sizeof(BITMAPFILEHEADER), 1, outptr);
    fwrite(&outfilebi, sizeof(BITMAPINFOHEADER), 1, outptr);

    int sizeOfHeaders = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // if the outfile needs padding, write it now
    if (outpadding > 0)
    {
        fseek(outptr, (outfilebi.biWidth * sizeof(RGBTRIPLE)), SEEK_CUR);
        for (int p = 0, outbiHeight = abs(outfilebi.biHeight); p < outbiHeight; p++ )
        {
            for (int n = 0; n < outpadding; n++)
            {
                fputc(0x00, outptr);
            }
            fseek(outptr, (outfilebi.biWidth * sizeof(RGBTRIPLE)), SEEK_CUR);
        }
        fseek(outptr, sizeOfHeaders, SEEK_SET);
    }

    int infileRowWidth = ((infilebi.biWidth) * sizeof(RGBTRIPLE)) + inpadding;
    int outfileRowWidth = ((outfilebi.biWidth) * sizeof(RGBTRIPLE)) + outpadding;

    if (atof(argv[1]) >= 1)
    {
        // iterate over infile's scanlines
        for (int i = 0, inbiHeight = abs(infilebi.biHeight); i < inbiHeight; i++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < infilebi.biWidth; j++)
            {
                //read and store RGBTRIPLE of next pixel to be written
                RGBTRIPLE triple;
                //read starting position

                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // equation to determine starting location to write next pixel
                int rowAdjustment = (outfileRowWidth * i * resizeFactor);
                int columnAdjustment = (j * resizeFactor * sizeof(RGBTRIPLE));

                int newPixelStartingLoc = sizeOfHeaders + rowAdjustment + columnAdjustment;

                //set starting point for next pixel and write a resizeFactor-larger "pixel" in outfile
                fseek(outptr, newPixelStartingLoc, SEEK_SET);
                for (int k = 0; k < resizeFactor; k++)
                {
                    for (int m = 0; m < resizeFactor; m++)
                    {
                        fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                    }
                    long skipRow = ((outfilebi.biWidth * sizeof(RGBTRIPLE)) + outpadding) - (resizeFactor * sizeof(RGBTRIPLE));
                    fseek(outptr, skipRow, SEEK_CUR);
                }
            }
            // skip over padding, if any
            fseek(inptr, inpadding, SEEK_CUR);
        }
    }
    else
    {
        int skipPxRow = round(abs(infilebi.biHeight) / abs(outfilebi.biHeight));
        int skipPxCol = round(infilebi.biWidth / outfilebi.biWidth);

        // iterate over infile's rows
        for (int k = 0; k < abs(outfilebi.biHeight); k++)
        {
            // iterate over columns
            for (int m = 0; m < outfilebi.biWidth; m++)
            {
                //read and store RGBTRIPLE of next pixel to be written
                RGBTRIPLE triple;

                //calculate read position for current iteration
                int currReadRow = sizeOfHeaders + (infileRowWidth * (k * skipPxRow));
                int currReadCol = m * (skipPxCol * sizeof(RGBTRIPLE));
                int currReadPosition = currReadRow + currReadCol;

                if (m < outfilebi.biWidth)
                {
                    fseek(inptr, currReadPosition, SEEK_SET);
                    fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            fseek(outptr, outpadding, SEEK_CUR);
        }
    }
    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
