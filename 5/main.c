#include <stdio.h>

void print(char ship[3][6])
{
    for (int i = 5; i >= 0; i--)
    {
        if (ship[0][i] == ' ' && ship[1][i] == ' ' && ship[2][i] == ' ')
            continue;

        printf(" %c  %c  %c \n", ship[0][i], ship[1][i], ship[2][i]);
    }
    printf(" 1  2  3 \n\n\n");
}

void main()
{
    char ship[3][6] = {
        {'Z', 'N', ' ', ' ', ' ', ' '},
        {'M', 'C', 'D', ' ', ' ', ' '},
        {'P', ' ', ' ', ' ', ' ', ' '}};

    struct instruction
    {
        int amount;
        int from;
        int to;
    };

    struct instruction instructions[4] = {
        {1, 2, 1},
        {3, 1, 3},
        {2, 2, 1},
        {1, 1, 2},
    };

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < instructions[i].amount; j++)
        {
            char object;

            for (int k = 5; k >= 0; k--)
            {
                char current = ship[instructions[i].from - 1][k];
                if (current != ' ')
                {
                    object = current;
                    ship[instructions[i].from - 1][k] = ' ';
                    break;
                }
            }

            for (int k = 5; k >= 0; k--)
            {
                char current = ship[instructions[i].to - 1][k];
                if (current != ' ')
                {
                    ship[instructions[i].to - 1][k + 1] = object;
                    break;
                }
                else if (k == 0)
                {
                    ship[instructions[i].to - 1][k] = object;
                }
            }

            printf("Moved %c from %d to %d\n\n", object, instructions[i].from, instructions[i].to);
            print(ship);
        }
    }

    printf("Final state:\n\n");
    print(ship);
}