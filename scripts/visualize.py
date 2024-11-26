# import matplotlib.pyplot as plt
# import pandas as pd

# # Данные
# df = pd.read_csv('/Users/egornidental/Repositories/Eqvilent_cpp/data/input.csv')
# print(df.head())
# print(df.describe())
# data = df.iloc[0:, 0].tolist()

# # Визуализация
# plt.figure(figsize=(10, 6))
# plt.plot(range(len(data)), data, marker='o', label='Time Series Data', color='blue')
# plt.title('Visualization of Time Series Data')
# plt.xlabel('Index')
# plt.grid(True)
# plt.legend()
# plt.show()

import matplotlib.pyplot as plt
import pandas as pd

# Данные
df = pd.read_csv('/Users/egornidental/Repositories/Eqvilent_cpp/data/input.csv', header=None, names=['alpha', 'beta'])
print(df.head())
print(df.describe())
data = df.iloc[:10, 0].tolist()

# Визуализация
plt.figure(figsize=(10, 6))
plt.plot(range(len(data)), data, marker='o', label='Time Series Data', color='blue')
# plt.plot(range(10), data[:10], marker='o', label='Time Series Data', color='blue')

# Добавление значений y на график
for i, value in enumerate(data):
    plt.annotate(f'{value:.2f}', (i, value), textcoords="offset points", xytext=(0, 10), ha='center')

plt.title('Visualization of Time Series Data')
plt.xlabel('Index')
plt.ylabel('Value')
plt.grid(True)
plt.legend()
plt.show()
