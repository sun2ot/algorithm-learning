#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/**
 * 打印解决方案
 * 
 * @param solution 解决方案数组
 * @param n 棋盘大小
 */
void printSolution(int* solution, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (solution[i] == j) {
                printf("Q ");
            } else {
                printf(". ");
            }
        }
        printf("\n");
    }
    printf("\n----------\n");
}


/**
 * 判断在指定位置放置皇后是否可行
 *
 * @param solution 存放皇后位置的数组
 * @param row      当前行数
 * @param col      当前列数
 * @return         如果安全放置皇后，则返回 true；否则返回 false
 */
bool isSafe(int* solution, int row, int col) {
    for (int i = 0; i < row; i++) {
        // 检查是否在同一列或同一斜线上
        if (solution[i] == col || abs(i - row) == abs(solution[i] - col)) {
            return false;
        }
    }
    return true;
}


/**
 * 解决N皇后问题的辅助函数
 * 
 * @param solution 存放皇后位置的数组
 * @param row 当前处理的行
 * @param n 皇后的数量
 */
void solveNQueensUtil(int* solution, int row, int n) {
    if (row == n) {
        // 处理完最后一行，表示找到一个解
        printSolution(solution, n);
        return;
    }

    for (int col = 0; col < n; col++) {  // 遍历当前行的每一列
        if (isSafe(solution, row, col)) {
            // 当前位置安全，将皇后放置在该位置
            solution[row] = col;

            // 递归地尝试放置下一行的皇后
            solveNQueensUtil(solution, row + 1, n);

            // 没有显式地撤销当前皇后的位置，这是因为我们使用了一个一维数组 solution 来存储每行皇后的列位置
            // 回溯：当递归返回到当前行时，我们会继续在其他列尝试放置皇后。在这个过程中，solution[row] 的值会被新的列位置覆盖，这实际上就是撤销了之前放置在该行的皇后。

        }
    }
}


/**
 * 解决N皇后问题
 * 
 * @param n 皇后的数量
 */
void solveNQueens(int n) {
    int* solution = (int*)malloc(n * sizeof(int));  // 申请分配用于存放皇后位置的数组

    solveNQueensUtil(solution, 0, n);  // 从第0行开始处理

    free(solution);  // 释放内存
}


int main() {
    int n = 4;
    solveNQueens(n);

    return 0;
}
