#define _CRT_SECURE_NO_WARNINGS
#include "Main.h"
#include "User.h" // nick, chip
#include "Game_Select.h"

void gotoxy(int x, int y) // 커서 위치 조작
{
	COORD CursorPosition = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
}
void setcursortype(CURSOR_TYPE c) // 커서 크기 조작
{
	CONSOLE_CURSOR_INFO CurInfo;
	switch (c)
	{
	case NOCURSOR:
		CurInfo.dwSize = 1;
		CurInfo.bVisible = FALSE;
		break;
	case SOLIDCURSOR:
		CurInfo.dwSize = 100;
		CurInfo.bVisible = TRUE;
		break;
	case NORMALCURSOR:
		CurInfo.dwSize = 20;
		CurInfo.bVisible = TRUE;
		break;
	}
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
}

int main(void)
{

	FILE * fin = fopen("save.tg", "rb");
	int check_save;

	if (fin == NULL)
	{
		check_save = 0;
	}
	else
	{
		check_save = 1;
		fread(&USER, sizeof(USER), 1, fin);
		fclose(fin);
	}

	setcursortype(NOCURSOR);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); // Text Color Green
	system("mode con:cols=90 lines=30");
	system("title THE GENIUS");
	main_side();
	main_title();
	main_menu(&check_save);
	return 0;
}

void main_side()
{
	int i;
	system("cls");
	for (i = 2; i < 28; i++)
	{
		gotoxy(2, i);  printf("│");
		gotoxy(86, i); printf("│");
	}
	gotoxy(2, 1);  printf("┌─────────────────────────────────────────┐");
	gotoxy(2, 17); printf("├─────────────────────────────────────────┤");
	gotoxy(2, 28); printf("└─────────────────────────────────────────┘");
}

void main_title()
{
	gotoxy(4, 2); printf("┌──┐┌┐┌┐┌──┐");
	gotoxy(4, 3); printf("└┐┌┘│││││┌─┘");
	gotoxy(4, 4); printf("  ││  │└┘││└─┐");
	gotoxy(4, 5); printf("  ││  │┌┐││┌─┘");
	gotoxy(4, 6); printf("  ││  │││││└─┐");
	gotoxy(4, 7); printf("  └┘  └┘└┘└──┘");
	gotoxy(8, 8);  printf("┌─────┐┌────┐┌───┐  ┌┐┌────┐┌┐    ┌┐┌────┐");
	gotoxy(8, 9);  printf("│┌───┐││┌───┘│┌─┐│  ││└─┐┌─┘││    │││┌───┘");
	gotoxy(8, 10); printf("││      └┘││        ││  ││  ││    ││    ││    ││││        ");
	gotoxy(8, 11); printf("││  ┌──┐│└───┐││  ││  ││    ││    ││    │││└───┐");
	gotoxy(8, 12); printf("││  └─┐││┌───┘││  ││  ││    ││    ││    ││└───┐│");
	gotoxy(8, 13); printf("││      ││││        ││  ││  ││    ││    ││    ││        ││");
	gotoxy(8, 14); printf("│└───┘││└───┐││  │└─┘│┌─┘└─┐│└──┘│┌───┘│");
	gotoxy(8, 15); printf("└─────┘└────┘└┘  └───┘└────┘└────┘└────┘");
	gotoxy(72, 16); printf("VERSION 1.0.0");
}


void main_menu(int * check_save)
{
	int position;
	char arrow_key;
	gotoxy(18, 27); printf("Copyright (C) 2015 by THE GENIUS. All rights reserved.");
	if (!*check_save) {
		position = 1;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6); // Text Color Dark Yellow
		gotoxy(40, 20); printf(" 불러오기 ");

		while (1) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); // Text Color Yellow
			gotoxy(40, 21); printf(" 신규게임 ");
			gotoxy(40, 22); printf("  제작자  ");
			gotoxy(40, 23); printf("  끝내기  ");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 224); // Background Color Yellow
			switch (position)
			{
			case 1:
				gotoxy(40, 21); printf(" 신규게임 ");
				break;
			case 2:
				gotoxy(40, 22); printf("  제작자  ");
				break;
			case 3:
				gotoxy(40, 23); printf("  끝내기  ");
				break;
			}
			arrow_key = _getch();
			if (arrow_key == 13) break;
			else if (position != 1 && arrow_key == 72) position--;
			else if (position != 3 && arrow_key == 80) position++;
			else if (position == 0 && arrow_key == 72) position = 3;
			else if (position == 3 && arrow_key == 80) position = 1;
		}
	}
	else {
		position = 0;

		while (1) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); // Text Color Yellow
			gotoxy(40, 20); printf(" 불러오기 ");
			gotoxy(40, 21); printf(" 신규게임 ");
			gotoxy(40, 22); printf("  제작자  ");
			gotoxy(40, 23); printf("  끝내기  ");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 224); // Background Color Yellow
			switch (position)
			{
			case 0:
				gotoxy(40, 20); printf(" 불러오기 ");
				break;
			case 1:
				gotoxy(40, 21); printf(" 신규게임 ");
				break;
			case 2:
				gotoxy(40, 22); printf("  제작자  ");
				break;
			case 3:
				gotoxy(40, 23); printf("  끝내기  ");
				break;
			}
			arrow_key = _getch();
			if (arrow_key == 13) break;
			else if (position != 0 && arrow_key == 72) position--; // UP Key
			else if (position != 3 && arrow_key == 80) position++; // DOWN Key
			else if (position == 0 && arrow_key == 72) position = 3;
			else if (position == 3 && arrow_key == 80) position = 0;
		}
	}
	switch (position)
	{
	case 0:
		game_select();
		break;
	case 1:
		main_new_nick();
		USER.chip = 30;
		game_select();
		break;
	case 2:
		main_create();
		break;
	case 3:
		exit(0);
	}
}

void main_create()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); // Text Color Yellow
	int i;
	gotoxy(10, 5);  printf("┌─────────────────────────────────┐");
	for (i = 6; i < 25; i++)
	{
		gotoxy(10, i); printf("│                                                                  │");
	}
	gotoxy(10, 25); printf("└─────────────────────────────────┘");
	gotoxy(40, 7); printf("『제작자』");
	gotoxy(21, 10); printf("고급 C 프로그래밍 및 설계 1조 THE GENIUS 프로젝트");
	gotoxy(13, 12); printf("케이블 방송사 tvN에서 방영된 '더 지니어스'의 보드게임을 참고하고");
	gotoxy(13, 13); printf("방영되지 않은 기타 보드게임을 참고하여 만들었습니다.");
	gotoxy(19, 16); printf("컴퓨터소프트웨어학과 2015726031 임동건 - 인디언 포커");
	gotoxy(19, 17); printf("컴퓨터소프트웨어학과 2015726019 이현창 - 베팅 흑과백");
	gotoxy(19, 18); printf("컴퓨터소프트웨어학과 2015726015 이충섭 - 다빈치 코드");
	gotoxy(19, 19); printf("컴퓨터소프트웨어학과 2015726026 김응주 - 줄다리기");
	gotoxy(40, 21); printf("광운대학교");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 224); // Background Color Yellow
	gotoxy(42, 23); printf(" 닫기 ");

	while (1)
	{
		if (_getch() == 13)   {
			main();
			break;
		}
	}
}

void main_new_nick()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); // Text Color Yellow
	int i;
	gotoxy(23, 10);  printf("┌────────────────────┐");
	for (i = 11; i < 20; i++)
	{
		gotoxy(23, i); printf("│                                        │");
	}
	gotoxy(23, 20); printf("└────────────────────┘");
	gotoxy(39, 12); printf("『신규게임』");
	gotoxy(37, 14); printf("닉네임을 정하세요");
	setcursortype(NORMALCURSOR);
	while (1)
	{
		gotoxy(32, 16); printf("┌───────────┐");
		gotoxy(32, 17); printf("│                      │");
		gotoxy(32, 18); printf("└───────────┘");
		gotoxy(36, 17);
		gets(USER.nick);
		if (USER.nick[0] != 0) break;
	}
}