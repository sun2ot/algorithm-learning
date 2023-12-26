#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 100

// 物品
typedef struct {
    int id;
    int weight;
    int value;
} Item;

// 解空间节点
typedef struct {
    int level;  // 层号
    int profit;  // 当前总价值
    int weight;  // 当前背包重量
    float bound;  // 价值上界
} Node;

int max(int a, int b) {
    return (a > b) ? a : b;
}

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
 * 计算节点的上界值。
 *
 * @param node 节点对象
 * @param n 物品数量
 * @param capacity 背包容量
 * @param items 物品数组
 * @return 上界值
 */
float bound(Node node, int n, int capacity, Item* items) {
    if (node.weight >= capacity) {  // 背包已满
        return 0;
    }

    float bound = node.profit;  // 初始化为当前节点的总价值
    int j = node.level + 1;  // 当前决策层的下一层，下一个物品的索引
    int totalWeight = node.weight;  // 当前背包重量

    while (j < n && totalWeight + items[j].weight <= capacity) {  // 下一个物品不是最后一个，且可以全部装下
        // 更新总重量和价值上界
        totalWeight += items[j].weight;  
        bound += items[j].value;
        j++;  // 继续考虑下一个物品
    }

    if (j < n) {  // 无法全部装下下一个物品
        bound += (capacity - totalWeight) * (float)items[j].value / items[j].weight;
    }

    return bound;
}

/**
 * 背包问题求解函数
 *
 * @param items 物品数组
 * @param n 物品数量
 * @param capacity 背包容量
 * @return 最大价值
 */
int knapsack(Item* items, int n, int capacity) {
    Node u, v;  // v: 根节点，u: 扩展节点
    int maxProfit = 0;  // 初始化当前最大收益

    // 创建优先队列
    Node priorityQueue[MAX_SIZE];
    int front = -1;  // 最后一个被移除的元素的位置
    int rear = 0;  // 下一个要添加的元素的位置

    // 初始化根节点
    v.level = -1;
    v.profit = 0;
    v.weight = 0;
    v.bound = bound(v, n, capacity, items);

    // 将根节点加入队列
    priorityQueue[rear++] = v;

    while (front != rear - 1) {  // front == rear - 1时，队列为空
        // 从队列中取出节点
        u = priorityQueue[++front];

        // 检查是否为可行节点
        if (u.bound > maxProfit) {
            // 选择当前物品
            v.level = u.level + 1;  
            v.weight = u.weight + items[v.level].weight;
            v.profit = u.profit + items[v.level].value;
            v.bound = bound(v, n, capacity, items);

            // 如果扩展后的节点为可行节点，更新最大收益
            if (v.weight <= capacity && v.profit > maxProfit) {
                maxProfit = v.profit;
            }

            // 如果扩展后的节点的界限值大于当前最大收益，将其加入队列
            if (v.bound > maxProfit) {
                priorityQueue[rear++] = v;
            }

            // 扩展右子节点（不选择当前物品）
            v.weight = u.weight;
            v.profit = u.profit;
            v.bound = bound(v, n, capacity, items);

            // 如果扩展后的节点的界限值大于当前最大收益，将其加入队列
            if (v.bound > maxProfit) {
                priorityQueue[rear++] = v;
            }
        }
    }

    return maxProfit;
}

int main() {
    // 01背包问题示例
    Item items[] = {
        {1, 10, 60},
        {2, 10, 70},
        {3, 20, 100},
        {4, 30, 120}
    };
    int n = sizeof(items) / sizeof(items[0]);
    int capacity = 40;

    // 按照单位重量价值进行降序排序
    qsort(items, n, sizeof(Item), compare);

    int maxProfit = knapsack(items, n, capacity);

    printf("The best value: %d\n", maxProfit);

    return 0;
}
