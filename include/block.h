#ifndef BLOCK_H
#define BLOCK_H

class block {
public:
    block(bool visited, bool exit, bool light, bool hole, bool breeze);
    block();
    ~block();
    bool isExit();
    bool isOcuppied();
    bool thereIsLight();
    bool isAHole();
    bool thereIsBreeze();
    bool isOrdinary();
    bool wasVisited();
    void visit();
    void leave();

private:
    bool exit;
    bool light;
    bool hole;
    bool breeze;
    bool visited;
    bool ocuppied;
};

#endif // BLOCK_H
