#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <cmath>

using namespace std;
using counter = unsigned int;
using dvec = vector<double>;
using matrix = vector<dvec>;
counter iters = 0;
counter maxN = 10;
string name = "data.txt";
double bound = 0.00000001;

ostream& operator<< (ostream &os, dvec& x)
{
	stringstream s;
	s<<'[';
	for(auto i : x) 
	{
		s<<i<<',';
	}
	string str = s.str();
	str[str.size()-1] =']';
	os<<str;
	return os;
};
ostream& operator<< (ostream &os, vector<int>& x)
{
	stringstream s;
	s<<'[';
	for(auto i : x) 
	{
		s<<i<<',';
	}
	string str = s.str();
	str[str.size()-1] =']';
	os<<str;
	return os;
};
ostream& operator<< (ostream &os, matrix& m)
{
	for(auto v : m)
	{
		os<<v<<endl;
	}	
	return os;
}
bool in (int j, vector<int>& index)
{
	for(auto i : index)
	{
		if (i == j ) return true;
	}
	return false;
}
int getNotNull(matrix& A, vector<int>& index, int i)
{
	cout<<"index="<<index<<endl;
	counter n = A[0].size();

	for(counter j = 0; j < n; j++)
	{
		cout<<"i="<<i<<",j="<<j<<endl;
		if (in(j, index)) continue;
		if (abs(A[i][j]) > 0) return j;
	}
	return n;
}
int getIndex(vector<int>& index, counter n)
{
	cout<<"index="<<index<<endl;
	for(counter i = 0; i < n; i++)
	{
		if (!in(i,index)) return i;
	}
	return n;
}
void trfMatrix(matrix& A, matrix& I, counter j, vector<int>& index, counter ii)
{
	cout<<"trfMatrix"<<endl;
	counter n = A[0].size();
	cout<<"index="<<index<<endl;
	cout<<"ii="<<ii<<endl;
	cout<<"j="<<j<<endl;

	double a = A[ii][j];
	cout<<"a="<<a<<endl;
	for (counter i = 0; i < n; ++i)
	{
		if (in(i,index))continue;
		double b = A[ii][i];
		if (b == 0) continue;
		cout<<"i="<<i<<endl;
		cout<<"b="<<b<<endl;
		cout<<"ii="<<ii<<endl;
		for (int k = ii; k >= 0; k-=1)
		{
			cout<<"k="<<k<<endl;
			A[k][i] += -(b/a)*A[k][j];
		}
		cout<<"AL="<<endl<<A<<endl;
		for( int k = n-1; k >= 0; k--)
		{
			I[k][i] += -(b/a)*I[k][j];
		}
		cout<<"I="<<endl<<I<<endl;
	}
}
int searchNull(matrix& A)
{
	cout<<"searchNull"<<endl;
	counter n = A[0].size();
	for (counter i = 0; i < n; ++i)
	{
		bool flag = true;
		for (counter j = 0; j < n; ++j)
		{	
			cout<<"A["<<j<<"]["<<i<<"]="<<A[j][i]<<endl;
			if(abs(A[j][i]) > bound)
			{
				flag = false;
				break;
			}
			
		}
		cout<<"flag="<<flag<<endl;
		if ( flag) return i;
	}
	return n;
}
dvec getVector(matrix& A, double l)
{
	matrix AL = A;
	counter n = A[0].size();
	cout<<"l="<<l<<endl;
	for (counter i = 0; i < n; ++i)
	{
		AL[i][i] -= l;
	}
	cout<<"AL="<<endl<<AL<<endl;
	matrix I;
	for (counter i = 0; i < n; ++i)
	{
		dvec tmp;
		for (counter j = 0; j < n; ++j)
		{
			tmp.push_back(0);
			if ( j == i) tmp[i] = 1;
		}
		I.push_back(tmp);
	}
	cout<<"I="<<endl<<I<<endl;
	vector<int> index;
	counter j;
	for(counter i = n-1; i >0; i--)
	{
		j = getNotNull(AL, index, i);
		cout<<"jj="<<j<<endl;
		if ( j == n) throw "bad index from getNotNull";
		index.push_back(j);
		trfMatrix(AL,I,j,index,i);
		j = searchNull(AL);
		if(j != n)
		{ 
			break;
		}
		else 
		{
			j = n;
		}
	}
	if( j == n) j = getIndex(index, n);
	if( j == n) throw "bad index from getIndex";
	dvec res;
	for (counter i = 0; i < n; ++i)
	{
		res.push_back(I[i][j]);
	}
	return res;
}
int main(int argc, char const *argv[])
{
	  // matrix B={{1.0/3.0,1.0/3.0,0},{2.0/3.0,0,2.0/3.0},{0,2.0/3.0,1.0/3.0}};
	// matrix B = {{4,1},{3,2}};
	matrix B = {{1,0,0},{0,2.25,0.433012701892},{0,0.433012701892,2.75}};
    cout<<"B="<<endl<<B<<endl;
    try
    {
    	double l = 1.0;
    	cout<<"l="<<l<<endl;
	    dvec v = getVector(B,l);
		cout<<"v="<<v<<endl;
		l=2.0;
    	cout<<"l="<<l<<endl;
	    v = getVector(B,l);
		cout<<"v="<<v<<endl;
		l=3.0;
    	cout<<"l="<<l<<endl;
	    v = getVector(B,l);
		cout<<"v="<<v<<endl;
	}
	catch(const char* e)
	{
		cout<<"error:"<<e<<endl;
	}
	return 0;
}