#include <iostream>
#include <cstdlib>
#include "matrix.h"
#include <vector>

using namespace std;

matrix& forthAndBack(matrix & m, matrix& b)
{
	matrix &res = m;
	matrix &bb = b;
	// matrix<n> &tmp;
	int r = m.getRow();
	// int c = m.getCol();

	for (int i = 0; i < r-1; ++i)
	{
		int max = i;
		for (int k = i; k < r; ++k)
		{
			if(res[k][i] > res[max][i] )
			{
				max = k;
			}
		}
		matrix& T = res.makeT(max,i);
		res = T*res;
		bb = T*bb;
		// cout<<res<<endl;
		// cout<<bb<<endl;
		for (int j = i+1; j < r; ++j)
		{
			double rr = m[j][i]/m[i][i];
			matrix& R = res.makeR(i,j,-rr);
			res = R*res;
			bb = R*bb;
			// cout<<res<<endl;
			// cout<<bb<<endl; 
		}
	}
	double x[3];
	for (int i = r - 1; i >= 0; i--)
	{
		double cur = 0;
		for (int j = r - 1; j > i; j--)
		{
			cur += m[i][j]*x[j];
			// cout<<"i="<<i<<" j="<<j<<"cur="<<cur<<endl;
		} 
		x[i] = (bb[i][0] - cur) / m[i][i];
	}

	for (int i = 0; i < r; ++i)
	{
		b[i][0] = x[i];
	}
	return b;
}
int main(int argc, char const *argv[])
{
	try
	{
		int n = 3;
		// matrix<n> mmm;
		matrix m(n,n,"2,3,1,5,7,9,1,2,3") ;
		matrix b(n,1,"9,6,12");
		matrix x(n,1);
		cout<<m<<endl;
		cout<<b<<endl;
		// matrix m2(3,3);
		x = forthAndBack(m,b);
		cout<<x<<endl;

	}
	catch(string e)
	{
		cout<<e<<endl;
	}
	catch(char* e)
	{
		cout<<e<<endl;
	}
	catch(...)
	{
		cout<<"error"<<endl;
	}
	return 0;
}