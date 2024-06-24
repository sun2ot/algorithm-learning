import random
import math

"""
模拟退火算法解决调度问题
"""

def schedule_makespan(schedules, machines):
    """
    计算每台机器上的作业完成时间，返回最大时间
    
    - schedules: `(job, machine_index)`
    - machines: 机器数量
    """
    machine_times = [0] * machines  # 初始化每个机器上的作业完成时间
    for schedule in schedules:
        machine_times[schedule[1]] += schedule[0]
    return max(machine_times)

def neighbor(schedule):
    """
    通过交换随机两个作业的机器分配来生成邻域解
    """
    new_schedule = schedule[:]
    i, j = random.sample(range(len(new_schedule)), 2)
    new_schedule[i], new_schedule[j] = new_schedule[j], new_schedule[i]
    return new_schedule

def simulated_annealing(jobs, machines, initial_temperature, cooling_rate, stopping_temperature):
    """
    模拟退火算法最小化作业调度中的完工时间
    """
    # 分配任务 => (job, machine_index)
    current_schedule = [(job, random.randint(0, machines - 1)) for job in jobs]
    current_makespan = schedule_makespan(current_schedule, machines)
    current_temperature = initial_temperature
    
    while current_temperature > stopping_temperature:
        #new_schedule = neighbor(current_schedule, machines)
        new_schedule = neighbor(current_schedule)
        new_makespan = schedule_makespan(new_schedule, machines)
        
        if new_makespan < current_makespan:
            # 温度降低，接受新解
            current_schedule, current_makespan = new_schedule, new_makespan
        else:
            delta = new_makespan - current_makespan  # 温度差
            # 以概率接受高温新解
            acceptance_probability = math.exp(-delta / current_temperature)
            if random.random() < acceptance_probability:
                current_schedule, current_makespan = new_schedule, new_makespan
        
        current_temperature *= cooling_rate
    
    return current_schedule, current_makespan


jobs = [2, 4, 6, 8]
machines = 2
initial_temperature = 1000
cooling_rate = 0.95
stopping_temperature = 0.01

final_schedule, final_makespan = simulated_annealing(jobs, machines, initial_temperature, cooling_rate, stopping_temperature)

print("Final schedule:", final_schedule)
print("Final makespan:", final_makespan)
