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

void draw_board(WINDOW *win, int boardOriginY, int boardOriginX, int cell_height, int cell_width, vector<vector<int>> &intersections) {

    for (int i = 1; i < 3; i++) {
        mvwvline(win, boardOriginY, boardOriginX + (i * cell_width), ACS_VLINE, (3 * cell_height) + 1);
    }
    for (int j = 1; j < 3; j++) {
        mvwhline(win, boardOriginY + (j * cell_height), boardOriginX, ACS_HLINE, (3 * cell_width) + 1);
    }

    for (int i = 1; i < 3; i++) {
        for (int j = 1; j < 3; j++) {
            int y_loc = boardOriginY + (i * cell_height);
            int x_loc = boardOriginX + (j * cell_width);
            intersections.push_back({y_loc, x_loc});
            mvwaddch(win, y_loc, x_loc, ACS_PLUS);
        }
    }
    
    //int text_height = 20;
    //for (int i = 0; i < intersections.size(); i++) {
    //    for (int j = 0; j < intersections[i].size(); j++) {
    //        mvprintw(text_height, 10, "%d", intersections[i][j]);
    //        text_height++;
    //        refresh();
    //    }
    //}
}

void mark_input(WINDOW *win, int wy, int wx, int boardOriginY, int boardOriginX, int cell_height, int cell_width, vector<vector<int>> &intersections, char *ch) {
    
    int put_y = (cell_height + boardOriginY) / 2;
    int put_x = (cell_width + boardOriginX) / 2;
    // cell 1
    if (wy > boardOriginY && wy < boardOriginY + cell_height && wx > boardOriginX && wx < boardOriginX + cell_width) {
        if (cell_1_marked == 0) {
            mvwprintw(win, put_y, put_x, "%s", ch);
            cell_1_marked = 1;
        }
    }

    // cell 2
    if (wy > boardOriginY && wy < boardOriginY + cell_height && wx > boardOriginX + cell_width && wx < boardOriginX + (cell_width*2)) {
        if (cell_2_marked == 0) {
            mvwprintw(win, put_y, put_x + cell_width, "%s", ch);
            cell_2_marked = 1;
        }
    }

    // cell 3
    if (wy > boardOriginY && wy < boardOriginY + cell_height && wx > boardOriginX + (cell_width*2) && wx < boardOriginX + (cell_width*3)) {
        if (cell_3_marked == 0) {
            mvwprintw(win, put_y, put_x + (cell_width*2), "%s", ch);
            cell_3_marked = 1;
        }
    }

    // cell 4
    if (wy > boardOriginY + cell_height && wy < boardOriginY + (cell_height*2) && wx > boardOriginX && wx < boardOriginX + cell_width) {
        if (cell_4_marked == 0) {
            mvwprintw(win, put_y + cell_height, put_x, "%s", ch);
            cell_4_marked = 1;
        }
    }

    // cell 5
    if (wy > boardOriginY + cell_height && wy < boardOriginY + (cell_height*2) && wx > boardOriginX + cell_width && wx < boardOriginX + (cell_width*2)) {
        if (cell_5_marked == 0) {
            mvwprintw(win, put_y + cell_height, put_x + cell_width, "%s", ch);
            cell_5_marked = 1;
        }
    }

    // cell 6
    if (wy > boardOriginY + cell_height && wy < boardOriginY + (cell_height*2) && wx > boardOriginX + (cell_width*2) && wx < boardOriginX + (cell_width*3)) {
        if (cell_6_marked == 0) {
            mvwprintw(win, put_y + cell_height, put_x + (cell_width*2), "%s", ch);
            cell_6_marked = 1;
        }
    }

    // cell 7
    if (wy > boardOriginY + (cell_height*2) && wy < boardOriginY + (cell_height*3) && wx > boardOriginX && wx < boardOriginX + cell_width) {
        if (cell_7_marked == 0) {
            mvwprintw(win, put_y + (cell_height*2) + 1, put_x, "%s", ch);
            cell_7_marked = 1;
        }
    }

    // cell 8
    if (wy > boardOriginY + (cell_height*2) && wy < boardOriginY + (cell_height*3) && wx > boardOriginX + cell_width && wx < boardOriginX + (cell_width*2)) {
        if (cell_8_marked == 0) {
            mvwprintw(win, put_y + (cell_height*2) + 1, put_x + cell_width, "%s", ch);
            cell_8_marked = 1;
        }
    }

    // cell 9
    if (wy > boardOriginY + (cell_height*2) && wy < boardOriginY + (cell_height*3) && wx > boardOriginX + (cell_width*2) && wx < boardOriginX + (cell_width*3)) {
        if (cell_9_marked == 0) {
            mvwprintw(win, put_y + (cell_height*2) + 1, put_x + (cell_width*2), "%s", ch);
            cell_9_marked = 1;
        }
    }

    wrefresh(win);
}

int main() {
    int win_height = 12;
    int win_width = 30;
    int win_originY = 10;
    int win_originX = 10;

    int board_originY = 1;
    int board_originX = 1;
    int cell_height = 3;
    int cell_width = cell_height * 3;
    vector<vector<int>> intersections;

    int click_x, click_y, ch;
    char player_char[] = "O";

    initscr();
    noecho();
    cbreak();
    
    keypad(stdscr, TRUE);
    mousemask(BUTTON1_CLICKED, NULL);
    nodelay(stdscr, TRUE);

    mvprintw(0, 0, "%s", R"(
    ###################################################
    ##   __  _         __               __           ##
    ##  / /_(_)_______/ /____ _________/ /____  ___  ##
    ## / __/ / __/___/ __/ _ `/ __/___/ __/ _ \/ -_) ##
    ## \__/_/\__/    \__/\_,_/\__/    \__/\___/\__/  ##
    ###################################################
    )");

    refresh();
                                                  
    WINDOW* main_win = newwin(win_height, win_width, win_originY, win_originX);
    box(main_win, '|', '-');
    draw_board(main_win, board_originY, board_originX, cell_height, cell_width, intersections);
    wrefresh(main_win);

    keypad(main_win, TRUE);
    nodelay(main_win, TRUE);

    MEVENT event;
    while (1) {
        ch = wgetch(main_win);
        if (ch == 'q') break;
        if (ch == KEY_MOUSE && getmouse(&event) == OK) {
              if (event.bstate & BUTTON1_CLICKED) {
                  click_y = event.y - win_originY;
                  click_x = event.x - win_originX;
                  mark_input(main_win, click_y, click_x, board_originY, board_originX, cell_height, cell_width, intersections, player_char);
              }
        }
        napms(10);
    }
    endwin();
    return 0;
}
