#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// было:
// #include <ncurses/ncurses.h>

// попробуй так:
#include <ncurses.h>
#include <inttypes.h>
#include <string.h>
#include <unistd.h>

#define MIN_Y  2
enum {LEFT=1, UP, RIGHT, DOWN, STOP_GAME=KEY_F(10)};
enum {MAX_TAIL_SIZE=100, START_TAIL_SIZE=3, MAX_FOOD_SIZE=20, FOOD_EXPIRE_SECONDS=10};

struct control_buttons {
    int down;
    int up;
    int left;
    int right;
} control_buttons;

struct control_buttons default_controls = {KEY_DOWN, KEY_UP, KEY_LEFT, KEY_RIGHT};

typedef struct snake_t {
    int x;
    int y;
    int direction;
    size_t tsize;
    struct tail_t *tail;
    struct control_buttons controls;
} snake_t;

typedef struct tail_t {
    int x;
    int y;
} tail_t;

void initTail(struct tail_t t[], size_t size) {
    struct tail_t init_t={0,0};
    for(size_t i=0; i<size; i++) {
        t[i]=init_t;
    }
}

void initHead(struct snake_t *head, int x, int y) {
    head->x = x;
    head->y = y;
    head->direction = RIGHT;
}

void initSnake(snake_t *head, size_t size, int x, int y) {
    tail_t* tail = (tail_t*) malloc(MAX_TAIL_SIZE*sizeof(tail_t));
    initTail(tail, MAX_TAIL_SIZE);
    initHead(head, x, y);
    head->tail = tail;
    head->tsize = size+1;
    head->controls = default_controls;
}

// Движение головы (убран перенос через границу экрана)
void go(struct snake_t *head) {
    char ch = '@';
    mvprintw(head->y, head->x, " "); 
    switch (head->direction) {
        case LEFT:
            mvprintw(head->y, --(head->x), "%c", ch);
            break;
        case RIGHT:
            mvprintw(head->y, ++(head->x), "%c", ch);
            break;
        case UP:
            mvprintw(--(head->y), head->x, "%c", ch);
            break;
        case DOWN:
            mvprintw(++(head->y), head->x, "%c", ch);
            break;
        default:
            break;
    }
    refresh();
}

void changeDirection(struct snake_t* snake, const int32_t key) {
    if (key == snake->controls.down)
        snake->direction = DOWN;
    else if (key == snake->controls.up)
        snake->direction = UP;
    else if (key == snake->controls.right)
        snake->direction = RIGHT;
    else if (key == snake->controls.left)
        snake->direction = LEFT;
}

// Движение хвоста
void goTail(struct snake_t *head) {
    char ch = '*';
    mvprintw(head->tail[head->tsize-1].y, head->tail[head->tsize-1].x, " ");
    for(size_t i = head->tsize-1; i>0; i--) {
        head->tail[i] = head->tail[i-1];
        if( head->tail[i].y || head->tail[i].x)
            mvprintw(head->tail[i].y, head->tail[i].x, "%c", ch);
    }
    head->tail[0].x = head->x;
    head->tail[0].y = head->y;
}

// Новая функция проверки столкновений
int check_collision(struct snake_t *head, int max_x, int max_y) {
    // 1. Проверка выхода за границы экрана
    if (head->x < 0 || head->x >= max_x || head->y < MIN_Y || head->y >= max_y) {
        return 1; // Врезались в стену
    }
    
    // 2. Проверка укуса самого себя
    // Начинаем с индекса 1, так как tail[0] — это предыдущая позиция головы
    for (size_t i = 1; i < head->tsize; i++) {
        if (head->x == head->tail[i].x && head->y == head->tail[i].y) {
            return 1; // Укусили свой хвост
        }
    }
    
    return 0; // Все чисто
}

int main() {
    snake_t* snake = (snake_t*)malloc(sizeof(snake_t));
    initSnake(snake, START_TAIL_SIZE, 10, 10);
    
    initscr();
    keypad(stdscr, TRUE);
    raw();
    noecho();
    curs_set(FALSE);
    mvprintw(0, 0, "Use arrows for control. Press 'F10' for EXIT");
    
    // Отключаем блокирующий ввод для getch()
    nodelay(stdscr, TRUE); 
    
    int key_pressed = 0;
    int game_over = 0;
    int max_x = 0, max_y = 0;
    getmaxyx(stdscr, max_y, max_x); // Получаем размер экрана

    while (key_pressed != STOP_GAME && !game_over) {
        key_pressed = getch(); // Считываем клавишу (не блокирующе)
        
        if (key_pressed != ERR) {
            changeDirection(snake, key_pressed);
        }
        
        go(snake);
        
        // Если произошло столкновение - выходим из цикла
        if (check_collision(snake, max_x, max_y)) {
            game_over = 1;
            break;
        }
        
        goTail(snake);
        
        // 3. Задержка кадра через clock() (100 миллисекунд)
        clock_t start_time = clock();
        while ((clock() - start_time) * 1000 / CLOCKS_PER_SEC < 100) {
            // Ждем (busy wait)
        }
    }
    
    // Если игра окончена из-за столкновения, а не по кнопке F10
    if (game_over) {
        mvprintw(max_y / 2, max_x / 2 - 5, "GAME OVER");
        refresh();
        timeout(-1); // Возвращаем блокирующий ввод, чтобы окно не закрылось сразу
        getch();
    }
    
    free(snake->tail);
    free(snake);
    endwin();
    return 0;
}
