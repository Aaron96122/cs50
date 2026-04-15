#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// here we define a random list to check the selection sort algorithm
int number[] = {3, 9, 22, 1, 90, 23, 54, 6, 2};

// here we include all the needed prototypes
int *selection(int *numbers, int index, int length);

int main(void)
{
    int length = sizeof(number) / sizeof(number[0]);
    int index = 0;
    int *result = selection(number, index, length);
    for (int i = 0; i < length; i++)
    {
        printf("%i ", result[i]);
    }
    printf("\n");
}

int *selection(int *numbers, int index, int length)
{
    if (index == length)
    {
        return 0;
    }

    int small = numbers[index];
    int pointer = index;
    for (int i = index; i < length; i++)
    {
        if (numbers[i] < small)
        {
            small = numbers[i];
            pointer = i;
        }
    }

    numbers[pointer] = numbers[index];
    numbers[index] = small;
    printf("Small: %i; Index: %i; Pointer: %i\n", small, index, pointer);
    selection(numbers, index + 1, length);
    return numbers;
}

