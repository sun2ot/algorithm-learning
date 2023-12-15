#include <stdio.h>
#include <limits.h>

// 定义矩阵的最大数量
#define MAX_MATRICES 100

/**
 * 使用动态规划解决矩阵连乘问题，并返回最小计算次数和最优解
 * 
 * @param dimensions 矩阵的维度数组
 * @param n 矩阵的数量
 * @param dp 存储最小计算次数的二维数组
 * @param split 存储最优划分点的二维数组
 * @return 最小计算次数
 */
int matrixChainOrder(int dimensions[], int n, int dp[MAX_MATRICES][MAX_MATRICES], int split[MAX_MATRICES][MAX_MATRICES]) {
    // 初始化dp数组和split数组
    for (int i = 1; i <= n; i++) {
        dp[i][i] = 0;
    }

    // 计算子问题的最优解和划分点
    for (int len = 2; len <= n; len++) {  // 子问题规模
        for (int i = 1; i <= n - len + 1; i++) {  // 子问题的起始位置
            int j = i + len - 1;  // 子问题的结束位置
            dp[i][j] = INT_MAX;  // 初始化最优值为最大值

            for (int k = i; k < j; k++) {  // 子问题的划分点
                int cost = dp[i][k] + dp[k + 1][j] + dimensions[i - 1] * dimensions[k] * dimensions[j];
                if (cost < dp[i][j]) {  
                    dp[i][j] = cost;  // 更新最优值
                    split[i][j] = k; // 记录最优划分点
                }
            }
        }
    }

    // 返回最小计算次数
    return dp[1][n];
}


/**
 * 输出最优解
 * 
 * @param split 分割矩阵的位置
 * @param i 矩阵的起始位置
 * @param j 矩阵的结束位置
 */
void printOptimalParenthesis(int split[MAX_MATRICES][MAX_MATRICES], int i, int j) {
    if (i == j) {  // 矩阵只有一个时，直接输出
        printf("A%d", i);
    } else {  // 矩阵有多个时，递归输出
        printf("(");  // 输出左括号
        printOptimalParenthesis(split, i, split[i][j]);  // 输出左边的矩阵链的
        printOptimalParenthesis(split, split[i][j] + 1, j);  // 输出右边的矩阵链
        printf(")");  // 输出右括号
    }
}

int main() {
    int dimensions[] = {10, 30, 5, 60}; // 矩阵的维度
    int n = sizeof(dimensions) / sizeof(dimensions[0]) - 1; // 矩阵的数量

    int dp[MAX_MATRICES][MAX_MATRICES]; // 保存子问题的最优解
    int split[MAX_MATRICES][MAX_MATRICES]; // 保存最优划分点

    int minOperations = matrixChainOrder(dimensions, n, dp, split);
    printf("最小计算次数为：%d\n", minOperations);

    printf("最优解为：");
    printOptimalParenthesis(split, 1, n);
    printf("\n");

    return 0;
}
