#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

char** read_file(FILE *f, int cols, int *number_of_lines, int *size){
    fseek(f, 0, SEEK_END);
    *size = ftell(f);
    fseek(f, 0, SEEK_SET);

    int cur_lines_size = 1;
    int cur_line_pos = 0;
    int temp = 1024;
    char *line = calloc(temp, sizeof(char*));
    char **ans = calloc(cur_lines_size, sizeof(char*));
    size_t chars_read;
    while ((chars_read = getline(&line, &temp, f)) != -1) {
        if (cur_line_pos == cur_lines_size) {
            cur_lines_size <<= 1;
            ans = realloc(ans, cur_lines_size * sizeof(char *));
        }
        line[cols] = 13;
        ans[cur_line_pos] = calloc(cols + 1, sizeof(char));
        memcpy(ans[cur_line_pos], line, (cols + 1) * sizeof(char));
        cur_line_pos += 1;
    }
    *number_of_lines = cur_line_pos;
    return ans;
}

void main(int argc, char **argv) {
    initscr();
    noecho();
    cbreak();
    refresh();

    FILE *f = fopen(argv[1], "r");
    int size, lines;
    char **text = read_file(f, COLS, &lines, &size);
    fclose(f);
    printw("File: %s; size: %d", argv[1], size);
    refresh();

    WINDOW *win = newwin(LINES - 1, COLS, 1, 1);
    keypad(win, TRUE);
    int start = 0, ch = 0;
    while(1) {
        if (ch == 27) {
            break;
        }
        if (ch == KEY_UP) {
            start = start - 1 < 0 ? 0 : start - 1;
        }
        if (ch == KEY_DOWN) {
            start = start + 1 > lines - LINES + 2 ? lines - LINES + 2 : start + 1;
        }
        wclear(win);
        wprintw(win, "\n");
        for (int i = start; i < start + LINES - 3; ++i) {
            wprintw(win, " ");
            int j = 0;
            while (text[i][j] != 13) {
                wprintw(win, "%c", text[i][j]);
                ++j;
            }
            wprintw(win, "\n");
        }
        box(win, 0, 0);
        wrefresh(win);
        ch = wgetch(win);
    }
    endwin();
}

