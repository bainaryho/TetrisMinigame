#pragma once
#include "main.h"
using namespace std;

#define TABLE_X 12 //���̺��� ���α���
#define TABLE_Y 20 //���̺��� ���α���

#define UNBLOCK 0
#define WALL 1 //1�� �ڽ� �׵θ�
#define FIXBLOCK 2 //���� ���(���� ��)
#define GAMEOVER 3 //3�̸� ���� ����
#define BOTTOM 4 //4�� �ٴ�

class GameTable {

public:
	static int BOX[TABLE_Y][TABLE_X]; //���� ���̺�
public:
	static int X; //������ġ
	static int Y; //������ġ
	static int Score;
	static int Speed;
	static int Level;
	static int LineCount;

	static void Print_table(void); //���� ���̺� ���
	static void Reset_table(void); //���� ���̺� ����
	static void Delete_Line(void); //������ ������ ���� �����ִ� �Լ�
	static void Game_Over(void); //������ ����Ǿ����� üũ

	static bool IsBlock(int x, int y); //�̵� �� ����� �浹 ���� �˻�
	static bool CheckBlock(int x, int y); //����� ���ϋ� �浹 ���� �˻�
	static void Maps(void); //���� �������̽� ǥ��
	static void Difficulty(void); //���� ���̵� ����
	static void GetScore(void); //���ھ�����
	static void SetScore(void); //���ھ����
	
};
