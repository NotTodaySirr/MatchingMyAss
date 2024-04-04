#include"Struct.h"
#include"Board.h"
#include<conio.h>
#include<Windows.h>
#include"Mode.h"
#include"Checking.h"
#include<fstream>

using namespace std;


void getPlayerInfo(player& p)
{
	gotoXY(45, 13);
	cout << "enter your name: ";
	getline(cin, p.name);

	p.life = 3;
	p.point = 0;
   
}

void resetStatus(int& x1, int& y1, int& x2, int& y2, int& cnt)
{
    x1 = -1;
    y1 = -1;
    x2 = -1;
    y2 = -1;
    cnt = 0;
}

void displayStatus(player& p)
{
    for (int i = 0; i < 5; i++)
    {
        gotoXY(70, i);
        if (i == 0)
        {
            cout << "player's name: " << p.name;
        }
        if (i == 1)
        {
            cout << "player's point: " << p.point;
        }
        if (i == 2)
        {
            cout << "player's life: " << p.life;
        }
        if (i == 3)
        {
            cout << "player's help: " << p.help;
        }
        if (i == 4)
        {
            cout << "player's stage: " << p.stage;
        }
    }
    gotoXY(70, 5);
    cout << "press h to suggest move";
    gotoXY(70, 6);
    cout << "press s to shuffle board";
    gotoXY(70, 15);
    cout << "PRESS ESC TO EXIT";
}

//source from PhVanMin
//https://github.com/PhVanMin/Pikachuuu/blob/master/Utility.cpp#L112
void displayResults(bool win) {
    if (win) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
        gotoXY(50, 10);
        cout << "__  ______  __  __  _      ______  _  __";
        gotoXY(50, 11);
        cout << "\\ \\/ / __ \\/ / / / | | /| / / __ \\/ |/ /";
        gotoXY(50, 12);
        cout << " \\  / /_/ / /_/ /  | |/ |/ / /_/ /    /";
        gotoXY(50, 13);
        cout << " /_/\\____/\\____/   |__/|__/\\____/_/|_/";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        Sleep(2000);
    }
    else {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        gotoXY(50, 10);
        cout << "__  ______  __  __  __   ____  ________";
        gotoXY(50, 11);
        cout << "\\ \\/ / __ \\/ / / / / /  / __ \\/ __/ __/";
        gotoXY(50, 12);
        cout << " \\  / /_/ / /_/ / / /__/ /_/ /\\ \\/ _/";
        gotoXY(50, 13);
        cout << " /_/\\____/\\____/ /____/\\____/___/___/";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        Sleep(2000);
    }
}

bool Is_Continue(char& NextGame)
{
    bool is_Loop = true;
    while (is_Loop)
    {
        gotoXY(50, 16);
        cout << "Do you want to advance to next game? Y/N: ";
        cin >> NextGame;

        if (NextGame == 'y' || NextGame == 'Y')
        {
            return true;
        }

        else if (NextGame == 'n' || NextGame == 'N')
        {
            return false;
        }
        else cout << "Wrong syntax, try again" << endl;
    }
}


void writeLeaderBoard(player p, string filename)
{
    ofstream f;
    f.open(filename, ios::app);
    if (!f.is_open())
    {
        cout << "can't open the file :(( " << endl;
        return;
    }

    if (f.eof())
    {
        f << p.name << " " << p.point;
    }
    else
        f << endl << p.name << " " << p.point;

    f.close();
}

void sortPlayer(player p[100], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n;j++)
        {
            if (p[i].point < p[j].point)
            {
                swap(p[i].point, p[j].point);
                string tmp;
                tmp = p[i].name;
                p[i].name = p[j].name;
                p[j].name = tmp;
            }
        }
    }
}


void drawLB(player p[100], int n)
{
    drawBox(50, 0, 30, 3);
    string s = { "LEADERBOARD" };
    gotoXY(60, 1);
    stringColor(s, 3);

    gotoXY(30, 6);
    s = { "NAME" };
    stringColor(s, 4);

    gotoXY(100, 6);
    s = { "POINT" };
    stringColor(s, 2);

    for (int i = 0; i < n; i++)
    {
        gotoXY(30, 6 + (2 * i + 1));
        for (int j = 0; j < 75; j++)
        {
            cout << "=";
        }
        gotoXY(30, 6 + (2 * i + 2));
        cout << p[i].name;

        gotoXY(100, 6 + (2 * i + 2));
        cout << p[i].point;

    }
}


void DisplayLB(string filename)
{
    system("cls");
    ifstream f;
    f.open(filename);

    if (!f.is_open())
    {
        cout << "hk tim thay " << endl;
        return;
    }

    if (f.eof())
    {
        cout << "hien tai khong co ai ca :((" << endl;
        return;
    }

    player p[100];

    int i = 0;

    while (!f.eof())
    {
        f >> p[i].name >> p[i].point;
        i++;
    }

    int number = i;

    sortPlayer(p, number);

    drawLB(p, number);
    bool isRunning = true;

    f.close();
}

void stringColor(string s, int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
    cout << s;
    SetConsoleTextAttribute(hConsole, 7);
}

void suggestMove(char** board, int width, int height) {
    for (int x1 = 0; x1 < height; ++x1) {
        for (int y1 = 0; y1 < width; ++y1) {
            if (board[x1][y1] == ' ') continue; // Skip empty tiles

            for (int x2 = 0; x2 < height; ++x2) {
                for (int y2 = 0; y2 < width; ++y2) {
                    if ((x1 == x2 && y1 == y2) || board[x2][y2] == ' ') continue; // Skip the same tile and empty tiles
                    if (board[x1][y1] == board[x2][y2]) {
                        // Check if a valid path exists between the two matching tiles
                        if (checkIPattern(board, x1, x2, y1, y2) ||
                            checkLPattern(board, x1, x2, y1, y2) ||
                            checkZPattern(board, x1, x2, y1, y2) ||
                            checkUPattern(board, x1, x2, y1, y2) ||
                            (checkBlankRow(board, y1, y2, x1) && checkBlankColumn(board, x1, x2, y2) && checkIPattern(board, x1, y2, x2, y2)) ||
                            (checkBlankColumn(board, x1, x2, y1) && checkBlankRow(board, y1, y2, x2) && checkIPattern(board, x2, y1, x2, y2))) {
                            gotoXY(70, 10);
                            cout << "Move suggestion:(" << x1 << "," << y1 << ") -> (" << x2 << "," << y2 << ")" << endl;
                            return;
                        }
                    }
                }
            }
        }
    }
    gotoXY(70, 15);
    cout << "No moves found." << endl;
}
