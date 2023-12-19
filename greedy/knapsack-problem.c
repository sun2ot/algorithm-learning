#include <stdio.h>
#include <stdlib.h>

struct Item {
    int weight;
    int value;
    char *name;  // 物品名称
};

/**
 * 比较函数，用于排序算法中的元素比较
 *
 * @param a 指向要比较的第一个元素的指针
 * @param b 指向要比较的第二个元素的指针
 * @return int 如果第一个元素小于第二个元素，则返回正数；如果第一个元素大于第二个元素，则返回负数；如果两个元素相等，则返回0
 */
int compare(const void *a, const void *b) {
    struct Item *itemA = (struct Item *)a;
    struct Item *itemB = (struct Item *)b;
    double r1 = (double)itemA->value / itemA->weight;  // 计算单位价值
    double r2 = (double)itemB->value / itemB->weight;
    return r2 - r1;
}

/**
 * 贪心算法解决背包问题
 *
 * @param capacity 背包的容量
 * @param items 物品数组
 * @param numItems 物品的数量
 */
void knapsackGreedy(int capacity, struct Item items[], int numItems) {
    qsort(items, numItems, sizeof(struct Item), compare);  // 按照单位价值从大到小排序

    double totalValue = 0.0;  // 背包中物品的总价值
    int currentWeight = 0;  // 背包中物品的总重量
    int i;

    for (i = 0; i < numItems; i++) {
        if (currentWeight + items[i].weight <= capacity) {  // 物品可以全部装入背包
            totalValue += items[i].value;
            currentWeight += items[i].weight;
            printf("selected all: %s, weight: %d, value: %d\n", items[i].name, items[i].weight, items[i].value);
        } else {  // 物品只能部分装入背包
            int remain = capacity - currentWeight;
            totalValue += items[i].value * ((double)remain / items[i].weight);
            printf("selected part: %s, weight: %d, value: %.2f\n", items[i].name, remain, items[i].value * ((double)remain / items[i].weight));
            break;  // 背包已经装满，退出循环
        }
    }

    printf("max value is: %f\n", totalValue);
}

int main() {
    struct Item items[] = {
        {10, 60, "item1"},
        {20, 100, "item2"},
        {50, 700, "item3"},
        {20, 1000, "item4"}
    };
    int numItems = sizeof(items) / sizeof(items[0]);

    knapsackGreedy(50, items, numItems);

    return 0;
}