#ifndef BOARD_H
#define BOARD_H
#include<vector>
using namespace std;

class Board
{
public:
    int SIZE;
    vector<vector<int>> brd;
    Board();
    void fillATile();
    void fillRandom();
    int getRandom2or4();
    int heuresticValue();
    void begin();
    bool valid(int, int);
    void move(char);
    void up();
    void left();
    void down();
    void right();
    bool isFull();
    void print();
};

#endif // BOARD_H
