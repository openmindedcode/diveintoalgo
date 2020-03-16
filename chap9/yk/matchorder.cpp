#include <iostream>
#include <string>
#include <set>
#include <vector>

using namespace std;

int order(const vector<int>& russian,
		const vector<int>& korean) {


	int n = russian.size(), wins= 0;

	// 자동 정렬, 중복 가능 
	multiset<int> ratings(korean.begin(), korean.end());

	for (int rus = 0; rus < n; ++rus) {
	
		// 가장 점수가 낮은 경우 
		// rbegin 역순 
		if (*ratings.rbegin() < russian[rus])
			ratings.erase(ratings.begin());
		else {
			//lower_bound 원소가 시작하는 구간의 반복자 
			ratings.erase(ratings.lower_bound(russian[rus]));
			++wins;
		}
	}

	return wins;
}

int main(void)
{
	cout << "MATCHORDER" <<endl;
	vector<int> russian{3000, 2700 ,2800, 2200, 2500, 1900};
	vector<int> korean{2800,2750,2995,1800,2600,2000};
	int wins = 0;
	wins = order(russian, korean);

	cout << "wins : "<<wins<<endl;

	return 1;
}
