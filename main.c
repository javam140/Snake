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
    // we must create frame and assign x and y to each field    for now 10x10
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

    if (direction == 'a' && *headX > 0) {
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

    if (direction == 's' && *headY < 9) {
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

    if (direction == 'd' && *headX < 9) {
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




int main() {
    //printf("this is square %c\n",254);
    //two random ints x and y
    int firstSnakeX = rand() % 10;
    int firstSnakeY = rand() % 10;
    int appleX, appleY;
    do {
        appleX = rand() % 10;
        appleY = rand() % 10;
    } while (appleX == firstSnakeX && appleY == firstSnakeY);

    Snake snake = {malloc(sizeof(int) * 10), malloc(sizeof(int) * 10), 1};
    Apple apple = {appleX, appleY};

    snake.x[0] = firstSnakeX;
    snake.y[0] = firstSnakeY;
    snake.length = 1;

    render(&snake, apple);
    char input;
    while (1) {
        if (_kbhit()) {
            input = (char)_getch();
        }
        if (input == 'w') {
            snake.y[snake.length - 1]--;
        } else if (input == 's') {
            snake.y[snake.length - 1]++;
        } else if (input == 'a') {
            snake.x[snake.length - 1]--;
        } else if (input == 'd') {
            snake.x[snake.length - 1]++;
        }
        
        render(&snake,apple);
        Sleep(1000);

    }

    free(snake.x);
    free(snake.y);
    return 0;
}
