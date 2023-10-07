#include <stdio.h>
#include <stdbool.h>

void main()
{
    int forest[5][5] = {
        {3, 0, 3, 7, 3},
        {2, 5, 5, 1, 2},
        {6, 5, 3, 3, 2},
        {3, 3, 5, 4, 9},
        {3, 5, 3, 9, 0},
    };

    int visible = 16;

    for (int i = 1; i < 4; i++)
    {
        for (int j = 1; j < 4; j++)
        {
            int tree = forest[i][j];
            printf("\nAnalyzing Tree of size %d at (%d, %d)\n", tree, i, j);
            bool complete = false;

            // top
            printf("Checking top\n");
            for (int k = i - 1; k >= 0; k--)
            {
                int max = 0;
                int current = forest[k][j];
                printf("Checking against tree of size %d at (%d, %d)\n", current, k, j);

                if (current > max)
                {
                    max = current;
                }

                if (max >= tree)
                {
                    printf("This tree is blocking the view\n");
                    break;
                }

                if (k == 0)
                {
                    complete = true;
                }
            }

            if (complete)
            {
                visible++;
                printf("This Tree is visible!\n");
                printf("Current visibility count: %d\n", visible);
                continue;
            }

            // right
            printf("Checking right\n");
            for (int k = j + 1; k < 5; k++)
            {
                int max = 0;
                int current = forest[i][k];
                printf("Checking against tree of size %d at (%d, %d)\n", current, i, k);

                if (current > max)
                {
                    max = current;
                }

                if (max >= tree)
                {
                    printf("This tree is blocking the view\n");
                    break;
                }

                if (k == 4)
                {
                    complete = true;
                }
            }

            if (complete)
            {
                visible++;
                printf("This Tree is visible!\n");
                printf("Current visibility count: %d\n", visible);
                continue;
                ;
            }

            // bottom
            printf("Checking bottom\n");
            for (int k = i + 1; k < 5; k++)
            {
                int max = 0;
                int current = forest[k][j];
                printf("Checking against tree of size %d at (%d, %d)\n", current, k, j);

                if (current > max)
                {
                    max = current;
                }

                if (max >= tree)
                {
                    printf("This tree is blocking the view\n");
                    break;
                }

                if (k == 4)
                {
                    complete = true;
                }
            }

            if (complete)
            {
                visible++;
                printf("This Tree is visible!\n");
                printf("Current visibility count: %d\n", visible);
                continue;
            }

            // left
            printf("Checking left\n");
            for (int k = j - 1; k >= 0; k--)
            {
                int max = 0;
                int current = forest[i][k];
                printf("Checking against tree of size %d at (%d, %d)\n", current, i, k);

                if (current > max)
                {
                    max = current;
                }

                if (max >= tree)
                {
                    printf("This tree is blocking the view\n");
                    break;
                }

                if (k == 0)
                {
                    complete = true;
                }
            }

            if (complete)
            {
                visible++;
                printf("This Tree is visible!\n");
                printf("Current visibility count: %d\n", visible);
                continue;
            }

            printf("This Tree is not visible from any angle...\n");
        }
    }

    printf("\nTotal visible trees: %d\n", visible);
}