#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    long long cardNum;
    cardNum = get_long_long("Input CC number: ");
        int checkDigit;
	    int checkSum = 0;
	    int checkSumHelper;
	    int digitCounter = 0;
	    int checkSumNonMultiplied = 0;
    // creating a helper cardNum for digitCounter
    long long cardNumHelper1;
    cardNumHelper1 = cardNum;
    while (cardNumHelper1)
    {
        cardNumHelper1 /= 10;
        digitCounter++;
    }

    // creating a helper cardNum for checkSum
    long long cardNumHelper2;
    cardNumHelper2 = cardNum;

    while (cardNumHelper2)
    {
        checkSumNonMultiplied += cardNumHelper2 % 10;
        // cutting off the last digit to expose second-to-last
        cardNumHelper2 /= 10;

        // adding together every second digit in order to get checkSum. We're dividing by ten at the end of the loop as well for the same purpose
        // if (cardNumHelper2 > 10)
        // {
        	// getting the last digit
            checkDigit = cardNumHelper2 % 10;

            // helper we utilize to cover case when the multiplication of checkDigit is bigger than 10. Explained below
            checkSumHelper = checkDigit * 2;
            if (checkSumHelper < 10)
                checkSum += (checkSumHelper);
            else
            {
            	// iterating through loop twice because this number is always between 10 and 19 and we need two digits out of it
            	for (int i=0; i<2; i++)
            	{

            		// getting digits of the two-digit number and adding to checkSum immediately
	                int checkSumHelperCounter = checkSumHelper % 10;
	                checkSum += checkSumHelperCounter;
	                checkSumHelper /= 10;
				}
            }
        // }
        // cutting off the added digit
        cardNumHelper2 /= 10;
    }

    int checkSumTotal = checkSum + checkSumNonMultiplied;
    int finalDigit = checkSumTotal % 10;
    if (finalDigit == 0 && digitCounter == 15 && (cardNum / 10000000000000 == 34 || cardNum / 10000000000000 == 37))
            printf("AMEX\n");
    else if (finalDigit == 0 && digitCounter == 16 && (cardNum / 1000000000000000 == 4))
		    printf("VISA\n");
	else if (finalDigit == 0 && digitCounter == 13 && (cardNum / 100000000000 == 51))
		    printf("VISA\n");
	else if (finalDigit == 0 && digitCounter == 16 && (cardNum / 100000000000000 == 51 || cardNum / 100000000000000 == 52 || cardNum / 100000000000000 == 53 || cardNum / 100000000000000 == 54 || cardNum / 100000000000000 == 55))
		    printf("MASTERCARD\n");
	else printf("INVALID\n");

	return 0;
}