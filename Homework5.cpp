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
long long i, j, cost, machineValue, highestPrice;
bool visitedStates[100];
struct node
{
	string posibilitate;
	int nodeNumber;
	string type;
	int value;
}temp;
struct state
{
	int money;
}st;
vector<node>conexiuni[100];
vector<node>preturiSiMonezi;
vector<node>possibleStates[100];
deque<state>states;
bool compatibleState(state st, node el)
{
	if (el.type == "bomboana")
	{
		if (st.money >= el.value)
			return true;
		else
			return false;
	}
	else
	{
		if (st.money + el.value <= highestPrice)
			return true;
		else
			return false;
	}
}
state moneyAfter(state st, node el)
{
	if (el.type == "bomboana")
	{
		st.money -= el.value;
	}
	else
	{
		st.money += el.value;
	}
	return st;
}
void navigate(state st)
{
	int nr;
	cout << "Acum ai " << st.money << " lei.\n Posibilitatile tale sunt:\n";
	for (auto it = possibleStates[st.money].begin(); it != possibleStates[st.money].end(); it++)
	{
		cout << (*it).posibilitate;
	}
	cout << "Alegeti o posibilitate:";
	cin >> nr;
	st = moneyAfter(st, (possibleStates[st.money][nr-1]));
	navigate(st);
}
int main()
{
	//ifstream f("file.in");
	//ofstream g("file.out");
	cout << "Automat de M&M\n";
	for (i = 1; i <= 3; i++)
	{
		cout << "Bomboana "<<i<<" costa:";
		cin >> cost;
		highestPrice = max(highestPrice, cost);
		temp.type = "bomboana";
		temp.value = cost;
		temp.nodeNumber = i;
		temp.posibilitate = "Puteti cumpara bomboana "+to_string(temp.nodeNumber)+" pentru "+to_string(temp.value)+"\n";
		preturiSiMonezi.push_back(temp);
	}
	for (i=1; i <= 2; i++)
	{
		cout << "Moneda " << i << " valoreaza:";
		cin >> cost;
		temp.type = "moneda";
		temp.value = cost;
		temp.nodeNumber = i;
		temp.posibilitate = "Puteti introduce moneda " + to_string(temp.nodeNumber) + " cu valoare " + to_string(temp.value)+"\n";
		preturiSiMonezi.push_back(temp);
	}
	st.money = 0;
	states.push_back(st);
	while (states.size()!=0)
	{
		st = *states.begin();
		states.pop_front();
		if (visitedStates[st.money] == 0)
		{
			for (auto it = preturiSiMonezi.begin(); it != preturiSiMonezi.end(); it++)
			{
				if (compatibleState(st, *it))
				{
					possibleStates[st.money].push_back(*it);
					if (visitedStates[moneyAfter(st, *it).money] == 0)
						states.push_back(moneyAfter(st, *it));
				}
			}
		}
		visitedStates[st.money] = 1;
	}
	st.money = 0;
	while (true)
	{
		navigate(st);
	}
	return 0;
}
