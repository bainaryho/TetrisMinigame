#include "main.h"

int main(void)
{
	init();		//초기설정

	while (true)
	{
		system("cls");		//화면 초기화
		int sel = Menu();	//메뉴 호출, 선택

		if (sel == 6)	//게임종료
			return 0;

		switch (sel)
		{

		case 0:			

			GameStart();//게임시작
			break;

		case 2:			//스코어
			ScoreInfo();
			break;


		default:
			break;

		}
	}
}
