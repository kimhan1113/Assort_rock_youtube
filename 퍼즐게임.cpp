// 어소트락 유튜브 강의

#include "pch.h"
#include <iostream>
#include <time.h>
#include <conio.h> // 콘솔 입출력 기능

using namespace std;

int main()
{
	srand((unsigned int)time(NULL));

	int iNumber[25] = {};

	for (int i = 0; i < 24; ++i)
	{
		iNumber[i] = i + 1;
	}

	// 공백 의미(특수값) - INT_MAX
	iNumber[24] = INT_MAX;		// 마지막 칸은 공백
	// F12 누르면 값 볼 수 있다

	int iStarIndex = 24; // * 위치 저장

	// 마지막 공백 제외하고 1~24 숫자를 섞는다
	// 인덱스는 0~23번
	int nTmp, idx1, idx2;

	for (int i = 0; i < 100; ++i)
	{
		idx1 = rand() % 24; // 0 ~ 23
		idx2 = rand() % 24; // 0 ~ 23

		nTmp = iNumber[idx1];
		iNumber[idx1] = iNumber[idx2];
		iNumber[idx2] = nTmp;
	}
	
	while (1)
	{
		//////////////////////////////////////////////////////

		// i는 세로
		for (int i = 0; i < 5; ++i)
		{
			// j는 가로
			for (int j = 0; j < 5; ++j)
			{
				// 마지막 칸은 * 표시
				if (iNumber[i * 5 + j] == INT_MAX)
					cout << "*\t";
				else
					// 줄번호 * 가로개수 + 칸번호
					cout << iNumber[i * 5 + j] << "\t";
			}

			cout << endl;
		}

		// 퍼즐 완성 확인
		bool bWin = true;

		for (int i = 0; i < 24; ++i)
		{
			if (iNumber[i] != i + 1)
			{
				bWin = false;
				break;
			}
		}

		if (bWin == true)
		{
			cout << "숫자를 모두 맞췄습니다" << endl;
			break;
		}

		//////////////////////////////////////////////////////


		cout << "w : 위 s : 아래 a : 왼쪽 d : 오른쪽 q : 종료 == ";
		
		// cin  엔터를 눌러줘야 하므로 불편

		char cInput = _getch();		// 문자 입력 후 바로 반환 종료

		
		switch (cInput)
		{
		case'w':
		case'W':
			if (iStarIndex > 4) // 예외처리
			{
				iNumber[iStarIndex] = iNumber[iStarIndex - 5];
				iNumber[iStarIndex - 5] = INT_MAX;
				iStarIndex -= 5;
			}
			break;

		case's':
		case'S':
			if (iStarIndex < 20) // 예외처리
			{
				iNumber[iStarIndex] = iNumber[iStarIndex + 5];
				iNumber[iStarIndex + 5] = INT_MAX;
				iStarIndex += 5;
			}
			break;

		case'a':
		case'A':
			if (iStarIndex % 5 != 0) // 예외처리
			{
				iNumber[iStarIndex] = iNumber[iStarIndex - 1];
				iNumber[iStarIndex - 1] = INT_MAX;
				--iStarIndex;
			}
			break;

		case'd':
		case'D':
			if (iStarIndex % 5 != 4) // 예외처리
			{
				iNumber[iStarIndex] = iNumber[iStarIndex + 1];
				iNumber[iStarIndex + 1] = INT_MAX;
				++iStarIndex;
			}
			break;
		}

		if (cInput == 'q' || cInput == 'Q')
			break;

		system("cls");
	}

	cout << endl;
	cout << endl;
	cout << "게임 종료" << endl;

	return 0;
}
