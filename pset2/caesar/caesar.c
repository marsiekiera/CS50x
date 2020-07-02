#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// main function
int main(int argc, string argv[])
{
    if (argc == 2)
    {
        char ciphertext;
        int error1 = 0;

        // check if arg contains of only digits
        for (int j = 0; j < strlen(argv[1]); j++)
        {
            if (isdigit(argv[1][j]) == 0)
            {
                error1 = error1 + 1;
            }
        }

        if (argc == 2 && atoi(argv[1]) > 0 && error1 == 0 && strlen(argv[1]) > 0) //arg must be one interger
        {
            string plaintext = get_string("plaintext: ");
            int key = atoi(argv[1]);
            printf("%d\n", key);
            int key_mod = key % 26;

            printf("ciphertext: ");
            for (int i = 0; i < strlen(plaintext); i++)
            {
                // A - 65, Z - 90
                if (isupper(plaintext[i]) > 0)
                {
                    if (plaintext[i] + key_mod > 90)
                    {
                        ciphertext = plaintext[i] + key_mod - 26;
                    }
                    else
                    {
                        ciphertext = plaintext[i] + key_mod;
                    }
                }
                // a - 97, z - 122
                else if (islower(plaintext[i]) > 0)
                {
                    if (plaintext[i] + key_mod > 122)
                    {
                        ciphertext = plaintext[i] + key_mod - 26;
                    }
                    else
                    {
                        ciphertext = plaintext[i] + key_mod; // max 127
                    }
                }
                else
                {
                    ciphertext = plaintext[i];
                }
                printf("%c", ciphertext);
            }
            printf("\n");
        }
        else
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
}