#include <iostream>
#include <vector>
#include <map>
#include <queue>

using namespace std;

template <class Item>
class pq_zero{
	private:
		vector<Item> heap;
		typedef int indx;
		map<Item, indx> index;
		map<Item, float> priority;

		/*HELPER FUNCTIONS*/
		unsigned getParent(int child)	{return (child-1)/2;}
		unsigned getLChild(int parent)	{return (parent*2)+1;}
		unsigned getRChild(int parent)	{return (parent*2)+2;}
		void swap(indx first, indx second)
		{
			Item temp = heap[first];
			heap[first] = heap[second];
			heap[second] = temp;
		}
		//FUNCTION TO CHECK IF DUPLICATE PRIORITY EXISTS
		bool priDup(float pri)
		{
			typename map<Item, float>::iterator i;
			i=priority.begin();
			for (; i!=priority.end(); i++)	if (i->second == pri)	return true;
			return false;
		}
		//FUNCTION TO DECREASE PRIORITY 
		void decreaseKey(Item w)	
		{
			typename map<Item, float>::iterator i=priority.begin();
			for (; i!=priority.end(); i++)	
			{
				if (i->first!=w && int(i->second) == int(priority[w]))
				{
					priority[w]+=.0001;
				}
			}
		}
		void percolate_up(indx i)
		{
			int x =i; 
			//loop until fully perculated up or until parent node has lower priority 
			while (x>0 && priority[heap[getParent(x)]] >= priority[heap[x]] )
			{	
				swap(x, getParent(x));
				index[heap[x]]=x;
				index[heap[getParent(x)]]=getParent(x);
				x=getParent(x);
			}
		}
		void percolate_down(indx i)
		{
			//if i has no children, return recursive function
			if (getLChild(i)>heap.size()-1)	{return;}
			//checking children of indx i, if children have lower priority then swap
			if (priority[heap[i]] > priority[heap[getLChild(i)]] || priority[heap[i]] > priority[heap[getRChild(i)]] )
			{
				//left child has higher priority than right
				if (priority[heap[getLChild(i)]] < priority[heap[getRChild(i)]])
				{
					swap(i, getLChild(i));
					index[heap[i]] = i;
					percolate_down(getLChild(i));
				}
				else
				{
					swap(i, getRChild(i));
					index[heap[i]] = i;
					percolate_down(getRChild(i));
				}
			}
		}
		void build_heap(vector<Item> itms, vector<float> pris)
		{
			//build heap vector and maps
			for (unsigned i=0; i<itms.size(); i++)
			{
				heap.push_back(itms[i]);
				index[heap[i]]=i;
				priority[heap[i]]=pris[i];
			}
			for (int x=(heap.size()/2)-1; x>=0; --x)	percolate_down(x);
		}
	public:
		/*CONSTRUCTOR + BIG3*/
		pq_zero()	{}
		pq_zero(vector<Item> itms, vector<float> pris)	{build_heap(itms, pris);}
		~pq_zero()	{}
		pq_zero(const pq_zero &copy)
		{
			for (unsigned i=0; i<size(); i++)
			{
				heap[i] = copy.heap[i];
				index[heap[i]] = copy.index[heap[i]];
				priority[heap[i]] = copy.priority[heap[i]];
			}
			
		}
		pq_zero& operator=(const pq_zero &copy)
		{
			if (this != &copy)
			{
				for (unsigned i=0; i<size(); i++)
				{
					heap[i] = copy.heap[i];
					index[heap[i]] = copy.index[heap[i]];
					priority[heap[i]] = copy.priority[heap[i]];
				}
			}
			return *this;
		}
		const Item& top() const	{return heap[0];}	
		int size()const	{return heap.size();}
		bool empty()const
		{
			if (heap.empty())	{return true;}
			return false;
		}
		void pop()
		{
			if (empty())	return;
			heap[0]=heap[heap.size()-1];
			heap.pop_back();
			percolate_down(0);
		}
		void push( const Item& w, float prio)
		{
			priority[w]=prio;
			if (priDup(prio))	decreaseKey(w);	
			bool keyExists=false;
			unsigned i=0;
			for (; i<heap.size(); i++)
			{
				if (heap[i] == w)
				{
					keyExists=true;
					break;
				}
			} 
			if (keyExists)
			{
				index[w] = i;
				percolate_up(i);
				percolate_down(0);
			}
			else
			{
				heap.push_back(w);
				index[w] = heap.size()-1;
				percolate_up(index[w]);
			}
		}
};
