// 어소트락 유튜브 강의

#include "pch.h"
#include <ctime>
#include <iostream>
using namespace std;


int main()
{
	int iLotto[45] = { 0, };

	srand((unsigned int)time(NULL));

	// 1 ~ 45까지 숫자를 순서대로 넣는다
	for (int i = 0; i < 45; i++)
	{
		iLotto[i] = i + 1;
	}

	// Shuffle - Swap 알고리즘 활용
	int nTemp, idx1, idx2;

	for (int i = 0; i < 100; i++)
	{
		idx1 = rand() % 45; // 0 ~ 44
		idx2 = rand() % 45; // 0 ~ 44

		nTemp = iLotto[idx1];
		iLotto[idx1] = iLotto[idx2];
		iLotto[idx2] = nTemp;
	}

	cout << "로또 번호 : ";
	for (int i = 0; i < 5; i++)
	{
		cout << iLotto[i] << " ";
	}

	cout << endl;
	cout << "보너스 번호 : " << iLotto[6] << endl;


	return 0;
}
