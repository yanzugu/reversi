#include <bits/stdc++.h>
#include <windows.h>
#include "board.h"
#include "player.h"
#include "Constants.h"

using namespace std;

int main()
{
    Board board;
    Player player;
    char x, y;

    while(true)
    {
        bool haveVP = board.checkValidPoint(player.getPlayer());
        if (haveVP == false)
        {
            player.setPlayer(-player.getPlayer());
            haveVP = board.checkValidPoint(player.getPlayer());
            if (haveVP == false)
            {
                int bc = board.finalCheckBoard(BLACK);
                int wc = board.finalCheckBoard(WHITE);
                if (bc + wc != 64)
                {
                    if (bc > wc) bc = 64 - wc;
                    else wc = 64 - bc;
                }
                system("cls");
                board.printBoard();
                cout << "END!!" << endl;
                cout << bc << " : " << wc << endl;
                system("pause");
                board.initialBoard();
                player.setPlayer(BLACK);
                system("cls");
                continue;
            }
            if (player.getPlayer() == BLACK)
                cout << "\n\n\n\n\n        White Player Pass";
            else
                cout << "\n\n\n\n\n        Black Player Pass";
            Sleep(2000);
            system("cls");
        }
        board.printBoard();

        while (cin >> y >> x)
        {
            if (isdigit(x) && board.getPointValue(x-'0', y-'a'+1) == VALID)
                break;
            cout << "Please input a valid point" << endl;
            cin.ignore(100, '\n');
        }

        board.reverseBoard(x-'0', y-'a'+1, player.getPlayer());
        player.setPlayer(-player.getPlayer());
        Sleep(50);
        system("cls");
    }
}
