#pragma once

#include "Drawable.hpp"

#include "../Time.hpp"

class Board
{
public:
    Board()
    {
        construct(0, 0, 300);
    }

    Board(int heigth, int width, int speed)
    {
        construct(heigth, width, speed);
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
        time_t time_last_input = getMils();
        int timeout = this->timeout;

        chtype input = wgetch(board_win);

        chtype new_input = ERR;

        setTimeout(0);
        while(time_last_input + timeout >= getMils()){
            new_input = wgetch(board_win);
        }

        setTimeout(timeout);

        if (new_input != ERR)
            input = new_input;

        return input;
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

    void setTimeout(int timeout) {
        wtimeout(board_win, timeout);
        this->timeout = timeout;
    }

private:
    WINDOW *board_win;
    int height, width, timeout;

    void construct(int height, int width, int speed)
    {
        int xMax, yMax;
        getmaxyx(stdscr, yMax, xMax);
        this->height = height;
        this->width = width;
        

        board_win = newwin(height, width, (yMax / 2) - (height / 2) + 4, (xMax / 2) - (width / 2));
    
        setTimeout(speed);
    }

    
};