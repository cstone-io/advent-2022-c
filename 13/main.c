#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

void unwrap(char *str)
{
    int length = strlen(str);
    if (length >= 2)
    {
        memmove(str, str + 1, length - 2);
        str[length - 2] = '\0';
    }
    else
    {
        str[0] = '\0';
    }
}

void wrap(char *str)
{
    int length = strlen(str);
    if (length >= 1)
    {
        memmove(str + 1, str, length);
        str[0] = '[';
        str[length + 1] = ']';
        str[length + 2] = '\0';
    }
    else
    {
        str[0] = '[';
        str[1] = ']';
        str[2] = '\0';
    }
}

enum type
{
    INTEGER,
    ARRAY,
    EMPTY,
};

enum type classify(char *str)
{
    char *post = strchr(str, ',');
    if (post == NULL)
    {
        if (strlen(str) == 1)
        {
            return INTEGER;
        }
        else
        {
            return EMPTY;
        }
    }

    int i = post - str;
    char substring[i + 1];
    strncpy(substring, str, i);
    substring[i] = '\0';

    char *check = strchr(substring, '[');
    if (check != NULL)
    {
        return ARRAY;
    }
    else
    {
        return INTEGER;
    }
}

char *extractArr(char *str)
{
    int countL = 0;
    int countR = 0;
    int i = 0;

    while (str[i] != '\0')
    {
        if (str[i] == '[')
        {
            countL++;
        }
        else if (str[i] == ']')
        {
            countR++;
        }

        if (countL == countR)
        {
            break;
        }

        i++;
    }

    char *result = malloc(i + 1);
    strncpy(result, str, i + 1);
    result[i + 1] = '\0';

    memmove(str, str + i + 2, strlen(str) - i - 1);
    str[strlen(str)] = '\0';

    if (strcmp(str, result) == 0)
    {
        str[0] = '\0';
    }

    return result;
}

int extractInt(char *str)
{
    if (strlen(str) == 1)
    {
        int result = atoi(str);
        str[0] = '\0';
        return result;
    }

    char *token = malloc(2);
    token[0] = str[0];
    token[1] = '\0';

    memmove(str, str + 2, strlen(str) - 1);
    int val = atoi(token);
    free(token);
    return val;
}

void main()
{
    char packets[][30] = {
        "[1,1,3,1,1]",
        "[1,1,5,1,1]",
        "[[1],[2,3,4]]",
        "[[1],4]",
        "[9]",
        "[[8,7,6]]",
        "[[4,4],4,4]",
        "[[4,4],4,4,4]",
        "[7,7,7,7]",
        "[7,7,7]",
        "[]",
        "[3]",
        "[[[]]]",
        "[[]]",
        "[1,[2,[3,[4,[5,6,7]]]],8,9]",
        "[1,[2,[3,[4,[5,6,0]]]],8,9]",
    };

    int sum = 0;

    for (int i = 0; i < 16; i += 2)
    {
        char *left = packets[i];
        char *right = packets[i + 1];
        printf("Raw packet pair %d: %s, %s\n", (i + 2) / 2, left, right);

        unwrap(left);
        unwrap(right);

        bool healthy = true;
        while (strlen(left) > 0)
        {
            if (classify(left) == EMPTY || classify(right) == EMPTY)
            {
                if (strlen(left) > strlen(right))
                {
                    healthy = false;
                }
                break;
            }

            int a, b;
            if (classify(left) == INTEGER && classify(right) == INTEGER)
            {
                a = extractInt(left);
                b = extractInt(right);
                if (a > b)
                {
                    healthy = false;
                    break;
                }
            }
            else if (classify(left) == INTEGER && classify(right) == ARRAY)
            {
                a = extractInt(left);
                char *subright = extractArr(right);
                unwrap(subright);
                while (classify(subright) == INTEGER)
                {
                    b = extractInt(subright);
                    if (a > b)
                    {
                        healthy = false;
                        break;
                    }
                }
                free(subright);
            }
            else if (classify(left) == ARRAY && classify(right) == INTEGER)
            {
                b = extractInt(right);
                char *subleft = extractArr(left);
                unwrap(subleft);
                while (strlen(subleft) > 0)
                {
                    a = extractInt(subleft);
                    if (a > b)
                    {
                        healthy = false;
                        break;
                    }
                }
                free(subleft);
            }
            else if (classify(left) == ARRAY && classify(right) == ARRAY)
            {
                char *subleft = extractArr(left);
                unwrap(subleft);
                a = extractInt(subleft);

                char *subright = extractArr(right);
                unwrap(subright);
                b = extractInt(subright);

                if (a > b)
                {
                    healthy = false;
                    break;
                }

                while (classify(subleft) == ARRAY && classify(subright) == ARRAY)
                {
                    subleft = extractArr(subleft);
                    unwrap(subleft);
                    a = extractInt(subleft);

                    subright = extractArr(subright);
                    unwrap(subright);
                    b = extractInt(subright);

                    if (a > b)
                    {
                        healthy = false;
                        break;
                    }
                };

                while (classify(subleft) == INTEGER && classify(subright) == INTEGER)
                {
                    a = extractInt(subleft);
                    b = extractInt(subright);
                    if (a > b)
                    {
                        healthy = false;
                        break;
                    }
                }

                free(subleft);
                free(subright);
            }
        }

        if (healthy)
        {
            int index = (i + 2) / 2;
            sum += index;
            printf("Packet pair %d is healthy!\n", index);
        }
    }

    printf("Sum of healthy packet pairs: %d\n", sum);
}