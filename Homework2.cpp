
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
int seed;

int generate_standard()
{
	srand(seed);
	seed = rand() % 10000;
	return seed;
}
int generate_midsquare()
{
	for (int i = 1; i <= 10; i++)
	{
		seed = seed*(seed+9);
		seed =((seed / 100)+132) % 10000;
	}
	return seed;
}
int generate_Lehmer()
{
	int a = 17;
	int c = 43;
	int m = 10000;
	for (int i = 1; i <= 30; i++)
	{
		seed = (a*seed + c) % m;
	}
	return seed;
}

float calculate_coeficient(int type)
{
	float a = 0;
	int x, y;
	for (int j = 1; j <= 10000; j++)
	{
		switch (type)
		{
		case 1:
			x = generate_standard();
			y = generate_standard();
			break;
		case 2:
			x = generate_midsquare();
			y = generate_midsquare();
			break;
		case 3:
			x = generate_Lehmer();
			y = generate_Lehmer();
			break;
		}
		if (x*x + y*y <= 10000 * 10000)
			a++;
	}
	return a / 2500.0;
}

int main()
{
	seed = 13372;
	cout << calculate_coeficient(1) << '\n';
	cout << calculate_coeficient(2) << '\n';
	cout << calculate_coeficient(3) << '\n';
	return 0;
}
