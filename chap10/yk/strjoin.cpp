#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <functional>
//문자열 합치기 문제를 해결하는 탐욕적 알고리즘
//탐욕적 알고리즘 : 매 단계 마다 가장 짧은 두 문자열을 합치는 일을 반복 
//
//
using namespace std;
int concat(const vector<int>& lengths)
{
	//greater : 첫번째 인자가 두번째 인자보다 크면 true qksghks
	priority_queue<int, vector<int> ,greater<int>> pq;
	for(int i= 0; i < lengths.size();++i)
	{
		pq.push(lengths[i]);
	}

	int ret = 0;
	while(pq.size() > 1)
	{
			//가장 짧은 문자열 두개 찾아서 합치고 큐에 넣음
		int min1 = pq.top();
		pq.pop();
		cout<< "min1 : "<<min1<<endl;
		int min2 = pq.top();
		pq.pop();
		cout<<"min2 : "<<min2 <<endl;
		pq.push(min1+min2);
		ret +=min1+min2;
		
	}
	return ret;

}

int main(void)
{
	cout << "<<strjoin>>" << endl;

	vector<int> lengths = {3,1,3,4,1};

	int ret = concat(lengths);
	cout << "ret : "<<ret<<endl;
	return 1;

}
