#include <iostream>
#include <ncurses.h>

using namespace std;

void draw_board() {

}

int main() {

    initscr();
    noecho();
    keypad(stdscr, TRUE);
    mousemask(BUTTON1_CLICKED, NULL);
    nodelay(stdscr, TRUE);

    int ch;

    MEVENT event;

    while (1) {
        clear();

        ch = getch();

        if (ch == 'q') break;

        if (ch == KEY_MOUSE && getmouse(&event) == OK) {
            if (event.bstate & BUTTON1_CLICKED) {
                mvprintw(event.y, event.x, "X");
                refresh();
            }
        }
        refresh();
        napms(10);
    }

    endwin();
    return 0;

}
