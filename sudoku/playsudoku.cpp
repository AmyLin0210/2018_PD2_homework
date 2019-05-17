#include "playsudoku.h"
#include "choosewindow.h"

PlaySudokuWindow::PlaySudokuWindow(difficultyClass *levelOfSudoku, int whichLevel)
{
    sudokuLevel = levelOfSudoku;
    difficulty = whichLevel;
    puzzlesNum = sudokuLevel->puzzleNum[difficulty];
    elapsedTime = sudokuLevel->elapsedTime[difficulty];

    int count, a[9];
    finalMessage = new QMessageBox(this);

    backgroundColor = new QPalette();                               //設定背景色
    backgroundColor->setColor(QPalette::Background, Qt::white);
    this->setPalette(*backgroundColor);   

    myTimer = new QTimer(this);                                     //設定倒數計時器
    myTimer->start(1000);                                           //每一千毫秒為一單位

    remainingTime = new QLCDNumber(this);                           //設定倒數計時錶
    remainingTime->setGeometry(210, 5, 100, 25);
    remainingTime->setDigitCount(5);
    myTimer->start(1000);

    errorMessage = new QLabel(this);                                //new error message
    InitiallizeErrorMessage();

    finishButton = new QPushButton(this);                           //設定button
    resetButton = new QPushButton(this);
    gobackButton = new QPushButton(this);
    hintButton = new QPushButton(this);
    InitiallizeButton();

    basicColor = new QPalette();
    basicColor->setColor(QPalette::Base, QColor(230, 230, 250));

    for(count = 0; count < 81; count++){                             //設定九宮格初始值
        sudoku[count/9][count%9] = new QLineEdit(this);
        sudoku[count/9][count%9]->setAlignment(Qt::AlignCenter);
        sudoku[count/9][count%9]->setGeometry(30+30*(count%9),40+30*(count/9),30,30);
    }
    SetBackground();

    sudokuQuestion = new QFile(":/Question/su_question.txt");      //從檔案中選擇數讀題目
    SetSudokuFcn();

    RandomNumber(a);                                                //random 數字隨機
    RandomUpDown();                                                 //random 上下對稱交換
    RandomLeftRight();                                              //random 左右對稱交換
    LetterToNumber(a);                                              //英文字母轉隨機數字

    for(count = 0; count < 81; count++){                            //設置數獨初盤
        if(num[count/9][count%9] != "0"){
            sudoku[count/9][count%9]->setText(num[count/9][count%9]);
            sudoku[count/9][count%9]->setReadOnly(true);
            sudoku[count/9][count%9]->setStyleSheet("font-weight:bold;"
                                                    "color:black;"
                                                    "font-size: 15px;");
        }
        else
            sudoku[count/9][count%9]->setStyleSheet("color:SteelBlue ; "
                                                    "font-weight:bold;"
                                                    "font-size: 15px;");
    }

    for(count = 0; count < 81; count++){
       connect(sudoku[count/9][count%9], SIGNAL(editingFinished()),     //確認輸入的數字是否正確
                this, SLOT(CheckValueCorrect()));
       connect(this, SIGNAL(InputError()),
                this, SLOT(InputErrorMessenge()));
       connect(this, SIGNAL(InputCorrect()),
               this, SLOT(InputCorrectMessage()));
    }

    connect(finishButton, SIGNAL(clicked(bool)),                       //各種button的connect設定
            this, SLOT(CheckSudoku()));
    connect(resetButton, SIGNAL(clicked(bool)),
            this, SLOT(ResetSudoku()));
    connect(gobackButton, SIGNAL(clicked(bool)),
            this, SLOT(GoBackFcn()));
    connect(hintButton, SIGNAL(clicked(bool)),
            this, SLOT(HintFcn()));
    connect(myTimer, SIGNAL(timeout()),
            this, SLOT(CountDownTimeFcn()));
}

void PlaySudokuWindow::InitiallizeButton(){
    QPixmap finishFlag(":/Image/finish_flag.png");                  //finish button
    finishFlag = finishFlag.scaled(50, 50);
    QIcon finishIcon(finishFlag);
    finishButton->setVisible(true);
    finishButton->setGeometry(50, 310, 60, 60);
    finishButton->setIcon(finishIcon);
    finishButton->setIconSize(finishFlag.rect().size());

    QPixmap resetImg(":/Image/reset.png");                          //reset button
    resetImg = resetImg.scaled(50, 50);
    QIcon resetIcon(resetImg);
    resetButton->setVisible(true);
    resetButton->setGeometry(110, 310, 60, 60);
    resetButton->setIcon(resetIcon);
    resetButton->setIconSize(resetImg.rect().size());

    QPixmap gobackImg(":/Image/home.png");                          //goback button
    gobackImg = gobackImg.scaled(50, 50);
    QIcon gobackIcon(gobackImg);
    gobackButton->setVisible(true);
    gobackButton->setGeometry(170, 310, 60, 60);
    gobackButton->setIcon(gobackIcon);
    gobackButton->setIconSize(gobackImg.rect().size());

    QPixmap hintImg(":/Image/hint.png");                          //goback button
    hintImg = hintImg.scaled(45, 45);
    QIcon hintIcon(hintImg);
    hintButton->setVisible(true);
    hintButton->setGeometry(230, 310, 60, 60);
    hintButton->setIcon(hintIcon);
    hintButton->setIconSize(hintImg.rect().size());

}

void PlaySudokuWindow::InitiallizeErrorMessage(){
    errorMessage->setGeometry(30, 10, 200, 30);
    errorMessage->setStyleSheet("font-family:fantasy;");
    errorMessage->setText("");
}

void PlaySudokuWindow::SetSudokuFcn(){
    int count, x;
    QString str, whichSudoku;
    QStringList temp;

    srand(time(NULL));                                               //選擇題庫中的數讀題目
    int questionNumber = rand()%puzzlesNum + 1;
    QString sudoNum = QString::number(questionNumber) + "\n";

    if(sudokuQuestion->exists())                                    //開始讀數讀題目檔
        sudokuQuestion->open(QIODevice::ReadOnly);

    if(difficulty == 1)
        whichSudoku = "easy\n";
    else if(difficulty == 2)
        whichSudoku = "middle\n";
    else
        whichSudoku = "hard\n";

    str = sudokuQuestion->readLine();
    while(str != whichSudoku){                                       //找到要讀哪個數獨
        str = sudokuQuestion->readLine();
    }
    while(str != sudoNum)
        str = sudokuQuestion->readLine();
    for(count = 0; count < 9; count++){                             //從檔案讀入預先設計好的數獨
        str = sudokuQuestion->readLine();
        temp = str.split(' ');
        for(x = 0; x < 9; x ++)
            num[count][x] = temp.at(x);
    }

}

void PlaySudokuWindow ::SetBackground(){
    int count;
    for(count = 0; count < 81; count++){
        if(((count/9 > 2 && count/9 < 6 )&& (count%9 < 3 || count%9 >5)) ||
                ((count%9 > 2 && count%9 < 6 )&& (count/9 <3 || count/9 >5)))
            sudoku[count/9][count%9]->setPalette(*basicColor);
    }
}

void PlaySudokuWindow ::RandomNumber(int a[]){
    int count, x;
    for(count = 0; count < 9; count++){
         a[count] = rand()%9 + 1;
         for(x = 0; x < count; x++){
             if(a[count] == a[x]){
                 count--;
                 break;
             }
         }
     }
}

void PlaySudokuWindow ::LetterToNumber(int a[]){
    QString aa[9];
    int count;

    for(count = 0; count < 9; count++)
        aa[count] = QString::number(a[count]);

    for(count = 0; count < 81; count++){
         if(num[count/9][count%9] == "a")  num[count/9][count%9] = aa[0];
         if(num[count/9][count%9] == "b")  num[count/9][count%9] = aa[1];
         if(num[count/9][count%9] == "c")  num[count/9][count%9] = aa[2];
         if(num[count/9][count%9] == "d")  num[count/9][count%9] = aa[3];
         if(num[count/9][count%9] == "e")  num[count/9][count%9] = aa[4];
         if(num[count/9][count%9] == "f")  num[count/9][count%9] = aa[5];
         if(num[count/9][count%9] == "g")  num[count/9][count%9] = aa[6];
         if(num[count/9][count%9] == "h")  num[count/9][count%9] = aa[7];
         if(num[count/9][count%9] == "i")  num[count/9][count%9] = aa[8];
         if(num[count/9][count%9] == "a\n")  num[count/9][count%9] = aa[0];
         if(num[count/9][count%9] == "b\n")  num[count/9][count%9] = aa[1];
         if(num[count/9][count%9] == "c\n")  num[count/9][count%9] = aa[2];
         if(num[count/9][count%9] == "d\n")  num[count/9][count%9] = aa[3];
         if(num[count/9][count%9] == "e\n")  num[count/9][count%9] = aa[4];
         if(num[count/9][count%9] == "f\n")  num[count/9][count%9] = aa[5];
         if(num[count/9][count%9] == "g\n")  num[count/9][count%9] = aa[6];
         if(num[count/9][count%9] == "h\n")  num[count/9][count%9] = aa[7];
         if(num[count/9][count%9] == "i\n")  num[count/9][count%9] = aa[8];
         if(num[count/9][count%9] == "0\n")  num[count/9][count%9] = "0";
     }
}

void PlaySudokuWindow :: RandomUpDown(){
    QString tempNum[9][9];
    int count;

    if(rand()%2 == 0){
        for(count = 0; count < 81; ++count)
            tempNum[count/9][count%9] = num[count/9][count%9];
        for(count = 0; count < 81; ++count){
            num[count/9][count%9] = tempNum[8-count/9][count%9];
        }
    }
}

void PlaySudokuWindow :: RandomLeftRight(){
    QString tempNum[9][9];
    int count;

    if(rand()%2 == 0){                              //random 左右對稱交換
        for(count = 0; count < 81; ++count)
            tempNum[count/9][count%9] = num[count/9][count%9];
        for(count = 0; count < 81; ++count){
            num[count/9][count%9] = tempNum[count/9][8-count%9];
        }
    }
}

void PlaySudokuWindow::ResetSudoku(){
    int count;
    for(count = 0; count < 81; count++){
        if(sudoku[count/9][count%9]->isReadOnly() != true){
            sudoku[count/9][count%9]->setText("");
            sudoku[count/9][count%9]->setStyleSheet("color:SteelBlue ; "
                                                    "font-weight:bold;"
                                                    "font-size: 15px;");
        }
    }
    InitiallizeErrorMessage();
    InitiallizeButton();
    myTimer->start(1000);
    elapsedTime = sudokuLevel->elapsedTime[difficulty];
}

void PlaySudokuWindow::CheckValueCorrect(){
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
            sudoku[count/9][count%9]->setText("");
            flag = 1;
            break;
        }
    }

    if(flag == 0)
        emit InputCorrect();
}

void PlaySudokuWindow::InputCorrectMessage(){
    errorMessage->setText("");
}

void PlaySudokuWindow::InputErrorMessenge()
{
    errorMessage->setText("please input number 1~9");
}

void PlaySudokuWindow::GoBackFcn(){
    ChooseWindow *chooseWindow;
    chooseWindow = new ChooseWindow;
    chooseWindow->show();
    this->close();
}

void PlaySudokuWindow::CountDownTimeFcn(){
    --elapsedTime;
    QString text = QString::number(elapsedTime/60)+":"+QString::number(elapsedTime%60);
    remainingTime->display(text);
    if (elapsedTime == 0)
        TimesUpFcn();
}

void PlaySudokuWindow::TimesUpFcn(){
    QPixmap correctImg(":/Image/timesUp.png");                  //finish button
    correctImg = correctImg.scaled(100, 100);
    finalMessage->setText("Time's up!");
    finalMessage->setIconPixmap(correctImg);
    finalMessage->show();
    finishButton->setVisible(false);
    hintButton->setVisible(false);
    resetButton->setGeometry(100,310,60,60);
    gobackButton->setGeometry(160,310,60,60);
    myTimer->start(100000000);

}

void PlaySudokuWindow::HintFcn(){
    int count;
    int num = 0;
    int x;
    bool sudokuAns;
    SolveSudokuFunction S;
    QString sudokuNum;

    for(count = 0; count < 81; ++count){                                            //解出此題數獨的答案
        if(sudoku[count/9][count%9]->isReadOnly())
            S.SetElement(count, sudoku[count/9][count%9]->text().toInt());
        else
            S.SetElement(count, 0);
    }
    sudokuAns = S.SolveSudoku(0,S,0);
    for(count = 0; count <81; count++){
        sudokuNum = QString::number(S.map[count/9][count%9]);
        if(sudoku[count/9][count%9]->text() != sudokuNum)
            num++;
     }
    x = rand()%num +1;
    num = 0;
    for(count = 0; count <81; count++){
        if(sudoku[count/9][count%9]->text() == "")
            ++num;
        if(num >= x)
            break;
    }
    sudoku[count/9][count%9]->setText(QString::number(S.map[count/9][count%9]));
    sudoku[count/9][count%9]->setStyleSheet("color:SteelBlue ; "
                                            "font-weight:bold;"
                                            "font-size: 15px;");

}

void PlaySudokuWindow::WinTheGameFcn(){
    QPixmap correctImg(":/Image/correct.png");                  //finish button
    correctImg = correctImg.scaled(100, 100);
    finalMessage->setText("You win the game!");
    finalMessage->setIconPixmap(correctImg);
    finalMessage->show();
}

void PlaySudokuWindow::LostTheGameFcn(){
    QPixmap correctImg(":/Image/wrong.png");                  //finish button
    correctImg = correctImg.scaled(100, 100);
    finalMessage->setText("You lost the game!");
    finalMessage->setIconPixmap(correctImg);
    finalMessage->show();
}

void PlaySudokuWindow::CheckSudoku()
{
    qDebug() << elapsedTime;
    int count;
    int number;
    SolveSudokuFunction S;
    bool sudokuAns;
    QString sudokuNum;

    for(count = 0; count < 81; count++){                                               //將數獨的值存到map[][]中
        if(sudoku[count/9][count%9]->text() == NULL)
            number = 0;
        else
            number = sudoku[count/9][count%9]->text().toInt();
        S.SetElement(count, number);
    }

    sudokuAns = S.SudokuCorrect();

    if(sudokuAns == true)
        WinTheGameFcn();
    else{
        for(count = 0; count < 81; ++count){                                            //解出此題數獨的答案
            if(sudoku[count/9][count%9]->isReadOnly())
                S.SetElement(count, sudoku[count/9][count%9]->text().toInt());
            else
                S.SetElement(count, 0);
        }
        sudokuAns = S.SolveSudoku(0,S,0);
        for(count = 0; count <81; count++){
            sudokuNum = QString::number(S.map[count/9][count%9]);
            if(sudoku[count/9][count%9]->text() != sudokuNum){
                sudoku[count/9][count%9]->setText(sudokuNum);
                sudoku[count/9][count%9]->setStyleSheet("color:red ; "
                                                        "font-weight:bold;"
                                                        "font-size: 15px;");
            }
         }
         LostTheGameFcn();
    }
    finishButton->setVisible(false);
    hintButton->setVisible(false);
    resetButton->setGeometry(100,310,60,60);
    gobackButton->setGeometry(160,310,60,60);
    myTimer->start(10000000);
}
