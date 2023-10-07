#include <stdbool.h>
#include <stdio.h>

void main()
{
    int assignments[6][2][2] = {
        {{2, 4}, {6, 8}},
        {{2, 3}, {4, 5}},
        {{5, 7}, {7, 9}},
        {{2, 8}, {3, 7}},
        {{6, 6}, {4, 6}},
        {{2, 6}, {4, 8}}};

    int total = 0;

    for (int i = 0; i < 6; i++)
    {
        int elf_1[2] = {assignments[i][0][0], assignments[i][0][1]};
        int elf_2[2] = {assignments[i][1][0], assignments[i][1][1]};
        bool match = false;

        if (elf_1[0] <= elf_2[0])
        {
            if (elf_1[1] >= elf_2[1])
            {
                match = true;
            }
        }
        else if (elf_2[0] <= elf_1[0])
        {
            if (elf_2[1] >= elf_1[1])
            {
                match = true;
            }
        }

        if (match)
        {
            printf("Match found for pair %d\n", i + 1);
            total++;
        }
    }

    printf("Total matches: %d\n", total);
}