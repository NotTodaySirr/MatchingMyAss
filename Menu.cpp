#include<iostream>
#include<conio.h>
#include "Library.h"

using namespace std;

void LeaderBoardMenu()
{
    bool is_Running = true;
    char cmd;

    while (is_Running)
    {
        DisplayLB("LeaderBoard.txt");
        cmd = _getch();

        if (cmd == 27)
        {
            is_Running = false;
        }
    }

    gotoXY(50, 25);
    cout << "back to main menu...";
    Sleep(1500);
}

void Menu()
{
    bool isRunning = true;
    int selectedOption = 0;

    while (isRunning) {
        // print menu
        system("cls");
        printMenu();

        drawBox(40, 18, 38, 5);


        gotoXY(53, 19);
        cout << (selectedOption == 0 ? "->" : "") << "PLAY" << endl;

        gotoXY(53, 20);
        cout << (selectedOption == 1 ? "->" : "") << "LEADERBOARD " << endl;
        
        gotoXY(53, 21);
        cout << (selectedOption == 2 ? "->" : "") << "EXIT" << endl;

        gotoXY(0, 24);
    
        char key = _getch();
        player p;
        int px = 1, py = 1, x1 = -1, x2 = -1, y1 = -1, y2 = -1;
        int cnt = 0, stage = 1;
        char gameCommand;
        char** board;
        // handle income
        switch (key) {
        case 72: // Up arrow

            selectedOption = (selectedOption - 1 + 3) % 3;
            break;

        case 80: // Down arrow

            selectedOption = (selectedOption + 1) % 3;
            break;

        case 13: // Enter

            // action on choice
            switch (selectedOption) {
            case 0:
                // Play game
                board = generateBoard();
                system("cls");
                getPlayerInfo(p);
                GamePlay(board, p, px, py, rows, cols, x1, y1, x2, y2, cnt, gameCommand);
                deleteBoard(board, rows, cols);
                break;

            case 1:

                // show leaderboard
                system("cls");
                LeaderBoardMenu();
                break;

            case 2:

                // exit game
                isRunning = false;
                break;
            }
            break;
        }
    }
END:    cout << endl;
}