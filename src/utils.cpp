#include<utils.hpp>
#include <SDL2/SDL.h>
#include <iostream>

void fail(SDL_Event& event, SDL_Renderer* renderer){
    // 输出 Game Over
    SDL_Log("Game Over");
        
    // 渲染红色背景提示失败（可选）
    SDL_SetRenderDrawColor(renderer, 100, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    // 暂停逻辑：进入事件循环，直到玩家关闭窗口
    bool waitToClose = true;
    while (waitToClose) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                return;
        }
        SDL_Delay(100); // 避免 CPU 过载
    }
}

void destroy_SDL(SDL_Renderer* renderer, SDL_Window* window){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    std::cout<<"quit!!\n";
}