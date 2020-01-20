#include <string>
#include <iostream>
#include <cstring>

// 모든 모스 부호 신호를 만드는 완전 탐색 알고리즘
// -의 아스키코드 45, o의 아스키 코드 111 이므로 o가 먼저 옴
// s : 모스 부호 
// m : 짧은 코드 - 의 남은 수 
// n : 긴 코드 o 의 남은 수 
//
//n,m 이 주어질때 모든 보스 부호를 만드는 완전 탐색 알고리즘
//

// --- ooo 일 경우, -는 먼저 나와야 하므로, 
// - 다음 --ooo의 조합. 
// -- 다음 -ooo의 조합
// --- 다음 ooo의 조합
// 그 다음 o가 앞인 조합
//
void generate (int n, int m, std::string s)

{
	if (n == 0 && m == 0)
	{
		std::cout <<s<<std::endl;
		return;
	}


	if (n > 0) generate(n-1, m, s + "-");// -가 먼저 앞에 나와야 함 

	if (m > 0) generate(n, m-1, s + "o");

}

// 9.7 k 번쨰 모스 부호만 출력 하기, 
// k-1 번째 까지는 출력 하지 않기 
int skip; // 건너 뛰어야 할 갯수의 전역 변수
// k 다음 번쨰 숫자는??
void generate2 (int n, int m, std::string s)
{

	if (skip < 0) return;//건너뛸 것이 없으면 리턴 == k번쨰 다음 부터 건너뛰기

	if (n == 0 && m == 0)
	{
		if (skip == 0)
			std::cout << s << std::endl;
			
		--skip;
		return;
		
	}
	
	if (n > 0) generate2(n-1, m, s + "-");
	if (m > 0) generate2(n, m-1, s + "o");
}

// 이항계수 이용
//K의 최대값 +100 , 로버플로를 막기위해 이보다 큰 값은 구하지 않는다. 

const int M = 1000000000+100;
int bino[201][201]; //n,m <=100
 
//필요한 이항계수 모두 계산 하기
void calcBino()
{
	std::memset(bino, 0, sizeof(bino));
	for (int i= 0; i <=200; i++)
	{
		bino[i][0] = bino[i][i] = 1; // 합 만큼 구하는 가짓수는 1로 항상 같음 
		for(int j = 1; j < i; j++)
			bino[i][j] = std::min(M, bino[i-1][j-1] + bino[i-1][j]); // C(n,k)+C(n,k+1) = C(n+1,K+1) 성립 하므로..
	}

}

void generate3(int n, int m, std::string s)
{
	std::cout<<"n: "<<n<<"m: "<<m<<std::endl;
	if (skip < 0) return;

	if (n == 0 && m == 0)
	{
		if (skip == 0)
			std::cout << s << std::endl;

		--skip;
		return;
	}

	//기저사례 아닐 경우 계속 재귀 함수 돌아야 함... 필요 없는것 건너 뛰고 싶음 
	//skip >= C(n+m, n) 이면 그 만큼 건너뛰기 ??
	if (bino[n+m][n] <= skip)
	{
		std::cout <<"skip : "<<skip <<std::endl;
		std::cout << "n: "<< n <<"m : "<< m << "bino"<<bino[n+m][n] <<std::endl;
		skip -= bino[n+m][n];
		return;
	 }	
	
	if (n > 0) generate3(n-1, m, s + "-");
	if (m > 0) generate3(n, m-1, s + "o"); 
}

int main (void)
{
	std::cout << "9.6 generate" << std::endl;

	std::string s;

	std::cout << "n:4,m:5" << std::endl;
	generate(4,5,s);

	std::cout << "9.7 generate2" << std::endl;
	std::cout << "n:4, m:5, k:3" << std::endl;
	skip = 3-1; // 0번부터 세므로 -1;
	generate2(4,5,s);

	std::cout << "9.8 generate3" <<std::endl;
	skip = 10;
	generate3(4,5,s);

	return 1;
}

