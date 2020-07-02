#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float dollars;
    int cents;
    int reszta;
    int quaters;
    int dimes;
    int nickels;
    int pennies;
    do
    {
        dollars = get_float("Change owed: ");
    }
    while (dollars <= 0);
    cents = round(dollars * 100);
    quaters = floor(cents / 25);
    dimes = floor((cents - quaters * 25) / 10);
    nickels = floor((cents - quaters * 25 - dimes * 10) / 5);
    pennies = floor((cents - quaters * 25 - dimes * 10 - nickels * 5) / 1);
    reszta = quaters + dimes + nickels + pennies;
    printf("%d\n", reszta);
}