import numpy as np

"""
粒子群算法优化 Rosenbrock 函数
"""

class Particle:
    def __init__(self, num_dimensions):
        self.position = np.random.uniform(-10, 10, num_dimensions)  # 位置
        self.velocity = np.random.uniform(-1, 1, num_dimensions)  # 速度
        self.best_position = self.position.copy()  # 最优位置
        self.best_score = float('inf')  # 最优适应度

    def update_velocity(self, global_best_position, w, c1, c2):
        """
        更新粒子的速度

        - `global_best_position`: 全局最佳位置
        - `w`: 惯性权重
        - `c1`: 个体学习因子
        - `c2`: 社会学习因子
        """
        # 随机数
        r1 = np.random.rand(len(self.position))
        r2 = np.random.rand(len(self.position))
        
        # 计算认知组件，反映粒子个体最佳位置与当前位置的差异
        cognitive_component = c1 * r1 * (self.best_position - self.position)
        
        # 计算社交组件，反映全局最佳位置与当前位置的差异
        social_component = c2 * r2 * (global_best_position - self.position)
        
        # 更新粒子的速度，综合考虑惯性权重、认知组件和社交组件
        self.velocity = w * self.velocity + cognitive_component + social_component

    def update_position(self, bounds):
        """
        更新粒子的位置：根据粒子的当前速度，调整粒子的位置。如果粒子的位置超出设定的边界，则将其位置重置为边界值。

        - bounds (tuple): (min_bound, max_bound)
        """
        # 根据当前速度更新物体位置
        self.position += self.velocity
        
        # 遍历物体的每个坐标维度
        for dim in range(len(self.position)):
            # 如果当前位置小于最小边界，则将其设置为最小边界值
            if self.position[dim] < bounds[0]:
                self.position[dim] = bounds[0]
            # 如果当前位置大于最大边界，则将其设置为最大边界值
            elif self.position[dim] > bounds[1]:
                self.position[dim] = bounds[1]

def rosenbrock_function(x):
    """
    计算Rosenbrock函数的值
    
    参数:
    - x: 输入坐标点
    """
    a = 1
    b = 100
    return (a - x[0])**2 + b * (x[1] - x[0]**2)**2

def pso(num_particles, num_dimensions, bounds, num_iterations):
    swarm = [Particle(num_dimensions) for _ in range(num_particles)]  # 创建粒子群
    global_best_position = np.random.uniform(bounds[0], bounds[1], num_dimensions)  # 初始化全局最佳位置
    global_best_score = float('inf')  # 初始化全局最佳适应度

    w = 0.5
    c1 = 1.5
    c2 = 1.5

    for iteration in range(num_iterations):
        for particle in swarm:
            score = rosenbrock_function(particle.position)
            if score < particle.best_score:
                # 更新粒子的最优位置和最优适应度
                particle.best_score = score
                particle.best_position = particle.position.copy()

            if score < global_best_score:
                # 更新全局最佳位置和全局最佳适应度
                global_best_score = score
                global_best_position = particle.position.copy()

        for particle in swarm:
            # 更新粒子的速度和位置
            particle.update_velocity(global_best_position, w, c1, c2)
            particle.update_position(bounds)

        print(f"Iteration {iteration + 1}/{num_iterations}, Best Score: {global_best_score}")

    return global_best_position, global_best_score

# --------------------------------------------------------------------------------------------------

"""
粒子群算法解决01背包问题
"""

class Particle01:
    def __init__(self, num_items):
        self.position = np.random.randint(2, size=num_items)
        self.velocity = np.random.uniform(-1, 1, num_items)
        self.best_position = self.position.copy()
        self.best_score = 0

    def update_velocity(self, global_best_position, w, c1, c2):
        r1 = np.random.rand(len(self.position))
        r2 = np.random.rand(len(self.position))
        cognitive_component = c1 * r1 * (self.best_position - self.position)
        social_component = c2 * r2 * (global_best_position - self.position)
        self.velocity = w * self.velocity + cognitive_component + social_component

    def update_position(self):
        # 01背包问题更新位置的方式略有不同
        # 因为物品只有拿和不拿两种情况，因此需要二值化
        # 随机数作为Sigmoid函数的输入，然后通过Sigmoid函数得到概率，根据概率决定是否拿物品
        sigmoid = 1 / (1 + np.exp(-self.velocity))
        self.position = np.where(np.random.rand(len(self.position)) < sigmoid, 1, 0)

def fitness(position, values, weights, capacity):
    """
    计算01背包的适应度
    """
    total_value = np.sum(position * values)
    total_weight = np.sum(position * weights)
    if total_weight > capacity:
        return 0  # 超重
    return total_value

def pso_knapsack(values, weights, capacity, num_particles, num_iterations):
    num_items = len(values)
    swarm = [Particle01(num_items) for _ in range(num_particles)]
    global_best_position = np.random.randint(2, size=num_items)
    global_best_score = 0

    w = 0.5
    c1 = 1.5
    c2 = 1.5

    for iteration in range(num_iterations):
        for particle in swarm:
            score = fitness(particle.position, values, weights, capacity)
            if score > particle.best_score:
                particle.best_score = score
                particle.best_position = particle.position.copy()

            if score > global_best_score:
                global_best_score = score
                global_best_position = particle.position.copy()

        for particle in swarm:
            particle.update_velocity(global_best_position, w, c1, c2)
            particle.update_position()

        print(f"Iteration {iteration + 1}/{num_iterations}, Best Score: {global_best_score}")

    return global_best_position, global_best_score



if __name__ == "__main__":
    # num_particles = 30
    # num_dimensions = 2
    # bounds = [-5, 5]
    # num_iterations = 600

    # best_position, best_score = pso(num_particles, num_dimensions, bounds, num_iterations)
    # print(f"Best Position: {best_position}, Best Score: {best_score}")

    values = np.array([60, 85, 70, 40, 55])
    weights = np.array([10, 25, 15, 20, 30])
    capacity = 60
    num_particles = 30
    num_iterations = 100
    best_position, best_score = pso_knapsack(values, weights, capacity, num_particles, num_iterations)
    print(f"Best Position: {best_position}, Best Score: {best_score}")