#include <iostream>
using namespace std;

enum MAIN_MENU
{
	MM_NONE,
	MM_ADD,
	MM_LOAD,
	MM_SAVE,
	MM_OUTPUT,
	MM_EXIT
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

void AddItem(_tagitem* pWeaponStore, _tagitem* pArmorStore)
{
	int iStore = 0;

	while (true)
	{
		system("cls");
		cout << "1. 무기상점" << endl;
		cout << "2. 방어구상점" << endl;
		cout << "3. 취소" << endl;
		cout << "추가할 상점을 선택하세요 : ";
		iStore = inputInt();

		if (iStore == 3)
			return;
		else if (iStore < 1 || iStore > 3)
			continue;

		break;
	}

	int iItemLevel = 0;
	while (true)
	{
		system("cls");
		cout << "1. 초급" << endl;
		cout << "2. 중급" << endl;
		cout << "3. 고급" << endl;
		cout << "4. 취소" << endl;
		cout << "추가할 아이템 난이도를 선택하세요 : ";
		iItemLevel = inputInt();

		if (iItemLevel == 4)
			return;
		else if (iItemLevel < 1 || iItemLevel > 4)
			continue;

		--iItemLevel;
		break;
	}

	cin.clear();
	cin.ignore(1024, '\n');

	_tagitem * pItem = NULL;

	if (iStore == SM_WEAPON)
	{
		pItem = &pWeaponStore[iItemLevel];
		pItem->eType = IT_WEAPON;
		strcpy_s(pItem->strTypeName, "무기");
	}
	else
	{
		pItem = &pArmorStore[iItemLevel];
		pItem->eType = IT_ARMOR;
		strcpy_s(pItem->strTypeName, "방어구");
	}	

	cout << "이름 : ";
	cin.getline(pItem->strName, NAME_SIZE - 1);

	cout << "아이템 설명 : ";
	cin.getline(pItem->strDesc, ITEM_DESC_LENGTH - 1);

	cout << "최소 능력치 : ";
	pItem->iMin = inputInt();	
	cout << "최대 능력치 : ";
	pItem->iMax = inputInt();

	cout << "Price : ";
	pItem->iPrice = inputInt();
	cout << "Sell : ";
	pItem->iSell = inputInt();

	cout << "아이템 추가 완료" << endl;
	system("pause");
}

bool SaveItem(_tagitem* pWeapon, _tagitem* pArmor)
{
	FILE* pFile = NULL;

	fopen_s(&pFile, "Store.str", "wb");

	if (pFile)
	{
		fwrite(pWeapon, sizeof(_tagitem), STORE_WEAPON_MAX, pFile);
		fwrite(pArmor, sizeof(_tagitem), STORE_ARMOR_MAX, pFile);

		fclose(pFile);
		return true;
	}

	return false;
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

void Output(_tagitem* pWeapon, _tagitem* pArmor)
{
	cout << "===================== STORE ==================== " << endl;
	for (int i = 0; i < STORE_WEAPON_MAX; ++i)
	{
		cout << i + 1 << ". 이름 : " << pWeapon[i].strName <<
			"\t종류 : " << pWeapon[i].strTypeName << endl;

		cout << "공격력 : " << pWeapon[i].iMin << " - " <<
			pWeapon[i].iMax << endl;

		cout << "판매가격 : " << pWeapon[i].iPrice <<
			"\t구매가격 : " << pWeapon[i].iSell << endl;

		cout << "설명 : " << pWeapon[i].strDesc << endl << endl;
	}

	for (int i = 0; i < STORE_ARMOR_MAX; ++i)
	{
		cout << i + 1 << ". 이름 : " << pArmor[i].strName <<
			"\t종류 : " << pArmor[i].strTypeName << endl;

		cout << "방어력 : " << pArmor[i].iMin << " - " <<
			pArmor[i].iMax << endl;

		cout << "판매가격 : " << pArmor[i].iPrice <<
			"\t구매가격 : " << pArmor[i].iSell << endl;

		cout << "설명 : " << pArmor[i].strDesc << endl << endl;
	}

	system("pause");
}

int main()
{
	_tagitem tWeapon[STORE_WEAPON_MAX] = {};
	_tagitem tArmor[STORE_ARMOR_MAX] = {};

	while (true)
	{
		system("cls");
		cout << "1. 아이템 추가" << endl;
		cout << "2. 읽어오기 " << endl;
		cout << "3. 저장 " << endl;
		cout << "4. 아이템 출력" << endl;
		cout << "5. 종료 " << endl;
		cout << "메뉴를 선택하세요: " << endl;
		int iMenu = inputInt();

		if (iMenu == MM_EXIT)
			break;

		switch (iMenu)
		{
		case MM_ADD:
			AddItem(tWeapon, tArmor);
			break;

		case MM_LOAD:
			LoadItem(tWeapon, tArmor);
			break;

		case MM_SAVE:
			SaveItem(tWeapon, tArmor);
			break;

		case MM_OUTPUT:
			Output(tWeapon, tArmor);
			break;
		}
	}
	SaveItem(tWeapon, tArmor);
	return 0;
}
