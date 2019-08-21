#include <iostream>
using namespace std;

enum MAP_TYPE
{
	MT_EASY,
	MT_NOMAL,
	MT_HARD,
	MT_END
};

enum MAIN_MENU
{
	MM_NONE,
	MM_ADD,
	MM_LOAD,
	MM_SAVE,
	MM_OUTPUT,
	MM_EXIT
};

#define NAME_SIZE			32
#define ITEM_DESC_LENGTH	512
#define INVENTORY_MAX		20
#define STORE_WEAPON_MAX	3
#define STORE_ARMOR_MAX		3
#define LEVEL_MAX			10

struct _tagMonster
{
	char	strName[NAME_SIZE];

	int		iAttackMin;
	int		iAttackMax;
	int		iArmorMin;
	int		iArmorMax;

	int		iHP;
	int		iHPMax;
	int		iMP;
	int		iMPMax;

	int		iLevel;
	int		iExp;
	int		iGoldMin;
	int		iGoldMax;
};

int inputInt()
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

void AddMonster(_tagMonster* pMonsterArr)
{
	int iMap = 0;

	while (true)
	{
		system("cls");
		cout << "1. Easy" << endl;
		cout << "2. Nomal" << endl;
		cout << "3. Hard" << endl;
		cout << "4. Exit" << endl;
		cout << "난이도를 선택하세요 : ";
		iMap = inputInt();

		if (iMap == 4)
			return;
		else if (iMap < 1 || iMap > 4)
			continue;

		--iMap;
		break;
	}

	cin.clear();
	cin.ignore(1024, '\n');

	cout << "이름 : ";
	cin.getline(pMonsterArr[iMap].strName, NAME_SIZE - 1);

	cout << "최소 공격력 : ";
	pMonsterArr[iMap].iAttackMin = inputInt();	// 최소 공격력
	cout << "최대 공격력 : ";
	pMonsterArr[iMap].iAttackMax = inputInt();	// 최대 공격력
	
	cout << "최소 방어력 : ";
	pMonsterArr[iMap].iArmorMin = inputInt();	// 최소 방어력
	cout << "최대 방어력 : ";
	pMonsterArr[iMap].iArmorMax = inputInt();	// 최대 방어력
	
	cout << "HP : ";
	pMonsterArr[iMap].iHP = inputInt();					// HP
	pMonsterArr[iMap].iHPMax = pMonsterArr[iMap].iHP;	// HP
	
	cout << "MP : ";
	pMonsterArr[iMap].iMP = inputInt();					// MP
	pMonsterArr[iMap].iMPMax = pMonsterArr[iMap].iMP;	// MP

	cout << "레벨 : ";
	pMonsterArr[iMap].iLevel = inputInt();

	cout << "경험치 : ";
	pMonsterArr[iMap].iExp = inputInt();

	cout << "획득 최소 골드 : ";
	pMonsterArr[iMap].iGoldMin = inputInt();

	cout << "획득 최대 골드 : ";
	pMonsterArr[iMap].iGoldMax = inputInt();

	cout << "몬스터 추가 완료" << endl;
	system("pause");
}

bool SaveMonster(_tagMonster* pMonsterArr)
{
	FILE* pFile = NULL;

	fopen_s(&pFile, "Monster.mst", "wb");

	if (pFile)
	{
		fwrite(pMonsterArr, sizeof(_tagMonster), MT_END, pFile);
		fclose(pFile);
		return true;
	}

	return false;
}

bool LoadMonster(_tagMonster* pMonsterArr)
{
	FILE* pFile = NULL;

	fopen_s(&pFile, "Monster.mst", "rb");

	if (pFile)
	{
		fread(pMonsterArr, sizeof(_tagMonster), MT_END, pFile);
		fclose(pFile);
		return true;
	}

	return false;
}

void OutputMonster(_tagMonster* pMonster)
{
	cout << " ================ Monster =======================" << endl;
	cout << "이름 : " << pMonster->strName << endl;
	cout << "레벨: " << pMonster->iLevel << endl << endl;

	cout << "공격력 : " << pMonster->iAttackMin << " - "
		<< pMonster->iAttackMax << endl;
	cout << "방어력 : " << pMonster->iArmorMin << " - "
		<< pMonster->iArmorMax << endl << endl;;
	cout << "HP : " << pMonster->iHP << " / "
		<< pMonster->iHPMax << endl;
	cout << "MP : " << pMonster->iMP << " / "
		<< pMonster->iMPMax << endl << endl;
	cout << "획득 경험치 : " << pMonster->iExp
		<< "\t획득 골드 : " << pMonster->iGoldMin << " - " << pMonster->iGoldMax << endl << endl;

}

void Output(_tagMonster* pMonsterArr)
{
	for (int i = 0; i < MT_END; ++i)
	{
		OutputMonster(&pMonsterArr[i]);
	}
	system("pause");
}

int main()
{
	_tagMonster tMonster[MT_END] = {};

	while (true)
	{
		system("cls");
		cout << "1. 몬스터 추가" << endl;
		cout << "2. 읽어오기 " << endl;
		cout << "3. 저장 " << endl;
		cout << "4. 몬스터 출력" << endl;
		cout << "5. 종료 " << endl;
		cout << "메뉴를 선택하세요: " << endl;
		int iMenu = inputInt();

		if (iMenu == MM_EXIT)
			break;

		switch (iMenu)
		{
		case MM_ADD:
			AddMonster(tMonster);
			break;

		case MM_LOAD:
			LoadMonster(tMonster);
			break;

		case MM_SAVE:
			SaveMonster(tMonster);
			break;

		case MM_OUTPUT:
			Output(tMonster);
			break;
		}
	}
	SaveMonster(tMonster);
	return 0;
}

/*
	pMonsterArr[0] = CreateMonster("고블린", 20, 30, 2, 5,
		100, 10, 1, 1000, 500, 1500);
	pMonsterArr[1] = CreateMonster("트롤", 80, 130, 60, 90,
		2000, 100, 5, 7000, 6000, 8000);
	pMonsterArr[2] = CreateMonster("드래곤", 250, 500, 200, 400,
		30000, 20000, 10, 30000, 20000, 50000);
*/
