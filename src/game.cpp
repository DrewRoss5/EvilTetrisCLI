#include "../inc/game.hpp"

GameState::GameState(){
    this->board = std::vector<int16_t>(COL_COUNT);
}

void GameState::display(){
    // display board top
    std::cout << "Score: " << this->score << "\n------------------------------------" << std::endl;
    for (int16_t row : this->board){
        std::cout << " | ";
        // display all tiles from left to right, 1 represents a tile, 0 represents a blank space
        int mask = 0b1000000000;
        for (int i = 0; i < ROW_SIZE; i++){
            bool has_block = row & mask;
            std::cout << ((has_block) ? "\033[37m ▮ \033[0m" : "\033[39m . \033[0m");
            // shift bitmask over one bit
            mask >>= 1;
        }
        std::cout << " | " << std::endl;

    }
    std::cout << "------------------------------------" << std::endl;
}

bool GameState::update(){
    bool updated {false};
    for(int col = (COL_COUNT - 1); col >= 0; col--){
        int16_t row = this->board[col];
        for (int i = 0; i < ROW_SIZE; i++){
            // if the line is full, clear it
            if (row == 1023){
                this->board[col] = 0;
                this->score += 100;
                updated = true;
                break;
            }
            // drop any falling lines
            int mask = 0b1000000000;
            for (int i = 0; i < ROW_SIZE; i++){
                if ((col != (COL_COUNT - 1)) && (row & mask) && !(this->board[col + 1] & mask)){
                    this->board[col + 1] |= mask;
                    this->board[col] ^= mask;
                    updated = true;
                }
                mask >>= 1;
            }
        }
    }
    return updated;
}