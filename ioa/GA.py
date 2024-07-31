# Python 3.11

from typing import TypedDict, NamedTuple
import random

class Item(TypedDict):
    weight: int
    value: int

ItemDict = dict[int, Item]

class Fitness(NamedTuple):
    weight: int
    value: int


#背包问题
# 物品 重量 价格
Items: ItemDict = {
    1: {'weight': 10, 'value': 15},
    2: {'weight': 15, 'value': 25},
    3: {'weight': 20, 'value': 35},
    4: {'weight': 25, 'value': 45},
    5: {'weight': 30, 'value': 55},
    6: {'weight': 35, 'value': 70},
}

#终止界限
FINISHED_LIMIT = 4

#重量界限
WEIGHT_LIMIT = 80

# 变异概率
MUTATION_RATE = 0.01

last_max_value = 0
diff_last = 10000

#判断退出
def is_finished(fitnesses: list[Fitness]):
    global last_max_value
    global diff_last
    tag = -1

    current_max_value: int = 0  # 当前最高适应度(最大价值)
    for index, fit in enumerate(fitnesses):
        if fit.value > current_max_value:
            current_max_value = fit.value
            tag = index
    
    diff = current_max_value - last_max_value # 价值差，也就是适应度的改变的大小
    # 这里判断连续两代的改变量如果都小于5，则停止迭代
    if diff < FINISHED_LIMIT and diff_last < FINISHED_LIMIT:
        return tag
    else:
        diff_last = diff
        last_max_value = current_max_value
        return -1


def init():
    """初始染色体样态(手动随机)"""
    chromosome1 = '100100'
    chromosome2 = '101010'
    chromosome3 = '010101'
    chromosome4 = '101011'
    chromosome_list = [chromosome1,
                        chromosome2,
                        chromosome3,
                        chromosome4]
    return chromosome_list


def cal_fitness(chromosome_list: list[str]):
    """
    计算每个染色体适应度(总重量和价值)
    - chromosome_list: 染色体列表

    return 染色体适应度列表
    """

    fitnesses: list[Fitness] = []

    for chromosome in chromosome_list:
        value = 0  # 物品总价值
        weight = 0 # 物品总重量

        for i, gene in enumerate(chromosome): # 遍历染色体的每个基因
            if int(gene) == 1:
                weight += Items[i + 1]['weight']
                value += Items[i + 1]['value']
        if weight > WEIGHT_LIMIT:  # 超重, 价值(适应度)置为0
            fitness = Fitness(weight, 0)
        else:
            fitness = Fitness(weight, value)
        
        fitnesses.append(fitness)

    return fitnesses


def filter(chromosome_list: list[str], fitnesses: list[Fitness]):
    """
    遗传算法-选择
    - chromosome_list: 染色体列表
    - fitnesses: 适应度列表

    选择要求：
    - 轮盘赌选择

    return 被选择染色体
    """

    # 种群总适应度(所有染色体总价值)
    total_fitness = sum([fit.value for fit in fitnesses])
    # 随机数
    pick = random.uniform(0, total_fitness)
    # 累计适应度
    cumulate = 0

    for chromosome, fitness in zip(chromosome_list, fitnesses):
        cumulate += fitness.value
        if cumulate > pick:
            return chromosome
    
    # 防御性编程
    return chromosome_list[-1]


def crossover(parent1: str, parent2: str):
    """
    遗传算法-(单点)交叉
    """

    point = random.randint(1, len(parent1)-1)
    child1 = parent1[:point] + parent2[point:]
    child2 = parent2[:point] + parent1[point:]
    return child1, child2


def mutate(chromosome: str, mutation_rate: float):
    """
    遗传算法-(随机)变异
    """
    # 将字符串转换为列表
    chromosome_list = list(chromosome)
    
    for i in range(len(chromosome_list)):
        if random.random() < mutation_rate:
            # 进行变异操作：0变为1，1变为0
            chromosome_list[i] = '1' if chromosome_list[i] == '0' else '0'
    
    # 将列表转换回字符串
    mutated_chromosome = ''.join(chromosome_list)
    return mutated_chromosome


def GA(epoch: int):
    """
    遗传算法
    - epoch: 迭代次数
    """
    # 初始群体
    population = init()
    fitnesses: list[Fitness] = []

    for generation in range(epoch):
        print(f"epoch {generation}")
        fitnesses = cal_fitness(population)
        new_population: list[str] = []

        for _ in range(len(population) // 2):
            parent1 = filter(population, fitnesses)
            parent2 = filter(population, fitnesses)
            child1, child2 = crossover(parent1, parent2)
            new_population.append(mutate(child1, MUTATION_RATE))
            new_population.append(mutate(child2, MUTATION_RATE))
        
        population = new_population
        fitnesses = cal_fitness(population)

    return population, fitnesses


if __name__ == '__main__':

    epochs = 10000
    max_value = 0
    tag = -1

    population, fitnesses = GA(epochs)
    for index, fit in enumerate(fitnesses):
        if fit.value > max_value:
            max_value = fit.value
            tag = index
    
    print(f"Best individual: {population[tag]}")
    print(f"Best fitness(value): {fitnesses[tag].value}")

