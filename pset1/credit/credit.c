#include <stdio.h>
#include <cs50.h>

int main(void)
{
    long number;
    do
    {
        number = get_long("Number: ");
    }
    while (number <= 0);
    long number_sum1 = number;
    int sum_1 = 0;
    int sum_2 = 0;
    int rest_1 = 0;
    int rest_2 = 0;
    for (long i = 100; i < 10 * number_sum1; i = i * 100)
    {
        rest_1 = (number_sum1 % i - number_sum1 % (i / 10)) / (i / 10);
        if (2 * rest_1 > 9)
        {
            sum_1 = sum_1 + 2 * rest_1 - 9;
        }
        else
        {
            sum_1 = sum_1 + 2 * rest_1;  
        }
    }
    for (long j = 10; j < 10 * number_sum1; j = j * 100)
    {
        rest_2 = (number_sum1 % j - number_sum1 % (j / 10)) / (j / 10);
        sum_2 = sum_2 + rest_2;
    }
    int sum = sum_1 + sum_2;
    if (sum % 10 == 0)
    {
        if (number >= 1000000000000000)
        {
            if (number < 10000000000000000)
            {
                if (number >= 5100000000000000 && number < 5600000000000000)
                {
                    printf("MASTERCARD\n"); 
                }
                else if (number >= 4000000000000000 && number < 5000000000000000)
                {
                    printf("VISA\n");
                }
                else
                {
                    printf("INVALID\n");
                }
            }
            else
            {
                printf("INVALID\n"); 
            }
        }
        else if ((number >= 340000000000000 && number < 350000000000000) || (number >= 370000000000000 && number < 380000000000000))
        {
            printf("AMEX\n");
        }
        else if (number >= 4000000000000)
        {
            if (number < 5000000000000)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}