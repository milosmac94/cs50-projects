#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float change;

    // making sure change is a positive amount
    do
    {
        change = get_float("How much change do I owe you? ");
    }
    while (change < 0);

    // declaring a coin counter variable
    int coins = 0;

    // rounding up a float change value to integer, for easier calculation later
    change = round(change*100);

    // counting change starting with the biggest coin until it becomes 0
    while (change)
    {
        if (change >= 25)
        {
            change -= 25;
            coins++;
        }
        else if (change >= 10 && change < 25)
        {
            change -= 10;
            coins++;
        }
        else if (change >=5 && change < 10)
        {
            change -= 5;
            coins++;
        }
        else
        {
            change -= 1;
            coins++;
        }
    };

    // outputting number of coins
    printf("\nThat totals %d coins/n", coins);
}