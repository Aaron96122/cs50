#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// here we get the plaintext of 26 characters
string PLAIN = "abcdefghijklmnopqrstuvwxyz";

// here we include all the needed prototypes
int get_length(string input);
char *convert(string plaintext, char *cipher_table);

int main(int argc, char *argv[])
{
    if (argc == 1 || argc > 2)
    {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }

    // here we check the whether the input key is valid for this program
    // first, we check the length of the key
    string key = argv[1];
    int length = get_length(key);
    if (length != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    // here we check whether all the characters are alphabatical and identical to each other
    char target;
    int index;
    int pointer;
    int *table = malloc(256 * sizeof(int));
    table = memset(table, 0, 256 * sizeof(int));
    char *cipher_table = malloc(256 * sizeof(char));
    for (int i = 0; i < length; i++)
    {
        target = key[i];
        if (isalpha(target))
        {
            target = tolower(target);
            index = (int) target;
            pointer = (int) PLAIN[i];
            if (table[index] == 0)
            {
                table[index] = 1;
                cipher_table[pointer] = target;
                // printf("Target: %c; Index: %i; Cipherz: %c\n", target, index, PLAIN[i]);
            }
            else
            {
                printf("key must contain 26 different characters.\n");
                return 1;
            }
        }
        else
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
    }

    // here we get the final ciphertext
    string input = get_string("plaintext: ");
    char *result = convert(input, cipher_table);
    printf("ciphertext: %s\n", result);
}

int get_length(string input)
{
    int i = 0;
    while (input[i])
    {
        i++;
    }
    return i;
}

char *convert(string plaintext, char *cipher_table)
{
    int LEN = 26;
    int len = get_length(plaintext);
    char *final = malloc(len * sizeof(char));
    char target;
    char temp;
    int index;
    for (int i = 0; i < len; i++)
    {
        target = plaintext[i];
        // printf("Check the value: %c\n", target);
        if (isalpha(target))
        {
            if (islower(target))
            {
                index = (int) target;
                final[i] = cipher_table[index];
                // printf("The index is: %i; The ciphered_character is: %c\n", index, final[i]);
            }
            else
            {
                target = tolower(target);
                index = (int) target;
                final[i] = toupper(cipher_table[index]);
                // printf("The index is: %i; The ciphered_character is: %c\n", index, final[i]);
            }
        }
        else
        {
            final[i] = target;
            // printf("The ciphered_character is: %c\n", final[i]);
        }
    }
    return final;
}
