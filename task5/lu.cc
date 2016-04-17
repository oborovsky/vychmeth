#include <iostream>
#include <cstdlib>
#include "matrix.h"
#include <vector>

using namespace std;

template <int n>
matrix<n>& forth(matrix<n> & m)
{
	matrix<n> &res = m;
	// matrix<n> &tmp;

	for (int i = 0; i < n-1; ++i)
	{
		int max = i;
		for (int k = i; k < n; ++k)
		{
			if(res[k][i] > res[max][i] )
			{
				max = k;
			}
		}
		matrix<n> T = res.makeT(max,i);
		res = T*res;
		cout<<res<<endl;
		for (int j = i+1; j < n; ++j)
		{
			double r = m[j][i]/m[i][i];
			matrix<n> R = res.makeR(i,j,-r);
			res = R*res;
			cout<<res<<endl; 
		}
	}
	return *(new matrix<n>(res.toArray()));
}
int main(int argc, char const *argv[])
{
	try
	{
		matrix<3> m("1,2,3,4,5,6,7,8,11") ;
		cout<<m<<endl;
		matrix<3> m2;
		m2 = forth(m);
		cout<<"result:"<<endl<<m2<<endl;


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