#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QLabel>
#include<QGridLayout>
#include<QPixmap>
#include<QMessageBox>
#include<QKeyEvent>
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
    void play();
    void Move();
    bool boardfull();
    void nexttile();
    void looks(int ,int);
    void up(int a[4][4]);
    void left(int a[4][4]);
    void right(int a[4][4]);
    void down(int a[4][4]);
    QWidget *centralWidget;
    QGridLayout *grid;
    QLabel* labels[4][4];
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
