#ifndef START_H
#define START_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QIcon>
#include <QPalette>

class start : public QWidget
{
    Q_OBJECT

public:
    start();

private:
    QPalette *backgroundColor;
    QPushButton *startButton;
    QLabel *startLable;

};

#endif // START_H
