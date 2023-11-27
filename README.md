[![C99](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1256.pdf)
# Ecosystem Simulation
Parallel implementation in shared memory environments of a simple ecosystem based on Lotka-Volterra model (Predator-Prey) utilizing OpenMP library (PA 2 from Parallel Computing course - DCOMP - UFSJ).

# Requirements

- [GCC](https://gcc.gnu.org/onlinedocs/gcc-12.2.0/gcc/) compiler:

      sudo apt install gcc
  
- [OpenMP](https://www.openmp.org/) library:

      sudo apt install libomp-dev

- [gprof](https://ftp.gnu.org/old-gnu/Manuals/gprof-2.9.1/html_mono/gprof.html) tool;

- To install all dependencies:

      ./install_dependencies.sh

# Optional Requirements

- [Python3](https://python.org) and [pip](https://pip.pypa.io/en/stable/installation/) package manager:

      sudo apt install python3 python3-pip build-essential python3-dev

- [PyCryptodome](https://pycryptodome.readthedocs.io/en/latest/src/introduction.html) library:
 
      pip install pycryptodomex

- [Matplotlib](https://matplotlib.org/) library:
 
      pip install matplotlib
       
- [seaborn](https://seaborn.pydata.org/) library:
 
      pip install seaborn

# Compilation

Execute the following command to compile the source code:

    make

# Execution

You can alter the parameters, such as the number of threads in the source code (_simulation.h_). 

## Sequential

To execute the sequential version with or without profiling, run the following respective commands:

- Without profiling:

      make sequential

- With profiling (**gprof**):

      make with_prof

## Parallel

Run the following command for executing the program with multiple threads:

    make parallel

# Optional Running

## Instance Generator

Inside _instances_ directory, you can generate your own instances by executing the command using the following template: `python3 instance_generator.py --rows <number> --columns <number> --genrabbit <number> --genfox <number> --hunger <number> --ngen <number> --rabbits <number> --foxes <number> --stones <number>`

- Example: Generating an instance file with ecosystem dimension 5 x 5, rabbit's reproduction interval 2, foxes' reproduction interval 4, foxes' starvation interval 3, 6 generations, 10% rabbits, 10% foxes and 20% stones:

      python3 instance_generator.py -l 5 -c 5 -gr 2 -gf 4 -hf 3 -n 6 -r 0.1 -f 0.1 -s 0.2

## Time graphics

Inside _plotting_ directory, you can generate the time graphics present in this works report by running the following commmand:

    python3 times.py
