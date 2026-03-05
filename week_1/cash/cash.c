#include <cs50.h>
#include <stdio.h>

typedef struct
{
    int coin;
    int remain;
} CoinRemain;
CoinRemain coin_remain(int change, int cents);

int main(void)
{
    int change;
    do
    {
        change = get_int("Change owed: ");
    }
    while (change < 0);

    int coins = 0;
    int remainings = change;
    int cents_array[4] = {25, 10, 5, 1};
    int index = 0;
    CoinRemain result;

    do
    {
        result = coin_remain(remainings, cents_array[index]);
        coins += result.coin;
        remainings = result.remain;
        index++;
    }
    while (remainings != 0);

    printf("%i\n", coins);
}

CoinRemain coin_remain(int change, int cents)
{
    CoinRemain result;
    result.coin = change / cents;
    result.remain = change - result.coin * cents;
    return result;
}