#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<bits/stdc++.h>
#include<unistd.h>

#define vvi vector<vector<int>>
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    centralWidget = new QWidget(this);
    ui->setupUi(this);
    windowstart();
    srand(time(NULL));
    myBoard.begin();
    //    myBoard.print();
    this->setCentralWidget(centralWidget);
    grid = new QGridLayout(centralWidget);
    for(int  i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            labels[i][j]= new QLabel("",this);
            grid->addWidget(labels[i][j], i, j);
            labels[i][j]->setAlignment(Qt::AlignCenter);
            looks(i,j);
        }
    }
    updateUI();
}

void MainWindow::windowstart()
{
    setWindowTitle("2048 by kungfucat");
    setFixedSize(500,500);
    QPixmap bkgnd(":\background.jpeg");
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
}

void MainWindow::looks(int i,int j)
{
    switch(labels[i][j]->text().toInt())
    {
    case 0://skin
        labels[i][j]->setStyleSheet("QLabel { background-color: #F9C2AB; color: black; font:20pt; font-weight:500; border-radius: 10px;}");   break;
    case 2://yellow
        labels[i][j]->setStyleSheet("QLabel { background-color: #F9FBAE; color: black; font:30pt; font-weight:500; border-radius: 10px;}");   break;
    case 4://blue
        labels[i][j]->setStyleSheet("QLabel { background-color: #AEFBF3; color: black; font:30pt; font-weight:500; border-radius: 10px;}");   break;
    case 8://light purple
        labels[i][j]->setStyleSheet("QLabel { background-color: #BAC1FC; color: black; font:30pt; font-weight:500; border-radius: 10px;}");   break;
    case 16://light green
        labels[i][j]->setStyleSheet("QLabel { background-color: #BAFCBF; color: black; font:30pt; font-weight:500; border-radius: 10px;}");   break;
    case 32://blue + green
        labels[i][j]->setStyleSheet("QLabel { background-color: #5CE8C8; color: black; font:30pt; font-weight:500; border-radius: 10px;}");   break;
    case 64://purple + pink
        labels[i][j]->setStyleSheet("QLabel { background-color: #DE78E8; color: black; font:30pt; font-weight:500; border-radius: 10px;}");   break;
    case 128://dirty yellow
        labels[i][j]->setStyleSheet("QLabel { background-color: #E7C16E; color: black; font:30pt; font-weight:500; border-radius: 10px;}");   break;
    case 256://Shade of green
        labels[i][j]->setStyleSheet("QLabel { background-color: #CDE76E; color: black; font:30pt; font-weight:500; border-radius: 10px;}");   break;
    case 512://Blue shade
        labels[i][j]->setStyleSheet("QLabel { background-color: #7ABBE5; color: black; font:30pt; font-weight:500; border-radius: 10px;}");   break;
    case 1024://very light yellow
        labels[i][j]->setStyleSheet("QLabel { background-color: #FFFF90; color: black; font:30pt; font-weight:500; border-radius: 10px;}");   break;
    case 2048://Dark green
        labels[i][j]->setStyleSheet("QLabel { background-color: #0FA030; color: white; font:30pt; font-weight:500; border-radius: 10px;}");   break;
    case 4096://Dark Blue
        labels[i][j]->setStyleSheet("QLabel { background-color: #056F77; color: white; font:30pt; font-weight:500; border-radius: 10px;}");   break;
    case 8192://Dark Red
        labels[i][j]->setStyleSheet("QLabel { background-color: #DF3C08; color: white; font:30pt; font-weight:500; border-radius: 10px;}");   break;
    default ://White
        labels[i][j]->setStyleSheet("QLabel { background-color: #FFFFFF; color: black; font:30pt; font-weight:500; border-radius: 10px;}");   break;
    }
}

void MainWindow::keyPressEvent(QKeyEvent * event)
{

    switch (event->key())
    {
    case Qt::Key_Up:
        myBoard.up();
        break;
    case Qt::Key_Down:
        myBoard.down();
        break;
    case Qt::Key_Left:
        myBoard.left();
        break;
    case Qt::Key_Right:
        myBoard.right();
        break;
    case Qt::Key_Space:
        AIPlay();
        break;
    default:
        QMainWindow::keyPressEvent(event);
    }
    myBoard.fillATile();
    updateUI();
    if(myBoard.isFull())
        endGame();
}
void MainWindow::endGame(){
    if(myBoard.isFull()){
        QMessageBox::information(this,tr("GAME OVER."),tr("Well Played!!"));
        delete ui;
        return;
    }
}

char choice='$';
int MAX_DEPTH;
int expectiMax(Board& brd, int depth, int player){
//    cout<<depth<<" "<<player<<"\n";
    if(depth==0)return brd.heuresticValue();
    if(player==0){
        int sc=0,v;
        Board temp;

        temp=brd;
        temp.up();
        v=expectiMax(temp, depth-1, 1-player);
        if(v>sc){
            sc=v;
            if(depth==MAX_DEPTH)
                choice='U';
        }

        temp=brd;
        temp.down();
        v=expectiMax(temp, depth-1, 1-player);
        if(v>sc){
            sc=v;
            if(depth==MAX_DEPTH)
                choice='D';
        }


        temp=brd;
        temp.left();
        v=expectiMax(temp, depth-1, 1-player);
        if(v>sc){
            sc=v;
            if(depth==MAX_DEPTH)
                choice='L';
        }

        temp=brd;
        temp.right();
        v=expectiMax(temp, depth-1, 1-player);
        if(v>sc){
            sc=v;
            if(depth==MAX_DEPTH)
                choice='R';
        }
        return sc;
    }else{
        //BOARD is playing
        int sc=0, empties=0;
        vvi& grid=brd.brd;
        for(int i=0;i<brd.SIZE;i++){
            for(int j=0;j<brd.SIZE;j++){
                if(grid[i][j]!=0)    continue;
                empties++;
                grid[i][j]=2;
                sc+=0.9*(expectiMax(brd,depth-1, 1-player)*1.0);
                grid[i][j]=4;
                sc+=0.1*(expectiMax(brd,depth-1, 1-player)*1.0);
                grid[i][j]=0;
            }
        }
        if(empties==0)  return 1e6;

        return sc/empties;
    }
}

void MainWindow::bestMove(){
    MAX_DEPTH=5;
    choice='$';
    int v=expectiMax(myBoard,MAX_DEPTH,0);
    if(choice=='$'){
        cout<<v<<" "<<choice<<"\n";
    }
    myBoard.move(choice);

}

void MainWindow::AIPlay(){
    if(myBoard.isFull()){
        endGame();
    }
    bestMove();

}

bool valid(int x, int y){
    if(x<0 || y<0 || x>=4||y>=4)    return false;
    return true;
}

void MainWindow::updateUI(){
    for(int  i=0;i<4;i++){
        for(int j=0;j<4;j++){
            labels[i][j]->setText(QString::number((myBoard.brd[i][j])));
            if(myBoard.brd[i][j]==0)
                labels[i][j]->setText("");
            looks(i,j);
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
