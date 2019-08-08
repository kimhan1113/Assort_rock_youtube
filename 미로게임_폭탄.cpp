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
	4 : 폭탄		♨
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
			if (Maze[i][j] == '4')
				cout << "♨";

			else if (pPlayerPos->x == j && pPlayerPos->y == i)
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
		if (Maze[pPlayerPos->y - 1][pPlayerPos->x] != '0' &&
			Maze[pPlayerPos->y - 1][pPlayerPos->x] != '4')
		{
			--pPlayerPos->y;
		}
	}
}

void MoveDown(char Maze[21][21], PPOINT pPlayerPos)
{
	if (pPlayerPos->y + 1 < 20)
	{
		if (Maze[pPlayerPos->y + 1][pPlayerPos->x] != '0' &&
			Maze[pPlayerPos->y + 1][pPlayerPos->x] != '4')
		{
			++pPlayerPos->y;
		}
	}
}

void MoveLeft(char Maze[21][21], PPOINT pPlayerPos)
{
	if (pPlayerPos->x - 1 >= 0)
	{
		if (Maze[pPlayerPos->y][pPlayerPos->x - 1] != '0' &&
			Maze[pPlayerPos->y][pPlayerPos->x - 1] != '4')
		{
			--pPlayerPos->x;
		}
	}
}

void MoveRight(char Maze[21][21], PPOINT pPlayerPos)
{
	if (pPlayerPos->x + 1 < 20)
	{
		if (Maze[pPlayerPos->y][pPlayerPos->x + 1] != '0' &&
			Maze[pPlayerPos->y][pPlayerPos->x + 1] != '4')
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

void CreateBomb(char Maze[21][21], const PPOINT pPlayer,
	PPOINT pBombArr, int* pBombCnt)
{
	// 폭탄 갯수 초과
	if (*pBombCnt == 5)
		return;

	// 중복 위치 설치 불가
	for (int i = 0; i < *pBombCnt; ++i)
	{
		if (pPlayer->x == pBombArr[i].x &&
			pPlayer->y == pBombArr[i].y)
			return;
	}

	pBombArr[*pBombCnt] = *pPlayer;
	++(*pBombCnt);

	Maze[pPlayer->y][pPlayer->x] = '4';
}

void Fire(char Maze[21][21], PPOINT pPlayer, PPOINT pBombArr,
	int* pBombCnt)
{
	for (int i = 0; i < *pBombCnt; ++i)
	{
		Maze[pBombArr[i].y][pBombArr[i].x] = '1';


		// 플레이어가 폭탄에 맞을 경우 시작점으로 보낸다
		if (pPlayer->x == pBombArr[i].x &&
			pPlayer->y == pBombArr[i].y)
		{
			pPlayer->x = 0;
			pPlayer->y = 0;
		}

		if (pBombArr[i].y - 1 >= 0)
		{
			if (Maze[pBombArr[i].y - 1][pBombArr[i].x] == '0')
				Maze[pBombArr[i].y - 1][pBombArr[i].x] = '1'; 

			if (pPlayer->x == pBombArr[i].x &&
				pPlayer->y == pBombArr[i].y - 1)
			{
				pPlayer->x = 0;
				pPlayer->y = 0;
			}
		}

		if (pBombArr[i].y + 1 < 20)
		{
			if (Maze[pBombArr[i].y + 1][pBombArr[i].x] == '0')
				Maze[pBombArr[i].y + 1][pBombArr[i].x] = '1';

			if (pPlayer->x == pBombArr[i].x &&
				pPlayer->y == pBombArr[i].y + 1)
			{
				pPlayer->x = 0;
				pPlayer->y = 0;
			}
		}

		if (pBombArr[i].x - 1 >= 0)
		{
			if (Maze[pBombArr[i].y][pBombArr[i].x - 1] == '0')
				Maze[pBombArr[i].y][pBombArr[i].x - 1] = '1';

			if (pPlayer->x == pBombArr[i].x - 1 &&
				pPlayer->y == pBombArr[i].y)
			{
				pPlayer->x = 0;
				pPlayer->y = 0;
			}
		}

		if (pBombArr[i].x + 1 < 20)
		{
			if (Maze[pBombArr[i].y][pBombArr[i].x + 1] == '0')
				Maze[pBombArr[i].y][pBombArr[i].x + 1] = '1';

			if (pPlayer->x == pBombArr[i].x + 1 &&
				pPlayer->y == pBombArr[i].y)
			{
				pPlayer->x = 0;
				pPlayer->y = 0;
			}
		}
		
	}

	*pBombCnt = 0;
}

int main()
{
	char strMaze[21][21];	// 20x20 배열 - 널문자포함 21x21 배열 생성
	int iBombCnt = 0;
	int iAddBomb = 0;

	POINT tPlayerPos;
	POINT tStartPos;
	POINT tEndPos;
	POINT tBombPos[5];

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
		cout << "t : 폭탄설치 u : 폭탄 터트리기" << endl;
		cout << "w : 위 s : 아래 a : 왼쪽 d : 오른쪽 q : 종료" << endl;

		char cInput = _getch();

		if (cInput == 'q' || cInput == 'Q')
			break;

		else if (cInput == 't' || cInput == 'T')
			CreateBomb(strMaze, &tPlayerPos, tBombPos, &iBombCnt);

		else if (cInput == 'u' || cInput == 'U')
		{
			Fire (strMaze, &tPlayerPos, tBombPos, &iBombCnt);
		}

		else
			MovePlayer(strMaze, &tPlayerPos, cInput);

	}


	return 0;
}





