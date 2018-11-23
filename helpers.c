// Helper functions for music

#include <cs50.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    // initialize array to place int values for X and Y
    int arr[strlen(fraction)];

    // convert fraction to int and put in array
    for (int i = 0; i < strlen(fraction); i++)
        arr[i] = atoi(&fraction[i]);

    if (arr[2] == 8)
        return arr[0];
    else
    {
        // multiply fraction to turn it into eights
        while (arr[2] < 8)
        {
            arr[2] *= 2;
            arr[0] *= 2;
        }
        return arr[0];
    }
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    //Get octave from last char in note string
    int octave = atoi(&note[strlen(note) - 1]);


    // Determine Frequency of note in the given octive
    double freq = 0.0;

    // Determine note letter
    if (note[0] == 'A')
        freq = 440;

    else if (note[0] == 'B')
        freq = 440.0 * (pow(2.0, (2.0 / 12.0)));

    else if (note[0] == 'C')
        freq = 440.0 / (pow(2.0, (9.0 / 12.0)));

    else if (note[0] == 'D')
        freq = 440.0 / (pow(2.0, (7.0 / 12.0)));

    else if (note[0] == 'E')
        freq = 440.0 / (pow(2.0, (5.0 / 12.0)));

    else if (note[0] == 'F')
        freq = 440.0 / (pow(2.0, (4.0 / 12.0)));

    else if (note[0] == 'G')
        freq = 440.0 / (pow(2.0, (2.0 / 12.0)));

    // Loop to shift octave
    if (octave > 4)
    {
        for (int i = 0; i < octave - 4; i++)
        {
            freq *= 2.0;
        }
    }
    else if (octave < 4)
    {
        for (int i = 0; i < 4 - octave; i++)
        {
            freq /= 2.0;
        }
    }

    // Final adjustment or flat or sharp
    if (note[1] == 'b')
        freq /= (pow(2.0, (1.0 / 12.0)));

    else if (note[1] == '#')
        freq *= (pow(2.0, (1.0 / 12.0)));

    // Return frequency value as an int
    int result = round(freq);
    return result;
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    // if first character of the string is a null character, string is an empty row (break)
    if (s[0] == '\0')
        return true;
    else return false;
}
