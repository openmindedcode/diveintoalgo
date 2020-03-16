#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

#define MAX_N 100000

int n, e[MAX_N], m[MAX_N];

int heat()
{
	// pair 두 객체를 하나의 객체로 취급
	vector<pair<int,int>> order;

	for (int i = 0;i< n; ++i)
	{
		// make_pair 변수1,2 가 들어간 pair 만들기 
		order.push_back(make_pair(-e[i],i));
	}
	sort(order.begin(), order.end());

	int ret = 0, beginEat = 0;
	for (int i = 0; i < n; ++i)
	{
		int box = order[i].second;
		beginEat += m[box];
		ret = max(ret, beginEat + e[box]);
	}
	return ret;
}

int main(void)
{
	cout << "LUNCHBOX"<<endl;
	for (int i = 0; i < 2; i++)
	{
		e[i] = 2;
		m[i] = 2;
	}
	int heat_n;
	heat_n = heat();
	cout << heat_n <<endl;

	return 1;
}
