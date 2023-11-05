#pragma once

class Menu
{
public:
    Menu(int height, int width, int yMax, int xMax)
    {                                                                                      
        menu = newwin(height, width, (yMax / 2) - (height / 2) + 4, (xMax / 2) - (width / 2));
        keypad(menu, true);

        std::vector<std::string> logo {
" _____             _                                      ",
"/  ___|           | |                                     ",
"\\ `--. _ __   __ _| | _____    __ _  __ _ _ __ ___   ___  ",
" `--. \\ '_ \\ / _` | |/ / _ \\  / _` |/ _` | '_ ` _ \\ / _ \\",
"/\\__/ / | | | (_| |   <  __/ | (_| | (_| | | | | | |  __/ ",
"\\____/|_| |_|\\__,_|_|\\_\\___|  \\__, |\\__,_|_| |_| |_|\\___|",
"                               __/ |                      ",
"                              |___/                       ",
};

        int y = 0;
        for(std::string line : logo){
            mvprintw(y, (xMax / 2) - (logo[0].size()/2) + 2, line.c_str());
            y++;
        }


        box(menu, 0, 0);
        mvwprintw(menu, 3, 16, "Menu");
        render();
        wrefresh(menu);
        refresh();
    }

    ~Menu() {
        wclear(menu);
        wrefresh(menu);
        delwin(menu);
        clear();
    }

    void render()
    {
        for (int i = 0; i < 4; i++)
        {
            if (selected == i)
            {
                wattron(menu, A_REVERSE);
                mvwprintw(menu, 7 + i * 2, 16, options[i]);
                wattroff(menu, A_REVERSE);
            }
            else
            {
                mvwprintw(menu, 7 + i * 2, 16, options[i]);
            }
        }
    }

    void handleInput(int *page)
    {
        while (active == 1)
        {
            int ch = wgetch(menu);
            if (ch == KEY_UP && selected > 0)
            {
                --selected;
            }
            else if (ch == KEY_DOWN && selected < 3)
            {
                ++selected;
            }
            else if (ch == 10)
            {
                mvwprintw(menu, 1, 1, "enter!");
                enterHandler(page);
            }
            if (active == 1){
                render();
            }
        }
    }

    void enterHandler(int *page)
    {
        switch (selected)
        {
        case 0:
            *page = 1;
            active = 0;
            
            break;
        case 1:
            *page = 2;
            active = 0;
            
            break;

        case 2:
            *page = 3;
            active = 0;
            

            break;

        case 3:
            endwin();
            exit(0);
            break;
        }
    }

private:
    int selected{0};
    int active{1};
    WINDOW *menu;
    const char *options[4]{"Play", "Leaderboard", "Settings", "Quit"};

    
};