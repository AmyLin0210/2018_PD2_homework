#include "choosewindow.h"
#include "solvesudoku.h"
#include "chooselevel.h"
#include <QDebug>

ChooseWindow::ChooseWindow()
{
    SolveSudokuWindow *solveWindow;
    ChooseLevelWindow *playWindow;
    solveWindow = new SolveSudokuWindow;
    playWindow = new ChooseLevelWindow;
    startGameButton = new QPushButton("玩遊戲", this);
    solveSudokuButton = new QPushButton("自訂題目", this);
    startGameButton->setStyleSheet("color:Black ; "
                                   "font-weight:bold;"
                                   "font-size: 15px;");
    solveSudokuButton->setStyleSheet("color:Black ; "
                                     "font-weight:bold;"
                                     "font-size: 15px;");

    QPixmap playGame(":/Image/play.png");                  //finish button
    playGame = playGame.scaled(70, 70);
    QIcon playIcon(playGame);
    startGameButton->setVisible(true);
    startGameButton->setGeometry(30, 30, 160,80);
    startGameButton->setIcon(playIcon);
    startGameButton->setIconSize(playGame.rect().size());

    QPixmap finishFlag(":/Image/solve.png");                  //finish button
    finishFlag = finishFlag.scaled(70, 70);
    QIcon finishIcon(finishFlag);
    solveSudokuButton->setVisible(true);
    solveSudokuButton->setGeometry(30, 120, 160,80);
    solveSudokuButton->setIcon(finishIcon);
    solveSudokuButton->setIconSize(finishFlag.rect().size());


    connect(solveSudokuButton, SIGNAL(clicked(bool)),
            solveWindow, SLOT(show()));
    connect(solveSudokuButton, SIGNAL(clicked(bool)),
            this, SLOT(close()));
    connect(startGameButton, SIGNAL(clicked(bool)),
            playWindow, SLOT(show()));
    connect(startGameButton, SIGNAL(clicked(bool)),
            this, SLOT(close()));

}
