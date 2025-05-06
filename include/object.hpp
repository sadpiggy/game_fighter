#pragma once
#include <SDL2/SDL.h>
// 定义object，包含renderer, update的功能
/*
    object，具有render/update/还有handle_input的功能
    + render根据color_r/color_g/color_b来渲染小方块
    + update根据direction进行移动
    + handle_input根据键盘输入改变direction
    
*/
class Object {
    public:
        enum class Direction { UP, DOWN, LEFT, RIGHT };
    
        Object(int x, int y, int grid_size, int width, int height):x(x),y(y),grid_size(grid_size),screen_width(width),screen_height(height){

        }

        virtual ~Object() = default;
    
        virtual void handle_input(SDL_Event& event){
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

        virtual void update(){
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

        virtual void render(SDL_Renderer* render){
            SDL_Rect rect = { x, y, grid_size, grid_size };
            SDL_SetRenderDrawColor(render, color_r, color_g, color_b, 255); // 绿色
            SDL_RenderFillRect(render, &rect); 
        }
    
        virtual int get_x(){
            return x;
        }

        virtual int get_y(){
            return y;
        }

        virtual void change_color(Uint8 color_r_, Uint8 color_g_, Uint8 color_b_){
            color_r = color_r_;
            color_g = color_g_;
            color_b = color_b_;
        }
    
    protected:
    
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