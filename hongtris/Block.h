#pragma once
#include "main.h"

class Block {
private:
    int bx; //기준점이 되는 좌표
    int by;
    int _shape[4][2]; //상대좌표 [색칠된칸][x,y좌표]
    int bname; // 블록형식
    int brotate; // 회전

public:
    const static int SHAPE[7][4][4][2];

    void operator=(const Block &ref); //대입연산자 오버로딩

    Block(int name, int rotate);//생성자, 블록의 시작위치는 4,20으로 해줌, _shape에 블록의 정보 저장

    void PrintBlock(void); //블록을 출력

    void DeleteBlock(void); //블록을 삭제

    void MoveBlock(int key); // 키입력에 따른 블록 움직임

    void RotateBlock(void); // 블록 회전

    void ShiftBlock(int x, int y); // 블록 이동

    bool FixBlock(void); //충돌 판정 검사

    void NewBlock(void); //새 블록 생성(쓰레기 코드)

    void HardDrop(void); // SPACE키 구현

    void ShowNextBlock(void); //다음 블록을 보여주는 함수


};