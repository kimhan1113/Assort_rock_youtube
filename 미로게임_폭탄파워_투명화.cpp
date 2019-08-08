// 어소트락 유튜브 강의

#include "pch.h"
#include <conio.h>
#include <time.h>
#include <iostream>
using namespace std;

struct _tagPoint
{
	int x;
	int y;
};

typedef _tagPoint	POINT;
typedef _tagPoint*	PPOINT;

typedef struct _tagPlayer
{
	_tagPoint	tPos;
	bool		bWallPush;
	bool		bTransparency;
	int			iBombPower;
} PLAYER, *PPLAYER;

/*
	0 : 벽		■
	1 : 길			
	2 : 시작점	☆
	3 : 도착점	◎
	4 : 폭탄		♨
	5 : 파워 아이템
	6 : 벽밀기 아이템
	7 : 투명 아이템
	8 : 윔홀
*/

void SetMaze(char Maze[21][21], PPLAYER pPlayer,
	PPOINT pStartPos, PPOINT pEndPos)
{
	pStartPos->x = 0;
	pStartPos->y = 0;

	pEndPos->x = 19;
	pEndPos->y = 19;

	pPlayer->tPos = *pStartPos; 

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

void Output(char Maze[21][21], PPLAYER pPlayer)
{
	for (int i = 0; i < 20; ++i)
	{
		for (int j = 0; j < 20; ++j)
		{
			if (Maze[i][j] == '4')
				cout << "♨";

			else if (pPlayer->tPos.x == j && pPlayer->tPos.y == i)
				cout << "＆";

			else if (Maze[i][j] == '0')
				cout << "■";

			else if (Maze[i][j] == '1')
				cout << "  ";

			else if (Maze[i][j] == '2')
				cout << "☆";

			else if (Maze[i][j] == '3')
				cout << "◎";

			else if (Maze[i][j] == '5')
				cout << "㉾";

			else if (Maze[i][j] == '6')
				cout << "※";

			else if (Maze[i][j] == '7')
				cout << "▲";
		}
		cout << endl;
	}

	cout << "폭탄파워 : " << pPlayer->iBombPower << endl;
	cout << "벽 통과 : ";
	if (pPlayer->bTransparency)
		cout << "ON\t";
	else
		cout << "OFF\t";

	cout << "벽 밀기 : ";
	if (pPlayer->bWallPush)
		cout << "ON\t";
	else
		cout << "OFF\t";

}

bool AddItem(char cItemType, PPLAYER pPlayer)
{
	if (cItemType  == '5')
	{
		if(pPlayer->iBombPower < 5)
			++pPlayer->iBombPower;

		return true;
	}

	else if (cItemType == '6')
	{
		pPlayer->bWallPush = true;
		return true;
	}

	else if (cItemType == '7')
	{
		pPlayer->bTransparency = true;
		return true;
	}

	return false;
}

void MoveUp(char Maze[21][21], PPLAYER pPlayer)
{
	if (pPlayer->tPos.y - 1 >= 0)
	{
		if (Maze[pPlayer->tPos.y - 1][pPlayer->tPos.x] != '0' &&
			Maze[pPlayer->tPos.y - 1][pPlayer->tPos.x] != '4')
		{
			--pPlayer->tPos.y;
		}

		else if (pPlayer->bTransparency)
			--pPlayer->tPos.y;

		if (AddItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer))
		{
			Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';
		}
	}
}

void MoveDown(char Maze[21][21], PPLAYER pPlayer)
{
	if (pPlayer->tPos.y + 1 < 20)
	{
		if (Maze[pPlayer->tPos.y + 1][pPlayer->tPos.x] != '0' &&
			Maze[pPlayer->tPos.y + 1][pPlayer->tPos.x] != '4')
		{
			++pPlayer->tPos.y;
		}


		else if (pPlayer->bTransparency)
			++pPlayer->tPos.y;

		if (AddItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer))
		{
			Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';
		}

	}
}

void MoveLeft(char Maze[21][21], PPLAYER pPlayer)
{
	if (pPlayer->tPos.x - 1 >= 0)
	{
		if (Maze[pPlayer->tPos.y][pPlayer->tPos.x - 1] != '0' &&
			Maze[pPlayer->tPos.y][pPlayer->tPos.x - 1] != '4')
		{
			--pPlayer->tPos.x;
		}

		else if (pPlayer->bTransparency)
			--pPlayer->tPos.x;

		if (AddItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer))
		{
			Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';
		}
	}

}

void MoveRight(char Maze[21][21], PPLAYER pPlayer)
{
	if (pPlayer->tPos.x + 1 < 20)
	{
		if (Maze[pPlayer->tPos.y][pPlayer->tPos.x + 1] != '0' &&
			Maze[pPlayer->tPos.y][pPlayer->tPos.x + 1] != '4')
		{
			++pPlayer->tPos.x;
		}

		else if (pPlayer->bTransparency)
			++pPlayer->tPos.x;

		if (AddItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer))
		{
			Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';
		}
	}
}

void MovePlayer(char Maze[21][21], PPLAYER pPlayer, char cInput)
{
	switch (cInput)
	{
	case 'w':
	case 'W':
		MoveUp(Maze, pPlayer);
		break;

	case 's':
	case 'S':
		MoveDown(Maze, pPlayer);
		break;

	case 'a':
	case 'A':
		MoveLeft(Maze, pPlayer);
		break;

	case 'd':
	case 'D':
		MoveRight(Maze, pPlayer);
		break;
	}
}

void CreateBomb(char Maze[21][21], const PPLAYER pPlayer,
	PPOINT pBombArr, int* pBombCnt)
{
	// 폭탄 갯수 초과
	if (*pBombCnt == 5)
		return;

	else if (Maze[pPlayer->tPos.y][pPlayer->tPos.x] == '0')
		return;

	// 중복 위치 설치 불가
	for (int i = 0; i < *pBombCnt; ++i)
	{
		if (pPlayer->tPos.x == pBombArr[i].x &&
			pPlayer->tPos.y == pBombArr[i].y)
			return;
	}

	pBombArr[*pBombCnt] = pPlayer->tPos;
	++(*pBombCnt);

	Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '4';
}

void Fire(char Maze[21][21], PPLAYER pPlayer, PPOINT pBombArr,
	int* pBombCnt)
{
	for (int i = 0; i < *pBombCnt; ++i)
	{
		Maze[pBombArr[i].y][pBombArr[i].x] = '1';

		// 플레이어가 폭탄에 맞을 경우 시작점으로 보낸다
		if (pPlayer->tPos.x == pBombArr[i].x &&
			pPlayer->tPos.y == pBombArr[i].y)
		{
			pPlayer->tPos.x = 0;
			pPlayer->tPos.y = 0;
		}

		for (int j = 1; j <= pPlayer->iBombPower; ++j)
		{
			if (pBombArr[i].y - j >= 0)
			{
				if (Maze[pBombArr[i].y - j][pBombArr[i].x] == '0')
				{
					// 아이템 드랍 확률을 구한다
					if (rand() % 100 < 20)
					{
						int iPercent = rand() % 100;

						if (iPercent < 70)
							Maze[pBombArr[i].y - j][pBombArr[i].x] = '5';
						else if (iPercent < 80)
							Maze[pBombArr[i].y - j][pBombArr[i].x] = '6';
						else
							Maze[pBombArr[i].y - j][pBombArr[i].x] = '7';
					}
					else
						Maze[pBombArr[i].y - j][pBombArr[i].x] = '1';
				}

				if (pPlayer->tPos.x == pBombArr[i].x &&
					pPlayer->tPos.y == pBombArr[i].y - 1)
				{
					pPlayer->tPos.x = 0;
					pPlayer->tPos.y = 0;
				}
			}

			if (pBombArr[i].y + j < 20)
			{
				if (Maze[pBombArr[i].y + j][pBombArr[i].x] == '0')
				{
					Maze[pBombArr[i].y + j][pBombArr[i].x] = '1';
				
					// 아이템 드랍 확률을 구한다
					if (rand() % 100 < 20)
					{
						int iPercent = rand() % 100;

						if (iPercent < 70)
							Maze[pBombArr[i].y + j][pBombArr[i].x] = '5';
						else if (iPercent < 80)
							Maze[pBombArr[i].y + j][pBombArr[i].x] = '6';
						else
							Maze[pBombArr[i].y + j][pBombArr[i].x] = '7';
					}
					else
						Maze[pBombArr[i].y + j][pBombArr[i].x] = '1';
				}
				if (pPlayer->tPos.x == pBombArr[i].x &&
					pPlayer->tPos.y == pBombArr[i].y + j)
				{
					pPlayer->tPos.x = 0;
					pPlayer->tPos.y = 0;
				}
			}

			if (pBombArr[i].x - j >= 0)
			{
				if (Maze[pBombArr[i].y][pBombArr[i].x - j] == '0')
				{
					Maze[pBombArr[i].y][pBombArr[i].x - j] = '1';

					// 아이템 드랍 확률을 구한다
					if (rand() % 100 < 20)
					{
						int iPercent = rand() % 100;

						if (iPercent < 70)
							Maze[pBombArr[i].y][pBombArr[i].x - j] = '5';
						else if (iPercent < 80)
							Maze[pBombArr[i].y][pBombArr[i].x - j] = '6';
						else
							Maze[pBombArr[i].y][pBombArr[i].x - j] = '7';
					}
					else
						Maze[pBombArr[i].y][pBombArr[i].x - j] = '1';
				}

				if (pPlayer->tPos.x == pBombArr[i].x - j &&
					pPlayer->tPos.y == pBombArr[i].y)
				{
					pPlayer->tPos.x = 0;
					pPlayer->tPos.y = 0;
				}
			}

			if (pBombArr[i].x + j < 20)
			{
				if (Maze[pBombArr[i].y][pBombArr[i].x + j] == '0')
				{
					Maze[pBombArr[i].y][pBombArr[i].x + j] = '1';

					// 아이템 드랍 확률을 구한다
					if (rand() % 100 < 20)
					{
						int iPercent = rand() % 100;

						if (iPercent < 70)
							Maze[pBombArr[i].y][pBombArr[i].x + j] = '5';
						else if (iPercent < 80)
							Maze[pBombArr[i].y][pBombArr[i].x + j] = '6';
						else
							Maze[pBombArr[i].y][pBombArr[i].x + j] = '7';
					}
					else
						Maze[pBombArr[i].y][pBombArr[i].x + j] = '1';
				}

				if (pPlayer->tPos.x == pBombArr[i].x + j &&
					pPlayer->tPos.y == pBombArr[i].y)
				{
					pPlayer->tPos.x = 0;
					pPlayer->tPos.y = 0;
				}
			}
		}
	}

	*pBombCnt = 0;
}

int main()
{
	srand((unsigned int)time(0));

	char strMaze[21][21];	// 20x20 배열 - 널문자포함 21x21 배열 생성
	int iBombCnt = 0;
	int iAddBomb = 0;

	PLAYER tPlayer = {};
	POINT tStartPos;
	POINT tEndPos;
	POINT tBombPos[5];

	tPlayer.iBombPower = 1;

	SetMaze(strMaze, &tPlayer, &tStartPos, &tEndPos);

	while (true)
	{
		system("cls");
		
		Output(strMaze, &tPlayer);

		if (tPlayer.tPos.x == tEndPos.x && tPlayer.tPos.y == tEndPos.y)
		{
			cout << "도착완료! 성공~" << endl;
			break;
		}

		cout << endl;
		cout << "t : 폭탄설치 u : 폭탄 터트리기 i : 벽밀기" << endl;
		cout << "w : 위 s : 아래 a : 왼쪽 d : 오른쪽 q : 종료" << endl;

		char cInput = _getch();

		if (cInput == 'q' || cInput == 'Q')
			break;

		else if (cInput == 't' || cInput == 'T')
			CreateBomb(strMaze, &tPlayer, tBombPos, &iBombCnt);

		else if (cInput == 'u' || cInput == 'U')
		{
			Fire (strMaze, &tPlayer, tBombPos, &iBombCnt);
		}

		else
			MovePlayer(strMaze, &tPlayer, cInput);

	}


	return 0;
}





