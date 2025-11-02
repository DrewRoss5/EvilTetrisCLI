#include <ncurses.h>
#include <cmath>

#include "../inc/game.hpp"
#include "../inc/block.hpp"



GameState::GameState(){
    init_rng();
    this->board = std::vector<int16_t>(ROW_COUNT);
    this->curr_block = Block::empty_block();
}


void GameState::display() {
    // clear the screen at the start of the frame
    clear();
    // display score at the top
    mvprintw(0, 0, "Score: %d", this->score);
    mvprintw(1, 0, "------------------------------------");
    for (int i = 2; i < ROW_COUNT; i++) {
        int16_t row = this->board[i];
        int offset = 3;
        mvprintw(i + 1, 0, " | ");
        int mask = 0b1000000000;
        for (int j = 0; j < ROW_SIZE; j++) {
            bool has_block = row & mask;
            mvprintw(i + 1, offset, (has_block) ? "#" : ".");
            mask >>= 1;
            offset += 2;
        }
        mvprintw(i + 1, offset, " |");
    }
    mvprintw(ROW_COUNT + 1, 0, "------------------------------------");
    refresh();
}

bool GameState::update(){
    if (!this->curr_block.is_empty){
        // if there's something under the bottom of the block, make it stop falling
        int16_t block_bottom = this->curr_block[curr_block.bottom_index].second;
        size_t bottom_index = this->curr_block[curr_block.bottom_index].first;
        if (bottom_index + 1 == ROW_COUNT || (this->board[bottom_index + 1] & block_bottom))
            this->curr_block = Block::empty_block();
        else{
            for (int i = this->curr_block.coords.size() - 1; i >= 0; i--)
                curr_block[i].first += 1;
        }
    }
    bool updated {false};
    for(int row_no = (ROW_COUNT - 1); row_no >= 0; row_no--){
        int16_t row = this->board[row_no];
        // if the line is full, clear it
        if (row == 1023){
            this->board[row_no] = 0;
            this->score += 100;
            updated = true;
            // check if the current block was in the line built
            if (this->curr_block[this->curr_block.bottom_index].first == row_no){
                this->curr_block[this->curr_block.bottom_index].second = 0;
                this->curr_block.bottom_index--;
                this->curr_block.height--;
                if (this->curr_block.height == 0)
                    this->curr_block = Block::empty_block();
            }
        }
        if (row_no != (ROW_COUNT - 1)){
            int16_t below = this->board[row_no + 1];
            int16_t falling = this->board[row_no] & ~below;
            this->board[row_no + 1] |= falling;
            this->board[row_no] &= ~falling;
        }
        if (board[row_no] != row)
            updated = true;
    }
    return updated;
}

// adds a random, player controlled block to the board
void GameState::add_random_block(){
    this->curr_block = Block();
    // this->curr_block.randomize_col(); // DELETE THIS
    for (std::pair<size_t, int16_t>& coord : this->curr_block.coords){
        // check if there's room to place the block segment on the board
        if (!(this->board[coord.first + 1] & coord.second))
            coord.first += 1;
        this->board[coord.first] |= coord.second;
    }
}

// awaits a player movement, and moves the block accordingly once one is found
void GameState::await_move(){
    std::vector<std::pair<size_t, int16_t>> new_coords;
    int input;
    input = getch();
    std::vector<int16_t> new_board;
    Block new_block = this->curr_block;
    switch (input){
        case KEY_LEFT:
            new_board = this->board;
            new_block = curr_block;
            for (int i = 0; i < this->curr_block.coords.size(); i++){
                // remove the current block position from the board
                new_board[new_block[i].first] ^= new_block[i].second;
                // ensure the block has enough room to move left
                if ((new_block[i].second << 1) > 1023 || (new_board[new_block[i].first] & (new_block[i].second << 1)))
                    return;
                // update the block's position
                new_block[i].second <<= 1;
                new_board[new_block[i].first] |= new_block[i].second;
            }
            this->curr_block = new_block;
            this->board = new_board;
            break;
        case KEY_RIGHT:
             new_board = this->board;
            new_block = curr_block;
            for (int i = 0; i < this->curr_block.coords.size(); i++){
                // remove the current block position from the board
                new_board[new_block[i].first] ^= new_block[i].second;
                // ensure the block has enough room to move left
                if ((new_block[i].second >> 1) < (pow(2, new_block.width - 1)) || (new_board[new_block[i].first] & (new_block[i].second >> 1)))
                    return;
                // update the block's position
                new_block[i].second >>= 1;
                new_board[new_block[i].first] |= new_block[i].second;
            }
            this->curr_block = new_block;
            this->board = new_board;
    }
    clear();
}