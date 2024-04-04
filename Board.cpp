#include "Board.h"
#include <cstdlib>
#include <iostream>
#include <Windows.h>
#include <time.h>
#include<conio.h>
#include "Checking.h"
#include "Struct.h"
#include<vector>
#include<algorithm>
#include<random>
using namespace std;

void setColour(int code) {
    HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(color, code);
}

//inspired by thuanphat611
//https://github.com/thuanphat611/Matching-Game/blob/master/Source/board.cpp

void createBoard(char** a, int m, int n, int px, int py, int x1, int y1, int x2, int y2) { // draw board to the console
	system("cls");
	cout << " ";
	for (int j = 1; j < n - 1; j++)
		cout << "    " << "   " << "    ";
	cout << endl << " ";
	for (int i = 1; i < m - 1; i++)
	{
		for (int j = 1; j < n - 1; j++)
		{
			if (a[i][j] != ' ')
			{
				charColor(a[i][j]);
				cout << " ------- ";
			}
			if (a[i][j] == ' ')
				cout << "         ";
		}
		cout << endl << " ";
		for (int j = 1; j < n - 1; j++)
		{
			if (a[i][j] != ' ')
			{
				if ((i == px && j == py) || (i == x1 && j == y1) || (i == x2 && j == y2))
				{
					charColor(a[i][j]);
					cout << "|";
					setColour(0x70);
					cout << "       ";
					charColor(a[i][j]);
					cout << "|";
				}
				else
				{
					charColor(a[i][j]);
					cout << "|       |";
				}
			}
			else
			{
				if ((i == px && j == py) || (i == x1 && j == y1) || (i == x2 && j == y2))
				{
					cout << " ";
					setColour(0x70);
					cout << "       ";
					setColour(0x07);
					cout << " ";
				}
				else
					cout << "         ";
			}
		}
		cout << endl;
		for (int j = 1; j < n - 1; j++)
		{
			if (j == 1)
			{
				setColour(0x07);
				cout << " ";
			}
			if (a[i][j] != ' ')
			{
				if ((i == px && j == py) || (i == x1 && j == y1) || (i == x2 && j == y2))
				{
					charColor(a[i][j]);
					cout << "|";
					setColour(0x70);
					cout << "   " << a[i][j] << "   ";
					charColor(a[i][j]);
					cout << "|";
				}
				else
				{
					charColor(a[i][j]);
					cout << "|   " << a[i][j] << "   |";
				}
			}
			else
			{
				if ((i == px && j == py) || (i == x1 && j == y1) || (i == x2 && j == y2))
				{
					cout << " ";
					setColour(0x70);
					cout << "       ";
					setColour(0x07);
					cout << " ";
				}
				else
					cout << "         ";
			}
		}
		cout << endl << " ";
		for (int j = 1; j < n - 1; j++)
		{
			if (a[i][j] != ' ')
			{
				if ((i == px && j == py) || (i == x1 && j == y1) || (i == x2 && j == y2))
				{
					charColor(a[i][j]);
					cout << "|";
					setColour(0x70);
					cout << "       ";
					charColor(a[i][j]);
					cout << "|";
				}
				else
				{
					charColor(a[i][j]);
					cout << "|       |";
				}
			}
			else
			{
				if ((i == px && j == py) || (i == x1 && j == y1) || (i == x2 && j == y2))
				{
					cout << " ";
					setColour(0x70);
					cout << "       ";
					setColour(0x07);
					cout << " ";
				}
				else
					cout << "         ";
			}
		}
		cout << endl << " ";
		for (int j = 1; j < n - 1; j++)
		{
			if (a[i][j] != ' ')
			{
				charColor(a[i][j]);
				cout << " ------- ";
			}
			if (a[i][j] == ' ')
				cout << "         ";
		}
		cout << endl << " ";
		setColour(0x07);
	}

}

char** generateBoard() {
    srand(time(0));
    char** a = new char* [rows];
    for (int i = 0; i < rows; ++i) {
        a[i] = new char[cols];
        for (int j = 0; j < cols; ++j) {
            a[i][j] = ' ';
        }
    }

    int charCounts[] = { 4, 4, 4, 4, 4, 4, 4, 2 };
    int totalChars = 0;
    for (int count : charCounts) {
        totalChars += count;
    }

    int charIndex = 0;
    for (int i = 1; i < rows - 1; ++i) {
        for (int j = 1; j < cols - 1; ++j) {
            if (totalChars <= 0) {
                break;
            }
            int randChar = rand() % sizeof(availableChars);
            while (charCounts[randChar] <= 0) {
                randChar = rand() % sizeof(availableChars);
            }
            a[i][j] = availableChars[randChar];
            charCounts[randChar]--;
            totalChars--;
        }
    }

    return a;
}

void charColor(char c) {
    switch (c) {
    case 'A':
        setColour(0x01);
        break;
    case 'B':
        setColour(0x02);
        break;
    case 'C':
        setColour(0x0E);
        break;
    case 'D':
        setColour(0x04);
        break;
    case 'E':
        setColour(0x05);
        break;
    case 'F':
        setColour(0x06);
        break;
    case 'G':
        setColour(0x0B);
        break;
    case 'H':
        setColour(0x0C);
        break;
    }
}

void deleteCell(char** board,char& a, char& b) {
    a = ' ';
    b = ' ';
}

HANDLE consoleOutput;

void setConsoleColor(int bg, int text)
{
	SetConsoleTextAttribute(consoleOutput, bg * 16 + text);
}

void gotoXY(int column, int line)
{
	COORD coord;
	coord.X = column;
	coord.Y = line;

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if (!SetConsoleCursorPosition(hConsole, coord))
	{
		cout << "hk dc" << endl;
	}
}

void deleteBoard(char** &a, int rows, int cols)
{
	for (int i = 0; i < rows;i++)
	{
		delete[] a[i];
	}
	delete[] a;
}

void Move(int xMax, int yMax, int& sx, int& sy, char command) { // ham di chuyen o con tro dua vao nut nguoi dung nhap la len xuong trai phai
//	command = _getch();
	switch (command) {
	case 77: { // di chuyen o con tro sang phai
		if (sy < yMax) // neu chua vuot qua bien thi di chuyen thanh cong
			sy++;
		break;
	}
	case 75: { // di chuyen o con tro sang trai
		if (sy > 1) // neu chua vuot qua bien thi di chuyen thanh cong
			sy--;
		break;
	}
	case 80: { // di chuyen o con tro xuong duoi
		if (sx < xMax)// neu chua vuot qua bien thi di chuyen thanh cong
			sx++;
		break;
	}
	case 72: { // di chuyen o con tro len tren
		if (sx > 1)// neu chua vuot qua bien thi di chuyen thanh cong
			sx--;
		break;
	}
	}
}



//extra advanced feature

// inspired by thuanphat(only deletetoleft function)
//cells move toward left
void deleteBlanktoLeft(char** a) { // ham xoa o trong, don sang trai trong difficult mode
	for (int i = 1; i < 6; i++)
		for (int j = 1; j < 7; j++)
		{
			if (a[i][j] == ' ')
			{
				for (int l = j; l < 6; l++)
				{
					a[i][l] = a[i][l + 1];
					a[i][l + 1] = ' ';
				}
			}
			if (a[i][j] == ' ')
			{
				for (int l = j; l < 6; l++)
				{
					a[i][l] = a[i][l + 1];
					a[i][l + 1] = ' ';
				}
			}
		}
}

//cells move toward right
void deleteBlanktoRight(char** a) { 
	for (int i = 1; i < 6; i++) {
		for (int j = 6; j > 0; j--) { 
			if (a[i][j] == ' ') {
				for (int l = j; l > 1; l--) { 
					a[i][l] = a[i][l - 1];
					a[i][l - 1] = ' ';
				}
			}
		}
	}
}

//cells move downward
void deleteBlankDownwards(char** a) {
	for (int j = 0; j < 7; j++) {
		for (int i = 0; i < 6; i++) {
			if (a[i][j] == ' ') {
				for (int k = i; k > 0; k--) {
					a[k][j] = a[k - 1][j];
					a[k - 1][j] = ' ';
				}
			}
		}
	}
}

//cell move upward
void deleteBlankUpwards(char** a) {
	for (int j = 0; j < 7; j++) {
		for (int i = 6  ; i > 0; i--) {
			if (a[i][j] == ' ') {
				for (int k = i; k < 6; k++) {
					a[k][j] = a[k + 1][j];
					a[k + 1][j] = ' ';
				}
			}
		}
	}
}



//source from louis2602
//https://github.com/Louis2602/Pikachu-Game/blob/master/Pikachu/Menu.cpp
void printMenu()
{
	unsigned char logo[] = R"(

		 ________  ___  ___  __    ________  ________  ___  ___  ___  ___     
		|\   __  \|\  \|\  \|\  \ |\   __  \|\   ____\|\  \|\  \|\  \|\  \    
		\ \  \|\  \ \  \ \  \/  /|\ \  \|\  \ \  \___|\ \  \\\  \ \  \\\  \   
		 \ \   ____\ \  \ \   __\_ \ \   __  \ \  \    \ \   __  \ \  \\\  \  
		  \ \  \___|\ \  \ \  \\ \  \ \  \ \  \ \  \____\ \  \ \  \ \  \\\  \ 
		   \ \__\    \ \__\ \__\\ \__\ \__\ \__\ \_______\ \__\ \__\ \_______\
		    \|__|     \|__|\|__| \|__|\|__|\|__|\|_______|\|__|\|__|\|_______|                                                                   
	)";
	cout << logo;
	gotoXY(38, 0);
	setConsoleColor(15, 1);
	gotoXY(38, 8);
	setConsoleColor(15, 2);
	cout << R"(
  _____  _  _  ___   __  __    _  _____  ___  _  _  ___  _  _   ___    ___    _    __  __  ___ 
 |_   _|| || || __| |  \/  |  /_\|_   _|/ __|| || ||_ _|| \| | / __|  / __|  /_\  |  \/  || __|
   | |  | __ || _|  | |\/| | / _ \ | | | (__ | __ | | | | .` || (_ | | (_ | / _ \ | |\/| || _| 
   |_|  |_||_||___| |_|  |_|/_/ \_\|_|  \___||_||_||___||_|\_| \___|  \___|/_/ \_\|_|  |_||___|
	)";
}

//inspired by Khoi Phan - Duy Vo 23CLC07
void drawBox(int x, int y, int width, int height)
{
	//print-
	for (int ix = x; ix < x + width; ix++) {
		gotoXY(ix, y);
		cout << char(196);
		gotoXY(ix, y + height - 1);
		cout << char(196);
	}

	//print |
	for (int iy = y; iy < y + height; iy++) {
		gotoXY(x, iy);
		cout << char(179);
		gotoXY(x + width - 1, iy);
		cout << char(179);
	}

	//print corners
	gotoXY(x, y); cout << char(218); //TOP LEFT CORNER
	gotoXY(x + width - 1, y); cout << char(191); //TOP RIGHT CORNER
	gotoXY(x, y + height - 1); cout << char(192); //BOTTOM LEFT CORNER
	gotoXY(x + width - 1, y + height - 1); cout << char(217); //BOTTOM RIGHT CORNER
}

//this function is used to shuffle the board
void shuffleNonEmptyCells(char** matrix, int rows, int cols) {
	// Create a random device
	std::random_device rd;

	// Initialize a default random engine with the random device
	std::default_random_engine engine(rd());

	// Create a vector to store the non-empty cells
	std::vector<char> nonEmptyCells;

	// Add the non-empty cells to the vector
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (matrix[i][j] != ' ') {  // If the cell is not empty
				nonEmptyCells.push_back(matrix[i][j]);
			}
		}
	}

	// Shuffle the non-empty cells
	std::shuffle(nonEmptyCells.begin(), nonEmptyCells.end(), engine);

	// Put the shuffled cells back into the matrix
	int index = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (matrix[i][j] != ' ') {  // If the cell is not empty
				matrix[i][j] = nonEmptyCells[index++];
			}
		}
	}
}