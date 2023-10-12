#ifndef _CHESS_BOARD_H
#define _CHESS_BOARD_H
/*
 * File: ChessBoard.h
 * Author: Jared McKneely
 * Description: Header file for the ChessBoard class
 */

#include "BaseObject.h"
#include "RectangularPrism.h"

class ChessBoard : public BaseObject {
  public:
    ChessBoard();
    ~ChessBoard();
    void draw();
  protected:
    RectangularPrism *blackSquare1;
    RectangularPrism *blackSquare2;
    RectangularPrism *whiteSquare1;
    RectangularPrism *whiteSquare2;
    float blackSquareR = 0.13;
    float blackSquareG = 0.13;
    float blackSquareB = 0.13;
    float whiteSquareR = 0.81;
    float whiteSquareG = 0.81;
    float whiteSquareB = 0.81;
};

#endif
