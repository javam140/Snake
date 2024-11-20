#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>


struct Snake {
    //two dynamic arrays for x and y coordinates, from the head to the tail
    int* x;
    int* y;
    int length;
};
typedef struct Snake Snake;


struct Apple {
    int x;
    int y;
};
typedef struct Apple Apple;


boolean isSnakeBodyThere(Snake* snake, int x, int y) {
    //iterate through all coordinates of snake body
    for (int i = 0; i < snake->length; i++) {
        if (snake->x[i] == x && snake->y[i] == y) {
            return 1;
        }
    }
    return 0;
}

void render(Snake* snake, Apple apple) {
    // create frame and assign x and y to each field    for now 10x10
    //clear console
    system("cls");
    for (int i = 0; i < 10; i++) {
        printf("|");
        for (int j = 0; j < 10; j++) {
            if (isSnakeBodyThere(snake, j, i)) {
                printf("O");
            }
            else if (i == apple.y && j == apple.x) {
                printf("*");
            } 
            
            else {
                printf(" ");
            }
            printf("|");
        }
        printf("\n");
    }
}

void endGame(Snake* snake) {
    //print game over message and score it is the snake's length
    printf("Game Over! Your score is: %d\n", snake->length - 1);
    free(snake->x);
    free(snake->y);
    free(snake);
    exit(0);
}

void moveSnake(Snake* snake, char direction) {
    int* headX = &(snake->x[0]);
    int* headY = &(snake->y[0]);
    if (direction == 'w' && *headY > 0) {
        if (isSnakeBodyThere(snake, *headX, *headY - 1)) {
            endGame(snake);
        }
        else {
            // Move the snake up
            (*headY)--;
            // Shift the rest of the body
            for (int i = snake->length - 1; i > 0; i--) {
                snake->x[i] = snake->x[i-1];
                snake->y[i] = snake->y[i-1];
            }
        }
    }

    else if (direction == 'a' && *headX > 0) {
        if (isSnakeBodyThere(snake, *headX - 1, *headY)) {
            endGame(snake);
        }
        else {
            // Move the snake left
            (*headX)--;
            // Shift the rest of the body
            for (int i = snake->length - 1; i > 0; i--) {
                snake->x[i] = snake->x[i-1];
                snake->y[i] = snake->y[i-1];
            }
        }
    }

    else if (direction == 's' && *headY < 9) {
        if (isSnakeBodyThere(snake, *headX, *headY + 1)) {
            endGame(snake);
        }
        else {
            // Move the snake down
            (*headY)++;
            // Shift the rest of the body
            for (int i = snake->length - 1; i > 0; i--) {
                snake->x[i] = snake->x[i-1];
                snake->y[i] = snake->y[i-1];
            }
        }
    }

    else if (direction == 'd' && *headX < 9) {
        if (isSnakeBodyThere(snake, *headX + 1, *headY)) {
            endGame(snake);
        }
        else {
            // Move the snake right
            (*headX)++;
            // Shift the rest of the body
            for (int i = snake->length - 1; i > 0; i--) {
                snake->x[i] = snake->x[i-1];
                snake->y[i] = snake->y[i-1];
            }
        }
    }
    else {
        endGame(snake);
    }

}

void growSnake(Snake* snake) {
    snake->x = realloc(snake->x, sizeof(int) * ((size_t)snake->length + 1));
    snake->y = realloc(snake->y, sizeof(int) * ((size_t)snake->length + 1));

    snake->x[snake->length] = snake->x[snake->length - 1];
    snake->y[snake->length] = snake->y[snake->length - 1];
    snake->length++;
}

int main() {
    srand((unsigned int)time(NULL)); 
    DWORD timeout = 1000;

    printf("Choose difficulty level (1-3): ");
    int difficulty;
    scanf("%d", &difficulty);
    timeout -= (DWORD)((difficulty - 1) * 200);

    int firstSnakeX = rand() % 10;
    int firstSnakeY = rand() % 10;
    int appleX, appleY;
    do {
        appleX = rand() % 10;
        appleY = rand() % 10;
    } while (appleX == firstSnakeX && appleY == firstSnakeY);

    Snake* snake = malloc(sizeof(Snake));
    snake->x = malloc(sizeof(int));
    snake->y = malloc(sizeof(int));
    snake->x[0] = firstSnakeX;
    snake->y[0] = firstSnakeY;
    snake->length = 1;
    Apple apple = {appleX, appleY};

    render(snake, apple);
    char input = 'd';  // init direction
    growSnake(snake);
    render(snake, apple);
    Sleep(timeout);
    while (1) {
        if (snake->length == 100) {
            printf("Congratulations! You reached the maximum length of 100.\n");
            endGame(snake);
        }

        if (_kbhit()) {
            input = (char)_getch();
        }

        moveSnake(snake, input);

        if (snake->x[0] == apple.x && snake->y[0] == apple.y) {
            growSnake(snake);
            do {
                apple.x = rand() % 10;
                apple.y = rand() % 10;
            } while (isSnakeBodyThere(snake, apple.x, apple.y));
        }

        render(snake, apple);
        Sleep(timeout);
    }

    free(snake->x);
    free(snake->y);
    free(snake);
    return 0;
}