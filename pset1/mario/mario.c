#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int n;
    do
    {
        n = get_int("Size: ");
    }
    while (n < 1 || n > 8);
    for (int i = 0; i < n; i++)
    {
        for (int j = 1; j < n - i; j++)
        {
            printf(" ");
        }
        for (int k = n - 1; k < n + i; k++)
        {
            printf("#");
        }
        printf("  ");
        for (int l = n - 1; l < n + i; l++)
        {
            printf("#");
        }
        printf("\n");
    }
}