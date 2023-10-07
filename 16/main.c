#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct valve
{
    char name[3];
    int flow_rate;
    char tunnels[3][3];
    bool open;
};

struct node
{
    struct node *parent;

    struct valve *valve;

    struct node *left;
    struct node *middle;
    struct node *right;
};

struct valve *build_valves(char *scan[])
{
    struct valve *valves = malloc(10 * sizeof(struct valve));
    for (int i = 0; i < 10; i++)
    {
        struct valve valve;

        char *string = strdup(scan[i]);
        char *token = strtok(string, " "); // Valve
        token = strtok(NULL, " ");         // [NAME]
        valve.name[0] = token[0];
        valve.name[1] = token[1];
        valve.name[2] = '\0';

        token = strtok(NULL, " "); // has
        token = strtok(NULL, " "); // flow
        token = strtok(NULL, " "); // rate=[RATE];
        char *rate = strdup(token);
        int start = strlen("rate=");
        int end = strlen(token) - 1;
        rate = rate + start;
        rate[end] = '\0';
        valve.flow_rate = atoi(rate);

        token = strtok(NULL, " "); // tunnels
        token = strtok(NULL, " "); // lead
        token = strtok(NULL, " "); // to
        token = strtok(NULL, " "); // valves

        for (int j = 0; j < 3; j++)
        {
            token = strtok(NULL, " "); // [NAME]

            if (token == NULL)
            {
                valve.tunnels[j][0] = '\0';
                valve.tunnels[j][1] = '\0';
                valve.tunnels[j][2] = '\0';
                continue;
            }

            valve.tunnels[j][0] = token[0];
            valve.tunnels[j][1] = token[1];
            valve.tunnels[j][2] = '\0';
        }

        valve.open = false;

        valves[i] = valve;
    }
    return valves;
}

void print_valves(struct valve vavles[])
{
    printf("Rendering valves...\n");
    for (int i = 0; i < 10; i++)
    {
        struct valve valve = vavles[i];
        printf("== Valve %s ==\n", valve.name);
        printf("Flow rate: %d\n", valve.flow_rate);
        printf("Tunnels: %s", valve.tunnels[0]);
        if (valve.tunnels[1][0] != '\0')
        {
            printf(", %s", valve.tunnels[1]);
        }
        if (valve.tunnels[2][0] != '\0')
        {
            printf(", %s", valve.tunnels[2]);
        }
        printf("\n\n");
    }
}

struct valve *find_valve(struct valve valves[], char *name)
{
    if (name[0] == '\0')
    {
        return NULL;
    }

    for (int i = 0; i < 10; i++)
    {
        struct valve *curr = &valves[i];
        if (strcmp(curr->name, name) == 0)
        {
            return curr;
        }
    }
    return NULL;
}

struct valve *copy_valve(const struct valve *original)
{
    if (original == NULL)
    {
        return NULL;
    }

    // Allocate memory for the new valve
    struct valve *copy = malloc(sizeof(struct valve));
    if (copy == NULL)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        return NULL;
    }

    // Copy individual elements of the original valve to the new copy
    strncpy(copy->name, original->name, sizeof(original->name) - 1);
    copy->name[sizeof(original->name) - 1] = '\0';
    copy->flow_rate = original->flow_rate;
    memcpy(copy->tunnels, original->tunnels, sizeof(original->tunnels));
    copy->open = original->open;

    return copy;
}

struct valve *copy_valve_array(struct valve original[], struct valve *replacement)
{
    if (original == NULL)
    {
        return NULL;
    }

    // Allocate memory for the new valve array
    struct valve *copy = malloc(10 * sizeof(struct valve));
    if (copy == NULL)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        return NULL;
    }

    // Copy each individual valve element to the new array
    for (int i = 0; i < 10; i++)
    {
        if (strcmp(original[i].name, replacement->name) == 0)
        {
            strncpy(copy[i].name, replacement->name, sizeof(replacement->name) - 1);
            copy[i].name[sizeof(replacement->name) - 1] = '\0';
            copy[i].flow_rate = replacement->flow_rate;
            memcpy(copy[i].tunnels, replacement->tunnels, sizeof(replacement->tunnels));
            copy[i].open = replacement->open;
            continue;
        }

        strncpy(copy[i].name, original[i].name, sizeof(original[i].name) - 1);
        copy[i].name[sizeof(original[i].name) - 1] = '\0';
        copy[i].flow_rate = original[i].flow_rate;
        memcpy(copy[i].tunnels, original[i].tunnels, sizeof(original[i].tunnels));
        copy[i].open = original[i].open;
    }

    return copy;
}

bool node_exists(struct node *node, struct valve *valve)
{
    while (node != NULL)
    {
        if (strcmp(node->valve->name, valve->name) == 0)
        {
            return true;
        }
        node = node->parent;
    }

    return false;
}

struct node *build_tree(struct valve valves[], struct valve *valve, struct node *parent)
{
    struct node *node = malloc(sizeof(struct node));
    node->parent = parent;
    node->valve = valve;
    node->left = NULL;
    node->middle = NULL;
    node->right = NULL;

    struct valve *left = find_valve(valves, valve->tunnels[0]);
    bool left_exists = node_exists(node, left);
    if (left != NULL && !left_exists)
    {
        node->left = build_tree(valves, left, node);
    }

    if (strcmp(valve->tunnels[1], "") != 0)
    {
        struct valve *middle = find_valve(valves, valve->tunnels[1]);
        bool middle_exists = node_exists(node, middle);
        if (middle != NULL && !middle_exists)
        {
            node->middle = build_tree(valves, middle, node);
        }
    }

    if (strcmp(valve->tunnels[2], "") != 0)
    {
        struct valve *right = find_valve(valves, valve->tunnels[2]);
        bool right_exists = node_exists(node, right);
        if (right != NULL && !right_exists)
        {
            node->right = build_tree(valves, right, node);
        }
    }

    return node;
}

void free_tree(struct node *node)
{
    if (node == NULL)
    {
        return;
    }

    free_tree(node->left);
    free_tree(node->middle);
    free_tree(node->right);

    free(node);
}

int solve(struct node *node, int time)
{
    if (node == NULL || time < 2)
    {
        return 0;
    }

    printf("== Minute %d ==\n", time);

    int flows[3] = {0, 0, 0};

    if (node->left != NULL)
    {
        if (node->left->valve->open)
        {
            printf("Moving to valve %s\n", node->left->valve->name);
            flows[0] = solve(node->left, time - 1);
        }
        else
        {
            printf("Moving to and opening valve %s\n", node->left->valve->name);
            node->left->valve->open = true;
            flows[0] = solve(node->left, time - 2) + node->left->valve->flow_rate * (time - 2);
        }
    }

    if (node->middle != NULL)
    {
        if (node->middle->valve->open)
        {
            printf("Moving to valve %s\n", node->middle->valve->name);
            flows[1] = solve(node->middle, time - 1);
        }
        else
        {
            printf("Moving to and opening valve %s\n", node->middle->valve->name);
            node->middle->valve->open = true;
            flows[1] = solve(node->middle, time - 2) + node->middle->valve->flow_rate * (time - 2);
        }
    }

    if (node->right != NULL)
    {
        if (node->right->valve->open)
        {
            printf("Moving to valve %s\n", node->right->valve->name);
            flows[2] = solve(node->right, time - 1);
        }
        else
        {
            printf("Moving to and opening valve %s\n", node->right->valve->name);
            node->right->valve->open = true;
            flows[2] = solve(node->right, time - 2) + node->right->valve->flow_rate * (time - 2);
        }
    }

    int max = 0;
    for (int i = 0; i < 3; i++)
    {
        if (flows[i] > max)
        {
            max = flows[i];
        }
    }
    return max;

    printf("\n");
}

int solve2(struct valve valves[], struct valve *valve, int time)
{
    if (time <= 0)
    {
        return 0;
    }

    int flows[3] = {0, 0, 0};

    if (strcmp(valve->tunnels[0], "") != 0)
    {
        struct valve *left = find_valve(valves, valve->tunnels[0]);

        if (left->open)
        {
            flows[0] = solve2(valves, left, time - 1);
        }
        else
        {
            int flow1 = solve2(valves, left, time - 1);

            struct valve *left_copy = copy_valve(left);
            left_copy->open = true;

            struct valve *valves_copy = copy_valve_array(valves, left_copy);
            int flow2 = solve2(valves_copy, left_copy, time - 2) + left_copy->flow_rate * (time - 2);

            free(left_copy);
            free(valves_copy);

            flows[0] = flow1 > flow2 ? flow1 : flow2;
        }
    }

    if (strcmp(valve->tunnels[1], "") != 0)
    {
        struct valve *middle = find_valve(valves, valve->tunnels[1]);

        if (middle->open)
        {
            flows[1] = solve2(valves, middle, time - 1);
        }
        else
        {
            int flow1 = solve2(valves, middle, time - 1);

            struct valve *middle_copy = copy_valve(middle);
            middle_copy->open = true;

            struct valve *valves_copy = copy_valve_array(valves, middle_copy);
            int flow2 = solve2(valves_copy, middle_copy, time - 2) + middle_copy->flow_rate * (time - 2);

            free(middle_copy);
            free(valves_copy);

            flows[1] = flow1 > flow2 ? flow1 : flow2;
        }
    }

    if (strcmp(valve->tunnels[2], "") != 0)
    {
        struct valve *right = find_valve(valves, valve->tunnels[2]);

        if (right->open)
        {
            flows[2] = solve2(valves, right, time - 1);
        }
        else
        {
            int flow1 = solve2(valves, right, time - 1);

            struct valve *right_copy = copy_valve(right);
            right_copy->open = true;

            struct valve *valves_copy = copy_valve_array(valves, right_copy);
            int flow2 = solve2(valves_copy, right_copy, time - 2) + right_copy->flow_rate * (time - 2);

            free(right_copy);
            free(valves_copy);

            flows[2] = flow1 > flow2 ? flow1 : flow2;
        }
    }

    int max = 0;
    for (int i = 0; i < 3; i++)
    {
        if (flows[i] > max)
        {
            max = flows[i];
        }
    }

    return max;
}

void main()
{
    char *scan[] = {
        "Valve AA has flow rate=0; tunnels lead to valves DD, II, BB",
        "Valve BB has flow rate=13; tunnels lead to valves CC, AA",
        "Valve CC has flow rate=2; tunnels lead to valves DD, BB",
        "Valve DD has flow rate=20; tunnels lead to valves CC, AA, EE",
        "Valve EE has flow rate=3; tunnels lead to valves FF, DD",
        "Valve FF has flow rate=0; tunnels lead to valves EE, GG",
        "Valve GG has flow rate=0; tunnels lead to valves FF, HH",
        "Valve HH has flow rate=22; tunnel leads to valve GG",
        "Valve II has flow rate=0; tunnels lead to valves AA, JJ",
        "Valve JJ has flow rate=21; tunnel leads to valve II",
    };

    struct valve *valves = build_valves(scan);
    print_valves(valves);

    struct node *root = build_tree(valves, &valves[0], NULL);

    // int result = solve(root, 30);
    int result = solve2(valves, &valves[0], 30);
    printf("Result: %d\n", result);

    free_tree(root);
    free(valves);
}