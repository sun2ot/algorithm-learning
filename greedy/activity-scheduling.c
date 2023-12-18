#include <stdio.h>
#include <stdlib.h>

// 活动结构体
typedef struct {
    int start;
    int finish;
} Activity;

// 比较函数，用于排序活动
int compare(const void* a, const void* b) {
    // 类型转换的优先级低，因此需要加两重括号
    return ((Activity*)a)->finish - ((Activity*)b)->finish;
}

// 贪心算法解决活动安排问题
void activityScheduling(Activity activities[], int n) {

    // 按照结束时间对活动进行排序
    qsort(activities, n, sizeof(Activity), compare);

    // 输出排序后的activities数组
    printf("Sorted activities, format is 'id: (start time, end time)': \n");
    for (int i = 0; i < n; i++) {
        printf("%d: (%d, %d)\n", i + 1, activities[i].start, activities[i].finish);
    }

    printf("selected activity, format is 'id: (start time, end time)': \n");

    // 选择第一个活动
    int i = 0;
    printf("%d: (%d, %d)\n", i + 1, activities[i].start, activities[i].finish);

    // 选择其他活动
    for (int j = 1; j < n; j++) {
        if (activities[j].start >= activities[i].finish) {  // 活动j与活动i不冲突
            i = j;  // 选择活动j
            printf("%d: (%d, %d)\n", i + 1, activities[i].start, activities[i].finish);
        }
    }
}

int main() {
    Activity activities[] = {
        {2, 13},
        {1, 4},
        {8, 11},
        {0, 6},
        {5, 7},
        {3, 8},
        {5, 9},
        {3, 5},
        {6, 10},
        {12, 14},
        {8, 12}
    };
    int n = sizeof(activities) / sizeof(activities[0]);

    activityScheduling(activities, n);

    return 0;
}
