#include <iostream>
#include <cstdlib>
#include "matrix.h"
#include "utilites.h"
#include <vector>
#include <functional>
#include <cmath>

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
	double x[r];
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
double xi(double a, int i)
{
	if( i == 0) return 1;
	return a*xi(a, i -1);
}
template <typename F1, typename F2>
double skal(const F1 &f1, const F2 &f2, dvec& x, int n)
{
	double res = 0;
	for (int j = 0; j < n; ++j)
	{
		res += f1(x[j]) * f2(x[j]);
	}
	return res;
}
void makeMatrix(matrix& m, matrix& b, dvec& x, dvec& y, int n, int k)
{
	using namespace std::placeholders;
	auto f = [&x,&y](double a)->double
	{
		unsigned int i = 0;
		for (; i < x.size(); ++i)
		{
			if ( a == x[i]) break;
		}
		return y[i];
	};
	auto phi = [](double a, int i)->double
	{
		return xi(a,i);
	};

	for (int i = 0; i < k; ++i)
	{
		auto pi = bind(phi, _1, i);

		for (int j = 0; j < k; ++j)
		{
			auto pj = bind(phi, _1, j);
			m[i][j] = skal(pi, pj, x, n);
		}
		b[i][0] = skal(pi,f, x, n);
	}
}
int main(int argc, char const *argv[])
{
	if (argc > 1) 
	{
		name = string(argv[1]);
		// cout<<name<<endl;
	}
	try
	{
		dvec x, y;
		int k;
		loadData(x, y, k);
		// cout<<x<<endl;
		// cout<<y<<endl;
		// cout<<k<<endl;
		matrix m(k,k);
		matrix b(k,1);
		int n = x.size();
		makeMatrix(m, b, x, y, n, k);
		// cout<<m<<endl;
		// cout<<b<<endl;
		matrix c(k,1);
		c = forthAndBack(m,b);
		// cout<<c<<endl;
		dvec cc;
		for (int i = 0; i < k; ++i)
		{
			cc.push_back(c[i][0]);
		}
		cout<<cc<<endl;
		auto P = [&cc](double a)->double
		{
			int n = cc.size();
			double res = 0;
			for (int i = 0; i < n; ++i)
			{
				res += cc[i]*xi(a,i);
			}
			return res;
		};

		for (int i = 0; i < n; ++i)
		{
			cout<<"P("<<x[i]<<")="<<P(x[i])<<" ";
			cout<<"y="<<y[i]<<endl;
		}

		double dk = 0;
		for (int i = 0; i < n; ++i)
		{
			dk += pow(abs(P(x[i]) - y[i]),2);
		}
		dk /= n;
		dk = sqrt(dk);
		cout<<"dk="<<dk<<endl;
		out(cc, x);

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