#include "chooselevel.h"
#include "playsudoku.h"
#include "settime.h"

ChooseLevelWindow::ChooseLevelWindow()
{

    easyButton = new QPushButton(" easy", this);
    easyButton->setGeometry(30, 30, 200, 60);
    QPixmap easyImg(":/Image/easy.png");                          //goback button
    easyImg = easyImg.scaled(45, 45);
    QIcon easyIcon(easyImg);
    easyButton->setVisible(true);
    easyButton->setIcon(easyIcon);
    easyButton->setIconSize(easyImg.rect().size());
    easyButton->setStyleSheet("color:Black ; "
                              "font-weight:bold;"
                              "font-size: 15px;");

    middleButton = new QPushButton("normal", this);
    middleButton->setGeometry(30, 90, 200, 60);
    QPixmap normalImg(":/Image/normal.png");                          //goback button
    normalImg = normalImg.scaled(45, 45);
    QIcon normalIcon(normalImg);
    middleButton->setVisible(true);
    middleButton->setIcon(normalIcon);
    middleButton->setIconSize(normalImg.rect().size());
    middleButton->setStyleSheet("color:Black ; "
                                "font-weight:bold;"
                                "font-size: 15px;");

    hardButton = new QPushButton(" hard", this);
    hardButton->setGeometry(30, 150, 200, 60);
    QPixmap hardImg(":/Image/hard.png");                          //goback button
    hardImg = hardImg.scaled(45, 45);
    QIcon hardIcon(hardImg);
    hardButton->setVisible(true);
    hardButton->setIcon(hardIcon);
    hardButton->setIconSize(hardImg.rect().size());
    hardButton->setStyleSheet("color:Black ; "
                              "font-weight:bold;"
                              "font-size: 15px;");

    setButton = new QPushButton("setting", this);
    setButton->setGeometry(30, 210, 200, 60);
    QPixmap settingImg(":/Image/setting.png");                          //goback button
    settingImg = settingImg.scaled(45, 45);
    QIcon settingIcon(settingImg);
    setButton->setVisible(true);
    setButton->setIcon(settingIcon);
    setButton->setIconSize(settingImg.rect().size());
    setButton->setStyleSheet("color:Black ; "
                              "font-weight:bold;"
                              "font-size: 15px;");

    connect(easyButton, SIGNAL(clicked(bool)),
            this, SLOT(EasyButtonClicked()));
    connect(middleButton, SIGNAL(clicked(bool)),
            this, SLOT(MiddleButtonClicked()));
    connect(hardButton, SIGNAL(clicked(bool)),
            this, SLOT(HardButtonClicked()));
    connect(setButton, SIGNAL(clicked(bool)),
            this, SLOT(SetButtonClicked()));

}

void ChooseLevelWindow:: EasyButtonClicked(){
    PlaySudokuWindow *playWindow;
    playWindow = new PlaySudokuWindow(&sudokuLevel, 1);
    playWindow->setWindowTitle("easy");
    playWindow->show();
    this->close();
}

void ChooseLevelWindow:: MiddleButtonClicked(){
    PlaySudokuWindow *playWindow;
    playWindow = new PlaySudokuWindow(&sudokuLevel, 2);
    playWindow->setWindowTitle("middle");
    playWindow->show();
    this->close();
}

void ChooseLevelWindow:: HardButtonClicked(){
    PlaySudokuWindow *playWindow;
//    int d = difficultyClass.difficulty[1];
    playWindow = new PlaySudokuWindow(&sudokuLevel, 3);
    playWindow->setWindowTitle("hard");
    playWindow->show();
    this->close();
}

void ChooseLevelWindow:: SetButtonClicked(){
    SetTime *setTimeWindow;
    setTimeWindow = new SetTime(&sudokuLevel);
    setTimeWindow->show();
}


