#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include <stdint.h>

enum BlockDirection{
    RIGHT = 1,
    LEFT
};

enum BlockType{
    BLOCK_O = 0,
    BLOCK_I,
    BLOCK_S,
    BLOCK_Z,
    BLOCK_L,
    BLOCK_J,
    BLOCK_T
};

struct Block{
    Block();
    static Block empty_block();
    std::vector<std::pair<size_t, int16_t>> coords;
    std::pair<size_t, int16_t>& operator[](size_t row);
    int type;
    int width;
    int height;
    size_t bottom_index;
    size_t direction {RIGHT};
    bool is_empty {false};
    void randomize_col();
   
};

void init_rng();

#endif