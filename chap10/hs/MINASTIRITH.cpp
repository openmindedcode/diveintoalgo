#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

#define _USE_MATH_DEFINES

using namespace std;

// n : 초소의 개수 (1<=n<=100)
int n;
// y,x : 초소위치, r : 감시범위
double y[100], x[100], r[100];
pair<double, double> ranges[100];

const int INF = 987654321;
// cmath의 M_PI 를 사용해도 동일함!
// const double pi = 2.0 * acos(0); // cos(pi/2) = 0

// atan2 범위: [-M_PI, M_PI]
// fmod() : 부동소수점 나머지 연산
// pair에 데이터 쌍으로 추가할 때는 make_pair() 호출 : https://blockdmask.tistory.com/64
void convertToRange()
{
    for(int i=0; i<n; i++)
    {
        double loc = fmod(2*M_PI + atan2(y[i], x[i]), 2*M_PI);
        double range = 2.0 * asin(r[i] / 2.0 / 8.0);

        ranges[i] = make_pair(loc-range, loc+range);
    }

    // 시작 위치 오름차순 정렬
    sort(ranges, ranges+n);
}

// begin ~ end 구간을 덮기 위해 선택한 최소한 구간 수 반환
int solveLinear(double begin, double end)
{
    int used=0, idx=0;

    while(begin < end)
    {
        // begin보다 이전에 시작하는 구간 중 가장 늦게 끝나는 구간을 찾는다.
        double maxCover = -1;

        while(idx < n && ranges[idx].first <= begin)
        {
            maxCover = max(maxCover, ranges[idx].second);
            idx++;
        }

        // 덮을 구간을 찾지 못한 경우
        if(maxCover <= begin) return INF;

        begin = maxCover;
        used++;
    }
    return used;
}

// 0을 덮을 구간을 선택하고 나머지는 선형으로 푼다
double solveCircular()
{
    int ret = INF;

    for(int i=0; i<n; i++)
    {
        if(ranges[i].first <= 0 || ranges[i].second >= 2*M_PI)
        {
            // 0을 덮은 구간의 end = 나머지 구간의 begin
            // 0을 덮은 구간의 begin = 나머지 구간의 end
            double begin = fmod(ranges[i].second, 2*M_PI);
            double end = fmod(ranges[i].first + 2*M_PI, 2*M_PI);

            ret = min(ret, 1 + solveLinear(begin, end)); // 1은 0 덮은 초소 카운트한 것
        }
    }

    return ret;
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
        if(n < 1 || n > 100)
            exit(-1);

        // n개의 초소 정보
        for(int j=0; j<n; j++)
        {
            cin >> y[j] >> x[j] >> r[j];
            if(r[j] < 1 || r[j] > 16.001)
                exit(-1);
        }
        convertToRange();
        cout.precision(8);

        if(solveCircular() != INF)
            cout << solveCircular() << endl;
        else
            cout << "IMPOSSIBLE" << endl;
    }

    return 0;
}