#pragma once
#include<string>
#include<iostream>

using namespace std;

struct player
{
	string name;
	int point = 0;
	int life = 3;
	int help = 3;
	int stage = 1;
};

void getPlayerInfo(player& p);

void resetStatus(int& x1, int& y1, int& x2, int& y2, int& cnt);

void displayStatus(player& p);

void displayResults(bool win);

bool Is_Continue(char& NextGame);

void writeLeaderBoard(player p, string filename);

void sortPlayer(player p[100], int n);

void drawLB(player p[100], int n);

void DisplayLB(string filename);

void stringColor(string s, int color);

void suggestMove(char** board, int width, int height);
