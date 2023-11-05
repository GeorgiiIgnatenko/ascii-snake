#pragma once

#include "UI/Settings.hpp"
#include "UI/Leaderboard.hpp"
#include "UI/Menu.hpp"

#include "GameController.hpp"

#define height 20
#define width 34

class PageController
{
public:
    PageController()
    {
        getmaxyx(stdscr, yMax, xMax);
        while (isOpen == 1)
        {
            switch (currentPage)
            {
            case 0:
            {
                Menu *menu = new Menu(height, width, yMax, xMax);
                menu->handleInput(&currentPage);
                delete menu;
            }
            break;
            case 1:
            {
                SnakeGame *game = new SnakeGame(height, width);
                game->start();
                delete game;
                refresh();
                currentPage = 0;
            }
            break;
            case 2:
            {
                Leaderboard *leaderboard = new Leaderboard(height, width, yMax, xMax);
                leaderboard->handleInput();
                delete leaderboard;
                refresh();
                currentPage = 0;
            }
            break;
            case 3:
            {
                Settings *settings = new Settings(height, width, yMax, xMax, settingsState);
                settings->handleInput();
                delete settings;
                refresh();
                currentPage = 0;
            }
            break;
            }
        }
    }

private:
    int xMax, yMax;
    int currentPage = 0;
    int isOpen = 1;

    std::array<int, 3> settingsState{1, 0, 0};
};