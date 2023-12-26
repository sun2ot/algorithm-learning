#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define LENGTH 6  // 网格的边长
#define MAX_LENGTH (LENGTH + 2)  // 网格的边长加上边界

int grid[MAX_LENGTH][MAX_LENGTH];  // 网格

typedef struct {  // 网格位置
    int row, col;
} Position;

typedef struct {
    Position data[100]; // 假设队列长度不超过100
    int front, rear;
} Queue;

/**
 * 初始化队列。
 *
 * @param q 队列指针
 */
void initQueue(Queue *q) {
    q->front = q->rear = -1;  // 队列为空
}

bool isEmpty(Queue *q) {
    return q->front == -1;  // 队列为空
}

/**
 * 将位置pos入队列
 * 
 * @details 将新探测的布线位置(活结点)入队
 *
 * @param q 队列指针
 * @param pos 位置
 */
void enqueue(Queue *q, Position pos) {
    if (q->rear == 99) {  // 队列已满
        printf("Queue overflow\n");
        exit(1);
    }
    // 调整指针
    if (q->front == -1) {  // 队列为空
        q->front = q->rear = 0;  // 队首和队尾都指向新元素
    } else {
        q->rear++;  // 队尾指向新元素
    }
    // 将新元素放入队尾
    q->data[q->rear] = pos; 
}

/**
 * 出队操作，从队列中取出一个元素
 * 
 * @param q 队列指针
 * @return 取出的元素
 */
Position dequeue(Queue *q) {
    if (isEmpty(q)) {  // 队列为空
        printf("Queue is empty\n");
        exit(1);
    }
    Position temp = q->data[q->front];  // 取出队首元素
    if (q->front == q->rear) {  // 队列中只有一个元素
        q->front = q->rear = -1;  // 队列置为空
    } else {
        q->front++;  // 队首指针向后移动
    }
    return temp;
}

/**
 * 打印布线问题的网格
 */
void Print() {
    for (int i = 1; i < MAX_LENGTH - 1; i++) {
        for (int j = 1; j < MAX_LENGTH - 1; j++)
            printf("%3d", grid[i][j]);
        printf("\n");
    }
    printf("\n");
}

/**
 * 在给定的起点和终点之间查找路径。
 *
 * @param start 起点位置
 * @param finish 终点位置
 * @param PathLen 路径长度的指针
 * @param path 路径的指针
 * @return 如果找到路径，则返回true；否则返回false。
 */
bool FindPath(Position start, Position finish, int *PathLen, Position **path) {
    Position nextStep[4] = {
        {0, 1},  // 右
        {1, 0},  // 下
        {0, -1}, // 左
        {-1, 0}  // 上
    };

    Position here, next;  // 当前位置和下一个位置
    // 将起点位置赋值给当前位置
    here.row = start.row;  
    here.col = start.col;
    grid[start.row][start.col] = 1;  // 起始点置为1表示已访问
    Queue Q;
    initQueue(&Q);

    while (true) {
        for (int i = 0; i < 4; i++) {  // 检查当前位置的四个方向
            // 四次循环分别检查右、下、左、上四个方向
            next.row = here.row + nextStep[i].row;  
            next.col = here.col + nextStep[i].col;
            // 该位置未被访问过且不是障碍物/边界
            if (grid[next.row][next.col] == 0 && next.row != -1 && next.col != -1) {  
                grid[next.row][next.col] = grid[here.row][here.col] + 1;  // 更新到达该位置的路径长度
                if (next.row == finish.row && next.col == finish.col)   // 到达目标终点
                    break;

                enqueue(&Q, next);  // 将新探测的布线位置(活结点)入队
            }
        }

        if (next.row == finish.row && next.col == finish.col)   // 对于目标终点，不再探测
            break;
        if (isEmpty(&Q)) return false;  // 队列为空，说明没有路径

        here = dequeue(&Q);  // 取出队首元素，作为新的当前位置
    }

    *PathLen = grid[finish.row][finish.col];  // grid终点存储了到达此处的路径长度
    *path = (Position *)malloc(*PathLen * sizeof(Position));  // 分配存储路径轨迹的空间
    here = finish;  // 从终点开始回溯

    for (int j = *PathLen - 1; j >= 0; j--) {  
        (*path)[j] = here;  // 将当前位置存入路径轨迹
        for (int i = 0; i < 4; i++) {  // 检查当前位置的四个方向
            next.row = here.row + nextStep[i].row;  
            next.col = here.col + nextStep[i].col;
            // 回溯时路径长度j逐渐减小，因此若当前位置四周有路径长度为j的点，则说明是上一个点
            if (grid[next.row][next.col] == j)  
                break;
        }
        here = next;  // 将回溯的点作为新的当前位置
    }

    return true;
}

int main() {
    int countNum = 0;  // 路径长度
    grid[2][3] = grid[3][4] = grid[3][5] = grid[4][2] = -1;  // 障碍物
    printf("The initial grid is as follows: \n");
    Print();

    Position start = {2, 1};  // 起点
    Position finish = {4, 6};  // 终点

    printf("Start point of wiring: (%3d,%3d)\n", start.row, start.col);
    printf("End point of wiring: (%3d,%3d)\n", finish.row, finish.col);

    Position *path;  // 路径
    if (FindPath(start, finish, &countNum, &path)) {
        printf("\nThe final result is as follows: \n");
        Print();

        printf("The length of the route: %d\n", countNum - 1);
        printf("The route is: ");
        // 0是起点，countNum-1是终点
        for (int i = 0; i < countNum; i++) {
            printf("->(%d, %d)", path[i].row, path[i].col);
        }
        printf("\n");
    } else {
        printf("No path found!\n");
    }

    free(path);
    return 0;
}
