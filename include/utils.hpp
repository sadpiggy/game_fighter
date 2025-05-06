#pragma once

#include <SDL2/SDL.h>

void fail(SDL_Event& event, SDL_Renderer* renderer);

void destroy_SDL(SDL_Renderer* renderer, SDL_Window* window);