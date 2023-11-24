#ifndef __SIMULATION__
#define __SIMULATION__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "common.h"

#define MIN(x, y) (x < y ? x : y)

void update_state (environment *config, cell **spaces);
void move_rabbits (environment *config, cell **spaces, unsigned int g);
void move_foxes (environment *config, cell **spaces, unsigned int g);
void evolve_system (environment *config);
void print_state (environment *config, unsigned int gen);
void print_limits (unsigned int n);

void copy_state (environment *config, cell **spaces);
void update_state (environment *config, cell **spaces);
void empty_cells (int x, int y, int north, int south, int east, int west, environment *config, int *adj, int *available, int type);
void move_animal_to_adj (environment *config, cell **spaces, int x, int y, int orientation, int type, bool vertical);

#endif
