#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// main function
int main(int argc, string argv[])
{
    //check is only 1 arg and consist of 26 char
    if (argc == 2 && strlen(argv[1]) == 26)
    {
        int error1 = 0;
        char char_sum_add;
        int char_sum_add_int;
        int char_sum = 0;
        for (int j = 0; j < strlen(argv[1]); j++)
        {
            // check if arg contains of only alpha
            if (isalpha(argv[1][j]) == 0)
            {
                error1 = error1 + 1;
            }
            // check if contains all alpha
            else
            {
                char_sum_add = toupper(argv[1][j]);
                char_sum_add_int = char_sum_add;
                char_sum = char_sum + char_sum_add_int;
            }
            // duplicate fail
        }
        char char_first_check;
        char char_second_check;

        // check duplicate char in key
        for (int i = 0; i < strlen(argv[1]); i++)
        {
            char_first_check = toupper(argv[1][i]);
            for (int j = 0; j < strlen(argv[1]); j++)
            {
                char_second_check = toupper(argv[1][j]);
                if (char_first_check == char_second_check && i != j)
                {
                    error1 = error1 + 1;
                }
            }
        }
        if (error1 == 0 && char_sum == 2015)
        {
            string plaintext = get_string("plaintext: ");
            string key = argv[1];
            char ciphertext;
            char plaintext_char;
            printf("ciphertext: ");
            for (int i = 0; i < strlen(plaintext); i++)
            {
                plaintext_char = plaintext[i];
                if (isupper(plaintext_char) > 0)
                {
                    if (isupper(key[plaintext_char - 65]) > 0)
                    {
                        ciphertext = key[plaintext_char - 65];
                    }
                    else
                    {
                        ciphertext = key[plaintext_char - 65] - 32;
                    }
                }
                else if (islower(plaintext_char) > 0)
                {
                    if (islower(key[plaintext_char - 97]) > 0)
                    {
                        ciphertext = key[plaintext_char - 97];
                    }
                    else
                    {
                        ciphertext = key[plaintext_char - 97] + 32;
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
            printf("Usage: ./substitution key\n");
            return 1;
        }
    }
    else
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
}