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

	int num_c, num_p; // 컴퓨터 카드, 플레이어 카드
	int betting_c = 0, betting_p = 0; // 베팅한 칩
	int betting_c_plus = 0, betting_p_plus = 0; // 추가 베팅한 칩
	int win = 0, draw = 0; // 승, 패, 무승부
	int card[10] = { 0 };
	int card_count = 0;

	srand(time(NULL));
	win = rand() % 2; // 선공, 후공 정하기

	while (USER.chip > 0 || draw && USER.chip == 0) // 유저 칩 수가 0개이고 이전 카드가 무승부 였을 때
	{
		indian_poker_side();
		indian_poker_map(&betting_c, &betting_p, &card_count);
		betting_p_plus = 0; betting_c_plus = 0;

		if (card_count == 20)
		{
			USER.chip += betting_p;
			gotoxy(18, 14);	printf("『20장의 카드를 다 사용하여 게임을 종료합니다』");
			while (1) { if (_getch() == 13)	break; }
			game_select();
			return;
		}

		gotoxy(27, 14);	printf("『카드를 나눠드리겠습니다』");
		while (1) { if (_getch() == 13)	break; }
		indian_poker_shuffle(card, &num_c, &num_p, &betting_p, &card_count);

		if (!draw) // 무승부 일때는 기본 베팅을 하지 않음
		{
			indian_poker_map(&betting_c, &betting_p, &card_count);
			gotoxy(20, 14);	printf("『기본 베팅으로 칩 하나씩 베팅해주십시오』");
			while (1) { if (_getch() == 13)	break; }
			USER.chip--; betting_c++; betting_p++;
		}
		indian_poker_map(&betting_c, &betting_p, &card_count);

		if (win == 0 && USER.chip != 0) // win == 0 이면 컴퓨터 선 베팅
		{
			gotoxy(28, 14);	printf("『컴퓨터 선 베팅입니다』");
			while (1) { if (_getch() == 13)	break; }

			betting_c_plus = indian_poker_ai(&num_c, &num_p, &card_count, &betting_p, &betting_p_plus);
			betting_c += betting_c_plus;
			indian_poker_map(&betting_c, &betting_p, &card_count);

			if (betting_c_plus == 0)
			{
				gotoxy(24, 14);	printf("『컴퓨터가 베팅을 포기하였습니다』");
				betting_c_plus = -1; // 컴퓨터가 베팅을 포기했을 경우 -1
			}
			else
			{
				gotoxy(25, 14);	printf("『컴퓨터가 %d개 베팅하였습니다』", betting_c_plus);
			}
			while (1) { if (_getch() == 13)	break; }


			while (betting_c_plus != -1) { // 컴퓨터가 베팅을 포기하지 않았을 경우 추가 베팅
				// 추가 베팅이 없었을 경우 참
				if (indian_poker_player_betting_plus(&betting_p, &betting_c, &betting_p_plus, &betting_c_plus, &card_count)) break;
				if (indian_poker_com_betting_plus(&num_p, &num_c, &betting_p, &betting_c, &betting_p_plus, &betting_c_plus, &card_count)) break;
			}
		}
		else if (win == 1 && USER.chip != 0) // win == 1 이면 플레이어 선 베팅
		{
			indian_poker_map(&betting_c, &betting_p, &card_count);
			gotoxy(27, 14);	printf("『플레이어 선 베팅입니다』");

			indian_poker_player_betting(&betting_p_plus, &betting_c_plus);
			betting_p += betting_p_plus;
			USER.chip -= betting_p_plus;
			indian_poker_map(&betting_c, &betting_p, &card_count);

			if (betting_p_plus == 0)
			{
				gotoxy(23, 14);	printf("『플레이어가 베팅을 포기하였습니다』");
				betting_p_plus = -1; // 플레이어가 베팅을 포기했을 경우 -1
			}
			else
			{
				gotoxy(24, 14);	printf("『플레이어가 %d개 베팅하였습니다』", betting_p_plus);
			}
			while (1) { if (_getch() == 13)	break; }


			while (betting_p_plus != -1) { // 플레이어가 베팅을 포기하지 않았을 경우 추가 베팅
				// 추가 베팅이 없었을 경우 참
				if (indian_poker_com_betting_plus(&num_p, &num_c, &betting_p, &betting_c, &betting_p_plus, &betting_c_plus, &card_count)) break;
				if (indian_poker_player_betting_plus(&betting_p, &betting_c, &betting_p_plus, &betting_c_plus, &card_count)) break;
			}
		}

		indian_poker_map(&betting_c, &betting_p, &card_count);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240); // Background Color White
		indian_poker_player_card(&num_p);

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // Text Color White
		gotoxy(28, 14); printf("『카드를 공개하겠습니다』");
		while (1) { if (_getch() == 13)	break; }

		if (betting_p_plus == -1 && num_p == 10) // 플레이어 카드가 10일 때 포기한 경우
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
			gotoxy(10, 14);	printf("『10카드 일때 베팅을 포기해서, 패널티로 10개의 칩을 잃습니다』");
			while (1) { if (_getch() == 13)	break; }
		}
		else if (betting_c_plus == -1 && num_c == 10) // 컴퓨터 카드가 10일 때 포기한 경우
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
			gotoxy(10, 14);	printf("『10카드 일때 베팅을 포기해서, 패널티로 10개의 칩을 잃습니다』");
			while (1) { if (_getch() == 13)	break; }
		}
		else if (num_c > num_p && betting_p_plus != -1 || betting_p_plus == -1) // 컴퓨터 카드 수가 크거나 플레이어가 포기한 경우
		{
			betting_c = 0; betting_p = 0;
			win = 0; draw = 0;
			indian_poker_map(&betting_c, &betting_p, &card_count);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 207); // Background Color Red
			indian_poker_player_card(&num_p);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 159); // Background Color Blue
			indian_poker_com_card(&num_c);

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // Text Color White
			gotoxy(24, 14);	printf("『컴퓨터가 이번 판을 이겼습니다』");
			while (1) { if (_getch() == 13)	break; }
		}
		else if (num_c < num_p && betting_c_plus != -1 || betting_c_plus == -1) // 플레이어 카드 수가 크거나 컴퓨터가 포기한 경우
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
			gotoxy(23, 14);	printf("『플레이어가 이번 판을 이겼습니다』");
			while (1) { if (_getch() == 13)	break; }
		}
		else if (num_c == num_p) // 카드 숫자가 같을 경우
		{
			draw = 1;
			indian_poker_map(&betting_c, &betting_p, &card_count);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 160); // Background Color Green
			indian_poker_player_card(&num_p);
			indian_poker_com_card(&num_c);

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // Text Color White
			gotoxy(28, 14);	printf("『이번 판은 무승부입니다』");
			while (1) { if (_getch() == 13)	break; }
		}

		// 칩 개수 자동 저장
		FILE * fout = fopen("save.tg", "wb");
		fwrite(&USER, sizeof(USER), 1, fout);
		fclose(fout);
	}
	bankrupt(); // 파산
}

void indian_poker_side()
{
	int i;
	system("cls");
	gotoxy(2, 1);  printf("┌────────────────────────────────────┐");
	gotoxy(2, 28); printf("└────────────────────────────────────┘");
	for (i = 2; i < 28; i++)
	{
		gotoxy(2, i);  printf("│");
		gotoxy(76, i); printf("│");
	}
}

void indian_poker_map(int * betting_c, int * betting_p, int * card_count)
{
	gotoxy(2, 7);   printf("├────────────────────────────────────┤");
	gotoxy(2, 13);  printf("├────────────────────────────────────┤");
	gotoxy(4, 14);	printf("                                                                        ");
	gotoxy(2, 15);  printf("├────────────────────────────────────┤");
	gotoxy(2, 22);  printf("├────────────────────────────────────┤");

	gotoxy(4, 2);  printf("┌───────────┐");
	gotoxy(4, 3);  printf("│                      │");
	gotoxy(4, 4);  printf("│        컴퓨터        │");
	gotoxy(4, 5);  printf("│                      │");
	gotoxy(4, 6);  printf("└───────────┘");
	gotoxy(50, 2);	printf("┌───────────┐");
	gotoxy(50, 3);  printf("│                      │");
	gotoxy(50, 4);  printf("│  남은카드 : (%02d/20)  │", *card_count);
	gotoxy(50, 5);  printf("│                      │");
	gotoxy(50, 6);  printf("└───────────┘");
	gotoxy(4, 9);	printf("                                                                        ");
	gotoxy(28, 7);	printf("┬──────────┬");
	gotoxy(28, 8);	printf("│                    │");
	gotoxy(28, 9);	printf("└──────────┘");
	gotoxy(33, 8);  printf("베팅한 칩 : %d", *betting_c);

	gotoxy(4, 23);  printf("┌───────────┐");
	gotoxy(4, 24);  printf("│                      │");
	gotoxy(4, 25);  printf("│                      │");
	gotoxy(4, 26);  printf("│                      │");
	gotoxy(4, 27);  printf("└───────────┘");
	gotoxy(14, 25);	printf("%s", USER.nick);
	gotoxy(50, 23);	printf("┌───────────┐");
	gotoxy(50, 24); printf("│                      │");
	gotoxy(50, 25); printf("│                      │");
	gotoxy(50, 26); printf("│                      │");
	gotoxy(50, 27); printf("└───────────┘");
	gotoxy(57, 25); printf("남은 칩 : %d", USER.chip);
	gotoxy(4, 20);	printf("                                                                        ");
	gotoxy(28, 20);	printf("┌──────────┐");
	gotoxy(28, 21);	printf("│                    │");
	gotoxy(28, 22);	printf("┴──────────┴");
	gotoxy(33, 21);	printf("베팅한 칩 : %d", *betting_p);

	gotoxy(64, 20);	printf("┌───┐");
	gotoxy(64, 21);	printf("│      │");
	gotoxy(64, 22);	printf("┴───┴");
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
			gotoxy(35, 23); printf("┌───┐");
			gotoxy(35, 24); printf("│      │");
			gotoxy(35, 25); printf("│  ▒  │");
			gotoxy(35, 26); printf("│      │");
			gotoxy(35, 27); printf("└───┘");
			break;
		}
	}
	*card_count += 2;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // Text Color White
}

void indian_poker_com_card(int * num_c)
{
	gotoxy(35, 2); printf("┌───┐");
	gotoxy(35, 3); printf("│      │");
	gotoxy(35, 4); printf("│  %02d  │", *num_c);
	gotoxy(35, 5); printf("│      │");
	gotoxy(35, 6); printf("└───┘");
}

void indian_poker_player_card(int * num_p)
{
	gotoxy(35, 23); printf("┌───┐");
	gotoxy(35, 24); printf("│      │");
	gotoxy(35, 25); printf("│  %02d  │", *num_p);
	gotoxy(35, 26); printf("│      │");
	gotoxy(35, 27); printf("└───┘");
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
	// 플레리어 추가 베팅 차례
	indian_poker_map(betting_c, betting_p, card_count);
	gotoxy(26, 14);	printf("『플레이어 베팅 차례입니다』");

	indian_poker_player_betting(betting_p_plus, betting_c_plus);
	*betting_p += *betting_p_plus;
	USER.chip -= *betting_p_plus;
	indian_poker_map(betting_c, betting_p, card_count);

	if (*betting_p_plus == 0)
	{
		gotoxy(23, 14);	printf("『플레이어가 베팅을 포기하였습니다』");
		*betting_p_plus = -1; // 플레이어가 베팅을 포기했을 경우 -1
		while (1) { if (_getch() == 13)	break; }
		return 1;
	}
	else if (*betting_p_plus == *betting_c_plus)
	{
		gotoxy(25, 14);	printf("『플레이어가 %d개에 응했습니다』", *betting_c_plus);
		while (1) { if (_getch() == 13)	break; }
		return 1;
	}
	else if (*betting_p_plus > *betting_c_plus)
	{
		gotoxy(18, 14);	printf("『플레이어가 %d개 받고 %d개 추가베팅하였습니다』", *betting_c_plus, *betting_p_plus - *betting_c_plus);
		*betting_p_plus -= *betting_c_plus; // 추가 베팅 한 만큼 betting_p_plus에 저장
		while (1) { if (_getch() == 13)	break; }
	}
	return 0;
}

int indian_poker_com_betting_plus(int * num_p, int * num_c, int * betting_p, int * betting_c, int * betting_p_plus, int * betting_c_plus, int * card_count)
{
	// 컴퓨터 추가 베팅 차례
	indian_poker_map(betting_c, betting_p, card_count);
	gotoxy(27, 14);	printf("『컴퓨터 베팅 차례입니다』");
	while (1) { if (_getch() == 13)	break; }

	*betting_c_plus = indian_poker_ai(num_c, num_p, card_count, betting_p, betting_p_plus);
	*betting_c += *betting_c_plus;
	indian_poker_map(betting_c, betting_p, card_count);

	if (*betting_c_plus == 0)
	{
		gotoxy(24, 14);	printf("『컴퓨터가 베팅을 포기하였습니다』");
		*betting_c_plus = -1; // 컴퓨터가 베팅을 포기했을 경우 -1
		while (1) { if (_getch() == 13)	break; }
		return 1;
	}
	else if (*betting_c_plus == *betting_p_plus)
	{
		gotoxy(25, 14);	printf("『컴퓨터가 %d개에 응했습니다』", *betting_p_plus);
		while (1) { if (_getch() == 13)	break; }
		return 1;
	}
	else if (*betting_c_plus > *betting_p_plus)
	{
		gotoxy(19, 14);	printf("『컴퓨터가 %d개 받고 %d개 추가베팅하였습니다』", *betting_p_plus, *betting_c_plus - *betting_p_plus);
		*betting_c_plus -= *betting_p_plus; // 추가 베팅 한 만큼 betting_c_plus에 저장
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
			// 10분의 1 확률로 블러핑
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
			// 상대방 카드가 7, 8, 9 이고 베팅 칩 개수가 5개에서 15개 사이일 때는 따라간다.
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
			// 상대방 카드가 4, 5, 6 이고 베팅 칩 개수가 10개 이상일 때는 따라간다.
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
			// 상대방 카드가 1, 2, 3 이고 베팅 칩 개수가 15개 이상일 때는 따라간다.
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