#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>

enum MapElement {
    ROAD = 0,
    WALL = 1,
    TARGET = 3,
    BOX = 4,
    MAN = 5,
    BOX_ON_TARGET = 7,
    MAN_ON_TARGET = 8
};

struct Point {
    int x;
    int y;
};

// define map array
static int map[8][8];
static int maxX;
static int maxY;

// the man position
static Point manPos;

// define four direction
const Point UP = { 0, -1 };
const Point DOWN = { 0, 1 };
const Point LEFT = { -1, 0 };
const Point RIGHT = { +1, 0 };


void initGame();

void drawMap();

void keyPress();

void moveItem(Point direction);

int checkGame();

int main() {
    initGame();
    int checkOut = 0;

    while (1) {
        system("cls");
        drawMap();
        keyPress();
        checkOut = checkGame();
        if (checkOut != 0) {
            break;
        }
    }

    system("cls");
    drawMap();

    switch (checkOut) {
    case 1:
        printf("You win!\n");
        break;
    case -1:
        printf("You failed!\n");
        break;
    }

    system("pause");

    return 0;
}

void initGame() {
    // map array
    int initMap[8][8] = {
            {1, 1, 1, 1, 1, 1, 1, 1},
            {1, 3, 4, 0, 1, 1, 1, 1},
            {1, 0, 3, 0, 0, 0, 0, 1},
            {1, 0, 1, 4, 1, 1, 0, 1},
            {1, 0, 1, 0, 5, 1, 0, 1},
            {1, 0, 1, 0, 1, 0, 0, 1},
            {1, 0, 0, 0, 0, 4, 3, 1},
            {1, 1, 1, 1, 1, 1, 1, 1}
    };

    //return map[y][x] array x,y
    maxX = sizeof(map[0]) / sizeof(map[0][0]);
    maxY = sizeof(map) / sizeof(map[0]);

    // copy initial map to global map variable
    memcpy(&map[0][0], &initMap[0][0], maxX * maxY * sizeof(int));

    // get the man position
    for (int y = 0; y < maxY; y++) {
        for (int x = 0; x < maxX; x++) {
            if (map[y][x] == MAN) {
                manPos.x = x;
                manPos.y = y;
            }
        }
    }
}

void drawMap() {
    printf("max ARR[%d,%d],the man on(%d,%d)\n", maxX, maxY, manPos.x, manPos.y);
    for (int y = 0; y < maxY; y++) {
        for (int x = 0; x < maxX; x++) {
            switch (map[y][x]) {
            case ROAD:
                printf(" ");
                break;
            case WALL:
                printf("#");
                break;
            case TARGET:
                printf("0");
                break;
            case BOX:
                printf("$");
                break;
            case MAN:
                printf("@");
                break;
            case BOX_ON_TARGET:
                printf("O");
                break;
            case MAN_ON_TARGET:
                printf("P");
                break;
            }
        }
        printf("\n");
    }

}


void keyPress() {
    char key = _getch();

    switch (key) {
    case 'W':
    case 'w':
    case 72:
        moveItem(UP);
        break;
    case 'S':
    case 's':
    case 80:
        moveItem(DOWN);
        break;
    case 'A':
    case 'a':
    case 75:
        moveItem(LEFT);
        break;
    case 'D':
    case 'd':
    case 77:
        moveItem(RIGHT);
        break;
    }

}

void moveItem(Point direction) {
    // the next item position
    Point next = { manPos.x + direction.x, manPos.y + direction.y };
    // the next item is ROAD or TARGET,then exchange MAN and next item.
    if (map[next.y][next.x] == ROAD || map[next.y][next.x] == TARGET) {
        map[next.y][next.x] += MAN;
        map[manPos.y][manPos.x] -= MAN;

        // update man position
        manPos = { manPos.x + direction.x, manPos.y + direction.y };
        return;
    }

    // the second direction variable base on next
    Point next2 = next;
    if (direction.x == 0) {
        next2.y += (direction.y > 0 ? 1 : -1);
    }
    else {
        next2.x += (direction.x > 0 ? 1 : -1);
    }

    // the next item is box,then judge the second item
    if (map[next.y][next.x] == BOX || map[next.y][next.x] == BOX_ON_TARGET) {
        if (map[next2.y][next2.x] == ROAD || map[next2.y][next2.x] == TARGET) {
            map[next2.y][next2.x] += BOX;
            map[next.y][next.x] -= BOX;
            map[next.y][next.x] += MAN;
            map[manPos.y][manPos.x] -= MAN;

            // update man position
            manPos = { manPos.x + direction.x, manPos.y + direction.y };
            return;
        }
    }


}


int checkGame() {
    // check BOX nearby item
    // TODO: more case to improve
    for (int y = 0; y < maxY; y++) {
        for (int x = 0; x < maxX; x++) {
            if (map[y][x] == BOX) {
                int upItem = map[y - 1][x] == WALL || map[y - 1][x] == BOX_ON_TARGET;
                int downItem = map[y + 1][x] == WALL || map[y + 1][x] == BOX_ON_TARGET;
                int leftItem = map[y][x - 1] == WALL || map[y][x - 1] == BOX_ON_TARGET;
                int rightItem = map[y][x + 1] == WALL || map[y][x + 1] == BOX_ON_TARGET;

                int checkOut = (upItem && rightItem) || (rightItem && downItem) ||
                    (downItem && leftItem) || (leftItem && upItem);
                if (checkOut) {
                    return -1;
                }
            }
        }
    }

    // check if exists TARGET or Box. then continue game
    for (int y = 0; y < maxY; y++) {
        for (int x = 0; x < maxX; x++) {
            if (map[y][x] == TARGET || map[y][x] == BOX) {
                return 0;
            }
        }
    }
    // else win
    return 1;
}
