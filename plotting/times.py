import matplotlib.pyplot as plt
from seaborn import barplot
from os import getcwd


def plot_time(buffer, instance_1, instance_2, instance_3, instance_4):
    
    plt.grid()
    plt.title("Tempo de Execução entre Entradas")
    plt.xlabel('Quantidade de Threads')
    plt.ylabel('Tempo de Execução (segundos)')
    plt.xticks(buffer)
    
    plt.plot(buffer, instance_1, color='g', label='instance_1.txt')
    plt.plot(buffer, instance_2, color='y', label='instance_2.txt')
    plt.plot(buffer, instance_3, color='r', label='instance_3.txt')
    plt.plot(buffer, instance_4, color='b', label='instance_4.txt')
    plt.legend(loc='best')
    
    plt.savefig(f'{getcwd()}/parallel.svg', format='svg')
    plt.show()


def plot_by_instance(buffer, instance, instance_name):

    plt.grid()
    plt.title(f'Tempo de Execução ({instance_name})')
    plt.xlabel('Quantidade de Threads')
    plt.ylabel('Tempo de Execução (segundos)')
    plt.xticks(buffer)

    plt.plot(buffer, instance, color='r')

    size = len(instance_name) - 4
    plt.savefig(f'{getcwd()}/{instance_name[:size]}.svg', format='svg')
    plt.show()


def plot_sequential(measures):

    fig, ax = plt.subplots(figsize=(12, 8))
    barplot(x=['instance_1.txt', 'instance_2.txt', 'instance_3.txt', 'instance_4.txt'], y=measures, palette='Blues')

    ax.set_title('Tempo de Processamento entre Instâncias', fontsize=18)
    ax.set_ylabel("Tempo de Execução (segundos)", fontsize=14)
    ax.set_xlabel("Instância", fontsize=14)

    ax.grid(which='both')
    ax.grid(which='minor', alpha=0.8)
    ax.grid(which='major', alpha=0.8)
    plt.show()

    fig.savefig(f'{getcwd()}/sequential.svg', format='svg')


def main():

    buffer = [2, 3, 4]

    instance_1 = [0.004, 0.004, 0.004]
    plot_by_instance(buffer, instance_1, 'instance_1.txt')

    instance_2 = [0.06, 0.058, 0.065]
    plot_by_instance(buffer, instance_2, 'instance_2.txt')

    instance_3 = [0.75, 0.7, 0.68]
    plot_by_instance(buffer, instance_3, 'instance_3.txt')
    
    instance_4 = [115, 105, 100]
    plot_by_instance(buffer, instance_4, 'instance_4.txt')

    plot_time(buffer, instance_1, instance_2, instance_3, instance_4)

    sequential = [0.001, 0.07, 1, 150]
    plot_sequential(sequential)


if __name__ == '__main__':
    main()
