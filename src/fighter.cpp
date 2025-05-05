#include "fighter.hpp"

Fighter::Fighter(int x, int y, int grid_size, int width, int height)
    : x(x), y(y), grid_size(grid_size), screen_width(width), screen_height(height) {
    // 默认颜色可以保留绿色或白色，供派生类覆盖
    color_r = 255;
    color_g = 255;
    color_b = 255;
}


void Fighter::handle_input(SDL_Event& event){
    // 对于方向键做出反应
    if (event.type == SDL_KEYDOWN){
        switch (event.key.keysym.sym){
            case SDLK_w:
            case SDLK_UP:
                /* code */
                dir = Direction::UP;
                break;
            case SDLK_s:
            case SDLK_DOWN:
                dir = Direction::DOWN;
                break;
            case SDLK_a:
            case SDLK_LEFT:
                dir = Direction::LEFT;
                break;
            case SDLK_d:
            case SDLK_RIGHT:
                dir = Direction::RIGHT;
                break;
            default:
                break;
        }
    }
}

void Fighter::render(SDL_Renderer* render){
    SDL_Rect rect = { x, y, grid_size, grid_size };
    SDL_SetRenderDrawColor(render, color_r, color_g, color_b, 255); // 绿色
    SDL_RenderFillRect(render, &rect);
}

void Fighter::update(){
    move();
}

void Fighter::move(){
    switch (dir)
    {
    case Direction::UP:
        /* code */
        y -= grid_size;
        if (y < 0){y = 0;}
        break;
    case Direction::DOWN:
        y += grid_size;
        if (y >= screen_height){y = screen_height - grid_size;}
        break;
    case Direction::LEFT:
        x -= grid_size;
        if (x<0){x=0;}
        break;
    case Direction::RIGHT:
        x += grid_size;
        if (x >= screen_width){x = screen_width - grid_size;}
    default:
        break;
    }
}

int Fighter::get_x(){
    return x;
}

int Fighter::get_y(){
    return y;
}

void Enemy::handle_input(int other_x, int other_y){
    int diff_x = abs(x - other_x);
    int diff_y = abs(y - other_y);

    if (diff_x >= diff_y){
        if (x <= other_x){dir = Direction::RIGHT;}
        else {dir = Direction::LEFT;}
    }else{
        if (y <= other_y)dir = Direction::DOWN;
        else dir = Direction::UP;
    }
}

void Player::render(SDL_Renderer* render){
    SDL_Rect rect = { x, y, grid_size, grid_size };
    if (has_weapon==false){
        SDL_SetRenderDrawColor(render, color_r, color_g, color_b, 255); // 绿色
    }else{
        SDL_SetRenderDrawColor(render, color_r, 125, 125, 255); // 怪色
    }
    SDL_RenderFillRect(render, &rect);
}