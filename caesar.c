#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, string argv[])
{
    // assuring correct number of command-line arguments input
    if (argc != 2)
    {
        printf("Incorrect number of input arguments!\n");
        return 1;
    }
    // converting command-line argument to integer
    int intArg = atoi(argv[1]);
    // making sure key wraps around if it's larger than alphabet length
    // in order keep the ciphertext in alphabet limits
    if (intArg > 26)
        intArg %= 26;
    string plainText = get_string("plaintext: ");
    string cipherText = plainText;
    int i = 0;
    while (plainText[i] != '\0')
    {
        // making sure uppercase stays uppercase
        if (plainText[i] >= 'A' && plainText[i] <= 'Z')
        {
        // reverting back to beginning of alphabet if overflow
            if (plainText[i] + intArg > 'Z')
                cipherText[i] = 'A' + intArg - ('Z' - plainText[i]) - 1;
            else cipherText[i] = plainText[i] + intArg;
        }
        // making sure lowercase stays lowercase
        else if (plainText[i] >= 'a' && plainText[i] <= 'z')
        {
        // reverting back to beginning of alphabet if overflow
            if (plainText[i] + intArg > 'z')
                cipherText[i] = 'a' + intArg - ('z' - plainText[i]) - 1;
            else cipherText[i] = plainText[i] + intArg;
        }
        else cipherText[i] = plainText[i];
        i++;
    }
    printf("ciphertext: %s", cipherText);
    printf("\n");
    return 0;
}