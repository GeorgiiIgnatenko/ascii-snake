#pragma once

#include "GameEntities/Apple.hpp"
#include "GameEntities/Empty.hpp"
#include "GameEntities/Drawable.hpp"
#include "GameEntities/Board.hpp"
#include "GameEntities/Snake.hpp"

enum Event
{
    standart,
    appleEvent
};

class SnakeGame
{
public:
    SnakeGame(std::array<int, 3> &state) : settingsState(state)
    {
        initValues();

        board = new Board(height, width, speed);
        board->init();
        srand(time(NULL));

        SnakePiece next = SnakePiece(1, 1);
        board->add(next);
        snake.addPiece(next);

        next = snake.nextHead();
        board->add(next);
        snake.addPiece(next);

        next = snake.nextHead();
        board->add(next);
        snake.addPiece(next);

        snake.setDirection(right);
        next = snake.nextHead();
        board->add(next);
        snake.addPiece(next);

        createApple();
    }

    ~SnakeGame()
    {
        delete apple;
        delete board;
    }

    void initValues()
    {
        switch (settingsState[0])
        {
        case 0:
            height = 13;
            width = height * 2.2;
            break;
        case 1:
            height = 17;
            width = height * 2.2;
            break;
        case 2:
            height = 20;
            width = height * 2.2;
            break;
        }
        switch (settingsState[1])
        {
        case 0:
            speed = 300;
            break;
        case 1:
            speed = 200;
            break;
        }
    }

    void start()
    {
        while (!game_over)
        {
            while (!is_paused)
            {
                processInput();

                updateState();

                redraw();
            }

            processInput();
        }
    }

    void processInput()
    {
        chtype input = board->getInput();
        SnakePiece next = snake.nextHead();
        switch (input)
        {
        case KEY_DOWN:
        case 's':
        case 'j':
            if (next.getY() != height - 2 && snake.getDirection() != down && snake.getDirection() != up && !is_paused)
            {
                snake.setDirection(down);
            }
            break;
        case KEY_UP:
        case 'w':
        case 'k':
            if (next.getY() != 1 && snake.getDirection() != up && snake.getDirection() != down && !is_paused)
            {
                snake.setDirection(up);
            }
            break;
        case KEY_LEFT:
        case 'a':
        case 'h':
            if (next.getX() != 1 && snake.getDirection() != left && snake.getDirection() != right && !is_paused)
            {
                snake.setDirection(left);
            }
            break;
        case KEY_RIGHT:
        case 'd':
        case 'l':
            if (next.getX() != width - 2 && snake.getDirection() != right && snake.getDirection() != left && !is_paused)
            {
                snake.setDirection(right);
            }
            break;
        case 'p':
            is_paused == true ? is_paused = false : is_paused = true;
            break;
        }
    }

    void createApple()
    {
        int y, x;
        board->getEmptyCoordinates(y, x);
        apple = new Apple(y, x);
        board->add(*apple);
    }

    void updateState()
    {
        SnakePiece next = snake.nextHead();
        SnakePiece head = snake.head();

        // Collisions with walls
        if (head.getX() == 0 || head.getX() == width - 1 || head.getY() == 0 || head.getY() == height - 1)
        {
            is_paused = 1;
            game_over = 1;
        }

        if (board->getCharAt(next.getY(), next.getX()) == '#')
        {
            is_paused = 1;
            game_over = 1;
        }

        if (next.getX() != apple->getX() || next.getY() != apple->getY())
        {
            int emptyRow = snake.tail().getY();
            int emptyCol = snake.tail().getX();
            board->add(Empty(emptyRow, emptyCol));
            snake.removePiece();
        }
        else
        {
            delete apple;
            createApple();
            speed -= 5;
            board->setTimeout(speed);
        }

        board->add(next);
        snake.addPiece(next);
    }

    void redraw()
    {
        board->refresh();
    }

    bool isOver()
    {
        return game_over;
    }

private:
    bool game_over = false;
    bool is_paused = false;
    int height;
    int width;
    int speed;
    Snake snake;
    Board *board;
    Apple *apple = NULL;
    std::array<int, 3> &settingsState;
};
