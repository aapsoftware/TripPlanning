#include <list>
#include <vector>
#include <iostream>

using namespace std;

/*   this solution is O^2 -> sould be optimized to O(n) */

/* define s tructure to hold the result of each day trip */

typedef struct
{
  int value;  //the node selected for day i
  int nodes;  //the number nodes that will be visited by chosing this node
  list<int> l; //list to hold the way from  root to current node
}Sol;

void getParentList(int* parent, int k,  Sol*s);
void testSolution(int k, int w,  int* parent, Sol*s);
void dfs(vector<int>* adjList, int*v, int*u, int* parent, int k, int w, Sol* s);

int _tmain(int argc, _TCHAR* argv[])
{
	const int N=7;
	int T[N] = {1,2,3,3,2,1,4}; //example test 
	int k=2;
	int i;
	int V[N]; //visited nodes array used in dfs
	int U[N]; //visited nodes array used to keep track of unvisited nodes
	int parent[N]; //array thatholds the parents of each of the nodes
	
	vector<int> adjList[N]; // graph representation
  Sol s;
	bool done = false;
	
	/* build adjecy list and initialize relevant array */
	for(i=0;i<N;i++)
	{
		adjList[i].push_back(T[i]);
		adjList[T[i]].push_back(i);
		V[i]=0;
		U[i]=0;
		parent[i]=-1;
	}
	
	/* while there are still unvisited nodes, use DFS to determine the next node to visit 
	   most strucutres must pe reinitilized between calls */
	while(!done)
	{
		dfs(adjList,V,U,parent,k,0,&s);
		cout << s.value <<" ";
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
		}
	}
	return 0;
}

void dfs(vector<int>* adjList, int*v, int*u, int* parent, int k, int w, Sol* s)
{
  v[k]=1;
	vector<int> l = adjList[k];
	while(!l.empty())
	{
	   int n = l.back();
	   l.pop_back();

     if(v[n] == 0 && n!=parent[k])
	   {          
        parent[n] = k;
		    if(u[n]==0)
  		  {
  			  testSolution(n, w+1, parent, s);	
  			  dfs(adjList, v, u, parent, n, w+1, s);	   
  		  }
  		  else
  			  dfs(adjList, v, u, parent, n, w, s);	
	   }	
	}
}

/* test is current node is a solution */
void testSolution(int k, int w, int* parent, Sol*s)
{
  if (s->nodes < w)
  {
    s->nodes =w;
  	s->value =k;
  	int c = k;
  	/* take out of the list all nodes up to the firs common ancestor */
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
  }
}


void getParentList(int* parent, int k, Sol*s)
{
	if(k==-1)
     return;
	getParentList(parent,parent[k],s);    
	s->l.push_front(k);
}
