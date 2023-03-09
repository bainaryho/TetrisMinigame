#include "util.h"

//커서이동
void Cursor(int x, int y)
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//방향키 입력을 받고 입력받은 키 반환
int KeyControl(void)
{
	char key = _getch();
	if (key == 224)
	{
		switch (key)
		{
		case UP:	// ↑ 방향키 회전
			return UP;
			break;
		case LEFT:	// ← 방향키 이동
			return LEFT;
			break;
		case RIGHT:	// → 방향키 이동
			return RIGHT;
			break;
		case DOWN:	// ↓ 방향키 이동
			return DOWN;
			break;
		case SPACE: // SPACE키 이동
			return SPACE;
		case ESC:
			return ESC;
		default:
			break;
		}
	}
	else
	{
		return key;
	}
}
