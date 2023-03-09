#include "GameTable.h"
#include <iostream>
#include <fstream>

int GameTable::X = 8;
int GameTable::Y = 4;
int GameTable::Score = 0; //����
int GameTable::Speed = 800; //�ʱ�ӵ�
int GameTable::Level = 1;
int GameTable::LineCount = 0;

static int scoreList[5];

int GameTable::BOX[TABLE_Y][TABLE_X] = {
      {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
      {1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1},
      {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
      {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
      {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
      {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
      {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
      {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
      {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
      {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
      {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
      {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
      {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
      {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
      {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
      {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
      {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
      {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
      {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
      {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4}
};

void GameTable::Print_table(void) {
    for (int i = 0; i < 20; i++) {
        Cursor(X, Y + i);
        for (int j = 0; j < 12; j++) {
            if (BOX[i][j] == WALL) cout << "��";
            else if (BOX[i][j] == BOTTOM) cout << "��";
            else if (BOX[i][j] == GAMEOVER) cout << "__";
            else if (BOX[i][j] == FIXBLOCK) cout << "��";
            else cout << " .";
        }
        cout << endl;
    }
}

void GameTable::Reset_table(void) {
    for (int i = 0; i < TABLE_Y; i++) {
        for (int j = 0; j < TABLE_X; j++) {
            if (BOX[i][j] == FIXBLOCK) {
                BOX[i][j] = UNBLOCK;
            }
        }
    }
    Score = 0; //����
    Speed = 800; //�ʱ�ӵ�
    Level = 1;
    LineCount = 0;
}

void GameTable::Game_Over(void)
{
    int i = 1;
    int x = 5;
    int y = 5;
    for (i = 1; i < TABLE_X - 1; i++) {
        if (BOX[1][i] == FIXBLOCK)
        { //õ�忡 FIXBLOCK�̻����Ǹ� ���� ���� 
            Cursor(x, y + 0); cout << "�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�";
            Cursor(x, y + 1); cout << "��+-----------------------+ ��";
            Cursor(x, y + 2); cout << "��|  G A M E  O V E R..   | ��";
            Cursor(x, y + 3); cout << "��+-----------------------+ ��";
            Cursor(x, y + 4); cout << "�� YOUR SCORE :             ��"; Cursor(x + 15, y + 4); cout << Score;
            Cursor(x, y + 5); cout << "�� YOUR LEVLE :             ��"; Cursor(x + 15, y + 5); cout << Level;
            Cursor(x, y + 6); cout << "��  ESC�� ���� �ٽ� ����..  ��";
            Cursor(x, y + 7); cout << "�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�";
            GetScore();

            if (KeyControl() == ESC) {

                GameTable::Speed = 800; //�ʱ�ӵ�
                GameTable::Level = 1;
                GameTable::LineCount = 0;
                GameTable::Score = 0;
                system("cls");
                Reset_table();
            }
        }
    }
    
}

bool GameTable::IsBlock(int x, int y) { //
    if (BOX[y - Y][(x - X) / 2] == WALL
        || BOX[y - Y][(x - X) / 2] == FIXBLOCK
        || BOX[y - Y][(x - X) / 2] == BOTTOM)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool GameTable::CheckBlock(int x, int y) { //����̳� �ٴڿ� ������
    if (BOX[y - Y][(x - X) / 2] == FIXBLOCK
        || BOX[y - Y][(x - X) / 2] == BOTTOM) {
        return true;
    }
    else {
        return false;
    }
}

void GameTable::Delete_Line(void) {
    int i, j, k, l;
    int blockCount; //������ ��� ����
    int combo = 0;

    for (i = TABLE_Y - 2; i > 3;) { // i>3 : õ��Ʒ����� �˻� 
        blockCount = 0; //��ϰ��� ���� ���� �ʱ�ȭ 
        for (j = 1; j < TABLE_X - 1; j++)
        { //���� �������� ��ϰ��縦 �� 
            if (BOX[i][j] > 0) blockCount++;
        }

        if (blockCount == TABLE_X - 2)
        { //����� 10s���� �Ǹ�~
            combo = 0; //�޺� �ʱ�ȭ
            for (k = i; k > 1; k--) { ////���� ��ĭ�� ������
                for (l = 1; l < TABLE_X - 1; l++) {
                    if (BOX[k - 1][l] != GAMEOVER)
                    {
                        BOX[k][l] = BOX[k - 1][l];
                    }
                    if (BOX[k - 1][l] == GAMEOVER)
                    { 
                        BOX[k][l] = UNBLOCK; 
                    }
                    //������ õ���� ��쿡�� õ���� ��ĭ ������ �ȵǴϱ� ��ĭ�� ���� 
                }
            }
            Score = (LineCount * 100)+(combo)*10;// ���� ���� ���
        }
        else {
            i--; //18�� �˻��ϰڴ� �̼Ҹ�
        }
    }
}

void GameTable::Maps(void) {
    int y = 4;
    Cursor(TABLE_X + 20, y);   cout << "+--N E X T--+";
    Cursor(TABLE_X + 20, y+1); cout << "|           |";
    Cursor(TABLE_X + 20, y+2); cout << "|           |";
    Cursor(TABLE_X + 20, y+3); cout << "|           |";
    Cursor(TABLE_X + 20, y+4); cout << "|           |";
    Cursor(TABLE_X + 20, y+5); cout << "+-----------+";
    Cursor(TABLE_X + 20, y+6); cout << "SCORE : "; cout << Score;
    Cursor(TABLE_X + 20, y+7); cout << "LEVEL : "; cout << Level;
    Cursor(TABLE_X + 20, y + 8); cout << "COUNT : "; cout << LineCount;
}

void GameTable::Difficulty(void) {
    if (LineCount == 100) {
        Level = 10;
        int x = 14;
        int y = 15;
         Cursor(x, y + 0); cout << "�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�";
         Cursor(x, y + 1); cout << "��+------------------------+��";
         Cursor(x, y + 2); cout << "��|�١�CONGRATULATIONS!�ڡ�|��";
         Cursor(x, y + 3); cout << "��+------------------------+��";
         Cursor(x, y + 4); cout << "�� �� �� �� �� �� ��!!      ��"; 
         Cursor(x, y + 5); cout << "�� �÷��� ���ּ� �����մϴ� ��"; 
         Cursor(x, y + 6); cout << "�� �ƹ��ų� ���� �ٽ� ����..��";
         Cursor(x, y + 7); cout << "�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�";
         Sleep(5000);
    }
    else if (LineCount >= 75) {
        Speed = 100;
        Level = 9;

    }
    else if (LineCount >= 55) {
        Speed = 150;
        Level = 8;
    }
    else if (LineCount >= 40) {
        Speed = 200;
        Level = 7;

    }
    else if (LineCount >= 30) {
        Speed = 300;
        Level = 6;

    }
    else if (LineCount >= 20) {
        Speed = 400;
        Level = 5;

    }
    else if (LineCount >= 15) {
        Speed = 500;
        Level = 4;

    }
    else if (LineCount >= 10) {
        Speed = 600;
        Level = 3;

    }
    else if (LineCount >= 5) {
        Speed = 700;
        Level = 2;
    }  
}

void GameTable::GetScore(void) {

    ofstream os;
    os.open("ScoreData.txt"); // os�� ������ ���� ��� ����)

        if (Score > scoreList[0]) {
            scoreList[0] = Score;
        }
        else if (Score > scoreList[1]) {
            scoreList[1] = Score;
        }
        else if (Score > scoreList[2]) {
            scoreList[2] = Score;
        }
        else if (Score > scoreList[3]) {
            scoreList[3] = Score;
        }
        else if (Score > scoreList[4]) {
            scoreList[4] = Score;
        }

        for (int i = 0; i < 5; i++) {
            os << scoreList[i] << endl;
        }
    os.close(); // ���� �ݱ� ( ������ �������� �׻� ����� �մϴ�. )
}

void GameTable::SetScore(void) {

    ifstream fin;
    fin.open("ScoreData.txt");

    while (!fin.eof())
    {
        for (int i = 0; i < 5; i++) {
        fin >> scoreList[i];
        cout << i+1<< "�� : " << scoreList[i] << endl;
        }
    }

    fin.close();
}
