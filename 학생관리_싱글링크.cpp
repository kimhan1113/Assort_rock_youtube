// 어소트락 유튜브 강의

#include "pch.h"
#include <iostream>
using namespace std;

#define NAME_SIZE	32

enum MAIN_MENU
{
	MM_NONE,
	MM_INSERT,
	MM_DELETE,
	MM_SEARCH,
	MM_OUTPUT,
	MM_EXIT,
};

typedef struct _tagStudent
{
	char	strName[NAME_SIZE];
	int		iNumber;
	int		iKor;
	int		iEng;
	int		iMath;
	int		nTotal;
	float	fAvg;
} STUDENT, *PSTUDENT;

typedef struct _tagNode
{
	STUDENT		tStudent;
	_tagNode*	pNext;
} NODE, *PNODE;

typedef struct _tagList
{
	PNODE		pBegin;
	PNODE		pEnd;
	int			iSize;
}LIST, *PLIST;

////////////////////////////////////////////

void InitList(LIST* pList)
{
	pList->pBegin = NULL;
	pList->pEnd = NULL;
	pList->iSize = 0;
}

int InputInt()
{
	int iInput;
	cin >> iInput;

	if (cin.fail())
	{
		cin.clear();
		cin.ignore(1024, '\n');
		return INT_MAX;
	}

	return iInput;
}

void InputString(char* pString, int iSize)
{
	cin.clear();
	cin.ignore(1024, '\n');

	cin.getline(pString, iSize - 1);
}

int OutputMenu()
{
	system("cls");
	cout << " 학생 관리 목록 " << endl;
	cout << "1. 학생 추가" << endl;
	cout << "2. 학생 삭제" << endl;
	cout << "3. 학생 검색" << endl;
	cout << "4. 학생 출력" << endl;
	cout << "5. 종료" << endl;
	cout << "메뉴를 선택하세요 : ";
	
	int iInput = InputInt();

	if (iInput <= MM_NONE || iInput > MM_EXIT)
		return MM_NONE;

	return iInput;
}

void Insert(PLIST pList)
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


	// 노드 생성
	PNODE pNode = new NODE;

	pNode->pNext = NULL;
	pNode->tStudent = tStudent;

	if (pList->pBegin == NULL)
		pList->pBegin = pNode;

	else
		pList->pEnd->pNext = pNode;

	pList->pEnd = pNode;

	++pList->iSize;
}

void ClearList(PLIST pList)
{
	PNODE pNode = pList->pBegin;

	while (pNode != NULL)
	{
		PNODE pNext = pNode->pNext;
		delete pNode;
		pNode = pNext;
	}

	pList->pBegin = NULL;
	pList->pEnd = NULL;
	pList->iSize = 0;
}

void OutputStudent(const PSTUDENT pStudent)
{
	cout << "이름 : " << pStudent->strName << endl;
	cout << "학번 : " << pStudent->iNumber << endl;
	cout << "국어 : " << pStudent->iKor << endl;
	cout << "영어 : " << pStudent->iEng << endl;
	cout << "수학 : " << pStudent->iMath << endl;
	cout << "총점 : " << pStudent->nTotal << endl;
	cout << "평균 : " << pStudent->fAvg << endl;
	cout << endl << endl;
}

void Output(PLIST pList)
{
	system("cls");
	cout << " ============ 학생 출력 =============" << endl;

	PNODE pNode = pList->pBegin;

	while (pNode != NULL)
	{
		OutputStudent(&pNode->tStudent);
		pNode = pNode->pNext;
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

	PNODE pNode = pList->pBegin;

	while (pNode != NULL)
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

	PNODE pNode = pList->pBegin;
	PNODE pPrev = NULL;

	while (pNode != NULL)
	{
		if (strcmp(pNode->tStudent.strName, strName) == 0)
		{
			cout << strName << " 학생 삭제" << endl;
			
			PNODE pNext = pNode->pNext;

			if (pPrev == NULL)
			{
				delete pNode;
				pList->pBegin = pNext;

				if (pNext == NULL)
					pList->pEnd = NULL;
			}

			else
			{
				delete pNode;
				pPrev->pNext = pNext;

				if (pNext == NULL)
					pList->pEnd = pPrev;
			}

			cout << strName << " 학생 삭제 완료" << endl << endl;
			--pList->iSize;
			system("pause");
			return;
		}

		pPrev = pNode;
		pNode = pNode->pNext;
	}
	cout << "해당 학생이 존재하지 않습니다" << endl << endl;
	system("pause");
}

int main()
{
	LIST tlist;

	InitList(&tlist);

	while (true)
	{
		int iMenu = OutputMenu();

		if (iMenu == MM_EXIT)
			break;

		switch (iMenu)
		{
		case MM_INSERT:
			Insert(&tlist);
			break;

		case MM_DELETE:
			Delete(&tlist);
			break;

		case MM_SEARCH:
			Search(&tlist);
			break;

		case MM_OUTPUT:
			Output(&tlist);
			break;

		}
	}

	ClearList(&tlist);

	return 0;
}
