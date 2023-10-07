#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_SIZE 100000

void main()
{
    char *terminal[] = {
        "$ cd /",
        "$ ls",
        "dir a",
        "14848514 b.txt",
        "8504156 c.dat",
        "dir d",
        "$ cd a",
        "$ ls",
        "dir e",
        "29116 f",
        "2557 g",
        "62596 h.lst",
        "$ cd e",
        "$ ls",
        "584 i",
        "$ cd ..",
        "$ cd ..",
        "$ cd d",
        "$ ls",
        "4060174 j",
        "8033020 d.log",
        "5626152 d.ext",
        "7214296 k",
        NULL};

    char delimiter[] = " ";
    char cwd = '-';

    struct dir
    {
        char name;
        long size;
        char children[5];
    };

    struct dir directories[5];
    for (int i = 0; i < 5; i++)
    {
        directories[i].name = '-';
        directories[i].size = 0;
        for (int j = 0; j < 4; j++)
        {
            directories[i].children[j] = '-';
        }
    }

    for (int i = 0; terminal[i] != NULL; i++)
    {
        char line[25];
        strcpy(line, terminal[i]);

        char buffer[3][10];
        strcpy(buffer[0], strtok(line, delimiter));

        for (int j = 1; j < 3; j++)
        {
            char *token = strtok(NULL, delimiter);
            if (token != NULL)
            {
                strcpy(buffer[j], token);
            }
            else
            {
                break;
            }
        }

        if (strcmp(buffer[0], "$") == 0)
        {
            if (strcmp(buffer[1], "cd") == 0)
            {
                if (strcmp(buffer[2], "..") != 0)
                {
                    cwd = buffer[2][0];

                    int k = 0;
                    while (directories[k].name != '-')
                    {
                        k++;
                    }
                    directories[k].name = cwd;
                }
            }
        }
        else if (strcmp(buffer[0], "dir") == 0)
        {
            int a = 0;
            while (directories[a].name != cwd)
            {
                a++;
            }

            int b = 0;
            while (directories[a].children[b] != '-')
            {
                b++;
            }
            directories[a].children[b] = buffer[1][0];
        }
        else
        {
            int i = 0;
            while (directories[i].name != cwd)
            {
                i++;
            }
            directories[i].size += atoi(buffer[0]);
        }
    }

    for (int i = 0; i < 5; i++)
    {
        int j = 0;
        while (directories[i].children[j] != '-')
        {
            int k = 0;
            while (directories[k].name != directories[i].children[j])
            {
                k++;
            }
            directories[i].size += directories[k].size;
            j++;
        }
    }

    int sum = 0;
    for (int i = 0; i < 5; i++)
    {
        if (directories[i].name == '-')
        {
            continue;
        }

        if (directories[i].size <= MAX_SIZE)
        {
            printf("Directory %c has acceptable size: %ld\n", directories[i].name, directories[i].size);
            sum += directories[i].size;
        }
    }

    printf("Total size of acceptable directories: %d\n", sum);
}