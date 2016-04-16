#ifndef MATRIX_H
#define MATRIX_H
#include <vector>
#include <iostream>
#include <iomanip>
#include <string>
#include <exception>

using namespace std;

template <int n>
class matrix 
{
	double m[n][n];
public:
	matrix(double arr[n][n])
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				m[i][j] = arr[i][j];
			}
		}
	};
	matrix(double* arr[n])
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				m[i][j] = arr[i][j];
			}
		}
	};
	matrix(const char* str):matrix(string(str)){};
	matrix(string str)
	{
		int r = 0,c = 0;
		int start = 0, end = 0;

		for (; end < str.size(); end++)
		{
			// cout<<str[end]<<":";
			if (str[end]!= ',') continue;
			// cout<<"start="<<start<<", end ="<<end<<endl;
			string chunk = str.substr(start,end-start);
			// cout<<chunk<<endl;
			double cur = stod(chunk);
			// cout<<"r="<<r<<" ,c="<<c<<endl;
			m[r][c] = cur;
			start = end + 1;
			if ( c + 1< n)
			{
				 c++;
			}
			else 
			{
				if( r + 1 < n)
				{
					r++;
					c = 0;
				}
				else throw "out of range";
			}
		}
		if (start != end)
		{
			// cout<<"start="<<start<<", end ="<<end<<endl;
			string chunk = str.substr(start, end-start);
			double cur = stod(chunk);
			m[r][c] = cur;
		}
	};
	matrix(matrix<n>& _m)
	{
		// cout<<"const copy"<<endl;
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				m[i][j] = _m.m[i][j];
			}
		}

	};
	matrix()
	{
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				m[i][j] = 0;	
			}
		}
	};
	matrix<n>& makeT(int i, int j)
	{
		if( i >= n && j >= n) throw "out of range";
		matrix<n> &m = makeE();
		m.set(i,j,1);
		m.set(i,i,0);
		m.set(j,j,0);
		m.set(j,i,1);
		return m;
	};
	matrix<n>& makeR(int i, int j, double r)
	{
		if ( i >= n && j >= n) throw "out of range";
		matrix<n> &m = makeE();
		m.set(j,i,r);
		return m;
	}
	matrix<n>& makeE()
	{
		double res[n][n];
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				res[i][j] = 0;
				if ( i == j) res[i][j] = 1;
			}
		}
		return *(new matrix<n>(res));
	};
	matrix<n>& operator=(matrix<n>& _m)
	{
		// cout<<"oper="<<endl;
		if(&_m == this) return *this;
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				m[i][j] = _m.m[i][j];
			}
		}
		return *this;
	};
	matrix<n>& operator+(const matrix<n>& _m)
	{
		double res[n][n];
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				res[i][j] = m[i][j] + _m.m[i][j];
			}
		}
		cout<<"end +"<<endl;
		return *(new matrix<n>(res));
	};
	matrix<n>& operator*(const matrix<n>& _m)
	{
		double res[n][n];
		double cur = 0;
		for (int i = 0; i < n; ++i)
		{
			for (int k = 0; k < n; ++k)
			{
				for (int j = 0; j < n; ++j)
				{
					cur += m[i][j]*_m.m[j][k];
				}
				res[i][k] = cur;
				cur = 0;
			}

		}
		return *(new matrix<n>(res));
	}
	double get(int i, int j)
	{
		return m[i][j];
	}
	void set(int i, int j, double val)
	{
		if( i < n && j < n)
		{
			m[i][j] = val;
		}
	}
	double* operator[](int i)
	{
		if( i < n) return m[i];
		return nullptr;
	};
	double** toArray()
	{
		double ** arr = new double*[n];
		for (int i = 0; i < n; ++i)
		{
			arr[i] = new double[n];
			for (int j = 0; j < n; ++j)
			{
				arr[i][j] = m[i][j];
			}
		}
		return arr;
	}
};
template <int n>
ostream& operator<<(ostream &os, matrix<n>& m)
{
	for( int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			os<<setw(3)<<m[i][j];
		}
		os<<endl;
	}
	return os;
}
#endif
