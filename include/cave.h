#ifndef CAVE_H
#define CAVE_H

#include "block.h"

class cave {
public:
    cave(int rows, int cols, int numberOfHoles);
    ~cave();
    bool canGoTo(int posX, int posY);
    block* at(int posX, int posY);
    void show();
    int getRows();
    int getCols();

protected:
    void fill();
    bool isValidPosition(int posX, int posY);
    bool canInsertBreezeAt(int posX, int posY);

private:
    int rows;
    int cols;
    int numberOfHoles;
    block ***Cave;
};

#endif // CAVE_H
