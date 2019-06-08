#include "board.h"
#include<bits/stdc++.h>
#define vi std::vector<int>
#define pb push_back
Board::Board(){
    begin();
}

void Board::begin(){
    SIZE = 4;
    brd.clear();	brd.resize(SIZE, vi(SIZE, 0));
    int i = rand() % (SIZE * SIZE), ni = i;
    brd[i / SIZE][i % SIZE] =getRandom2or4();
    do {ni = rand() % (SIZE * SIZE);} while (ni == i);
    brd[ni / SIZE][ni % SIZE] =getRandom2or4();
}
bool Board::valid(int x, int y){
    return !(x<0||x>=SIZE||y<0||y>=SIZE);
}

void Board::print(){
    for(auto& x: brd){
        for(auto& y: x){
            cout<<y<<" ";
        }
        cout<<"\n";
    }
}

void Board::fillATile(){
    int as = 0;
    for (int i = 0; i < brd.size(); i++) {
        for (int j = 0; j < brd[i].size(); j++) {
            as += (brd[i][j] == 0);
        }
    }
    if(as==0)   return;
    int kk = 1 + (rand() % as);
    int fORt=rand()%100;
    as = 0;
    for (int i = 0; i < brd.size(); i++) {
        for (int j = 0; j < brd.size(); j++) {
            if (brd[i][j] == 0) {
                as++;
                if (as == kk) {
                    brd[i][j]=getRandom2or4();
                }
            }
        }
    }
    return;
}

const int dX[]={0,0,-1,+1};
const int dY[]={1,-1,0,0};

int Board::heuresticValue(){
    vector<vector<int>> table = {{12, 13, 14, 15}, {11, 10, 9, 8}, {4, 5, 6, 7}, {3, 2, 1, 0}};
    int sc=0, pen=0;
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            sc+=(table[i][j]*brd[i][j]);
        }
    }
    return sc;
}


void Board::fillRandom(){
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            brd[i][j] = 1 << (rand() % 2);
        }
    }
}

bool Board::isFull(){

    int i,j;
    const int dX[]={0,0,+1,-1};
    const int dY[]={+1,-1,0,0};
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            if(brd[i][j]==0)    return false;

    for (i=0;i<4;i++){
        for(j=0;j<4;j++){
            for(int k=0;k<4;k++){
                int nX=i+dX[k], nY=j+dY[k];
                if(valid(nX, nY) && brd[nX][nY]==brd[i][j]) return false;
            }
        }
    }
    return true;
}

int Board::getRandom2or4(){
    int r=rand()%100;
    if(r<90)   return 2;
    return 4;
}

void Board::move(char c){
    if(c=='U')
        up();
    else if(c=='L')
        left();
    else if(c=='R')
        right();
    else if(c=='D')
        down();
}
void Board::up(){
    for (int j = 0; j < SIZE; j++) {
        vi nZ;
        for (int i = 0; i < SIZE; i++) {if (brd[i][j] != 0)	nZ.pb(brd[i][j]);}
        for (int i = 0; i < nZ.size(); i++) {brd[i][j] = nZ[i];}
        for (int i = nZ.size(); i < SIZE; i++) {brd[i][j] = 0;}
    }
    for (int j = 0; j < SIZE; j++) {
        for (int i = 0; i < SIZE; i++) {
            if (valid(i + 1, j) && brd[i][j] != 0 && brd[i][j] == brd[i + 1][j]) {
                brd[i][j] *= 2;
                brd[i + 1][j] = 0;
            }
        }
    }

    for (int j = 0; j < SIZE; j++) {
        vi nZ;
        for (int i = 0; i < SIZE; i++) {if (brd[i][j] != 0)	nZ.pb(brd[i][j]);}
        for (int i = 0; i < nZ.size(); i++) {brd[i][j] = nZ[i];}
        for (int i = nZ.size(); i < SIZE; i++) {brd[i][j] = 0;}
    }
}


void Board::down(){
    for (int i = 0; i < brd.size() / 2; i++) {
        for (int j = 0; j < brd.size(); j++) {
            swap(brd[i][j], brd[SIZE - 1 - i][j]);
        }
    }

    up();

    for (int i = 0; i < brd.size() / 2; i++) {
        for (int j = 0; j < brd.size(); j++) {
            swap(brd[i][j], brd[SIZE - 1 - i][j]);
        }
    }
}

void Board::left(){
    for (int i = 0; i < SIZE; i++) {
        vi nZ;
        for (int j = 0; j < SIZE; j++) {if (brd[i][j] != 0)	nZ.pb(brd[i][j]);}
        for (int j = 0; j < nZ.size(); j++) {brd[i][j] = nZ[j];}
        for (int j = nZ.size(); j < SIZE; j++) {brd[i][j] = 0;}
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (valid(i, j + 1) && brd[i][j] != 0 && brd[i][j] == brd[i][j + 1]) {
                brd[i][j] *= 2;
                brd[i][j + 1] = 0;
            }
        }
    }
    for (int i = 0; i < SIZE; i++) {
        vi nZ;
        for (int j = 0; j < SIZE; j++) {if (brd[i][j] != 0)	nZ.pb(brd[i][j]);}
        for (int j = 0; j < nZ.size(); j++) {brd[i][j] = nZ[j];}
        for (int j = nZ.size(); j < SIZE; j++) {brd[i][j] = 0;}
    }
}

void Board::right(){
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE / 2; j++) {
            swap(brd[i][j], brd[i][SIZE - 1 - j]);
        }
    }
    left();
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE / 2; j++) {
            swap(brd[i][j], brd[i][SIZE - 1 - j]);
        }
    }
}
