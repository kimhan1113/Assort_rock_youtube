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

void SetNumber(int*);				// 숫자 초기화
void Shuffle(int*);					// 숫자 섞기
AI_MODE SelectAiMode();				// 난이도 선택
void OutputNumber(int*, int);		// 
bool ChangeNumber(int*, int);		//
int SelectAINumber(int*, AI_MODE);

int BingoCounting(int*);			// 빙고 카운터
int BingoCountingH(int*);			// 가로 빙고
int BingoCountingV(int*);			// 세로 빙고
int BingoCountingLTD(int*);			// 왼쪽 상단 대각선 빙고
int BingoCountingRTD(int*);			// 오른쪽 상단 대각선 빙고


int main()
{
	srand((unsigned int)time(0));

	int iNumber[25] = { 0, };
	int AiNumber[25] = { 0, };

	// 숫자 초기화 및 숫자 섞기 ///////////////////////////
	SetNumber(iNumber);
	SetNumber(AiNumber);

	Shuffle(iNumber);
	Shuffle(AiNumber);

	// AI 난이도 선택 ///////////////////////////////////
	int iBingo = 0, iAIBingo = 0;
	AI_MODE eiAiMode = SelectAiMode();

	//////////////////////////////////////////////////// 

	while (true)
	{
		system("cls");

		// 빙고판 출력 //////////////////////////////////////
		cout << " ============= Player ============= " << endl;
		OutputNumber(iNumber, iBingo);
		
		cout << " ============= AI ============= " << endl;

		switch (eiAiMode)
		{
		case AM_EASY:
			cout << "AIMODE : EASY ***** " << endl;
			break;

		case AM_HARD:
			cout << "AIMODE : HARD ***** " << endl;
			break;
		}

		OutputNumber(AiNumber, iAIBingo);
		//////////////////////////////////////////////////// 

		// 승리 조건 ///////////////////////////////////////
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

		// 숫자 입력 ////////////////////////////////////////
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
		bool bAcc = ChangeNumber(iNumber, nInput);

		if (bAcc)		// true일 경우 중복 숫자입력으로 다시 입력
			continue;

		ChangeNumber(AiNumber, nInput);
		/////////////////////////////////////////////////////

		// AI모드에 맞춰 AI가 숫자 선택
		nInput = SelectAINumber(AiNumber, eiAiMode);

		// AI 숫자 선택 //////////////////////////////////////
		ChangeNumber(iNumber, nInput);
		ChangeNumber(AiNumber, nInput);

		// 초기화 ////////////////////////////////////////////
		iBingo = BingoCounting(iNumber);
		iAIBingo = BingoCounting(AiNumber);
	}

	cout << endl;
	cout << "게임종료" << endl;

	return 0;
}

// 숫자 초기화
void SetNumber(int* pArray)
{
	for (int i = 0; i < 25; ++i)
	{
		pArray[i] = i + 1;
	}
}

// 숫자 섞음
void Shuffle(int* pArray)
{
	int nTmp, idx1, idx2;

	for (int i = 0; i < 100; ++i)
	{
		idx1 = rand() % 25;
		idx2 = rand() % 25;

		nTmp = pArray[idx1];
		pArray[idx1] = pArray[idx2];
		pArray[idx2] = nTmp;
	}
}

// 난이도 선택
AI_MODE SelectAiMode()
{
	int iAiMode;

	while (true)
	{
		system("cls");

		cout << "1.Easy" << endl;
		cout << "2.Hard" << endl;
		cout << "AI 모드를 선택하세요 : ";

		cin >> iAiMode;

		if (iAiMode >= AM_EASY && iAiMode <= AM_HARD)
			break;
	}

	return (AI_MODE)iAiMode;
} 

// 화면 출력 및 빙고 라인 
void OutputNumber(int* pArray, int iBingo)
{
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			if (pArray[i * 5 + j] == INT_MAX)
				cout << "*\t";
			else
				cout << pArray[i * 5 + j] << "\t";
		}
		cout << endl;
	}


	cout << "Bingo Line : " << iBingo << endl << endl;
}

// *로 변경
bool ChangeNumber(int* pArray, int iInput)
{
	for (int i = 0; i < 25; ++i)
	{
		if (iInput == pArray[i])
		{
			// 숫자 *로 변경
			pArray[i] = INT_MAX;
		
			return false;
		}
	}
	 
	return true;	// 중복 숫자 입력
}

// AI모드에 맞춰 AI가 숫자 선택
int SelectAINumber(int* pArray, AI_MODE eMode)
{
	int iNoneSelect[25] = {};	// 선택 안된 목록 배열 생성
	int iNoneSelCnt = 0;		// 선택 안된 숫자 개수 저장

	switch (eMode)
	{
//////////////////////////////////////////////////////////////
	case AM_EASY:
		// 선택 안된 숫자 배열 구성 ///////////////////////////
		iNoneSelCnt = 0;
		for (int i = 0; i < 25; ++i)
		{
			if (pArray[i] != INT_MAX)
			{
				iNoneSelect[iNoneSelCnt] = pArray[i];
				++iNoneSelCnt;
			}
		}

		// 선택 안된 숫자 중 하나를 nInput에 입력
		return iNoneSelect[rand() % iNoneSelCnt];

//////////////////////////////////////////////////////////////
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
				if (pArray[i * 5 + j] == INT_MAX)
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
				if (pArray[j * 5 + i] == INT_MAX)
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
			if (pArray[i] == INT_MAX)
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
			if (pArray[i] == INT_MAX)
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
				if (pArray[iLine * 5 + i] != INT_MAX)
				{
					return pArray[iLine * 5 + i];
				}
			}
		}

		else if (iLine <= LN_V5)	// 세로
		{
			for (int i = 0; i < 5; ++i)
			{
				// 세로 iLine 5 ~ 9
				if (pArray[i * 5 + (iLine - 5)] != INT_MAX)
				{
					return pArray[i * 5 + (iLine - 5)];
				}
			}
		}

		else if (iLine == LN_LT)	// 왼쪽 -> 오른쪽
		{
			for (int i = 0; i < 25; ++i)
			{
				if (pArray[i] != INT_MAX)
				{
					return pArray[i];
				}
			}
		}

		else if (iLine == LN_RT)	// 오른쪽 -> 왼쪽
		{
			for (int i = 4; i < 20; i += 4)
			{
				if (pArray[i] != INT_MAX)
				{
					return pArray[i];
				}
			}
		}

		break;
	} 

	return -1;	// 오류
}

int BingoCounting(int* pArray)
{	
	int iBingo = 0;

	iBingo += BingoCountingH(pArray);		// 가로줄 체크
	iBingo += BingoCountingV(pArray);		// 세로줄 체크
	iBingo += BingoCountingLTD(pArray);		// 왼상 대각선
	iBingo += BingoCountingRTD(pArray);		// 오상 대각선

	return iBingo;   
}

// 가로 체크
int BingoCountingH(int* pArray)
{
	int iStar1 = 0, iBingo = 0;

	for (int i = 0; i < 5; ++i)
	{
		iStar1 = 0;

		for (int j = 0; j < 5; ++j)
		{
			if (pArray[i * 5 + j] == INT_MAX)
				++iStar1;
		}

		if (iStar1 == 5)
			++iBingo;
	}

	return iBingo;
}

// 세로 체크
int BingoCountingV(int* pArray)
{
	int iStar1 = 0, iBingo = 0;

	for (int i = 0; i < 5; ++i)
	{
		iStar1 = 0;

		for (int j = 0; j < 5; ++j)
		{
			if (pArray[j * 5 + i] == INT_MAX)
				++iStar1;
		}

		if (iStar1 == 5)
			++iBingo;
	}

	return iBingo;
}

// 왼쪽상단 -> 오른쪽상단 대각선
int BingoCountingLTD(int* pArray)
{
	int iStar1 = 0, iBingo = 0;

	for (int i = 0; i < 25; i += 6)
	{
		if (pArray[i] == INT_MAX)
			++iStar1;
	}

	if (iStar1 == 5)
		++iBingo;

	return iBingo;
}

// 오른쪽상단 -> 왼쪽상단 대각선
int BingoCountingRTD(int* pArray)
{
	int iStar1 = 0, iBingo = 0;

	for (int i = 4; i < 21; i += 4)
	{
		if (pArray[i] == INT_MAX)
			++iStar1;
	}

	if (iStar1 == 5)
		++iBingo;

	return iBingo;
}
