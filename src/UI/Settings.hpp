#pragma once

class Settings
{
public:
    Settings(int heigth, int width, int yMax, int xMax, std::array<int, 3> &state) : settingsState(state)
    {
        settings_win = newwin(heigth, width, (yMax / 2) - (heigth / 2) + 4, (xMax / 2) - (width / 2));
        box(settings_win, 0, 0);
        keypad(settings_win, true);
        render();
        wrefresh(settings_win);
    }

    ~Settings()
    {
        wclear(settings_win);
        wrefresh(settings_win);
        delwin(settings_win);
        clear();
    }

    void render()
    {
        wclear(settings_win);
        box(settings_win, 0, 0);
        for (int i = 0; i < 3; i++)
        {
            int selected = settingsState[i];
            if (selectedRow == i)
            {
                wattron(settings_win, A_REVERSE);
                mvwprintw(settings_win, 3 + i * 2, 24, optionValues[i][selected].c_str());
                wattroff(settings_win, A_REVERSE);
            }
            else
            {
                mvwprintw(settings_win, 3 + i * 2, 24, optionValues[i][selected].c_str());
            }

            mvwprintw(settings_win, 3 + i * 2, 4, options[i].c_str());
            mvwprintw(settings_win, 3 + i * 2, 21, "<");
            mvwprintw(settings_win, 3 + i * 2, 31, ">");
        }

        if (selectedRow == 3)
        {
            wattron(settings_win, A_REVERSE);
            mvwprintw(settings_win, 17, 4, "Save");
            wattroff(settings_win, A_REVERSE);
        }
        else
        {
            mvwprintw(settings_win, 17, 4, "Save");
        }
    }

    void handleInput()
    {
        while (active == 1)
        {
            int ch = wgetch(settings_win);
            if (ch == KEY_DOWN && selectedRow < 3)
            {
                selectedRow++;
            }
            else if (ch == KEY_UP && selectedRow > 0)
            {
                selectedRow--;
            }
            else if (ch == KEY_RIGHT && optionValues[selectedRow].size() > settingsState[selectedRow] + 1 && selectedRow < 3)
            {
                settingsState[selectedRow]++;
            }
            else if (ch == KEY_LEFT && settingsState[selectedRow] > 0 && selectedRow < 3)
            {
                settingsState[selectedRow]--;
            }
            else if (ch == 10 && selectedRow == 3)
            {
                break;
            }
            if (active)
            {
                render();
            }
        }
    }

private:
    std::vector<std::string> options{
        "Board_size",
        "Speed",
        "Random_events"};

    std::vector<std::vector<std::string>> optionValues{
        {"Small", "Medium", "Big"},
        {"Normal", "Fast"},
        {"True", "False"}};

    std::array<int, 3> &settingsState;

    int selectedRow = 0;
    int active = 1;
    WINDOW *settings_win;
};
