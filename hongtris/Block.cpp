#include "Block.h"

const int Block::SHAPE[7][4][4][2] = {
    //I
    { { {0, -1}, {0, 0}, {0, 1}, {0, 2} },
    { {-2, 0}, {-1, 0}, {0, 0}, {1, 0} },
    { {0, -1}, {0, 0}, {0, 1}, {0, 2} },
    { {-2, 0}, {-1, 0}, {0, 0}, {1, 0} } },
    //L
    { { {0, -1}, {0, 0}, {0, 1}, {1, 1} },
    { {-1, 0}, {0, 0}, {1, 0}, {-1, 1} },
    { {-1, -1}, {0, -1}, {0, 0}, {0, 1} },
    { {1, -1}, {-1, 0}, {0, 0}, {1, 0} } },
    //RL
    { { {0, -1}, {0, 0}, {-1, 1}, {0, 1} },
    { {-1, -1}, {-1, 0}, {0, 0}, {1, 0} },
    { {0, -1}, {1, -1}, {0, 0}, {0, 1} },
    { {-1, 0}, {0, 0}, {1, 0}, {1, 1} } },
    //T
    { { {0, -1}, {-1, 0}, {0, 0}, {0, 1} },
    { {0, -1}, {-1, 0}, {0, 0}, {1, 0} },
    { {0, -1}, {0, 0}, {1, 0}, {0, 1} },
    { {-1, 0}, {0, 0}, {1, 0}, {0, 1} } },
    //O
    { { {0, 0}, {1, 0}, {0, 1}, {1, 1} },
    { {0, 0}, {1, 0}, {0, 1}, {1, 1} },
    { {0, 0}, {1, 0}, {0, 1}, {1, 1} },
    { {0, 0}, {1, 0}, {0, 1}, {1, 1} }, },
    //S
    { { {0, 0}, {1, 0}, {-1, 1}, {0, 1} },
    { {-1, -1}, {-1, 0}, {0, 0}, {0, 1} },
    { {0, 0}, {1, 0}, {-1, 1}, {0, 1} },
    { {-1, -1}, {-1, 0}, {0, 0}, {0, 1} } },
    //RS
    { { {-1, 0}, {0, 0}, {0, 1}, {1, 1} },
    { {0, -1}, {-1, 0}, {0, 0}, {-1, 1} },
    { {-1, 0}, {0, 0}, {0, 1}, {1, 1} },
    { {0, -1}, {-1, 0}, {0, 0}, {-1, 1} } }
}; // [ ��� ���� ][ ȸ���� ���� ��� ] [ ��ĥ�� ĭ ][ x,y��ǥ ]

Block::Block(int name, int rotate):bname(name), brotate(rotate)
{   
    bx = 20;
    by = 4;
    
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            _shape[i][j] = SHAPE[name][rotate][i][j];
        }
    }
};

void Block::operator=(const Block &ref) {
    bx = 20;
    by = 4;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            _shape[i][j] = ref._shape[i][j];
        }
    }
    bname = ref.bname;
    brotate = ref.brotate;
}

void Block::PrintBlock(void)
{
    for (int i = 0; i < 4; i++)
    {
        Cursor(bx + (_shape[i][0] * 2), by + _shape[i][1]);
        cout << "��";
    }
};

void Block::DeleteBlock(void)
{
    for (int i = 0; i < 4; i++)
    {
        Cursor(bx + _shape[i][0] * 2, by + _shape[i][1]);
        cout << "  ";
    }
}

void Block::RotateBlock(void) {

    //�ӽ÷� ȸ���� ����� Ȯ���ϰ� ȸ�� �Ǵ� ����� ���̳� ���� ������ ȸ���� �Ƚ�Ŵ
    int tempShape[4][2];
    int tempRotate = brotate;

    tempRotate = (tempRotate + 1) % 4;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            tempShape[i][j] = SHAPE[bname][tempRotate][i][j];
        }
    }

    for (int i = 0; i < 4; i++) {
        if (GameTable::IsBlock(bx + (tempShape[i][0] * 2), by + tempShape[i][1])) {
            return;//�ӽ÷� ȸ���� ����� Ȯ���ϰ� ȸ�� �Ǵ� ����� ���̳� ���� ������ ȸ���� �Ƚ�Ŵ
        }
    }

    /*ȸ���� ������ �κ��� ȸ�� ������*/
    DeleteBlock();
    brotate = (brotate + 1) % 4;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            _shape[i][j] = SHAPE[bname][brotate][i][j];
        }
    }
    PrintBlock();

}

void Block::MoveBlock(int key) {

    switch (key) {
    case LEFT: //���ʹ���
        ShiftBlock(-2, 0);
        break;

    case RIGHT: //������ ����. ���ʹ����̶� ���� ������ ���� 
        ShiftBlock(2, 0);
        break;

    case DOWN: //�Ʒ��� ����. ���ʹ����̶� ���� ������ ����
        ShiftBlock(0, 1);
        break;

    case UP: //Ű���� ���� �������� ȸ����Ŵ. 
        //����� �ѹ� ȸ����Ŵ SHAPE[7][ȸ��][4][2] �׸��� ����Ʈ��Ŵ
        RotateBlock();
        break;

    case SPACE:
        HardDrop();
        break;

    }
}

void Block::ShiftBlock(int x, int y) { 
    for (int i = 0; i < 4; i++) {//���� �̵� ��Ű�µ� �������� ���� ����� Ȯ��
        if (GameTable::IsBlock(bx + (_shape[i][0] * 2) + x, by + _shape[i][1] + y))
            return;
    }
    Block::DeleteBlock();
    bx += x;
    by += y;
    Block::PrintBlock();
}

bool Block::FixBlock(void) { 
    for (int i = 0; i < 4; i++) {
        if (GameTable::CheckBlock(bx + (_shape[i][0] * 2), by + _shape[i][1] + 1)) {//���� �ٴ��̳� ���� ���� ������
            for (int i = 0; i < 4; i++){
                GameTable::BOX[by + _shape[i][1] - GameTable::Y][(bx + (_shape[i][0]*2) - GameTable::X)/2] = FIXBLOCK;
            }
            return true;
        }
    }
    return false;
}

void Block::NewBlock(void) {
        Cursor(20, 4);
        PrintBlock();
}

void Block::HardDrop(void) {
    while (!FixBlock()) {
        MoveBlock(DOWN);
    }
}

void Block::ShowNextBlock(void) {
    for (int i = 0; i < 4; i++)
    {
        Cursor(38 + (_shape[i][0] * 2), 6 + _shape[i][1]);
        cout << "��";
    }
}
