#include "solvesudoku.h"
#include "solvesudokufunction.h"
#include "choosewindow.h"

SolveSudokuWindow::SolveSudokuWindow()
{
    int count;
    errorMessage = new QLabel(this);                 //new error message
    errorMessage->setGeometry(30, 0, 150, 30);
    errorMessage->setStyleSheet("font-family:fantasy;");

    backgroundColor = new QPalette();
    backgroundColor->setColor(QPalette::Background, Qt::white);
    this->setPalette(*backgroundColor);

    basicColor = new QPalette();
    basicColor->setColor(QPalette::Base, QColor(220,220,220));

    buttonColor = new QPalette();
    buttonColor->setColor(QPalette::Base, QColor(173,216,230));

    QPixmap finishFlag(":/Image/finish_flag.png");                  //finish button
    finishFlag = finishFlag.scaled(50, 50);
    QIcon finishIcon(finishFlag);
    finishButton = new QPushButton(this);
    finishButton->setGeometry(90, 310, 60, 60);
    finishButton->setIcon(finishIcon);
    finishButton->setIconSize(finishFlag.rect().size());
    finishButton->setPalette(*buttonColor);

    QPixmap homeImg(":/Image/home.png");                          //goback button
    homeImg = homeImg.scaled(50, 50);
    QIcon homeIcon(homeImg);
    homeButton = new QPushButton(this);
    homeButton->setVisible(true);
    homeButton->setGeometry(160, 310, 60, 60);
    homeButton->setIcon(homeIcon);
    homeButton->setIconSize(homeImg.rect().size());

    for(count = 0; count <81; count++){                             //new sudoku value
        sudoku[count/9][count%9] = new QLineEdit(this);
        sudoku[count/9][count%9]->setGeometry(30+30*(count%9),30+30*(count/9),30,30);
        sudoku[count/9][count%9]->setAlignment(Qt::AlignCenter);
        sudoku[count/9][count%9]->setStyleSheet("font-weight:bold;"
                                                "color:black;"
                                                "font-size: 15px;");
    }

    SetBackground();

    for(count = 0; count < 81; count++){
       connect(sudoku[count/9][count%9], SIGNAL(editingFinished()),     //check if the input value legally
                this, SLOT(CheckValueCorrect()));
       connect(this, SIGNAL(InputError()),
                this, SLOT(InputErrorMessenge()));
       connect(this, SIGNAL(InputCorrect()),
               this, SLOT(InputCorrectMessage()));
    }

    connect(finishButton, SIGNAL(clicked(bool)),
            this, SLOT(CheckSudoku()));
    connect(homeButton, SIGNAL(clicked(bool)),
            this, SLOT(HomeFcn()));

}

void SolveSudokuWindow::CheckValueCorrect()
{
    int count, flag = 0;
    QString inputValue;
    QByteArray ba;
    char *number;
    for(count = 0; count < 81; count++){
        inputValue = sudoku[count/9][count%9]->text();
        ba = inputValue.toLatin1();
        number = ba.data();
        if(inputValue == NULL ||(inputValue.length() == 1 && *number <= 57 && *number>=49)){
        }
        else{
            emit InputError();
            sudoku[count/9][count%9]->setText("");                         //因為填錯了，電腦自動把填錯那行還原空白
            flag = 1;
            break;
        }
    }

    if(flag == 0)
        emit InputCorrect();
}

void SolveSudokuWindow::HomeFcn(){
    ChooseWindow *chooseWindow;
    chooseWindow = new ChooseWindow;
    chooseWindow->show();
    this->close();
}

void SolveSudokuWindow::InputCorrectMessage()
{
    errorMessage->setText("");
}

void SolveSudokuWindow::InputErrorMessenge()
{
    errorMessage->setText("please input number 1~9");
//    QMessageBox::warning(this, "error", "please input number 1~9");

}

void SolveSudokuWindow::CheckSudoku()
{
    int count;
    int number;
    SolveSudokuFunction S;
    bool sudokuAns;
    QString sudokuNum;

    for(count = 0; count < 81; count++){
        if(sudoku[count/9][count%9] == NULL)
            number = 0;
        else{
            number = sudoku[count/9][count%9]->text().toInt();
        }
        S.SetElement(count, number);
    }

    sudokuAns = S.SolveSudoku(0,S,0);

    if(sudokuAns == false)
        QMessageBox::warning(this, "error", "no solution");
    else{
        for(count = 0; count <81; count++){
            sudokuNum = QString::number(S.map[count/9][count%9]);
            if(sudoku[count/9][count%9]->text() == ""){
                sudoku[count/9][count%9]->setText(sudokuNum);
                sudoku[count/9][count%9]->setStyleSheet("color:SteelBlue ; "
                                                        "font-weight:bold;"
                                                        "font-size: 15px;");
            }
        }
        errorMessage->setText("good question!");
        finishButton->setVisible(false);
        homeButton->setGeometry(125, 310, 60,60);
    }

}

void SolveSudokuWindow ::SetBackground(){
    int count;
    for(count = 0; count < 81; count++){
        if(((count/9 > 2 && count/9 < 6 )&& (count%9 < 3 || count%9 >5)) ||
                ((count%9 > 2 && count%9 < 6 )&& (count/9 <3 || count/9 >5)))
            sudoku[count/9][count%9]->setPalette(*basicColor);
    }
}
