#include <iostream>
#include <ncurses.h>
#include <vector>

using namespace std;

void draw_board() {
    // origin: y = 5, x = 10
    vector<int> origin = {5, 10};

    int height = 3;
    int width = height * 3;

    for (int i = 1; i < 3; i++) {
        mvvline(origin[0], origin[1] + (i * width), ACS_VLINE, (3 * height) + 1);
    }
    for (int j = 1; j < 3; j++) {
        mvhline(origin[0] + (j * height), origin[1], ACS_HLINE, (3 * width) + 1);
    }

    for (int i = 1; i < 3; i++) {
        for (int j = 1; j < 3; j++) {
            mvaddch(origin[0] + (i * height), origin[1] + (j * width), ACS_PLUS);
        }
    }
}

int main() {
    initscr();
    noecho();
    keypad(stdscr, TRUE);
    mousemask(BUTTON1_CLICKED, NULL);
    nodelay(stdscr, TRUE);

    MEVENT event;
    draw_board();

    while (1) {
        int ch = getch();

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
