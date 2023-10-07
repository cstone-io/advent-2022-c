#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

struct coordinates
{
    int x;
    int y;
};

struct coordinates paths[2][4] = {
    {
        {498, 4},
        {498, 6},
        {496, 6},
    },
    {
        {503, 4},
        {502, 4},
        {502, 9},
        {494, 9},
    },
};

struct coordinates hole = {500, 0};

const char ROCK = '#';
const char SAND = 'o';
const char AIR = '.';
const char HOLE = '+';
const char FLOW = '~';

void display(struct coordinates rocks[], int numRocks, struct coordinates sand[], int numSand)
{
    for (int y = 0; y < 10; y++)
    {
        for (int x = 494; x < 504; x++)
        {
            if (x == hole.x && y == hole.y)
            {
                printf("%c", HOLE);
                continue;
            }

            bool isRock = false;
            for (int i = 0; i < numRocks; i++)
            {
                if (x == rocks[i].x && y == rocks[i].y)
                {
                    printf("%c", ROCK);
                    isRock = true;
                    break;
                }
            }

            if (isRock)
            {
                continue;
            }

            bool isSand = false;
            for (int i = 0; i < numSand; i++)
            {
                if (x == sand[i].x && y == sand[i].y)
                {
                    printf("%c", SAND);
                    isSand = true;
                    break;
                }
            }

            if (isSand)
            {
                continue;
            }

            printf("%c", AIR);
        }
        printf("\n");
    }
    printf("\n");
}

void main()
{
    struct coordinates *rocks = (struct coordinates *)malloc(sizeof(struct coordinates));
    int numRocks = 0;

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2 + i; j++)
        {
            int delta_x, delta_y;
            bool pos_x, pos_y;

            if (paths[i][j + 1].x > paths[i][j].x)
            {
                pos_x = true;
                delta_x = paths[i][j + 1].x - paths[i][j].x;
            }
            else
            {
                pos_x = false;
                delta_x = paths[i][j].x - paths[i][j + 1].x;
            }

            if (paths[i][j + 1].y > paths[i][j].y)
            {
                pos_y = true;
                delta_y = paths[i][j + 1].y - paths[i][j].y;
            }
            else
            {
                pos_y = false;
                delta_y = paths[i][j].y - paths[i][j + 1].y;
            }

            if (delta_x > delta_y)
            {
                if (pos_x)
                {
                    for (int k = paths[i][j].x; k < paths[i][j + 1].x + 1; k++)
                    {
                        numRocks++;
                        rocks = (struct coordinates *)realloc(rocks, numRocks * sizeof(struct coordinates));
                        rocks[numRocks - 1] = (struct coordinates){k, paths[i][j].y};
                    }
                }
                else
                {
                    for (int k = paths[i][j + 1].x; k < paths[i][j].x + 1; k++)
                    {
                        numRocks++;
                        rocks = (struct coordinates *)realloc(rocks, numRocks * sizeof(struct coordinates));
                        rocks[numRocks - 1] = (struct coordinates){k, paths[i][j].y};
                    }
                }
            }
            else
            {
                if (pos_y)
                {
                    for (int k = paths[i][j].y; k < paths[i][j + 1].y + 1; k++)
                    {
                        numRocks++;
                        rocks = (struct coordinates *)realloc(rocks, numRocks * sizeof(struct coordinates));
                        rocks[numRocks - 1] = (struct coordinates){paths[i][j].x, k};
                    }
                }
                else
                {
                    for (int k = paths[i][j + 1].y; k < paths[i][j].y + 1; k++)
                    {
                        numRocks++;
                        rocks = (struct coordinates *)realloc(rocks, numRocks * sizeof(struct coordinates));
                        rocks[numRocks - 1] = (struct coordinates){paths[i][j].x, k};
                    }
                }
            }
        }
    }

    struct coordinates *sand = (struct coordinates *)malloc(sizeof(struct coordinates));
    int numSand = 0;
    display(rocks, numRocks, sand, numSand);

    bool done = false;
    while (!done)
    {
        struct coordinates newSand = {500, 0};

        bool settled = false;
        while (!settled)
        {
            if (newSand.x == 493)
            {
                done = true;
                break;
            }

            bool down = true;
            bool downLeft = true;
            bool downRight = true;

            for (int i = 0; i < numRocks; i++)
            {
                if (newSand.x == rocks[i].x && newSand.y + 1 == rocks[i].y)
                {
                    down = false;
                }
                else if (newSand.x - 1 == rocks[i].x && newSand.y + 1 == rocks[i].y)
                {
                    downLeft = false;
                }
                else if (newSand.x + 1 == rocks[i].x && newSand.y + 1 == rocks[i].y)
                {
                    downRight = false;
                }
            }

            for (int i = 0; i < numSand; i++)
            {
                if (newSand.x == sand[i].x && newSand.y + 1 == sand[i].y)
                {
                    down = false;
                }
                else if (newSand.x - 1 == sand[i].x && newSand.y + 1 == sand[i].y)
                {
                    downLeft = false;
                }
                else if (newSand.x + 1 == sand[i].x && newSand.y + 1 == sand[i].y)
                {
                    downRight = false;
                }
            }

            if (down)
            {
                newSand.y++;
            }
            else if (downLeft)
            {
                newSand.x--;
                newSand.y++;
            }
            else if (downRight)
            {
                newSand.x++;
                newSand.y++;
            }
            else
            {
                settled = true;
            }
        }
        numSand++;
        sand = (struct coordinates *)realloc(sand, numSand * sizeof(struct coordinates));
        sand[numSand - 1] = (struct coordinates){newSand.x, newSand.y};

        display(rocks, numRocks, sand, numSand);
        usleep(500 * 1000);
    }

    free(rocks);
}