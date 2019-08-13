#pragma once

#include "pch.h"
#include <iostream>
using namespace std;

enum OUTPUT_TYPE
{
	OT_NONE,
	OT_OUTPUT,
	OT_INVERSE
};

#define NAME_SIZE 32

typedef struct _tagStudent
{
	char	strName[NAME_SIZE];
	int		iNumber;
	int		iKor;
	int		iEng;
	int		iMath;
	int		nTotal;
	float	fAvg;
} STUDENT, * PSTUDENT;

typedef struct _tagNode
{
	STUDENT tStudent;
	_tagNode* pNext;
	_tagNode* pPrev;
} NODE, *PNODE;

typedef struct _tagList
{
	PNODE pBegin;
	PNODE pEnd;
	int iSize;
} LIST, *PLIST;

static int InputInt()
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

static void InputString(char* pString, int iSize)
{
	cin.clear();
	cin.ignore(1024, '\n');

	cin.getline(pString, iSize - 1);
}

int OutputMenu();
void OutputStudent(const PSTUDENT);

void InitList(PLIST);

void Push_Back(PLIST);
void Push_Front(PLIST);
void Search(PLIST);
void Delete(PLIST);
void Output(PLIST);

void DestroyList(PLIST);

