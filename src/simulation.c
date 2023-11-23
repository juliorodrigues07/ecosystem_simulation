#include "include/simulation.h"

void move_rabbits (environment *config, cell **spaces, unsigned int g)
{
    for (int x = 0; x < config->r; x++)
    {
        for (int y = 0; y < config->c; y++)
        {
            int possible[4];
            int available = 0;
            int north = y - 1;
            int east = x + 1;
            int south = y + 1;
            int west = x - 1;

            if (config->spaces[x][y].type == 2)
            {
                if (0 <= north < config->r && config->spaces[x][north].type == 0)
                    available++;
                if (0 <= east < config->c && config->spaces[east][y].type == 0)
                    available++;
                if (0 <= south < config->r && config->spaces[x][south].type == 0)
                    available++;
                if (0 <= west < config->c && config->spaces[west][y].type == 0)
                    available++;
            }

            if (available > 0)
            {
                int next_cell = (g + x + y) % available;
                switch (next_cell)
                {
                    case 0:
                        spaces[x][north].type = config->spaces[x][y].type;
                        spaces[x][north].age_rabbit = config->spaces[x][y].age_rabbit;
                        break;
                    case 1:
                        spaces[east][y].type = config->spaces[x][y].type;
                        spaces[east][y].age_rabbit = config->spaces[x][y].age_rabbit;
                        break;
                    case 2:
                        spaces[x][south].type = config->spaces[x][y].type;
                        spaces[x][south].age_rabbit = config->spaces[x][y].age_rabbit;
                        break;
                    case 3:
                        spaces[west][y].type = config->spaces[x][y].type;
                        spaces[west][y].age_rabbit = config->spaces[x][y].age_rabbit;
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