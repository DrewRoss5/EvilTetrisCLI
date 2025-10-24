#ifndef GAME_H
#define GAME_H

#define ROW_SIZE 10
#define COL_COUNT 20

#include <iostream> 
#include <vector>
#include <stdint.h>

class GameState{
    private:
        std::vector<int16_t> board;
        int score {0};
    public:
        GameState();
        void display();
        void set_row(size_t row, int16_t val) {this->board[row] = val;}
        bool update();

};

#endif