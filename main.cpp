#include "game_manager.hpp"

int main() {
    GameManager game(720, 720, 20);
    game.init();
    game.run();
    return 0;
}
