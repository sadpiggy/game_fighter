#pragma once
#include "object.hpp"

/*
+ 采用object默认的update
+ 采用object默认的handle_input
+ 覆盖object的render，拥有weapon时修改颜色（改变alpha value）

默认绿色，拥有武器后变成另外一种颜色
*/
class Player : public Object {
    public:
        Player(int x, int y, int grid_size, int width, int height)
            : Object(x, y, grid_size, width, height) {
            color_r = 0;
            color_g = 255;
            color_b = 0;
            has_weapon = false;
        }
    
        void render(SDL_Renderer* render){
            SDL_Rect rect = { x, y, grid_size, grid_size };
            if (has_weapon==false){
                SDL_SetRenderDrawColor(render, color_r, color_g, color_b, 255); // 绿色
            }else{
                SDL_SetRenderDrawColor(render, color_r, color_g, color_g, 125); // 怪色
            }
            SDL_RenderFillRect(render, &rect);   
        }
        
        bool has_weapon;
};