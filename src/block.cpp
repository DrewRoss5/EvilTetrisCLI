#include <chrono>
#include <cstdlib>

#include "../inc/block.hpp"

// THESE WILL BE CHANGED FOR THE BOARD CENTER AFTER
#define BOARD_CENTER_LEFT  0b0000100000
#define BOARD_CENTER_RIGHT 0b0000010000


// sets the seed for the random number generator to the current time
void init_rng(){
    srand(static_cast<unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count()));
}

// constructs a new random block
Block::Block(){
    // randomly generate a block type
    this->type = rand() % (BLOCK_T + 1);
    // create the coordinates for the appropriate block type
    switch (this->type){
        case BLOCK_O:
            this->coords = {{0, BOARD_CENTER_LEFT | BOARD_CENTER_RIGHT}, {1, BOARD_CENTER_LEFT | BOARD_CENTER_RIGHT}};
            this->width = 2;
            this->height = 2;
            break;
        case BLOCK_I:
            this->coords = {{0, BOARD_CENTER_LEFT}, {1, BOARD_CENTER_LEFT}, {2, BOARD_CENTER_LEFT}, {3, BOARD_CENTER_LEFT}};
            this->width = 1;
            this->height = 4;
            break;
        case BLOCK_S:
            this->coords = {{0, BOARD_CENTER_RIGHT | BOARD_CENTER_LEFT}, {1, BOARD_CENTER_RIGHT | (BOARD_CENTER_RIGHT << 1)}};
            this->width = 2;
            this->height = 3;
            break;
        case BLOCK_Z:
            this->coords = {{0, BOARD_CENTER_RIGHT | BOARD_CENTER_LEFT}, {1, BOARD_CENTER_LEFT | (BOARD_CENTER_LEFT >> 1)}};
            this->width = 2;
            this->height = 3;
            break;
        case BLOCK_L:
            this->coords = {{0, BOARD_CENTER_LEFT}, {1, BOARD_CENTER_LEFT}, {2, BOARD_CENTER_LEFT | BOARD_CENTER_RIGHT}};
            this->width = 2;
            this->height = 3;
            break;
        case BLOCK_J:
            this->coords = {{0, BOARD_CENTER_RIGHT}, {1, BOARD_CENTER_RIGHT}, {2, BOARD_CENTER_RIGHT | BOARD_CENTER_LEFT}};
            this->width = 2;
            this->height = 3;
            break;
        case BLOCK_T:
            this->coords = {{0, BOARD_CENTER_LEFT}, {1, (BOARD_CENTER_LEFT << 1) | BOARD_CENTER_LEFT | BOARD_CENTER_RIGHT}};
            this->width = 3;
            this->height = 2;
            break;
    }
}

Block Block::empty_block(){
    Block block;
    block.coords.clear();
    block.is_empty = true;
    return block;
}

std::pair<size_t, int16_t>& Block::operator[](size_t row){
    return this->coords[row];
}

// THIS FUNCTION IS FOR TESTING, AND WILL BE REMOVED!
void Block::randomize_col(){
    int offset = rand() % 9;
    for (std::pair<size_t, int16_t>& coord : this->coords){
        coord.second >>= offset;
    }
}