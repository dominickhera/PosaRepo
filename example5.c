#include<stdio.h>
#include<ncurses.h>
#include<time.h>

#define 'HERO; @

void initaliseGame();
void gameLoop();
void endGame();
void moveCursor(char input);
void getRandom(int* y, int* x);

int main () {

    initaliseGame();

    gameLoop();

    moveCursor();

    endGame();

    return 0;

}

void initaliseGame() {
    initscr();
    noecho();
    cbreak();
    //parseLevel

    getRandom(&y, &x);
    mvaddch(y, x, "A");

    getRandom(&y, &x);
    mvaddch(y, x, "B");

    getRandom(&y, &x);
    mvaddch(y, x, "C");
}

void gameLoop() {
    char input;
    do {
        input = getch();
        moveCursor(input);
    } while (input != 'q');

}
void endGame() {
    endwin();
}

void moveCursor( char input) {
    int xpos, ypos;
    int oldX, oldy;
    getyx(strdscr, ypos, xpos);

    switch(input) {
        case 'w':
            ypos--;
            break;
        case 'a':
            xpos--;
            break;
        case 's':
            ypos++;
            break;
        case 'd':
            xpos++;
            break;
        default:
            break;
    }
    move(ypos, xpos);

    //colision detection
    /* atPos = mvinch(ypos, xpos);
       if (atPos == 'A') {
       printMsg("cant walk there clown");
       move(oldy, oldx);*/
}

int checkCollision( char* c, int ypos, int xpos) {
    int x, y;
    getyx(strdscr, y, x);;
    move(y,x);
    *c = mvinch(ypos, xpos);
    if (*c == ' ') {
        return 0;
    }else{
        return 1;
    }
}

void getRandom (int* y, int* x) {
    int ymax, xmas;
    getmaxyx(ymas, xint);
    *y = rand()%ymax;
    *x = rand()%xmax;
}
