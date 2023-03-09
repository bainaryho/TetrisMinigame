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
}; // [ 블록 종류 ][ 회전에 따른 모양 ] [ 색칠된 칸 ][ x,y좌표 ]

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
        cout << "□";
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

    //임시로 회전될 모양을 확인하고 회전 되는 모양이 벽이나 블럭에 막히면 회전을 안시킴
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
            return;//임시로 회전될 모양을 확인하고 회전 되는 모양이 벽이나 블럭에 막히면 회전을 안시킴
        }
    }

    /*회전이 가능한 부분은 회전 시켜줌*/
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
    case LEFT: //왼쪽방향
        ShiftBlock(-2, 0);
        break;

    case RIGHT: //오른쪽 방향. 왼쪽방향이랑 같은 원리로 동작 
        ShiftBlock(2, 0);
        break;

    case DOWN: //아래쪽 방향. 왼쪽방향이랑 같은 원리로 동작
        ShiftBlock(0, 1);
        break;

    case UP: //키보드 위쪽 눌렀을때 회전시킴. 
        //블록을 한번 회전시킴 SHAPE[7][회전][4][2] 그리고 프린트시킴
        RotateBlock();
        break;

    case SPACE:
        HardDrop();
        break;

    }
}

void Block::ShiftBlock(int x, int y) { 
    for (int i = 0; i < 4; i++) {//블럭을 이동 시키는데 조건으로 벽에 닿는지 확인
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
        if (GameTable::CheckBlock(bx + (_shape[i][0] * 2), by + _shape[i][1] + 1)) {//블럭이 바닥이나 굳은 블럭에 닿으면
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
        cout << "□";
    }
}
