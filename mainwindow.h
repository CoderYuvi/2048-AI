
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QLabel>
#include<QGridLayout>
#include<QPixmap>
#include<bits/stdc++.h>
#include<QMessageBox>
#include<QKeyEvent>
#include "board.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    virtual void keyPressEvent(QKeyEvent * event);
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void windowstart();
    void AIPlay();
    void endGame();
    void bestMove();
    void looks(int ,int);
    void updateUI();
    QWidget *centralWidget;
    QGridLayout *grid;
    QLabel* labels[4][4];
    Board myBoard;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
