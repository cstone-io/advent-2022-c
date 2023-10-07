#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void main()
{
    char *signals[] = {
        "bvwbjplbgvbhsrlpgdmjqwftvncz",
        "nppdvjthqldpwncqszvftbrmjlhg",
        "nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg",
        "zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw"};

    for (int i = 0; i < 4; i++)
    {
        int length = strlen(signals[i]);

        for (int j = 0; j < length; j++)
        {
            bool complete = false;
            char buffer[5] = {"----"};

            for (int index = 3; index >= 0; index--)
            {
                char current = signals[i][j + index];
                char *result = strchr(buffer, current);
                buffer[index] = current;

                if (result != NULL)
                {
                    memset(buffer, 0, sizeof(buffer));
                    index = 3;
                    break;
                }
                else if (index == 0)
                {
                    complete = true;
                    break;
                }
            }

            if (complete)
            {
                printf("Marker detected: %s\n", buffer);
                printf("First marker after character %d\n", j + 4);
                break;
            }
        }
    }
}