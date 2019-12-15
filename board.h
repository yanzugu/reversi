#ifndef BOARD_H
#define BOARD_H

class Board
{
public:
    Board();
    void reverseBoard(int,int,int);
    bool checkValidPoint(int);
    void initialBoard();
    void printBoard();
    void setPointValue(int,int,int);
    int getPointValue(int,int);
    int finalCheckBoard(int);

private:
    int board[10][10];
};
#endif // BOARD_H
