#include <iostream>
#include "game.h"

using namespace std;

int main() {
    game *newGame = new game();

    newGame->init();

    delete newGame;

    return 0;
}
