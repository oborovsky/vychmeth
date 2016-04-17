#include <iostream>
#include <cstdlib>
#include "matrix.h"
#include <vector>

using namespace std;

template <int r, int c >
matrix<r,c>& forth(matrix<r,c> & m, matrix<r,1>& b)
{
	matrix<r,c> &res = m;
	matrix<r,1> &bb = b;
	// matrix<n> &tmp;

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
		matrix<r,c> T = res.makeT(max,i);
		res = T*res;
		bb = T*bb;
		cout<<res<<endl;
		cout<<bb<<endl;
		for (int j = i+1; j < r; ++j)
		{
			double rr = m[j][i]/m[i][i];
			matrix<r,c> R = res.makeR(i,j,-rr);
			res = R*res;
			bb = R*bb;
			cout<<res<<endl;
			cout<<bb<<endl; 
		}
	}
	b = bb;
	return *(new matrix<r,c>(res.toArray()));
}
int main(int argc, char const *argv[])
{
	try
	{
		// int n = 3;
		// matrix<n> mmm;
		matrix<3,3> m("2,3,1,5,7,9,1,2,3") ;
		matrix<3,1> b("9,6,12");
		cout<<m<<endl;
		cout<<b<<endl;
		matrix<3,3> m2;
		m2 = forth(m,b);
		double x[3];
		for (int i = 2; i >=0; i--)
		{
			double cur = 0;
			for (int j = 2; j > i; j--)
			{
				cur += m[i][j]*x[j];
				cout<<"i="<<i<<" j="<<j<<"cur="<<cur<<endl;
			} 
			x[i] = (b[i][0] - cur) / m[i][i];
		}
		for (auto v : x)
		{
			cout<<v<<endl;
		}
		// cout<<"result:"<<endl<<m2<<endl<<b<<endl;


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