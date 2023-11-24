#ifndef __SIMULATION__
#define __SIMULATION__

#include <stdio.h>
#include <stdlib.h>

#include "common.h"

#define MIN(x, y) (x < y ? x : y)

void update_state (environment *config, cell **spaces);
void move_rabbits (environment *config, cell **spaces, unsigned int g);
void evolve_system (environment *config);
void print_state (environment *config, int gen);
void print_limits (int n);

void copy_state (environment *config, cell **spaces);
void update_state (environment *config, cell **spaces);

#endif
