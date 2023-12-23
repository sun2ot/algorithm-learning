// 纯回溯法解决01背包问题

#include <stdio.h>
#include <stdbool.h>


/**
 * 求两个整数的最大值
 * 
 * @param a 第一个整数
 * @param b 第二个整数
 * @return 两个整数中的较大值
 */
int max(int a, int b) {
    return (a > b) ? a : b;
}


/**
 * 回溯算法：背包问题
 * 
 * @param weights 物品的重量数组
 * @param values 物品的价值数组
 * @param n 物品的数量
 * @param W 背包的容量
 * @param selected 当前已选中的物品数组
 * @param currentWeight 当前已选中物品的总重量
 * @param currentValue 当前已选中物品的总价值
 * @param maxValue 当前最大的总价值
 * @param index 当前处理的物品索引
 */
void backtrack(int* weights, int* values, int n, int W, int* selected, int* currentWeight, int* currentValue, int* maxValue, int index) {
    if (index == n) {  // 处理完所有物品
        if (*currentWeight <= W && *currentValue > *maxValue) {  // 找到一个更优解
            *maxValue = *currentValue;  // 更新最大价值
            printf("Max value is: %d\n", *maxValue);
            printf("The optimal choice is as follows:\n");
            for (int i = 0; i < n; i++) {  // 打印最优解
                if (selected[i]) {
                    printf("item %d\n", i + 1);
                }
            }
            printf("\n");
        }
        return;
    }

    selected[index] = true;  // 选中index对应的当前物品
    *currentWeight += weights[index];  // 更新当前总重量
    *currentValue += values[index];  // 更新当前总价值
    // 选择当前物品的情况下，递归处理下一个物品
    backtrack(weights, values, n, W, selected, currentWeight, currentValue, maxValue, index + 1);  

    selected[index] = false;  // 撤销选择当前的物品
    // 恢复不选择这个物品时的总重量和总价值
    *currentWeight -= weights[index];
    *currentValue -= values[index];
    // 不选择当前物品的情况下，尝试所有可能的后续选择
    backtrack(weights, values, n, W, selected, currentWeight, currentValue, maxValue, index + 1);
}


/**
 * 解决01背包问题
 * 
 * @param weights 物品的重量数组
 * @param values 物品的价值数组
 * @param n 物品的数量
 * @param W 背包的最大承重量
 */
void knapsack(int* weights, int* values, int n, int W) {
    // 初始化
    int selected[n];
    int currentWeight = 0;
    int currentValue = 0;
    int maxValue = 0;
    int index = 0;

    // 回溯处理
    backtrack(weights, values, n, W, selected, &currentWeight, &currentValue, &maxValue, index);

    printf("The best value is: %d\n", maxValue);
}

int main() {
    int weights[] = {2, 3, 4, 5};  // 物品的重量数组
    int values[] = {3, 4, 5, 6};  // 物品的价值数组
    int n = sizeof(weights) / sizeof(weights[0]);  // 物品的数量
    int W = 8;  // 背包的最大承重量

    knapsack(weights, values, n, W);

    return 0;
}
