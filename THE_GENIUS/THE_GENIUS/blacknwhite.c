#define _CRT_SECURE_NO_WARNINGS
#include "Main.h"
#include "User.h" // nick, chip
#include "Game_Select.h"
#include "blacknwhite.h"

void blacknwhite()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // Text Color White
	system("mode con:cols=90 lines=33");
	system("title BLACK N WHITE");

	int random;
	int hide[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	int pcard[9] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
	int pchip[10] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
	int tchip = 21;
	int comtchip = 0;
	int ptchip = 0;
	int knowcard[10] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
	int know = 10;
	int remain; // 남아있는 칩의 갯수
	int ccard[9] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
	int cchip[10];
	int pc[9] = { -1, -1, -1, -1, -1, -1, -1, -1, -1 };
	int i, j, k = 9, l;
	int jack = 0;
	int hol = 0;
	int jwa, jwa_temp;
	int a = 0, b = 0, temp;
	srand((unsigned)time(NULL));
	random = rand();

	blacknwhite_side();

	gotoxy(34, 12); printf("『카드를 섞어 주세요』");
	for (i = 0; i < 9; i++) card(9 * i + 5, 17, pcard[i]);

	jwa = 4;
	for (;;)//카드 섞기
	{
		gotoxy(jwa * 9 + 8, 15); printf("▼");
		a = _getch();
		if (a == 75)
		{
			if (jwa != 0)
			{
				gotoxy(jwa * 9 + 8, 15); printf("  ");
				jwa--;
			}
		}
		else if (a == 77)
		{
			if (jwa != 8)
			{
				gotoxy(jwa * 9 + 8, 15); printf("  ");
				jwa++;
			}
		}
		else if (a == 32)
		{
			if (b == 0)
			{
				card(9 * jwa + 5, 16, pcard[jwa]);
				gotoxy(9 * jwa + 5, 21); printf("        ");
				jwa_temp = jwa;
				b = 1;
			}
			else
			{
				temp = pcard[jwa];
				pcard[jwa] = pcard[jwa_temp];
				pcard[jwa_temp] = temp;
				b = 0;
				gotoxy(4, 16); printf("                                                                                  ");
				for (i = 0; i < 9; i++) card(9 * i + 5, 17, pcard[i]);
				gotoxy(4, 12); printf("                                                                                  ");
				gotoxy(34, 12); printf("『카드를 섞어 주세요』");
			}
		}
		else if (a == 13)
		{
			gotoxy(4, 16); printf("                                                                                  ");
			Sleep(500);
			break;
		}
	}

	gotoxy(jwa * 9 + 8, 15); printf("  ");
	for (i = 0; i < 9; i++) erazer(9 * i + 5, 17);

	gotoxy(4, 12); printf("                                                                                  ");
	gotoxy(35, 12); printf("『칩을 분배해주세요』");

	for (i = 0; i < 9; i++)
		if (pcard[i] != 10)
			card(9 * i + 5, 24, pcard[i]);

	jwa = 0;
	for (;;) // 칩 갯수 정하기
	{
		gotoxy(37, 18); printf("남은 칩 갯수 : %2d", tchip);
		for (j = 0; j < 9; j++)
		{
			gotoxy(9 * j + 8, 30); printf("%2d", pchip[j]);
		}
		gotoxy(9 * jwa + 8, 29); printf("▼");
		a = _getch();

		if (a == 80 && pchip[jwa] > 1) // 아래
		{
			pchip[jwa]--;
			tchip += 1;
		}
		else if (a == 75) // 왼쪽
		{
			if (jwa != 0)
			{
				gotoxy(9 * jwa + 8, 29); printf("  ");
				jwa--;
			}
		}
		else if (a == 77) // 오른쪽
		{
			if (jwa != 8)
			{
				gotoxy(9 * jwa + 8, 29); printf("  ");
				jwa++;
			}
		}
		else if (a == 72) // 위쪽
		{
			pchip[jwa]++;
			tchip -= 1;
		}
		else if (a == 13 && tchip == 0)
		{
			gotoxy(37, 18); printf("                   ");
			gotoxy(9 * jwa + 8, 29); printf("  ");
			gotoxy(4, 12); printf("                                                                                  ");
			gotoxy(4, 21); printf("                                                                                  ");
			break;
		}
	}

	randomcard(ccard);
	comchip(ccard, cchip);

	gotoxy(2, 20); printf("├──────────┐");
	gotoxy(24, 21); printf("│");
	gotoxy(24, 22); printf("┴");
	gotoxy(11, 21); printf("%s", USER.nick);

	gotoxy(64, 10); printf("┬");
	gotoxy(64, 11); printf("│");
	gotoxy(64, 12); printf("└──────────┤");
	gotoxy(73, 11); printf("컴퓨터");

	for (i = 0; i < 9; i++) // 게임 start
	{
		gotoxy(50, 15); printf("                       ");
		gotoxy(50, 16); printf("                       ");
		gotoxy(50, 17); printf("                       ");

		comtchip = 0; ptchip = 0;

		for (l = i; l < 9; l++)
		{
			if (ccard[l] < ccard[i])
				comtchip += cchip[l] - 1;

			ptchip += pchip[l] - 1;
		}//칩갯수 확인

		for (j = 0; j < 9; j++)//카드 그리기
		{
			if (hide[j] == 1)
				card(9 * j + 5, 4, ccard[j]);
			else
				comcard(9 * j + 5, 4, ccard[j]);
			card(9 * j + 5, 24, pcard[j]);
		}
		erazer(37, 17);
		erazer(37, 11);
		Sleep(1000);

		for (j = 0; j <= i; j++)
		{
			gotoxy(9 * j + 8, 2); printf("%2d", cchip[j]);//칩을 그린다
		}

		for (j = 0; j < 9; j++)
		{
			gotoxy(9 * j + 8, 30); printf("%2d", pchip[j]);//플레이어칩
		}

		erazer(9 * i + 5, 24);
		card(37, 17, pcard[i]);//나의 카드낸다
		erazer(9 * i + 5, 4);
		comcard(37, 11, ccard[i]);//여기는 컴카드
		Sleep(1000);

		if (pchip[i] == cchip[i])//칩이 같으면 
		{
			hide[i] = 1;
			knowcard[i] = pcard[i];
			know--;
			if (pcard[i] == ccard[i])//crad가 같을 경우
			{

				gotoxy(52, 16); printf("무승부 입니다");
				Sleep(2000);
				continue;
			}
			else if (pcard[i] < ccard[i])
			{
				gotoxy(52, 16); printf("컴퓨터의 승리입니다");
				Sleep(2000);
				cchip[i] = cchip[i] + pchip[i];
				pchip[i] = 0;
				continue;
			}
			else if (pcard[i] > ccard[i])
			{
				gotoxy(52, 16); printf("플레이어의 승리입니다");
				Sleep(2000);
				pchip[i] = cchip[i] + pchip[i];
				cchip[i] = 0;
				continue;
			}
		}


		else if (pchip[i] < cchip[i])//칩이 다르다면 내가 작음
		{
			if (ptchip < cchip[i])
			{
				gotoxy(52, 16); printf("칩이 부족해서");
				gotoxy(52, 17); printf("레이즈를 할 수 없습니다");
				Sleep(1000);

				gotoxy(52, 16); printf("                  ");
				gotoxy(52, 17); printf("                        ");
				knowcard[i] = pcard[i];
				know--;
				if (pcard[i] == ccard[i])//crad가 같을 경우
				{
					gotoxy(52, 16); printf("무승부 입니다");
					Sleep(1000);
					continue;
				}
				else if (pcard[i] < ccard[i])
				{
					gotoxy(52, 16); printf("컴퓨터의 승리입니다");
					Sleep(1000);
					cchip[i] = cchip[i] + pchip[i];
					pchip[i] = 0;
					continue;
				}
				else if (ccard[i] > pcard[i]);
				{
					gotoxy(52, 16); printf("플레이어의 승리입니다");
					Sleep(1000);
					pchip[i] = cchip[i] + pchip[i];
					cchip[i] = 0;
					continue;
				}
			}
			else {
				gotoxy(52, 15); printf("1.포기하시겠습니까?");
				gotoxy(52, 17); printf("2.레이즈 하시겠습니까?");
				jwa = 15;

				while (1)
				{
					gotoxy(50, jwa); printf("▶");
					a = _getch();
					if (a == 80)//아래쪽
					{
						if (jwa == 15)
						{
							gotoxy(50, jwa); printf("  ");
							jwa += 2;
						}
					}

					else if (a == 72)//위쪽
					{
						if (jwa == 17)
						{
							gotoxy(50, jwa); printf("  ");
							jwa -= 2;
						}
					}
					else if (a == 13)
					{
						gotoxy(50, 17); printf("  ");
						gotoxy(50, 15); printf("  ");
						break;
					}
				}//검색 끝

				if (jwa == 15)
				{
					gotoxy(52, 15); printf("                       ");
					gotoxy(52, 17); printf("                       ");
					gotoxy(52, 15); printf("1.포기하셨습니다.              ");

					cchip[i] = cchip[i] + pchip[i];
					pchip[i] = 0;
					Sleep(1000);
					continue;
				}
				else if (jwa == 17)//2를 선택시
				{
					gotoxy(52, 15); printf("                       ");
					gotoxy(52, 17); printf("                       ");
					gotoxy(52, 17); printf("2.레이즈 하셨습니다.             ");
					Sleep(1000);
					gotoxy(52, 17); printf("                           ");
					k = i + 1;

					while (1)//칩 갯수 정하기
					{
						for (j = i; j < 9; j++)
						{
							gotoxy(9 * j + 8, 30); printf("%2d ", pchip[j]);
						}

						gotoxy(9 * k + 8, 29); printf("▼");
						a = _getch();

						if (a == 80 && pchip[k] != 0)//아래
						{
							pchip[i]++;
							pchip[k]--;
						}

						else if (a == 75)//왼쪽
						{
							if (k != i + 1)
							{
								gotoxy(9 * k + 8, 29); printf("  ");
								k -= 1;
							}
						}

						else if (a == 77)//오른쪽
						{
							if (k != 8)
							{
								gotoxy(9 * k + 8, 29); printf("  ");
								k += 1;
							}
						}

						else if (a == 72)//위쪽
						{
							pchip[i]--;
							pchip[k]++;
						}

						else if (a == 13 && pchip[i] == cchip[i])
						{
							gotoxy(9 * k + 8, 29); printf("  ");
							Sleep(1000);
							break;
						}
					}
					knowcard[i] = pcard[i];
					know--;
					hide[i] = 1;
					if (pcard[i] == ccard[i])//crad가 같을 경우
					{
						gotoxy(52, 16); printf("무승부 입니다");
						Sleep(1000);
						continue;
					}
					else if (pcard[i] < ccard[i])
					{
						gotoxy(52, 16); printf("컴퓨터의 승리입니다");
						Sleep(1000);
						cchip[i] = cchip[i] + pchip[i];
						pchip[i] = 0;
						continue;
					}
					else if (ccard[i] > pcard[i]);
					{
						gotoxy(52, 16); printf("플레이어의 승리입니다");
						Sleep(1000);
						pchip[i] = cchip[i] + pchip[i];
						cchip[i] = 0;
						continue;//여기까지 스페이스바로 칩결정
					}
				}
			}//2를 선택한다 끝
		}//칩이 작다 끝

		else if (cchip[i] < pchip[i])//여기서 인공지능을 만들자
		{
			if (comtchip < pchip[i])//컴퓨터가 레이즈를 할수 없을 경우
			{
				gotoxy(50, 16); printf("컴퓨터가 레이즈를");
				gotoxy(50, 17); printf("할 수 없습니다");
				Sleep(1000);
				gotoxy(50, 16); printf("플레이어의 승리입니다            ");
				gotoxy(50, 17); printf("                ");
				Sleep(1000);
				pchip[i] = cchip[i] + pchip[i];
				cchip[i] = 0;
				continue;
			}

			else if (ccard[i] < 4)//컴퓨터의 숫자가 0,1,2,3 일때는 레이즈 포기
			{
				gotoxy(50, 16); printf("컴퓨터가 레이즈를 포기합니다");
				Sleep(1000);
				gotoxy(50, 16); printf("플레이어의 승리입니다        ");
				Sleep(1000);
				pchip[i] = cchip[i] + pchip[i];
				cchip[i] = 0;
				continue;
			}

			else if (ccard[i] > 6)
			{
				remain = 0;
				for (l = i; l < 9; l++)
				{
					if (ccard[l]>3 && ccard[l] < 7)
						remain += ccard[l];
				}

				if ((pchip[i] - cchip[i]) > remain)
				{
					gotoxy(52, 16); printf("컴퓨터가 레이즈를 포기합니다");
					Sleep(1000);
					gotoxy(52, 16); printf("플레이어의 승리입니다        ");
					Sleep(1000);
					pchip[i] = cchip[i] + pchip[i];
					cchip[i] = 0;
					continue;
				}

				else//여기서 칩은 되는데 뽑아올수가 없다면 레이즈가 정지한다. 이거까지만 구형하자
				{
					gotoxy(52, 16); printf("컴퓨터가 레이즈합니다");
					Sleep(1000);

					for (l = i + 1; l < 9; l++)
					{
						if (cchip[l] != 1 && ccard[l] < ccard[i])
						{
							cchip[l]--;
							cchip[i]++;
						}
						else if (pchip[i] == cchip[i])
							break;

						else if (l == 8)
						{
							l = i + 1;
						}
					}

					for (j = 0; j <= i; j++)
					{
						gotoxy(9 * k + 8, 2); printf("%2d", cchip[j]);//칩을 그린다
					}
					for (j = 0; j < 9; j++)
					{
						gotoxy(9 * k + 8, 30); printf("%2d", pchip[j]);//플레이어칩
					}


					if (pcard[i] == ccard[i])//crad가 같을 경우
					{
						gotoxy(52, 16); printf("무승부 입니다.     ");
						Sleep(1000);
						continue;
					}
					else if (pcard[i] < ccard[i])
					{
						gotoxy(52, 16); printf("컴퓨터의 승리입니다 ");
						Sleep(1000);
						cchip[i] = cchip[i] + pchip[i];
						pchip[i] = 0;
						continue;
					}
					else if (ccard[i] > pcard[i]);
					{
						gotoxy(52, 16); printf("플레이어의 승리입니다  ");
						Sleep(1000);
						pchip[i] = cchip[i] + pchip[i];
						cchip[i] = 0;
						continue;//7,8,9, 일때 레이즈 하기
					}
				}
			}

			else//4,5,6 일때
			{
				remain = 0;
				for (l = i; l < 9; l++)
				{
					if (ccard[l]>0 && ccard[l] < 4)
						remain += ccard[l];
				}

				if ((pchip[i] - cchip[i]) > remain)
				{
					gotoxy(52, 16); printf("컴퓨터가 레이즈를 포기합니다");
					Sleep(1000);
					gotoxy(52, 16); printf("플레이어의 승리입니다        ");
					Sleep(1000);
					pchip[i] = cchip[i] + pchip[i];
					cchip[i] = 0;
					continue;
				}

				else
				{
					gotoxy(52, 16); printf("컴퓨터가 레이즈합니다");
					Sleep(1000);

					for (l = i + 1; l < 9; l++)
					{
						if (pchip[i] == cchip[i])
							break;

						else if (cchip[l] != 1 && ccard[l] < 4)
						{
							cchip[l]--;
							cchip[i]++;
						}

						else if (l == 8)
							l = i + 1;
					}


					if (pcard[i] == ccard[i])//crad가 같을 경우
					{
						gotoxy(52, 16); printf("무승부 입니다");
						Sleep(1000);
						continue;
					}
					else if (pcard[i] < ccard[i])
					{
						gotoxy(52, 16); printf("컴퓨터의 승리입니다");
						Sleep(1000);
						cchip[i] = cchip[i] + pchip[i];
						pchip[i] = 0;
						continue;
					}
					else if (ccard[i] > pcard[i]);
					{
						gotoxy(52, 16); printf("플레이어의 승리입니다");
						Sleep(1000);
						pchip[i] = cchip[i] + pchip[i];
						cchip[i] = 0;
						continue;//4,5,6 일때 레이즈 하기
					}
				}
			}
		}
		Sleep(2000);
	}

	gotoxy(50, 15); printf("                       ");
	gotoxy(50, 16); printf("                       ");

	if (hide[8] == 1)
		card(9 * 8 + 5, 4, ccard[8]);
	else
		comcard(9 * 8 + 5, 4, ccard[8]);
	card(9 * 8 + 5, 24, pcard[8]);

	erazer(37, 17); // 남은 카드 다 지우기
	erazer(37, 11);

	gotoxy(9 * 8 + 8, 2); printf("%2d", cchip[8]);//칩을 그린다
	gotoxy(9 * 8 + 8, 30); printf("%2d", pchip[8]);

	for (j = 0; j < 8; j++)
	{
		gotoxy(9 * j + 13, 2); printf("+"); // 더하기를 그린다
		gotoxy(9 * j + 13, 30); printf("+");
		Sleep(500);
	}

	comtchip = 0; ptchip = 0;
	for (j = 0; j < 9; j++)
	{
		comtchip += cchip[j];
		ptchip += pchip[j];
	}

	gotoxy(39, 14); printf("컴퓨터  플레이어");
	gotoxy(42, 16); printf("%d VS %d", comtchip, ptchip);
	Sleep(1000);

	if (comtchip < ptchip)
	{
		gotoxy(26, 18); printf("플레이어가 승리하여 %d개의 칩을 받았습니다", (ptchip - comtchip) * 2);
		USER.chip += (ptchip - comtchip) * 2;
	}
	else if (comtchip > ptchip)
	{
		gotoxy(26, 18); printf("플레이어가 패배하여 %d개의 칩을 잃었습니다", (comtchip - ptchip) * 2);
		USER.chip -= (comtchip - ptchip) * 2;
	}
	else
	{
		gotoxy(39, 18); printf("무승부 입니다");
	}
	while (1) { if (_getch() == 13)	break; }
	game_select();
}

void blacknwhite_side()
{
	int i;
	system("cls");
	gotoxy(2, 1);  printf("┌─────────────────────────────────────────┐");
	gotoxy(2, 31); printf("└─────────────────────────────────────────┘");
	for (i = 2; i < 31; i++)
	{
		gotoxy(2, i);  printf("│");
		gotoxy(86, i); printf("│");
	}
	gotoxy(2, 10); printf("├─────────────────────────────────────────┤");
	gotoxy(2, 22); printf("├─────────────────────────────────────────┤");
}

int jung(int a, int *pb, int k) //중복확인 함수 hi =1 이면 중복
{
	int i; int hi = 0;
	for (i = 0; i <= k; i++)
	{
		if (a == pb[i])
			hi = 1;
	}
	return hi;
}

void randomcard(int *parr)//카드 섞기
{
	int i, k;
	srand((unsigned)time(NULL));

	parr[0] = (rand()) % 9;

	for (i = 0; i < 9; i++)
	{
		for (k = 0; k < i; k++)
		{
			for (;;)
			{
				if (parr[i] != parr[k])
					if (i == 8)
						break;
					else if (parr[i - 1] + 1 != parr[i])
						break;
					else
					{
						parr[i] = (rand()) % 9;
						k = 0;
					}
				else
				{
					parr[i] = (rand()) % 9;
					k = 0;
				}
			}
		}
	}
}

void erazer(int x, int y)//카드 지우기
{
	gotoxy(x, y);     printf("        ");
	gotoxy(x, y + 1); printf("        ");
	gotoxy(x, y + 2); printf("        ");
	gotoxy(x, y + 3); printf("        ");
	gotoxy(x, y + 4); printf("        ");
}

void comcard(int x, int y, int c) // 컴퓨터 카드 그리기
{
	if (c % 2 == 1) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240); // Background Color White
	else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 128); // Background Color Gray

	gotoxy(x, y);     printf("┌──┐");
	gotoxy(x, y + 1); printf("│    │");
	gotoxy(x, y + 2); printf("│ ▒ │");
	gotoxy(x, y + 3); printf("│    │");
	gotoxy(x, y + 4); printf("└──┘");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

void card(int x, int y, int c) // 플레이어 카드 그리기
{
	if (c % 2 == 1) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240); // Background Color White
	else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 128); // Background Color Gray
	gotoxy(x, y);     printf("┌──┐");
	gotoxy(x, y + 1); printf("│    │");
	gotoxy(x, y + 2); printf("│ %02d │", c);
	gotoxy(x, y + 3); printf("│    │");
	gotoxy(x, y + 4); printf("└──┘");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

void comb(int *arr, int *a, int *b, int k)
{
	int i;

	for (i = k + 1; i < 9; i++)
	{
		if (arr[i] % 2 == 0)
			(*a)++;
		else
			(*b)++;
	}
}

void comchip(int *a, int *b)
{
	int random;
	int i;
	int arr[16][9] = { { 1, 1, 1, 2, 3, 4, 6, 6, 6 }, { 1, 1, 1, 2, 3, 5, 5, 5, 7 }, { 1, 1, 1, 2, 3, 4, 6, 6, 6 }, { 1, 1, 1, 1, 4, 3, 6, 6, 7 },
	{ 22, 1, 1, 1, 1, 1, 1, 1, 1 }, { 1, 1, 1, 1, 1, 1, 1, 1, 22 }, { 1, 1, 1, 1, 1, 6, 5, 7, 7 }, { 1, 1, 1, 1, 3, 3, 6, 6, 8 },
	{ 1, 1, 1, 2, 3, 4, 6, 6, 6 }, { 1, 1, 1, 2, 3, 5, 5, 5, 7 }, { 1, 1, 1, 2, 3, 4, 6, 6, 6 }, { 1, 1, 1, 1, 4, 3, 6, 6, 7 },
	{ 1, 1, 1, 2, 3, 4, 6, 6, 6 }, { 1, 1, 1, 1, 1, 6, 5, 7, 7 }, { 1, 1, 1, 1, 3, 3, 6, 6, 8 }, { 1, 1, 1, 1, 4, 3, 6, 6, 7 } };

	srand((unsigned)time(NULL));
	random = rand();

	for (i = 0; i < 9; i++)
		b[a[i]] = arr[(random % 16)][i];
}