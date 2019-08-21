#include "pch.h"
#include <iostream>
#include <time.h>

using namespace std;

enum GAME_MODE
{
	GM_NONE,
	GM_NEW,
	GM_LOAD,
	GM_END
};

enum MAIN_MENU
{
	MM_NONE,
	MM_MAP,
	MM_STORE,
	MM_INVENTORY,
	MM_EXIT
};

enum MAP_TYPE
{
	MT_NONE,
	MT_EASY,
	MT_NOMAL,
	MT_HARD,
	MT_BACK
};

enum JOB
{
	JOB_NONE,
	JOB_KNIGHT,
	JOB_ARCHER,
	JOB_WIZARD,
	JOB_END
};

enum BATTLE
{
	BATTLE_NONE,
	BATTLE_ATTACK,
	BATTLE_BACK
};

enum ITEM_TYPE
{
	IT_NONE,
	IT_WEAPON,
	IT_ARMOR,
	IT_BACK
};

enum EQUIP
{
	EQ_WEAPON,
	EQ_ARMOR,
	EQ_MAX
};

enum STORE_MENU
{
	SM_NONE,
	SM_WEAPON,
	SM_ARMOR,
	SM_BACK
};

#define NAME_SIZE			32
#define ITEM_DESC_LENGTH	512
#define INVENTORY_MAX		20
#define STORE_WEAPON_MAX	3
#define STORE_ARMOR_MAX		3
#define LEVEL_MAX			10

struct _tagitem
{
	char strName[NAME_SIZE];
	char strTypeName[NAME_SIZE];
	ITEM_TYPE eType;

	int iMin;
	int iMax;
	int iPrice;
	int iSell;
	char strDesc[ITEM_DESC_LENGTH];
};

struct _tagInventory
{
	_tagitem	tItem[INVENTORY_MAX];
	int			iGold;
	int			tItemCnt;
};

struct _tagPlayer
{
	char	strName[NAME_SIZE];
	char	strJobName[NAME_SIZE];
	JOB		eJob;

	int		iAttackMin;
	int		iAttackMax;
	int		iArmorMin;
	int		iArmorMax;

	int		iHP;
	int		iHPMax;
	int		iMP;
	int		iMPMax;
	int		iExp;
	int		iLevel;

	_tagitem	  tEquip[EQ_MAX];
	bool		  bEquip[EQ_MAX];
	_tagInventory tInventory;
};

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

struct _tagLevelUpStatus
{
	int iAttackMin;
	int	iAttackMax;
	int	iArmorMin;
	int	iArmorMax;
	int	iHPMin;
	int	iHPMax;
	int	iMPMin;
	int	iMPMax;
};

// 레벨업에 필요한 경험치 목록 
const int	g_iLevelUpExp[LEVEL_MAX] = { 4000, 10000, 20000, 35000, 50000, 70000, 100000, 150000, 200000, 400000 };
_tagLevelUpStatus g_tLvUpTable[JOB_END - 1] = {};


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

// 메인 메뉴 표시
int OutPutMainMenu()
{
	system("cls");

	cout << " ================ 로비 =======================" << endl;
	cout << "1. 맵" << endl;
	cout << "2. 상점" << endl;
	cout << "3. 가방" << endl;
	cout << "4. 종료" << endl;
	cout << "메뉴를 선택하세요 : ";

	int iMenu = inputInt();

	if (iMenu == INT_MAX || iMenu <= MM_NONE || iMenu > MM_EXIT)
		return MM_NONE;

	return iMenu;
}

int OutPutMapMenu()
{
	system("cls");
	cout << " ================ 맵 =======================" << endl;
	cout << "1. 쉬움" << endl;
	cout << "2. 보통" << endl;
	cout << "3. 어려움" << endl;
	cout << "4. 뒤로가기" << endl;

	int iMenu = inputInt();

	if (iMenu == INT_MAX || iMenu <= MT_NONE || iMenu > MT_BACK)
		return MT_NONE;

	return iMenu;
}

// 맵에 관련된 함수
void RunMap()
{
	bool bLoop = true;

	while (true)
	{
		switch (OutPutMapMenu())
		{
		case MT_EASY:
			break;
		case MT_NOMAL:
			break;
		case MT_HARD:
			break;
		case MT_BACK:
			bLoop = false;
			break;
		}
	}
}

int SelectJob()
{
	int iJob = JOB_NONE;
	while (iJob == JOB_NONE)
	{
		system("cls");

		cout << "1. 기사" << endl;
		cout << "2. 궁수" << endl;
		cout << "3. 마법사" << endl;
		cout << "직업을 선택하세요 : ";

		iJob = inputInt();

		// 예외 처리
		if (iJob <= JOB_NONE || iJob >= JOB_END)
			iJob = JOB_NONE;
	}

	return iJob;
}

void SetPlayer(_tagPlayer * pPlayer)
{
	system("cls");
	cin.clear();
	cin.ignore(1024, '\n');

	cout << "이름 : ";
	cin.getline(pPlayer->strName, NAME_SIZE - 1);

	pPlayer->eJob = (JOB)SelectJob();

	pPlayer->iLevel = 1;
	pPlayer->iExp = 0;
	pPlayer->tInventory.iGold = 10000;

	switch (pPlayer->eJob)
	{
	case JOB_KNIGHT:
		strcpy_s(pPlayer->strJobName, "기사");
		pPlayer->iAttackMin = 5;
		pPlayer->iAttackMax = 10;
		pPlayer->iArmorMin = 15;
		pPlayer->iArmorMax = 20;

		pPlayer->iHPMax = 500;
		pPlayer->iHP = 500;
		pPlayer->iMP = 100;
		pPlayer->iMPMax = 100;
		break;

	case JOB_ARCHER:
		strcpy_s(pPlayer->strJobName, "궁수");
		pPlayer->iAttackMin = 10;
		pPlayer->iAttackMax = 15;
		pPlayer->iArmorMin = 10;
		pPlayer->iArmorMax = 15;

		pPlayer->iHPMax = 400;
		pPlayer->iHP = 400;
		pPlayer->iMP = 200;
		pPlayer->iMPMax = 200;
		break;

	case JOB_WIZARD:
		strcpy_s(pPlayer->strJobName, "마법사");
		pPlayer->iAttackMin = 15;
		pPlayer->iAttackMax = 20;
		pPlayer->iArmorMin = 5;
		pPlayer->iArmorMax = 10;

		pPlayer->iHPMax = 300;
		pPlayer->iHP = 300;
		pPlayer->iMP = 300;
		pPlayer->iMPMax = 300;
		break;
	}
}

bool LoadPlayer(_tagPlayer* pPlayer)
{
	FILE* pFile = NULL;

	fopen_s(&pFile, "Player.ply", "rb");

	if (pFile)
	{
		fread(pPlayer->strName, 1, NAME_SIZE, pFile);	// 이름
		fread(&pPlayer->eJob, sizeof(JOB), 1, pFile);	// 직업
		fread(pPlayer->strJobName, 1, NAME_SIZE, pFile);

		fread(&pPlayer->iAttackMin, 4, 1, pFile);	// 공격력
		fread(&pPlayer->iAttackMax, 4, 1, pFile);	

		fread(&pPlayer->iArmorMin, 4, 1, pFile);	// 방어력
		fread(&pPlayer->iArmorMax, 4, 1, pFile);

		fread(&pPlayer->iHP, 4, 1, pFile);			// HP
		fread(&pPlayer->iHPMax, 4, 1, pFile);

		fread(&pPlayer->iMP, 4, 1, pFile);			// MP
		fread(&pPlayer->iMPMax, 4, 1, pFile);

		fread(&pPlayer->iExp, 4, 1, pFile);			// 경험치
		fread(&pPlayer->iLevel, 4, 1, pFile);		// 레벨

		fread(&pPlayer->bEquip[EQ_WEAPON], 1, 1, pFile);		// 무기 장착 여부

		// 만약 저장할 때 무기를 차고 있었을 경우
		if (pPlayer->bEquip[EQ_WEAPON])
			fread(&pPlayer->tEquip[EQ_WEAPON], sizeof(_tagitem), 1, pFile);

		fread(&pPlayer->bEquip[EQ_ARMOR], 1, 1, pFile);		// 방어구 장착 여부

		// 만약 저장할 때 무기를 차고 있었을 경우
		if (pPlayer->bEquip[EQ_ARMOR])
			fread(&pPlayer->tEquip[EQ_ARMOR], sizeof(_tagitem), 1, pFile);

		fread(&pPlayer->tInventory.iGold, 4, 1, pFile);			// 골드

		fread(&pPlayer->tInventory.tItemCnt, 4, 1, pFile);		// 인벤토리 아이템 수 읽어온다

		// 읽어온 아이템 수만큼 인벤토리에 아이템 정보를 읽어온다
		fread(pPlayer->tInventory.tItem, sizeof(_tagitem), pPlayer->tInventory.tItemCnt, pFile);


		fclose(pFile);
		return true;
	}

	return false;
}

bool SavePlayer(_tagPlayer* pPlayer)
{
	FILE* pFile = NULL;

	fopen_s(&pFile, "Player.ply", "wb");

	if (pFile)
	{
		fwrite(pPlayer->strName, 1, NAME_SIZE, pFile);	// 이름
		fwrite(&pPlayer->eJob, sizeof(JOB), 1, pFile);	// 직업
		fwrite(pPlayer->strJobName, 1, NAME_SIZE, pFile);
		
		fwrite(&pPlayer->iAttackMin, 4, 1, pFile);	// 공격력
		fwrite(&pPlayer->iAttackMax, 4, 1, pFile);

		fwrite(&pPlayer->iArmorMin, 4, 1, pFile);	// 방어력
		fwrite(&pPlayer->iArmorMax, 4, 1, pFile);

		fwrite(&pPlayer->iHP, 4, 1, pFile);			// HP
		fwrite(&pPlayer->iHPMax, 4, 1, pFile);

		fwrite(&pPlayer->iMP, 4, 1, pFile);			// MP
		fwrite(&pPlayer->iMPMax, 4, 1, pFile);

		fwrite(&pPlayer->iExp, 4, 1, pFile);			// 경험치
		fwrite(&pPlayer->iLevel, 4, 1, pFile);		// 레벨

		fwrite(&pPlayer->bEquip[EQ_WEAPON], 1, 1, pFile);		// 무기 장착 여부

		// 만약 저장할 때 무기를 차고 있었을 경우
		if (pPlayer->bEquip[EQ_WEAPON])
			fwrite(&pPlayer->tEquip[EQ_WEAPON], sizeof(_tagitem), 1, pFile);

		fwrite(&pPlayer->bEquip[EQ_ARMOR], 1, 1, pFile);		// 방어구 장착 여부

		// 만약 저장할 때 무기를 차고 있었을 경우
		if (pPlayer->bEquip[EQ_ARMOR])
			fwrite(&pPlayer->tEquip[EQ_ARMOR], sizeof(_tagitem), 1, pFile);

		fwrite(&pPlayer->tInventory.iGold, 4, 1, pFile);			// 골드

		fwrite(&pPlayer->tInventory.tItemCnt, 4, 1, pFile);		// 인벤토리 아이템 수 읽어온다

		// 읽어온 아이템 수만큼 인벤토리에 아이템 정보를 읽어온다
		fwrite(pPlayer->tInventory.tItem, sizeof(_tagitem), pPlayer->tInventory.tItemCnt, pFile);

		fclose(pFile);
		return true;
	}

	return false;
}

_tagMonster CreateMonster(const char* pName, int iAttackMin,
	int iAttackMax, int iArmorMin, int iArmorMax, int iHP,
	int iMP, int iLevel, int iExp, int iGoldMin, int iGoldMax)
{
	_tagMonster tMonster = {};

	strcpy_s(tMonster.strName, pName);
	tMonster.iAttackMin = iAttackMin;
	tMonster.iAttackMax = iAttackMax;
	tMonster.iArmorMin = iArmorMin;
	tMonster.iArmorMax = iArmorMax;
	tMonster.iHP = iHP;
	tMonster.iHPMax = iHP;
	tMonster.iMP = iMP;
	tMonster.iHPMax = iMP;
	tMonster.iLevel = iLevel;
	tMonster.iExp = iExp;
	tMonster.iGoldMin = iGoldMin;
	tMonster.iGoldMax = iGoldMax;

	return tMonster;
}

void SetMonster(_tagMonster * pMonsterArr)
{
 
		FILE* pFile = NULL;

		fopen_s(&pFile, "Monster.mst", "rb");

		if (pFile)
		{
			fread(pMonsterArr, sizeof(_tagMonster), MT_BACK - 1, pFile);
			fclose(pFile);
		}

		 
	/*
	pMonsterArr[0] = CreateMonster("고블린", 20, 30, 2, 5,
		100, 10, 1, 1000, 500, 1500);
	pMonsterArr[1] = CreateMonster("트롤", 80, 130, 60, 90,
		2000, 100, 5, 7000, 6000, 8000);
	pMonsterArr[2] = CreateMonster("드래곤", 250, 500, 200, 400,
		30000, 20000, 10, 30000, 20000, 50000);
		*/
}

void OutputBattleTag(int iMenu)
{
	switch (iMenu)
	{
	case MT_EASY:
		cout << " ================ 쉬움 =======================" << endl;
		break;

	case MT_NOMAL:
		cout << " ================ 보통 =======================" << endl;
		break;

	case MT_HARD:
		cout << " ================ 어려움 =======================" << endl;
		break;
	}
}

void OutputPlayer(_tagPlayer * pPlayer)
{
	// 플레이어 정보
	cout << " ================ Player =======================" << endl;
	cout << "이름 : " << pPlayer->strName
		<< "\t직업 : " << pPlayer->strJobName << endl << endl;
	cout << "레벨 : " << pPlayer->iLevel
		<< "\t경험치 : " << pPlayer->iExp << " / "
		<< g_iLevelUpExp[pPlayer->iLevel - 1] << endl << endl;

	///////////////////////////////////////////////////////////

	// 무기를 장착하고 있을 경우 공격력에 무기공격력을 추가하여 출력한다.
	if (pPlayer->bEquip[EQ_WEAPON] == true)
	{
		cout << "공격력 : " << pPlayer->iAttackMin << " + " <<
			pPlayer->tEquip[EQ_WEAPON].iMin << " - " <<
			pPlayer->iAttackMax << " + " << pPlayer->tEquip[EQ_WEAPON].iMax;
	}

	else
	{
		cout << "공격력 : " << pPlayer->iAttackMin << " - " <<
			pPlayer->iAttackMax;
	}

	// 방어구를 장착하고 있을 경우 방어력에 방어구 방어력을 추가하여 출력한다.
	if (pPlayer->bEquip[EQ_ARMOR] == true)
	{
		cout << "\t방어력 : " << pPlayer->iArmorMin << " + " <<
			pPlayer->tEquip[EQ_ARMOR].iMin << " - " <<
			pPlayer->iArmorMax << " + " << pPlayer->tEquip[EQ_ARMOR].iMax << endl;
	}

	else
	{
		cout << "\t방어력 : " << pPlayer->iArmorMin << " - " <<
			pPlayer->iArmorMax << endl;
	}

	///////////////////////////////////////////////////////////

	cout << "HP : " << pPlayer->iHP << " / "
		<< pPlayer->iHPMax << endl;
	cout << "MP : " << pPlayer->iMP << " / "
		<< pPlayer->iMPMax << endl << endl;

	///////////////////////////////////////////////////////////
	if (pPlayer->bEquip[EQ_WEAPON])
		cout << "장착무기 : " << pPlayer->tEquip[EQ_WEAPON].strName;

	else
		cout << "장착무기 : 없음";

	if (pPlayer->bEquip[EQ_ARMOR])
		cout << "\t장착방어구 : " << pPlayer->tEquip[EQ_ARMOR].strName << endl;

	else
		cout << "\t장착방어구 : 없음" << endl;
	///////////////////////////////////////////////////////////

	cout << "보유 골드 : " << pPlayer->tInventory.iGold << " Gold" << endl << endl;

}

void OutputMonster(_tagMonster * pMonster)
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

int OutPutBattleMenu()
{
	cout << "1. 공격" << endl;
	cout << "2. 도망가기" << endl;
	cout << "메뉴를 선택하세요 :";

	int iMenu = inputInt();

	if (iMenu == INT_MAX || iMenu <= BATTLE_NONE || iMenu > BATTLE_BACK)
		return BATTLE_NONE;

	return iMenu;
}

void Battle(_tagPlayer * pPlayer, _tagMonster * pMoster)
{
	int	iAttackMin = pPlayer->iAttackMin;
	int	iAttackMax = pPlayer->iAttackMax;

	// 무기를 장착하고 있을 경우 무기와 Min, Max를 더해준다.
	if (pPlayer->bEquip[EQ_WEAPON])
	{
		iAttackMin += pPlayer->tEquip[EQ_WEAPON].iMin;
		iAttackMax += pPlayer->tEquip[EQ_WEAPON].iMax;
	}

	int	iAttack = rand() % (iAttackMax - iAttackMin + 1) +
		iAttackMin;
	int	iArmor = rand() % (pMoster->iArmorMax - pMoster->iArmorMin + 1) +
		pMoster->iArmorMin;

	int	iDamage = iAttack - iArmor;

	// 최소데미지 1 고정
	// 삼항연산자 >> 조건식 ? true : false
	iDamage = iDamage < 1 ? 1 : iDamage;


	// 몬스터 HP 감소
	pMoster->iHP -= iDamage;

	cout << endl;
	cout << pPlayer->strName << " 가 " << pMoster->strName <<
		"에게 " << iDamage << " 피해를 입혔습니다" << endl;

	// 몬스터가 죽었을 경우
	if (pMoster->iHP <= 0)
	{
		cout << endl;
		cout << pMoster->strName << " 몬스터가 죽었습니다" << endl << endl;

		pPlayer->iExp += pMoster->iExp;
		int iGold = (rand() % (pMoster->iGoldMax - pMoster->iGoldMin + 1)
			+ pMoster->iGoldMin);
		pPlayer->tInventory.iGold += iGold;

		cout << pMoster->iExp << " 경험치를 획득했습니다" << endl;
		cout << iGold << " 골드를 획득했습니다" << endl << endl;

		// 몬스터 부활
		pMoster->iHP = pMoster->iHPMax;
		pMoster->iMP = pMoster->iMPMax;

		// 레벨업 체크
		if (pPlayer->iExp >= g_iLevelUpExp[pPlayer->iLevel - 1])
		{
			pPlayer->iExp -= g_iLevelUpExp[pPlayer->iLevel - 1];

			++pPlayer->iLevel;

			cout << pPlayer->iLevel << " 레벨업 " << endl;

			// 능력치를 상승시킨다
			int	iJobIndex = pPlayer->eJob - 1; 	// 직업 인덱스를 구한다.

			int	iHPUp = rand() % (g_tLvUpTable[iJobIndex].iHPMax - g_tLvUpTable[iJobIndex].iHPMin + 1) +
				g_tLvUpTable[iJobIndex].iHPMin;
			int	iMPUp = rand() % (g_tLvUpTable[iJobIndex].iMPMax - g_tLvUpTable[iJobIndex].iMPMin + 1) +
				g_tLvUpTable[iJobIndex].iMPMin;

			pPlayer->iAttackMin += g_tLvUpTable[iJobIndex].iAttackMin;
			pPlayer->iAttackMax += g_tLvUpTable[iJobIndex].iAttackMax;
			pPlayer->iArmorMin += g_tLvUpTable[iJobIndex].iArmorMin;
			pPlayer->iArmorMax += g_tLvUpTable[iJobIndex].iArmorMax;

			pPlayer->iHPMax += iHPUp;
			pPlayer->iMPMax += iMPUp;

			// 체력과 마나를 회복시킨다.
			pPlayer->iHP = pPlayer->iHPMax;
			pPlayer->iMP = pPlayer->iMPMax;
		}
		return;
	}

	// 몬스터가 살아있을 경우 플레이어 공격 
	iAttack = rand() % (pMoster->iAttackMax - pMoster->iAttackMin + 1) +
		pMoster->iAttackMin;

	int	iArmorMin = pPlayer->iArmorMin;
	int	iArmorMax = pPlayer->iArmorMax;

	if (pPlayer->bEquip[EQ_ARMOR])
	{
		iArmorMin += pPlayer->tEquip[EQ_ARMOR].iMin;
		iArmorMax += pPlayer->tEquip[EQ_ARMOR].iMax;
	}

	iArmor = rand() % (iArmorMax - iArmorMin + 1) +
		iArmorMin;

	iDamage = iAttack - iArmor;

	iDamage = iDamage < 1 ? 1 : iDamage;

	pPlayer->iHP -= iDamage;

	cout << pMoster->strName << " 가 " << pPlayer->strName <<
		"에게 " << iDamage << " 피해를 입혔습니다" << endl;


	// 플레이어 사망
	if (pPlayer->iHP <= 0)
	{
		cout << endl;
		cout << pPlayer->strName << " 플레이어가 죽었습니다" << endl << endl;

		int iExp = pPlayer->iExp * 0.1f;
		int iGold = pPlayer->tInventory.iGold * 0.1f;

		pPlayer->iExp -= iExp;
		pPlayer->tInventory.iGold -= iGold;

		cout << iExp << " 경험치를 잃었습니다" << endl;
		cout << iGold << " 골드를 잃었습니다" << endl << endl;

		// 플레이어 부활
		pPlayer->iHP = pPlayer->iHPMax;
		pPlayer->iMP = pPlayer->iMPMax;
	}
}

void RunBattle(_tagPlayer * pPlayer, _tagMonster * pMonsterArr,
	int iMenu)
{
	_tagMonster tMonster = pMonsterArr[iMenu - 1];

	while (true)
	{
		system("cls");
		OutputBattleTag(iMenu);

		// 플레이어 출력
		OutputPlayer(pPlayer);

		// 몬스터 출력
		OutputMonster(&tMonster);

		switch (OutPutBattleMenu())
		{
		case BATTLE_ATTACK:
			Battle(pPlayer, &tMonster);
			system("pause");
			break;

		case BATTLE_BACK:
			return;
		}
	}
}

void RunMap(_tagPlayer * pPlayer, _tagMonster * pMonsterArr)
{
	bool bLoop = true;

	while (true)
	{
		int iMenu = OutPutMapMenu();

		if (MT_BACK == iMenu)
			return;


		// 전투시작
		RunBattle(pPlayer, pMonsterArr, iMenu);
	}
}


_tagLevelUpStatus CreateLvUpStatus(int iAttackMin, int iAttackMax,
	int iArmorMin, int iArmorMax, int iHPMin, int iHPMax,
	int iMPMin, int iMPMax)
{
	_tagLevelUpStatus tStatus = {};

	tStatus.iAttackMin = iAttackMin;
	tStatus.iAttackMax = iAttackMax;
	tStatus.iArmorMin = iArmorMin;
	tStatus.iArmorMax = iArmorMax;
	tStatus.iHPMin = iHPMin;
	tStatus.iHPMax = iHPMax;
	tStatus.iMPMin = iMPMin;
	tStatus.iMPMax = iMPMax;

	return tStatus;
}

int OutputStoreMenu()
{

	system("cls");
	cout << " ================ 상점 =======================" << endl;
	cout << "1. 무기 상점" << endl;
	cout << "2. 방어구 상점" << endl;
	cout << "3. 뒤로가기" << endl;
	cout << "상점을 선택하세요 : ";

	int iMenu = inputInt();

	if (iMenu <= SM_NONE || iMenu > SM_BACK)
		return SM_NONE;

	return iMenu;

}

int OutputStoreItemList(_tagInventory * pInventory, _tagitem * pStore,
	int iItemCount)
{
	for (int i = 0; i < iItemCount; ++i)
	{
		cout << i + 1 << ". 이름 : " << pStore[i].strName <<
			"\t종류 : " << pStore[i].strTypeName << endl;

		cout << "공격력 : " << pStore[i].iMin << " - " <<
			pStore[i].iMax << endl;

		cout << "판매가격 : " << pStore[i].iPrice <<
			"\t구매가격 : " << pStore[i].iSell << endl;

		cout << "설명 : " << pStore[i].strDesc << endl << endl;
	}

	cout << iItemCount + 1 << ". 뒤로가기" << endl;
	cout << "보유 금액 : " << pInventory->iGold << " GOLD" << endl;
	cout << "남은 공간 : " << INVENTORY_MAX - pInventory->tItemCnt << endl;
	cout << "구입할 아이템을 선택하세요 : ";

	int iMenu = inputInt();

	if (iMenu <1 || iMenu > iItemCount + 1)
		return INT_MAX;

	return iMenu;
}

void BuyItem(_tagInventory * pInventory, _tagitem * pStore,
	int iItemCount, int iStoreType)
{
	while (true)
	{
		system("cls");

		switch (iStoreType)
		{
		case SM_WEAPON:
			cout << " ================= 무기 상점 =================" << endl;
			break;
		case SM_ARMOR:
			cout << " ================= 방어구 상점 =================" << endl;
			break;
		}

		int iInput = OutputStoreItemList(pInventory, pStore, iItemCount);

		if (iInput == INT_MAX)
		{
			cout << "잘못 입력" << endl;
			system("pause");
			continue;
		}

		else if (iInput == iItemCount + 1)
			break;

		// 상점판매목록 배열 인덱스
		int iIndex = iInput - 1;

		// 인벤토리 검사
		if (pInventory->tItemCnt == INVENTORY_MAX)
		{
			cout << "가방이 가득 찼습니다" << endl;
			system("pause");
			continue;
		}

		// 잔액 부족
		else if (pInventory->iGold < pStore[iIndex].iPrice)
		{
			cout << "잔액 부족" << endl;
			system("pause");
			continue;
		}

		pInventory->tItem[pInventory->tItemCnt] =
			pStore[iIndex];
		++pInventory->tItemCnt;

		pInventory->iGold -= pStore[iIndex].iPrice;

		cout << pStore[iIndex].strName << " 아이템 구매 완료" << endl;
		system("pause");
	}
}

void RunStore(_tagInventory * pInventory, _tagitem * pWeapon,
	_tagitem * pArmor)
{
	while (true)
	{
		switch (OutputStoreMenu())
		{
		case SM_WEAPON:
			BuyItem(pInventory, pWeapon, STORE_WEAPON_MAX, SM_WEAPON);
			break;

		case SM_ARMOR:
			BuyItem(pInventory, pArmor, STORE_ARMOR_MAX, SM_ARMOR);
			break;

		case SM_BACK:
			return;
		}
	}
}

_tagitem CreateItem(const char* pName, ITEM_TYPE eType, int iMin,
	int iMax, int iPrice, int iSell, const char* pDesc)
{
	_tagitem tItem = {};

	strcpy_s(tItem.strName, pName);
	strcpy_s(tItem.strDesc, pDesc);

	tItem.eType = eType;

	switch (eType)
	{
	case IT_WEAPON:
		strcpy_s(tItem.strTypeName, "무기");
		break;
	case IT_ARMOR:
		strcpy_s(tItem.strTypeName, "방어구");
		break;
	}

	tItem.iMin = iMin;
	tItem.iMax = iMax;
	tItem.iPrice = iPrice;
	tItem.iSell = iSell;

	return tItem;
}

int OutputInventory(_tagPlayer * pPlayer)
{
	system("cls");
	cout << " ****************** 가방 *********************" << endl;

	OutputPlayer(pPlayer);

	for (int i = 0; i < pPlayer->tInventory.tItemCnt; ++i)
	{
		cout << i + 1 << ". 이름 : " << pPlayer->tInventory.tItem[i].strName <<
			"\t종류 : " << pPlayer->tInventory.tItem[i].strTypeName << endl;

		cout << "공격력 : " << pPlayer->tInventory.tItem[i].iMin << " - " <<
			pPlayer->tInventory.tItem[i].iMax << endl;

		cout << "판매가격 : " << pPlayer->tInventory.tItem[i].iPrice <<
			"\t구매가격 : " << pPlayer->tInventory.tItem[i].iSell << endl;

		cout << "설명 : " << pPlayer->tInventory.tItem[i].strDesc << endl << endl;
	}

	cout << pPlayer->tInventory.tItemCnt + 1 << ". 뒤로가기" << endl;
	cout << "장착할 아이템을 선택하세요 : ";


	int iMenu = inputInt();

	if (iMenu < 1 || iMenu > pPlayer->tInventory.tItemCnt + 1)
		return INT_MAX;

	return iMenu;
}

EQUIP ComputeEquipType(ITEM_TYPE eType)
{
	EQUIP eq;

	switch (eType)
	{
	case IT_WEAPON:
		eq = EQ_WEAPON;
		break;
	case IT_ARMOR:
		eq = EQ_ARMOR;
		break;
	}

	return eq;
}

void RunInventory(_tagPlayer * pPlayer)
{
	while (true)
	{
		int iInput = OutputInventory(pPlayer);

		if (iInput == INT_MAX)
			continue;

		else if (iInput == pPlayer->tInventory.tItemCnt + 1)
			break;

		// 아이템 인덱스
		int idx = iInput - 1;

		EQUIP eq = ComputeEquipType(pPlayer->tInventory.tItem[idx].eType);

		// 장착된 아이템 교체
		if (pPlayer->bEquip[eq] == true)
		{
			_tagitem tSwap = pPlayer->tEquip[eq];
			pPlayer->tEquip[eq] = pPlayer->tInventory.tItem[idx];
			pPlayer->tInventory.tItem[idx] = tSwap;
		}

		// 장착 되어있지 않을 경우
		else
		{
			pPlayer->tEquip[eq] = pPlayer->tInventory.tItem[idx];

			for (int i = idx; i < pPlayer->tInventory.tItemCnt - 1; ++i)
			{
				pPlayer->tInventory.tItem[i] = pPlayer->tInventory.tItem[i + 1];
			}

			--pPlayer->tInventory.tItemCnt;

			pPlayer->bEquip[eq] = true;
		}

		cout << pPlayer->tEquip[eq].strName << "아이템을 장착했습니다" << endl;

		system("pause");
	}
}

bool LoadItem(_tagitem* pWeapon, _tagitem* pArmor)
{
	FILE* pFile = NULL;

	fopen_s(&pFile, "Store.str", "rb");

	if (pFile)
	{
		fread(pWeapon, sizeof(_tagitem), STORE_WEAPON_MAX, pFile);
		fread(pArmor, sizeof(_tagitem), STORE_ARMOR_MAX, pFile);

		fclose(pFile);
		return true;
	}

	return false;
}

///////////////////////////////////////////////////////////
int main()
{
	srand((unsigned int)time(0));

	// 플레이어 정보 설정
	_tagPlayer tPlayer = {};

	int iGameMode = 0;

	while (iGameMode <= GM_NONE || iGameMode >= GM_END)
	{
		system("cls");
		cout << "1. 새로하기" << endl;
		cout << "2. 이어하기" << endl;
		cout << "3. 종료" << endl;
		iGameMode = inputInt();
	}

	if (iGameMode == GM_END)
		return 0;

	switch (iGameMode)
	{
	case GM_NEW:
		SetPlayer(&tPlayer);
		break;

	case GM_LOAD:
		if (!LoadPlayer(&tPlayer))	// false에 !을 붙이면 ture가 된다
		{
			cout << "플레이어 파일 오류!" << endl;
			return 0;
		}
		break;
	}

	// 몬스터 생성
	_tagMonster tMonsterArr[MT_BACK - 1] = {};

	SetMonster(tMonsterArr);

	g_tLvUpTable[JOB_KNIGHT - 1] = CreateLvUpStatus(4, 10,
		8, 16, 50, 100, 10, 20);
	g_tLvUpTable[JOB_ARCHER - 1] = CreateLvUpStatus(10, 15,
		5, 10, 30, 60, 30, 50);
	g_tLvUpTable[JOB_WIZARD - 1] = CreateLvUpStatus(15, 20,
		3, 7, 20, 40, 50, 1);



	// 아이템 목록
	_tagitem	tStoreWeapon[STORE_WEAPON_MAX] = {};
	_tagitem	tStoreArmor[STORE_ARMOR_MAX] = {};
/*
	tStoreWeapon[0] = CreateItem("목검", IT_WEAPON, 5, 10,
		1000, 500, "나무로 만든 칼");
	tStoreWeapon[1] = CreateItem("장궁", IT_WEAPON, 20, 10,
		7000, 3500, "짱짱하게 만든 활");
	tStoreWeapon[2] = CreateItem("지팡이", IT_WEAPON, 90, 150,
		30000, 15000, "나무로 만든 지팡이");

	tStoreArmor[0] = CreateItem("천갑옷", IT_ARMOR, 2, 5,
		1000, 500, "천으로 만든 갑옷");
	tStoreArmor[1] = CreateItem("가죽갑옷", IT_ARMOR, 10, 20,
		7000, 3500, "가죽으로 만든 갑옷");
	tStoreArmor[2] = CreateItem("플레이트아머", IT_ARMOR, 70, 90,
		30000, 15000, "금속으로 만든 갑옷");
*/

	LoadItem(tStoreWeapon, tStoreArmor);

	bool bLoop = true;

	while (bLoop)
	{
		switch (OutPutMainMenu())
		{
		case MM_MAP:
			RunMap(&tPlayer, tMonsterArr);
			break;
		case MM_STORE:
			RunStore(&tPlayer.tInventory, tStoreWeapon, tStoreArmor);
			break;
		case MM_INVENTORY:
			RunInventory(&tPlayer);
			break;
		case MM_EXIT:
			bLoop = false;
			break;
		}
	}

	SavePlayer(&tPlayer);

	return 0;
}
