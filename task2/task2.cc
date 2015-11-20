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

const unsigned long n = 4;

auto func = [](double a)->double {return sqrt(a);};
Interval interval = {0,3};
// auto func = [](double a)->double{return a*sin(a);};
// Interval interval = {0,4};
// auto func = [](double a)->double {return 1/(1+a);};
// Interval interval = {0,1};
// auto func = [](double a)->double {return a/(1+a*a);};
// Interval interval = {-1,1};

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

double integralRectangle(dvec& x)
{
	double result = 0;
	unsigned long length = x.size();

	for(unsigned long i = 0; i < length - 1 ; i++)
	{
		result += func((x[i] + x[i+1])/2);
	}
	result *= interval.length()/(length-1);
	return result;	
}
double integralGauss(dvec& x)
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
	double Rect1 = integralRectangle(x);
	double Rect2 = integralRectangle(x2);
	double G = integralGauss(x);
	double I = 3.4641;
	double pogrRect = (Rect2 - Rect1)/3;
	cout<<"Rectangle method for n="<<n<<" :"<<setiosflags(ios::scientific)<<setprecision(6)<<Rect1<<endl;
	cout<<"Rectangle method for n="<<2*n<<" :"<<Rect2<<endl;
	cout<<"Ih/2 - Ih / 2^2-1= "<<pogrRect<<endl;
	cout<<"I* = "<<(4*Rect2-Rect1)/3<<endl;
	cout<<"p="<<log2((I-Rect1)/(I-Rect2))<<endl;
	cout<<"Gauss's method(n=2) :"<<G<<endl;
	return 0;
}