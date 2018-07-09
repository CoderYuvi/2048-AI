#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    centralWidget = new QWidget(this);
     ui->setupUi(this);
     windowstart();
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
         nexttile();
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

void MainWindow::nexttile()
{
    int i,j,r,count=0,k=0;
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            if(labels[i][j]->text().toInt()==0)
                k++;
        }
    }
    if(k!=0)
    {
    r=rand()%k;
    for(i=0;i<4;i++)
            {
                for(j=0;j<4;j++)
                {
                    if(labels[i][j]->text().toInt()==0)
                        count++;
                    if(count==r+1)
                    {
                        labels[i][j]->setText("2");
                        looks(i,j);
                        break;
                    }
                }
            }
    }
}
bool MainWindow::boardfull()
{
    int i,j;
    for (i=0;i<3;i++)
    {
        for(j=0;j<4;j++)
        {
            if(labels[i][j]->text().toInt()==labels[i+1][j]->text().toInt()||labels[i][j]->text().toInt()==0)
                return false;
        }
    }
    for (i=0;i<4;i++)
    {
        for(j=0;j<3;j++)
        {
            if(labels[i][j]->text().toInt()==labels[i][j+1]->text().toInt()||labels[i][j]->text().toInt()==0)
                return false;
        }
    }
    return true;
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
    int i,j,a[4][4];
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        a[i][j]=labels[i][j]->text().toInt();
    }
   switch (event->key())
    {
        case Qt::Key_Up:
            up(a);
            break;
        case Qt::Key_Down:
            down(a);
            break;
        case Qt::Key_Left:
            left(a);
            break;
        case Qt::Key_Right:
            right(a);
            break;
        default:
          QMainWindow::keyPressEvent(event);
    }
    if(boardfull()==true)
    {
        QMessageBox::information(this,tr("GAME OVER."),tr("Well Played!!"));
        delete ui;
    }
     nexttile();
}
void MainWindow::up(int a[4][4])
{
    int i,j,k;
    for(i=0; i<4; i++)
        for(j=0; j<4; j++)
        {
            if(!a[j][i])
            {
                for(k=j+1; k<4; k++)
                    if(a[k][i])
                    {
                        a[j][i]=a[k][i];
                        a[k][i]=0;
                        break;
                    }
            }
        }
    for(i=0; i<4; i++)
        for(int j=0; j<3; j++)
        {
            if(a[j][i]&&a[j][i]==a[j+1][i])
            {
                a[j][i]+=a[j+1][i];
                a[j+1][i]=0;

            }
        }
    for(i=0; i<4; i++)
    {
        for(j=0; j<4; j++)
        {
            labels[i][j]->setText(QString::number((a[i][j])));
            if(labels[i][j]->text().toInt()==0)
                labels[i][j]->setText("");
            looks(i,j);
        }
    }
}
void MainWindow::down(int a[4][4])
{
    int i,j,k;
    for(i=0; i<4; i++)
        for(j=3; j>=0; j--)
        {
            if(!a[j][i])
            {
                for(k=j-1; k>=0; k--)
                    if(a[k][i])
                    {
                        a[j][i]=a[k][i];
                        a[k][i]=0;
                        break;
                    }
            }

        }
    for(i=0; i<4; i++)
        for(j=3; j>0; j--)
        {
            if(a[j][i]&&a[j][i]==a[j-1][i])
            {
                a[j][i]+=a[j-1][i];
                a[j-1][i]=0;
            }
        }
    for(i=0; i<4; i++)
    {
        for(j=0; j<4; j++)
        {
            labels[i][j]->setText(QString::number((a[i][j])));
            if(labels[i][j]->text().toInt()==0)
                labels[i][j]->setText("");
            looks(i,j);
        }
    }
}
void MainWindow::left(int a[4][4])
{
    int i,j,k;
    for(i=0; i<4; i++)
        for(j=0; j<4; j++)
        {
            if(!a[i][j])
            {
                for(k=j+1; k<4; k++)
                    if(a[i][k])
                    {
                        a[i][j]=a[i][k];
                        a[i][k]=0;
                        break;
                    }
            }

        }
    for(i=0; i<4; i++)
        for( j=0; j<3; j++)
        {
            if(a[i][j]&&a[i][j]==a[i][j+1])
            {
                a[i][j]+=a[i][j+1];
                a[i][j+1]=0;
            }
        }
    for(i=0; i<4; i++)
    {
        for(j=0; j<4; j++)
        {
            labels[i][j]->setText(QString::number((a[i][j])));
            if(labels[i][j]->text().toInt()==0)
                labels[i][j]->setText("");
            looks(i,j);
        }
    }

}
void MainWindow::right(int a[4][4])
{
    int i,j,k;
    for(i=0; i<4; i++)
        for(j=3; j>=0; j--)
        {
            if(!a[i][j])
            {
                for(k=j-1; k>=0; k--)
                    if(a[i][k])
                    {
                        a[i][j]=a[i][k];
                        a[i][k]=0;
                        break;
                    }
            }

        }
    for(int i=0; i<4; i++)
        for(j=3; j>0; j--)
        {
            if(a[i][j]&&a[i][j]==a[i][j-1])
            {
                a[i][j]+=a[i][j-1];
                a[i][j-1]=0;
            }
        }
    for(i=0; i<4; i++)
    {
        for(j=0; j<4; j++)
        {
            labels[i][j]->setText(QString::number((a[i][j])));
            if(labels[i][j]->text().toInt()==0)
                labels[i][j]->setText("");
            looks(i,j);
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
