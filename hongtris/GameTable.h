#pragma once
#include "main.h"
using namespace std;

#define TABLE_X 12 //테이블의 가로길이
#define TABLE_Y 20 //테이블의 세로길이

#define UNBLOCK 0
#define WALL 1 //1은 박스 테두리
#define FIXBLOCK 2 //쌓인 블록(고정 됨)
#define GAMEOVER 3 //3이면 게임 오버
#define BOTTOM 4 //4는 바닥

class GameTable {

public:
	static int BOX[TABLE_Y][TABLE_X]; //게임 테이블
public:
	static int X; //시작위치
	static int Y; //시작위치
	static int Score;
	static int Speed;
	static int Level;
	static int LineCount;

	static void Print_table(void); //게임 테이블 출력
	static void Reset_table(void); //게임 테이블 리셋
	static void Delete_Line(void); //라인이 꽉차면 삭제 시켜주는 함수
	static void Game_Over(void); //게임이 종료되었는지 체크

	static bool IsBlock(int x, int y); //이동 시 블록의 충돌 판정 검사
	static bool CheckBlock(int x, int y); //블록이 쌓일떄 충돌 판정 검사
	static void Maps(void); //게임 인터페이스 표시
	static void Difficulty(void); //게임 난이도 조정
	static void GetScore(void); //스코어저장
	static void SetScore(void); //스코어출력
	
};
