#include <iostream>

static char box[5][12] = {
    {" --------- "},
    {"|         |"},
    {"|         |"},
    {"|         |"},
    {" --------- "}
};

const int rows = 7;
const int cols = 8;

const char availableChars[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H' };

void setColour(int);

void createBoard(char** , int, int, int, int, int, int, int, int);

char** generateBoard();

void charColor(char);

void deleteCell(char** board, char& a, char& b);

void setConsoleColor(int bg, int text);

void gotoXY(int column, int line);

void deleteBoard(char**& a, int rows, int cols);

void Move(int xMax, int yMax, int& sx, int& sy, char command);

void deleteBlanktoLeft(char** a);

void deleteBlanktoRight(char** a);

void deleteBlankDownwards(char** a);

void deleteBlankUpwards(char** a);

void printMenu();

void drawBox(int x, int y, int width, int height);

void shuffleNonEmptyCells(char** matrix, int rows, int cols);