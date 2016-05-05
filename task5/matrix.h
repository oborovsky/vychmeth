#ifndef MATRIX_H
#define MATRIX_H
#include <vector>
#include <iostream>
#include <iomanip>
#include <string>
#include <exception>
#include <cstring>
#include <functional>

using namespace std;

class matrix 
{
	int r;
	int c;
	double** m = nullptr;
	matrix(){};
	double** getmem(int r, int c)
	{
		double **mem;
		mem = new double*[r];

		for (int i = 0; i < r; ++i)
		{
			mem[i] = new double[c];	
		}
		return mem;
	}
	void freemem(int r, int c)
	{
		if (m != nullptr)
		{
			for (int i = 0; i < r; ++i)
			{
				delete[] m[i];
			}
		}
		delete[] m;
	}
public:
	~matrix()
	{
		freemem(r,c);
		m = nullptr;
	}
	matrix(int _r, int _c, double** arr):r(_r),c(_c),m(arr){};
	matrix(int _r, int _c, const char* str):matrix(_r, _c, string(str)){};
	matrix(int _r, int _c, string str):r(_r),c(_c)
	{
		int rr = 0,cc = 0;
		unsigned int start = 0, end = 0;

		m = getmem(r,c);

		for (; end < str.size(); end++)
		{
			if (str[end]!= ',') continue;
			string chunk = str.substr(start,end-start);
			double cur = stod(chunk);
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
			string chunk = str.substr(start, end-start);
			double cur = stod(chunk);
			m[rr][cc] = cur;
		}
	};
	matrix(matrix& _m)
	{
		r = _m.r;
		c = _m.c;
		m = _m.toArray();
	};
	matrix(int _r, int _c):r(_r),c(_c)
	{
		m = getmem(r, c);
		for (int i = 0; i < r; ++i)
		{
			for (int j = 0; j < c; ++j)
			{
				m[i][j] = 0;	
			}
		}
	};
	void transpose(int i, int j)
	{
		double tmp;
		for (int k = 0; k < c; ++k)
		{
			tmp = m[i][k];
			m[i][k] = m[j][k];
			m[j][k] = tmp;
		}
	}
	void addRow(int i, int j, double rr)
	{
		for (int ii = 0; ii < c; ++ii)
		{
			m[j][ii] += rr*m[i][ii];
		}
	}
	matrix& operator=(matrix& _m)
	{
		if(_m.m == this->m) return *this;
		if (r != _m.r && c != _m.c)
		{
			throw "different rang of matrix";
		}
		
		for (int i = 0; i < r; ++i)
		{
			for (int j = 0; j < c; ++j)
			{
				m[i][j] = _m.m[i][j];
			}
		}
		return *this;
	};
	matrix& operator+(matrix& _m)
	{
		for (int i = 0; i < r; i++)
		{
			for (int j = 0; j < c; j++)
			{
				m[i][j] += _m.m[i][j];
			}
		}
		return *this;
	};
	matrix& operator*(matrix& _m)
	{
		double** res = getmem(r, _m.c);
		double cur = 0;
		for (int i = 0; i < r; ++i)
		{
			for (int k = 0; k < _m.c; ++k)
			{
				for (int j = 0; j < c; ++j)
				{
					cur += m[i][j]*_m[j][k];
				}
				res[i][k] = cur;
				cur = 0;
			};
		};
		freemem(r,c);
		c = _m.c;
		m = res;
		return *this;
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
	int getRow(){return r;};
	int getCol(){return c;};
	double* operator[](int i)
	{
		if( i < r) return m[i];
		return nullptr;
	};
	double** toArray()
	{
		double ** arr = getmem(r,c);
		for (int i = 0; i < r; ++i)
		{
			memcpy(arr[i], m[i], sizeof(double)*c);
		}
		
		return arr;
	}
	friend ostream& operator<<(ostream&, matrix&);
};
ostream& operator<<(ostream &os, matrix& m)
{
	for( int i = 0; i < m.r; i++)
	{
		for (int j = 0; j < m.c; j++)
		{
			os<<setw(10)<<setprecision(2)<<m[i][j];
		}
		os<<endl;
	}
	return os;
}
#endif
