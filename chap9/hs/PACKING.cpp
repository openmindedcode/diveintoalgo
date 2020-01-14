#include <iostream>
#include <vector>
#include <string>
#include <cstring>

#include <algorithm>

using namespace std;

int total, capacity;         // total: 총 물건 갯수(최대 100), capacity: 캐리어 용량(최대 1000)
string name[100];            // name: 상품 이름
int volume[100], need[100];  // volume: 상품 부피(최대 1000), need: 상품의 절박도(최대 1000)
int cache[1001][100];        // 캐리어 무게에 따른 각 아이템 별로 절박도를 저장하는 캐시
                             // 참고. 입력받을 캐리어 용량 크기만큼만 할당해도 좋을 것 같음.

// 완전 탐색: 지금까지 고른 물건 목록(items)을 주면 남은 용량으로 채울 수 있는 최대 절박도 합 리턴
// int pack(vector<> items)

// 동적계획법
// 캐리어에 capacity 용량 남았을 때 item 이후 물건들로 얻을 수 있는 최대 절박도
int pack(int capacity, int item)
{
    // 더 담을 물건 없을 때
    if(item == total) return 0;

    int& ret = cache[capacity][item];

    if(ret != -1) return ret;

    // item 선택하지 않은 경우
    ret = pack(capacity, item+1);

    // item 선택한 경우
    if(capacity >= volume[item])
        ret = max(ret, pack(capacity - volume[item], item+1) + need[item]);

    return ret;
}

void reconstruct(int capacity, int item, vector<string>& picked)
{
    // 모든 아이템 다 따져봄
    if(item == total) return;

    // item을 선택하지 않았다는 소리임
    if(pack(capacity, item) == pack(capacity, item+1)) // ** 부피나 절박도가 동일한 경우에 대해서 해결 불가!!!
    {
        reconstruct(capacity, item+1, picked);
    }
    else
    {
        picked.push_back(name[item]); // 선택했으니까 picked에 name 추가!
        reconstruct(capacity - volume[item], item+1, picked);
    }
}

int main(void)
{
    int testCase;
    cin >> testCase;

    if(testCase < 1 || testCase > 50)
        exit(-1);

    for(int i=0; i<testCase; i++)
    {
        vector<string> picked;
        cin >> total >> capacity;

        if (total < 1 || total > 100 || capacity < 1 || capacity > 1000)
            exit(-1);

        for(int j=0; j<total; j++)
        {
            cin >> name[j] >> volume[j] >> need[j];
            if(name[j].empty() || name[j].size()>21 || volume[j]<1 || volume[j]>1000 || need[j]<1 || need[j]>1000)
                exit(-1);
        }

        memset(cache, -1, sizeof(cache));
        reconstruct(capacity, 0, picked);
        cout << pack(capacity, 0) << " " << picked.size() << endl;
        for(int k=0; k<picked.size(); k++)
            cout << picked[k] << endl;
    }
    return 0;
}