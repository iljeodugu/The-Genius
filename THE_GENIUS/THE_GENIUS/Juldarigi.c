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
		gotoxy(40, 12); printf("��ī�带 �����մϴ١�");

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 224); // Background Color Yellow
		gotoxy(4 + 7 * position_c, 2); printf("������");
		gotoxy(4 + 7 * position_c, 3); printf("��%+d��", all_card[position_c]);
		gotoxy(4 + 7 * position_c, 4); printf("������");
		gotoxy(27 + 7 * position_p, 15); printf("������");
		gotoxy(27 + 7 * position_p, 16); printf("��%+d��", all_card[position_p]);
		gotoxy(27 + 7 * position_p, 17); printf("������");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // Text Color White
		while (1) { if (_getch() == 13)	break; }

		gotoxy(4, 12); printf("                                                                                            ");
		gotoxy(17, 12); printf("����ǻ�Ͱ� %+d, �÷��̾ %+d ī�带 ���� Ÿ���� %+d ��ŭ �̵��մϴ١�", all_card[position_c], all_card[position_p], all_card[position_p] + all_card[position_c]);
		juldarigi_game_board(&target);
		while (1) { if (_getch() == 13)	break; }

		if (target >= 4 && target <= 6)
		{
			gotoxy(4, 12); printf("                                                                                            ");
			gotoxy(21, 12); printf("��Ÿ���� ��ġ�� %d �̹Ƿ� �ƹ��� ������ ŉ������ ���մϴ١�", target);
			while (1) { if (_getch() == 13)	break; }
		}
		else if (target >= 1 && target <= 3)
		{
			gotoxy(4, 12); printf("                                                                                            ");
			gotoxy(20, 12); printf("��Ÿ���� ��ġ�� %d �̹Ƿ� �÷��̾ ���� 1���� ŉ���մϴ١�", target);
			player.score++;
			while (1) { if (_getch() == 13)	break; }
		}
		else if (target >= 7 && target <= 9)
		{
			gotoxy(4, 12); printf("                                                                                            ");
			gotoxy(21, 12); printf("��Ÿ���� ��ġ�� %d �̹Ƿ� ��ǻ�Ͱ� ���� 1���� ŉ���մϴ١�", target);
			com.score++;
			while (1) { if (_getch() == 13)	break; }
		}
		else if (target == 10)
		{
			gotoxy(4, 12); printf("                                                                                            ");
			gotoxy(20, 12); printf("��Ÿ���� ��ġ�� %d �̹Ƿ� �÷��̾ ���� 3���� ŉ���մϴ١�", target);
			player.score += 3;
			while (1) { if (_getch() == 13)	break; }
		}
		else if (target == 0)
		{
			gotoxy(4, 12); printf("                                                                                            ");
			gotoxy(21, 12); printf("��Ÿ���� ��ġ�� %d �̹Ƿ� ��ǻ�Ͱ� ���� 3���� ŉ���մϴ١�", target);
			com.score += 3;
			while (1) { if (_getch() == 13)	break; }
		}
		else if (target < 0)
		{
			gotoxy(4, 12); printf("                                                                                            ");
			gotoxy(19, 12); printf("��Ÿ���� ��ġ�� 0 �̸��̹Ƿ� �÷��̾ ���� 1���� ŉ���մϴ١�");
			player.score++;
			while (1) { if (_getch() == 13)	break; }
			gotoxy(4, 12); printf("                                                                                            ");
			gotoxy(18, 12); printf("��Ÿ���� ��ġ�� ���Ӻ��带 �Ѿ���Ƿ� ��ġ�� 5�� �ʱ�ȭ�մϴ١�");
			target = 5;
			while (1) { if (_getch() == 13)	break; }
		}
		else if (target > 10)
		{
			gotoxy(4, 12); printf("                                                                                            ");
			gotoxy(19, 12); printf("��Ÿ���� ��ġ�� 10 �ʰ��̹Ƿ� ��ǻ�Ͱ� ���� 1���� ŉ���մϴ١�");
			com.score++;
			while (1) { if (_getch() == 13)	break; }
			gotoxy(4, 12); printf("                                                                                            ");
			gotoxy(18, 12); printf("��Ÿ���� ��ġ�� ���Ӻ��带 �Ѿ���Ƿ� ��ġ�� 5�� �ʱ�ȭ�մϴ١�");
			target = 5;
			while (1) { if (_getch() == 13)	break; }
		}
	}

	juldarigi_map(&player, &com, all_card);
	gotoxy(4, 12); printf("                                                                                            ");
	gotoxy(40, 12); printf("�������� �������ϴ١�");
	while (1) { if (_getch() == 13)	break; }
	if (player.score > com.score)
	{
		gotoxy(4, 12); printf("                                                                                            ");
		gotoxy(24, 12); printf("���÷��̾ ���ӿ��� �¸��Ͽ� Ĩ %d���� �޾ҽ��ϴ١�", (player.score - com.score) * 10);
		USER.chip += (player.score - com.score) * 10;
		while (1) { if (_getch() == 13)	break; }
	}
	else if (player.score < com.score)
	{
		gotoxy(4, 12); printf("                                                                                            ");
		gotoxy(24, 12); printf("���÷��̾ ���ӿ��� �й��Ͽ� Ĩ %d���� �Ҿ����ϴ١�", (com.score - player.score) * 10);
		USER.chip -= (com.score - player.score) * 10;
		while (1) { if (_getch() == 13)	break; }
	}
	else
	{
		gotoxy(4, 12); printf("                                                                                            ");
		gotoxy(36, 12); printf("���̹� ������ ���º� �Դϴ١�");
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
		gotoxy(2, i);  printf("��");
		gotoxy(96, i); printf("��");
	}
	gotoxy(2, 1);  printf("������������������������������������������������������������������������������������������������");
	gotoxy(2, 13); printf("������������������������������������������������������������������������������������������������");
	gotoxy(2, 18); printf("������������������������������������������������������������������������������������������������");

	gotoxy(2, 16); printf("������������������������");
	gotoxy(24, 17); printf("��");
	gotoxy(24, 18); printf("��");
	gotoxy(11, 17); printf("%s", USER.nick);

	gotoxy(74, 1); printf("��");
	gotoxy(74, 2); printf("��");
	gotoxy(74, 3); printf("������������������������");
	gotoxy(83, 2); printf("��ǻ��");
}

void juldarigi_map(PLAYER * player, PLAYER * com, int * all_card)
{
	int i, j;
	for (i = 4, j = 0; j < 10; i += 7, j++)
	{
		if (!com->card[j])
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112); // Background Color Gray
			gotoxy(i, 2); printf("������");
			gotoxy(i, 3); printf("���Ʀ�");
			gotoxy(i, 4); printf("������");
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
			gotoxy(i, 15); printf("������");
			gotoxy(i, 16); printf("��%+d��", all_card[j]);
			gotoxy(i, 17); printf("������");
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
	gotoxy(82, 4); printf("���� : %d", com->score);
	gotoxy(10, 15); printf("���� : %d", player->score);
}

void juldarigi_game_board(int * target)
{
	int i, j;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 31); // Background Color Blue
	for (i = 5, j = 0; j < 11; i += 8, j++)
	{
		gotoxy(i, 6);  printf("����������");
		gotoxy(i, 7);  printf("��      ��");
		gotoxy(i, 8);  printf("��  %02d  ��", j);
		gotoxy(i, 9);  printf("��      ��");
		gotoxy(i, 10); printf("����������");
		if (j == *target)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 79); // Background Color Red
			gotoxy(i + 2, 7);  printf("      ");
			gotoxy(i + 2, 8);  printf("  %02d  ", j);
			gotoxy(i + 2, 9);  printf("      ");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 31); // Background Color Blue
		}
	}
	gotoxy(5, 6);  printf("��"); gotoxy(93, 6);  printf("��");
	gotoxy(5, 10); printf("��"); gotoxy(93, 10); printf("��");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // Text Color White
}

int juldarigi_card_select(PLAYER * player)
{
	int position;
	char arrow_key;

	gotoxy(4, 12); printf("                                                                                            ");
	gotoxy(38, 12); printf("��ī�� �� ���� �����䡻");

	for (position = 0; position < 10; position++)
	{
		if (!player->card[position]) break;
	}

	while (1) {
		gotoxy((position * 7) + 29, 14); printf("��");

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