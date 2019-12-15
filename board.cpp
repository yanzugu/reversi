#include "board.h"
#include "Constants.h"
#include <iostream>

using namespace std;
pair<int, int> _way[8] =
{
    {-1, -1}, {-1, 0}, {-1, 1},
    {0, -1}, {0, 1}, {1, -1},
    {1, 0}, {1, 1}
};
void dfsCVP(int player,int x, int y, pair<int, int> way, int c, Board &arg, int &vc); // checkValidPoint
void dfsRB(int player, int x, int y, pair<int, int> way, int c, Board &arg);        // reverseBoard

Board::Board() {initialBoard();}
void Board::setPointValue(int x, int y, int value)
{
    this->board[x][y] = value;
}
int Board::getPointValue(int x, int y)
{
    return this->board[x][y];
}
void Board::initialBoard()         //-1, 0, 1 -> White, empty, Black ; 2, 3 -> valid, outside
{
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
        {
            if (i == 0 || j == 0 || i == 9 || j == 9)
                setPointValue(i, j, OUTSIDE);
            else
                setPointValue(i, j, EMPTY);
        }
    setPointValue(4,4,WHITE);
    setPointValue(5,5,WHITE);
    setPointValue(4,5,BLACK);
    setPointValue(5,4,BLACK);
}
void Board::printBoard()
{
    cout << "    ";
    for(int i = 0; i < 8; i++)
        cout << char(i + 'a') << "   ";
    cout << endl ;
    cout <<  "  ┌";
    for(int i = 0; i < 7; i++)
        cout << "───┬";
    cout << "───┐" << endl;
    for(int i = 1; i <= 8; i++)
    {
        cout << i <<" ";
        for(int j = 1; j <= 8; j++)
        {
            cout << "│";
            if(getPointValue(i,j) == VALID)
                cout << " 。" ;
            else if(getPointValue(i,j) == BLACK)
                cout << " ○" ;
            else if(getPointValue(i,j) == WHITE)
                cout << " ●" ;
            else
                cout << "   ";
        }
        cout << "│";
        cout << endl;
        if(i != 8)
        {
            cout << "  ├";
            for(int j = 0; j < 7; j++)
                cout << "───┼";
            cout << "───┤" << endl;
        }
    }
    cout <<  "  └";
    for(int i = 0; i < 7; i++)
        cout << "───┴";
    cout << "───┘" << endl;
}
bool Board::checkValidPoint(int player)
{
    int vc = 0;
    for (int i = 1; i <= 8; i++)
    {
        for (int j = 1; j <= 8; j++)
        {
            if (getPointValue(i, j) != player)
                continue;
            for (int idx = 0; idx < 8; idx++)
                dfsCVP(player, i, j, _way[idx], 0, *this, vc);
        }
    }
    return vc > 0;
}
void Board::reverseBoard(int x, int y, int player)
{
    setPointValue(x, y, player);
    for (int i = 1; i <= 8; i++)
        for (int j = 1; j <= 8; j++)
            if(getPointValue(i, j) == VALID)
                setPointValue(i, j, EMPTY);
    for (int i = 0; i < 8; i++)
        dfsRB(player, x, y, _way[i], 0, *this);
}
int Board::finalCheckBoard(int player)
{
    int tmp = 0;
    for (int i = 1; i <= 8; i++)
        for (int j = 1; j <= 8; j++)
            if (getPointValue(i, j) == player)
                tmp++;
    return tmp;
}
void dfsRB(int player, int x, int y, pair<int, int> way, int c, Board &arg)
{
    if(arg.getPointValue(x+way.first, y+way.second) == -player)
        dfsRB(player, x+way.first, y+way.second, way, c+1, arg);
    else if(arg.getPointValue(x+way.first, y+way.second) == player && c > 0)
    {
        for (int i = 0; i <= 8; i++)
        {
            if (arg.getPointValue(x-way.first*i, y-way.second*i) == player)
                break;
            arg.setPointValue(x-way.first*i, y-way.second*i, -arg.getPointValue(x-way.first*i, y-way.second*i));
        }
    }
    else
        return;
}
void dfsCVP(int player,int x, int y, pair<int, int> way, int c, Board &arg, int &vc)
{
    if (arg.getPointValue(x+way.first, y+way.second) == -player)
        dfsCVP(player, x+way.first, y+way.second, way, c+1, arg, vc);
    else if (arg.getPointValue(x+way.first, y+way.second) == EMPTY && c > 0)
    {
        arg.setPointValue(x+way.first, y+way.second, VALID);
        vc++;
        return;
    }
    else
        return;
}
