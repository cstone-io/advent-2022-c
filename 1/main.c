#include <stdio.h>

void main()
{
    int calories[5][3] = {{1000, 2000, 3000}, {4000}, {5000, 6000}, {7000, 8000, 9000}, {10000}};

    int i, j, subtotal, max = 0, elf = 0;

    for (i = 0; i < 5; i++)
    {
        subtotal = 0;
        for (j = 0; j < 3; j++)
        {
            subtotal += calories[i][j];
        }
        if (subtotal > max)
        {
            max = subtotal;
            elf = i + 1;
        }
    }

    printf("Elf %d has the most calories with %d\n", elf, max);
}