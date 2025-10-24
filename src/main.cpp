#include <iostream>
#include "../inc/game.hpp"
#include <thread> 
#include <chrono>

int main(){
    GameState game;
    game.set_row(19, 511);
    game.set_row(18, 449);
    game.set_row(17, 449);
    game.set_row(16, 1);
    game.set_row(0, 527);
    game.set_row(1, 512);
    game.set_row(2, 512);
    game.set_row(3, 512);
    while (true){
        game.display();
        if (!game.update()){
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
        system("clear");
    }
}