/*
 * 0세대 : FX
 * X -> X + YF
 * Y -> FX - Y
 *
 * n세대 드래곤 커브 문자열 구하기!
 * 문자열 중 p 번째 글자부터 l 글자만을 계산하는 프로그램 만들기!*/

#include <iostream>
#include <string>

int skip;

void curve (const std::string& seed, int generations)
{
	if (skip < 0 ) return;

	if (generations == 0)
	{
		if (seed.size() >= skip)
			std::cout << seed;
		--skip;
		return;
	}

	for (int i = 0 ; i < seed.size(); i ++)
	{
		if (seed[i] == 'X')
			curve("X+YF", generations -1);
		else if (seed[i] == 'Y')
			curve("FX-Y", generations -1);
		else
		{
			if(seed.size() >= skip) 
				std::cout << seed[i];

			--skip;
		}
	}
	return;
}

int main(void)
{
	std::cout <<"9.12 curve example" << std::endl;

	std::cout << "generations:0" << std::endl;
	skip = 0;
	curve ("FX", 0);
	
	std::cout << std::endl << "generations:1" << std::endl;
	skip = 0;
	curve ("FX", 1);

	std::cout << std::endl << "generations:2" << std::endl;
	skip = 5;
	curve ("FX", 2);

	return 1;
}
