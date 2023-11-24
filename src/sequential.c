#include "include/data_management.h"
#include "include/simulation.h"

int main (int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Incorrect number of arguments.\n");
        fprintf(stderr, "Usage: %s <path/to/file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *file_name = argv[1];
    environment *config = read_input_file(file_name);

    cell **space_copy = (cell **) malloc (config->r * sizeof(cell *));
    for (int i = 0; i < config->r; i++)
        space_copy[i] = (cell *) malloc (config->c * sizeof(cell));
    copy_state(config, space_copy);

//    print_state(config, 0);
    for (int i = 0; i < config->n_gen; i++)
    {
        move_rabbits(config, space_copy, i);
        update_state(config, space_copy);
        move_foxes(config, space_copy, i);
        update_state(config, space_copy);
        evolve_system(config);
        copy_state(config, space_copy);
//        print_state(config, i + 1);
    }
    print_result(config);

    // Clean up
    for (int i = 0; i < config->r; i++)
    {
        free(config->spaces[i]);
        free(space_copy[i]);
    }
    free(config->spaces);
    free(space_copy);
    free(config);
    return 0;
}
