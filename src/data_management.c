#include "include/data_management.h"
#include "include/common.h"

environment *read_input_file (char *file_name)
{
    FILE *input_file = fopen(file_name, "r");
    if (input_file == NULL)
    {
        printf("Failed opening file\n");
        exit(EXIT_FAILURE);
    }

    environment *config = (environment *) malloc (1 * sizeof(environment));
    fscanf(input_file, "%u %u %u %u %u %u %u\n", &config->rabbit_gen, &config->fox_gen, &config->fox_food, &config->n_gen, &config->r, &config->c, &config->n);

    config->spaces = (cell **) malloc (config->r * sizeof(cell *));
    for (int i = 0; i < config->r; i++)
        config->spaces[i] = (cell *) malloc (config->c * sizeof(cell));

    char object[6];
    unsigned int x, y;
    while (fscanf(input_file, "%s %u %u\n", object, &x, &y) != EOF)
    {
        if (!strcmp("COELHO", object)) {
            config->spaces[x][y].type = 2;
            config->spaces[x][y].age_rabbit = 0;
        }
        else if (!strcmp("RAPOSA", object)) {
            config->spaces[x][y].type = 1;
            config->spaces[x][y].age_fox = 0;
            config->spaces[x][y].hunger_fox = 0;
        }
        else if (!strcmp("ROCHA", object))
            config->spaces[x][y].type = -1;
        else
            config->spaces[x][y].type = 0;
    }

    fclose(input_file);
    return config;
}