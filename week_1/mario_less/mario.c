#include <cs50.h>
#include <stdio.h>

void print_row(int empties, int bricks);
int main(void)
{
    int height;
    int i = 1;

    do
    {
        height = get_int("Height? ");
    }
    while (height <= 0);

    do
    {
        print_row(height - i, i);
        i++;
    }
    while (i <= height);
}

void print_row(int empties, int bricks)
{
    for (int i = 1; i <= empties; i++)
    {
        printf(" ");
    }
    for (int j = 1; j <= bricks; j++)
    {
        printf("#");
    }
    printf("\n");
}
