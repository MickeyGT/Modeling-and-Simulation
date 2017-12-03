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
struct tranzitie
{
	string posibilitate;
	int nodeNumber;
	string type;
	int tokens;
}temp, rest;
struct state
{
	int tokens;
}st;
vector<tranzitie>conexiuni[100];
vector<tranzitie>preturiSiMonezi;
vector<tranzitie>possibleStates[100];
deque<state>states;
bool compatibleState(state st, tranzitie el)
{
	if (el.type == "bomboana")
	{
		if (st.tokens >= el.tokens)
			return true;
		else
			return false;
	}
	else
	{
		if (st.tokens + el.tokens <= highestPrice)
			return true;
		else
			return false;
	}
}
state moneyAfter(state st, tranzitie el)
{
	if (el.type == "bomboana")
	{
		st.tokens -= el.tokens;
	}
	else
		if (el.type == "moneda")
		{
			st.tokens += el.tokens;
		}
		else
		{
			st.tokens -= el.tokens;
		}
	return st;
}
void navigate(state st)
{
	int nr;
	cout << "Acum ai " << st.tokens << " lei.\nTranzitiile posibile sunt:\n";
	for (auto it = possibleStates[st.tokens].begin(); it != possibleStates[st.tokens].end(); it++)
	{
		cout << (*it).posibilitate;
	}
	cout << "Alegeti o tranzitie:";
	cin >> nr;
	st = moneyAfter(st, (possibleStates[st.tokens][nr - 1]));
	navigate(st);
}
int main()
{
	//ifstream f("file.in");
	//ofstream g("file.out");
	cout << "Automat de M&M\n";
	for (i = 1; i <= 3; i++)
	{
		cout << "Bomboana " << i << " costa:";
		cin >> cost;
		highestPrice = max(highestPrice, cost);
		temp.type = "bomboana";
		temp.tokens = cost;
		temp.nodeNumber = i;
		temp.posibilitate = "Puteti cumpara bomboana " + to_string(temp.nodeNumber) + " pentru " + to_string(temp.tokens) + "\n";
		preturiSiMonezi.push_back(temp);
	}
	for (i = 1; i <= 2; i++)
	{
		cout << "Moneda " << i << " valoreaza:";
		cin >> cost;
		temp.type = "moneda";
		temp.tokens = cost;
		temp.nodeNumber = i;
		temp.posibilitate = "Puteti introduce moneda " + to_string(temp.nodeNumber) + " cu valoare " + to_string(temp.tokens) + "\n";
		preturiSiMonezi.push_back(temp);
	}
	st.tokens = 0;
	states.push_back(st);
	while (states.size() != 0)
	{
		st = *states.begin();
		states.pop_front();
		if (visitedStates[st.tokens] == 0)
		{
			for (auto it = preturiSiMonezi.begin(); it != preturiSiMonezi.end(); it++)
			{
				if (compatibleState(st, *it))
				{
					possibleStates[st.tokens].push_back(*it);
					if (visitedStates[moneyAfter(st, *it).tokens] == 0)
						states.push_back(moneyAfter(st, *it));
				}
			}
			if (st.tokens != 0)
			{
				rest.tokens = st.tokens;
				rest.posibilitate = "Puteti primi inapoi " + to_string(st.tokens) + " rest.\n";
				possibleStates[st.tokens].push_back(rest);
			}
		}
		visitedStates[st.tokens] = 1;
	}
	st.tokens = 0;
	while (true)
	{
		navigate(st);
	}
	return 0;
}
