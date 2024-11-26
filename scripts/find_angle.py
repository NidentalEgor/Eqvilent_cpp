import math

# Функция для вычисления длины вектора
def vector_length(x, y):
    return math.sqrt(x**2 + y**2)

# Функция для вычисления скалярного произведения
def dot_product(x1, y1, x2, y2):
    return x1 * x2 + y1 * y2

# Функция для вычисления угла между двумя отрезками
def angle_between_segments(A, B, C, D):
    # Векторы отрезков AB и CD
    AB = (B[0] - A[0], B[1] - A[1])
    CD = (D[0] - C[0], D[1] - C[1])
    
    # Скалярное произведение
    dot_prod = dot_product(AB[0], AB[1], CD[0], CD[1])
    
    # Длины векторов
    length_AB = vector_length(AB[0], AB[1])
    length_CD = vector_length(CD[0], CD[1])
    
    # Косинус угла между векторами
    cos_theta = dot_prod / (length_AB * length_CD)
    
    # Ограничим значение cos_theta в диапазоне [-1, 1], чтобы избежать ошибок из-за погрешностей округления
    cos_theta = max(-1, min(1, cos_theta))
    
    # Угол в радианах
    theta_rad = math.acos(cos_theta)
    
    print("rad = ", theta_rad)

    # Преобразуем угол в градусы
    theta_deg = math.degrees(theta_rad)
    
    return theta_deg

print("123")
# Пример точек
A = (0, 11384.96)
B = (1, 11373.01)
C = (0, 11373.01)
D = (1, 11373.01)

# Вычисление угла между отрезками
angle = angle_between_segments(A, B, C, D)
print(f"Угол между отрезками: {angle} градусов")
