#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
double a, b, c, x, y;

double f(double X){
	return sqrt((X - x)*(X - x) + (a*X*X + b*X + c - y)*(a*X*X + b*X + c - y));
}
int main()
{
	cin >> a >> b >> c >> x >> y;
	double left, right ;
	if (x < -b / (2 * a))
	{
		right = -b / (2 * a);
		left = right - 400;
	}
	else
	{
		left = -b / (2 * a);
		right = left + 400;
	}
	while (right-left>0.00000001)
	{
		double lm = (left * 2 + right) / 3, rm = (left + right * 2) / 3;
		if (f(lm) < f(rm))
		{
			right = rm;
		}
		else
		{
			left = lm;
		}
	}
	double ans = f(left);
	printf("%.3lf\n", ans);
	return 0;
}