#include <stdio.h>
#include <string.h>

char heightmap[5][8] = {
    "Sabqponm",
    "abcryxxl",
    "accszExk",
    "acctuvwj",
    "abdefghi",
};

int visited[5][8] = {
    {1, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
};

struct coordinates
{
    int x;
    int y;
};

int travel(struct coordinates from, struct coordinates to)
{
    // bounds
    if (to.x < 0 || to.y > 7 || to.x > 4 || to.y < 0)
    {
        return 0;
    }

    // check if already visited
    if (visited[to.x][to.y] == 1)
    {
        return 0;
    }

    char curr = heightmap[to.x][to.y];
    char last = heightmap[from.x][from.y] == 'S' ? 'a' : heightmap[from.x][from.y];

    // check if step is too high
    if (curr > last + 1)
    {
        return 0;
    }

    // check if final step
    if (curr == 'E')
    {
        if (last == 'z')
        {
            return 1;
        }

        return 0;
    }

    // move was successful
    visited[to.x][to.y] = 1;

    // recursion
    struct coordinates moves[4] = {
        {to.x + 1, to.y},
        {to.x - 1, to.y},
        {to.x, to.y - 1},
        {to.x, to.y + 1},
    };

    int results[4];
    for (int i = 0; i < 4; i++)
    {
        results[i] = travel(to, moves[i]);
    }

    int max = 0;
    for (int i = 0; i < 4; i++)
    {
        if (results[i] > max)
        {
            max = results[i];
        }
    }

    int min = max;
    for (int i = 1; i < 4; i++)
    {
        if (results[i] < min && results[i] != 0)
        {
            min = results[i];
        }
    }

    if (min != 0)
    {
        return min + 1;
    }
}

void main()
{
    struct coordinates from = {0, 0};
    struct coordinates to = {0, 1};
    int result = travel(from, to);
    printf("Total moves: %d\n", result);
}