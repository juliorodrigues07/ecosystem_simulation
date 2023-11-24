#include "include/simulation.h"

void enumerate_positions (int *adj, int value) 
{
    for (int i = 0; i < 4; i++) 
    {
        if (adj[i] == -1) 
        {
            adj[i] = value;
            break;
        }
    }
}

void move_rabbits (environment *config, cell **spaces, unsigned int g)
{
    int available;
    int north, south, east, west;

    for (int x = 0; x < config->r; x++)
    {
        north = x - 1;
        south = x + 1;

        for (int y = 0; y < config->c; y++)
        {
            int possible[] = {-1, -1, -1, -1};
            available = 0;
            east = y + 1;
            west = y - 1;

            if (config->spaces[x][y].type == 2)
            {
                if (north >= 0 && north < config->r && config->spaces[north][y].type == 0)
                {
                    enumerate_positions(possible, 0);
                    available++;
                }
                if (east >= 0 && east < config->c && config->spaces[x][east].type == 0)
                {
                    enumerate_positions(possible, 1);
                    available++;
                }
                if (south >= 0 && south < config->r && config->spaces[south][y].type == 0)
                {
                    enumerate_positions(possible, 2);
                    available++;
                }
                if (west >= 0 && west < config->c && config->spaces[x][west].type == 0){
                    enumerate_positions(possible, 3);
                    available++;
                }
            }

            if (available > 0)
            {
                int index = (g + x + y) % available;
                int next_cell = possible[index];
                switch (next_cell)
                {
                    case 0:
                        spaces[north][y].type = config->spaces[x][y].type;
                        if (config->spaces[x][y].age_rabbit == config->rabbit_gen)
                            spaces[north][y].age_rabbit = -1;
                        else
                            spaces[north][y].age_rabbit = MIN(spaces[north][y].age_rabbit, config->spaces[x][y].age_rabbit);
                        break;
                    case 1:
                        spaces[x][east].type = config->spaces[x][y].type;
                        if (config->spaces[x][y].age_rabbit == config->rabbit_gen)
                            spaces[x][east].age_rabbit = -1;
                        else
                            spaces[x][east].age_rabbit = MIN(spaces[x][east].age_rabbit, config->spaces[x][y].age_rabbit);
                        break;
                    case 2:
                        spaces[south][y].type = config->spaces[x][y].type;
                        if (config->spaces[x][y].age_rabbit == config->rabbit_gen)
                            spaces[south][y].age_rabbit = -1;
                        else
                            spaces[south][y].age_rabbit = MIN(spaces[south][y].age_rabbit, config->spaces[x][y].age_rabbit);
                        break;
                    case 3:
                        spaces[x][west].type = config->spaces[x][y].type;
                        if (config->spaces[x][y].age_rabbit == config->rabbit_gen)
                            spaces[x][west].age_rabbit = -1;
                        else
                            spaces[x][west].age_rabbit = MIN(spaces[x][west].age_rabbit, config->spaces[x][y].age_rabbit);
                        break;
                    default:
                        break;
                }

                switch (next_cell) {
                    case 0:
                    case 1:
                    case 2:
                    case 3:
                        if (config->spaces[x][y].age_rabbit == config->rabbit_gen)
                        {
                            spaces[x][y].age_rabbit = -1;
                            spaces[x][y].type = 2;
                        }
                        else
                        {
                            spaces[x][y].type = 0;
                            spaces[x][y].age_rabbit = INT_MAX;
                        }
                        break;
                    default:
                        break;
                }
            }
        }
    }
}

void copy_state (environment *config, cell **spaces)
{
    for (int i = 0; i < config->r; i++)
    {
        for (int j = 0; j < config->c; j++)
        {
            if (config->spaces[i][j].type == 2)
                spaces[i][j].age_rabbit = config->spaces[i][j].age_rabbit;
            else if (config->spaces[i][j].type == 1)
            {
                spaces[i][j].age_fox = config->spaces[i][j].age_fox;
                spaces[i][j].hunger_fox = config->spaces[i][j].hunger_fox;
            }
            else if (config->spaces[i][j].type == 0 || config->spaces[i][j].type == -1)
            {
                spaces[i][j].age_rabbit = INT_MAX;
                spaces[i][j].age_fox = INT_MAX;
                spaces[i][j].hunger_fox = INT_MAX;
            }
            spaces[i][j].type = config->spaces[i][j].type;
        }
    }
}

void update_state (environment *config, cell **spaces)
{
    for (int i = 0; i < config->r; i++)
    {
        for (int j = 0; j < config->c; j++)
        {
            if (spaces[i][j].type == 2)
            {
                config->spaces[i][j].age_rabbit = spaces[i][j].age_rabbit;
                config->spaces[i][j].hunger_fox = INT_MAX;
            }
            else if (spaces[i][j].type == 1)
            {
                config->spaces[i][j].age_fox = spaces[i][j].age_fox;
                config->spaces[i][j].hunger_fox = spaces[i][j].hunger_fox;
            }
            else if (spaces[i][j].type == 0)
            {
                config->spaces[i][j].age_rabbit = INT_MAX;
                config->spaces[i][j].age_fox = INT_MAX;
                config->spaces[i][j].hunger_fox = INT_MAX;
            }
            config->spaces[i][j].type = spaces[i][j].type;
        }
    }
    printf("\n");
}

void evolve_system (environment *config)
{
    for (int i = 0; i < config->r; i++)
    {
        for (int j = 0; j < config->c; j++)
        {
            if (config->spaces[i][j].type == 2)
                config->spaces[i][j].age_rabbit++;
            else if (config->spaces[i][j].type == 1) {
                config->spaces[i][j].age_fox++;
                config->spaces[i][j].hunger_fox++;
            }
        }
    }
}

void print_limits (int n)
{
    for (int i = 0; i < n; i++)
        printf("-");
    printf("\n");
}

void print_state (environment *config, int gen)
{
    int object;
    int header = 2 * config->c + 3;

    printf("Gen %d\n", gen);
    print_limits(header);

    for (int x = 0; x < config->r; x++)
    {
        printf("| ");
        for (int y = 0; y < config->c; y++)
        {
            object = config->spaces[x][y].type;
            switch (object)
            {
                case -1:
                    printf("* ");
                    break;
                case 0:
                    printf("  ");
                    break;
                case 1:
                    printf("R ");
                    break;
                case 2:
                    printf("C ");
                    break;
                default:
                    break;
            }
        }
        printf("|\n");
    }
    print_limits(header);
}