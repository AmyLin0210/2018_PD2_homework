#ifndef PLAYSUDOKUWINDOW_H
#define PLAYSUDOKUWINDOW_H

#include <QObject>
#include <QWidget>
#include <QFile>
#include <QLineEdit>
#include <QString>
#include <QDebug>
#include <QPushButton>
#include <QLabel>
#include <cstdlib>
#include <ctime>
#include <QMessageBox>
#include <QPalette>
#include <QColor>
#include <QPixmap>
#include <QIcon>
#include <QTimer>
#include <QTime>
#include <QLCDNumber>
#include "solvesudokufunction.h"
#include "difficultyclass.h"

class PlaySudokuWindow : public QWidget
{
    Q_OBJECT

public:
    difficultyClass *sudokuLevel;
    PlaySudokuWindow(difficultyClass *levelOfSudoku, int whichLevel);
    QLineEdit *sudoku[9][9];
    QFile *sudokuQuestion;
    QString num[9][9];
    QPushButton *finishButton;
    QPushButton *resetButton;
    QPushButton *gobackButton;
    QPushButton *hintButton;
    QLabel *errorMessage;

private:
    void RandomNumber(int a[]);
    void LetterToNumber(int a[]);
    void RandomUpDown();
    void RandomLeftRight();
    void SetBackground();
    void InitiallizeButton();
    void InitiallizeErrorMessage();
    void WinTheGameFcn();
    void LostTheGameFcn();
    void SetSudokuFcn();
    void TimesUpFcn();
    int elapsedTime;
    int difficulty;
    int puzzlesNum;
    QPalette *basicColor;
    QPalette *backgroundColor;
    QLCDNumber *remainingTime;
    QTimer * myTimer;
    QMessageBox *finalMessage;

signals:
    void InputError();
    void InputCorrect();

private slots:
    void ResetSudoku();
    void CheckValueCorrect();
    void InputErrorMessenge();
    void InputCorrectMessage();
    void CheckSudoku();
    void GoBackFcn();
    void CountDownTimeFcn();
    void HintFcn();
};

#endif // PLAYSUDOKUWINDOW_H
