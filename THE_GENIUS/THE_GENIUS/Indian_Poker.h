#ifndef __INDIAN_POKER__ 
#define __INDIAN_POKER__

void indian_poker();
void indian_poker_side();
void indian_poker_map(int *, int *, int *);
void indian_poker_shuffle(int *, int *, int *, int *, int *);
void indian_poker_com_card(int *);
void indian_poker_player_card(int *);
void indian_poker_player_betting(int *, int *);
int indian_poker_player_betting_plus(int *, int *, int *, int *, int *);
int indian_poker_com_betting_plus(int *, int *, int *, int *, int *, int *, int *);
int indian_poker_ai(int *, int *, int *, int *, int *);

#endif