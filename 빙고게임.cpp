// 어소트락 유튜브 강의

#include "pch.h"
#include <time.h>
#include <iostream>
using namespace std;

int main()
{
	srand((unsigned int)time(0));

	int iNumber[25] = { 0, };

	// 숫자 넣어준다
	for (int i = 0; i < 25; ++i)
	{
		iNumber[i] = i + 1;
	}

	// 숫자 섞어준다
	int nTmp, idx1, idx2;

	for (int i = 0; i < 100; ++i)
	{
		idx1 = rand() % 25;
		idx2 = rand() % 25;

		nTmp = iNumber[idx1];
		iNumber[idx1] = iNumber[idx2];
		iNumber[idx2] = nTmp;
	}

	int iBingo = 0;
	//int nWidth, nHeight, ndiagonal;

	while (true)
	{
		system("cls");

		// 랜덤 숫자 출력
		for (int i = 0; i < 5; ++i)
		{
			for (int j = 0; j < 5; ++j)
			{
				if (iNumber[i * 5 + j] == INT_MAX)
					cout << "*\t";
				else
					cout << iNumber[i * 5 + j] << "\t";
			}
			cout << endl;
		}

		// 숫자 입력
		cout << "Bingo Line : " << iBingo << endl;

		// 빙고가 5개 이상이면 게임 종료
		if (iBingo >= 5)
			break;

		cout << "숫자를 입력하세요(0 : END) : ";
		int nInput;
		cin >> nInput;

		// 예외처리
		if (nInput == 0)
			break;
		// nInput < 1 || nInput > 25
		else if (nInput < 0 || 25 < nInput)
		{
			cout << "1 ~ 25 사이의 숫자를 입력해주세요" << endl;
			continue;
		}

		//////////////////////////////////////////////////////////
		// 중복체크 (true 중복O false 중복X)
		bool bAcc = true;

		for (int i = 0; i < 25; ++i)
		{
			if (nInput == iNumber[i])
			{
				bAcc = false;

				// 숫자 *로 변경
				iNumber[i] = INT_MAX;
			}
		}

		if (bAcc)
			continue;
		//////////////////////////////////////////////////////////


		// 빙고 체크
		iBingo = 0;
		int iStar1 = 0, iStar2 = 0;


		for (int i = 0; i < 5; ++i)
		{
			int iStar1 = 0, iStar2 = 0;

			for (int j = 0; j < 5; ++j)
			{
				// 가로 체크
				if (iNumber[i * 5 + j] == INT_MAX)
					++iStar1;

				// 세로 체크
				if (iNumber[j * 5 + i] == INT_MAX)
					++iStar2;
			}

			if (iStar1 == 5)
				++iBingo;
			if (iStar2 == 5)
				++iBingo;
		}

		// 왼쪽상단 -> 오른쪽상단 대각선
		iStar1 = 0;
		for (int i = 0; i < 25; i += 6)
		{
			if (iNumber[i] == INT_MAX)
				++iStar1;
		}

		if (iStar1 == 5)
			++iBingo;

		// 오른쪽 상단 -> 왼쪽상단 대각선
		iStar1 = 0;
		for (int i = 4; i <= 20; i += 4)
		{
			if (iNumber[i] == INT_MAX)
				++iStar1;
		}

		if (iStar1 == 5)
			++iBingo;
	}

	cout << endl;
	cout << "게임종료" << endl;

	return 0;
}
