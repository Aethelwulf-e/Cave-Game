#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <stack>

using std::string;
using std::stack;

class player {
public:
    player(string name);
    player(string name, int score, int posX, int posY, bool isAlive);
    ~player();
    bool isDead();
    void kill();
    void makeAMove(char direction);
    void undoLastAction();
    void increaseScore();
    void decreaseScore();
    void setScore(int score);
    int getPosX();
    int getPosY();
    int getScore();
    string getName();

private:
    string name;
    int score;
    int posX;
    int posY;
    bool isAlive;
    stack<char> actions;
};

#endif // PLAYER_H
