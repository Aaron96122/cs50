#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int count;
    int *array;
} GetArray;

typedef struct
{
    int *odd;
    int odd_size;
    int *even;
    int even_size;
} OddEven;

GetArray get_array(long number);
OddEven get_oddeven(GetArray input);
GetArray multiplication(GetArray input, int number);
int add(GetArray input);
int main(void)
{
    long number = get_long("Number: ");
    GetArray temp = get_array(number);
    // for (int i = 0; i < temp.count; i++)
    // {
    //     printf("%i", temp.array[i]);
    // }
    // printf("\n");
    int last = temp.count - 1;
    int first_one = temp.array[last];
    int second_last = temp.count - 2;
    int length = temp.count;
    // printf("%i", temp.array[last]);
    // printf("\n");
    int first_two = temp.array[last] * 10 + temp.array[second_last];
    // printf("%i", first_two);
    // printf("\n");

    // here we get the odd and even arrays
    OddEven result = get_oddeven(temp);
    GetArray odd, even;
    odd.count = result.odd_size;
    odd.array = result.odd;
    even.count = result.even_size;
    even.array = result.even;
    // for (int i = 0; i < odd.count; i++)
    // {
    //     printf("%i", odd.array[i]);
    // }
    // printf("\n");
    // for(int i = 0; i < even.count; i++)
    // {
    //     printf("%i", even.array[i]);
    // }
    // printf("\n");

    GetArray new;
    new = multiplication(odd, 2);

    // here we do the add version
    int odd_part = add(new);
    // printf("%i", odd_part);
    // printf("\n");
    int even_part = add(even);
    // printf("%i", even_part);
    // printf("\n");
    int final = odd_part + even_part;
    // printf("%i", final);
    // printf("\n");

    if (final % 10 == 0)
    {
        // here we check the VISA detail
        if (first_one == 4)
        {
            if (length == 13 || length == 16)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }

        // here we check the MASTERCARD detail
        else if (first_one == 5 && first_two != 56 && first_two != 57 && first_two != 58 &&
                 first_two != 59)
        {
            if (length == 16)
            {
                printf("MASTERCARD\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        // here we check the AMEX detail
        else if (first_two == 34 || first_two == 37)
        {
            if (length == 15)
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }

        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}

GetArray get_array(long number)
{ // here we extract the digits from long number using the subtraction of 10
    // for example:
    // 12345 / 10 = 1234; 12345 % 10 = 5;
    // 1234 / 10 = 123; 1234 % 10 = 4;
    // ...
    // 1 / 10 = 0; 1 % 10 = 1;
    long temp = number;
    int digit;
    GetArray result;
    int count = 0;
    result.array = malloc(1 * sizeof(int));

    do
    {
        count++;
        digit = temp % 10;
        result.array[count - 1] = digit;
        result.array = realloc(result.array, (count + 1) * sizeof(int));
        temp /= 10;
    }
    while (temp > 0);

    result.count = count;
    return result;
}

OddEven get_oddeven(GetArray input)
{
    int number = input.count;
    int *temp = input.array;
    int even_size = 0;
    int odd_size = 0;

    // here we measure the size of even and odd arraries
    if (number % 2 == 0)
    {
        even_size = number / 2;
        odd_size = number / 2;
    }
    else
    {
        odd_size = number / 2 + 1;
    }

    // here we define the odd and even arrays
    int *even_array = malloc(even_size * sizeof(int));
    int *odd_array = malloc(odd_size * sizeof(int));

    // here we allocate each int from the original array into the odd and even arrays
    int even_index = 0;
    int odd_index = 0;
    int i = 0;
    do
    {
        if (i % 2 == 0)
        {
            even_array[even_index] = temp[i];
            even_index++;
        }
        else
        {
            odd_array[odd_index] = temp[i];
            odd_index++;
        }
        i++;
    }
    while (i < number);

    OddEven result;
    result.odd = odd_array;
    result.odd_size = odd_index;
    result.even = even_array;
    result.even_size = even_index;

    return result;
}

GetArray multiplication(GetArray input, int number)
{
    GetArray new;
    new.count = input.count;
    new.array = malloc(new.count * sizeof(int));

    int i = 0;
    do
    {
        new.array[i] = input.array[i] * number;
        i++;
    }
    while (i < new.count);

    return new;
}

int add(GetArray input)
{
    int i = 0;
    int total = 0;
    do
    {
        if (input.array[i] / 10 != 0)
        {
            total += input.array[i] / 10 + input.array[i] % 10;
        }
        else
        {
            total += input.array[i];
        }
        i++;
    }
    while (i < input.count);

    return total;
}
