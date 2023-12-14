from Cryptodome.Random.random import randint
from argparse import ArgumentParser
from datetime import datetime
from numpy import full
from os import getcwd
from sys import argv


def help(args):

    if args['rows'] < 1:
        print(f'Number of rows must be greater than zero!')
        exit(127)

    if args['columns'] < 1:
        print(f'Number of columns must be greater than zero!')
        exit(127)

    if args['genrabbit'] < 0:
        print(f'Interval between rabbits reproduction must be equal or greater than zero!')
        exit(127)

    if args['genfox'] < 0:
        print(f'Interval between foxes reproduction must be equal or greater than zero!')
        exit(127)

    if args['hunger'] < 1:
        print(f'Interval between foxes death by starvation must be greater than zero!')
        exit(127)

    if args['ngen'] < 1:
        print(f'Number of generations to simulate must be greater than zero!')
        exit(127)

    if args['rabbits'] < 0:
        print(f'Amount of rabbits must be equal or greater than zero!')
        exit(127)

    if args['foxes'] < 0:
        print(f'Amount of foxes must be equal or greater than zero!')
        exit(127)

    if args['stones'] < 0:
        print(f'Amount of stones must be equal or greater than zero!')
        exit(127)

    if int(args['rabbits']) + int(args['foxes']) + int(args['stones']) > 1:
        print(f'Amount of objects must fit into the matrix.')
        exit(127)


def gen_random_coords(r, c):
    return randint(0, r - 1), randint(0, c - 1)


def generate_instances():

    argpar = ArgumentParser()
    argpar.add_argument("-l", "--rows", type=int, default=1, help="Amount of rows.")
    argpar.add_argument("-c", "--columns", type=int, default=1, help="Amount of columns.")
    argpar.add_argument("-gr", "--genrabbit", type=int, default=0, help="Interval between rabbits reproduction.")
    argpar.add_argument("-gf", "--genfox", type=int, default=0, help="Interval between foxes reproduction.")
    argpar.add_argument("-hf", "--hunger", type=int, default=1, help="Interval between foxes death by starvation.")
    argpar.add_argument("-n", "--ngen", type=int, default=1, help="Number of generations.")
    argpar.add_argument("-r", "--rabbits", type=float, default=0, help="Percent amount of rabbits.")
    argpar.add_argument("-f", "--foxes", type=float, default=0, help="Percent amount of foxes.")
    argpar.add_argument("-s", "--stones", type=float, default=0, help="Percent amount of stones.")
    args = vars(argpar.parse_args())
    help(args)

    r = args['rows']
    c = args['columns']
    cells = r * c
    matrix = full((r, c), -1)
    
    n_rabbits = int(args['rabbits'] * cells)
    n_foxes = int(args['foxes'] * cells)
    n_stones = int(args['stones'] * cells)

    now = datetime.now()
    file_name = f'Instance - {str(now.date())} | {str(now.hour)}:{str(now.minute)}:{str(now.second)}'

    with open(f'{getcwd()}/{file_name}.txt', 'w') as instance_file:
        instance_file.write(f'{args["genrabbit"]} {args["genfox"]} {args["hunger"]} {args["ngen"]} {r} {c} {n_rabbits + n_foxes + n_stones}\n')

        while (n_rabbits > 0):
            x, y = gen_random_coords(r, c)
            if matrix[x][y] == -1:
                instance_file.write(f'COELHO {x} {y}\n')
                n_rabbits -= 1

        while (n_foxes > 0):
            x, y = gen_random_coords(r, c)
            if matrix[x][y] == -1:
                instance_file.write(f'RAPOSA {x} {y}\n')
                n_foxes -= 1

        while (n_stones > 0):
            x, y = gen_random_coords(r, c)
            if matrix[x][y] == -1:
                instance_file.write(f'ROCHA {x} {y}\n')
                n_stones -= 1


if __name__ == '__main__':
    generate_instances()

