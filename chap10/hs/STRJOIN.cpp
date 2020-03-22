// 한 개의 문자열로 합칠 때 필요한 최소 비용
// --> 입력된 문자열 길이를 오름차순 정렬하고 작은거부터 합치면 됨!
// 참조 : https://hyeonstorage.tistory.com/324 (vector에 관해)

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// n     : 문자열의 수    (1<=n<=100)
// len   : 문자열의 길이  (1<=len<=1000)
// price : 합칠 때 드는 비용
int n, len, price[100];

void printVector(const vector<int> &a)
{
    for(int i=0; i<a.size(); i++)
    {
        cout << a[i] << " ";
        cout << endl;
    }
}

int calcMinPrice(vector<int> &strLen)
{
    if(strLen.size() <= 1) return 0;

    int minFirst = strLen.front();
    strLen.erase(strLen.begin()); // 제일 작은거 vector에서 삭제
                                  // (+ 뒷 요소들이 자동으로 한 칸 씩 앞으로 당겨짐)
    int minSecond = strLen.front();
    strLen.erase(strLen.begin()); // 두 번째 작은거 vector에서 삭제

    int sum = minFirst + minSecond;

    strLen.push_back(sum);
    sort(strLen.begin(), strLen.end());

    return sum + calcMinPrice(strLen);
}

int main()
{
    int testCase;
    cin >> testCase;

    if(testCase < 1 || testCase > 50)
        exit(-1);

    for(int i=0; i<testCase; i++)
    {
        cin >> n;
        if(n < 1 || n > 20)
            exit(-1);

        // n개 만큼 vector 생성!
        vector<int> strLen(n);

        for(int j=0; j<n; j++)
        {
            cin >> strLen[j];

            if(strLen[j] < 1 || strLen[j] > 100)
                exit(-1);
        }

        sort(strLen.begin(), strLen.end()); // 오름차순 정렬
        cout << calcMinPrice(strLen) << endl;
    }

    return 0;
}