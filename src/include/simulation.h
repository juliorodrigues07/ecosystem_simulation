#ifndef __SIMULATION__
#define __SIMULATION__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "common.h"

#define MIN(x, y) (x < y ? x : y)

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

# ifdef _OPENMP
#define N_THREADS 4
# else
#define N_THREADS 1
# endif

void empty_cells (int x, int y, int north, int south, int east, int west,
                  environment *config, int *adj, unsigned int *available, int type);
void move_animal_to_adj (environment *config, cell **spaces, int x, int y,
                         int orientation, int type, bool vertical);
void move_rabbits (environment *config, cell **spaces, unsigned int g);
void move_foxes (environment *config, cell **spaces, unsigned int g);
void evolve_system (environment *config);
void update_state (environment *config, cell **spaces);
void copy_state (environment *config, cell **spaces);

void print_state (environment *config, unsigned int gen);
void print_limits (unsigned int n);

#endif
