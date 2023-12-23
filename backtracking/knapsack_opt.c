// 01背包问题的优化解法，使用上界函数剪枝

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// 定义物品结构体
typedef struct {
    int id;
    int weight;
    int value;
} Item;


/**
 * 比较函数，用于排序
 *
 * @param a 指向要比较的第一个元素的指针
 * @param b 指向要比较的第二个元素的指针
 * @return 如果a的单位价值大于b，则返回一个负数；如果a的单位价值小于b，则返回一个正数；如果两者单位价值相等，则返回0
 */
int compare(const void* a, const void* b) {
    Item* itemA = (Item*)a;
    Item* itemB = (Item*)b;

    if (itemA->value/itemA->weight > itemB->value/itemB->weight) {
        return -1;
    } else if (itemA->value/itemA->weight < itemB->value/itemB->weight) {
        return 1;
    } else {
        return 0;
    }
}


/**
 * 计算选择剩余所有物品后的价值上界
 * 
 * @details 用于剪枝，如果价值上界小于当前最大价值，则不再继续搜索
 * 
 * @param items 物品数组
 * @param n 物品数量
 * @param W 背包容量
 * @param index 当前物品索引
 * @param currentWeight 当前背包重量
 * @param currentValue 当前背包价值
 * @return 价值上界
 */
int upperBound(Item* items, int n, int W, int index, int currentWeight, int currentValue) {
    int remainingWeight = W - currentWeight;  // 剩余容量
    int upperValue = currentValue;  // 上界价值：初始值为当前已选中物品的总价值

    // 从index开始，尽可能多地装入物品
    while (index < n && items[index].weight <= remainingWeight) {  // 不是最后一个物品，且剩余容量足够装下当前物品
        remainingWeight -= items[index].weight;
        upperValue += items[index].value;
        index++;
    }

    if (index < n) {  // 剩余容量不足以装下当前物品
        upperValue += (remainingWeight * (items[index].value/items[index].weight));  // 装入部分当前物品，更新上界价值
    }

    return upperValue;
}


/**
 * 回溯搜索函数
 *
 * @param items 物品数组
 * @param n 物品数量
 * @param W 背包容量
 * @param selected 选中的物品数组
 * @param currentWeight 当前背包重量
 * @param currentValue 当前背包价值
 * @param maxValue 最大背包价值
 * @param index 当前物品索引
 */
void backtrack(Item* items, int n, int W, bool* selected, int* currentWeight, int* currentValue, int* maxValue, int index) {
    if (index == n) {  // 处理完所有物品
        if (*currentWeight <= W && *currentValue > *maxValue) {  // 找到一个更优解
            *maxValue = *currentValue;
            printf("The max value is: %d\n", *maxValue);
            printf("The best choice is as follows:\n");
            for (int i = 0; i < n; i++) {
                if (selected[i]) {
                    printf("item %d\n", items[i].id);
                }
            }
            printf("----------\n");
        }
        return;
    }

    if (*currentWeight + items[index].weight <= W) {  // 当前物品可以装入背包
        selected[index] = true;  // 选中当前物品
        // 更新当前总重量和总价值
        *currentWeight += items[index].weight;
        *currentValue += items[index].value;
        // 选择当前物品的情况下，递归处理下一个物品
        backtrack(items, n, W, selected, currentWeight, currentValue, maxValue, index + 1);

        selected[index] = false;  // 撤销选择当前的物品
        // 恢复不选择这个物品时的总重量和总价值
        *currentWeight -= items[index].weight;
        *currentValue -= items[index].value;
    }
    
    // 不选择当前物品(从index+1开始)的情况下，尝试所有可能的后续选择
    // 如果选择剩余物品的上界价值大于当前最大价值，则递归处理下一个物品
    if (upperBound(items, n, W, index + 1, *currentWeight, *currentValue) > *maxValue) {
        backtrack(items, n, W, selected, currentWeight, currentValue, maxValue, index + 1);  
    }
}


/**
 * 解决01背包问题
 * 
 * @param items 物品数组
 * @param n 物品数量
 * @param W 背包容量
 */
void knapsack(Item* items, int n, int W) {
    // 初始化
    bool selected[n];
    int currentWeight = 0;
    int currentValue = 0;
    int maxValue = 0;
    int index = 0;

    // 按照单位重量价值进行降序排序
    qsort(items, n, sizeof(Item), compare);
    printf("Sort by unitValue:\n");
    for (int i = 0; i < n; i++)
    {
        printf("item %d: weight = %d, value = %d, unitValue = %d\n", items[i].id, items[i].weight, items[i].value, items[i].value/items[i].weight);
    }
    printf("----------\n");
    

    backtrack(items, n, W, selected, &currentWeight, &currentValue, &maxValue, index);

    printf("The final best value is: %d\n", maxValue);
}

int main() {
    Item items[] = {
        {1, 10, 60},
        {2, 30, 120},
        {3, 20, 100}
    };
    int n = sizeof(items) / sizeof(items[0]);
    int W = 50;

    knapsack(items, n, W);

    return 0;
}
