#pragma once
#include <SDL2/SDL.h>
#include <deque>
#include "player.hpp"
#include "enemy.hpp"
#include "weapon.hpp"
#include "hud.hpp"

class GameManager {
public:
    GameManager(int width, int height, int grid_size);
    ~GameManager();

    void init();
    void run();

private:
    void handle_input();
    void spawn_enemies();
    void spawn_weapons();
    void update();
    void check_collisions();
    void render();
    void cleanup();

    int width, height, grid_size;
    int frame_count = 0;
    bool running = true;

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Event event;

    Player player;
    std::deque<Enemy> enemy_queue;
    std::deque<Weapon> weapon_queue;

    const int spawn_enemy_interval = 50;
    const int spawn_weapon_interval = 20;

    HUD hud;
};
