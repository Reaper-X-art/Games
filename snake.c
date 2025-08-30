// Simple Snake Game in C
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define HEIGHT 20
#define WIDTH 40

int snakeTailX[100], snakeTailY[100];
int snakeTailLen;
int gameover, direction, score;
int x, y, fruitx, fruity;

void setup() {
    gameover = 0;
    x = WIDTH / 2;
    y = HEIGHT / 2;
label1:
    fruitx = rand() % WIDTH;
    if (fruitx == 0) goto label1;
label2:
    fruity = rand() % HEIGHT;
    if (fruity == 0) goto label2;
    score = 0;
    snakeTailLen = 0;
    direction = 0;  
}

void draw() {
    system("cls");
    int i, j, k;
    for (i = 0; i < WIDTH + 2; i++)
        printf("-");
    printf("\n");

    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j <= WIDTH; j++) {
            if (j == 0 || j == WIDTH)
                printf("#");
            else if (i == y && j == x)
                printf("O");
            else if (i == fruity && j == fruitx)
                printf("*");
            else {
                int isTail = 0;
                for (k = 0; k < snakeTailLen; k++) {
                    if (i == snakeTailY[k] && j == snakeTailX[k]) {
                        printf("o");
                        isTail = 1;
                    }
                }
                if (!isTail)
                    printf(" ");
            }
        }
        printf("\n");
    }

    for (i = 0; i < WIDTH + 2; i++)
        printf("-");
    printf("\n");
    printf("Score = %d\n", score);
    printf("Press W/A/S/D to move, X to quit.\n");
}

void input() {
    if (kbhit()) {
        switch (tolower(getch())) {
            case 'a':
                if (direction != 2) direction = 1;  
                break;
            case 'd':
                if (direction != 1) direction = 2;  
                break;
            case 'w':
                if (direction != 4) direction = 3;  
                break;
            case 's':
                if (direction != 3) direction = 4;  
                break;
            case 'x':
                gameover = 1;
                break;
        }
    }
}

void logic() {
    Sleep(100);  

    int prevX = snakeTailX[0];
    int prevY = snakeTailY[0];
    int prev2X, prev2Y;
    snakeTailX[0] = x;
    snakeTailY[0] = y;
    for (int i = 1; i < snakeTailLen; i++) {
        prev2X = snakeTailX[i];
        prev2Y = snakeTailY[i];
        snakeTailX[i] = prevX;
        snakeTailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (direction) {
        case 1: x--; break;  
        case 2: x++; break; 
        case 3: y--; break; 
        case 4: y++; break;
    }

    if (x >= WIDTH || x < 1 || y >= HEIGHT || y < 0)
        gameover = 1;

    for (int i = 0; i < snakeTailLen; i++) {
        if (snakeTailX[i] == x && snakeTailY[i] == y)
            gameover = 1;
    }

    if (x == fruitx && y == fruity) {
        score += 10;
label3:
        fruitx = rand() % WIDTH;
        if (fruitx == 0) goto label3;
label4:
        fruity = rand() % HEIGHT;
        if (fruity == 0) goto label4;
        snakeTailLen++;
    }
}

int main() {
    setup();
    while (!gameover) {
        draw();
        input();
        logic();
    }
    printf("Game Over! Final Score: %d\n", score);
    return 0;
}
