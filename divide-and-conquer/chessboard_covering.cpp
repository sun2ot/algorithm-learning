#include <stdio.h>
#include <stdlib.h>

// 定义棋盘大小
#define BOARD_SIZE 8

// 定义特殊位置的值，用于标记骨牌覆盖的情况
#define SPECIAL_VALUE -1

// 定义骨牌的编号
int tile = 0;

// 定义棋盘数组
int board[BOARD_SIZE][BOARD_SIZE];

// 函数声明
void printBoard();
void chessboard(int tr, int tc, int dr, int dc, int size);

// 打印棋盘
void printBoard() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf("%2d ", board[i][j]);
        }
        printf("\n");
    }
}

// 棋盘覆盖函数
void chessboard(int tr, int tc, int dr, int dc, int size) {
    if (size == 1) {
        return;
    }

    int t = tile++;
    int s = size / 2;

    // 覆盖左上角子棋盘
    if (dr < tr + s && dc < tc + s) {
        chessboard(tr, tc, dr, dc, s);
    } else {
        board[tr + s - 1][tc + s - 1] = t;
        chessboard(tr, tc, tr + s - 1, tc + s - 1, s);
    }

    // 覆盖右上角子棋盘
    if (dr < tr + s && dc >= tc + s) {
        chessboard(tr, tc + s, dr, dc, s);
    } else {
        board[tr + s - 1][tc + s] = t;
        chessboard(tr, tc + s, tr + s - 1, tc + s, s);
    }

    // 覆盖左下角子棋盘
    if (dr >= tr + s && dc < tc + s) {
        chessboard(tr + s, tc, dr, dc, s);
    } else {
        board[tr + s][tc + s - 1] = t;
        chessboard(tr + s, tc, tr + s, tc + s - 1, s);
    }

    // 覆盖右下角子棋盘
    if (dr >= tr + s && dc >= tc + s) {
        chessboard(tr + s, tc + s, dr, dc, s);
    } else {
        board[tr + s][tc + s] = t;
        chessboard(tr + s, tc + s, tr + s, tc + s, s);
    }
}

int main() {
    int dr = 0; // 特殊位置的行号
    int dc = 0; // 特殊位置的列号

    // 初始化棋盘
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = SPECIAL_VALUE;
        }
    }

    // 调用棋盘覆盖函数
    chessboard(0, 0, dr, dc, BOARD_SIZE);

    // 打印棋盘
    printBoard();

    return 0;
}
