#include "Mode.h"
#include "Checking.h"
#include <conio.h>
#include <iostream>
#include"Struct.h"
#include"Board.h"
#include<Windows.h>
#include"Sound.h"
using namespace std;

void GamePlay(char** a, player& p, int px, int py, int xMax, int yMax, int x1, int y1, int x2, int y2, int cnt, char& command)
{
    bool is_next = true;
    while (is_next) {
        a = generateBoard();
        do {
            createBoard(a, rows, cols, px, py, x1, y1, x2, y2);
            displayStatus(p);
            command = _getch();

            if (int(command) == 13)
            {
                if (cnt == 0 && a[px][py] != ' ')
                {
                    x1 = px;
                    y1 = py;
                    cnt++;

                }

                if (cnt == 1 && a[px][py] != ' ' && (px != x1 || py != y1))
                {
                    x2 = px;
                    y2 = py;
                    cnt++;
                }
            }

            if (cnt == 2)
            {
                //check patterns
                if (checkIPattern(a, x1, x2, y1, y2) && a[x1][y1] == a[x2][y2])
                {
                    MatchingSound();
                    deleteCell(a, a[x1][y1], a[x2][y2]);
                    resetStatus(x1, y1, x2, y2, cnt);
                    p.point += 10;

                }

                else if (checkLPattern(a, x1, x2, y1, y2) && a[x1][y1] == a[x2][y2])
                {
                    MatchingSound();
                    deleteCell(a, a[x1][y1], a[x2][y2]);
                    resetStatus(x1, y1, x2, y2, cnt);
                    p.point += 10;
                }

                else if (checkUPattern(a, x1, x2, y1, y2) && a[x1][y1] == a[x2][y2])
                {
                    MatchingSound();
                    deleteCell(a, a[x1][y1], a[x2][y2]);
                    resetStatus(x1, y1, x2, y2, cnt);
                    p.point += 10;

                }

                else if (checkZPattern(a, x1, x2, y1, y2) && a[x1][y1] == a[x2][y2])
                {
                    MatchingSound();
                    deleteCell(a, a[x1][y1], a[x2][y2]);
                    resetStatus(x1, y1, x2, y2, cnt);
                    p.point += 10;
                }

                else
                {
                    IncorrectSound();
                    p.life--;
                    resetStatus(x1, y1, x2, y2, cnt);
                }
            }
            if (int(command) == 27)
            {
                is_next = false;
                break;
            }


            if (command == 72 || command == 75 || command == 77 || command == 80)
            {
                Move(5, 6, px, py, command);
            }

            else if ((command == 'h' || command == 'H') && p.help > 0)
            {
                suggestMove(a, 8, 7);
                gotoXY(70, 15);
                Sleep(2000);
                p.help--;
            }
            else if (command == 'S' || command == 's')
            {
 SHUFFLE:       shuffleNonEmptyCells(a, rows, cols);
            }

            //if stage = 1, play normal mode
            //if stage = 2, play mode that delete blank downward
            if (p.stage % 5 == 2)
            {
                deleteBlankDownwards(a);
            }

            //if stage = 3, play mode that delete blank upward
            else if (p.stage % 5 == 3)
            {
                deleteBlankUpwards(a);
            }

            //if stage = 4, play mode that delete blank to ri   ght
            else if (p.stage % 5 == 4)
            {
                deleteBlanktoRight(a);
            }

            //if stage = 5, play mode that delete blank to left
            else if (p.stage % 5 == 0)
            {
                deleteBlanktoLeft(a);
            }


        } while (checkPairsLeft(a, 6, 7) && checkValidPairs(a, 6, 7)  && p.life != 0);

        if (p.life <= 0)
        {
            system("cls");
            displayResults(0);
            LosingSound();
            writeLeaderBoard(p, "LeaderBoard.txt");
            is_next = false;
            break;
        }

        if (!checkPairsLeft(a, 6, 7))
        {
            system("cls");
            displayResults(1);
            WinningSound();
            cout << endl;
            if (Is_Continue(command))
            {
                p.stage++;
            }
            else
            {
                writeLeaderBoard(p, "LeaderBoard");
                break;
            }
        }

        deleteBoard(a, rows, cols);
    }
    deleteBoard(a, rows, cols);
    system("cls");
    gotoXY(50, 19);
    cout << "Heading back to menu, please wait...";
    Sleep(2000);
}