#include "solvesudokufunction.h"
#include <iostream>
#include <QDebug>

using namespace std;

SolveSudokuFunction::SolveSudokuFunction()
{
}


void SolveSudokuFunction::SetElement(int index, int value){
    map[index/9][index%9] = value;
}

void SolveSudokuFunction::CoutElement(){
    int x, y;
    for(y = 0; y < 9; y++){
        for(x = 0; x < 9; x++)
           cout << map[y][x] << " ";
            cout << endl;
    }
}

int SolveSudokuFunction::FirstZero(int pos){
   int count;
   for(count = pos; count < 81; count++){
       if(map[count/9][count%9] == 0)
           return count;
   }
   return -1;
}

bool SolveSudokuFunction::SudokuCorrect(){
    int a, b, c, d;

    for(a = 0; a < 9; a++){
        for(b = 0; b < 9; b++)
            if(map[a][b] <= 0 || map[a][b] > 9)
                return false;
    }

    for(a = 0; a < 9; a++){                    //check if row and colume value correct
        for(b = 0; b < 9; b++){
            for(c = b+1; c < 9; c++){
                if(map[a][b] == map[a][c] || map[b][a] == map[c][a])
                    return false;
            }
        }
    }

    for(a = 0; a < 3; a++){                   //check if the 3*3 zome correct
        for(b = 0; b < 3; b++){
            for(c = 0; c < 9; c++){
                for(d = c+1; d < 9; d++){
                    if(map[a*3+c%3][b*3+c/3] == map[a*3+d%3][b*3+d/3])
                        return false;
                }
            }
        }
    }
    return true;
}

bool SolveSudokuFunction::FillInNumber(int pos, int num){
    int a = pos/9;
    int b = pos%9;
    int c = a/3;
    int d = b/3;
    int count;

    for(count = 0; count < 9; count++){
        if(map[a][count] == num) return false;
        if(map[count][b] == num) return false;
        if(map[c*3+count/3][d*3+count%3] == num) return false;
    }
    return true;
}

bool SolveSudokuFunction::InitialSudokuCheck(){
    int a, b, c, d;

    for(a = 0; a < 9; a++){                    //check if colume value correct
        for(b = 0; b < 9; b++){
            for(c = b+1; c < 9; c++){
                if(map[a][b] != 0 && map[a][c] != 0){
                    if(map[a][b] == map[a][c]){
                        return false;
                    }
                }
            }
        }
    }

    for(a = 0; a < 9; a++){                    //check if row value correct
        for(b = 0; b < 9; b++){
            for(c = b+1; c < 9; c++){
                if(map[b][a] != 0 && map[c][a] != 0){
                    if(map[b][a] == map[c][a]){
                        return false;
                    }
                }
            }
        }
    }


    for(a = 0; a < 3; a++){                   //check if the 3*3 zome correct
        for(b = 0; b < 3; b++){
            for(c = 0; c < 9; c++){
                for(d = c+1; d < 9; d++){
                    if(map[a*3+c%3][b*3+c/3] != 0 &&  map[a*3+d%3][b*3+d/3] != 0){
                        if(map[a*3+c%3][b*3+c/3] == map[a*3+d%3][b*3+d/3])
                            return false;
                    }
                }
            }
        }
    }
    return true;
}

bool SolveSudokuFunction::SolveSudoku(int pos, SolveSudokuFunction &S, int flag){
    int firstZero;
    int count;

    //check if the initial sudoku has the same value in the same row, colume, 3*3zoom
    //only check at the beginning
    // 0:uncheck  1:correct -1:false
    if(flag == 0){
        if(S.InitialSudokuCheck())
            flag = 1;
        else flag = -1;
    }
    if(flag == -1)
        return false;

    firstZero = S.FirstZero(pos);

    if(firstZero == -1){                 //finish setting the value
        if(S.SudokuCorrect())
            return true;
        else
            return false;
    }
    else{
        for(count = 1; count <= 9; count++){
            S.SetElement(firstZero, count);
            if(S.InitialSudokuCheck()){
                if(SolveSudoku(firstZero, S, 1))
                    return true;
            }
        }
        S.SetElement(firstZero, 0);
        return false;
    }
}



