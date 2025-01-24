import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

def func1(x):
    return x * np.log(x)

def func2(x):
    return x

def func3(x):
    return x * x

x1 = np.linspace(10, 1000000, 10000) # generate 1000 points from 0.1 to 5
y1 = func1(x1)


x2 = np.linspace(10, 1000000, 10000) # generate 1000 points from 0.1 to 5
y2 = func2(x2)


x3 = np.linspace(10, 1000000, 1000) # generate 1000 points from 0.1 to 5
y3 = func3(x3)


name_graphique = 'Temps de calcul'
file_names = ['mesure_temps_de_calcul']
graph_names = ['Comparaisons tris']
for i in range(len(file_names)):
    ax = pd.read_csv('csv/' + file_names[i] + '.csv')
    ax = ax.plot(x='N', marker='o')
    ax.plot(x1, y1, ':', label="n*log(n)", linewidth=2)
    ax.plot(x2, y2, ':', label="n", linewidth=2)
    #ax.plot(x3, y3, ':', label="n^2", linewidth=2)
    ax.set_yscale('log')
    ax.set_xscale('log')
    ax.set_ylabel("log(Temps execution (ms))")
    ax.set_xlabel("log(Taille du dataset)")
    ax.set_title(graph_names[i])
    plt.legend()
    plt.savefig('svg/' + file_names[i] + '.svg', format='svg')

