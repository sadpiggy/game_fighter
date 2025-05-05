#pragma once
#include <SDL2/SDL.h>

class Fighter {
public:
    enum class Direction { UP, DOWN, LEFT, RIGHT };

    Fighter(int x, int y, int grid_size, int width, int height);
    virtual ~Fighter() = default;

    virtual void handle_input(SDL_Event& event);  // 注意加 virtual
    virtual void update();
    virtual void render(SDL_Renderer* renderer);

    virtual int get_x();
    virtual int get_y();

protected:
    void move();

    int x, y;
    int grid_size;
    int screen_width;
    int screen_height;
    Direction dir = Direction::UP;

    // 新增颜色成员变量（r, g, b）
    Uint8 color_r = 255;
    Uint8 color_g = 255;
    Uint8 color_b = 255;
};

class Player : public Fighter {
public:
    Player(int x, int y, int grid_size, int width, int height)
        : Fighter(x, y, grid_size, width, height) {
        color_r = 0;
        color_g = 255;
        color_b = 0;
        has_weapon = false;
    }

    void render(SDL_Renderer* renderer);
    
    bool has_weapon;
};
    

class Enemy : public Fighter {
public:
    Enemy(int x, int y, int grid_size, int width, int height)
        : Fighter(x, y, grid_size, width, height) {
        color_r = 255;
        color_g = 0;
        color_b = 0;
    }

    void handle_input(int other_x, int other_y);
};
        
