#define  _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <iostream>

using namespace std;
const int MAXINT = 100000+10;
int N, a[MAXINT], lefta[MAXINT], righta[MAXINT];

long long merge(int l, int r)
{
	int m = l + (r - l) / 2;
	long long ans = 0;
	for (int i = l; i <= m; i++) lefta[i] = a[i];
	for (int i = m + 1; i <= r; i++) righta[i] = a[i];
	int leftidx = l, rightidx = m + 1, idx = l;
	for (; leftidx <= m && rightidx <= r; idx++)
	{
		if (lefta[leftidx] <= righta[rightidx])
			a[idx] = lefta[leftidx++];
		else
		{
			a[idx] = righta[rightidx++];
			ans += (m - leftidx + 1);
		}
	}
	for (; leftidx <= m; idx++)
		a[idx] = lefta[leftidx++];
	for (; rightidx <= r; idx++)
		a[idx] = righta[rightidx++];
	return ans;
}

long long solve(int l, int r)
{
	if (l >= r) return 0;
	int m = l + (r - l) / 2;
	long long ans = 0;
	ans += solve(l, m);
	ans += solve(m + 1, r);
	ans += merge(l, r);
	return ans;
}

int main()
{
	cin >> N;
	for (int i = 1; i <= N; i++)
	{
		scanf("%d", &a[i]);
	}
	long long ans = solve(1, N);
	cout << ans << endl;
	return 0;
}