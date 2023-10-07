#include <stdio.h>
#include <string.h>

void main()
{
    enum direction
    {
        UP,
        DOWN,
        LEFT,
        RIGHT,
    };

    const char *dirstr[] = {
        "UP",
        "DOWN",
        "LEFT",
        "RIGHT",
    };

    struct instruction
    {
        enum direction direction;
        int steps;
    };

    struct instruction instructions[8] = {
        {RIGHT, 4},
        {UP, 4},
        {LEFT, 3},
        {DOWN, 1},
        {RIGHT, 4},
        {DOWN, 1},
        {LEFT, 5},
        {RIGHT, 2},
    };

    struct position
    {
        int x;
        int y;
    };

    struct position head = {0, 0};
    struct position tail = {0, 0};

    int visited[5][6] = {
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
    };

    for (int i = 0; i < 8; i++)
    {
        printf("Instruction %d: %s %d\n", i + 1, dirstr[instructions[i].direction], instructions[i].steps);

        for (int j = 0; j < instructions[i].steps; j++)
        {
            switch (instructions[i].direction)
            {
            case UP:
                head.y++;
                break;
            case DOWN:
                head.y--;
                break;
            case LEFT:
                head.x--;
                break;
            case RIGHT:
                head.x++;
                break;
            }

            int delta_x = head.x - tail.x;
            int delta_y = head.y - tail.y;

            if (delta_x > 1)
            {
                if (delta_y != 0)
                {
                    tail.y = head.y;
                }
                tail.x++;
            }
            else if (delta_x < -1)
            {
                if (delta_y != 0)
                {
                    tail.y = head.y;
                }
                tail.x--;
            }
            else if (delta_y > 1)
            {
                if (delta_x != 0)
                {
                    tail.x = head.x;
                }
                tail.y++;
            }
            else if (delta_y < -1)
            {
                if (delta_x != 0)
                {
                    tail.x = head.x;
                }
                tail.y--;
            }

            if (!visited[tail.y][tail.x])
            {
                visited[tail.y][tail.x] = 1;
            }

            for (int k = 4; k >= 0; k--)
            {
                for (int l = 0; l < 6; l++)
                {
                    if (k == head.y && l == head.x)
                    {
                        printf("H");
                    }
                    else if (k == tail.y && l == tail.x)
                    {
                        printf("T");
                    }
                    else
                    {
                        printf(".");
                    }
                }
                printf("\n");
            }
            printf("\n");
        }
    }

    int sum = 0;

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            sum += visited[i][j];
        }
    }

    printf("Total unique positions visited: %d\n", sum);
}