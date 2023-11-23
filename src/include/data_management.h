#ifndef __DATA_MANAGEMENT__
#define __DATA_MANAGEMENT__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"

environment *read_input_file(char *file_name);
void print_result (environment *config);

#endif
