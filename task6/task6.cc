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
double bound = 0.000000001;

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
void loadData(matrix& A, dvec& b, double& e)
{
	ifstream is(name);
	if(!is)
	{
		cout<<"невозможно открыть файл"<<endl;
		exit(1);
	}
	counter n = 0;
	is>>n;
	for (counter i = 0; i < n; ++i)
	{
		dvec tmp;
		for (counter j = 0; j < n; ++j)
		{
			double r;
			is>>r;
			tmp.push_back(r);
		}
		A.push_back(tmp);
	}
	for (counter i = 0; i < n; ++i)
	{
		double r;
		is>>r;
		b.push_back(r);
	}
	is>>e;
}
double operator*(dvec v1, dvec v2)
{
	counter n = v1.size();
	double res = 0;
	for (counter i = 0; i < n; ++i)
	{
		res += v1[i]*v2[i];
	}
	return res;
}
dvec operator-(dvec v1, dvec v2)
{
	dvec res;
	counter n = v1.size();
	for (counter i = 0; i < n; ++i)
	{
		res.push_back(v1[i] - v2[i]);
	}
	return res;
}
dvec mult(matrix& A, dvec& x)
{
	dvec res;
	for(auto v:A)
	{
		res.push_back(v*x);
	}
	return res;
}
double norma(dvec& v)
{
	double res = 0;
	for(auto i : v)
	{
		res += i*i;
	}
	return sqrt(res);
}
//решение линейного ур. Ax=b методом релаксаций
dvec relaxation(matrix& A, dvec& b, dvec& x0, double e)
{
	counter n = x0.size();
	dvec x1, x2(n),bb;
	x1 = x0;
	x2 = x1;
	bb = b;
	bb = mult(A,x2) - bb;
	iters = 0;
	while( norma(bb) > e ) 
	{
		iters++;
		for (counter i = 0; i < n; ++i)
		{
			double t1, t2;
			t1 = 0;
			t2 = 0;
			for (counter j = 0; j < i; ++j)
			{
				t2 += A[i][j]*x2[j];
			}
			for (counter j = i + 1; j < n; ++j)
			{
				t1 += A[i][j]*x1[j];
			}

			x2[i] = (1-e)*x1[i] + e*(b[i] - t2 - t1)/A[i][i]; 
		}
		x1 = x2;
		bb = b;
		bb = mult(A,x2) - bb;
	}
	return x2;
}
// собственные числа матрицы методом Якоби
double ND(matrix& A)
{
	double res = 0;
	counter n = A[0].size();

	for (counter i = 0; i < n; ++i)
	{
		for (counter j = 0; j < n; ++j)
		{
			if (i == j) continue;
			res += A[i][j]*A[i][j];
		}
	}
	return sqrt(res);
}

void rotation(matrix& A, counter i, counter j)
{
	double t = (A[i][i] - A[j][j]) / (2 * A[i][j]);
	int sgnt = (t > 0) ? 1 : -1;
	double tt;

	if ( t == 0)
	{
		tt = 1;
	}
	else
	{
		tt = 1/(t + sgnt*sqrt(t*t+1));
	}
	double c = 1/sqrt(tt*tt + 1);
	double s = tt*c;
	matrix Q;
	matrix Qt;
	counter n = A[0].size();

	for (counter ii = 0; ii < n; ++ii)
	{
		dvec q;
		for (counter jj = 0; jj < n; ++jj)
		{
			q.push_back(0);
			if ( jj == ii )
			{ 
				q[jj] = 1;
				if ( i == ii || j == ii)
				{
					q[jj] = c;
				}

			}
			if (i == ii && j == jj)
			{
				q[jj] = -s;
			}
			if (i == jj && j == ii)
			{
				q[jj] = s;
			}
		}
		Q.push_back(q);
	}
	// cout<<Q<<endl;
	matrix A1;
	for (counter ii = 0; ii < n; ++ii)
	{
		dvec tmp;
		for (counter jj = 0; jj < n; ++jj)
		{
			double res = 0;
			for (counter k = 0; k < n; ++k)
			{
				res += A[ii][k]*Q[k][jj];
			}
			tmp.push_back(res);
		}
		A1.push_back(tmp);
	}
	matrix A2;
	for (counter ii = 0; ii < n; ++ii)
	{
		dvec tmp;
		for (counter jj = 0; jj < n; ++jj)
		{
			double res = 0;
			for (counter k = 0; k < n; ++k)
			{
				res += Q[k][ii] * A1[k][jj];
			}
			tmp.push_back(res);
		}
		A2.push_back(tmp);
	}
	A = A2;
	// cout<<A<<endl;
}
void next(matrix& A, counter& i, counter& j)
{
	static counter ii=1,jj=1;
	counter n = A[0].size();
	do{
		jj++;
		if( ii == jj) jj++;
		jj = jj%(n+1);
		if( jj == 0)
		{
			jj = 1;
			ii++;
			ii = ii%(n+1);
			if( ii == 0)
			{
				ii = 1;
			    jj++;
			}
		}
	}
	while(abs(A[ii-1][jj-1]) < bound);
	i = ii-1;
	j = jj-1;
}
void methodJacobi(matrix& A, double e)
{	
	iters = 0;
	counter i=0, j=1;
	while (ND(A) > e)
	{
		iters++;
		next(A, i, j);
		rotation(A, i,j);
		// cout<<"i="<<i<<",j="<<j<<endl;
		// cout<<"A="<<A<<endl;
		// cout<<"ND(A)="<<ND(A)<<endl;
	}
}
//нахождение собственных векторов методом Чуркина
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
	// cout<<"index="<<index<<endl;
	counter n = A[0].size();

	for(counter j = 0; j < n; j++)
	{
		// cout<<"i="<<i<<",j="<<j<<endl;
		if (in(j, index)) continue;
		if (abs(A[i][j]) > 0) return j;
	}
	return n;
}
int getIndex(vector<int>& index, counter n)
{
	// cout<<"index="<<index<<endl;
	for(counter i = 0; i < n; i++)
	{
		if (!in(i,index)) return i;
	}
	return n;
}
void trfMatrix(matrix& A, matrix& I, counter j, vector<int>& index, counter ii)
{
	counter n = A[0].size();
	// cout<<"trfMatrix"<<endl;
	// cout<<"index="<<index<<endl;
	// cout<<"ii="<<ii<<endl;
	// cout<<"j="<<j<<endl;

	double a = A[ii][j];
	// cout<<"a="<<a<<endl;
	for (counter i = 0; i < n; ++i)
	{
		if (in(i,index))continue;
		double b = A[ii][i];
		if (b == 0) continue;
		// cout<<"i="<<i<<endl;
		// cout<<"b="<<b<<endl;
		// cout<<"ii="<<ii<<endl;
		for (int k = ii; k >= 0; k-=1)
		{
			// cout<<"k="<<k<<endl;
			A[k][i] += -(b/a)*A[k][j];
		}
		// cout<<"AL="<<endl<<A<<endl;
		for( int k = n-1; k >= 0; k--)
		{
			I[k][i] += -(b/a)*I[k][j];
		}
		// cout<<"I="<<endl<<I<<endl;
	}
}
int searchNull(matrix& A)
{
	// cout<<"searchNull"<<endl;
	counter n = A[0].size();
	for (counter i = 0; i < n; ++i)
	{
		bool flag = true;
		for (counter j = 0; j < n; ++j)
		{	
			// cout<<"A["<<j<<"]["<<i<<"]="<<A[j][i]<<endl;
			if(abs(A[j][i]) > bound)
			{
				flag = false;
				break;
			}
			
		}
		// cout<<"flag="<<flag<<endl;
		if ( flag) return i;
	}
	return n;
}
dvec getVector(matrix& A, double l)
{
	matrix AL = A;
	counter n = A[0].size();
	// cout<<"l="<<l<<endl;
	for (counter i = 0; i < n; ++i)
	{
		AL[i][i] -= l;
	}
	// cout<<"AL="<<endl<<AL<<endl;
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
	// cout<<"I="<<endl<<I<<endl;
	vector<int> index;
	counter j;
	for(counter i = n-1; i >0; i--)
	{
		j = getNotNull(AL, index, i);
		// cout<<"jj="<<j<<endl;
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
	// j = getIndex(index, n);
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
	if (argc > 1) 
	{
		name = string(argv[1]);
		// cout<<name<<endl;
	}
	matrix A;
	dvec b;
	double e;
	loadData(A, b, e);
	cout<<"A="<<endl<<A<<endl;
	cout<<"b="<<b<<endl;
	cout<<"e="<<e<<endl;
	dvec res = relaxation(A, b, b, e);
	cout<<"x="<<res<<endl;

	matrix AA = A;
	methodJacobi(AA,e);
	counter n = AA[0].size();

	for (counter i = 0; i < n; ++i)
	{
		
		cout<<" l"<<i+1<<"="<<AA[i][i]<<endl;
		try
	    {
	    	double l = AA[i][i];
		    dvec v = getVector(A,l);
			cout<<"v"<<i+1<<"="<<v<<endl;
		}
		catch(const char* e)
		{
			cout<<"error:"<<e<<endl;
		}
	}

	// cout<<"number iteration: "<<iters<<endl;
	return 0;
}