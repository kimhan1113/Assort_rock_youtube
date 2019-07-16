// 어소트락 유튜브 강의

#include "pch.h"
#include <iostream>
using namespace std;

#define NAME_SIZE		32
#define ADDRESS_SIZE	128
#define PHONE_SIZE		14

#define STUDENT_MAX		10

struct _tagStudent
{
	char	strName[NAME_SIZE];
	char	strAddress[ADDRESS_SIZE];
	char	strPhoneNum[PHONE_SIZE];
	int		iNumber;
	int		iKor;
	int		iEng;
	int		iMath;
	int		iTotal;
	float	iAvg;
};

enum MENU
{
	MENU_NONE,
	MENU_INSERT,
	MENU_DELETE,
	MENU_SEARCH,
	MENU_OUTPUT,
	MENU_EXIT,
};

int main()
{
	_tagStudent tStudentArr[STUDENT_MAX] = {};
	int iStudentCnt = 0;
	int iStdNumber = 0;

	char strName[NAME_SIZE] = {};

	while (true)
	{
		system("cls");

		// 메뉴 출력
		cout << "1. 학생 등록" << endl;
		cout << "2. 학생 삭제" << endl;
		cout << "3. 학생 탐색" << endl;
		cout << "4. 학생 출력" << endl;
		cout << "5. 종료" << endl;
		cout << "메뉴를 선택하세요 : ";

		int iMenu;
		cin >> iMenu;

		// 예외처리 ///////////////////////////////////////////
		if (cin.fail())					// 입력 에러 발생 시 true 반환
		{
			cin.clear();				// 에러 버퍼를 비운다
			cin.ignore(1024, '\n');		// 검색할 버퍼 크기, 찾고자 하는 문자
			continue;
		}
		//////////////////////////////////////////////////////

		// 종료 처리
		if (iMenu == MENU_EXIT)
			break;

		//////////////////////////////////////////////////////

		switch (iMenu)
		{
		case MENU_INSERT:
			system("cls");
			cout << "========== 학생 추가 =========" << endl;

			// 예외처리
			if (iStudentCnt == STUDENT_MAX)
				break;

			cout << "이름 : ";
			cin >> tStudentArr[iStudentCnt].strName;

			// cin.getline()에 엔터가 안들어가도록 처리
			cin.ignore(1024, '\n');

			cout << "주소 : ";
			// 스페이스까지 입력 받고 싶을때 사용되는 함수 cin.getline()
			cin.getline(tStudentArr[iStudentCnt].strAddress, ADDRESS_SIZE);

			cout << "번호 : ";
			cin.getline(tStudentArr[iStudentCnt].strPhoneNum, PHONE_SIZE);
			
			cout << "국어 : ";
			cin >> tStudentArr[iStudentCnt].iKor;

			cout << "영어 : ";
			cin >> tStudentArr[iStudentCnt].iEng;

			cout << "수학 : ";
			cin >> tStudentArr[iStudentCnt].iMath;

			tStudentArr[iStudentCnt].iTotal =
				tStudentArr[iStudentCnt].iKor +
				tStudentArr[iStudentCnt].iEng +
				tStudentArr[iStudentCnt].iMath;

			tStudentArr[iStudentCnt].iAvg =
				tStudentArr[iStudentCnt].iTotal / 3.f;

			tStudentArr[iStudentCnt].iNumber = iStdNumber;
			
			++iStdNumber;
			++iStudentCnt;

			cout << "학생 추가 완료" << endl;  

			break;

		case MENU_DELETE:
			system("cls");
			cout << "========== 학생 삭제 =========" << endl;

			cin.ignore(1024, '\n');
			cout << "삭제할 이름 입력 : ";
			cin.getline(strName, NAME_SIZE);

			for (int i = 0; i < iStudentCnt; ++i)
			{
				if (strcmp(tStudentArr[i].strName, strName) == 0)
				{
					for (int j = i; j < iStudentCnt - 1; ++j)
					{
						tStudentArr[i] = tStudentArr[i + 1];
					}

					--iStudentCnt;

					cout << "학생 삭제 완료" << endl;
					break;
				}
			}
			break;

		case MENU_SEARCH:
			system("cls");
			cout << "========== 학생 탐색 =========" << endl;

			cin.ignore(1024, '\n');
			cout << "탐색할 이름 입력 : ";
			cin.getline(strName, NAME_SIZE);

			for (int i = 0; i < iStudentCnt; ++i)
			{
				if (strcmp(tStudentArr[i].strName, strName) == 0)
				{
					cout << "이름 : " << tStudentArr[i].strName << endl;
					cout << "번호 : " << tStudentArr[i].strPhoneNum << endl;
					cout << "주소 : " << tStudentArr[i].strAddress << endl;
					cout << "학번 : " << tStudentArr[i].iNumber << endl;
					cout << "국어 : " << tStudentArr[i].iKor << endl;
					cout << "영어 : " << tStudentArr[i].iEng << endl;
					cout << "수학 : " << tStudentArr[i].iMath << endl;
					cout << "합계 : " << tStudentArr[i].iTotal << endl;
					cout << "평균 : " << tStudentArr[i].iAvg << endl << endl;
					break;
				}
			}
			break;

		case MENU_OUTPUT:
			system("cls");
			cout << "========== 학생 출력 =========" << endl;

			for (int i = 0; i < iStudentCnt; ++i)
			{
				cout << "이름 : " << tStudentArr[i].strName << endl;
				cout << "번호 : " << tStudentArr[i].strPhoneNum << endl;
				cout << "주소 : " << tStudentArr[i].strAddress << endl;
				cout << "학번 : " << tStudentArr[i].iNumber << endl;
				cout << "국어 : " << tStudentArr[i].iKor << endl;
				cout << "영어 : " << tStudentArr[i].iEng << endl;
				cout << "수학 : " << tStudentArr[i].iMath << endl;
				cout << "합계 : " << tStudentArr[i].iTotal << endl;
				cout << "평균 : " << tStudentArr[i].iAvg << endl << endl;
			}
			break;

		default:
			cout << "메뉴를 잘못 선택했습니다" << endl;
			break;
		}

		system("pause");
	}

	return 0;
}
