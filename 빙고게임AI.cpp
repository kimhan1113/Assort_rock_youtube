// 어소트락 유튜브 강의

#include "pch.h"
#include <time.h>
#include <iostream>
using namespace std;

enum AI_MODE
{
	AM_EASY = 1,
	AM_HARD
};

enum LINE_NUMBER
{
	LN_H1,
	LN_H2,
	LN_H3,
	LN_H4,
	LN_H5,
	LN_V1,
	LN_V2,
	LN_V3,
	LN_V4,
	LN_V5,
	LN_LT,
	LN_RT
};

int main()
{
	srand((unsigned int)time(0));

	int iNumber[25] = { 0, };
	int AiNumber[25] = { 0, };

	// 숫자 배정 및 숫자 섞기 /////////////////////////////////
	for (int i = 0; i < 25; ++i)
	{
		iNumber[i] = i + 1;
		AiNumber[i] = i + 1;
	}

	int nTmp, idx1, idx2;

	for (int i = 0; i < 100; ++i)
	{
		idx1 = rand() % 25;
		idx2 = rand() % 25;

		nTmp = iNumber[idx1];
		iNumber[idx1] = iNumber[idx2];
		iNumber[idx2] = nTmp;

		idx1 = rand() % 25;
		idx2 = rand() % 25;

		nTmp = AiNumber[idx1];
		AiNumber[idx1] = AiNumber[idx2];
		AiNumber[idx2] = nTmp;
	}
	
	// AI 난이도 선택 ///////////////////////////////////
	int iAiMode;

	while (true)
	{
		system("cls");

		cout << "1.Easy" << endl;
		cout << "2.Hard" << endl;
		
		// EASY : *로 바뀌지 않은 숫자를 선택하게 한다
		// HARD : 
	
		cin >> iAiMode;

		if (iAiMode >= AM_EASY && iAiMode <= AM_HARD)
			break;
	}
	//////////////////////////////////////////////////// 

	int iBingo = 0, iAIBingo = 0;
	int iNoneSelect[25] = {};
	int iNoneSelCnt = 0;

	while (true)
	{
		system("cls");

		// 빙고판 출력 /////////////////////////////////////////////
		cout << " ============= Player ============= " << endl;

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

		cout << "Bingo Line : " << iBingo << endl << endl;


		cout << " ============= AI ============= " << endl;

		switch (iAiMode)
		{
		case AM_EASY:
			cout << "AIMODE : EASY ***** " << endl;
			break;

		case AM_HARD:
			cout << "AIMODE : HARD ***** " << endl;
			break;
		}

		for (int i = 0; i < 5; ++i)
		{
			for (int j = 0; j < 5; ++j)
			{
				if (AiNumber[i * 5 + j] == INT_MAX)
					cout << "*\t";
				else
					cout << AiNumber[i * 5 + j] << "\t";
			}
			cout << endl;
		}

		cout << "AIBingo Line : " << iAIBingo << endl << endl;

		// 승리 조건 //////////////////////////////////////////
		
		if (iBingo >= 5)
		{
			cout << "Player 승리" << endl;
			break;
		}

		else if (iAIBingo >= 5)
		{
			cout << "AI 승리" << endl;
			break;
		}

		// 숫자 입력 ///////////////////////////////////////////

		cout << "숫자를 입력하세요(0 : END) : ";
		int nInput;
		cin >> nInput;

		// 예외처리 /////////////////////////////////////////
		if (nInput == 0)						// 강제종료
			break;

		else if (nInput < 1 || nInput > 25)		// 입력오류
		{
			cout << "1 ~ 25 사이의 숫자를 입력해주세요" << endl;
			continue;
		}

		// 중복체크 (true 중복 O false 중복 X) ////////////////
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

		// AI 빙고판 사용자 숫자 입력 ////////////////////////////
		for (int i = 0; i < 25; ++i)
		{
			if (AiNumber[i] == nInput)
			{
				AiNumber[i] = INT_MAX;
				break;
			}
		}

		switch (iAiMode)
		{
		case AM_EASY:
			// 선택 안된 숫자 배열 구성 ///////////////////////////
			iNoneSelCnt = 0;
			for (int i = 0; i < 25; ++i)
			{
				if (AiNumber[i] != INT_MAX)
				{
					iNoneSelect[iNoneSelCnt] = AiNumber[i];
					++iNoneSelCnt;
				}
			}

			// 선택 안된 숫자 중 하나를 nInput에 입력
			nInput = iNoneSelect[rand() % iNoneSelCnt];
			break;

		case AM_HARD:
			int iLine = 0;		
			int iStarCnt = 0;	// * 카운트
			int iSaveCnt = 0;	// 라인별 * 갯수 저장

			// 가능성 높은 라인 조사 //////////////////////////////

			// 가로
			for (int i = 0; i < 5; ++i)
			{
				iStarCnt = 0;		
				for (int j = 0; j < 5; ++j)
				{
					if (AiNumber[i * 5 + j] == INT_MAX)
						++iStarCnt;
				}

				// iStarCnt가  5 미만 >> 5개부터 빙고이기 때문에

				if (iStarCnt < 5 && iSaveCnt < iStarCnt)
				{
					// i = 가로 라인 enum 0 ~ 4
					iLine = i;
					iSaveCnt = iStarCnt;
				}
			}

			// 세로
			for (int i = 0; i < 5; ++i)
			{
				iStarCnt = 0; 
				for (int j = 0; j < 5; ++j)
				{
					if (AiNumber[j * 5 + i] == INT_MAX)
						++iStarCnt;
				}

				if (iStarCnt < 5 && iSaveCnt < iStarCnt)
				{
					// 세로 라인 enum 5 ~ 9
					iLine = i + 5;
					iSaveCnt = iStarCnt;
				}
			}

			// 왼쪽 -> 오른쪽
			iStarCnt = 0;
			for (int i = 0; i < 25; ++i)
			{
				if (AiNumber[i] == INT_MAX)
					++iStarCnt;
			}

			if (iStarCnt < 5 && iSaveCnt < iStarCnt)
			{
				iLine = LN_LT;
				iSaveCnt = iStarCnt;
			}

			// 오른쪽 -> 왼쪽
			iStarCnt = 0;
			for (int i = 4; i < 20; i += 4)
			{
				if (AiNumber[i] == INT_MAX)
					++iStarCnt;
			}

			if (iStarCnt < 5 && iSaveCnt < iStarCnt)
			{
				iLine = LN_RT;
				iSaveCnt = iStarCnt;
			}


			// 조사를 끝내면 가장 가능성 높은 라인이 iLine에 저장된다
			/////////////////////////////////////////////////////

			if (iLine <= LN_H5)	// 가로
			{
				for (int i = 0; i < 5; ++i)
				{
					if (AiNumber[iLine * 5 + i] != INT_MAX)
					{
						nInput = AiNumber[iLine * 5 + i];
						break;
					}
				}
			}

			else if (iLine <= LN_V5)	// 세로
			{
				for (int i = 0; i < 5; ++i)
				{
					// 세로 iLine 5 ~ 9
					if (AiNumber[i * 5 + (iLine - 5)] != INT_MAX)
					{
						nInput = AiNumber[i * 5 + (iLine - 5)];
						break;
					}
				}
			}

			else if (iLine == LN_LT)	// 왼쪽 -> 오른쪽
			{
				for (int i = 0; i < 25; ++i)
				{
					if (AiNumber[i] != INT_MAX)
					{
						nInput = AiNumber[i];
						break;
					}
				}
			}

			else if (iLine == LN_RT)	// 오른쪽 -> 왼쪽
			{
				for (int i = 4; i < 20; i += 4)
				{
					if (AiNumber[i] != INT_MAX)
					{
						nInput = AiNumber[i];
						break;
					}
				}
			}

			break;
		}

		// AI 숫자 선택 //////////////////////////////////////////
		for (int i = 0; i < 25; ++i)
		{
			if (iNumber[i] == nInput)
			{
				iNumber[i] = INT_MAX;
				break;
			}
		}

		for (int i = 0; i < 25; ++i)
		{
			if (AiNumber[i] == nInput)
			{
				AiNumber[i] = INT_MAX;
				break;
			}
		}

		// 초기화 /////////////////////////////////////////////////
		iBingo = 0;
		iAIBingo = 0;

		int iStar1 = 0, iStar2 = 0;
		int AiStar1 = 0, AiStar2 = 0;

		// 빙고 체크 /////////////////////////////////////////////
		for (int i = 0; i < 5; ++i)
		{
			iStar1 = 0, iStar2 = 0;
			AiStar1 = 0, AiStar2 = 0;

			for (int j = 0; j < 5; ++j)
			{
				// 가로 체크
				if (iNumber[i * 5 + j] == INT_MAX)
					++iStar1;

				// 세로 체크
				if (iNumber[j * 5 + i] == INT_MAX)
					++iStar2;

				// AI 가로 체크
				if (AiNumber[i * 5 + j] == INT_MAX)
					++AiStar1;

				// AI 세로 체크
				if (AiNumber[j * 5 + i] == INT_MAX)
					++AiStar2;
			}

			if (iStar1 == 5)
				++iBingo;
			if (iStar2 == 5)
				++iBingo;
			if (AiStar1 == 5)
				++iAIBingo;
			if (AiStar2 == 5)
				++iAIBingo;
		}

		// 왼쪽상단 -> 오른쪽상단 대각선 ///////////////////////////
		iStar1 = 0;
		AiStar1 = 0;

		for (int i = 0; i < 25; i += 6)
		{
			if (iNumber[i] == INT_MAX)
				++iStar1;

			if (AiNumber[i] == INT_MAX)
				++AiStar1;
		}

		if (iStar1 == 5)
			++iBingo;

		if (AiStar1 == 5)
			++iAIBingo;

		// 오른쪽 상단 -> 왼쪽상단 대각선 //////////////////////////
		iStar1 = 0;
		AiStar1 = 0;
		for (int i = 4; i <= 20; i += 4)
		{
			if (iNumber[i] == INT_MAX)
				++iStar1;

			if (AiNumber[i] == INT_MAX)
				++AiStar1;
		}

		if (iStar1 == 5)
			++iBingo;


		if (AiStar1 == 5)
			++iAIBingo;
	}

	cout << endl;
	cout << "게임종료" << endl;

	return 0;
}
