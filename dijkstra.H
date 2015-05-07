#include <iostream>
#include <map>
#include <list>
#include <set>
#include "pq_zero.H"
#include <fstream>
#include <stack>

using namespace std;

class WordLadder
{
	private:
		set <string> checked_set;
		map<string, set<string> > neighbors;
		map<string, string> parent;
		list <string> dictionary;
		pq_zero<string> worklist;

		//HELPER FUNCTIONS
		bool isNeighbor(const string &cur, const string &tar)
		{
			int iterator=0;
			for (unsigned i=0; i<cur.size(); i++)	if (cur[i]!=tar[i])	iterator++;
			if (iterator==1)	return true;
			return false;
		}
		void addNeighbors(const string &cur)
		{
			for (list<string>::iterator i=dictionary.begin(); i!=dictionary.end(); i++)	if (isNeighbor(cur, *i) && !checked_set.count(*i))	neighbors[cur].insert(*i);
		}
		void dijkstra(const string &begin, const string &end)
		{
			//push beginning node with 0 priority
			worklist.push(begin, 0);					
			while (!worklist.empty())
			{
				checked_set.insert(worklist.top());
				//iterate through neighbors of worklist.top
				addNeighbors(worklist.top());
				for (set<string>::iterator i=neighbors[worklist.top()].begin(); i!=neighbors[worklist.top()].end(); i++)
				{
					parent[*i] = worklist.top();
					if (*i==end)	return;
					worklist.push(*i, 0);
					//keep track of what is already in the priority queue; if it is in the priority queue, do not add to neighbors
					checked_set.insert(*i);
				}
				worklist.pop();
			}
		}
	public:
		WordLadder (const string &input)
		{
			ifstream list(input.c_str(), ifstream::in);	
			while (list)
			{
				string word;
				list >> word;
				dictionary.push_back(word);
			}
		}
		void outputLadder(const string &begin, const string &end)
		{
			dijkstra(begin, end);
			stack<string> s_stack;
			for (string s = end; s!=""; s=parent[s])	s_stack.push(s);
			unsigned size=s_stack.size();
			for (unsigned i=0; i<size; i++)	
			{
				cout << s_stack.top() << endl;
				if (s_stack.top() == end)	exit(0);
				s_stack.pop();
			}
			cerr << "No valid ladder found" << endl;
			exit(1);
		}	
};

