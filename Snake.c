#include "Snake.h"

void InitFood(void) {
	food[0] = rand() % WIDE;
	food[1] = rand() % HIGH;
}

void InitSnake(void) {
	snake.size = 2;
	snake.body[0].X = WIDE / 2;
	snake.body[0].Y = HIGH / 2;
	snake.body[1].X = WIDE / 2 - 1;
	snake.body[1].Y = HIGH / 2;
}

void ShowUI(void)
{
	COORD coord;
	//更新末尾空格
	coord.X = lx;
	coord.Y = ly;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	putchar(' ');
	//显示蛇的位置
	for (int i = 0; i < snake.size; i++) {
		coord.X = snake.body[i].X;
		coord.Y = snake.body[i].Y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);//设置控制台位置
		if(i == 0) {
			putchar('@');
		}
		else {
			putchar('*');
		}
	}
	//食物位置
	coord.X = food[0];
	coord.Y = food[1];
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	putchar('#');
}

void PlayGame(void)
{
	char key = 'D';
	//游戏是否结束判断
	while (snake.body[0].X >= 0 && snake.body[0].X <WIDE &&
		snake.body[0].Y >= 0 && snake.body[0].Y < HIGH)
	{
		//显示界面
		ShowUI();
		//方向控制
		while (_kbhit())//判断有没有输入
		{
			key = _getch();
		}
		switch (key)
		{
		case 'D':case 'd':dx = 1; dy = 0; break;
		case 'A':case 'a':dx = -1; dy = 0; break;
		case 'W':case 'w':dx = 0; dy = -1; break;
		case 'S':case 's':dx = 0; dy = 1; break;
		default:
			break;
		}
		//是否和自身碰撞
		for (int i = 1; i < snake.size; i++) {//0是蛇头 后面是身体
			if (snake.body[0].X == snake.body[i].X && snake.body[0].Y == snake.body[i].Y) {
				return;
			}
		}
		//蛇和食物
		if (snake.body[0].X == food[0] && snake.body[0].Y == food[1]) {
			InitFood();//重新生成食物
			snake.size++;//身体增长
			score+=10;//分数增长
			//关卡 速度 障碍物

		}
		//蛇更新坐标
		lx = snake.body[snake.size - 1].X;
		ly = snake.body[snake.size - 1].Y;
		for (int i = snake.size - 1; i > 0; i--) {//身体
			snake.body[i].X = snake.body[i - 1].X;
			snake.body[i].Y = snake.body[i - 1].Y;
		}
		snake.body[0].X += dx;//更新蛇头🐍
		snake.body[0].Y += dy;
		Sleep(100);
		//system("cls");
	}
}

void InitWall(void)
{
	for (int i = 0; i <= HIGH; i++) {
		for (int j = 0; j <= WIDE; j++) {
			if (i == HIGH||j==WIDE) {
				putchar('=');
			}
			else {
				putchar(' ');
			}
		}
		putchar('\n');
	}
}

#include "Snake.h"
/*
1.定义蛇的结构体
2.初始化蛇和食物
3.开始游戏
	蛇和墙的碰撞
	蛇和自身碰撞
	蛇和食物碰撞
		重新随机食物
		蛇身体增长
		分数增长
	方向控制
4.游戏结束
*/

int main() {
	srand((unsigned int)time(NULL));

	CONSOLE_CURSOR_INFO cci;//控制台去光标
	cci.dwSize = (sizeof(cci));
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);

	InitWall();
	InitFood();
	InitSnake();
	PlayGame();
	system("pause");
	return EXIT_SUCCESS;
}
