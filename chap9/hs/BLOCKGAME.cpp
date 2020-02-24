// https://jaimemin.tistory.com/382 참조.
/*
(0,0)(0,1)(0,2)(0,3)(0,4) → (0)(1)(2)(3)(4)
(1,0)(1,1)(1,2)(1,3)(1,4) → (5)(6)(7)(8)(9)
(2,0)(2,1)(2,2)(2,3)(2,4) → (10)(11)(12)(13)(14)
(3,0)(3,1)(3,2)(3,3)(3,4)
(4,0)(4,1)(4,2)(4,3)(4,4)
           ↓
□□□□□ □□□□□ □□□□□ □□□□□ □□□□□


* (y,x) 칸 = (y*5 + x) 비트
*/

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <bitset>

using namespace std;

char cache[1<<25]; // int가 아니라 char로 한 이유는 메모리!
vector<int> moves;

int cell(int y, int x)
{
    return 1 << (y*5 + x);
}

// 게임판에 놓을 수 있는 블록들의 위치 미리 계산
void preCalculate(void)
{
    // L자 모양 블럭
    // 가로/세로 2칸 씩
    for(int y=0; y<4; y++)
    {
        for(int x=0; x<4; x++)
        {
            vector<int> cells;
            for(int dy=0; dy<2; dy++)
                for(int dx=0; dx<2; dx++)
                    cells.push_back(cell(y + dy, x + dx));

            int square = cells[0] + cells[1] + cells[2] + cells[3];
            for(int k=0; k<4; k++)
                moves.push_back(square - cells[k]);
        }
    }

    // 2칸 모양 블럭
    // 1) 가로 1칸 / 세로 2칸
    // 2) 가로 2칸 / 세로 1칸
    for(int i=0; i<5; i++)
    {
        for(int j=0; j<4; j++)
        {
            moves.push_back(cell(i, j) + cell(i, j+1));
            moves.push_back(cell(j, i) + cell(j+1, i));
        }
    }

#if 1
    cout << "<moves print>" << endl;
    for(int k=0; k<moves.size(); k++)
    {
        cout << bitset<25>(moves[k]) << " ";
        if(k % 5 == 4) cout << endl;
    }
    cout << endl;
#endif
}

// 현재 게임판 상태가 board 일 때, 현재 차례인 사람이 이길지 판단
char play(int board)
{
    char& result = cache[board];

    if(result != -1) return result;

    result = 0;
    for(int i=0; i<moves.size(); i++)
    {
        if((moves[i] & board) == 0) // 아직 보드 판에 놓이지 않음
        {
            if(!play(board | moves[i])) // board 판에 놓으려는데 불가능한 경우
            {
                result = 1;
                break;
            }
        }
    }

    return result;
}

int main()
{
    int testCase;
    cin >> testCase;

    preCalculate();

    if(testCase < 1 || testCase > 50)
        exit(-1);

    for(int i=0; i<testCase; i++)
    {
        memset(cache, -1, sizeof(cache));

        // 5x5 char를 25자리의 숫자로!
        int board = 0;

        for(int j=0; j<5; j++)
        {
            for(int k=0; k<5; k++)
            {
                char ch;
                cin >> ch;

                if(ch == '#')
                    board += cell(j,k);
            }
        }

        if(play(board)) cout << "WINNING" << endl;
        else cout << "LOSING" << endl;
    }

    return 0;
}