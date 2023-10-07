#include <string.h>
#include <stdio.h>

void main()
{
    char *rucksacks[] = {
        "vJrwpWtwJgWrhcsFMMfFFhFp",
        "jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL",
        "PmmdzqPrVvPwwTWBwg",
        "wMqvLMZHhHMvwLHjbvcjnnSBnvTQFn",
        "ttgJtRGJQctTZtZT",
        "CrZsJsPPZsGzwwsLwLmpwMDw",
    };

    int prioritySum = 0;

    for (int i = 0; i < 6; i++)
    {
        int size = strlen(rucksacks[i]) / 2;
        char comp_1[size + 1];
        char comp_2[size + 1];

        strncpy(comp_1, rucksacks[i], size);
        comp_1[size] = '\0';

        strncpy(comp_2, rucksacks[i] + size, size);
        comp_2[size] = '\0';

        char match = 0;
        int priority = 0;

        for (int j = 0; j < size; j++)
        {
            char *result = strchr(comp_2, comp_1[j]);
            if (result != NULL)
            {
                match = comp_1[j];
                break;
            }
        }

        if (match)
        {
            if (match > 90)
            {
                priority = match - 96;
            }
            else
            {
                priority = match - 64 + 26;
            }
            prioritySum += priority;
        }

        printf("Rucksack %d contains match: %c (%d)\n", i + 1, match, priority);
    }

    printf("Priority sum: %d\n", prioritySum);
}