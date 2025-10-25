#ifndef GAME_H
#define GAME_H

#define ROW_SIZE 10
#define COL_COUNT 20

#include <iostream> 
#include <vector>
#include <stdint.h>
#include "../inc/block.hpp"

class GameState{
    private:
        std::vector<int16_t> board;
        int score {0};
        Block curr_block;
    public:
        GameState();
        void display();
        void set_row(size_t row, int16_t val) {this->board[row] = val;}
        bool update();
        void add_random_block();

};

#endif