#ifndef __JULDARIGI__ 
#define __JULDARIGI__

// �÷��̾� ����ü
typedef struct
{
	int score;
	int card[10];
}PLAYER;

void juldarigi();
void juldarigi_side();
void juldarigi_map(PLAYER *, PLAYER *, int *);
void juldarigi_game_board(int *);
int juldarigi_card_select(PLAYER *);

#endif