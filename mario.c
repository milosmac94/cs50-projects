#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int n;
    do {
        n = get_int("insert pyramid height: ");

    }
    while (n < 0 || n > 23);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n-i-1; j++)
            printf(" ");
        for (int k = 0; k < i+1; k++)
            printf("#");
        for (int s = 0; s < 2; s++)
            printf(" ");
        for (int m = 0; m < i+1; m++)
            printf("#");
    printf("\n");
    };
};