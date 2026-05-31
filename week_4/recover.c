#include <cs50.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Accept a single command-line argument;
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open the memory card
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("The file cannot be read probably.\n");
        return 1;
    }

    // Create a buffer for a block of data
    uint8_t buffer[512];
    int count = 0, pivot = 0;
    FILE *img = NULL;
    // here we initialize the filename where 8 characters also include the final null value
    char filename[8];

    // While there's still data left to read from the memroy card
    while (fread(&buffer, 1, 512, card) == 512)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            if (count)
            {
                fclose(img);
            }
            sprintf(filename, "%03i.jpg", count);
            img = fopen(filename, "w");
            count++;
        }

        // here we check whether we get the first one
        if (count)
        {
            fwrite(&buffer, 1, 512, img);
        }
    }
    fclose(img);
    fclose(card);
}

//             count++;
//             sprintf(filename, "%03i.jpg", count);
//             printf("%s\n", filename);
//             img = fopen(filename, "w");
//             fwrite(&buffer, 1, 512, img);
//             fclose(img);
//         }
//     }
//     fclose(card);
//     return 0;
// }
