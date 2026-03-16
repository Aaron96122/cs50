#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// here we specified the two arrays of characters and scores
string ALPHABETS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
int VALUES[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

// here we define a pattern with length and all upper- and lower-cased characters for referrnece
typedef struct
{
    int length;
    char *upper;
    char *lower;
    int *values;
} Pattern;

// here we include the prototypes
Pattern make_pattern(void);
int get_score(string input, Pattern referrence);

int main(void)
{
    string input1 = get_string("Player 1: ");
    string input2 = get_string("Player 2: ");

    // here we get the two scores for two input strings
    Pattern referrence = make_pattern( );
    int score1 = get_score(input1, referrence);
    int score2 = get_score(input2, referrence);

    // here we compare the values of these two scores and decide which one wins
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int get_length(string input)
{
    // here we calculate the length of the ALPHABETS
    int count = 0;
    while (input[count])
    {
        count += 1;
    }
    return count;
}

Pattern make_pattern(void)
{
    Pattern output;
    int length = get_length(ALPHABETS);

    // here we define the two strings of arrays;
    output.upper = malloc(length * sizeof(char));
    output.lower = malloc(length * sizeof(char));
    output.values = malloc(length * sizeof(int));

    int temp = 0;
    for (int i = 0; i <= length; i++)
    {
        output.upper[i] = ALPHABETS[i];
        temp = (int)ALPHABETS[i] + 32;
        output.lower[i] = (char)temp;
        output.values[i] = VALUES[i];
    }
    output.length = length;
    return output;
}

int get_score(string input, Pattern referrence)
{
    int leng = get_length(input);
    int LEN = referrence.length;
    char *UPP = referrence.upper;
    char *LOW = referrence.lower;
    int *VAL = referrence.values;

    char temp;
    int score = 0;
    for (int i = 0; i < leng; i++)
    {
        temp = input[i];
        int j = 0;
        while (j < LEN + 1 && UPP[j] != temp && LOW[j] != temp)
        {
            j++;
        }

        if (j != LEN + 1)
        {
            score += VAL[j];
        }
    }
    return score;
}

