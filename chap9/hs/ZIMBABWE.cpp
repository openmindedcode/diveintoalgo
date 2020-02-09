// https://jaimemin.tistory.com/366 참조함

#include <iostream>
#include <vector>
#include <string>
#include <cstring>  // for memset
#include <algorithm>

using namespace std;

const int MOD = 1000000007;
string egg, digits;             // digits : egg의 자릿수들을 정렬한 것
int n, m;                       // n : egg의 자릿수
                                // m : 사탕 m개

bool taken[15] = {false};

// 자릿수 최대 14자리 / m<=20 / egg보다 작은지 여부
int cache[1<<14][20][2];


// egg의 숫자들로 만들 수 있는 숫자들 모두 출력
// price : 지금까지 만든 가격
// taken : 각 숫자들의 사용 여부
void generate(string price, bool taken[15])
{
    // 기저 사례
    if(price.size() == n)
    {
        if(price < egg)
            cout << price << endl;
        return;
    }

    for(int i=0; i<n; i++)
    {
        if(!taken[i] &&
            (i==0 || digits[i-1] != digits[i] || taken[i-1]))
        {
            taken[i] = true;
            generate(price + digits[i], taken);
            taken[i] = false;
        }
    }
}


// 과거 가격을 앞자리부터 채우기
// index : 이번에 채울 자리의 인덱스
// taken : 지금까지 사용한 자릿수들의 집합
// mod : 지금까지 만든 가격의 m에 대한 나머지
// less : 지금까지 만든 가격이 이미 egg 보다 작으면 1, 아니면 0
long long price(int index, int taken, int mod, int less)
{
    // 기저 사례
    if(index == n)
        return (less && mod == 0) ? 1 : 0;

    int& ret = cache[taken][mod][less];

    if(ret != -1) return ret;

    ret = 0;
    for(int next = 0; next < n; next++)
    {
        if((taken & (1 << next)) == 0)  // next번째 숫자 사용한 적 없다면
        {
            // 과거 가격이 새 가격보다 작아야한다
            if(!less && (egg[index] < digits[next])) continue;

            // 같은 숫자는 한 번만 선택
            if(next > 0 &&
               (digits[next -1] == digits[next]) &&
               (taken & (1 << (next-1))) == 0 )
               continue;

            // next 번째 숫자는 사용된 것임
            int nextTaken = taken | (1 << next);

            int nextMod = (mod * 10 + digits[next] - '0') % m; // 다음 나머지
            int nextLess = less || egg[index] > digits[next];  // egg보다 작은 숫자인지 확인

            ret += price(index + 1, nextTaken, nextMod, nextLess);
            ret %= MOD;
        }
    }

    return ret;
}

int main(void)
{
    int testCase;
    cin >> testCase;

    if(testCase < 1 || testCase > 50)
        exit(-1);

    for(int i=0; i<testCase; i++)
    {
        vector<long long> c;
        memset(cache, -1, sizeof(cache));
        n=0;
        cin >> egg >> m;

        // long long은 8바이트의 공간을 가지는 자료형 (-9,223,372,036,854,775,808 to 9,223,372,036,854,775,807)
        long long num = atoll(egg.c_str());

        while(num > 0)
        {
            c.push_back(num % 10);
            num /= 10;
            n++;
        }

        sort(c.begin(), c.end());

        for(int j=0; j<n; j++)
        {
            digits += c[j] + '0';
            //generate(digits, taken);
        }

        cout << price(0,0,0,0) << endl;
    }
    return 0;
}
