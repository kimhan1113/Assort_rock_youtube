#include <iostream>
using namespace std;

void Test(int** pp)
{
	*pp = new int;
}

int main()
{
	int* p = NULL;
	Test(&p); // == (p = new int); 


	
	FILE* pFile = NULL;

	/*  파일쓰기
	// 1번 인자 : 파일 이중포인터
	// 2번 인자 : 파일 경로
	// 3번 인자 : 파일 모드
	fopen_s(&pFile, "textfile.txt", "wt");

	if (pFile != NULL)
	{
		// fwrite(), fread()
		// fputs(), fgets()

		const char* pText = "Test_Text";
		// 1번 인자 : 메모리 주소
		// 2번 인자 : 변수 타입의 메모리 크기
		// 3번 인자 : 값의 갯수
		// 4번 인자 : 파일 스트림
		fwrite(pText, 1, 4, pFile);
		fclose(pFile);
	}
*/
	// 파일 읽기
	fopen_s(&pFile, "textfile.txt", "rt");

	if (pFile != NULL)
	{
		char strText[32] = {};

		// 1번 인자 : 메모리 주소
		// 2번 인자 : 변수 타입의 메모리 크기
		// 3번 인자 : 값의 갯수
		// 4번 인자 : 파일 스트림
		fread(strText, 1, 4, pFile);
		
		cout << strText << endl;
		
		fclose(pFile);
	}

	return 0;
}
