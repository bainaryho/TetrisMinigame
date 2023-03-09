#pragma once
#include "main.h"

class Block {
private:
    int bx; //�������� �Ǵ� ��ǥ
    int by;
    int _shape[4][2]; //�����ǥ [��ĥ��ĭ][x,y��ǥ]
    int bname; // �������
    int brotate; // ȸ��

public:
    const static int SHAPE[7][4][4][2];

    void operator=(const Block &ref); //���Կ����� �����ε�

    Block(int name, int rotate);//������, ����� ������ġ�� 4,20���� ����, _shape�� ����� ���� ����

    void PrintBlock(void); //����� ���

    void DeleteBlock(void); //����� ����

    void MoveBlock(int key); // Ű�Է¿� ���� ��� ������

    void RotateBlock(void); // ��� ȸ��

    void ShiftBlock(int x, int y); // ��� �̵�

    bool FixBlock(void); //�浹 ���� �˻�

    void NewBlock(void); //�� ��� ����(������ �ڵ�)

    void HardDrop(void); // SPACEŰ ����

    void ShowNextBlock(void); //���� ����� �����ִ� �Լ�


};