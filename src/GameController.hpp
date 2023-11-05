#pragma once

#include "GameEntities/Apple.hpp"
#include "GameEntities/Empty.hpp"
#include "GameEntities/Drawable.hpp"
#include "GameEntities/Board.hpp"
#include "GameEntities/Snake.hpp"

class SnakeGame
{
public:
    SnakeGame(int height, int width)
    {
        this->heigth = height;
        this->width = width;
        board = new Board(height, width);
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
    }

    ~SnakeGame()
    {
        delete apple;
        delete board;
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
            if (next.getY() != heigth - 2 && snake.getDirection() != up && !is_paused)
            {
                snake.setDirection(down);
            }
            break;
        case KEY_UP:
            if (next.getY() != 1 && snake.getDirection() != down && !is_paused)
            {
                snake.setDirection(up);
            }
            break;
        case KEY_LEFT:
            if (next.getX() != 1 && snake.getDirection() != right && !is_paused)
            {
                snake.setDirection(left);
            }
            break;
        case KEY_RIGHT:
            if (next.getX() != width - 2 && snake.getDirection() != left && !is_paused)
            {
                snake.setDirection(right);
            }
            break;
        case KEY_BACKSPACE:
            is_paused == true ? is_paused = false : is_paused = true;
            break;
        }
    }

    void checkColisions()
    {
        // collissions with walls
        // collissions with apple
        // collistions with snake
    }

    void updateState()
    {
        if (apple == NULL)
        {
            int y, x;
            board->getEmptyCoordinates(y, x);
            apple = new Apple(y, x);
            board->add(*apple);
        }

        SnakePiece next = snake.nextHead();
        SnakePiece head = snake.head();

        // Collisions with walls
        if (head.getX() == 0 || head.getX() == width - 1 || head.getY() == 0 || head.getY() == heigth - 1)
        {
            is_paused = 1;
            game_over = 1;
        }

        if (board->getCharAt(next.getY(), next.getX()) == '#'){
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
            apple = NULL;
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
    int heigth;
    int width;
    Snake snake;
    Board *board;
    Apple *apple{NULL};
};