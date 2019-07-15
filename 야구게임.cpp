// 어소트락 유튜브 강의

#include "pch.h"
#include "time.h"
#include <iostream>
using namespace std;

int main()
{
	srand((unsigned int)time(0));
	int iNumber[9] = {};

	// 1~9까지 숫자를 설정한다
	for (int i = 0; i < 9; ++i)
	{
		iNumber[i] = i + 1;
	}

	// 설정된 숫자를 섞어준다
	int nTmp, idx1, idx2;

	for (int i = 0; i < 100; i++)
	{
		idx1 = rand() % 9;
		idx2 = rand() % 9;

		nTmp = iNumber[idx1];
		iNumber[idx1] = iNumber[idx2];
		iNumber[idx2] = nTmp;
	}

	cout << " * * * " << endl;
	
	
	// 숫자 보기
	//cout << iNumber[0] << '\t' << iNumber[1] << "\t" << iNumber[2] << endl;
	cout << endl;

	int iStrike = 0, iBall = 0;
	int iInput[3];
	int nCnt = 1;

	while (true)
	{
		cout << nCnt << "회" << endl;
		nCnt++;

		cout << "1~9 사이의 숫자 중 숫자 3개를 입력하세요(0: END) : ";
		cin >> iInput[0] >> iInput[1] >> iInput[2];

		// 강제종료 처리
		if (iInput[0] == 0 || iInput[1] == 0 || iInput[2] == 0)
			break;

		// 예외 처리
		else if (iInput[0] < 0 || iInput[0] > 9 ||
			iInput[1] < 0 || iInput[1] > 9 ||
			iInput[2] < 0 || iInput[2] > 9)
		{
			cout << "잘못된 숫자를 입력하셨습니다" << endl;
			continue;
		}

		// 중복 숫자일 경우
		else if (iInput[0] == iInput[1] ||
			iInput[0] == iInput[2] ||
			iInput[1] == iInput[2])
		{
			cout << "중복된 숫자를 입력하였습니다" << endl;
			continue;
		}

		// 초기화
		iStrike = iBall = 0;

		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				if (iNumber[i] == iInput[j])
				{
					// 자리 수 같은거 찾아내기
					if (i == j)
						++iStrike;
					else
						++iBall;
					break;
				}
			}
		}

		if (iStrike == 3)
		{
			cout << "숫자를 모두 맞췄습니다" << endl;
			break;
		}
		
		else if (iStrike == 0 && iBall == 0)
			cout << "OUT" << endl;
		
		else
		{
			cout << iStrike << " 스트라이크 " << iBall << " 볼" << endl;
		}
		cout << endl;
	}

	return 0;
}
