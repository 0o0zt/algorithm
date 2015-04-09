#include <iostream>
#include <cstring>
#include <iomanip>
#include <vector>
#include <queue>
using namespace std;
const int MAXNODE = 50 + 5;
int cases = 0;
const int INF = 10000000*50;
struct Edge
{
	int s, d;
	double t;
};
class BellmanFord
{
public:
	int n,m;
	vector<int> G[MAXNODE];
	vector<Edge>  edges;
	double dist[MAXNODE];
	int pre[MAXNODE];
	//bool inq[MAXNODE];
	//int cnt[MAXNODE];
	bool solve(int source);
	void init(int n);
	void addedge(int, int, double);
private:

};

void BellmanFord::init(int n){
	this->n = n;
	for (int i = 1; i <= n; i++)
	{
		dist[i] = INF;
		pre[i] = 0;
		for (int j = 1; j <= n; j++)
			G[i].clear();
		edges.clear();
	}
}

void BellmanFord::addedge(int s, int d, double t)
{
	edges.push_back(Edge{ s, d, t });
	m = edges.size();
	G[s].push_back(m - 1);
}

bool BellmanFord::solve(int source)
{
	//bool res = false;
	queue<int> Q;
	for (int i = 1; i <= n; i++)
		dist[i] = i == source ? 0 : INF;
	for (int i = 1; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			Edge e = edges[j];
			if (dist[e.d]>dist[e.s] + e.t)
			{
				dist[e.d] = dist[e.s] + e.t;
				pre[e.d] = e.s;
			}
		}
	}
	for (int j = 0; j < m; j++)
	{
		Edge e = edges[j];
		if (dist[e.d]>dist[e.s] + e.t)
		{
			return true;
		}
	}
	return false;
}

BellmanFord solver;

bool hascycle(double x){

	for (int i = 0; i < solver.m; i++)
		solver.edges[i].t -= x;
	bool ret = solver.solve(1);
	for (int i = 0; i < solver.m; i++)
		solver.edges[i].t += x;
	return ret;
}

int main()
{
	cin >> cases;
	int c = 1 ;
	while (c<=cases){

		int n, m, mt = 0;
		cin >> n >> m;
		solver.init(n);
		for (int i = 0; i < m; i++)
		{
			int s, d;
			double t;
			cin >> s >> d >> t;
			solver.addedge(s, d, t);
			mt = mt>t ? mt : t;
		}

		if (!hascycle(mt + 1)) {
			cout << "Case #"<<c<<": "<<"No cycle found." << endl;
			c++;
			continue;
		}
		
		double r = mt,l = 0;
		while (r - l > 1e-3){
			double mid = (r + l) / 2;
			if (hascycle(mid))
				r = mid;
			else l = mid;
		}
		cout << setiosflags(ios::fixed);
		cout << setprecision(2);
		cout << "Case #" << c << ": " << l << endl;
		c++;
	}
	return 0;
}