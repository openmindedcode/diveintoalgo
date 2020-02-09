#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

const int MAX = 1000000000 + 50;
const string EXPAND_X = "X+YF";
const string EXPAND_Y = "FX-Y";

int length[51]; // X나 Y를 i번 치환한 후의 문자열 길이

int skip, range;

// seed를 generations 세대 만큼 진화한 결과를 출력
void curve(const string& seed, int generations)
{
    // 기저 사례
    if(generations == 0)
    {
        cout << seed;
        return;
    }

    for(int i=0; i<seed.length(); i++)
    {
        if(seed[i] == 'X')
            curve(EXPAND_X, generations-1);
        else if(seed[i] == 'Y')
            curve(EXPAND_Y, generations-1);
        else
            cout << seed[i];
    }
}

bool printCheck() {
    if(skip > 1) {
        skip -= 1;
        return false;
    }

    if(range <= 0)
        return false;

    range--;

    return true;
}

// 원하는 범위만큼만 출력하도록 함(미출력 구간은 _로 출력)
void curve2(const string& seed, int generations)
{
    if(generations == 0)
    {
        for(int i=0; i<seed.length(); i++)
        {
            if(printCheck()) cout << seed[i];
            else cout << "_";
        }
        return;
    }

    for(int i=0; i<seed.length(); i++)
    {
        if(seed[i] == 'X')
            curve2(EXPAND_X, generations-1);
        else if(seed[i] == 'Y')
            curve2(EXPAND_Y, generations-1);
        else if(printCheck())
            cout << seed[i];
        else
            cout << "_";
    }
}

char expand(const string& dragonCurve, int generations, int skip)
{
    // 기저 사례
    if(generations == 0) {
        if(skip > dragonCurve.size()) // 더 이상 확장되지 않는데 문자열 크기보다 skip이 큰 경우 프로그램 종료
            exit(-1);
        return dragonCurve[skip];
    }

    for(int i=0; i<dragonCurve.size(); i++)
    {
        // 문자열 확장되는 경우
        if(dragonCurve[i] == 'X' || dragonCurve[i] == 'Y')
        {
            if(skip >= length[generations])
                skip -= length[generations];
            else if(dragonCurve[i] == 'X')
                return expand(EXPAND_X, generations-1, skip);
            else
                return expand(EXPAND_Y, generations-1, skip);
        }
        // 확장되지 않지만 건너뛰어야 하는 경우
        else if(skip > 0)
            --skip;
        // 답을 찾은 경우
        else
            return dragonCurve[i];
    }
}

int main(void)
{
    int testCase;
    cin >> testCase;

    if(testCase < 1 || testCase > 50)
        exit(-1);

    // precalc
    length[0] = 1;
    for(int k=1; k<=50; k++)
        length[k] = min(MAX, length[k-1]*2 + 2);

    for(int i=0; i<testCase; i++)
    {
        int generation;

        cin >> generation >> skip >> range;

        if(generation < 0 || generation > 50
          || skip < 1 || skip > 1000000000
          || range < 1 || range > 50)
          exit(-1);

        for(int j=0; j<range; j++)
            cout << expand("FX", generation, skip+j-1);

        //curve("FX", generation);
        //curve2("FX", generation);

        cout << endl;
    }
    return 0;
}
