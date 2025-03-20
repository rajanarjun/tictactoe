#include <iostream>
#include <ncurses.h>
#include <vector>

using namespace std;

void draw_board(WINDOW *win) {
    vector<int> boardOrigin = {1, 1};
    vector<vector<int>> intersections;

    int cell_height = 3;
    int cell_width = cell_height * 3;

    for (int i = 1; i < 3; i++) {
        mvwvline(win, boardOrigin[0], boardOrigin[1] + (i * cell_width), ACS_VLINE, (3 * cell_height) + 1);
    }
    for (int j = 1; j < 3; j++) {
        mvwhline(win, boardOrigin[0] + (j * cell_height), boardOrigin[1], ACS_HLINE, (3 * cell_width) + 1);
    }

    for (int i = 1; i < 3; i++) {
        for (int j = 1; j < 3; j++) {
            int y_loc = boardOrigin[0] + (i * cell_height);
            int x_loc = boardOrigin[1] + (j * cell_width);
            intersections.push_back({y_loc, x_loc});
            mvwaddch(win, y_loc, x_loc, ACS_PLUS);
        }
    }
    
    int text_height = 20;
    for (int i = 0; i < intersections.size(); i++) {
        for (int j = 0; j < intersections[i].size(); j++) {
            mvprintw(text_height, 10, "%d", intersections[i][j]);
            text_height++;
        }
    }
}

int main() {
    int win_height = 12;
    int win_width = 30;
    int click_x, click_y;

    initscr();
    noecho();
    
    WINDOW* main_win = newwin(win_height, win_width, 5, 10);
    box(main_win, '|', '-');
    draw_board(main_win);

    keypad(stdscr, TRUE);
    mousemask(BUTTON1_CLICKED, NULL);
    nodelay(stdscr, TRUE);

    MEVENT event;

    while (1) {
        int ch = getch();

        if (ch == 'q') break;
        if (ch == KEY_MOUSE && getmouse(&event) == OK) {
              if (event.bstate & BUTTON1_CLICKED) {
                  click_x = event.x;
                  click_y = event.y;
                  mvprintw(event.y, event.x, "X");
                  refresh();
                }
        }
        wrefresh(main_win);
        refresh();
        napms(10);
    }
    endwin();
    return 0;
}
