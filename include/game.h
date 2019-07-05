#ifndef GAME_H
#define GAME_H

#include "cave.h"
#include "player.h"

class game {
public:
    game();
    ~game();
    void init();

protected:
    void clearScreen();
    void writePlayerStatsToFile();
    player* findPlayerFromFile(string name);
    int showGameScreen();

private:
    cave *cave_;
    player *player_;
};

#endif // GAME_H
