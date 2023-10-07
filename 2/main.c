#include <stdio.h>

enum Moves
{
    ROCK = 1,
    PAPER = 2,
    SCISSORS = 3
};

enum Outcomes
{
    LOSS = 0,
    DRAW = 3,
    WIN = 6
};

int game(enum Moves player, enum Moves opponent)
{
    if (player == opponent)
    {
        enum Outcomes outcome = DRAW;
        return player + outcome;
    }
    else if (player == ROCK && opponent == SCISSORS)
    {
        enum Outcomes outcome = WIN;
        return player + outcome;
    }
    else if (player == PAPER && opponent == ROCK)
    {
        enum Outcomes outcome = WIN;
        return player + outcome;
    }
    else if (player == SCISSORS && opponent == PAPER)
    {
        enum Outcomes outcome = WIN;
        return player + outcome;
    }
    else
    {
        enum Outcomes outcome = LOSS;
        return player + outcome;
    }
}

void main()
{
    int strategy[3][2] = {{ROCK, PAPER}, {PAPER, ROCK}, {SCISSORS, SCISSORS}};

    int i, score = 0;

    for (i = 0; i < 3; i++)
    {
        score += game(strategy[i][1], strategy[i][0]);
    }

    printf("Your score: %d\n", score);
}