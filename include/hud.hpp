#pragma once

#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include <string>

class HUD{
public:
    HUD(int initial_life);
    ~HUD();

    int get_life() const;
    int get_score() const;

    void add_score(int points);
    void lose_life(int amount);

    void render(SDL_Renderer* renderer);

    bool init_font(const std::string& font_path, int font_size);

private:
    int life;
    int score;

    TTF_Font* font = nullptr;

};