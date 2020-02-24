// https://sangdo913.tistory.com/85 참조

#include <iostream>
#include <vector>
#include <string>

using namespace std;

char board[3][3];
char initTurn = 'x';
// 메모이제이션
int cache[19683]; // 3^9

// 한 줄이 완성되었는지
bool isFinished(char turn)
{
    // 가로
    for(int i=0; i<3; i++)
    {
        if(board[i][0] == turn && board[i][1] == turn && board[i][2] == turn)
            return true;
    }

    // 세로
    for(int j=0; j<3; j++)
    {
        if(board[0][j] == turn && board[1][j] == turn && board[2][j] == turn)
            return true;
    }

    // 대각선 ↘
    if(board[0][0] == turn && board[1][1] == turn && board[2][2] == turn)
        return true;

    // 대각선 ↙
    if(board[0][2] == turn && board[1][1] == turn && board[2][0] == turn)
        return true;

    return false;
}

int calcResult()
{
    int result = 0;
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            result *= 3;
            if(board[i][i] == 'o')
                result++;
            else if(board[i][j] == 'x')
                result += 2;
        }
    }
    return result;
}

int canWin(char turn)
{
    // 기저 사례 : 마지막에 둬서 한 줄이 만들어진 경우
    if(isFinished('o'+'x'-turn)) return -1;

    int& result = cache[calcResult()];
    if(result != -2) return result;

    // 모든 반환 값의 min
    int minValue = 2;

    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            if(board[i][j] == '.')
            {
                board[i][j] = turn;
                minValue = min(minValue, canWin('o'+'x'-turn));
                board[i][j] = '.';
            }
        }
    }

    // 플레이할 수 없거나 어떻게 해도 비기는 경우
    if(minValue == 2 || minValue == 0) return result = 0;
    result -= minValue;
    return result;
}

int main()
{
    int testCase;
    cin >> testCase;

    if(testCase < 1 || testCase > 50)
        exit(-1);

    for(int j=0; j<19683; j++)
        cache[j] = -2;

    int x_num, o_num;
    for(int i=0; i<testCase; i++)
    {
        x_num, o_num = 0;

        for(int i=0; i<3; i++)
        {
            for(int j=0; j<3; j++)
            {
                cin >> board[i][j];

                if(board[i][j] == 'x') x_num++;
                else if (board[i][j] == 'o') o_num++;
            }
        }

        if(x_num <= o_num) initTurn = 'x';
        else if(x_num > o_num) initTurn = 'o';

        int get = canWin(initTurn);

        if(initTurn == 'x')
        {
            if(get == 1) cout << "x" << endl;
            else if(get == 0) cout << "TIE" << endl;
            else if(get == -1) cout << "o" << endl;
        }
        else if(initTurn == 'o')
        {
            if(get == 1) cout << "o" << endl;
            else if(get == 0) cout << "TIE" << endl;
            else if(get == -1) cout << "x" << endl;
        }
    }

    return 0;
}