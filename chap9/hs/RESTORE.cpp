// https://sangdo913.tistory.com/77 참조

#include <iostream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

const int MAX = 15;
int count;
string subStr[MAX+1];

// 메모이제이션
int cache[MAX][1<<MAX + 1];

// overlap[i][j]
// : subStr[i] 뒤에 subStr[j] 문자열이 올 때, subStr[j]에서 겹치는 부분 뺀 길이
// : 추가할 길이!
int overlap[MAX][MAX];

//========================================================================//

// last : 마지막 조각
// used : 지금까지의 조각 집합
// 나머지 조각 추가해서 얻을 수 있는 overlap()의 최대 값 (총 겹쳐있는 글자 수 반환)
int restore(int last, int used)
{
    //cout << "[[[[[[ restore ]]]]]] last : " << last << ", used : " << used << endl;
    // 기저 사례 : 모든 문자열을 다 선택한 경우
    if(used == (1 << count) - 1)
        return 0;

    int& ret = cache[last+1][used];
    if(ret != -1) return ret;
    ret = 0;

    // 아직 선택되지 않은 문자열에 대해서 모두 시도
    for(int next=0; next < count; next++)
    {
        if((used & (1<<next)) == 0)
        {
            int cand = overlap[last][next] + restore(next, used+(1<<next));
            ret = max(ret, cand);
        }
    }
    return ret;
}

void printOverlap()
{
    cout << "[[[[[[[[ overlap ]]]]]]]]]]]" << endl;
    for(int i=0; i<count+1; i++)
    {
        for(int j=0; j<count+1; j++)
            cout << overlap[i][j] << " ";

        cout << endl;
    }

    cout << endl;
}

// s1과 s2에서 실제로 겹치는 문자의 수 반환
int overlay(string& s1, string& s2)
{
    // s1 = oji , s2 = jing
    // s1.size() = 3, s2.size() = 4
    for(int len = min(s1.size(), s2.size()); len > 0; len--)
    {
        if(s1.substr(s1.size() - len) == s2.substr(0, len))
            return len;
    }

    return 0;
}

string reconstruct(int last, int used)
{
    // 기저 사례 : 모든 문자열을 다 선택한 경우
    if(used == (1 << count) - 1)
        return "";

    // 다음에 올 문자열 조각 찾기
    for(int next=0; next < count; next++)
    {
        // next가 이미 사용된 경우 제외
        if(used & (1<<next)) continue;

        // next를 사용한 경우의 답이 최적해와 같다면 next를 사용한다.
        int ifUsed = restore(next, used + (1<<next)) + overlap[last][next];
        if(restore(last, used) == ifUsed)
        {
            string ret = subStr[next].substr(overlap[last][next])
                         + reconstruct(next, used + (1 << next));
            return ret;
        }

    }

    return "error";
}

int main(void)
{
    int testCase;
    cin >> testCase;

    if(testCase < 1 || testCase > 50)
        exit(-1);

    for(int i=0; i<testCase; i++)
    {
        cin >> count;

        if (count < 1 || count > 15)
            exit(-1);

        for(int j=0; j<count; j++)
        {
            cin >> subStr[j];
            if(subStr[j].empty() || subStr[j].size()>21)
                exit(-1);
        }

        memset(cache, -1, sizeof(cache));
        memset(overlap, -1, sizeof(overlap));

        while(true)
        {
            bool check = false;

            cout << "" << endl;
            for(int k=0; k < count && !check; k++)
            {
                for(int l=0; l < count; l++)
                {
                    if(k!=l && subStr[k].find(subStr[l]) != -1) // subStr[k] 안에 subStr[l] 이 발견됨! (포함)
                    {
                        //cout << "[[입력 문자들 중에 서로 포함된 경우가 발견됨!]]" << endl;
                        //cout << "[PREV] substring[" << k << "]:" << subStr[k] << ", substring[" << l << "]:" << subStr[l] << endl;
                        subStr[l] = subStr[count - 1]; // 맨 끝에 있는 string과 위치 변경
                        count--; // 총 입력 수를 1개 줄임
                        check = true;

                        //cout << "[POST] substring[" << k << "]:" << subStr[k] << ", substring[" << l << "]:" << subStr[l] << endl;
                    }
                }
            }
            if(!check) break;
        }

        subStr[count] = "";

        // overlap 초기화
        for(int j=0; j<=count; j++)
        {
            for(int k=0; k<=count; k++)
            {
                overlap[j][k] = overlay(subStr[j], subStr[k]);
            }
        }

        //printOverlap();

        cout << reconstruct(count, 0) << endl;
    }
    return 0;
}