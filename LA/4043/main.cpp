#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;
const int MAXN = 200;
const int INF = 1<<31-1;

double w[MAXN][MAXN], slack[MAXN], lx[MAXN], ly[MAXN];
int  match[MAXN], n;
bool vistx[MAXN], visty[MAXN];

struct point {
	double x, y;
} tree[MAXN], ant[MAXN];

bool dfs(int u){
	vistx[u] = true;
	for (int i = 1; i <= n; i++)
	{
		if (visty[i]) continue;
		
		double t = lx[u] + ly[i] - w[u][i];
		if (fabs(t)<1e-6) {
			visty[i] = true;
			if (!match[i] || dfs(match[i])) {
				match[i] = u;
				return true;
			}
		}
		else if (t < slack[i])
			slack[i] = t;
	}
	return false;
}

void update() {
	double d = INF;
	for (int i = 1; i <= n; i++) {
		if (!visty[i] && slack[i] < d)
			d = slack[i];
	}
	for (int i = 1; i <= n; i++) {
		if (vistx[i]) lx[i] -= d;
	}
	for (int i = 1; i <= n; i++) {
		if (visty[i]) ly[i] += d;
		else slack[i] -= d;
	}
}

int solve(){
	memset(match, 0, sizeof(match));
	memset(ly, 0, sizeof(ly));
	for (int i = 1; i <= n; i++) 
		lx[i] = 0;
	for (int i = 1; i <= n; i++)
	for (int j = 1; j <= n; j++)
		lx[i] = max(lx[i], w[i][j]);

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
			slack[j] = INF;
		while (1){
			memset(vistx, 0, sizeof(vistx));
			memset(visty, 0, sizeof(visty));

			if (dfs(i)) break;
			update();
		}
	}

	int ans = 0;
	for (int i = 1; i <= n; i++)
		ans += (lx[i] + ly[i]);
	return ans;
}

int main(){
	while (cin>>n) {
		for (int  i = 1; i <= n; i++)
			cin>>ant[i].x>>ant[i].y ;
		for (int i = 1; i <= n; i++)
			cin>>tree[i].x>>tree[i].y;
		for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			w[i][j] = -sqrt((tree[i].x - ant[j].x) * (tree[i].x - ant[j].x) + (tree[i].y - ant[j].y) * (tree[i].y - ant[j].y));
		solve();
		for (int i = 1; i <= n; i++)
			cout << match[i] << endl;
		cout << endl;
	}
	return 0;
}