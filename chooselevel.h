#ifndef CHOOSELEVELWINDOW_H
#define CHOOSELEVELWINDOW_H

#include <QWidget>
#include <QObject>
#include <QPushButton>
#include <QString>
#include <QDebug>
#include <QPixmap>
#include <QIcon>
#include "difficultyclass.h"

class ChooseLevelWindow : public QWidget
{
    Q_OBJECT

public:
    ChooseLevelWindow();
    QPushButton *easyButton;
    QPushButton *middleButton;
    QPushButton *hardButton;
    QPushButton *setButton;
    difficultyClass sudokuLevel;

public slots:
    void EasyButtonClicked();
    void MiddleButtonClicked();
    void HardButtonClicked();
    void SetButtonClicked();

};

#endif // CHOOSELEVELWINDOW_H
