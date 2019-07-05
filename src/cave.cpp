#include "cave.h"

#include <iostream>
#include <ctime>
#include <cstdlib>

using std::cout;
using std::endl;

cave::cave(int rows, int cols, int numberOfHoles) {
    this->rows = rows;
    this->cols = cols;
    this->numberOfHoles = numberOfHoles;
    this->Cave = new block**[rows];

    for(int i = 0; i < rows; i++) {
        this->Cave[i] = new block*[cols];
    }

    this->fill();
}

cave::~cave() {
    for(int i = 0; i < this->rows; i++) {
        for(int j = 0; j < this->cols; j++) {
            delete this->Cave[i][j];
        }
        delete [] this->Cave[i];
    }
    delete [] this->Cave;
}

void cave::show() {
    for(int i = 0; i < this->rows; i++) {
        for(int j = 0; j < this->cols; j++) {
            if(this->Cave[i][j]->wasVisited()) {
                if(this->Cave[i][j]->isAHole()) {
                    cout << "o ";
                }
                else if(this->Cave[i][j]->isExit()) {
                    cout << "# ";
                }
                else if(this->Cave[i][j]->thereIsBreeze()) {
                    cout << "~ ";
                }
                else if(this->Cave[i][j]->thereIsLight()) {
                    cout << "* ";
                } else {
                    cout << "x ";
                }
            } else {
                cout << "_ ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

void cave::fill() {
    for(int i = 0; i < this->rows; i++) {
        for(int j = 0; j < this->cols; j++) {
            this->Cave[i][j] = new block(false, false, false, false, false);
        }
    }

    srand(time(0));
    int posX_exit;
    int posY_exit;

    while(true) {
        posX_exit = rand() % this->rows;
        posY_exit = rand() % this->cols;

        if(isValidPosition(posX_exit, posY_exit)) {
            this->Cave[posX_exit][posY_exit] = new block(false, true, false, false, false);
            break;
        }
    }

    if(isValidPosition(posX_exit - 1, posY_exit)) {
        this->Cave[posX_exit - 1][posY_exit] = new block(false, false, true, false, false);
    }
    if(isValidPosition(posX_exit + 1, posY_exit)) {
        this->Cave[posX_exit + 1][posY_exit] = new block(false, false, true, false, false);
    }
    if(isValidPosition(posX_exit, posY_exit - 1)) {
        this->Cave[posX_exit][posY_exit - 1] = new block(false, false, true, false, false);
    }
    if(isValidPosition(posX_exit, posY_exit + 1)) {
        this->Cave[posX_exit][posY_exit + 1] = new block(false, false, true, false, false);
    }

    int counterOfHoles = this->numberOfHoles;

    while(counterOfHoles > 0) {
        int posX_hole = rand() % this->rows;
        int posY_hole = rand() % this->cols;

        if(isValidPosition(posX_hole, posY_hole)) {
            this->Cave[posX_hole][posY_hole] = new block(false, false, false, true, false);
            counterOfHoles -= 1;
        } else {
            continue;
        }

        if(canInsertBreezeAt(posX_hole - 1, posY_hole)) {
            this->Cave[posX_hole - 1][posY_hole] = new block(false, false, false, false, true);
        }

        if(canInsertBreezeAt(posX_hole + 1, posY_hole)) {
            this->Cave[posX_hole + 1][posY_hole] = new block(false, false, false, false, true);
        }

        if(canInsertBreezeAt(posX_hole, posY_hole - 1)) {
            this->Cave[posX_hole][posY_hole - 1] = new block(false, false, false, false, true);
        }

        if(canInsertBreezeAt(posX_hole, posY_hole + 1)) {
            this->Cave[posX_hole][posY_hole + 1] = new block(false, false, false, false, true);
        }
    }
}

bool cave::canGoTo(int posX, int posY) {
    return ((posX >= 0 && posX < this->rows) &&
            (posY >= 0 && posY < this->cols));
}

block* cave::at(int posX, int posY) {
    return this->Cave[posX][posY];
}

bool cave::canInsertBreezeAt(int posX, int posY) {
    return ((posX >= 0 && posX < this->rows) &&
            (posY >= 0 && posY < this->cols) &&
            (this->Cave[posX][posY]->isOrdinary()));
}

bool cave::isValidPosition(int posX, int posY) {
    return ((posX >= 0 && posX < this->rows) &&
            (posY >= 0 && posY < this->cols) &&
            (posX != 0 || posY != 0) &&
            (posX != 0 || posY != 1) &&
            (posX != 1 || posY != 0) &&
            (posX != 1 || posY != 1) &&
            (this->Cave[posX][posY]->isOrdinary()));
}

int cave::getRows() {return this->rows;}

int cave::getCols() {return this->cols;}
