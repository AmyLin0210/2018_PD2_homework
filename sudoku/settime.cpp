#include "settime.h"

SetTime::SetTime(difficultyClass *changeTime)
{
    difficultyInformation = changeTime;
    int count;
    for(count = 0; count <3; count++)
    {
        elapsedTime[count] = difficultyInformation->elapsedTime[count+1];

        difficultyLable[count] = new QLabel(this);
        difficultyLable[count]->setGeometry(30, 30+count*40, 30, 30);

        difficultyMin[count] = new QLineEdit(this);
        difficultyMin[count]->setGeometry(70, 30+count*40, 30, 30);
        difficultyMin[count]->setText(QString::number(elapsedTime[count]/60));
        difficultyMin[count]->setAlignment(Qt::AlignCenter);

        minLabel[count] = new QLabel(this);
        minLabel[count]->setGeometry(105, 30+count*40, 20, 30);
        minLabel[count]->setText("分");

        difficultySec[count] = new QLineEdit(this);
        difficultySec[count]->setGeometry(130, 30+count*40, 30, 30);
        difficultySec[count]->setText(QString::number(elapsedTime[count]%60));
        difficultySec[count]->setAlignment(Qt::AlignCenter);

        secLabel[count] = new QLabel(this);
        secLabel[count]->setGeometry(165, 30+count*40, 30, 30);
        secLabel[count]->setText("秒");
    }

    difficultyLable[0]->setText("easy");
    difficultyLable[1]->setText("middle");
    difficultyLable[2]->setText("hard");

    finishButton = new QPushButton(this);
    finishButton->setGeometry(70, 165, 80, 40);
    finishButton->setText("store");

    connect(finishButton, SIGNAL(clicked(bool)),
            this, SLOT(StoreFcn()));

}

void SetTime::StoreFcn(){
    int count;
    int totalTime = 0;
    for(count = 0; count < 3; count++){
        totalTime += difficultyMin[count]->text().toInt()*60 + difficultySec[count]->text().toInt();
        difficultyInformation->elapsedTime[count+1] = totalTime;
    }
    this->close();
}




