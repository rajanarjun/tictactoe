#include <iostream>
#include <ncurses.h>
#include <vector>

using namespace std;

void draw_board() {
    // origin: 5,10
    vector<int> origin = {5, 10};

    int height = 3;
    int width = height * 3;

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            mvvline(origin[0] + (j * height), origin[1] + width + (i * width), ACS_VLINE, height);
            mvhline(origin[0] + height + (i * height), origin[1] + (j * width), ACS_HLINE, width);
        }
    }

    //for (int i = 0; i < 2; i++) {
    //}
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
