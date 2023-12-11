#pragma once

class Leaderboard{
public:
    Leaderboard(int heigth, int width, int yMax, int xMax) {
        render();
        refresh();
    }

    ~Leaderboard() {
        clear();
    }

    void render() {
        for (int i = 0; i < 3; i++)
        {
            mvprintw(5 + i * 2, 16, leaders[i]);
        }
    }

    void handleInput() {
        while(int ch = getch() != KEY_BACKSPACE){

        }
    }
private:
    const char *leaders[3] = {
        "test",
        "test2",
        "test3"
    };
};
