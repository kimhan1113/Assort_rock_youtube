// 어소트락 유튜브 강의

#include "List.h"

void InitList(PLIST pList)
{
	pList->iSize = 0;

	pList->pBegin = new NODE;
	pList->pEnd = new NODE;

	pList->pBegin->pNext = pList->pEnd;
	pList->pEnd->pPrev = pList->pBegin;

	pList->pEnd->pNext = NULL;
	pList->pBegin->pPrev = NULL;
}

void DestroyList(PLIST pList)
{
	PNODE pNode = pList->pBegin;

	while (pNode != NULL)
	{
		PNODE pNext = pNode->pNext;
		delete pNode;
		pNode = pNext;
	}

	pList->iSize = 0;
	pList->pBegin = NULL;
	pList->pEnd = NULL;
}

void Push_Back(PLIST pList)
{
	system("cls");
	cout << " ============ 학생 추가 =============" << endl;
	STUDENT tStudent = {};

	cout << "이름 : ";
	InputString(tStudent.strName, NAME_SIZE);

	cout << "학번 : ";
	tStudent.iNumber = InputInt();

	cout << "국어 : ";
	tStudent.iKor = InputInt();

	cout << "영어 : ";
	tStudent.iEng = InputInt();

	cout << "수학 : ";
	tStudent.iMath = InputInt();

	tStudent.nTotal = tStudent.iKor + tStudent.iEng + tStudent.iMath;
	tStudent.fAvg = tStudent.nTotal / 3.f;

	PNODE pNode = new NODE;

	pNode->tStudent = tStudent;

	PNODE pPrev = pList->pEnd->pPrev;

	pPrev->pNext = pNode;
	pNode->pPrev = pPrev;

	pNode->pNext = pList->pEnd;
	pList->pEnd->pPrev = pNode;

	++pList->iSize;
}

void Push_Front(PLIST pLsit)
{
	
}

void Output(PLIST pList)
{
	int iMenu;

	while (true)
	{
		system("cls");
		cout << " ============ 학생 출력 =============" << endl;
		cout << "1. 정방향 출력" << endl;
		cout << "2. 역방향 출력" << endl;
		cout << "메뉴를 선택하세요 : ";

		iMenu = InputInt();

		if (iMenu > OT_NONE && iMenu <= OT_INVERSE)
			break;
	}

	PNODE pNode = NULL;

	switch (iMenu)
	{
	case OT_OUTPUT:
		pNode = pList->pBegin->pNext;

		while (pNode != pList->pEnd)
		{
			OutputStudent(&pNode->tStudent);
			pNode = pNode->pNext;
		}
		break;

	case OT_INVERSE:
		pNode = pList->pEnd->pPrev;

		while (pNode != pList->pBegin)
		{
			OutputStudent(&pNode->tStudent);
			pNode = pNode->pPrev;
		}
		break;
	}
	cout << "학생 수 : " << pList->iSize << endl;
	system("pause");
}

void Search(PLIST pList)
{
	system("cls");
	cout << " ============ 학생 탐색 =============" << endl;
	cout << "탐색할 이름을 입력하세요 : ";

	char strName[NAME_SIZE] = {};
	InputString(strName, NAME_SIZE);

	PNODE pNode = pList->pBegin->pNext;

	while (pNode != pList->pEnd)
	{
		if (strcmp(pNode->tStudent.strName, strName) == 0)
		{
			OutputStudent(&pNode->tStudent);
			system("pause");
			return;
		}

		pNode = pNode->pNext;
	}

	cout << "일치하는 학생이 없습니다." << endl << endl;
	system("pause");
}

void Delete(PLIST pList)
{
	system("cls");
	cout << " ============ 학생 삭제 =============" << endl;
	cout << "삭제할 이름을 입력하세요 : ";

	char strName[NAME_SIZE] = {};
	InputString(strName, NAME_SIZE);

	PNODE pNode = pList->pBegin->pNext;


	while (pNode != pList->pEnd)
	{
		if (strcmp(pNode->tStudent.strName, strName) == 0)
		{
			cout << strName << " 학생 삭제" << endl;

			pNode->pPrev->pNext = pNode->pNext;
			pNode->pNext->pPrev = pNode->pPrev;
			delete pNode;

			cout << strName << " 학생 삭제 완료" << endl << endl;
			--pList->iSize;
			system("pause");
			return;
		}

		
		pNode = pNode->pNext;
	}
	cout << "해당 학생이 존재하지 않습니다" << endl << endl;
	system("pause");
}

void Sort(PLIST pList)
{
	system("cls");
	cout << " ============ 학생 정렬 =============" << endl;
	cout << "1. 학점 기준" << endl;
	cout << "2. 평균 기준" << endl;
	cout << "메뉴를 선택하세요 : ";
	int iInput = InputInt();

	if (iInput <= ST_NONE || iInput > ST_AVG)
	{
		cout << "잘못 선택" << endl;
		system("pause");
		return;
	}

	cout << endl << endl;
	cout << "1. 오름차순" << endl;
	cout << "2. 내림차순" << endl;
	cout << "메뉴를 선택하세요 : ";
	int iOption = InputInt();

	if (iOption <= SO_NONE || iOption > SO_DESCRIVE)
	{
		cout << "잘못 선택" << endl;
		system("pause");
		return;
	}

	PNODE pFirst = pList->pBegin->pNext;
	PNODE pSecond = pFirst->pNext;

	// Frist는 End 이전 노드와 같아지게 되면
	// 더 이상 비교할 노드가 없어지므로 종료
	while (pFirst != pList->pEnd->pPrev)
	{
		// Seconde는 무조건 First 노드 다음 노드부터 검사
		pSecond = pFirst->pNext;

		// Second는 End 이전까지 반복
		// End가 아닐 동안 반복
		while (pSecond != pList->pEnd)
		{
			bool bSWap = false;

			switch (iInput)
			{
			case ST_NUMBER:
				switch (iOption)
				{
				case SO_CRIVE:
					if (pFirst->tStudent.iNumber > pSecond->tStudent.iNumber)
						bSWap = true;
					break;
				case SO_DESCRIVE:
					if (pFirst->tStudent.iNumber < pSecond->tStudent.iNumber)
						bSWap = true;
					break;
				}
				
			case ST_AVG:
				switch (iOption)
				{
				case SO_CRIVE:
					if (pFirst->tStudent.fAvg > pSecond->tStudent.fAvg)
						bSWap = true;
					break;
				case SO_DESCRIVE:
					if (pFirst->tStudent.fAvg < pSecond->tStudent.fAvg)
						bSWap = true;
					break;
				}
			}

			if (bSWap)
			{
				// First 노드의 이전과 다음 노트 저장
				PNODE pFirstPrev = pFirst->pPrev;
				PNODE pFirstNext = pFirst->pNext;

				// Second 노드의 이전과 다음 노트 저장
				PNODE pSecondPrev = pSecond->pPrev;
				PNODE pSecondNext = pSecond->pNext;

				pFirstPrev->pNext = pSecond;
				pSecond->pPrev = pFirstPrev;

				// 바꾸려는 노드가 붙어 있지 않은 경우
				if (pSecond != pFirstNext)
				{
					pFirstNext->pPrev = pSecond;
					pSecond->pNext = pFirstNext;

					pSecondPrev->pNext = pFirst;
					pFirst->pPrev = pSecondPrev;
				}

				// 바꾸려는 노드가 붙어 있는 경우
				else
				{
					pSecond->pNext = pFirst;
					pFirst->pPrev = pSecond;
				}

				pSecondNext->pPrev = pFirst;
				pFirst->pNext = pSecondNext;

				PNODE pTemp = pFirst;
				pFirst = pSecond;
				pSecond = pTemp;
			}
			pSecond = pSecond->pNext;
		}
		pFirst = pFirst->pNext;
	}
	cout << "정렬 완료" << endl;
}
