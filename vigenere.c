#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int main(int argc, string argv[])
{
    // assuring correct number of command-line arguments input
    if (argc != 2)
    {
        printf("Incorrect number of input arguments!\n");
        return 1;
    }
    // initializing an array of integer to serve as a container for key
    int cipher[100];
    // converting key to uppercase for simplicity
    for (int i = 0; i < strlen(argv[1]); i++)
        argv[1][i] = toupper(argv[1][i]);\
    // assuring key is all alphabetical characters
    int j = 0;
    while (argv[1][j] != '\0')
    {
        if (argv[1][j] < 'A' || argv[1][j] > 'Z')
        {
            printf ("Incorrect key!\n");
            return 1;
        }
        j++;
    }
    // converting command-line argument to array of integers where A = 0, B = 1 etc. to get key values
    for (int k = 0; k < strlen(argv[1]); k++)
        cipher[k] = argv[1][k] - 65;
    string plainText = get_string("plaintext: ");
    string cipherText = plainText;
    int l = 0;
    int m = 0;
    while (plainText[m] != '\0')
    {
        // making sure uppercase stays uppercase
        if (plainText[m] >= 'A' && plainText[m] <= 'Z')
        {
        // reverting back to beginning of alphabet if overflow
            if (plainText[m] + cipher[l] > 'Z')
                cipherText[m] = 'A' + cipher[l] - ('Z' - plainText[m]) - 1;
            else cipherText[m] = plainText[m] + cipher[l];
            l++;
            // resetting key array to beginning if it overflows
            if (l >= strlen(argv[1]))
                l = 0;
        }
        // making sure lowercase stays lowercase
        else if (plainText[m] >= 'a' && plainText[m] <= 'z')
        {
        // reverting back to beginning of alphabet if overflow
            if (plainText[m] + cipher[l] > 'z')
                cipherText[m] = 'a' + cipher[l] - ('z' - plainText[m]) - 1;
            else cipherText[m] = plainText[m] + cipher[l];
            l++;
            if (l >= strlen(argv[1]))
                l = 0;
        }
        else cipherText[m] = plainText[m];
        m++;
    }
    printf("ciphertext: %s", cipherText);
    printf("\n");
    return 0;
}