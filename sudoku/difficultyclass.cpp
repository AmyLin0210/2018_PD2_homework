#include "difficultyclass.h"

difficultyClass::difficultyClass(){
    difficulty[1] = 1;
    difficulty[2] = 2;
    difficulty[3] = 3;
    elapsedTime[1] = 10*60;
    elapsedTime[2] = 15*60;
    elapsedTime[3] = 20*60;
    puzzleNum[1] = 4;
    puzzleNum[2] = 4;
    puzzleNum[3] = 4;
}

int difficultyClass::difficulty[4];
int difficultyClass::elapsedTime[4];
int difficultyClass::puzzleNum[4];

