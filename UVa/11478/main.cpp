#include <vector>
#include <iostream>
#include <cstring>
using namespace std;

const int MAXNODE = 500 + 1;
const int MAXEDGE = 2700 + 1;
const int MAXD = 10000;

struct Edge
{
	int from, to, dist;
	Edge(int _from, int _to, int _dist){
		from = _from;
		to = _to;
		dist = _dist;
	}
};

vector<int> G[MAXNODE];
vector<Edge> edges;
int pre[MAXNODE];

struct BellmanFord
{
	vector<int> G[MAXNODE];
	vector<Edge> edges;
	int dist[MAXNODE];
	int n, m;
	void init(int _n)
	{
		n = _n;
		for (int i = 0; i <= n; i++)
			G[i].clear();
		edges.clear();
	}
	void addEdge(int from, int to, int dist)
	{
		edges.push_back(Edge( from, to, dist ));
		m = edges.size();
		G[from].push_back(m - 1);
	}
	bool solve()
	{
		for (int i = 1; i <= n; i++)
			dist[i] = (MAXNODE - 1) * MAXD;
		dist[0] = 0;
		for (int i = 1; i < n; i++)
		{
			for (int i = 0; i< edges.size(); i++)
			{
				Edge e = edges[i];
				if (dist[e.to] > dist[e.from] + e.dist)
					dist[e.to] = dist[e.from] + e.dist;
			}
		}
		for (int i = 0; i< edges.size(); i++)
		{
			Edge e = edges[i];
			if (dist[e.to] > dist[e.from] + e.dist)
				return false;
		}
		return true;
	}
};

BellmanFord solver;
int nodeNum, edgeNum;

bool dfs(int u){
	for (int v = 0; v < G[u].size(); v++)
	{
		if (pre[edges[v].to]++ || dfs(edges[v].to))
			return true;
	}
	return false;
}

bool hasCycle(){
	for (int i = 1; i <= nodeNum; i++)
	{
		if (pre[i])
			continue;
		pre[i] = 1;
		if (dfs(i))
			return true;
	}
	return false;
}

bool test(int x){
	solver.init(nodeNum);
	for (int i = 1; i <= nodeNum; i++)
	{
		solver.addEdge(0, i, 0);
	}
	for (int i = 0; i< edges.size(); i++)
	{
		Edge e = edges[i];
		solver.addEdge(e.to, e.from, e.dist - x);
	}
	return solver.solve();
}

int main()
{
	while (cin >> nodeNum >> edgeNum){
		memset(pre, 0, sizeof(pre));
		for (int i = 1; i <= nodeNum; i++)
		{
			G[i].clear();
		}
		edges.clear();
		for (int i = 0; i < edgeNum; i++)
		{
			int from, to, dist;
			cin >> from >> to >> dist;
			edges.push_back(Edge(from, to, dist ));
			G[from].push_back(edges.size() - 1);
		}
		if (test(MAXD))
		{
			cout << "Infinite" << endl;
			continue;
		}
		if (!test(0))
		{
			cout << "No Solution" << endl;
			continue;
		}
		int l = 0, r = MAXD;
		while (r > l){
			int mid = l + (r - l + 1) / 2;
			if (test(mid))
				l = mid;
			else
				r = mid - 1;
		}
		cout << l << endl;
	}
	return 0;
}