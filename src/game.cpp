#include "../inc/game.hpp"
#include "../inc/block.hpp"

GameState::GameState(){
    init_rng();
    this->board = std::vector<int16_t>(COL_COUNT);
    this->curr_block = Block::empty_block();
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
    if (!this->curr_block.is_empty){
        for (int i = this->curr_block.coords.size() - 1; i >= 0; i--){
            // check if there is space for the block to fall, and mark the block as empty if not
            if (curr_block.coords[i].first >= COL_COUNT || (curr_block.coords[i].second & this->board[this->curr_block.coords[i].first + 1])){
                this->curr_block = Block::empty_block();
                break;
            }
            curr_block.coords[i].first += 1;
        }
    }
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

// adds a random, player controlled block to the board
void GameState::add_random_block(){
    this->curr_block = Block();
    this->curr_block.randomize_col(); // DELETE THIS
    for (const std::pair<int, int16_t>& coord : this->curr_block.coords)
        this->board[coord.first] ^= coord.second;
}