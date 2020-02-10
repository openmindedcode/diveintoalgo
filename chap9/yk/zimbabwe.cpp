#include <string>
#include <iostream>
#include <cstring>

// e : 현재 계란 가격 (1 <= e <= 10^14)
// 이전 계란 가격은 m 의 배수 (2 <= m <= 20)
// 출력은, 가능한 가격의 수를 1,000,000,007로 나눈 나머지

std::string e;
//e 안에 중복되는 숫자가 있을 때 가장 먼저 오는 것만 계산 하기 위해
//e의 자릿수를 정렬 한 것
std::string digits;
// e의 자릿수
int n; 
int m;

const int MOD = 1000000007;
int cache[1<<14] [20] [2];
// e의 자릿수를 재배열 하여, 만들 수 있는 가격들을 전부 만드는 완전탐색 알고리즘 
// price : 지금까지 만든 가격
// taken : 자릿수가 사용 되었는지 여부
void generate(std::string price, bool taken[15])
{
	//기저 사례
	// e의 자릿수로 만들 수 있는 숫자들을 모두 출력한다. 
	// 지금 만들어진 숫자(e에 이루어진 문자열의 조합) 의 자릿수가 e의 자릿수와 일치  
	if (price.size() == n)
	{
		// 현재 가격 보다 적어야 함 
		if (price < e)
			std::cout << price << std::endl;
		
		return;
	}
	
	for (int i = 0; i < n ; i++)
	{
		// 이번에 사용할 자릿수 바로 앞자리가 없거나, i ==0
		// 이번 자릿수랑 다르거나 
		// 이미 사용된 경우
		std::cout << "taken[" << i << "]" << taken[i] << std::endl; 
		if ( !taken[i] && (i == 0 || digits[i-1] != digits[i] || taken[i-1]))
		{
			// 현재 자릿수 사용해도 됨
			std::cout <<" "<<std::endl; 
			taken[i] = true;
			generate(price + digits[i], taken);
			taken[i] = false;
		}
	}
}

// 과거 가격을 앞자리 부터 채워 나감. 앞자리가 작은지 큰지 비교
// index : 이번에 채울 자릿수의 인덱스
// taken :  지금까지 사용한 자릿수들의 집합
// mod : 지금까지 만든 가격의 m에 대한 나머지
// less : 지금까지 만ㄷ느 가격이 이미 e보다 작으면 1, 아니면 0
int price(int index, int taken, int mod, int less)
{
	//기저 사례
	// 이번에 채울 자릿수가 전체 자릿수와 일치 할 경우
	if (index == n)
	{
		// m의 배수이거나  e보다 작은 경우 
		return (less && mod == 0) ? 1: 0;
	}

	int &ret = cache [taken][mod][less];
	if (ret != -1) return ret;

	ret = 0;
	for (int next = 0; next < n; next++)
	{
		if ((taken & (1<<next)) == 0)
		{
			// 과거 가격은 항상 새 가격 보다 작아야 한다.
			//지금까지 만든 가격이 e 보다 작고 
			// && e의 index 는 digits 의 다음 보다 작아야 함(e=3124 이면 price =31 뒤에 4 못옴) 
			if (!less && e[index] < digits[next])
				continue;
			//같은 숫자는 한번만 선택
			if (next > 0 && digits[next -1] == digits[next] && (taken & (1<<(next-1)))== 0)
				continue;

			int nextTaken = taken | (1<<next);
			int nextMod = (mod *10 + digits[next] - '0' ) %m;
			int nextLess = less|| e[index] >  digits[next];
			ret += price(index+1, nextTaken, nextMod, nextLess);
			ret %= MOD;
		}
	}
	return ret;
}

int main(void)
{

	std::cout<<"9.16 generate" <<std::endl;

	std::cout <<"e = 321" << std::endl;
	e = "321";
	digits = "123";
	n = 3;
	std::string price = "";
	bool taken[15];
	std::memset(taken, 0, sizeof(bool)*15);
	generate(price, taken);
	return 1;
}

