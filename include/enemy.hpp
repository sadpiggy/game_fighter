#pragma once
#include "object.hpp"

/*
+ 采用object默认的render
+ 采用object默认的update
+ 覆盖handle_input，改为通过player的坐标自动寻敌

拥有自动寻敌的逻辑
+ 目前基于贪心来寻敌
*/
class Enemy : public Object {
    public:
        Enemy(int x, int y, int grid_size, int width, int height)
            : Object(x, y, grid_size, width, height) {
            color_r = 255;
            color_g = 0;
            color_b = 0;
        }
    
        void handle_input(int other_x, int other_y){
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
    };