#ifndef __USER__ 
#define __USER__

struct
{
	char nick[12]; // �÷��̾��� �г���
	int chip; // �÷��̾��� Ĩ ��
}USER;

#endif

typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE;