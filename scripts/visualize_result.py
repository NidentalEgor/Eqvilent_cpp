import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
from math import pi

inputs_file = "/Users/egornidental/Repositories/Eqvilent_cpp/data/input.csv"
results_file = "/Users/egornidental/Repositories/Eqvilent_cpp/data/result_window_10.csv"

inputs = pd.read_csv(inputs_file, header=None).iloc[:, 0].values
results = pd.read_csv(results_file, header=None).values

window_size = 10

def plot_window(inputs, results, start, end, idx):
    x = np.arange(start, end)
    y = inputs[start:end]
    alpha, beta = results[end - 1]
    alpha, beta = -alpha, -beta # because the angles are in the left half-plane

    plt.plot(x, y, 'o-', label='Values')

    for xi, yi in zip(x, y):
        plt.text(xi, yi, f"({yi})", fontsize=8, ha='right')

    last_point_x = x[-1]
    last_point_y = y[-1]

    # tangent alpha
    if alpha != 0:
        tangent_alpha_x = [x[0], last_point_x]
        tangent_alpha_y = [
            last_point_y - np.tan(alpha) * (last_point_x - x[0]),
            last_point_y
        ]
        plt.plot(tangent_alpha_x, tangent_alpha_y, 'r--', label='Tangent Alpha')

    # tangent beta
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

for i in range(0, 10):
    start_idx = max(0, i - window_size + 1)
    end_idx = i + 1
    plot_window(inputs, results, start_idx, end_idx, i)
