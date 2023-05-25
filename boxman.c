#include <stdio.h>
#include <conio.h>
#include <stdbool.h> //C语言并未定义布尔类型，引入此头文件可以使用布尔类型
#include <windows.h>

int arr[2];
// 构造地图数组
int map[8][8] = {{1, 1, 1, 1, 1, 1, 1, 1},
                 {1, 3, 4, 0, 0, 0, 0, 1},
                 {1, 0, 1, 1, 1, 1, 0, 1},
                 {1, 0, 0, 0, 5, 0, 0, 1},
                 {1, 0, 1, 1, 0, 1, 0, 1},
                 {1, 0, 1, 1, 0, 1, 0, 1},
                 {1, 0, 0, 0, 0, 4, 3, 1},
                 {1, 1, 1, 1, 1, 1, 1, 1}};

// 枚举地图元素
enum MapElement {
    ROAD = 0,
    WALL = 1,
    TARGET = 3,
    BOX = 4,
    PLAYER = 5,
    BOX_IN_TARGET = 7,
    PLAYER_IN_TARGET = 8
};

// 绘制地图
void drawMap() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            switch (map[i][j]) {
                case ROAD:
                    printf(" ");
                    break;
                case WALL:
                    printf("#");
                    break;
                case TARGET:
                    printf("$");
                    break;
                case BOX:
                    printf("o");
                    break;
                case PLAYER:
                    printf("@");
                    break;
                case BOX_IN_TARGET:
                    printf("O");
                    break;
                case PLAYER_IN_TARGET:
                    printf("P");
                    break;
            }
        }
        printf("\n");
    }
}

// 获取PLAYER坐标指针
int *getPlayerPos() {
    int *pos = arr;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (map[i][j] == PLAYER ||
                map[i][j] == PLAYER_IN_TARGET) {
                pos[0] = i;
                pos[1] = j;
                break;
            }
        }
    }
    return pos;
}

// 接收用户按键
void keyDown() {
    // windows需引入conio.h
    char userKey = _getch();

    int *pos = getPlayerPos();
    int x = pos[0];
    int y = pos[1];

    switch (userKey) {
        case 'W':
        case 'w':
        case 72:
            // 上方是路或者目标点
            if (map[x - 1][y] == ROAD ||
                map[x - 1][y] == TARGET) {
                map[x][y] -= PLAYER;
                map[x - 1][y] += PLAYER;
            }

            // 上方是箱子，则判断箱子上方元素
            if (map[x - 1][y] == BOX ||
                map[x - 1][y] == BOX_IN_TARGET) {
                if (map[x - 2][y] == TARGET ||
                    map[x - 2][y] == ROAD) {
                    map[x - 2][y] += BOX;
                    map[x - 1][y] -= BOX;
                    map[x - 1][y] += PLAYER;
                    map[x][y] -= PLAYER;
                }
            }
            break;

        case 'S':
        case 's':
        case 80:
            if (map[x + 1][y] == ROAD ||
                map[x + 1][y] == TARGET) {
                map[x][y] -= PLAYER;
                map[x + 1][y] += PLAYER;
            }

            if (map[x + 1][y] == BOX ||
                map[x + 1][y] == BOX_IN_TARGET) {
                if (map[x + 2][y] == TARGET ||
                    map[x + 2][y] == ROAD) {
                    map[x + 2][y] += BOX;
                    map[x + 1][y] -= BOX;
                    map[x + 1][y] += PLAYER;
                    map[x][y] -= PLAYER;
                }
            }
            break;
        case 'A':
        case 'a':
        case 75:
            if (map[x][y - 1] == ROAD ||
                map[x][y - 1] == TARGET) {
                map[x][y] -= PLAYER;
                map[x][y - 1] += PLAYER;
            }

            if (map[x][y - 1] == BOX ||
                map[x][y - 1] == BOX_IN_TARGET) {
                if (map[x][y - 2] == TARGET ||
                    map[x][y - 2] == ROAD) {
                    map[x][y - 2] += BOX;
                    map[x][y - 1] -= BOX;
                    map[x][y - 1] += PLAYER;
                    map[x][y] -= PLAYER;
                }
            }
            break;
        case 'D':
        case 'd':
        case 77:
            if (map[x][y + 1] == ROAD ||
                map[x][y + 1] == TARGET) {
                map[x][y] -= PLAYER;
                map[x][y + 1] += PLAYER;
            }

            if (map[x][y + 1] == BOX ||
                map[x][y + 1] == BOX_IN_TARGET) {
                if (map[x][y + 2] == TARGET ||
                    map[x][y + 2] == ROAD) {
                    map[x][y + 2] += BOX;
                    map[x][y + 1] -= BOX;
                    map[x][y + 1] += PLAYER;
                    map[x][y] -= PLAYER;
                }
            }
            break;
    }
}

bool winCheck() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (map[i][j] == TARGET ||
                map[i][j] == PLAYER_IN_TARGET) {
                return false;
            }
        }
    }
    return true;
}


int main() {
    while (1) {
        drawMap();
        keyDown();
        system("cls");
        if (winCheck()) {
            break;
        }
    }
    drawMap(); //绘制最后的结果图
    printf("You win!\n");
    system("pause");
    return 0;
}
