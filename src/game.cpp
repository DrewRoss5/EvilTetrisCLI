#include <ncurses.h>

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
        for (int i = this->curr_block.coords.size() - 1; i >= 0; i--){
            // check if there is space for the block to fall, and mark the block as empty if not
            if (curr_block.coords[i].first >= ROW_COUNT){
                this->curr_block = Block::empty_block();
                break;
            }
            curr_block.coords[i].first += 1;
        }
    }
    bool updated {false};
    for(int col = (ROW_COUNT - 2); col >= 0; col--){
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
                if ((col != (ROW_COUNT - 1)) && (row & mask) && !(this->board[col + 1] & mask)){
                    // move the block to the row below   
                    this->board[col + 1] |= mask;
                    // delete the block from this row, keeping others intact
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
    int input;
    input = getch();
    switch (input){
        case KEY_LEFT:
            for (int i = 0; i < this->curr_block.coords.size(); i++){
                // TODO: Add movement validation
                // remove the current block position from the board
                this->board[this->curr_block.coords[i].first] ^= this->curr_block.coords[i].second;
                // update the block's position
                this->curr_block.coords[i].second <<= 1;
                this->board[this->curr_block.coords[i].first] |= this->curr_block.coords[i].second;
            }
            break;
        case KEY_RIGHT:
            for (int i = 0; i < this->curr_block.coords.size(); i++){
                // TODO: Add movement validation
                // remove the current block position from the board
                this->board[this->curr_block.coords[i].first] ^= this->curr_block.coords[i].second;
                // update the block's position
                this->curr_block.coords[i].second >>= 1;
                this->board[this->curr_block.coords[i].first] |= this->curr_block.coords[i].second;
            }
            break;
    }
    clear();
    this->display();
    printw("\n%d", this->curr_block.coords[0].second << 1);
    refresh();
}