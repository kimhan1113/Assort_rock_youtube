// 어소트락 유튜브 강의

#include "pch.h"
#include <conio.h>
#include <iostream>
using namespace std;

struct _tagPoint
{
	int x;
	int y;
};

typedef _tagPoint	POINT;
typedef _tagPoint*	PPOINT;

/*
	0 : 벽		■
	1 : 길			
	2 : 시작점	☆
	3 : 도착점	◎
*/

void SetMaze(char Maze[21][21], PPOINT pPlayerPos, 
	PPOINT pStartPos, PPOINT pEndPos)
{
	pStartPos->x = 0;
	pStartPos->y = 0;

	pEndPos->x = 19;
	pEndPos->y = 19;

	*pPlayerPos = *pStartPos;

	strcpy_s(Maze[0],  "21100000000000000000");
	strcpy_s(Maze[1],  "00111111111100000000");
	strcpy_s(Maze[2],  "00100010000111111100");
	strcpy_s(Maze[3],  "01100010000000000100");
	strcpy_s(Maze[4],  "01000011110001111100");
	strcpy_s(Maze[5],  "01000000001111000000");
	strcpy_s(Maze[6],  "01100000001000000000");
	strcpy_s(Maze[7],  "00100000001111111000");
	strcpy_s(Maze[8],  "00001110000000001000");
	strcpy_s(Maze[9],  "01111011111111111000");
	strcpy_s(Maze[10], "01000000000000000000");
	strcpy_s(Maze[11], "01111100111111100000");
	strcpy_s(Maze[12], "00000111100000111110");
	strcpy_s(Maze[13], "01111100000000000010");
	strcpy_s(Maze[14], "01000000000000000010");
	strcpy_s(Maze[15], "01111110000000000010");
	strcpy_s(Maze[16], "00000010000000000010");
	strcpy_s(Maze[17], "01111110000000011110");
	strcpy_s(Maze[18], "01000000000000010000");
	strcpy_s(Maze[19], "11000000000000011113");
}

void Output(char Maze[21][21], PPOINT pPlayerPos)
{
	for (int i = 0; i < 20; ++i)
	{
		for (int j = 0; j < 20; ++j)
		{
			if (pPlayerPos->x == j && pPlayerPos->y == i)
				cout << "＆";

			else if (Maze[i][j] == '0')
				cout << "■";

			else if(Maze[i][j] == '1')
				cout << "  ";

			else if (Maze[i][j] == '2')
				cout << "☆";

			else if (Maze[i][j] == '3')
				cout << "◎";
		}
		cout << endl;
	}
}

void MoveUp(char Maze[21][21], PPOINT pPlayerPos)
{
	if (pPlayerPos->y - 1 >= 0)
	{
		if (Maze[pPlayerPos->y - 1][pPlayerPos->x] != '0')
		{
			--pPlayerPos->y;
		}
	}
}

void MoveDown(char Maze[21][21], PPOINT pPlayerPos)
{
	if (pPlayerPos->y + 1 < 20)
	{
		if (Maze[pPlayerPos->y + 1][pPlayerPos->x] != '0')
		{
			++pPlayerPos->y;
		}
	}
}

void MoveLeft(char Maze[21][21], PPOINT pPlayerPos)
{
	if (pPlayerPos->x - 1 >= 0)
	{
		if (Maze[pPlayerPos->y][pPlayerPos->x - 1] != '0')
		{
			--pPlayerPos->x;
		}
	}
}

void MoveRight(char Maze[21][21], PPOINT pPlayerPos)
{
	if (pPlayerPos->x + 1 < 20)
	{
		if (Maze[pPlayerPos->y][pPlayerPos->x + 1] != '0')
		{
			++pPlayerPos->x;
		}
	}
}

void MovePlayer(char Maze[21][21], PPOINT pPlayerPos, char cInput)
{
	switch (cInput)
	{
	case 'w':
	case 'W':
		MoveUp(Maze, pPlayerPos);
		break;

	case 's':
	case 'S':
		MoveDown(Maze, pPlayerPos);
		break;

	case 'a':
	case 'A':
		MoveLeft(Maze, pPlayerPos);
		break;

	case 'd':
	case 'D':
		MoveRight(Maze, pPlayerPos);
		break;
	}
}

int main()
{
	char strMaze[21][21];	// 20x20 배열 - 널문자포함 21x21 배열 생성
	
	POINT tPlayerPos;
	POINT tStartPos;
	POINT tEndPos;

	SetMaze(strMaze, &tPlayerPos, &tStartPos, &tEndPos);

	while (true)
	{
		system("cls");
		
		Output(strMaze, &tPlayerPos);

		if (tPlayerPos.x == tEndPos.x && tPlayerPos.y == tEndPos.y)
		{
			cout << "도착완료! 성공~" << endl;
			break;
		}

		cout << endl;
		cout << "w : 위 s : 아래 a : 왼쪽 d : 오른쪽 q : 종료" << endl;

		char cInput = _getch();

		if (cInput == 'q' || cInput == 'Q')
			break;

		MovePlayer(strMaze, &tPlayerPos, cInput);

	}


	return 0;
}





