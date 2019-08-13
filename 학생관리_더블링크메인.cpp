
#include "List.h"

enum MAIN_MENU
{
	MM_NONE,
	MM_INSERT,
	MM_DELETE,
	MM_SEARCH,
	MM_OUTPUT,
	MM_EXIT,
};

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
			Push_Back(&tlist);
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

	DestroyList(&tlist);

	return 0;
}
