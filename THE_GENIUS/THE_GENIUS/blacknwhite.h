#ifndef __BLACKNWHILE__ 
#define __BLACKNWHILE__

void card(int, int, int); //카드 그리기
void erazer(int, int);//카드 지우기
void randomcard(int *);//카드 섞기
void comcard(int, int, int);//컴퓨터 카드그리기
int jung(int, int *, int);//중복확인 함수
void comb(int *, int *, int *, int);//컴퓨터의 카드의 짝수와 홀수의 갯수 확인 프로그램
void comchip(int *, int *);//컴퓨터 카드에 배팅을 하는 함수, a 에 컴퓨터 카드, b에 칩
void blacknwhite_side();

#endif