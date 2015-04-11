#include <iostream>
#include <cstring>
using namespace std;
const int MOD = 19999997;
struct Matrix
{
	long long x11, x12, x21, x22;
	Matrix operator * (const Matrix & a){
		Matrix res;
		res.x11 = (x11 * a.x11 + x12 * a.x21) % MOD;
		res.x12 = (x11 * a.x12 + x12 * a.x22) % MOD;
		res.x21 = (x21 * a.x11 + x22 * a.x21) % MOD;
		res.x22 = (x21 * a.x12 + x22 * a.x22) % MOD;
		return res;
	}
	void init(long long a, long long b, long long c, long long d){
		x11 = a%MOD; x12 = b%MOD; x21 = c%MOD ; x22 = d%MOD;
	}
};

Matrix m[50];
int binary[50];

void init(){
	m[0].init(0,1,1,1);
	for(int i= 1; i<50; i++){
		m[i] = m[i-1] * m[i-1];
	}
}

int main()
{
	long long input;
	cin>>input;
	int idx = 0;
	memset(binary, 0 , sizeof(binary));
	while(input){
		binary[idx++] = input%2;
		input /= 2;
	}
	init();
	Matrix M;
	M.init(1,0,0,1);
	for(int i=0; i<=idx; i++){
		if(binary[i])
			M = M * m[i];
	}
	cout<<(M.x11+M.x21)%MOD<<endl;
	return 0;
}