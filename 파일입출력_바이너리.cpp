// 어소트락 유튜브 강의

#include <iostream>
using namespace std;

#define NAME_SIZE	32
#define STUDENT_MAX	3

typedef struct _tagStudent
{
	char strName[NAME_SIZE];
	int nTotal;
} STUDENT, * PSTUDENT;

int main()
{
	/* 파일 쓰기
	STUDENT tStudent[STUDENT_MAX] = {};

	for(int i = 0; i < STUDENT_MAX; ++i)
	{
		cout << "이름 : ";
		cin >> tStudent[i].strName;

		cout << "점수 : ";
		cin >> tStudent[i].nTotal;
	}

	int iStudentCnt = STUDENT_MAX;

	FILE* pFile = NULL;

	fopen_s(&pFile, "Student.std", "wb");

	if (pFile)
	{
		fwrite(&iStudentCnt, 4, 1, pFile);

		for (int i = 0; i < iStudentCnt; ++i)
		{
			fwrite(&tStudent[i], sizeof(STUDENT), 1, pFile);
		}

		fclose(pFile);
	}
	*/

	// 파일 읽기
	STUDENT tStudent[STUDENT_MAX] = {};
	int iStudentCnt = 0;

	FILE* pFile = NULL;

	fopen_s(&pFile, "Student.std", "rb");

	if (pFile)
	{
		// 저장할 때 학생 수를 먼저 저장했기 때문에 학생 수부터 읽어온다
		fread(&iStudentCnt, 4, 1, pFile);

		for (int i = 0; i < iStudentCnt; ++i)
		{
			fread(&tStudent[i], sizeof(STUDENT), 1, pFile);
		}

		fclose(pFile);
	}

	for (int i = 0; i < iStudentCnt; ++i)
	{
		cout << "이름 : " << tStudent[i].strName << "\t";
		cout << "점수 : " << tStudent[i].nTotal;
		cout << endl;
	}

	return 0;
}
