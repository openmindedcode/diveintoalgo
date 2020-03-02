#include <iostream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

const int MAX_BUDGET = 2147483647 - 1;

// n     : 초밥 종류   (1<=n<=20)
// m     : 예산       (1<=m<=1,000,000,000)
// price : 초밥 가격   (<=20000 / 100의 배수)
// pref  : 초밥 선호도 (1<=pref<=20)
int n, m, price[20], pref[20];

//int cache[100000000];
//int cache2[100000000];
int cache3[20000 / 100 + 1];

// budget 만큼 예산을 써서 얻을 수 있는 최대 선호도 합
/*
int sushi(int budget)
{
    // 메모이제이션
    int& ret = cache[budget];
    if(ret != -1) return ret;

    ret = 0;
    for(int i=0; i<n; i++)
    {
        if(budget < price[i]) continue;
        ret = max(ret, sushi(budget - price[i]) + pref[i]);
    }

    return ret;
}

// 반복적 동적 계획법
int sushi2()
{
    int ret = 0;
    for(int budget=1; budget<=m; budget++)
    {
        cache2[budget] = 0;
        for(int d=0; d<n; d++)
        {
            if(budget >= price[d])
                cache2[budget] = max(cache2[budget], cache2[budget - price[d]] + pref[d]);
        }

        ret = max(ret, cache2[budget]);
    }
    return ret;
}
*/

// 반복적 동적 계획법 : cache size 줄이기
int sushi3()
{
    int ret = 0;
    cache3[0] = 0;

    for(int budget=1; budget<=m; budget++)
    {
        int cand = 0;
        for(int dish=0; dish<n; dish++)
        {
            if(budget >= price[dish])
                cand = max(cand, cache3[(budget - price[dish])%201] + pref[dish]);
        }
        cache3[budget % 201] = cand;
        ret = max(ret, cand);
    }
    return ret;
}

int main()
{
    int testCase;
    cin >> testCase;

    if(testCase < 1 || testCase > 5)
        exit(-1);

    //memset(cache, -1, sizeof(cache));

    for(int i=0; i<testCase; i++)
    {
        cin >> n >> m;
        if(n < 1 || n > 20 || m < 1 || m > 2147483647)
            exit(-1);
        m /= 100; // 예산을 100으로 나눠준다.

        for(int j=0; j<n; j++)
        {
            cin >> price[j] >> pref[j];
            price[j] /= 100; // 가격도 100으로 나눠놓음.
        }

        //cout << sushi(m) << endl;
        //cout << sushi2() << endl;
        cout << sushi3() << endl;
    }

    return 0;
}