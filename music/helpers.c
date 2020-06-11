// Helper functions for music
#include <math.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    //Convert ASCII numbers of Chars to true value and store in ints
    int numer = fraction[0] - '0';
    int denom = fraction[2] - '0';

    int duration = (8 / denom) * numer;
    return duration;
}

bool is_rest(string s)
{
    if (s[0] == 0)
        return true; //TRUE == Rest
    else
        return false; //FALSE == No Rest
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    int natoracc = strlen(note); //Get length to test if accidental present
    double ahz; //Hz of A in given octave

    if (natoracc == 2)
    {
        //Use formula ahz = 440 * (2^(oct-4)) to determine Hz of A in a given octave
        ahz = 440 * pow(2, ((note[1] - '0') - 4));
    }
    //Same process if the octave number is shifted in the string by and accidental
    if (natoracc == 3)
    {
        ahz = 440 * pow(2, ((note[2] - '0') - 4));
    }

    double adj;
    double Hz;

    switch (note[0])
    {
        case 'A': //Note A ASCII value
            adj = 0;
            break;
        case 'B': //
            adj = 2;
            break;
        case 'C':
            adj = -9;
            break;
        case 'D':
            adj = -7;
            break;
        case 'E':
            adj = -5;
            break;
        case 'F':
            adj = -4;
            break;
        case 'G':
            adj = -2;
            break;
    }

    adj = (note[1] == 'b') ? adj - 1 : adj;
    adj = (note[1] == '#') ? adj + 1 : adj;

    Hz = ahz * pow(2, (adj / 12));
    return round(Hz);
}