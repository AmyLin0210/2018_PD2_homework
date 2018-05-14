#ifndef CHOOSEWINDOW_H
#define CHOOSEWINDOW_H

#include <QWidget>
#include <QPushButton>

class ChooseWindow : public QWidget
{
    Q_OBJECT


public:
    ChooseWindow();
private:
    QPushButton *startGameButton;
    QPushButton *solveSudokuButton;
};

#endif // CHOOSEWINDOW_H
