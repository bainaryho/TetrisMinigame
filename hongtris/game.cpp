#include "game.h"
#include <iostream> 
#include <fstream>

//게임 초기설정
void init(void)
{
	//콘솔 앱 크기
	system("mode con cols=60 lines=35 | title TETRIS");

	//커서 숨기기
	CONSOLE_CURSOR_INFO consoleCursor;
	consoleCursor.bVisible = false;
	consoleCursor.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleCursor);
}

//메뉴출력 밑 이동
int Menu(void)
{
	int x = 18;		//커서 기준점
	int y = 14;

	int x1 = 5; //타이틀화면이 표시되는 x좌표 
	int y1 = 4; //타이틀화면이 표시되는 y좌표  

	Cursor(x1, y1 + 0); cout << " ■□□□■■■□□■■□□■■□□"; Sleep(200);
	Cursor(x1, y1 + 1); cout << " ■■■□□■□□□□■■□□■□■"; Sleep(100);
	Cursor(x1, y1 + 2); cout << " □□□■                    ■□■"; Sleep(200);
	Cursor(x1, y1 + 3); cout << " ■■□■■□□■□□□■■□□□■"; Sleep(100);
	Cursor(x1, y1 + 4); cout << " ■■                            ■"; Sleep(200);
	Cursor(x1 + 10, y1 + 2); cout << "  테  트  리  스"; Sleep(100);
	Cursor(x1, y1 + 5); cout << " □   △   : 회전                □"; Sleep(100);
	Cursor(x1, y1 + 6); cout << " □ ◁  ▷ : 좌측이동 / 우측이동 □"; Sleep(200);
	Cursor(x1, y1 + 7); cout << " □   ▽   : 하단이동            □"; Sleep(100);
	Cursor(x1, y1 + 8); cout << " ■  SPACE : 드롭                □"; Sleep(200);
	Cursor(x1, y1 + 9); cout << " ■                            ■■"; Sleep(100);
	Cursor(x1, y1 + 10); cout << " ■   Enter 를 눌러 선택하세요   ■"; Sleep(100);
	Cursor(x1, y1 + 11); cout << " □                              ■"; Sleep(100);
	Cursor(x1, y1 + 12); cout << " □                              □ "; 
	Cursor(x1, y1 + 13); cout << " ■■                          ■□ ";
	Cursor(x1, y1 + 14); cout << " ■                            ■■ ";
	Cursor(x1, y1 + 15); cout << " □                              ■ ";
	Cursor(x1, y1 + 16); cout << " □                              □ "; 
	Cursor(x1, y1 + 17); cout << " □                  ■          □ ";
	Cursor(x1, y1 + 18); cout << " ■■                ■■        ■ ";
	Cursor(x1, y1 + 19); cout << " ■■□□■■■■□□□■□□■■■  "; 
	Cursor(x - 2, y+2);
	cout << "> 게임시작 ";
	Cursor(x + 1, y + 4);
	cout << "스코어";
	Cursor(x, y + 6);
	cout << "게임종료";
	

	while (true)
	{
		int sel = KeyControl(); //방향키 입력정보

		switch (sel)
		{
		case UP:
			if (y > 16) {
				Cursor(x - 2, y);
				cout << " ";
				y -= 2;		//기준점 이동
				Cursor(x - 2, y);//커서이동
				cout << ">";
			}
			break;
		case DOWN:
			if (y < 22) {
				Cursor(x - 2, y);
				cout << " ";
				y += 2;		//기준점 이동
				Cursor(x - 2, y);//커서이동
				cout << ">";
			}
			break;
		case SPACE: case ENTER:
			return y - 16;
		default:
			break;
		}
	}
}

//점수 출력
void ScoreInfo()
{
	system("cls"); //화면 초기화

	while (true)
	{
		GameTable::SetScore();

		if (KeyControl() == ESC)
			return;
	}
}

//게임정보
void GameInfo()
{
	system("cls"); //화면 초기화
	while (true)
	{

		Cursor(25, 10);
		cout << "☆TETRIS☆";

		Cursor(12, 16);
		cout << "←, → 방향키 : 좌우 블럭이동";
		Cursor(12, 17);
		cout << "↓ 방향키 : 아래로 블럭이동";
		Cursor(12, 18);
		cout << "↑ 방향키 : 블럭 회전";
		Cursor(12, 19);
		cout << "SPACE : 하드 드롭";
		Cursor(12, 20);
		cout << "ESC : 메인 화면";
		

		if (KeyControl() == ESC)
			return;
	}
}

//게임시작
void GameStart() {
	clock_t begin, now;
	int reset = 1; // ESC 플래그
	srand((unsigned int)time(NULL));
	system("cls");
	begin = clock(); //한칸씩 자동으로 내려가기 위한 시간 정보
	Block block(rand() % 7, 0); //블록 객체 생성

	while (reset) {
		GameTable::Delete_Line();
		GameTable::Difficulty();
		GameTable::Game_Over();
		GameTable::Maps();
	
		Block Nextblock(rand() % 7, 0); //다음번에 나올 블록 생성
		Nextblock.ShowNextBlock(); //다음에 나올 블록 출력
	
		GameTable::Print_table();
		block.PrintBlock();
		while (1) {
			now = clock(); // 한칸씩 자동으로 내려가기 위한 시간 정보
			if (now - begin > GameTable::Speed) {
				begin = now;
				if (block.FixBlock()) {
					block = Nextblock;
					break;
				}
				block.MoveBlock(DOWN);
			}
			if (_kbhit()) { //키 입력
				int key = KeyControl();
				if (key == ESC) {
					GameTable::Reset_table();
					reset = 0; //밖 while문 종료 ESC플래그 세움
					break;
				}
				else {
					block.MoveBlock(key); //ESC아니면 게임 진행
				}
			}
		}
	}
}
