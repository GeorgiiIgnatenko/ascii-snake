#include <array>
#include <string>
#include <vector>
#include <queue>
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>

#include "src/PageController.hpp"


int main()
{
    initscr();
    refresh();
    curs_set(0);
    keypad(stdscr, true);

    PageController controller;

    endwin();

    return 0;
}