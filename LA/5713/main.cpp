#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
const int maxn = 1000 + 10;
struct Node
{
	int from, to;
	double dist;
	Node(int from, int to, double dist)
	{
		this->from = from;
		this->to = to;
		this->dist = dist;
	}
	bool operator<(const struct Node &ans)const
	{
		return dist > ans.dist;
	}
};

double popu[maxn], edge[maxn][maxn], sum;
int x[maxn], y[maxn];

bool vis[maxn], flag[maxn][maxn];//是否属于树
double dist[maxn];
vector<int> adj[maxn];//MST的邻接表

double EdgeM[maxn][maxn];//每两个点间的最大边

int tcase, n;
void Init()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d%d%lf", &x[i], &y[i], &popu[i]);
	for (int i = 1; i <= n; i++)
	for (int j = 1; j <= n; j++)
	{
		double xx = x[i] - x[j];
		double yy = y[i] - y[j];
		edge[i][j] = sqrt(xx*xx + yy*yy);
	}
}

void Prim()
{
	priority_queue<struct Node> myQue;
	for (int i = 1; i <= n; i++)
	{
		dist[i] = -1;
		vis[i] = false;
		adj[i].clear();
		memset(flag[i], false, sizeof(flag[i]));
	}
	sum = 0;//MST的总长度
	dist[1] = 0;
	vis[1] = true;
	for (int i = 2; i <= n; i++)//以1为起始集合
	{
		dist[i] = edge[1][i];
		myQue.push(Node(1, i, dist[i]));
	}
	while (!myQue.empty())
	{
		struct Node ans = myQue.top();
		myQue.pop();
		int f = ans.from;
		int u = ans.to;
		if (vis[u])
			continue;
		sum += edge[f][u];
		vis[u] = true;//改点已经加入MST了
		flag[f][u] = flag[u][f] = true;
		adj[u].push_back(f);
		adj[f].push_back(u);
		for (int v = 1; v <= n; v++)
		if ((v != u && !vis[v]) && (dist[v] == -1 || dist[v] > edge[u][v]))
		{
			dist[v] = edge[u][v];
			myQue.push(Node(u, v, dist[v]));
		}
	}
}

void DFS(int root, int cur, double MM)
{
	EdgeM[root][cur] = MM;
	vis[cur] = true;
	for (vector<int>::iterator it = adj[cur].begin(); it != adj[cur].end(); it++)
	if (!vis[*it])
		DFS(root, *it, max(MM, edge[cur][*it]));

}

void Solve()
{
	for (int i = 1; i <= n; i++)
	{
		memset(vis, false, sizeof(vis));
		DFS(i, i, 0);
	}

	double ans = -1;
	for (int i = 1; i <= n; i++)
	for (int j = 1; j < i; j++)//枚举super的那条路
	{
		if (flag[i][j])
			ans = max(ans, (popu[i] + popu[j]) / (sum - edge[i][j]));
		else
			ans = max(ans, (popu[i] + popu[j]) / (sum - EdgeM[i][j]));

	}
	printf("%.2lf\n", ans);
}

int main()
{
	scanf("%d", &tcase);
	while (tcase--)
	{
		Init();
		Prim();
		Solve();
	}
	return 0;
}