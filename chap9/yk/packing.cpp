#include <string>
#include <iostream>
#include <algorithm>
#include <vector>

int n = 6;
int capacity = 10;
std::string name[] = {"laptop", "camera", "xbox", "grinder", "dumbell", "enclopedia"};
int volume[] = {4,2,6,4,2,10};
int need[] = {7,10,6,7,5,4};

int cache[1001][100];//최대 절박도의 합

int pack(int capacity, int item)
{
	//기저 사례
	if (item == n) return 0;

	int& ret = cache[capacity][item];
	// if (ret  != -1) return ret;
	
	//물건을 담지 않을 경우 
	ret = pack(capacity, item +1);

	//물건을 담을 경우 , 다음 capacity가 물건 뺀 용량 만큼으로 줄어들고 cache 의 절박도는 그만큼 커짐 
	if (capacity >= volume[item])
	{
		ret = std::max (ret, pack(capacity -volume[item], item+1) + need[item]);
	}

	return ret;
}

//선택된 아이템
void reconstructor(int capacity, int item, std::vector<std::string>& picked)
{
	//기저 사례 
	if (item == n) return;

	//현재 아이템과 다음 아이템의 최대 절박도가 같다면,
	//현재 아이템이 선택되지 않은 것이므로... 
	if(pack(capacity, item) == pack(capacity, item+1))
	{
		//선택되지 않았으므로 용량도 변함 없음 
		reconstructor(capacity, item+1, picked);
	}
	else
	{
		picked.push_back(name[item]);
		std::cout << "item :" << name[item] << std::endl;
		reconstructor(capacity-volume[item], item+1, picked);
	}

	return;
}

int main(void)
{
	std::cout << "9.2 packing" << std::endl;

	std::vector<std::string> picked;
	reconstructor(capacity, 0, picked);

	int need_max = pack(capacity, 0);
	std::cout << "max : " << need_max <<std::endl;

	return 1;
}

