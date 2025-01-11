#define _CRT_SECURE_NO_WARNINGS
#define ANSI_RESET_ALL          "\x1b[0m"
#define ANSI_COLOR_RED          "\x1b[31m"
#define N 10
#define INF 1000000 /*INT_MAX*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


int copy_array[N][N]
= {
    { 0,     0,     0,     0,     0,     0,     0,     0,     0, 0 },
    { 0,     0,     0,     0,     0,     0,     0,     0,     0, 0 },
    { 0,     0,     0,     0,     0,     0,     0,     0,     0, 0 },
    { 0,     0,     0,     0,     0,     0,     0,     0,     0, 0 },
    { 0,     0,     0,     0,     0,     0,     0,     0,     0, 0 },
    { 0,     0,     0,     0,     0,     0,     0,     0,     0, 0 },
    { 0,     0,     0,     0,     0,     0,     0,     0,     0, 0 },
    { 0,     0,     0,     0,     0,     0,     0,     0,     0, 0 },
    { 0,     0,     0,     0,     0,     0,     0,     0,     0, 0 },
    { 0,     0,     0,     0,     0,     0,     0,     0,     0, 0 }
}
;

// добавить проверку нашелся ли путь
int array[N][N] = {
    {1,     2,     1,     2,     3,     1,     1,     1,     2, 1},
    {1, -1000, -1000,     1,     3,     1,     1, -1000,     1, 1},
    {2,     3,     1,     5, -1000, -1000,     1,     1,     1, 1},
    {1, -1000,     1,     2,     3, -1000, -1000,     1, -1000, 1},
    {1, -1000,     1,     1,     2,     1,     2,     1,     1, 1},
    {1,     1,     2, -1000, -1000, -1000, -1000,     100, -1000, 100},
    {1, -1000,     1,     1,     3, -1000,     1,     1,     2, 1},
    {1, -1000, -1000, -1000, -1000, -1000, -1000,     1,     2, 1},
    {1,     1,     1,     1, -1000,     1, -1000,     3, -1000, 1},
    {1,     1,     2,     3,     1,     1,     1, -1000, -1000, 1}
};

struct Point {
    int x, y, cost;
};

typedef struct Point point;
point queue[N * N];
int front = -1, rear = -1;
int visit[N][N];
int parent[N][N];
int visited[N][N];
int directions[8][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, -1}, {-1, 1} };
point end = { 0 , 1, 1 };
point start = { 3, 3, 1 };

void enqueue(point node) {
    queue[++rear] = node;
    if (front == -1) front = 0;
}

point dequeue() {
    return queue[front++];
}

int is_empty() {
    return front == -1 || front > rear;
}

int if_diagonal(x1, y1, x2, y2) {
    int res = 0;
    for (int i = 0; i < 8; i++) {
        if (x1 + directions[i][0] == x2 && y1 + directions[i][1] == y2) {
            res = 1;
        }
    }
    return res;
}

void find_cheapest_path(int start_x, int start_y, int end_x, int end_y) { // переделай на тип points
    

    enqueue((point) { start_x, start_y, array[start_x][start_y] });
    visit[start_x][start_y] = 1;

    while (!is_empty()) {
        point current = dequeue();
        point min_point = { -1, -1, INF };

        for (int i = 0; i < 8; i++) {
            int new_x = current.x + directions[i][1];
            int new_y = current.y + directions[i][0];
            if ((array[new_x][new_y] != -1000) && (new_x >= 0) && (new_y >= 0) && (new_x < N) && (new_y < N) && (copy_array[new_x][new_y] > copy_array[current.x][current.y] + array[new_x][new_y])) {
                copy_array[new_x][new_y] = copy_array[current.x][current.y] + array[new_x][new_y];
                if (copy_array[new_x][new_y] == 0){
                    printf("\n%d %d\n", current.x, current.y);
                }
                visited[new_x][new_y] = 1;
                if (min_point.cost > copy_array[new_x][new_y]) {
                    min_point.cost = copy_array[new_x][new_y];
                    min_point.x = new_x;
                    min_point.y = new_y;
                }
                point next_point = { new_x, new_y };
                enqueue(next_point);
            }
        }
    }
}

void printing_the_path(int start_x, int start_y, int end_x, int end_y) {
    if (start_x == end_x && start_y == end_y) {
        //printf("Reached destination: (%d, %d)\n", end_x, end_y);
        printf(ANSI_COLOR_RED "Reached destination: (%d, %d)\n", end_x, end_y, ANSI_RESET_ALL);
        return;
    }
    point min_point = { -1, -1, INF };
    point current = { start_x, start_y, copy_array[start_x][start_y] };
    //array[current.x][current.y] *= -1;
    visit[start_x][start_y] = 1;
    for (int i = 0; i < 8; i++) {
        int new_x = current.x + directions[i][1];
        int new_y = current.y + directions[i][0];
        if (copy_array[new_x][new_y] < min_point.cost && array[new_x][new_y] != -1000 && !visit[new_x][new_y] && (new_x >= 0 && new_x < N) && (new_y >= 0 && new_y < N)) {
            min_point.cost = copy_array[new_x][new_y]; //разреши это если точка вне диапазона - единственный путь!
            min_point.x = new_x;
            min_point.y = new_y;
            //printf("\n%d %d\n", min_point.x, min_point.y);
        }
    }
    if (min_point.x != -1 && min_point.y != -1) {
        visit[min_point.x][min_point.y] = 1;
        array[min_point.x][min_point.y] *= -1;
        if (!if_diagonal(min_point.x, min_point.y, end_x, end_y)) {
            printing_the_path(min_point.x, min_point.y, end_x, end_y);
        }
        else {
            visit[min_point.x][min_point.y] = 1;
            return;
        }
    }
}
// проход по массиву от начала до конца, выбирается 1 минимальная точка от соседей и от нее дальше вызывается рекурсияю выбранная мин точка *-1

void print_grid() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (array[i][j] < 0 && array[i][j] != -1000) {
                printf("\033[1;31m%6d \033[0m", array[i][j]);
            }
            else {
                printf("%6d ", array[i][j]);
            }
        }
        printf("\n");
    }
}

int main() {
    int s_x, s_y, e_x, e_y;
    printf("Enter start point: ");
    scanf("%d %d", &s_x, &s_y);
    printf("Enter finish point: ");
    scanf("%d %d", &e_x, &e_y);
    if (array[s_x][s_y] == -1000 || array[e_x][e_y] == -1000) {
        printf("Choose another points");
        return -1;
    }

   for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (array[i][j] == -1000) {
                copy_array[i][j] = -1000;
            }
            else {
                copy_array[i][j] = INF;
            }
        }
    }
    copy_array[s_x][s_y] = array[s_x][s_y];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            visited[i][j] = 0;
        }
    }
    printf("Original path:\n");
    print_grid();

    find_cheapest_path(s_x, s_y, e_x, e_y); // Находим путь от (0, 0) до (9, 9)
    if (copy_array[e_x][e_y] == -1000) {
        printf("\nPath is unavaible\n");
        return -1;
    }
    printing_the_path(e_x, e_y, s_x, s_y);
    array[s_x][s_y] *= -1;
    array[e_x][e_y] *= -1;
    printf("\nFinal path:\n");
    print_grid();
    printf("\n");
    printf("\n");
}

// ЗАДАНИЕ:
// В массиве 10x10 задаются координаты начала и конца. У каждой точки есть свой вес != 1. Недоступные точки имеют вес -1000.
// Необходимо вывести самый дешевый путь из начальной точки в конечную.