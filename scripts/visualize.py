import matplotlib.pyplot as plt
import pandas as pd
import argparse

# Парсер командной строки
parser = argparse.ArgumentParser(description="Визуализация данных из файла")
parser.add_argument("start", type=int, help="Начало диапазона по X (натуральное число)")
parser.add_argument("end", type=int, help="Конец диапазона по X (натуральное число)")
args = parser.parse_args()

# Данные
df = pd.read_csv('/Users/egornidental/Repositories/Eqvilent_cpp/data/input.csv', header=None, names=['alpha', 'beta'])
print(df.head())
print(df.describe())

# Определение начала и конца диапазона
start = args.start
end = args.end

# Учитываем диапазон
data = df.iloc[start:end+1, 0].tolist()  # start и end считаются в натуральных числах

# Визуализация
plt.figure(figsize=(10, 6))
x_values = range(start, start + len(data))  # Натуральные числа в заданном диапазоне
plt.plot(x_values, data, marker='o', label='Time Series Data', color='blue')

# Добавление значений y на график
for x, value in zip(x_values, data):
    plt.annotate(f'{value:.2f}', (x, value), textcoords="offset points", xytext=(0, 10), ha='center')

# Настройка сетки по оси X
plt.xticks(range(start, end + 1, 1))  # Натуральные числа с шагом 2 в указанном диапазоне

plt.title('Visualization of Time Series Data')
plt.xlabel('Index')
plt.ylabel('Value')
plt.grid(True)
plt.legend()
plt.show()
