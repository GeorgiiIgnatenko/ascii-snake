#pragma once
#include "Drawable.hpp"

class Board
{
public:
    Board()
    {
        construct(0, 0);
    }

    Board(int heigth, int width)
    {
        construct(heigth, width);
    }

    ~Board(){
        wtimeout(board_win, -1);
        wclear(board_win);
        wrefresh(board_win);
        delwin(board_win);
    }

    void init()
    {
        clear();
        refresh();
        keypad(board_win, true);
    }

    void add(Drawable drawable) {
        addAt(drawable.getY(), drawable.getX(), drawable.getIcon());
    }

    void addAt(int y, int x, chtype ch)
    {
        mvwaddch(board_win, y, x, ch);
    }

    chtype getCharAt(int y, int x){
        return mvwinch(board_win, y, x);
    }

    chtype getInput()
    {
        return wgetch(board_win);
    }

    void addBorder()
    {
        box(board_win, 0, 0);
    }

    void getEmptyCoordinates(int &y, int &x){
        while(mvwinch(board_win, y = rand() % height, x = rand() % width) != ' ');
    }

    void clear()
    {
        wclear(board_win);
        addBorder();
    }

    void refresh()
    {
        wrefresh(board_win);
    }

private:
    WINDOW *board_win;
    int height, width;

    void construct(int height, int width)
    {
        int xMax, yMax;
        getmaxyx(stdscr, yMax, xMax);
        this->height = height;
        this->width = width;

        board_win = newwin(height, width, (yMax / 2) - (height / 2) + 4, (xMax / 2) - (width / 2));
    
        wtimeout(board_win, 500);
    }

    
};