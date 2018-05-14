#ifndef SETTIME_H
#define SETTIME_H

#include <QWidget>
#include <QObject>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QString>
#include "difficultyclass.h"


class SetTime : public QWidget
{
    Q_OBJECT
public:
    SetTime(difficultyClass *changeTime);
    QPushButton *finishButton;
    QLineEdit *difficultyMin[3];
    QLineEdit *difficultySec[3];
    QLabel *difficultyLable[3];
    QLabel *minLabel[3];
    QLabel *secLabel[3];
    difficultyClass *difficultyInformation;
    int elapsedTime[3];

private slots:
    void StoreFcn();


};

#endif // SETTIME_H
