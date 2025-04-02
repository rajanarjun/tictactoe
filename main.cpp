#include <iostream>
#include <ncurses.h>
#include <vector>
#include <string>
#include <array>

using namespace std;

static const string player_1_char = "X";
static const string player_2_char = "O";

array<string, 9> result = {};

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
}

void mark_input(WINDOW *win, int wy, int wx, int boardOriginY, int boardOriginX, int cell_height, int cell_width, vector<vector<int>> &intersections, const string &ch) {

    int put_y = (cell_height + boardOriginY) / 2;
    int put_x = (cell_width + boardOriginX) / 2;
    // cell 1
    if (wy > boardOriginY && wy < boardOriginY + cell_height && wx > boardOriginX && wx < boardOriginX + cell_width) {
        if (result[0].empty()) {
            mvwprintw(win, put_y, put_x, "%s", ch.c_str());
            result[0] = ch;
        }
    }

    // cell 2
    if (wy > boardOriginY && wy < boardOriginY + cell_height && wx > boardOriginX + cell_width && wx < boardOriginX + (cell_width*2)) {
        if (result[1].empty()) {
            mvwprintw(win, put_y, put_x + cell_width, "%s", ch.c_str());
            result[1] = ch;
        }
    }

    // cell 3
    if (wy > boardOriginY && wy < boardOriginY + cell_height && wx > boardOriginX + (cell_width*2) && wx < boardOriginX + (cell_width*3)) {
        if (result[2].empty()) {
            mvwprintw(win, put_y, put_x + (cell_width*2), "%s", ch.c_str());
            result[2] = ch;
        }
    }

    // cell 4
    if (wy > boardOriginY + cell_height && wy < boardOriginY + (cell_height*2) && wx > boardOriginX && wx < boardOriginX + cell_width) {
        if (result[3].empty()) {
            mvwprintw(win, put_y + cell_height, put_x, "%s", ch.c_str());
            result[3] = ch;
        }
    }

    // cell 5
    if (wy > boardOriginY + cell_height && wy < boardOriginY + (cell_height*2) && wx > boardOriginX + cell_width && wx < boardOriginX + (cell_width*2)) {
        if (result[4].empty()) {
            mvwprintw(win, put_y + cell_height, put_x + cell_width, "%s", ch.c_str());
            result[4] = ch;
        }
    }

    // cell 6
    if (wy > boardOriginY + cell_height && wy < boardOriginY + (cell_height*2) && wx > boardOriginX + (cell_width*2) && wx < boardOriginX + (cell_width*3)) {
        if (result[5].empty()) {
            mvwprintw(win, put_y + cell_height, put_x + (cell_width*2), "%s", ch.c_str());
            result[5] = ch;
        }
    }

    // cell 7
    if (wy > boardOriginY + (cell_height*2) && wy < boardOriginY + (cell_height*3) && wx > boardOriginX && wx < boardOriginX + cell_width) {
        if (result[6].empty()) {
            mvwprintw(win, put_y + (cell_height*2) + 1, put_x, "%s", ch.c_str());
            result[6] = ch;
        }
    }

    // cell 8
    if (wy > boardOriginY + (cell_height*2) && wy < boardOriginY + (cell_height*3) && wx > boardOriginX + cell_width && wx < boardOriginX + (cell_width*2)) {
        if (result[7].empty()) {
            mvwprintw(win, put_y + (cell_height*2) + 1, put_x + cell_width, "%s", ch.c_str());
            result[7] = ch;
        }
    }

    // cell 9
    if (wy > boardOriginY + (cell_height*2) && wy < boardOriginY + (cell_height*3) && wx > boardOriginX + (cell_width*2) && wx < boardOriginX + (cell_width*3)) {
        if (result[8].empty()) {
            mvwprintw(win, put_y + (cell_height*2) + 1, put_x + (cell_width*2), "%s", ch.c_str());
            result[8] = ch;
        }
    }

    wrefresh(win);
}

int input_filled() {
    for (int i = 0; i < result.size(); i++) {
        if (result[i].empty()) {
            return 0;
        }
    }
    return 1;
}

int check_result() {
    // X wins return 1
    // 0 wins return 2
    // draw return 3

    // horizontal checks
    if (!result[0].empty() && !result[1].empty() && !result[2].empty()) {
        if (result[0] == result[1] && result[1] == result[2]) {
            return (result[0] == player_1_char) ? 1 : 2;
        }   
    }
    if (!result[3].empty() && !result[4].empty() && !result[5].empty()) {
        if (result[3] == result[4] && result[4] == result[5]) {
            return (result[3] == player_1_char) ? 1 : 2;
        }
    }
    if (!result[6].empty() && !result[7].empty() && !result[8].empty()) {
        if (result[6] == result[7] && result[7] == result[8]) {
            return (result[6] == player_1_char) ? 1 : 2;
        }
    }

    // vertical checks
    if (!result[0].empty() && !result[3].empty() && !result[6].empty()) {
        if (result[0] == result[3] && result[3] == result[6]) {
            return (result[0] == player_1_char) ? 1 : 2;
        }
    }
    if (!result[1].empty() && !result[4].empty() && !result[7].empty()) {
        if (result[1] == result[4] && result[4] == result[7]) {
            return (result[1] == player_1_char) ? 1 : 2;
        }
    }
    if (!result[2].empty() && !result[5].empty() && !result[8].empty()) {
        if (result[2] == result[5] && result[5] == result[8]) {
            return (result[2] == player_1_char) ? 1 : 2;
        }
    }

    // diagonal checks
    if (!result[0].empty() && !result[4].empty() && !result[8].empty()) {
        if (result[0] == result[4] && result[4] == result[8]) {
            return (result[0] == player_1_char) ? 1 : 2;
        }
    }
    if (!result[2].empty() && !result[4].empty() && !result[6].empty()) {
        if (result[2] == result[4] && result[4] == result[6]) {
            return (result[2] == player_1_char) ? 1 : 2;
        }
    }

    // everything is filled and no win condition met: draw
    if (input_filled() == 1) {
        return 3;
    }

    return 0;
}

void draw_ascii_art() {
    mvprintw(0, 0, "%s", R"(
    ###################################################
    ##   __  _         __               __           ##
    ##  / /_(_)_______/ /____ _________/ /____  ___  ##
    ## / __/ / __/___/ __/ _ `/ __/___/ __/ _ \/ -_) ##
    ## \__/_/\__/    \__/\_,_/\__/    \__/\___/\__/  ##
    ###################################################
    )");
}

void play_game() {
    int win_height = 12;
    int win_width = 30;
    int win_originY = 10;
    int win_originX = 10;

    int board_originY = 1;
    int board_originX = 1;
    int cell_height = 3;
    int cell_width = cell_height * 3;
    vector<vector<int>> intersections;

    int click_x, click_y, ch, winner;
    int player_1_turn = 1;
    int player_2_turn = 0;

    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    mousemask(BUTTON1_CLICKED, NULL);
    nodelay(stdscr, TRUE);

    draw_ascii_art();
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
                if (player_1_turn == 1) {
                    mark_input(main_win, click_y, click_x, board_originY, board_originX, cell_height, cell_width, intersections, player_1_char);
                    player_1_turn = 0;
                    player_2_turn = 1;
                }
                else if (player_2_turn == 1) {
                    mark_input(main_win, click_y, click_x, board_originY, board_originX, cell_height, cell_width, intersections, player_2_char);
                    player_1_turn = 1;
                    player_2_turn = 0;
                }
                winner = check_result();
                if (winner != 0) {
                    if (winner == 1) {
                        mvprintw(25, 5, "%s", "Player 1 Wins!");
                    } else if (winner == 2) { 
                        mvprintw(25, 5, "%s", "Player 2 Wins!");
                    } else if (winner == 3) {
                        mvprintw(25, 5, "%s", "Its a Draw!");
                    }
                    refresh();
                    break;
                }
            }
        }
    }
    int nch;
    mvprintw(27, 5, "%s", "Press q to exit");
    mvprintw(28, 5, "%s", "Press r to play again");
    while (1) {
        nch = getch();
        if (nch == 'q') {
            napms(10);
            endwin();
            break;
        } else if (nch == 'r') {
            result.fill("");
            clear();
            wclear(main_win);
            box(main_win, '|', '-');
            draw_board(main_win, board_originY, board_originX, cell_height, cell_width, intersections);
            wrefresh(main_win);
            refresh();
            play_game();
            break;
        }
    }
}

int main() {

    play_game();
    return 0;

}
