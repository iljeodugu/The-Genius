#define _CRT_SECURE_NO_WARNINGS
#include "Main.h"
#include "User.h" // nick, chip
#include "Game_Select.h"
#include "Indian_Poker.h"


void indian_poker()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // Text Color White
	system("mode con:cols=80 lines=30");
	system("title INDIAN POKER");

	int num_c, num_p; // ��ǻ�� ī��, �÷��̾� ī��
	int betting_c = 0, betting_p = 0; // ������ Ĩ
	int betting_c_plus = 0, betting_p_plus = 0; // �߰� ������ Ĩ
	int win = 0, draw = 0; // ��, ��, ���º�
	int card[10] = { 0 };
	int card_count = 0;

	srand(time(NULL));
	win = rand() % 2; // ����, �İ� ���ϱ�

	while (USER.chip > 0 || draw && USER.chip == 0) // ���� Ĩ ���� 0���̰� ���� ī�尡 ���º� ���� ��
	{
		indian_poker_side();
		indian_poker_map(&betting_c, &betting_p, &card_count);
		betting_p_plus = 0; betting_c_plus = 0;

		if (card_count == 20)
		{
			USER.chip += betting_p;
			gotoxy(18, 14);	printf("��20���� ī�带 �� ����Ͽ� ������ �����մϴ١�");
			while (1) { if (_getch() == 13)	break; }
			game_select();
			return;
		}

		gotoxy(27, 14);	printf("��ī�带 �����帮�ڽ��ϴ١�");
		while (1) { if (_getch() == 13)	break; }
		indian_poker_shuffle(card, &num_c, &num_p, &betting_p, &card_count);

		if (!draw) // ���º� �϶��� �⺻ ������ ���� ����
		{
			indian_poker_map(&betting_c, &betting_p, &card_count);
			gotoxy(20, 14);	printf("���⺻ �������� Ĩ �ϳ��� �������ֽʽÿ���");
			while (1) { if (_getch() == 13)	break; }
			USER.chip--; betting_c++; betting_p++;
		}
		indian_poker_map(&betting_c, &betting_p, &card_count);

		if (win == 0 && USER.chip != 0) // win == 0 �̸� ��ǻ�� �� ����
		{
			gotoxy(28, 14);	printf("����ǻ�� �� �����Դϴ١�");
			while (1) { if (_getch() == 13)	break; }

			betting_c_plus = indian_poker_ai(&num_c, &num_p, &card_count, &betting_p, &betting_p_plus);
			betting_c += betting_c_plus;
			indian_poker_map(&betting_c, &betting_p, &card_count);

			if (betting_c_plus == 0)
			{
				gotoxy(24, 14);	printf("����ǻ�Ͱ� ������ �����Ͽ����ϴ١�");
				betting_c_plus = -1; // ��ǻ�Ͱ� ������ �������� ��� -1
			}
			else
			{
				gotoxy(25, 14);	printf("����ǻ�Ͱ� %d�� �����Ͽ����ϴ١�", betting_c_plus);
			}
			while (1) { if (_getch() == 13)	break; }


			while (betting_c_plus != -1) { // ��ǻ�Ͱ� ������ �������� �ʾ��� ��� �߰� ����
				// �߰� ������ ������ ��� ��
				if (indian_poker_player_betting_plus(&betting_p, &betting_c, &betting_p_plus, &betting_c_plus, &card_count)) break;
				if (indian_poker_com_betting_plus(&num_p, &num_c, &betting_p, &betting_c, &betting_p_plus, &betting_c_plus, &card_count)) break;
			}
		}
		else if (win == 1 && USER.chip != 0) // win == 1 �̸� �÷��̾� �� ����
		{
			indian_poker_map(&betting_c, &betting_p, &card_count);
			gotoxy(27, 14);	printf("���÷��̾� �� �����Դϴ١�");

			indian_poker_player_betting(&betting_p_plus, &betting_c_plus);
			betting_p += betting_p_plus;
			USER.chip -= betting_p_plus;
			indian_poker_map(&betting_c, &betting_p, &card_count);

			if (betting_p_plus == 0)
			{
				gotoxy(23, 14);	printf("���÷��̾ ������ �����Ͽ����ϴ١�");
				betting_p_plus = -1; // �÷��̾ ������ �������� ��� -1
			}
			else
			{
				gotoxy(24, 14);	printf("���÷��̾ %d�� �����Ͽ����ϴ١�", betting_p_plus);
			}
			while (1) { if (_getch() == 13)	break; }


			while (betting_p_plus != -1) { // �÷��̾ ������ �������� �ʾ��� ��� �߰� ����
				// �߰� ������ ������ ��� ��
				if (indian_poker_com_betting_plus(&num_p, &num_c, &betting_p, &betting_c, &betting_p_plus, &betting_c_plus, &card_count)) break;
				if (indian_poker_player_betting_plus(&betting_p, &betting_c, &betting_p_plus, &betting_c_plus, &card_count)) break;
			}
		}

		indian_poker_map(&betting_c, &betting_p, &card_count);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240); // Background Color White
		indian_poker_player_card(&num_p);

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // Text Color White
		gotoxy(28, 14); printf("��ī�带 �����ϰڽ��ϴ١�");
		while (1) { if (_getch() == 13)	break; }

		if (betting_p_plus == -1 && num_p == 10) // �÷��̾� ī�尡 10�� �� ������ ���
		{
			USER.chip -= 10;
			betting_c = 0; betting_p = 0;
			win = 0; draw = 0;
			indian_poker_map(&betting_c, &betting_p, &card_count);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 207); // Background Color Red
			indian_poker_player_card(&num_p);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 159); // Background Color Blue
			indian_poker_com_card(&num_c);

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // Text Color White
			gotoxy(10, 14);	printf("��10ī�� �϶� ������ �����ؼ�, �г�Ƽ�� 10���� Ĩ�� �ҽ��ϴ١�");
			while (1) { if (_getch() == 13)	break; }
		}
		else if (betting_c_plus == -1 && num_c == 10) // ��ǻ�� ī�尡 10�� �� ������ ���
		{
			USER.chip += 10 + betting_c + betting_p;
			betting_c = 0; betting_p = 0;
			win = 1; draw = 0;
			indian_poker_map(&betting_c, &betting_p, &card_count);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 159); // Background Color Blue
			indian_poker_player_card(&num_p);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 207); // Background Color Red
			indian_poker_com_card(&num_c);

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // Text Color White
			gotoxy(10, 14);	printf("��10ī�� �϶� ������ �����ؼ�, �г�Ƽ�� 10���� Ĩ�� �ҽ��ϴ١�");
			while (1) { if (_getch() == 13)	break; }
		}
		else if (num_c > num_p && betting_p_plus != -1 || betting_p_plus == -1) // ��ǻ�� ī�� ���� ũ�ų� �÷��̾ ������ ���
		{
			betting_c = 0; betting_p = 0;
			win = 0; draw = 0;
			indian_poker_map(&betting_c, &betting_p, &card_count);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 207); // Background Color Red
			indian_poker_player_card(&num_p);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 159); // Background Color Blue
			indian_poker_com_card(&num_c);

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // Text Color White
			gotoxy(24, 14);	printf("����ǻ�Ͱ� �̹� ���� �̰���ϴ١�");
			while (1) { if (_getch() == 13)	break; }
		}
		else if (num_c < num_p && betting_c_plus != -1 || betting_c_plus == -1) // �÷��̾� ī�� ���� ũ�ų� ��ǻ�Ͱ� ������ ���
		{
			USER.chip += betting_c + betting_p;
			betting_c = 0; betting_p = 0;
			win = 1; draw = 0;
			indian_poker_map(&betting_c, &betting_p, &card_count);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 159); // Background Color Blue
			indian_poker_player_card(&num_p);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 207); // Background Color Red
			indian_poker_com_card(&num_c);

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // Text Color White
			gotoxy(23, 14);	printf("���÷��̾ �̹� ���� �̰���ϴ١�");
			while (1) { if (_getch() == 13)	break; }
		}
		else if (num_c == num_p) // ī�� ���ڰ� ���� ���
		{
			draw = 1;
			indian_poker_map(&betting_c, &betting_p, &card_count);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 160); // Background Color Green
			indian_poker_player_card(&num_p);
			indian_poker_com_card(&num_c);

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // Text Color White
			gotoxy(28, 14);	printf("���̹� ���� ���º��Դϴ١�");
			while (1) { if (_getch() == 13)	break; }
		}

		// Ĩ ���� �ڵ� ����
		FILE * fout = fopen("save.tg", "wb");
		fwrite(&USER, sizeof(USER), 1, fout);
		fclose(fout);
	}
	bankrupt(); // �Ļ�
}

void indian_poker_side()
{
	int i;
	system("cls");
	gotoxy(2, 1);  printf("����������������������������������������������������������������������������");
	gotoxy(2, 28); printf("����������������������������������������������������������������������������");
	for (i = 2; i < 28; i++)
	{
		gotoxy(2, i);  printf("��");
		gotoxy(76, i); printf("��");
	}
}

void indian_poker_map(int * betting_c, int * betting_p, int * card_count)
{
	gotoxy(2, 7);   printf("����������������������������������������������������������������������������");
	gotoxy(2, 13);  printf("����������������������������������������������������������������������������");
	gotoxy(4, 14);	printf("                                                                        ");
	gotoxy(2, 15);  printf("����������������������������������������������������������������������������");
	gotoxy(2, 22);  printf("����������������������������������������������������������������������������");

	gotoxy(4, 2);  printf("��������������������������");
	gotoxy(4, 3);  printf("��                      ��");
	gotoxy(4, 4);  printf("��        ��ǻ��        ��");
	gotoxy(4, 5);  printf("��                      ��");
	gotoxy(4, 6);  printf("��������������������������");
	gotoxy(50, 2);	printf("��������������������������");
	gotoxy(50, 3);  printf("��                      ��");
	gotoxy(50, 4);  printf("��  ����ī�� : (%02d/20)  ��", *card_count);
	gotoxy(50, 5);  printf("��                      ��");
	gotoxy(50, 6);  printf("��������������������������");
	gotoxy(4, 9);	printf("                                                                        ");
	gotoxy(28, 7);	printf("������������������������");
	gotoxy(28, 8);	printf("��                    ��");
	gotoxy(28, 9);	printf("������������������������");
	gotoxy(33, 8);  printf("������ Ĩ : %d", *betting_c);

	gotoxy(4, 23);  printf("��������������������������");
	gotoxy(4, 24);  printf("��                      ��");
	gotoxy(4, 25);  printf("��                      ��");
	gotoxy(4, 26);  printf("��                      ��");
	gotoxy(4, 27);  printf("��������������������������");
	gotoxy(14, 25);	printf("%s", USER.nick);
	gotoxy(50, 23);	printf("��������������������������");
	gotoxy(50, 24); printf("��                      ��");
	gotoxy(50, 25); printf("��                      ��");
	gotoxy(50, 26); printf("��                      ��");
	gotoxy(50, 27); printf("��������������������������");
	gotoxy(57, 25); printf("���� Ĩ : %d", USER.chip);
	gotoxy(4, 20);	printf("                                                                        ");
	gotoxy(28, 20);	printf("������������������������");
	gotoxy(28, 21);	printf("��                    ��");
	gotoxy(28, 22);	printf("������������������������");
	gotoxy(33, 21);	printf("������ Ĩ : %d", *betting_p);

	gotoxy(64, 20);	printf("����������");
	gotoxy(64, 21);	printf("��      ��");
	gotoxy(64, 22);	printf("����������");
}

void indian_poker_shuffle(int * card, int * num_c, int * num_p, int * betting_p, int * card_count)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240); // Background Color White
	while (1)
	{
		*num_c = rand() % 10 + 1;
		if (card[*num_c - 1] < 2)
		{
			card[*num_c - 1]++;
			indian_poker_com_card(num_c);
			break;
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112); // Background Color Gray
	while (1)
	{
		*num_p = rand() % 10 + 1;
		if (card[*num_p - 1] < 2)
		{
			card[*num_p - 1]++;
			gotoxy(35, 23); printf("����������");
			gotoxy(35, 24); printf("��      ��");
			gotoxy(35, 25); printf("��  ��  ��");
			gotoxy(35, 26); printf("��      ��");
			gotoxy(35, 27); printf("����������");
			break;
		}
	}
	*card_count += 2;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // Text Color White
}

void indian_poker_com_card(int * num_c)
{
	gotoxy(35, 2); printf("����������");
	gotoxy(35, 3); printf("��      ��");
	gotoxy(35, 4); printf("��  %02d  ��", *num_c);
	gotoxy(35, 5); printf("��      ��");
	gotoxy(35, 6); printf("����������");
}

void indian_poker_player_card(int * num_p)
{
	gotoxy(35, 23); printf("����������");
	gotoxy(35, 24); printf("��      ��");
	gotoxy(35, 25); printf("��  %02d  ��", *num_p);
	gotoxy(35, 26); printf("��      ��");
	gotoxy(35, 27); printf("����������");
}

void indian_poker_player_betting(int * betting_p_plus, int * betting_c_plus)
{
	char input[8] = { 0 };

	setcursortype(NORMALCURSOR);
	while (1)
	{
		gotoxy(68, 21);	printf("    ");
		gotoxy(68, 21);	gets(input);
		*betting_p_plus = atoi(input);
		if (*betting_p_plus != 0 && *betting_p_plus <= USER.chip && *betting_p_plus >= *betting_c_plus) break;
		else if (input[0] == '0') break;
	}
	setcursortype(NOCURSOR);
}

int indian_poker_player_betting_plus(int * betting_p, int * betting_c, int * betting_p_plus, int * betting_c_plus, int * card_count)
{
	// �÷����� �߰� ���� ����
	indian_poker_map(betting_c, betting_p, card_count);
	gotoxy(26, 14);	printf("���÷��̾� ���� �����Դϴ١�");

	indian_poker_player_betting(betting_p_plus, betting_c_plus);
	*betting_p += *betting_p_plus;
	USER.chip -= *betting_p_plus;
	indian_poker_map(betting_c, betting_p, card_count);

	if (*betting_p_plus == 0)
	{
		gotoxy(23, 14);	printf("���÷��̾ ������ �����Ͽ����ϴ١�");
		*betting_p_plus = -1; // �÷��̾ ������ �������� ��� -1
		while (1) { if (_getch() == 13)	break; }
		return 1;
	}
	else if (*betting_p_plus == *betting_c_plus)
	{
		gotoxy(25, 14);	printf("���÷��̾ %d���� ���߽��ϴ١�", *betting_c_plus);
		while (1) { if (_getch() == 13)	break; }
		return 1;
	}
	else if (*betting_p_plus > *betting_c_plus)
	{
		gotoxy(18, 14);	printf("���÷��̾ %d�� �ް� %d�� �߰������Ͽ����ϴ١�", *betting_c_plus, *betting_p_plus - *betting_c_plus);
		*betting_p_plus -= *betting_c_plus; // �߰� ���� �� ��ŭ betting_p_plus�� ����
		while (1) { if (_getch() == 13)	break; }
	}
	return 0;
}

int indian_poker_com_betting_plus(int * num_p, int * num_c, int * betting_p, int * betting_c, int * betting_p_plus, int * betting_c_plus, int * card_count)
{
	// ��ǻ�� �߰� ���� ����
	indian_poker_map(betting_c, betting_p, card_count);
	gotoxy(27, 14);	printf("����ǻ�� ���� �����Դϴ١�");
	while (1) { if (_getch() == 13)	break; }

	*betting_c_plus = indian_poker_ai(num_c, num_p, card_count, betting_p, betting_p_plus);
	*betting_c += *betting_c_plus;
	indian_poker_map(betting_c, betting_p, card_count);

	if (*betting_c_plus == 0)
	{
		gotoxy(24, 14);	printf("����ǻ�Ͱ� ������ �����Ͽ����ϴ١�");
		*betting_c_plus = -1; // ��ǻ�Ͱ� ������ �������� ��� -1
		while (1) { if (_getch() == 13)	break; }
		return 1;
	}
	else if (*betting_c_plus == *betting_p_plus)
	{
		gotoxy(25, 14);	printf("����ǻ�Ͱ� %d���� ���߽��ϴ١�", *betting_p_plus);
		while (1) { if (_getch() == 13)	break; }
		return 1;
	}
	else if (*betting_c_plus > *betting_p_plus)
	{
		gotoxy(19, 14);	printf("����ǻ�Ͱ� %d�� �ް� %d�� �߰������Ͽ����ϴ١�", *betting_p_plus, *betting_c_plus - *betting_p_plus);
		*betting_c_plus -= *betting_p_plus; // �߰� ���� �� ��ŭ betting_c_plus�� ����
		while (1) { if (_getch() == 13)	break; }
	}
	return 0;
}

int indian_poker_ai(int * num_c, int * num_p, int * card_count, int * betting_p, int * betting_p_plus)
{
	int random = rand() % 5, temp;

	if (random == 0 || *card_count == 20 || *betting_p > 1000)
	{
		if (*num_c < *num_p && *num_c != 10)
		{
			return 0;
		}
		else if (*num_c >= *num_p)
		{
			temp = rand() % 7 + *betting_p_plus;
			while (temp == 0 || temp - *betting_p_plus > USER.chip)
			{
				temp = rand() % 7 + *betting_p_plus;
			}
			return temp;
		}
	}
	else
	{
		if (*num_p == 10)
		{
			// 10���� 1 Ȯ���� ����
			if (rand() % 10 == 0 && USER.chip >= 10 + *betting_p_plus)
			{
				temp = rand() % 5 + 10 + *betting_p_plus;
				while (temp - *betting_p_plus > USER.chip)
				{
					temp = rand() % 5 + 10 + *betting_p_plus;
				}
				return temp;
			}
			else
			{
				return 0;
			}
		}
		else if (*num_p > 6)
		{
			// ���� ī�尡 7, 8, 9 �̰� ���� Ĩ ������ 5������ 15�� ������ ���� ���󰣴�.
			if (*betting_p > 5 && *betting_p <= 10)
			{
				return *betting_p_plus;
			}
			else if (rand() % 3 == 0 && USER.chip >= *betting_p_plus && *betting_p <= 5)
			{
				temp = rand() % 5 + *betting_p_plus;
				while (temp == 0 || temp - *betting_p_plus > USER.chip)
				{
					temp = rand() % 5 + *betting_p_plus;
				}
				return temp;
			}
			else
			{
				return 0;
			}
		}
		else if (*num_p > 3)
		{
			// ���� ī�尡 4, 5, 6 �̰� ���� Ĩ ������ 10�� �̻��� ���� ���󰣴�.
			if (*betting_p > 10)
			{
				return *betting_p_plus;
			}
			else if (USER.chip >= 3 + *betting_p_plus)
			{
				temp = rand() % 5 + 3 + *betting_p_plus;
				while (temp - *betting_p_plus > USER.chip)
				{
					temp = rand() % 5 + 3 + *betting_p_plus;
				}
				return temp;
			}
			else
			{
				temp = rand() % 5 + *betting_p_plus;
				while (temp == 0 || temp - *betting_p_plus > USER.chip)
				{
					temp = rand() % 5 + *betting_p_plus;
				}
				return temp;
			}
		}
		else
		{
			// ���� ī�尡 1, 2, 3 �̰� ���� Ĩ ������ 15�� �̻��� ���� ���󰣴�.
			if (*betting_p > 15)
			{
				return *betting_p_plus;
			}
			else if (USER.chip >= 5 + *betting_p_plus)
			{
				temp = rand() % 7 + 5 + *betting_p_plus;
				while (temp - *betting_p_plus > USER.chip)
				{
					temp = rand() % 7 + 5 + *betting_p_plus;
				}
				return temp;
			}
			else
			{
				temp = rand() % 5 + *betting_p_plus;
				while (temp == 0 || temp - *betting_p_plus > USER.chip)
				{
					temp = rand() % 5 + *betting_p_plus;
				}
				return temp;
			}
		}
	}
}