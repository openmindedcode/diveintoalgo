#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>

/*
 * 1. 게임판의 왼쪽끝이나 오른쪽 끝에 있는 숫자중 하나 가져가기
 * 2. 게임판의 왼쪽 끝 2개 혹은 오른쪾 끝 2개 지우기 
 * 가져간 점수의 차이 계산 하기 */

const int EMPTY = -987654321;
int n, board[50]; // 주어지는 게임판의 길이 n (1<=n<=50)
int cache[50][50];
int play(int left, int right)
{
	//기저사례: 모든수가 다 없어 졌을때
	if (left > right) return 0;
	int& ret = cache[left][right];
	
	if (ret != EMPTY) return ret;

	std::cout << "left: "<<left <<" right: "<<right<<std::endl;

	// 수를 가져가는 경우 
	ret =  std::max (board[left] - play(left+1, right),
			board[right] - play(left, right-1));

	std::cout <<"ret : "<<ret<<std::endl;
	// 수를 없애는 경우
	if (right - left +1 >= 2)
	{
		ret = std::max(ret, -play(left+2, right));
		ret = std::max(ret, -play(left, right -2));
	}
	
	return ret;

}

int main(void)
{
	for (int i = 0; i < 50; i++)
	{
		for(int j = 0; j < 50; j++)
			cache[i][j] = EMPTY;
	}
//		std::memset(cache[i], EMPTY, sizeof(cache));

//	std::cout <<"EMPTY : "<<EMPTY<<std::endl;
	std::memset (board, EMPTY, sizeof(board));

	board[0] = -1000;
	board[1] = -1000;
	board[2] = -3;
	board[3] = -1000;
	board[4] = -1000;

	int result = play(0, 4);

	std::cout << "result : "<<result <<std::endl;

	return 1;
}
