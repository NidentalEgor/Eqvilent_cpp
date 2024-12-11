import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
from math import pi

# Загрузка данных
inputs_file = "/Users/egornidental/Repositories/Eqvilent_cpp/data/input.csv"
results_file = "/Users/egornidental/Repositories/Eqvilent_cpp/data/result_window_10.csv"

inputs = pd.read_csv(inputs_file, header=None).iloc[:, 0].values  # Входные данные
results = pd.read_csv(results_file, header=None).values  # Углы альфа и бета

window_size = 10

# Функция для построения графика
def plot_window(inputs, results, start, end, idx):
    x = np.arange(start, end)
    y = inputs[start:end]
    print(np.tan(pi/4.0))
    print(f"start = {start}")
    print(f"end - 1 = {end - 1}")
    alpha, beta = results[end - 1]
    alpha, beta = -alpha, -beta # потому что углы в левой полуплоскости
    print(f"alpha = {alpha}, beta = {beta}")

    # Построение исходных данных
    plt.plot(x, y, 'o-', label='Values')

    for xi, yi in zip(x, y):
        plt.text(xi, yi, f"({yi})", fontsize=8, ha='right')

    # Построение касательных
    last_point_x = x[-1]
    last_point_y = y[-1]

    # Касательная alpha (слева вверх)
    if alpha != 0:
        tangent_alpha_x = [x[0], last_point_x]
        tangent_alpha_y = [
            last_point_y - np.tan(alpha) * (last_point_x - x[0]),
            last_point_y
        ]
        plt.plot(tangent_alpha_x, tangent_alpha_y, 'r--', label='Tangent Alpha')

    # Касательная beta (слева вниз)
    if beta != 0:
        tangent_beta_x = [x[0], last_point_x]
        tangent_beta_y = [
            last_point_y - np.tan(beta) * (last_point_x - x[0]),
            last_point_y
        ]
        plt.plot(tangent_beta_x, tangent_beta_y, 'g--', label='Tangent Beta')

    plt.title(f"Window {idx}")
    plt.xlabel("Index")
    plt.ylabel("Value")
    plt.legend()
    plt.grid()
    plt.show()

for i in range(0, 4):
    start_idx = max(0, i - window_size + 1)
    end_idx = i + 1
    plot_window(inputs, results, start_idx, end_idx, i)
