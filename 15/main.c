#include <stdio.h>
#include <stdlib.h>

#define MARGIN 4

struct coordinates
{
    int x;
    int y;
};

struct position
{
    struct coordinates sensor;
    struct coordinates beacon;
};

struct position positions[] = {
    {{2, 18}, {-2, 15}},
    {{9, 16}, {10, 16}},
    {{13, 2}, {15, 3}},
    {{12, 14}, {10, 16}},
    {{10, 20}, {10, 16}},
    {{14, 17}, {10, 16}},
    {{8, 7}, {2, 10}},
    {{2, 0}, {2, 10}},
    {{0, 11}, {2, 10}},
    {{20, 14}, {25, 17}},
    {{17, 20}, {21, 22}},
    {{16, 7}, {15, 3}},
    {{14, 3}, {15, 3}},
    {{20, 1}, {15, 3}},
};

void main(int argc, char *argv[])
{
    int min_x = 0;
    int max_x = 0;
    int min_y = 0;
    int max_y = 0;

    for (int i = 0; i < 14; i++)
    {
        struct position *loc = &positions[i];
        if (loc->sensor.x < min_x)
        {
            min_x = loc->sensor.x;
        }

        if (loc->beacon.x < min_x)
        {
            min_x = loc->beacon.x;
        }

        if (loc->sensor.x > max_x)
        {
            max_x = loc->sensor.x;
        }

        if (loc->beacon.x > max_x)
        {
            max_x = loc->beacon.x;
        }

        if (loc->sensor.y < min_y)
        {
            min_y = loc->sensor.y;
        }

        if (loc->beacon.y < min_y)
        {
            min_y = loc->beacon.y;
        }

        if (loc->sensor.y > max_y)
        {
            max_y = loc->sensor.y;
        }

        if (loc->beacon.y > max_y)
        {
            max_y = loc->beacon.y;
        }
    }

    int width = max_x - min_x + (2 * MARGIN);
    int height = max_y - min_y + (2 * MARGIN);

    printf("Max x: %d\n", max_x);
    printf("Min x: %d\n", min_x);
    printf("Max y: %d\n", max_y);
    printf("Min y: %d\n", min_y);
    printf("Width: %d\n", width);
    printf("Height: %d\n", height);

    char grid[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            grid[i][j] = '.';
        }
    }

    for (int i = 0; i < 14; i++)
    {
        struct position *loc = &positions[i];
        grid[loc->sensor.y - min_y + MARGIN][loc->sensor.x - min_x + MARGIN] = 'S';
        grid[loc->beacon.y - min_y + MARGIN][loc->beacon.x - min_x + MARGIN] = 'B';
    }

    for (int i = 0; i < 14; i++)
    {
        struct position *loc = &positions[i];
        int x, y;

        if (loc->sensor.x > loc->beacon.x)
        {
            x = loc->sensor.x - loc->beacon.x;
        }
        else
        {
            x = loc->beacon.x - loc->sensor.x;
        }

        if (loc->sensor.y > loc->beacon.y)
        {
            y = loc->sensor.y - loc->beacon.y;
        }
        else
        {
            y = loc->beacon.y - loc->sensor.y;
        }

        int distance = x + y;
        struct coordinates *sensor = &loc->sensor;

        for (int j = 0; j <= distance; j++)
        {
            for (int k = distance - j; k >= 0; k--)
            {
                int pos_jx = sensor->x - min_x + j + MARGIN;
                int neg_jx = sensor->x - min_x - j + MARGIN;
                int pos_jy = sensor->y - min_y + j + MARGIN;
                int neg_jy = sensor->y - min_y - j + MARGIN;
                int pos_kx = sensor->x - min_y + k + MARGIN;
                int neg_kx = sensor->x - min_y - k + MARGIN;
                int pos_ky = sensor->y - min_y + k + MARGIN;
                int neg_ky = sensor->y - min_y - k + MARGIN;

                if (pos_jx > height)
                    pos_jx = height - 1;
                if (neg_jx < 0)
                    neg_jx = 0;
                if (pos_jy > width)
                    pos_jy = width - 1;
                if (neg_jy < 0)
                    neg_jy = 0;
                if (pos_kx > height)
                    pos_kx = height - 1;
                if (neg_kx < 0)
                    neg_kx = 0;
                if (pos_ky > width)
                    pos_ky = width - 1;
                if (neg_ky < 0)
                    neg_ky = 0;

                if (grid[pos_jx][pos_ky] == '.')
                {
                    grid[pos_jx][pos_ky] = '#';
                }
                if (grid[neg_jx][neg_ky] == '.')
                {
                    grid[neg_jx][neg_ky] = '#';
                }
                if (grid[pos_jx][neg_ky] == '.')
                {
                    grid[pos_jx][neg_ky] = '#';
                }
                if (grid[neg_jx][pos_ky] == '.')
                {
                    grid[neg_jx][pos_ky] = '#';
                }
            }
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width + 1; j++)
        {
            printf("%c", grid[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    int cannot = 0;
    int row = atoi(argv[1]) - min_y + MARGIN;
    for (int i = 0; i < width; i++)
    {
        if (grid[row][i] == '#')
        {
            cannot++;
        }
    }

    printf("Row %s has %d positions where a Beacon cannot be present!\n", argv[1], cannot);
}