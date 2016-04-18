#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include <functional>
#include <random>

using namespace std;
using dvec=vector<double>;

double PI = acos(-1);
auto f = [](double a)->double {return sin(PI*a/2);};
int n = 10;
double a = 0;
double b = 1;
double h = (b - a)/(n-1);
double e = 0.01;

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

int main(int argc, char const *argv[])
{
	string name = "test.txt";
	if (argc > 1) 
	{
		name = string(argv[1]);
	}
	ofstream os(name);
	if(!os) 
	{
		cout<<"невозможно создать файл"<<endl;
		exit(1);
	};
	default_random_engine genr;
	uniform_real_distribution<double> distr(0.0, 1.0);

	for (int i = 0; i < n; ++i)
	{
		double random = pow(-1,i)*e*distr(genr);
		double r = f(a+i*h) + random;
		os<<r<<" ";
		cout<<"r="<<random<<" ";
	}
	os<<endl;
	for (int i = 0; i < n; ++i)
	{
		double r = a+i*h;
		os<<r<<" ";
	}
	os<<endl;
	cout<<PI<<endl;
}