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
    for (int len = 2; len <= n; len++) {
        for (int i = 1; i <= n - len + 1; i++) {
            int j = i + len - 1;
            dp[i][j] = INT_MAX;

            for (int k = i; k < j; k++) {
                int cost = dp[i][k] + dp[k + 1][j] + dimensions[i - 1] * dimensions[k] * dimensions[j];
                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                    split[i][j] = k; // 记录最优划分点
                }
            }
        }
    }

    // 返回最小计算次数
    return dp[1][n];
}

// 输出最优解
void printOptimalParenthesis(int split[MAX_MATRICES][MAX_MATRICES], int i, int j) {
    if (i == j) {
        printf("A%d", i);
    } else {
        printf("(");
        printOptimalParenthesis(split, i, split[i][j]);
        printOptimalParenthesis(split, split[i][j] + 1, j);
        printf(")");
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
