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
double integralSimpson(dvec& x)
{
	double result = func(x[0]);
	unsigned long length = x.size();

	for(unsigned long i = 1; i < length - 1 ; i += 2)
	{
		result += 4 * func(x[i]) + 2 * func(x[i+1]);
	}
	result += func(x[length-1]);
	result *= interval.length()/(3 * (length-1));
	return result;
}
double integralTrapeze(dvec& x)
{
	double result = func(x[0]);
	unsigned long length = x.size();

	for(unsigned long i = 1; i < length - 1 ; i++)
	{
		result += 2 * func(x[i]);
	}
	result += func(x[length-1]);
	result *= interval.length()/(2 * (length-1));
	return result;
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
	// double S1 = integralSimpson(x);
	// double S2 = integralSimpson(x2);
	// double Tr1 = integralTrapeze(x);
	// double Tr2 = integralTrapeze(x2);
	double Rect1 = integralRectangle(x);
	double Rect2 = integralRectangle(x2);
	double G = integralGauss(x);
	double I = 3.4641;
	// double pogrS = (S2 - S1)/15;
	// double pogrTr = (Tr2 - Tr1)/3;
	double pogrRect = (Rect2 - Rect1)/3;
	// cout<<"Simpson's method for n="<<n<<" :"<<setiosflags(ios::scientific)<<setprecision(6)<<S1<<endl;
	// cout<<"Simpson's method for n="<<2*n<<" :"<<S2<<endl;
	// cout<<"Ih/2 - Ih / 2^4-1= "<<pogrS<<endl;
	// cout<<"Trapeze method for n="<<n<<" :"<<setiosflags(ios::scientific)<<setprecision(6)<<Tr1<<endl;
	// cout<<"Trapeze method for n="<<2*n<<" :"<<Tr2<<endl;
	// cout<<"Ih/2 - Ih / 2^2-1= "<<pogrTr<<endl;
	cout<<"Rectangle method for n="<<n<<" :"<<setiosflags(ios::scientific)<<setprecision(6)<<Rect1<<endl;
	cout<<"Rectangle method for n="<<2*n<<" :"<<Rect2<<endl;
	cout<<"Ih/2 - Ih / 2^2-1= "<<pogrRect<<endl;
	cout<<"I* = "<<(4*Rect2-Rect1)/3<<endl;
	cout<<"p="<<log2((I-Rect1)/(I-Rect2))<<endl;
	// cout<<"I*="<<(2*S2 - S1)<<endl;
	cout<<"Gauss's method(n=2) :"<<G<<endl;
	return 0;
}