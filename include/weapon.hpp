#pragma once
#include "fighter.hpp"

class Weapon: public Fighter {
public:
    Weapon(int x, int y, int grid_size, int width, int height)
        : Fighter(x, y, grid_size, width, height) {
        color_r = 0;
        color_g = 0;
        color_b = 255;
    }

    void handle_input(SDL_Event& event){};  // 注意加 virtual
    void update(){};
protected:
    void move(){};

};