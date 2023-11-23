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
                        spaces[north][y].age_rabbit = config->spaces[x][y].age_rabbit;
                        spaces[x][y].type = 0;
                        break;
                    case 1:
                        spaces[x][east].type = config->spaces[x][y].type;
                        spaces[x][east].age_rabbit = config->spaces[x][y].age_rabbit;
                        spaces[x][y].type = 0;
                        break;
                    case 2:
                        spaces[south][y].type = config->spaces[x][y].type;
                        spaces[south][y].age_rabbit = config->spaces[x][y].age_rabbit;
                        spaces[x][y].type = 0;
                        break;
                    case 3:
                        spaces[x][west].type = config->spaces[x][y].type;
                        spaces[x][west].age_rabbit = config->spaces[x][y].age_rabbit;
                        spaces[x][y].type = 0;
                        break;
                    default:
                        break;
                }
            }
        }
    }
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

void update_state (environment *config, cell **spaces)
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
            spaces[i][j].type = config->spaces[i][j].type;
        }
    }
}