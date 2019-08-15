#ifndef __MAIN__ 
#define __MAIN__

#include <stdio.h> // FILE
#include <stdlib.h> // exit()
#include <conio.h> // gotoxy()
#include <windows.h> // gotoxy(), Text Color, Background Color
#include <time.h> // srand()

void main_side(); // 가장자리
void main_title(); // 타이틀
void main_menu(int *); // 메뉴 구성
void main_create(); // 제작자
void main_new_nick(); // 새 닉네임 생성
void gotoxy(int, int); // 콘솔창 커서 위치 지정 함수

#endif