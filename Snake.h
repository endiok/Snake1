#define _CRT_SECURE_NO_WARNINGS 1
#ifndef __SNAKE_H__
#define __SNAKE_H__
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>//_getch()
#define HIGH 20
#define WIDE 60
struct BODY
{
	int X;
	int Y;
};
struct SNAKE
{
	int size;
	struct BODY body[HIGH*WIDE];
}snake;
int score;
int dx, dy;//ƫ������
int food[2];//food[0]Ϊx���� food[1]Ϊy����
//��¼��ĩβ����
int lx, ly;

void InitFood(void);
void InitSnake(void);
void ShowUI(void);
void PlayGame(void);
void InitWall(void);
#endif
