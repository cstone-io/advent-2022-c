#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ROUNDS 20

void inspect(int *item, char *operation)
{
    char copy[10];
    strcpy(copy, operation);

    char *arg1 = strtok(copy, " ");
    char *operator= strtok(NULL, " ");
    char *arg2 = strtok(NULL, " ");

    int val1, val2;

    if (strcmp(arg1, "old") == 0)
    {
        val1 = *item;
    }
    else
    {
        val1 = atoi(arg1);
    }

    if (strcmp(arg2, "old") == 0)
    {
        val2 = *item;
    }
    else
    {
        val2 = atoi(arg2);
    }

    if (strcmp(operator, "*") == 0)
    {
        *item = val1 * val2;
    }
    else if (strcmp(operator, "+") == 0)
    {
        *item = val1 + val2;
    }
    else if (strcmp(operator, "-") == 0)
    {
        *item = val1 - val2;
    }
    else if (strcmp(operator, "/") == 0)
    {
        *item = val1 / val2;
    }

    *item /= 3;
}

void bubbleSort(int arr[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                // Swap arr[j] and arr[j + 1]
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void main()
{
    struct monkey
    {
        int items[10];
        char *operation;
        int test;
        int pass;
        int fail;
        int count;
    };

    struct monkey monkeys[4] = {
        {{79, 98, 0, 0, 0, 0, 0, 0, 0, 0}, "old * 19", 23, 2, 3, 0},
        {{54, 65, 75, 74, 0, 0, 0, 0, 0, 0}, "old + 6", 19, 2, 0, 0},
        {{79, 60, 97, 0, 0, 0, 0, 0, 0, 0}, "old * old", 13, 1, 3, 0},
        {{74, 0, 0, 0, 0, 0, 0, 0, 0, 0}, "old + 3", 17, 0, 1, 0},
    };

    for (int round = 0; round < ROUNDS; round++)
    {
        for (int i = 0; i < 4; i++)
        {
            struct monkey *monkey = &monkeys[i];

            for (int j = 0; monkey->items[j] != 0; j++)
            {
                inspect(&monkey->items[j], monkey->operation);
                monkey->count++;

                int target = monkey->items[j] % monkey->test == 0 ? monkey->pass : monkey->fail;

                int k = 0;
                while (monkeys[target].items[k] != 0)
                {
                    k++;
                }

                monkeys[target].items[k] = monkey->items[j];
                monkey->items[j] = 0;
            }
        }
    }

    int buffer[4] = {0, 0, 0, 0};
    for (int i = 0; i < 4; i++)
    {
        buffer[i] = monkeys[i].count;
        printf("Monkey %d inspected %d items\n", i, buffer[i]);
    }

    bubbleSort(buffer, 4);
    int monkey_business = buffer[2] * buffer[3];
    printf("Monkey business: %d\n", monkey_business);
}