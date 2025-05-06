#include <SDL2/SDL.h>
#include <iostream>
#include "enemy.hpp"
#include "player.hpp"
#include <deque>
#include "weapon.hpp"
#include "utils.hpp"


int main() {
    std::cout << "hello fight game!\n";

    // 初始化
    int grid_size = 20;
    int width = 720;
    int height = 720;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Fight", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // player初始化
    int player_x_start = width / 2 / grid_size * grid_size;
    int player_y_start = height / 2 / grid_size * grid_size;
    Player player(player_x_start, player_y_start, grid_size, width, height);

    // enemy队列初始化
    std::deque<Enemy> enemy_queue;
    enemy_queue.emplace_back(0, 0, grid_size, width, height);

    // weapon队列初始化
    std::deque<Weapon> weapon_queue;
    weapon_queue.emplace_back(width - grid_size, height - grid_size, grid_size, width, height);

    int frame_count = 0;
    int spawn_enemy_interval = 50;
    int spawn_weapon_inierval = 20;
    bool running = true;
    SDL_Event event;

    while (running) {
        // 输入
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
            player.handle_input(event);
        }

        // 生成武器和敌人
        frame_count++;

        if (frame_count % spawn_weapon_inierval == 0){
            int spawn_x = (std::rand() % (width / grid_size)) * grid_size;
            int spawn_y = (std::rand() % (height / grid_size)) * grid_size;
            weapon_queue.emplace_back(spawn_x, spawn_y, grid_size, width, height);
        }


        if (frame_count % spawn_enemy_interval == 0) {
            while (true){
                int spawn_x = (std::rand() % (width / grid_size)) * grid_size;
                int spawn_y = (std::rand() % (height / grid_size)) * grid_size;
                // 防止壁咚
                if ((abs(spawn_x - player.get_x()) <= 200) || (abs(spawn_y - player.get_y()) <= 200)){
                    continue;
                }else{
                    enemy_queue.emplace_back(spawn_x, spawn_y, grid_size, width, height);
                    break;
                }
            }
        }

        // 更新所有对象
        player.update();
        for (auto& enemy : enemy_queue) {
            enemy.handle_input(player.get_x(), player.get_y());
            enemy.update();
        }

        // 检测碰撞
        // 检测武器碰撞
        for (size_t i = 0; i < weapon_queue.size(); ++i) {
            bool collision = (weapon_queue[i].get_x() == player.get_x() &&
                              weapon_queue[i].get_y() == player.get_y());
            if (collision) {
                player.has_weapon = true;
                weapon_queue.erase(weapon_queue.begin() + i);  // 删除该武器
                break;  // 如果每次只拾取一个，建议 break；否则 i 不用加
            }
        }
        
        // 检测敌人碰撞
        bool collision_enemy = false;
        for (size_t i = 0; i < enemy_queue.size();) {
            // auto& enemy = enemy_queue[i];
            bool collision = (enemy_queue[i].get_x()==player.get_x() && enemy_queue[i].get_y()==player.get_y());
            if (collision) {
                collision_enemy = true;
                if (player.has_weapon){
                    enemy_queue.erase(enemy_queue.begin()+i);
                }else{
                    running = false;
                    fail(event, renderer);
                    destroy_SDL(renderer, window);
                    return 0;
                    // break;
                }
            }else{
                ++i;
            }
        }
        if (collision_enemy == true){ player.has_weapon = false;}


        // 渲染
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        player.render(renderer);
        for (auto& enemy : enemy_queue) {
            enemy.render(renderer);
        }
        for (auto& weapon : weapon_queue){
            weapon.render(renderer);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(100);
    }

    destroy_SDL(renderer, window);
    return 0;
}
