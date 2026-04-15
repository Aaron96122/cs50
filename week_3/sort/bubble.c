#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

// here we define a random list to check the selection sort algorithm
int number[] = {3, 9, 22, 1, 90, 23, 54, 6, 2};

// here we include all the needed prototypes
int *bubble(int *numbers, int length);

int main(void)
{
    int length = sizeof(number) / sizeof(number[0]);
    int *result = bubble(number, length);
    for (int i = 0; i < length; i++)
    {
        printf("%i ", result[i]);
    }
    printf("\n");
}

int *bubble(int *numbers, int length)
{
    int swap = 0;
    int small;
    int large;

    for (int i = 0; i < length - 1; i++)
    {
        if (numbers[i] > numbers[i+1])
        {
            swap = 1;
            small = numbers[i + 1];
            large = numbers[i];
            numbers[i] = small;
            numbers[i + 1] = large;
        }
    }

    if (swap == 0)
    {
        return 0;
    }

    bubble(numbers, length);
    return numbers;
}
