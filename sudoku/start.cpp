#include "start.h"
#include "ui_start.h"
#include "choosewindow.h"

start::start()
{
    ChooseWindow *switchWindow;

    backgroundColor = new QPalette();
    backgroundColor->setColor(QPalette::Background, Qt::white);
    this->setPalette(*backgroundColor);

    startLable = new QLabel(this);
    QPixmap sudokuImg(":/Image/sudoku.png");                  //finish button
    sudokuImg= sudokuImg.scaled(200, 200);
    startLable->setGeometry(50, 50, 200, 200);
    startLable->setPixmap(sudokuImg);


    QPixmap startImg(":/Image/start.png");                  //finish button
    startImg = startImg.scaled(50, 50);
    QIcon startIcon(startImg);
    startButton = new QPushButton(this);
    startButton->setGeometry(120, 270, 60, 60);
    startButton->setIcon(startIcon);
    startButton->setIconSize(startImg.rect().size());


    switchWindow = new ChooseWindow;

    connect(startButton, SIGNAL(clicked(bool)),
            this, SLOT(close()));
    connect(startButton, SIGNAL(clicked(bool)),
            switchWindow, SLOT(show()));
}


