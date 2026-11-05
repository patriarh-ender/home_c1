#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses/ncurses.h>
#include <inttypes.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h> // Для функции tolower() (приведение к нижнему регистру)

#define MIN_Y  2
enum {LEFT=1, UP, RIGHT, DOWN, STOP_GAME=KEY_F(10)};
enum {MAX_TAIL_SIZE=100, START_TAIL_SIZE=3};

// Определяем количество наборов управления (Стрелки, WASD нижний, WASD верхний)
#define CONTROLS 3 

struct control_buttons {
    int down;
    int up;
    int left;
    int right;
};

// Массив кодов управления согласно заданию
struct control_buttons default_controls[CONTROLS] = {
    {KEY_DOWN, KEY_UP, KEY_LEFT, KEY_RIGHT}, // Стрелки
    {'s', 'w', 'a', 'd'},                    // WASD нижний регистр
    {'S', 'W', 'A', 'D'}                     // WASD верхний регистр
};

typedef struct snake_t {
    int x;
    int y;
    int direction;
    size_t tsize;
    struct tail_t *tail;
} snake_t;

typedef struct tail_t {
    int x;
    int y;
} tail_t;

void initTail(struct tail_t t[], size_t size) {
    struct tail_t init_t={0,0};
    for(size_t i=0; i<size; i++) t[i]=init_t;
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
}

void go(struct snake_t *head) {
    char ch = '@';
    mvprintw(head->y, head->x, " "); // Очищаем старую позицию
    switch (head->direction) {
        case LEFT:  mvprintw(head->y, --(head->x), "%c", ch); break;
        case RIGHT: mvprintw(head->y, ++(head->x), "%c", ch); break;
        case UP:    mvprintw(--(head->y), head->x, "%c", ch); break;
        case DOWN:  mvprintw(++(head->y), head->x, "%c", ch); break;
        default: break;
    }
    refresh();
}

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

// НОВАЯ ФУНКЦИЯ 1: Проверка корректности выбранного направления
// Возвращает 1, если направление допустимо, и 0, если это разворот на 180 градусов
int checkDirection(snake_t* snake, int32_t key) {
    int new_dir = 0;
    
    // Ищем, какому направлению соответствует нажатая клавиша
    for (int i = 0; i < CONTROLS; i++) {
        if (key == default_controls[i].down) new_dir = DOWN;
        else if (key == default_controls[i].up) new_dir = UP;
        else if (key == default_controls[i].right) new_dir = RIGHT;
        else if (key == default_controls[i].left) new_dir = LEFT;
    }
    
    if (new_dir == 0) return 0; // Клавиша не относится к управлению

    // Запрет разворота на 180 градусов
    if (snake->direction == RIGHT && new_dir == LEFT) return 0;
    if (snake->direction == LEFT && new_dir == RIGHT) return 0;
    if (snake->direction == UP && new_dir == DOWN) return 0;
    if (snake->direction == DOWN && new_dir == UP) return 0;

    return 1; // Направление корректно
}

// Функция смены направления (теперь использует массив)
void changeDirection(struct snake_t* snake, const int32_t key) {
    for (int i = 0; i < CONTROLS; i++) {
        if (key == default_controls[i].down) snake->direction = DOWN;
        else if (key == default_controls[i].up) snake->direction = UP;
        else if (key == default_controls[i].right) snake->direction = RIGHT;
        else if (key == default_controls[i].left) snake->direction = LEFT;
    }
}

// Проверка столкновений (стены и хвост)
int check_collision(struct snake_t *head, int max_x, int max_y) {
    if (head->x <= 0 || head->x >= max_x || head->y <= MIN_Y || head->y >= max_y) return 1;
    for (size_t i = 1; i < head->tsize; i++) {
        if (head->x == head->tail[i].x && head->y == head->tail[i].y) return 1;
    }
    return 0;
}

int main() {
    snake_t* snake = (snake_t*)malloc(sizeof(snake_t));
    initSnake(snake, START_TAIL_SIZE, 10, 10);
    
    initscr();
    keypad(stdscr, TRUE);
    raw();
    noecho();
    curs_set(FALSE);
    mvprintw(0, 0, "Use arrows or WSAD to control. Press 'F10' for EXIT");
    
    nodelay(stdscr, TRUE); 
    
    int key_pressed = 0;
    int game_over = 0;
    int max_x = 0, max_y = 0;
    getmaxyx(stdscr, max_y, max_x);

    while (key_pressed != STOP_GAME && !game_over) {
        key_pressed = getch();
        
        if (key_pressed != ERR) {
            // Сначала проверяем, можно ли поворачивать в эту сторону
            if (checkDirection(snake, key_pressed)) {
                changeDirection(snake, key_pressed);
            }
        }
        
        go(snake);
        
        if (check_collision(snake, max_x, max_y)) {
            game_over = 1;
            break;
        }
        
        goTail(snake);
        
        // Задержка через clock()
        clock_t start_time = clock();
        while ((clock() - start_time) * 1000 / CLOCKS_PER_SEC < 100) {
            // Ждем
        }
    }
    
    if (game_over) {
        mvprintw(max_y / 2, max_x / 2 - 5, "GAME OVER");
        refresh();
        timeout(-1);
        getch();
    }
    
    free(snake->tail);
    free(snake);
    endwin();
    return 0;
}
