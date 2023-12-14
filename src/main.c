#include <sys/time.h>
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

    // Creates an auxiliary copy of the ecosystem matrix to operate the movements
    cell **space_copy = (cell **) malloc (config->r * sizeof(cell *));
    for (int i = 0; i < config->r; i++)
        space_copy[i] = (cell *) malloc (config->c * sizeof(cell));
    copy_state(config, space_copy);

    int i;
    print_state(config, 0);
    struct timeval begin, end;
    gettimeofday(&begin, NULL);

    for (i = 0; i < config->n_gen; i++)
    {
        // Tries to move all rabbits solving any possible conflicts and updates the source matrix
        move_rabbits(config, space_copy, i);
        update_state(config, space_copy);

        // Also tries to move all foxes solving any possible conflicts and updates the source matrix
        move_foxes(config, space_copy, i);
        update_state(config, space_copy);

        // Raises the animals' ages and eliminates any fox that has reach its hunger threshold
        evolve_system(config);

        // Matches the source and auxiliary matrices to perform the next iteration
        copy_state(config, space_copy);
        print_state(config, i + 1);
    }
    gettimeofday(&end, NULL);
    double total_time = (end.tv_sec - begin.tv_sec) + (end.tv_usec - begin.tv_usec) / 1000000.0;
    
    print_result(config, config->n_gen - i);
    printf("\nProcessing time: %0.3lfs\n", total_time);    

    // Clean up
    for (i = 0; i < config->r; i++)
    {
        free(config->spaces[i]);
        free(space_copy[i]);
    }
    free(config->spaces);
    free(space_copy);
    free(config);
    return 0;
}
