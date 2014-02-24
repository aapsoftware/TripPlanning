#include "stdafx.h"
#include <list>
#include <vector>
#include <iostream>

using namespace std;

typedef struct
{
  int value;
  int nodes;
  list<int> l;
}Sol;

void getParentList(int* parent, int k,  Sol*s);
void testSolution(int k, int w,  int* parent, list<Sol>*s);
void dfs(list<int>* adjList, int*v, int*u, int* parent, int k, int w, list<Sol>* s);
int _tmain(int argc, _TCHAR* argv[])
{
	const int N=7;
	int T[N] = {1,2,3,3,2,1,4};
	int k=2;
	int i;
	int V[N];
	int U[N];
	int parent[N];
	list<int> adjList[N];
	vector<int> solution;
    list<Sol> s;
	bool done = false;
	for(i=0;i<N;i++)
	{
		if(i!=T[i])
		{
           adjList[i].push_back(T[i]);
		   adjList[T[i]].push_back(i);
		}
		V[i]=0;
		U[i]=0;
		parent[i]=-1;
	}
	solution.push_back(k);
	while(!done)
	{
		dfs(adjList,V,U,parent,k,0,&s);

		while(!s.empty())
		{
		   
		}

		/*solution.push_back(s.value);
		s.nodes=-1;
		s.value=-1; 
		k = s.l.front();
		while(!s.l.empty())
		{
			U[s.l.back()]=1;
			s.l.pop_back();
		}
		done =true;
		for(i=0;i<N;i++)
		{
			V[i]=0;
			parent[i]=-1;
			if(U[i]==0)
				done=false;
		}*/
	}


	for(i=0;i<solution.size();i++)
	{
		cout<<solution[i]<<" ";
	}
	return 0;
}

void dfs(list<int>* adjList, int*v, int*u, int* parent, int k, int w, list<Sol>* s)
{    
	list<int> l = adjList[k];
	if(l.size()==1 && v[k] == 0) 
		testSolution(k, w, parent, s);	

	v[k]=1;

	while(!l.empty())
	{
		int n = l.back();

		if(v[n] == 0 && n!=parent[k])
		{          
			parent[n] = k;
			if(u[n]==0)
			{  			 
				// testSolution(n, w+1, parent, s);	
				dfs(adjList, v, u, parent, n, w+1, s);	   
			}
			else
				dfs(adjList, v, u, parent, n, w, s);	
		}
		l.pop_back();
	}
}

void testSolution(int k, int w, int* parent, list<Sol>*s)
{

  Sol n;
  n.nodes = w;
  n.value = k;
  n.l.push_back(k);
  int t = parent[k];
  while(t!=-1)
  {
	  n.l.push_back(t);
      t = parent[t];
  }

  s->push_back(n);


  /*if (s->nodes < w)
  {
    s->nodes =w;
	s->value =k;
	
	int c = k;
	while(!s->l.empty()&&s->l.front()!=c)
	{
	  s->l.pop_front();  
	  c = parent[c];
	}
	
	getParentList(parent, k, s);
	
  }
  else if(s->value > k  && s->nodes == w)
  {
	  s->value = k;	 

	  while(!s->l.empty()&&s->l.front()!=k)	 
		  s->l.pop_front();      

	  getParentList(parent, k, s);
  }*/
}


void getParentList(int* parent, int k, Sol*s)
{
	if(k==-1)
     return;
	getParentList(parent,parent[k],s);    
	s->l.push_front(k);
}
