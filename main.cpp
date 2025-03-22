#include <iostream>
#include <ncurses.h>
#include <vector>

using namespace std;

static int cell_1_marked = 0;
static int cell_2_marked = 0;
static int cell_3_marked = 0;
static int cell_4_marked = 0;
static int cell_5_marked = 0;
static int cell_6_marked = 0;
static int cell_7_marked = 0;
static int cell_8_marked = 0;
static int cell_9_marked = 0;

void draw_board(WINDOW *win, vector<int> &boardOrigin, int cell_height, int cell_width, vector<vector<int>> &intersections) {

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
            refresh();
        }
    }
}

void mark_input(WINDOW *win, int wy, int wx, vector<int> &boardOrigin, int cell_height, int cell_width, vector<vector<int>> &intersections) {
    
    // cell 1
    if (wy > boardOrigin[0] && wy < boardOrigin[0] + cell_height && wx > boardOrigin[1] && wx < boardOrigin[1] + cell_width) {
        if (cell_1_marked == 0) {
            mvwprintw(win, wy, wx, "X");
            cell_1_marked = 1;
        }
    }

    // cell 2
    // cell 3
    // cell 4
    // cell 5
    // cell 6
    // cell 7
    // cell 8
    // cell 9

    wrefresh(win);
}

int main() {
    int win_height = 12;
    int win_width = 30;
    vector<int> scr_win_left_upper_corner = {5, 10};
    vector<int> scr_win_right_lower_corner = {scr_win_left_upper_corner[0] + win_height - 1, scr_win_left_upper_corner[1] + win_width - 1};

    vector<int> board_origin = {1, 1};
    int cell_height = 3;
    int cell_width = cell_height * 3;
    vector<vector<int>> intersections;

    int click_x, click_y, ch;

    initscr();
    noecho();
    cbreak();
    
    keypad(stdscr, TRUE);
    mousemask(BUTTON1_CLICKED, NULL);
    nodelay(stdscr, TRUE);

    WINDOW* main_win = newwin(win_height, win_width, 5, 10);
    box(main_win, '|', '-');
    draw_board(main_win, board_origin, cell_height, cell_width, intersections);
    wrefresh(main_win);

    keypad(main_win, TRUE);
    nodelay(main_win, TRUE);

    MEVENT event;
    while (1) {
        ch = wgetch(main_win);
        if (ch == 'q') break;
        if (ch == KEY_MOUSE && getmouse(&event) == OK) {
              if (event.bstate & BUTTON1_CLICKED) {
                  click_x = event.x - 10;
                  click_y = event.y - 5;
                  mark_input(main_win, click_y, click_x, board_origin, cell_height, cell_width, intersections);
              }
        }
        napms(10);
    }
    endwin();
    return 0;
}
