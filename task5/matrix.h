#ifndef MATRIX_H
#define MATRIX_H
#include <vector>
#include <iostream>
#include <iomanip>
#include <string>
#include <exception>

using namespace std;

template <int r, int c >
class matrix 
{
	double m[r][c];
public:
	matrix(double arr[r][c])
	{
		for (int i = 0; i < r; i++)
		{
			for (int j = 0; j < c; j++)
			{
				m[i][j] = arr[i][j];
			}
		}
	};
	matrix(double* arr[c])
	{
		for (int i = 0; i < r; i++)
		{
			for (int j = 0; j < c; j++)
			{
				m[i][j] = arr[i][j];
			}
		}
	};
	matrix(const char* str):matrix(string(str)){};
	matrix(string str)
	{
		int rr = 0,cc = 0;
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
			m[rr][cc] = cur;
			start = end + 1;
			if (cc + 1 < c)
			{
				 cc++;
			}
			else 
			{
				if(rr + 1 < r)
				{
					rr++;
					cc = 0;
				}
				else throw "out of range";
			}
		}
		if (start != end)
		{
			// cout<<"start="<<start<<", end ="<<end<<endl;
			string chunk = str.substr(start, end-start);
			double cur = stod(chunk);
			m[rr][cc] = cur;
		}
	};
	matrix(matrix<r,c>& _m)
	{
		// cout<<"const copy"<<endl;
		for (int i = 0; i < r; ++i)
		{
			for (int j = 0; j < c; ++j)
			{
				m[i][j] = _m.m[i][j];
			}
		}

	};
	matrix()
	{
		for (int i = 0; i < r; ++i)
		{
			for (int j = 0; j < c; ++j)
			{
				m[i][j] = 0;	
			}
		}
	};
	matrix<r,c>& makeT(int i, int j)
	{
		if( i >= r && j >= c) throw "out of range";
		matrix<r,c> &m = makeE();
		m.set(i,j,1);
		m.set(i,i,0);
		m.set(j,j,0);
		m.set(j,i,1);
		return m;
	};
	matrix<r,c>& makeR(int i, int j, double rr)
	{
		if ( i >= r && j >= c) throw "out of range";
		matrix<r,c> &m = makeE();
		m.set(j,i,rr);
		return m;
	}
	matrix<r,c>& makeE()
	{
		double res[r][c];
		for (int i = 0; i < r; ++i)
		{
			for (int j = 0; j < c; ++j)
			{
				res[i][j] = 0;
				if ( i == j) res[i][j] = 1;
			}
		}
		return *(new matrix<r,c>(res));
	};
	matrix<r,c>& operator=(matrix<r,c>& _m)
	{
		// cout<<"oper="<<endl;
		if(&_m == this) return *this;
		for (int i = 0; i < r; ++i)
		{
			for (int j = 0; j < c; ++j)
			{
				m[i][j] = _m.m[i][j];
			}
		}
		return *this;
	};
	matrix<r,c>& operator+(const matrix<r,c>& _m)
	{
		double res[r][c];
		for (int i = 0; i < r; i++)
		{
			for (int j = 0; j < c; j++)
			{
				res[i][j] = m[i][j] + _m.m[i][j];
			}
		}
		cout<<"end +"<<endl;
		return *(new matrix<r,c>(res));
	};
	// matrix<r,c>& operator*(const matrix<r,c>& _m)
	// {
	// 	double res[r][c];
	// 	double cur = 0;
	// 	for (int i = 0; i < r; ++i)
	// 	{
	// 		for (int k = 0; k < c; ++k)
	// 		{
	// 			for (int j = 0; j < c; ++j)
	// 			{
	// 				cur += m[i][j]*_m.m[j][k];
	// 			}
	// 			res[i][k] = cur;
	// 			cur = 0;
	// 		}

	// 	}
	// 	return *(new matrix<r,c>(res));
	// };
	template<int cc>
	matrix<r,cc>& operator*(matrix<c,cc>& _m)
	{
		double res[r][cc];
		double cur = 0;
		for (int i = 0; i < r; ++i)
		{
			for (int k = 0; k < cc; ++k)
			{
				for (int j = 0; j < c; ++j)
				{
					cur += m[i][j]*_m[j][k];
				}
				res[i][k] = cur;
				cur = 0;
			}

		}
		return *(new matrix<r,cc>(res));
	}

	double get(int i, int j)
	{
		return m[i][j];
	}
	void set(int i, int j, double val)
	{
		if( i < r && j < c)
		{
			m[i][j] = val;
		}
	}
	double* operator[](int i)
	{
		if( i < r) return m[i];
		return nullptr;
	};
	double** toArray()
	{
		double ** arr = new double*[r];
		for (int i = 0; i < r; ++i)
		{
			arr[i] = new double[c];
			for (int j = 0; j < c; ++j)
			{
				arr[i][j] = m[i][j];
			}
		}
		return arr;
	}
};
template <int r, int c>
ostream& operator<<(ostream &os, matrix<r,c>& m)
{
	for( int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			os<<setw(10)<<setprecision(2)<<m[i][j];
		}
		os<<endl;
	}
	return os;
}
#endif
