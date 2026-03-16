#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// here we define the alphabets in upper and lower cases
string UPP = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
string LOW = "abcdefghijklmnopqrstuvwxyz";

// here we include all the needed prototypes
int get_length(string input);
int normal_key(int length, char *input);
char *convert(string input, int key);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }

    char *input = argv[1];
    int LEN = get_length(input);
    int key = normal_key(LEN, input);
    if (key == 0)
    {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }

    string text = get_string("plaintext: ");



    char *result = convert(text, key);
    printf("ciphertext: %s\n", result);
}

int get_length(string input)
{
    int length = 0;
    do
    {
        length++;
    }
    while (input[length]);

    return length;
}

int normal_key(int length, char *input)
{
    int i = length;
    int number = 0;
    int value = 0;
    while (isdigit(input[i - 1]))
    {
        if (i == 0)
        {
            break;
        }
        value = input[i - 1] - '0';
        number += pow(10, length - i) * value;
        i--;
    }
    return number;
}

char *convert(string input, int key)
{
    int len = get_length(input);
    int LEN = get_length(UPP);
    char target;
    int j;
    char *ciphertext = malloc(len * sizeof(char));
    int c;

    for (int i = 0; i < len; i++)
    {
        j = 0;
        target = input[i];
        if (isalpha(target))
        {
            if (isupper(target))
            {
                while (j <= LEN && UPP[j] != target)
                {
                    j++;
                }
            }
            else if (islower(target))
            {
                while (j <= LEN && LOW[j] != target)
                {
                    j++;
                }
            }
        }
        else
        {
            j = LEN;
        }

        // here we get the value of j
        // printf("The value of j is: %i;", j);
        if (j != LEN)
        {
            c = (j + key) % 26;
            if (isupper(target))
            {
                ciphertext[i] = UPP[c];
            }
            else
            {
                ciphertext[i] = LOW[c];
            }
        }
        else
        {
            ciphertext[i] = target;
        }
        // printf("The ciphered one is: %c\n", ciphertext[i]);
    }
    return ciphertext;
}
