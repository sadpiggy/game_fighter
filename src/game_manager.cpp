#include "game_manager.hpp"
#include "utils.hpp"
#include <cstdlib>
#include <ctime>

GameManager::GameManager(int width, int height, int grid_size)
    : width(width), height(height), grid_size(grid_size),
      player(width / 2 / grid_size * grid_size,
             height / 2 / grid_size * grid_size,
             grid_size, width, height),hud(3)
{
    std::srand(std::time(nullptr));
}

GameManager::~GameManager() {
    cleanup();
}

void GameManager::init() {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Fight", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    hud.init_font("/System/Library/Fonts/NewYork.ttf", 24); 
}

void GameManager::run() {
    while (running) {
        handle_input();
        spawn_weapons();
        spawn_enemies();
        update();
        check_collisions();
        render();
        SDL_Delay(100);
        frame_count++;
    }
}

void GameManager::handle_input() {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) running = false;
        player.handle_input(event);
    }
    for (auto& enemy : enemy_queue) {
        enemy.handle_input(player.get_x(), player.get_y());
    }
}

void GameManager::spawn_weapons() {
    if (frame_count % spawn_weapon_interval != 0) return;
    int x = (std::rand() % (width / grid_size)) * grid_size;
    int y = (std::rand() % (height / grid_size)) * grid_size;
    weapon_queue.emplace_back(x, y, grid_size, width, height);
}

void GameManager::spawn_enemies() {
    if (frame_count % spawn_enemy_interval != 0) return;

    while (true) {
        int x = (std::rand() % (width / grid_size)) * grid_size;
        int y = (std::rand() % (height / grid_size)) * grid_size;
        if (abs(x - player.get_x()) <= 200 || abs(y - player.get_y()) <= 200) continue;
        enemy_queue.emplace_back(x, y, grid_size, width, height);
        break;
    }
}

void GameManager::update() {
    player.update();
    for (auto& enemy : enemy_queue) {
        // enemy.handle_input(player.get_x(), player.get_y());
        enemy.update();
    }
}

void GameManager::check_collisions() {
    for (size_t i = 0; i < weapon_queue.size(); ++i) {
        if (weapon_queue[i].get_x() == player.get_x() && weapon_queue[i].get_y() == player.get_y()) {
            player.has_weapon = true;
            weapon_queue.erase(weapon_queue.begin() + i);
            break;
        }
    }

    for (size_t i = 0; i < enemy_queue.size();) {
        bool hit = (enemy_queue[i].get_x() == player.get_x() && enemy_queue[i].get_y() == player.get_y());
        if (hit) {
            enemy_queue.erase(enemy_queue.begin() + i);
            if (player.has_weapon) {
                player.has_weapon = false;
                hud.add_score(1);
            } else {
                hud.lose_life(1);
                if (hud.get_life()<=0){
                    running = false;
                    fail(event, renderer);
                    break;
                }
            }
        } else {
            ++i;
        }
    }
}

void GameManager::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    player.render(renderer);
    for (auto& enemy : enemy_queue) enemy.render(renderer);
    for (auto& weapon : weapon_queue) weapon.render(renderer);
    hud.render(renderer);

    SDL_RenderPresent(renderer);
}

void GameManager::cleanup() {
    destroy_SDL(renderer, window);
}
