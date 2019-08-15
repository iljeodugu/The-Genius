#define _CRT_SECURE_NO_WARNINGS
#include "Main.h"
#include "User.h" // nick, chip
#include "Game_Select.h"
#include "Juldarigi.h"

void juldarigi()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // Text Color White
	system("mode con:cols=100 lines=20");
	system("title JULDARIGI");

	int target = 5;
	const int all_card[] = { -5, -4, -3, -2, -1, 1, 2, 3, 4, 5 };

	int game, position_p, position_c;

	PLAYER player = { 0 };
	PLAYER com = { 0 };

	juldarigi_side();
	for (game = 0; game < 10; game++)
	{
		srand(time(NULL));
		juldarigi_map(&player, &com, all_card);
		juldarigi_game_board(&target);

		position_p = juldarigi_card_select(&player);
		position_c = rand() % 10;
		while (com.card[position_c]) position_c = rand() % 10;
		com.card[position_c] = 1;

		target += all_card[position_p] + all_card[position_c];

		gotoxy(4, 12); printf("                                                                                            ");
		gotoxy(40, 12); printf("『카드를 공개합니다』");

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 224); // Background Color Yellow
		gotoxy(4 + 7 * position_c, 2); printf("┌─┐");
		gotoxy(4 + 7 * position_c, 3); printf("│%+d│", all_card[position_c]);
		gotoxy(4 + 7 * position_c, 4); printf("└─┘");
		gotoxy(27 + 7 * position_p, 15); printf("┌─┐");
		gotoxy(27 + 7 * position_p, 16); printf("│%+d│", all_card[position_p]);
		gotoxy(27 + 7 * position_p, 17); printf("└─┘");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // Text Color White
		while (1) { if (_getch() == 13)	break; }

		gotoxy(4, 12); printf("                                                                                            ");
		gotoxy(17, 12); printf("『컴퓨터가 %+d, 플레이어가 %+d 카드를 내서 타겟이 %+d 만큼 이동합니다』", all_card[position_c], all_card[position_p], all_card[position_p] + all_card[position_c]);
		juldarigi_game_board(&target);
		while (1) { if (_getch() == 13)	break; }

		if (target >= 4 && target <= 6)
		{
			gotoxy(4, 12); printf("                                                                                            ");
			gotoxy(21, 12); printf("『타겟의 위치가 %d 이므로 아무도 승점을 흭득하지 못합니다』", target);
			while (1) { if (_getch() == 13)	break; }
		}
		else if (target >= 1 && target <= 3)
		{
			gotoxy(4, 12); printf("                                                                                            ");
			gotoxy(20, 12); printf("『타겟의 위치가 %d 이므로 플레이어가 승점 1점을 흭득합니다』", target);
			player.score++;
			while (1) { if (_getch() == 13)	break; }
		}
		else if (target >= 7 && target <= 9)
		{
			gotoxy(4, 12); printf("                                                                                            ");
			gotoxy(21, 12); printf("『타겟의 위치가 %d 이므로 컴퓨터가 승점 1점을 흭득합니다』", target);
			com.score++;
			while (1) { if (_getch() == 13)	break; }
		}
		else if (target == 10)
		{
			gotoxy(4, 12); printf("                                                                                            ");
			gotoxy(20, 12); printf("『타겟의 위치가 %d 이므로 플레이어가 승점 3점을 흭득합니다』", target);
			player.score += 3;
			while (1) { if (_getch() == 13)	break; }
		}
		else if (target == 0)
		{
			gotoxy(4, 12); printf("                                                                                            ");
			gotoxy(21, 12); printf("『타겟의 위치가 %d 이므로 컴퓨터가 승점 3점을 흭득합니다』", target);
			com.score += 3;
			while (1) { if (_getch() == 13)	break; }
		}
		else if (target < 0)
		{
			gotoxy(4, 12); printf("                                                                                            ");
			gotoxy(19, 12); printf("『타겟의 위치가 0 미만이므로 플레이어가 승점 1점을 흭득합니다』");
			player.score++;
			while (1) { if (_getch() == 13)	break; }
			gotoxy(4, 12); printf("                                                                                            ");
			gotoxy(18, 12); printf("『타겟의 위치가 게임보드를 넘어갔으므로 위치를 5로 초기화합니다』");
			target = 5;
			while (1) { if (_getch() == 13)	break; }
		}
		else if (target > 10)
		{
			gotoxy(4, 12); printf("                                                                                            ");
			gotoxy(19, 12); printf("『타겟의 위치가 10 초과이므로 컴퓨터가 승점 1점을 흭득합니다』");
			com.score++;
			while (1) { if (_getch() == 13)	break; }
			gotoxy(4, 12); printf("                                                                                            ");
			gotoxy(18, 12); printf("『타겟의 위치가 게임보드를 넘어갔으므로 위치를 5로 초기화합니다』");
			target = 5;
			while (1) { if (_getch() == 13)	break; }
		}
	}

	juldarigi_map(&player, &com, all_card);
	gotoxy(4, 12); printf("                                                                                            ");
	gotoxy(40, 12); printf("『게임이 끝났습니다』");
	while (1) { if (_getch() == 13)	break; }
	if (player.score > com.score)
	{
		gotoxy(4, 12); printf("                                                                                            ");
		gotoxy(24, 12); printf("『플레이어가 게임에서 승리하여 칩 %d개를 받았습니다』", (player.score - com.score) * 10);
		USER.chip += (player.score - com.score) * 10;
		while (1) { if (_getch() == 13)	break; }
	}
	else if (player.score < com.score)
	{
		gotoxy(4, 12); printf("                                                                                            ");
		gotoxy(24, 12); printf("『플레이어가 게임에서 패배하여 칩 %d개를 잃었습니다』", (com.score - player.score) * 10);
		USER.chip -= (com.score - player.score) * 10;
		while (1) { if (_getch() == 13)	break; }
	}
	else
	{
		gotoxy(4, 12); printf("                                                                                            ");
		gotoxy(36, 12); printf("『이번 게임은 무승부 입니다』");
		while (1) { if (_getch() == 13)	break; }
	}
	game_select();
}

void juldarigi_side()
{
	int i;
	system("cls");
	for (i = 2; i < 18; i++)
	{
		gotoxy(2, i);  printf("│");
		gotoxy(96, i); printf("│");
	}
	gotoxy(2, 1);  printf("┌──────────────────────────────────────────────┐");
	gotoxy(2, 13); printf("├──────────────────────────────────────────────┤");
	gotoxy(2, 18); printf("└──────────────────────────────────────────────┘");

	gotoxy(2, 16); printf("├──────────┐");
	gotoxy(24, 17); printf("│");
	gotoxy(24, 18); printf("┴");
	gotoxy(11, 17); printf("%s", USER.nick);

	gotoxy(74, 1); printf("┬");
	gotoxy(74, 2); printf("│");
	gotoxy(74, 3); printf("└──────────┤");
	gotoxy(83, 2); printf("컴퓨터");
}

void juldarigi_map(PLAYER * player, PLAYER * com, int * all_card)
{
	int i, j;
	for (i = 4, j = 0; j < 10; i += 7, j++)
	{
		if (!com->card[j])
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112); // Background Color Gray
			gotoxy(i, 2); printf("┌─┐");
			gotoxy(i, 3); printf("│▒│");
			gotoxy(i, 4); printf("└─┘");
		}
		else
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // Text Color White
			gotoxy(i, 2); printf("      ");
			gotoxy(i, 3); printf("      ");
			gotoxy(i, 4); printf("      ");
		}
	}
	for (i = 27, j = 0; j < 10; i += 7, j++)
	{
		if (!player->card[j])
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240); // Background Color White
			gotoxy(i, 15); printf("┌─┐");
			gotoxy(i, 16); printf("│%+d│", all_card[j]);
			gotoxy(i, 17); printf("└─┘");
		}
		else
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // Text Color White
			gotoxy(i, 15); printf("      ");
			gotoxy(i, 16); printf("      ");
			gotoxy(i, 17); printf("      ");
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // Text Color White
	gotoxy(82, 4); printf("승점 : %d", com->score);
	gotoxy(10, 15); printf("승점 : %d", player->score);
}

void juldarigi_game_board(int * target)
{
	int i, j;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 31); // Background Color Blue
	for (i = 5, j = 0; j < 11; i += 8, j++)
	{
		gotoxy(i, 6);  printf("┬───┬");
		gotoxy(i, 7);  printf("│      │");
		gotoxy(i, 8);  printf("│  %02d  │", j);
		gotoxy(i, 9);  printf("│      │");
		gotoxy(i, 10); printf("┴───┴");
		if (j == *target)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 79); // Background Color Red
			gotoxy(i + 2, 7);  printf("      ");
			gotoxy(i + 2, 8);  printf("  %02d  ", j);
			gotoxy(i + 2, 9);  printf("      ");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 31); // Background Color Blue
		}
	}
	gotoxy(5, 6);  printf("┌"); gotoxy(93, 6);  printf("┐");
	gotoxy(5, 10); printf("└"); gotoxy(93, 10); printf("┘");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // Text Color White
}

int juldarigi_card_select(PLAYER * player)
{
	int position;
	char arrow_key;

	gotoxy(4, 12); printf("                                                                                            ");
	gotoxy(38, 12); printf("『카드 한 장을 고르세요』");

	for (position = 0; position < 10; position++)
	{
		if (!player->card[position]) break;
	}

	while (1) {
		gotoxy((position * 7) + 29, 14); printf("▼");

		arrow_key = _getch();
		gotoxy((position * 7) + 29, 14); printf("  ");
		if (arrow_key == 13) break;
		else if (arrow_key == 75) // LEFT Key
		{
			position--;
			if (position < 0) position = 9;
			while (player->card[position])
			{
				position--;
				if (position < 0) position = 9;
			}
		}
		else if (arrow_key == 77) // RIGHT Key
		{
			position++;
			if (position > 9) position = 0;
			while (player->card[position])
			{
				position++;
				if (position > 9) position = 0;
			}
		}
	}

	player->card[position] = 1;
	return position;
}