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
#include<time.h>
#include<windows.h>
using namespace std;
class State
{
	private:
		int nrTokens;
	public:
		State(int tokens){ nrTokens = tokens; }
		void changeTokens(int tokens) { nrTokens = tokens; }
		int getTokens() { return nrTokens; }
};

class Transition
{
private:
	string type;
public:
	vector< pair<State*, int> > in, out;

	Transition(string str)
	{
		type = str;
	}
	void addEdgeIn(State &edge, int tokens)
	{
		in.push_back(make_pair(&edge, tokens));
	}

	void addEdgeOut(State &edge, int tokens)
	{
		out.push_back(make_pair(&edge, tokens));
	}
	void fire_in()
	{
		for (int i = 0; i<in.size(); ++i)
		{
			in[i].first->changeTokens(in[i].first->getTokens() - in[i].second);
		}
		cout << "Transition " + type + " has been activated\n";
	}
	void fire_out()
	{
		for (int i = 0; i<out.size(); ++i)
		{
			out[i].first->changeTokens(out[i].first->getTokens() + out[i].second);
		}
	}
	bool can_fire()
	{
		for (int i = 0; i<in.size(); ++i)
			if (in[i].first->getTokens() < in[i].second)
				return false;
		return true;
	}
};

class PetriNetwork
{

private:
	vector<State> states;
	vector<Transition> transitions;
public:

	PetriNetwork() {};

	void createNetwork()
	{

		const int PROD = 0, CONS = 1, PROD_READY = 2, DATA_READY = 3, FILL_POS = 4, FREE_POS = 5, MUTEX = 6;

		for (int i = 0; i<7; ++i)
			states.push_back(State(0));

		Transition prod("PRODUCE");
		prod.addEdgeIn(states[PROD], 1);
		prod.addEdgeOut(states[PROD_READY], 1);

		transitions.push_back(prod);

		Transition cons("CONSUME");
		cons.addEdgeIn(states[DATA_READY], 1);
		cons.addEdgeOut(states[CONS], 1);

		transitions.push_back(cons);

		Transition push("PUSH");
		push.addEdgeIn(states[PROD_READY], 1);
		push.addEdgeIn(states[FREE_POS], 1);
		push.addEdgeIn(states[MUTEX], 1);
		push.addEdgeOut(states[FILL_POS], 1);
		push.addEdgeOut(states[MUTEX], 1);
		push.addEdgeOut(states[PROD], 1);

		transitions.push_back(push);


		Transition pop("POP");
		pop.addEdgeIn(states[MUTEX], 1);
		pop.addEdgeIn(states[FILL_POS], 1);
		pop.addEdgeIn(states[CONS], 1);
		pop.addEdgeOut(states[FREE_POS], 1);
		pop.addEdgeOut(states[MUTEX], 1);
		pop.addEdgeOut(states[DATA_READY], 1);

		transitions.push_back(pop);

		states[PROD].changeTokens(20);
		states[CONS].changeTokens(20);
		states[MUTEX].changeTokens(1);
		states[FREE_POS].changeTokens(10);

	}

	void simulate()
	{
		int round=0;
		while(true)
		{
			round++;
			cout << "Round " << round << '\n';
			vector<Transition> vec;
			vector<Transition> fired;
			for (int j = 0; j<transitions.size(); ++j)
				if (transitions[j].can_fire())
					vec.push_back(transitions[j]);
			srand(time(NULL));
			while (vec.size())
			{
				int index = rand() % vec.size();
				if (vec[index].can_fire())
				{
					vec[index].fire_in();
					fired.push_back(vec[index]);
				}
				vec.erase(vec.begin() + index);
			}
			for (int i = 0; i<fired.size(); ++i)
			{
				fired[i].fire_out();
			}
			Sleep(1000);
		}
	}
};


int main()
{
	//ifstream f("file.in");
	//ofstream g("file.out");
	PetriNetwork petri;
	petri.createNetwork();
	petri.simulate();
	return 0;
}
