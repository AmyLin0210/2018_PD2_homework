#ifndef SOLVESUDOKUFUNCTION_H
#define SOLVESUDOKUFUNCTION_H

#include <QApplication>
#include <iostream>

using namespace std;

class SolveSudokuFunction
{

public:
    SolveSudokuFunction();
    void SetElement(int index, int value);
    void CoutElement();
    bool SolveSudoku(int pos, SolveSudokuFunction &S, int flag);
    bool SudokuCorrect();
    int  FirstZero(int pos);
    bool FillInNumber(int pos, int num);
    bool InitialSudokuCheck();
    int map[9][9];

};

#endif // SOLVESUDOKUFUNCTION_H
