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

	// �ʱ� ȭ�� ����
	system("mode con: cols=100 lines=30");  //cols = ĭ/�� (����)  lines = ��/�� (����)
	SetConsoleTitle(TEXT("Last Choice"));
	CursorView(false);

	// ���� ������ ���
	//PrintfText("intro_logo.txt"); //�ΰ� ���
	

	// �� ��ҿ� �������� ������ ����
	ItemRandom();

	// 60�� ���� ������ ����
	ItemChoice();
	//printf("������ ����Ǿ����ϴ�.\n");

	// ���ȣ���� 10��





	//���� ��
	//printf_txt("logo.txt"); //�ΰ� ���
}

