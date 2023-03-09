#include "game.h"
#include <iostream> 
#include <fstream>

//���� �ʱ⼳��
void init(void)
{
	//�ܼ� �� ũ��
	system("mode con cols=60 lines=35 | title TETRIS");

	//Ŀ�� �����
	CONSOLE_CURSOR_INFO consoleCursor;
	consoleCursor.bVisible = false;
	consoleCursor.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleCursor);
}

//�޴���� �� �̵�
int Menu(void)
{
	int x = 18;		//Ŀ�� ������
	int y = 14;

	int x1 = 5; //Ÿ��Ʋȭ���� ǥ�õǴ� x��ǥ 
	int y1 = 4; //Ÿ��Ʋȭ���� ǥ�õǴ� y��ǥ  

	Cursor(x1, y1 + 0); cout << " ������������������"; Sleep(200);
	Cursor(x1, y1 + 1); cout << " ������������������"; Sleep(100);
	Cursor(x1, y1 + 2); cout << " �����                    ����"; Sleep(200);
	Cursor(x1, y1 + 3); cout << " ������������������"; Sleep(100);
	Cursor(x1, y1 + 4); cout << " ���                            ��"; Sleep(200);
	Cursor(x1 + 10, y1 + 2); cout << "  ��  Ʈ  ��  ��"; Sleep(100);
	Cursor(x1, y1 + 5); cout << " ��   ��   : ȸ��                ��"; Sleep(100);
	Cursor(x1, y1 + 6); cout << " �� ��  �� : �����̵� / �����̵� ��"; Sleep(200);
	Cursor(x1, y1 + 7); cout << " ��   ��   : �ϴ��̵�            ��"; Sleep(100);
	Cursor(x1, y1 + 8); cout << " ��  SPACE : ���                ��"; Sleep(200);
	Cursor(x1, y1 + 9); cout << " ��                            ���"; Sleep(100);
	Cursor(x1, y1 + 10); cout << " ��   Enter �� ���� �����ϼ���   ��"; Sleep(100);
	Cursor(x1, y1 + 11); cout << " ��                              ��"; Sleep(100);
	Cursor(x1, y1 + 12); cout << " ��                              �� "; 
	Cursor(x1, y1 + 13); cout << " ���                          ��� ";
	Cursor(x1, y1 + 14); cout << " ��                            ��� ";
	Cursor(x1, y1 + 15); cout << " ��                              �� ";
	Cursor(x1, y1 + 16); cout << " ��                              �� "; 
	Cursor(x1, y1 + 17); cout << " ��                  ��          �� ";
	Cursor(x1, y1 + 18); cout << " ���                ���        �� ";
	Cursor(x1, y1 + 19); cout << " ������������������  "; 
	Cursor(x - 2, y+2);
	cout << "> ���ӽ��� ";
	Cursor(x + 1, y + 4);
	cout << "���ھ�";
	Cursor(x, y + 6);
	cout << "��������";
	

	while (true)
	{
		int sel = KeyControl(); //����Ű �Է�����

		switch (sel)
		{
		case UP:
			if (y > 16) {
				Cursor(x - 2, y);
				cout << " ";
				y -= 2;		//������ �̵�
				Cursor(x - 2, y);//Ŀ���̵�
				cout << ">";
			}
			break;
		case DOWN:
			if (y < 22) {
				Cursor(x - 2, y);
				cout << " ";
				y += 2;		//������ �̵�
				Cursor(x - 2, y);//Ŀ���̵�
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

//���� ���
void ScoreInfo()
{
	system("cls"); //ȭ�� �ʱ�ȭ

	while (true)
	{
		GameTable::SetScore();

		if (KeyControl() == ESC)
			return;
	}
}

//��������
void GameInfo()
{
	system("cls"); //ȭ�� �ʱ�ȭ
	while (true)
	{

		Cursor(25, 10);
		cout << "��TETRIS��";

		Cursor(12, 16);
		cout << "��, �� ����Ű : �¿� ���̵�";
		Cursor(12, 17);
		cout << "�� ����Ű : �Ʒ��� ���̵�";
		Cursor(12, 18);
		cout << "�� ����Ű : �� ȸ��";
		Cursor(12, 19);
		cout << "SPACE : �ϵ� ���";
		Cursor(12, 20);
		cout << "ESC : ���� ȭ��";
		

		if (KeyControl() == ESC)
			return;
	}
}

//���ӽ���
void GameStart() {
	clock_t begin, now;
	int reset = 1; // ESC �÷���
	srand((unsigned int)time(NULL));
	system("cls");
	begin = clock(); //��ĭ�� �ڵ����� �������� ���� �ð� ����
	Block block(rand() % 7, 0); //��� ��ü ����

	while (reset) {
		GameTable::Delete_Line();
		GameTable::Difficulty();
		GameTable::Game_Over();
		GameTable::Maps();
	
		Block Nextblock(rand() % 7, 0); //�������� ���� ��� ����
		Nextblock.ShowNextBlock(); //������ ���� ��� ���
	
		GameTable::Print_table();
		block.PrintBlock();
		while (1) {
			now = clock(); // ��ĭ�� �ڵ����� �������� ���� �ð� ����
			if (now - begin > GameTable::Speed) {
				begin = now;
				if (block.FixBlock()) {
					block = Nextblock;
					break;
				}
				block.MoveBlock(DOWN);
			}
			if (_kbhit()) { //Ű �Է�
				int key = KeyControl();
				if (key == ESC) {
					GameTable::Reset_table();
					reset = 0; //�� while�� ���� ESC�÷��� ����
					break;
				}
				else {
					block.MoveBlock(key); //ESC�ƴϸ� ���� ����
				}
			}
		}
	}
}
