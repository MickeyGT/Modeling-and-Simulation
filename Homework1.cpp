#include<fstream>
#include<cstring>
#include<queue>
#include<algorithm>
#include<string.h>
#include<bitset>
#include<ctime>
#include<set>
#include<cmath>
#include<unordered_map>
#include<iomanip>
#include<map>
#include<stack>
#include<vector>
#include<bitset>
#include<functional>
#include<iostream>
#include<deque>
#include<unordered_set>
#include<queue>
#include<list>
#include<array>
#include<ctype.h>
using namespace std;
long long i, j, k, ok, nr, n, m, el, min1, max1, x, y, a, b;
void generate_standard()
{
	srand(time(NULL));
	for(int i=1;i<=30;i++)
		cout << rand() % 10000<<" ";
	cout << "\n";
}
void generate_midsquare()
{
	int seed = 1337;
	for (int i = 1; i <= 30; i++)
	{
		seed = seed*seed;
		seed = (seed / 100)%10000;
		cout << seed<<" ";
	}
	cout << "\n";
}
void generate_Lehmer()
{
	int x = 27;
	int a = 17;
	int c = 43;
	int m = 100;
	for (int i = 1; i <= 30; i++)
	{
		x = (a*x + c) % m;
		cout << x << " ";
	}
	cout << "\n";
}
int main()
{
	generate_standard();
	generate_midsquare();
	generate_Lehmer();
	return 0;
}
