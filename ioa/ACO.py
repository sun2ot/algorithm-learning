import numpy as np

"""
蚁群算法解 TSP 问题
"""

# 初始化参数
num_cities = 5  # 城市数量
num_ants = 10  # 蚂蚁数量
max_iterations = 100  # 最大迭代次数
alpha = 1.0  # 信息素重要程度因子
beta = 5.0  # 启发函数重要程度因子
evaporation_rate = 0.5  # 信息素挥发系数
Q = 100  # 信息素常量

# 城市距离矩阵
distances = np.array([
    [0, 2, 9, 10, 5],
    [1, 0, 6, 4, 3],
    [15, 7, 0, 8, 3],
    [6, 3, 12, 0, 11],
    [9, 7, 5, 6, 0]
])

# 初始化信息素矩阵
pheromones = np.ones((num_cities, num_cities))

# 计算启发信息矩阵(1 / 距离)
# 对角线设置无穷大，避免除以0
heuristic_matrix = 1 / (distances + np.diag([np.inf] * num_cities))

# 计算转移概率矩阵
def calculate_transition_probabilities(current_city, allowed, pheromones, heuristic_matrix):
    probabilities = np.zeros(num_cities)
    for city in allowed:
        # 蚁群算法的转移概率
        probabilities[city] = (pheromones[current_city, city] ** alpha) * (heuristic_matrix[current_city, city] ** beta)
    probabilities /= probabilities.sum()
    return probabilities

# 选择下一个城市
def select_next_city(probabilities):
    return np.random.choice(range(num_cities), p=probabilities)

# 更新信息素
def update_pheromones(pheromones, all_paths, all_lengths):
    pheromones *= (1 - evaporation_rate)  # 信息素挥发
    for path, length in zip(all_paths, all_lengths):
        for i in range(len(path) - 1):  # 遍历路径上的每对城市
            pheromones[path[i], path[i+1]] += Q / length  # 信息素增益(蚂蚁圈模型)
            pheromones[path[i+1], path[i]] += Q / length

# 蚁群算法主循环
best_path = None
best_length = np.inf

for iteration in range(max_iterations):
    all_paths = []
    all_lengths = []
    for ant in range(num_ants):
        path = [np.random.randint(num_cities)]  # 每只蚂蚁随机选择起始城市
        allowed = set(range(num_cities)) - set(path)  # 蚂蚁当前城市外的所有城市
        while allowed:
            current_city = path[-1]  # 当前城市
            probabilities = calculate_transition_probabilities(current_city, allowed, pheromones, heuristic_matrix)
            next_city = select_next_city(probabilities)
            path.append(next_city)
            allowed.remove(next_city)
        path.append(path[0])  # 回到起点
        length = sum(distances[path[i], path[i+1]] for i in range(num_cities))
        all_paths.append(path)
        all_lengths.append(length)
        # 更新最佳路径
        if length < best_length:
            best_length = length
            best_path = path
    update_pheromones(pheromones, all_paths, all_lengths)
    print(f"Iteration {iteration + 1}: Best Length = {best_length}")

# 输出结果
print("Optimal path:", best_path)
print("Shortest distance:", best_length)
