#include <stdio.h>
#include <stdbool.h>

#define N 8


/**
 * 打印棋盘
 * 
 * @param board 棋盘数组
 */
void printSolution(int board[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%c ", board[i][j] ? 'Q' : '.');  // 1 -> Q, 0 -> .
        }
        printf("\n");
    }
    printf("\n----------\n");
}


/**
 * 判断皇后在棋盘上的某个位置是否可行
 *
 * @param board 棋盘
 * @param row 行索引
 * @param col 列索引
 * @return 如果位置安全则返回true，否则返回false
 */
bool isSafe(int board[N][N], int row, int col) {
    int i, j;

    // 检查当前列
    for (i = 0; i < row; i++) {  // 只需要检查当前行之前的行
        if (board[i][col]) {  // board值为1表示有皇后
            return false;
        }
    }

    // 检查左上方对角线: 斜率为-1的直线
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--) {  // 往上一格,往左一格 -> 向左上方移动
        if (board[i][j]) {
            return false;
        }
    }

    // 检查右上方对角线: 斜率为1的直线
    for (i = row, j = col; i >= 0 && j < N; i--, j++) {  // 往上一格,往右一格 -> 向右上方移动
        if (board[i][j]) {
            return false;
        }
    }

    return true;
}


/**
 * 解决N皇后问题的辅助函数
 * 
 * @param board 棋盘数组
 * @param row 当前行数
 * @return 如果成功找到解决方案，则返回true；否则返回false
 */
bool solveNQueensUtil(int board[N][N], int row) {
    // 所有行都已经放置了皇后，表示找到了一个解
    if (row == N) {
        printSolution(board);
        return true;
    }

    bool res = false;
    for (int col = 0; col < N; col++) {  // 尝试在给定的当前行中的每一列放置皇后
        if (isSafe(board, row, col)) {
            // 在当前位置放置皇后
            board[row][col] = 1;

            // 递归地尝试放置下一行的皇后
            res = solveNQueensUtil(board, row + 1) || res;

            // 回溯，撤销当前位置的皇后
            board[row][col] = 0;
        }
    }

    return res;
}


/**
 * 解决 N 皇后问题，将解决方案打印出来。
 */
void solveNQueens() {
    int board[N][N] = {0};

    if (!solveNQueensUtil(board, 0)) {
        printf("无解\n");
    }
}

int main() {
    solveNQueens();

    return 0;
}
