#define _CRT_SECURE_NO_WARNINGS
#include "Main.h"
#include "User.h" // nick, chip
#include "Game_Select.h"
#include "Indian_Poker.h"
#include "Juldarigi.h"
#include "blacknwhite.h"

void game_select()
{
	if (USER.chip <= 0) bankrupt();
	FILE * fout = fopen("save.tg", "wb");
	fwrite(&USER, sizeof(USER), 1, fout);
	fclose(fout);

	setcursortype(NOCURSOR);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); // Text Color Green
	system("mode con:cols=50 lines=35");
	system("title THE GENIUS");
	game_select_side();
	game_select_info();
	game_select_menu();
}

void game_select_side()
{
	int i;
	system("cls");
	for (i = 2; i < 33; i++)
	{
		gotoxy(2, i);  printf("��");
		gotoxy(46, i); printf("��");
	}
	gotoxy(2, 1);  printf("����������������������������������������������");
	gotoxy(2, 33); printf("����������������������������������������������");
}

void game_select_info()
{
	gotoxy(18, 3); printf("��GAME SELECT��");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); // Text Color Red
	gotoxy(4, 5); printf("������������������������������������������");
	gotoxy(4, 6); printf("��                      ��              ��");
	gotoxy(4, 7); printf("������������������������������������������");
	gotoxy(6, 6);  printf("�г��� : %s", USER.nick);
	gotoxy(30, 6);  printf("Ĩ ���� : %d", USER.chip);
}

void game_select_menu()
{
	int position = 0;
	char arrow_key;

	while (1) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5); // Text Color Dark Purple
		game_select_1();
		game_select_2();
		game_select_3();
		game_select_4();
		game_select_exit();
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13); // Text Color Purple
		switch (position)
		{
		case 0:
			game_select_1();
			break;
		case 1:
			game_select_2();
			break;
		case 2:
			game_select_3();
			break;
		case 3:
			game_select_4();
			break;
		case 4:
			game_select_exit();
			break;
		}
		arrow_key = _getch();
		if (arrow_key == 13) break;
		else if (position != 0 && arrow_key == 72) position--; // UP Key
		else if (position != 4 && arrow_key == 80) position++; // DOWN Key
		else if (position == 0 && arrow_key == 72) position = 4;
		else if (position == 4 && arrow_key == 80) position = 0;
	}


	switch (position)
	{
	case 0:
		indian_poker();
		break;
	case 1:
		blacknwhite();
		break;
	case 2:
		break;
	case 3:
		juldarigi();
		break;
	case 4:
		main();
		break;
	}
}

void game_select_1()
{
	int i = 9;
	gotoxy(4, i);     printf("������������������������������������������");
	gotoxy(4, i + 1); printf("��            ���ε�� ��Ŀ��           ��");
	gotoxy(4, i + 2); printf("��  ī�� 1�徿 ���� �� ���� ī�� Ȯ�� ��");
	gotoxy(4, i + 3); printf("��   ���� �� ���� ����ī�尡 �¸��Ѵ�   ��");
	gotoxy(4, i + 4); printf("������������������������������������������");
}

void game_select_2()
{
	int i = 14;
	gotoxy(4, i);     printf("������������������������������������������");
	gotoxy(4, i + 1); printf("��            ������ ����须           ��");
	gotoxy(4, i + 2); printf("������Ÿ�� 10������ �̸� Ĩ�� ���� �� �Ħ�");
	gotoxy(4, i + 3); printf("��    �� ���� ������ �÷��̾ �¸�    ��");
	gotoxy(4, i + 4); printf("������������������������������������������");
}

void game_select_3()
{
	int i = 19;
	gotoxy(4, i);     printf("������������������������������������������");
	gotoxy(4, i + 1); printf("��            ���ٺ�ġ �ڵ塻           ��");
	gotoxy(4, i + 2); printf("��       �ܼ��� �̿��� ��������       ��");
	gotoxy(4, i + 3); printf("��    ������ Ÿ���� �� ���߸� �¸�    ��");
	gotoxy(4, i + 4); printf("������������������������������������������");
}

void game_select_4()
{
	int i = 24;
	gotoxy(4, i);     printf("������������������������������������������");
	gotoxy(4, i + 1); printf("��             ���ٴٸ��⡻             ��");
	gotoxy(4, i + 2); printf("��11ĭ ���Ӻ��忡 ����ī�� 10���� �̿��ئ�");
	gotoxy(4, i + 3); printf("�� Ÿ���� �̵����� ������ ȹ���ϴ� ���� ��");
	gotoxy(4, i + 4); printf("������������������������������������������");
}

void game_select_exit()
{
	gotoxy(4, 30); printf("������������������������������������������");
	gotoxy(4, 31); printf("��                ������                ��");
	gotoxy(4, 32); printf("������������������������������������������");
}

void bankrupt()
{
	int i = 1;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); // Text Color Red
	system("mode con:cols=90 lines=30");
	system("title THE GENIUS");
	system("cls");
	_unlink("save.tg");
	gotoxy(2, i);      printf("��������������������������������������������������������������������������������������");
	gotoxy(2, i + 1);  printf("��                                                                                  ��");
	gotoxy(2, i + 2);  printf("��                                                                                  ��");
	gotoxy(2, i + 3);  printf("��                                                                                  ��");
	gotoxy(2, i + 4);  printf("��                                                                                  ��");
	gotoxy(2, i + 5);  printf("��  �����������������������̢̡����������������������������������̢̡�����������    ��");
	gotoxy(2, i + 6);  printf("��  �������������������������̢̢̡��������������������������������̢̢̡�������    ��");
	gotoxy(2, i + 7);  printf("��  ���������������������������̢̡��������������������̢̡����������̢̡�������    ��");
	gotoxy(2, i + 8);  printf("��  �����������������̢̡������̢̡����������������������̢̡��������̢̡�������    ��");
	gotoxy(2, i + 9);  printf("��  �����̢̢̢̢̢̢̢̢̡����̢̡����������������������̢̡��������̢̡�������    ��");
	gotoxy(2, i + 10); printf("��  ���������̡������̡��������̢̡��������������������̢̡����������̢̡�������    ��");
	gotoxy(2, i + 11); printf("��  ���������̡������̡��������̢̡��������������������̢̢̡��������̢̡�������    ��");
	gotoxy(2, i + 12); printf("��  ���������̡������̢̡������̢̡������������������̢̡����̢̡����̢̡��̡���    ��");
	gotoxy(2, i + 13); printf("��  ���������̢̡����̢̡������̢̡��̡������������̢̡������̢̡����̢̢̢̢̡�    ��");
	gotoxy(2, i + 14); printf("��  �����������̡����̡��������̢̢̢̢̡������̢̡������������������̢̡�������    ��");
	gotoxy(2, i + 15); printf("��  �����������̡����̡����̢̢̢̡����������������������������������̢̡�������    ��");
	gotoxy(2, i + 16); printf("��  �����̢̢̢̢̢̢̢̢̡����̢̡����������������������������������̡���������    ��");
	gotoxy(2, i + 17); printf("��  �������̢̢̡��������������̢̡��������������������̢̢̡��������̡���������    ��");
	gotoxy(2, i + 18); printf("��  ���������������������������̢̡����������������������̢̢̡�����������������    ��");
	gotoxy(2, i + 19); printf("��  ���������������������������̡��������������������������̢̡�����������������    ��");
	gotoxy(2, i + 20); printf("��  ���������������������������̡����������������������������̢̢̢̢̢̡�������    ��");
	gotoxy(2, i + 21); printf("��  ���������������������������̡������������������������������̢̢̢̡���������    ��");
	gotoxy(2, i + 22); printf("��                                                                                  ��");
	gotoxy(2, i + 23); printf("��                                                                                  ��");
	gotoxy(2, i + 24); printf("��                                                                                  ��");
	gotoxy(2, i + 25); printf("��                                                                                  ��");
	gotoxy(2, i + 26); printf("��                                                                                  ��");
	gotoxy(2, i + 27); printf("��������������������������������������������������������������������������������������");
	while (1) { if (_getch() == 13)	break; }
	main();
}