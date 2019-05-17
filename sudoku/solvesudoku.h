#ifndef SOLVESUDOKUWINDOW_H
#define SOLVESUDOKUWINDOW_H

#include <QObject>
#include <QWidget>
#include <QLineEdit>
#include <QString>
#include <QDebug>
#include <QMessageBox>
#include <QByteArray>
#include <QLabel>
#include <QPushButton>
#include <QDebug>
#include <QPalette>
#include <QColor>

class SolveSudokuWindow : public QWidget
{
    Q_OBJECT

public:
    SolveSudokuWindow();
    QLineEdit *sudoku[9][9];
    QLabel *errorMessage;
    QPushButton *finishButton;
    QPushButton *homeButton;
    QPalette *basicColor;
    QPalette *buttonColor;
    QPalette *backgroundColor;

private:
    void SetBackground();

signals:
    void InputError();
    void InputCorrect();

public slots:
    void CheckValueCorrect();
    void InputErrorMessenge();
    void InputCorrectMessage();
    void CheckSudoku();
    void HomeFcn();

};

#endif // SOLVESUDOKUWINDOW_H
