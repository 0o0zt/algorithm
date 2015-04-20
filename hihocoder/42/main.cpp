#include <iostream>

using namespace std;
const int MOD = 12357;
struct Matrix
{
	int a[6][6];
	
	Matrix & operator = (const Matrix & c) {
		if (this == &c) return *this;
		for (int i=0;i<6; i++)
			for (int j = 0; j<6; j++)
				this->a[i][j] = c.a[i][j];
		return *this;
	};

	Matrix &  operator *= (const Matrix &x) {
		Matrix res; 
		for (int i=0; i<6; i++)
		{
			for (int j=0; j<6; j++)
			{
				res.a[i][j] = 0;
				for (int k = 0; k < 6; k ++)
					res.a[i][j] += this->a[i][k] * x.a[k][j];
				res.a[i][j] %= MOD;
			}
		}
		*this = res;
		return *this;
	};
};

Matrix m[35];
int binary[35];
int minit[6][6] = {
	0,1,1,1,0,0,
	1,0,0,0,1,0,
	1,0,0,0,0,1,
	1,0,0,0,0,0,
	0,1,0,0,0,0,
	0,0,1,0,0,0
};

void init() {
	for (int i = 0; i<6; i++)
	{
		for (int j = 0; j<6; j++)
		{
			m[0].a[i][j] = minit[i][j];
		}
	}
	Matrix me;
	me = m[0];
	for (int i = 1; i<=30; i ++)
	{
		me *= me;
		m[i] = me;
	}
}

int main() 
{
	init();
	int n;
	cin>>n;
	n -= 2;
	int idx = 0;
	while (n)
	{
		binary[idx++] = n%2;
		n /= 2;
	}
	Matrix me;
	for (int i=0; i<6; i++)
		for (int j=0; j<6; j++)
			me.a[i][j] = (i==j);
	for (int i=0; i<idx; i++) 
	{
		if (binary[i])
			me *= m[i];
	}
	cout <<((3* me.a[0][0] + me.a[4][0] + me.a[5][0]) % MOD)<<endl;
	return 0;
}