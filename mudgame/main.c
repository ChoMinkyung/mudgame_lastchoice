#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include<conio.h>
#include <process.h>
#include <Windows.h>
#include "func.h"



int main()
{
	what Item;
	where place = LIVING_ROOM;

	int cols = 80, lines = 30;
	// �ʱ� ȭ�� ����
	system("mode con: cols=80 lines=30");  //cols = ĭ/�� (����)  lines = ��/�� (����)
	SetConsoleTitle(TEXT("Last Choice"));
	CursorView(false);
	
	// �޴� ����
	int cursor_loc = -1;
	int* pCL = &cursor_loc;
	int start = 0;
	int* pS = &start;

	//PrintfText("map.txt", 10, 5);
	PrintMap();
	/*
	
	DrawLines(cols, lines);
	DrawStart(cols, lines, pCL, pS);

	// ���� ����
	DrawLines(cols, lines);

	// ������ ���� - �� ��ҿ� �������� ������ ����
	ItemRandom();
	// 60�� ���� ������ ����
	//TimeCount(60);

	ItemChoice(cols, lines);
	//printf("������ ����Ǿ����ϴ�.\n");

	// ���ȣ���� 10��





	//���� ��
	//printf_txt("logo.txt"); //�ΰ� ���
	*/
}


