/*
n개의 정수를 일렬로 늘어놓은 게임판을 가지고 현우와 서하가 게임을 한다.
게임은 현우부터 시작해서 번갈아가며 진행하며, 각 참가자는 자기 차례마다 두 가지 일 중 하나를 할 수 있다.

1.게임판의 왼쪽 끝에 있는 숫자나 오른쪽 끝에 있는 숫자 중 하나를 택해 가져간다.
  가져간 숫자는 게임판에서 지워진다.
2.게임판에 두 개 이상의 숫자가 있을 경우, 왼쪽 끝에서 2개, 혹은 오른쪽 끝에서 2개를 지운다.(가져가지 않고 지우기만 한다)

게임은 모든 숫자가 다 없어졌을 때 끝나며, 각 사람의 점수는 자신이 가져간 숫자들의 합!
현우와 서하는 점수가 더 낮은 쪽이 점수 높은 쪽에 한 점 차이마다 백 원씩 주기로 내기를 했다.
두 사람 모두 최선을 다할 때, 두 사람의 최종 점수 차이는?
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int MAX = 50;
const int EMPTY = -987654321;
int board[MAX], boardSize;
int cache[MAX][MAX];

int play(int left, int right)
{
    // 기저 사례 : 왼쪽이 오른쪽보다 커지면...
    if(left > right) return 0;

    int& ret = cache[left][right];
    if(ret != EMPTY) return ret;

    // 1. 왼쪽/오른쪽 끝에서 하나씩 가져감.
    ret = max(board[left] - play(left+1, right), board[right] - play(left, right-1));

    // 2. 왼쪽 끝 or 오른쪽 끝에서 2개 삭제
    if(right-left+1 >= 2)
    {
        // 1) 왼쪽에서 삭제
        ret = max(ret, -play(left + 2, right));
        // 2) 오른쪽에서 삭제
        ret = max(ret, -play(left, right - 2));
    }

    return ret;
}

int main()
{
    int testCase;
    cin >> testCase;

    if(testCase < 1 || testCase > 50)
        exit(-1);

    // cache 버퍼 초기화 (memset 못씀)
    for(int i=0; i<MAX; i++)
    {
        for(int j=0; j<MAX; j++)
            cache[i][j] = EMPTY;
    }

    for(int i=0; i<testCase; i++)
    {
        cin >> boardSize;
        if(boardSize < 1 || boardSize > 50)
            exit(-1);

        for(int j=0; j<boardSize; j++)
            cin >> board[j];

        cout << play(0, boardSize-1) << endl;
    }

    return 0;
}