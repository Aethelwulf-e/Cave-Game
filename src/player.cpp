#include "player.h"

player::player(string name) {
    this->name    = name;
    this->isAlive = true;
    this->posX    = 0;
    this->posY    = 0;
    this->score   = 0;
    this->actions = stack<char>();
}

player::player(string name, int score, int posX, int posY, bool isAlive) {
    this->name    = name;
    this->score   = score;
    this->posX    = posX;
    this->posY    = posY;
    this->isAlive = isAlive;
    this->actions = stack<char>();
}

player::~player()                {}

int player::getPosX()            {return this->posX;}

int player::getPosY()            {return this->posY;}

int player::getScore()           {return this->score;}

string player::getName()         {return this->name;}

bool player::isDead()            {return ! this->isAlive;}

void player::kill()              {this->isAlive = false;}

void player::setScore(int score) {this->score = score;}

void player::increaseScore()     {this->score += 100;}

void player::decreaseScore()     {this->score == 0 ? this->score = 0 : this->score -= 100;}

void player::makeAMove(char direction) {
    this->actions.push(direction);

    if(direction == 'w') {
        this->posX -= 1;
    }
    else if(direction == 's') {
        this->posX += 1;
    }
    else if(direction == 'd') {
        this->posY += 1;
    }
    else if(direction == 'a') {
        this->posY -= 1;
    }
    else {
        this->actions.pop();
    }
}

void player::undoLastAction() {
    if(this->actions.empty()) {
        return;
    }

    char lastAction = this->actions.top();

    if(lastAction == 'w') {
        this->posX += 1;
    }
    else if(lastAction == 's') {
        this->posX -= 1;
    }
    else if(lastAction == 'd') {
        this->posY -= 1;
    }
    else {
        this->posY += 1;
    }

    this->actions.pop();
}
