#ifndef __USER__ 
#define __USER__

struct
{
	char nick[12]; // 플레이어의 닉네임
	int chip; // 플레이어의 칩 수
}USER;

#endif

typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE;