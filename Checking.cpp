#include <iostream>
#include <algorithm>
#include "Checking.h"
#include<conio.h>
#include"Board.h"
using namespace std;

//all these checking pattern are inspired by thuanphat611
//https://github.com/thuanphat611/Matching-Game/blob/master/Source/matching.cpp
//https://github.com/thuanphat611/Matching-Game/blob/master/Source/endGameCheck.cpp

bool checkBlankRow(char** a, int y1, int y2, int row) {
	int first = min(y1, y2);
	int last = max(y1, y2);

	for (int i = first; i <= last; i++) {
		if (a[row][i] != ' ')
			return false;
	}
	return true;
}
bool checkBlankColumn(char** a, int x1, int x2, int column) {
	int first = min(x1, x2);
	int last = max(x1, x2);

	for (int i = first ; i <= last; i++) {
		if (a[i][column] != ' ')
			return false;
	}
	return true;
}


bool checkIPattern(char** &a, int x1, int x2, int y1, int y2) {


	if (x1 == x2 && y1 == y2) {
		return false;
	}
	if (x1 == x2) {

		if (y1 + 1 == y2 || y2 + 1 == y1)
		{
			return true;
		}

		return checkBlankRow(a, y1 +1, y2 - 1, x1);
	}

	else if (y1 == y2) {
		if (x1 + 1 == x2 || x2 + 1 == x1)
		{
			return true;
		}

		return checkBlankColumn(a, x1 + 1, x2 - 1, y1);
	}
	return false;
}
bool checkLPattern(char**& a, int x1, int x2, int y1, int y2) { // check if two cells can pair with each other
	if (x1 == x2 || y1 == y2) //if they are in the same rows or cols, they can not be paired
		return false;
	//check distribution of two cells
	if ((y1 < y2 && x1 < x2) || (y1 > y2 && x1 > x2)) // First one: one cell at the left up and one cell at the right down
	{
		int LUx, LUy, RDx, RDy;
		if (y1 < y2 && x1 < x2) // determine which cell is left up, which one is right down
		{
			LUx = x1;
			LUy = y1;
			RDx = x2;
			RDy = y2;
		}
		if (y1 > y2 && x1 > x2)
		{
			LUx = x2;
			LUy = y2;
			RDx = x1;
			RDy = y1;
		}
		if (checkBlankRow(a, LUy + 1, RDy, LUx) && checkBlankColumn(a, LUx, RDx - 1, RDy))
			return true;
		if (checkBlankRow(a, LUy, RDy - 1, RDx) && checkBlankColumn(a, LUx + 1, RDx, LUy))
			return true;
		return false;
	}
	if ((y1 > y2 && x1 < x2) || (y1 < y2 && x1 > x2))// Second one: one at the right up and one at the left down
	{
		int RUx, RUy, LDx, LDy;
		if (y1 > y2 && x1 < x2) // check which is right up and which is left down
		{
			RUx = x1;
			RUy = y1;
			LDx = x2;
			LDy = y2;
		}
		if (y1 < y2 && x1 > x2)
		{
			RUx = x2;
			RUy = y2;
			LDx = x1;
			LDy = y1;
		}

		if (checkBlankRow(a, LDy, RUy - 1, RUx) && checkBlankColumn(a, RUx, LDx - 1, LDy))
			return true;
		if (checkBlankRow(a, LDy + 1, RUy, LDx) && checkBlankColumn(a, RUx + 1, LDx, RUy))
			return true;
		return false;
	}
}
bool checkZPattern(char**& a, int x1, int x2, int y1, int y2) {
	if (x1 == x2 || y1 == y2) //neu 2 o cung hang hoac cung cot thi khong noi kieu Z duoc
		return false;
	if ((y1 < y2 && x1 < x2) || (y1 > y2 && x1 > x2))//kiem tra kieu phan bo cua 2 o tuong tu ham checkL
	{
		int LUx, LUy, RDx, RDy;
		if (y1 < y2 && x1 < x2) //xac dinh Left Up , Right Down
		{
			LUx = x1;
			LUy = y1;
			RDx = x2;
			RDy = y2;
		}
		if (y1 > y2 && x1 > x2)
		{
			LUx = x2;
			LUy = y2;
			RDx = x1;
			RDy = y1;
		}
		// duong noi chu Z
		for (int i = LUy + 1; i <= RDy - 1;i++)
			if (checkBlankColumn(a, LUx, RDx, i))
				if (checkBlankRow(a, LUy + 1, i, LUx) && checkBlankRow(a, i, RDy - 1, RDx))
					return true;
		// duong noi chu N
		for (int j = LUx + 1; j <= RDx - 1; j++)
			if (checkBlankRow(a, LUy, RDy, j))
				if (checkBlankColumn(a, LUx + 1, j, LUy) && checkBlankColumn(a, j, RDx - 1, RDy))
					return true;
		return false;
	}
	if ((y1 > y2 && x1 < x2) || (y1 < y2 && x1 > x2))
	{
		int RUx, RUy, LDx, LDy;
		if (y1 > y2 && x1 < x2) // xac dinh Right Up, Left Down, sau do lam tuong tu o tren
		{
			RUx = x1;
			RUy = y1;
			LDx = x2;
			LDy = y2;
		}
		if (y1 < y2 && x1 > x2)
		{
			RUx = x2;
			RUy = y2;
			LDx = x1;
			LDy = y1;
		}
		for (int i = LDy + 1; i <= RUy - 1; i++)
			if (checkBlankColumn(a, RUx, LDx, i))
				if (checkBlankRow(a, LDy + 1, i, LDx) && checkBlankRow(a, i, RUy - 1, RUx))
					return true;
		for (int j = RUx + 1; j <= LDx - 1; j++)
			if (checkBlankRow(a, LDy, RUy, j))
				if (checkBlankColumn(a, RUx + 1, j, RUy) && checkBlankColumn(a, j, LDx - 1, LDy))
					return true;
		return false;
	}
}
bool checkUPattern(char**& a, int x1, int x2, int y1, int y2) {
	if (x1 == x2) // neu 2 o cung cot thi chi kiem tra duong noi hinh chu U nga ve trai va chu U nga ve phai
	{	//mang 2 chieu dua vao co cac gia tri o ngoai vien deu la khoang trong chinh la de kiem tra duong noi hinh chu U de dang hon
		for (int i = 0; i < x1; i++)
			if (checkBlankRow(a, min(y1, y2), max(y1, y2), i))
				if (checkBlankColumn(a, i, x1 - 1, y1) && checkBlankColumn(a, i, x2 - 1, y2))
					return true;
		for (int i = x1 + 1; i < 7; i++)
			if (checkBlankRow(a, min(y1, y2), max(y1, y2), i))
				if (checkBlankColumn(a, x1 + 1, i, y1) && checkBlankColumn(a, x2 + 1, i, y2))
					return true;
		return false;
	}
	if (y1 == y2) // Neu 2 o cung hang thi kiem tra duong noi hinh chu U va chu U nguoc
	{
		for (int i = 0; i < y1; i++)
			if (checkBlankColumn(a, min(x1, x2), max(x1, x2), i))
				if (checkBlankRow(a, i, y1 - 1, x1) && checkBlankRow(a, i, y2 - 1, x2))
					return true;
		for (int i = y1 + 1; i < 8; i++)
			if (checkBlankColumn(a, min(x1, x2), max(x1, x2), i))
				if (checkBlankRow(a, y1 + 1, i, x1) && checkBlankRow(a, y2 + 1, i, x2))
					return true;
		return false;
	}
	// neu 2 o khong cung hang cung khong cung cot thi kiem tra ca 4 chu U, cach lam nhu tren
	for (int i = 0; i < min(x1, x2); i++)
		if (checkBlankRow(a, min(y1, y2), max(y1, y2), i))
			if (checkBlankColumn(a, i, x1 - 1, y1) && checkBlankColumn(a, i, x2 - 1, y2))
				return true;
	for (int i = max(x1, x2) + 1; i < 7; i++)
		if (checkBlankRow(a, min(y1, y2), max(y1, y2), i))
			if (checkBlankColumn(a, x1 + 1, i, y1) && checkBlankColumn(a, x2 + 1, i, y2))
				return true;
	for (int i = 0; i < min(y1, y2); i++)
		if (checkBlankColumn(a, min(x1, x2), max(x1, x2), i))
			if (checkBlankRow(a, i, y1 - 1, x1) && checkBlankRow(a, i, y2 - 1, x2))
				return true;
	for (int i = max(y1, y2) + 1; i < 8;i++)
		if (checkBlankColumn(a, min(x1, x2), max(x1, x2), i))
			if (checkBlankRow(a, y1 + 1, i, x1) && checkBlankRow(a, y2 + 1, i, x2))
				return true;
	return false;
}


bool checkPairsLeft(char** a, int xArr, int yArr) { // check if there are any cells left
	for (int i = 1; i < xArr; i++)
		for (int j = 0; j < yArr; j++)
			if (a[i][j] != ' ')
				return true;
	return false;
}
bool checkValidPairs(char** a,int xArr, int yArr) { // check if there are any valid pairs
	for (int i = 1; i < xArr; i++)
		for (int j = 1; j < yArr; j++)
		{
			for (int k = j + 1; k < yArr; k++)
				if (a[i][j] == a[i][k] && a[i][j] != ' ')
					if (checkIPattern(a, i, j, i, k) || checkLPattern(a, i, j, i, k) || checkZPattern(a, i, j, i, k) || checkUPattern(a, i, j, i, k))
					{
						return true;
					}
			if (i < 5)
			{
				for (int m = i + 1; m < xArr; m++)
					for (int n = 1; n < yArr; n++)
						if (a[i][j] == a[m][n] && a[i][j] != ' ')
							if (checkIPattern(a, i, j, m, n) || checkLPattern(a, i, j, m, n) || checkZPattern(a, i, j, m, n) || checkUPattern(a, i, j, m, n))
							{
								return true;
							}
			}
		}
	return false;
}
