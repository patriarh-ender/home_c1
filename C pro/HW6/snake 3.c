#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <inttypes.h>
#include <string.h>

#define MIN_Y 2
enum {LEFT=1, UP, RIGHT, DOWN, STOP_GAME=27}; // 27 - это ESC
enum {MAX_TAIL_SIZE=100, START_TAIL_SIZE=3, FOOD_COUNT=1};
#define CONTROLS 3

// Структура для кнопок управления
struct control_buttons {
    int down;
    int up;
    int left;
    int right;
};

struct control_buttons default_controls[CONTROLS] = {
    {KEY_DOWN, KEY_UP, KEY_LEFT, KEY_RIGHT},
    {'s', 'w', 'a', 'd'},
    {'S', 'W', 'A', 'D'}
};

typedef struct tail_t {
    int x;
    int y;
} tail_t;

typedef struct snake_t {
    int x;
    int y;
    int direction;
    size_t tsize;
    struct tail_t *tail;
} snake_t;

typedef struct food_t {
    int x;
    int y;
} food_t;

// ==========================================
// ПУНКТ 3: Настройка цветов
// ==========================================
void setColor(int objectType) {
    attroff(COLOR_PAIR(1));
    attroff(COLOR_PAIR(2));
    attroff(COLOR_PAIR(3));
    switch (objectType) {
        case 1: attron(COLOR_PAIR(1)); break; // Змейка (Красная)
        case 2: attron(COLOR_PAIR(2)); break; // Резерв (Синяя)
        case 3: attron(COLOR_PAIR(3)); break; // Еда (Зеленая)
    }
}

// ==========================================
// ПУНКТ 4: Стартовое меню
// ==========================================
int startMenu() {
    clear();
    mvprintw(3, 10, "=== SNAKE GAME ===");
    mvprintw(5, 10, "1. Standard Mode (die on self-bite)");
    mvprintw(6, 10, "2. Ghost Mode (no self-bite)");
    mvprintw(8, 10, "Press 1 or 2 to select...");
    refresh();
    
    int mode = 0;
    while (mode != '1' && mode != '2') {
        int ch = getch();
        if (ch == '1') mode = 1;
        if (ch == '2') mode = 2;
    }
    clear();
    return mode; // Возвращаем выбранный режим
}

// Инициализация
void initTail(struct tail_t t[], size_t size) {
    struct tail_t init_t={0,0};
    for(size_t i=0; i<size; i++) t[i]=init_t;
}

void initSnake(snake_t *head, size_t size, int x, int y) {
    tail_t* tail = (tail_t*) malloc(MAX_TAIL_SIZE*sizeof(tail_t));
    initTail(tail, MAX_TAIL_SIZE);
    head->x = x;
    head->y = y;
    head->direction = RIGHT;
    head->tail = tail;
    head->tsize = size+1;
}

// Движение головы
void go(struct snake_t *head) {
    char ch = '@';
    setColor(1); // Красим змейку
    mvprintw(head->y, head->x, " "); 
    switch (head->direction) {
        case LEFT:  mvprintw(head->y, --(head->x), "%c", ch); break;
        case RIGHT: mvprintw(head->y, ++(head->x), "%c", ch); break;
        case UP:    mvprintw(--(head->y), head->x, "%c", ch); break;
        case DOWN:  mvprintw(++(head->y), head->x, "%c", ch); break;
    }
    refresh();
}

// Движение хвоста
void goTail(struct snake_t *head) {
    char ch = '*';
    setColor(1); // Красим хвост в тот же цвет
    mvprintw(head->tail[head->tsize-1].y, head->tail[head->tsize-1].x, " ");
    for(size_t i = head->tsize-1; i>0; i--) {
        head->tail[i] = head->tail[i-1];
        if( head->tail[i].y || head->tail[i].x)
            mvprintw(head->tail[i].y, head->tail[i].x, "%c", ch);
    }
    head->tail[0].x = head->x;
    head->tail[0].y = head->y;
}

void changeDirection(struct snake_t* snake, const int32_t key) {
    for (int i = 0; i < CONTROLS; i++) {
        if (key == default_controls[i].down) snake->direction = DOWN;
        else if (key == default_controls[i].up) snake->direction = UP;
        else if (key == default_controls[i].right) snake->direction = RIGHT;
        else if (key == default_controls[i].left) snake->direction = LEFT;
    }
}

int checkDirection(snake_t* snake, int32_t key) {
    int new_dir = 0;
    for (int i = 0; i < CONTROLS; i++) {
        if (key == default_controls[i].down) new_dir = DOWN;
        else if (key == default_controls[i].up) new_dir = UP;
        else if (key == default_controls[i].right) new_dir = RIGHT;
        else if (key == default_controls[i].left) new_dir = LEFT;
    }
    if (new_dir == 0) return 0;
    if (snake->direction == RIGHT && new_dir == LEFT) return 0;
    if (snake->direction == LEFT && new_dir == RIGHT) return 0;
    if (snake->direction == UP && new_dir == DOWN) return 0;
    if (snake->direction == DOWN && new_dir == UP) return 0;
    return 1; 
}

// ==========================================
// ПУНКТ 2: Проверка столкновений (isCrush)
// ==========================================
int isCrush(snake_t* snake, int max_x, int max_y, int ignore_self) {
    // Выход за границы (стены) - всегда смерть
    if (snake->x <= 0 || snake->x >= max_x || snake->y <= MIN_Y || snake->y >= max_y) {
        return 1;
    }
    
    // Укус себя - только если НЕ включен "режим призрака"
    if (!ignore_self) {
        for (size_t i = 1; i < snake->tsize; i++) {
            if (snake->x == snake->tail[i].x && snake->y == snake->tail[i].y) {
                return 1;
            }
        }
    }
    return 0;
}

// Генерация еды (Пункт 5 - своя механика)
void spawnFood(food_t *food, int max_x, int max_y) {
    food->x = rand() % (max_x - 2) + 1;
    food->y = rand() % (max_y - MIN_Y - 2) + MIN_Y + 1;
}

int main() {
    srand(time(NULL));
    
    initscr();
    keypad(stdscr, TRUE);
    raw();
    noecho();
    curs_set(FALSE);
    nodelay(stdscr, TRUE); // Неблокирующий ввод

    // ПУНКТ 3: Инициализация цветов
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_BLUE, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);

    // ПУНКТ 4: Запуск меню и выбор режима
    int mode = startMenu();
    int ignore_self = (mode == 2) ? 1 : 0; // Если выбран режим 2, разрешаем укусы

    snake_t* snake = (snake_t*)malloc(sizeof(snake_t));
    initSnake(snake, START_TAIL_SIZE, 10, 10);
    
    int max_x = 0, max_y = 0;
    getmaxyx(stdscr, max_y, max_x);

    food_t food;
    spawnFood(&food, max_x, max_y);

    mvprintw(0, 0, "Use arrows or WSAD. Press 'ESC' for EXIT");
    int key_pressed = 0;
    int game_over = 0;

    while (key_pressed != STOP_GAME && !game_over) {
        key_pressed = getch();
        
        if (key_pressed != ERR) {
            if (checkDirection(snake, key_pressed)) {
                changeDirection(snake, key_pressed);
            }
        }
        
        go(snake);
        
        // ПУНКТ 2: Передаем флаг ignore_self в функцию проверки
        if (isCrush(snake, max_x, max_y, ignore_self)) {
            game_over = 1;
            break;
        }
        
        goTail(snake);

        // Отрисовка еды
        setColor(3);
        mvprintw(food.y, food.x, "$");

        // Логика поедания еды и роста змейки
        if (snake->x == food.x && snake->y == food.y) {
            if (snake->tsize < MAX_TAIL_SIZE) {
                snake->tsize++; // Змейка растет
            }
            spawnFood(&food, max_x, max_y);
        }

        refresh();

        // Задержка кадра через clock()
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
