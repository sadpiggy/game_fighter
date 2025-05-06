#include "hud.hpp"
#include <sstream>

HUD::HUD(int initial_life) : score(0), life(initial_life) {}

HUD::~HUD() {
    if (font) TTF_CloseFont(font);
}

bool HUD::init_font(const std::string& font_path, int font_size) {
    if (TTF_Init() != 0) {
        SDL_Log("TTF_Init error: %s", TTF_GetError());
        return false;
    }
    font = TTF_OpenFont(font_path.c_str(), font_size);
    if (!font) {
        SDL_Log("Failed to load font: %s", TTF_GetError());
        return false;
    }
    return true;
}

void HUD::add_score(int points) {
    score += points;
}

void HUD::lose_life(int amount) {
    life -= amount;
}

int HUD::get_score() const { return score; }
int HUD::get_life() const { return life; }

void HUD::render(SDL_Renderer* renderer) {
    if (!font) return;

    SDL_Color color = {255, 255, 255};  // 白色
    std::ostringstream oss;
    oss << "Score: " << score << "  |  Life: " << life;
    std::string text = oss.str();

    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect dst;
    dst.x = 10;
    dst.y = 10;
    dst.w = surface->w;
    dst.h = surface->h;

    SDL_RenderCopy(renderer, texture, nullptr, &dst);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}
