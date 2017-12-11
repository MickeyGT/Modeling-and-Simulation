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

class transition
{
private:
	string label;
public:
	vector< pair<State*, int> > in_states, out_states;
	transition(string label)
	{
		this->label = label;
	}
	void add_edge_in(State &in, int weight)
	{
		in_states.push_back(make_pair(&in, weight));
	}
	void add_edge_out(State &out, int weight)
	{
		out_states.push_back(make_pair(&out, weight));
	}
	void fire_in()
	{
		for (int i = 0; i<in_states.size(); ++i)
		{
			in_states[i].first->changeTokens(in_states[i].first->getTokens() - in_states[i].second);
		}
		cout << "Transition " + label + " has fired!\n";
	}
	void fire_out()
	{
		for (int i = 0; i<out_states.size(); ++i)
		{
			out_states[i].first->changeTokens(out_states[i].first->getTokens() + out_states[i].second);
		}
	}
	bool can_fire()
	{
		for (int i = 0; i<in_states.size(); ++i)
			if (in_states[i].first->getTokens() < in_states[i].second)
				return false;
		return true;
	}
};

class PetriNetwork
{

private:
	vector<State> states;
	vector<transition> transitions;
public:

	PetriNetwork() {};

	void create_petri_net()
	{
		const int PROD = 0, CONS = 1, PROD_READY = 2, DATA_READY = 3, FILL_POS = 4, FREE_POS = 5, MUTEX = 6;

		for (int i = 0; i<7; ++i)
			states.push_back(State(0));

		transition prod("PRODUCE");
		prod.add_edge_in(states[PROD], 1);
		prod.add_edge_out(states[PROD_READY], 1);

		transitions.push_back(prod);

		transition cons("CONSUME");
		cons.add_edge_in(states[DATA_READY], 1);
		cons.add_edge_out(states[CONS], 1);

		transitions.push_back(cons);

		transition push("PUSH");
		push.add_edge_in(states[PROD_READY], 1);
		push.add_edge_in(states[FREE_POS], 1);
		push.add_edge_in(states[MUTEX], 1);
		push.add_edge_out(states[FILL_POS], 1);
		push.add_edge_out(states[MUTEX], 1);
		push.add_edge_out(states[PROD], 1);

		transitions.push_back(push);


		transition pop("POP");
		pop.add_edge_in(states[MUTEX], 1);
		pop.add_edge_in(states[FILL_POS], 1);
		pop.add_edge_in(states[CONS], 1);
		pop.add_edge_out(states[FREE_POS], 1);
		pop.add_edge_out(states[MUTEX], 1);
		pop.add_edge_out(states[DATA_READY], 1);

		transitions.push_back(pop);

		states[PROD].changeTokens(20);
		states[CONS].changeTokens(20);
		states[MUTEX].changeTokens(1);
		states[FREE_POS].changeTokens(10);

	}

	void simulate()
	{
		int i = 1;
		for (;; i++)
		{
			cout << "Cycle " << i << '\n';

			vector<transition> vec;
			vector<transition> fired;
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
	petri.create_petri_net();
	petri.simulate();
	return 0;
}
