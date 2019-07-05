#ifndef BLOCK_H
#define BLOCK_H

class block {
public:
    block(bool visited, bool exit, bool light, bool hole, bool breeze);
    block();
    ~block();
    bool isExit();
    bool thereIsLight();
    bool isAHole();
    bool thereIsBreeze();
    bool isOrdinary();
    bool wasVisited();
    void visit();

private:
    bool exit;
    bool light;
    bool hole;
    bool breeze;
    bool visited;
};

#endif // BLOCK_H
