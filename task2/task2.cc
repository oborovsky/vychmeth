#include <iostream>
#include <cmath>
#include <vector>
#include <sstream>
#include <functional>
#include <iomanip>

using namespace std;
using dvec = vector<double>;
struct Interval
{
	double a;
	double b;
	double length() { return b - a;};
};

const unsigned long n = 100;

auto func = [](double a)->double {return sqrt(a);};
Interval interval = {0,3};

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
}

template<typename F>
void makeNodeOfInterval(dvec& x, unsigned long nodes, const F& next)
{
	for (int i = 0; i < nodes; i++) 
	{
		x.push_back(next(i));
	} 
}
double integralSimpson(dvec& x)
{
	double result = func(x[0]);
	unsigned long length = x.size();

	for(unsigned long i = 1; i < length - 1 ; i += 2)
	{
		result += 4 * func(x[i]) + 2 * func(x[i+1]);
	}
	result += func(x[length-1]);
	result *= interval.length()/(3 * length);
	return result;
}
double integralGauss(dvec&x)
{
	double result = 0;
	unsigned long length = x.size();

	for (unsigned long i = 0; i < length - 1; i++)
	{
		double a = x[i];
		double b = x[i+1];
		double z1 = (a + b)/2 - (b-a)*sqrt(3)/6;
		double z2 = (a + b)/2 + (b-a)*sqrt(3)/6;
		result += func(z1)*(b-a)/2 + func(z2)*(b-a)/2;
		// cout<<"["<<a<<","<<b<<"] "<<"z1="<<z1<<", z2="<<z2<<", result="<<result<<endl;
	}
	return result;
}
int main(int argc, char const *argv[])
{
	auto f = [](int i, unsigned long nodes)->double{return interval.a + i*((interval.b-interval.a)/(nodes-1));};
	using namespace std::placeholders;
	auto  next = bind(f, _1, n);
	dvec x;
	makeNodeOfInterval(x, n, next);
	dvec x2;
	auto next2 = bind(f, _1, 2*n);
	makeNodeOfInterval(x2, 2*n, next2);
	// cout<<x<<endl;
	// cout<<x2<<endl;
	double S1 = integralSimpson(x);
	double S2 = integralSimpson(x2);
	double pogr = (S2 - S1);
	double I = 3.464101615;
	double p = (I - S1)/(I-S2);
	p = log2(p);
	cout<<"p="<<p<<endl;
	cout<<"Simpson's method for h:"<<setiosflags(ios::scientific)<<setprecision(6)<<S1<<endl;
	cout<<"Simpson's method for h/2:"<<S2<<endl;
	cout<<"Ih/2 - Ih / 2^4-1= "<<pogr<<endl;
	cout<<"I*="<<(2*S2 - S1)<<endl;
	cout<<"Gauss's method(n=2) :"<<integralGauss(x)<<endl;
	return 0;
}