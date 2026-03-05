#include <cs50.h>
#include <stdio.h>

void print_any(int anything, char symbol);
void print_row(int index, int height);
int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    int index = 0;
    do
    {
        index++;
        print_row(index, height);
        printf("\n");
    }
    while (index < height);
}

void print_any(int anything, char symbol)
{
    for (int i = 1; i <= anything; i++)
    {
        printf("%c", symbol);
    }
}

void print_row(int index, int height)
{
    // Here we calculate the number of first empties
    int empty = height - index;
    print_any(empty, ' ');

    // Here we calculate the number of second bricks
    print_any(index, '#');

    // Here we print out the two empties anyway
    printf("  ");

    // Here we print out the fourth bricks
    print_any(index, '#');
}
