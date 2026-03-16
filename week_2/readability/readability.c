#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

// here we define a structure to return information needed
typedef struct
{
    float letter;
    float word;
    float sentence;
} Basic;

// here we include all the necessary prototypes
Basic get_basic(string input);
float get_score(Basic info);

int main(void)
{
    string text = get_string("Text: ");
    Basic temp = get_basic(text);
    // printf("Letters: %f\nWords: %f\nSentences: %f\n", temp.letter, temp.word, temp.sentence);
    float score = get_score(temp);
    int final = (int)round(score);

    if (final < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (final > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", final);
    }

}

Basic get_basic(string input)
{
    int lett_count = 0;
    int word_count = 0;
    int sent_count = 0;
    Basic result;

    int i = 0;
    while (input[i])
    {
        if (isalpha(input[i]))
        {
            lett_count++;
        }
        else if (input[i] == '.' || input[i] == '?' || input[i] == '!')
        {
            if (input[i+1] != '\0' && input[i+2] != '\0')
            {
                sent_count++;
            }
        }
        else if (input[i] == ' ')
        {
            word_count++;
        }
        i++;
    }

    result.letter = lett_count;
    result.word = word_count + 1;
    result.sentence = sent_count + 1;

    return result;
}

float get_score(Basic info)
{
    float L = info.letter / info.word * 100;
    // printf("%f\n", L);
    float S = info.sentence / info.word * 100;
    // printf("%f\n", S);
    float index = 0.0588 * L - 0.296 * S - 15.8;
    return index;
}

