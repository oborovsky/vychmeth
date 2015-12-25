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

const unsigned long n = 1000;

auto func = [](double a)->double {return sqrt(a);};
Interval interval = {0,3};
double I = 2*(pow(sqrt(interval.b),3) - pow(sqrt(interval.a),3))/3;
// auto func = [](double a)->double {return exp(a);};
// Interval interval = {-1,2};
// double I = exp(interval.b)-exp(interval.a);
// auto func = [](double a)->double{return a*sin(a);};
// Interval interval = {0,4};
// double I = sin(interval.b)-interval.b*cos(interval.b) - sin(interval.a) + interval.a*cos(interval.a);
// auto func = [](double a)->double {return 1/(1+a);};
// Interval interval = {0,1};
// double I = log(1+interval.b) - log(1 + interval.a);
// auto func = [](double a)->double {return a/(1+a*a);};
// Interval interval = {-1,1};
// double I = log(sqrt(1 + pow(interval.b,2))) - log(sqrt(1 + pow(interval.a,2)));

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
	double d = interval.length()/(length-1);

	for(unsigned long i = 0; i < length - 1 ; i++)
	{
		result += func((x[i]+x[i+1])*0.5) * d;
	}
	//result = result;
	return result;	
}
double integralGauss(dvec& x)
{
	double result = 0;
	unsigned long length = x.size();
	double x1 = -0.7745966692;
	double x3 = 0.7745966692;
	double x2 = 0.0;

	for (unsigned long i = 0; i < length - 1; i++)
	{
		double a = x[i];
		double b = x[i+1];
		double z1 = (a + b)/2 + (b-a)*x1/2;
		double z2 = (a + b)/2 + (b-a)*x2/2;
		double z3 = (a + b)/2 + (b-a)*x3/2;
		result += (func(z1)*5 + func(z2)*8 + func(z3)*5)*(b-a)/18;
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
	dvec x16;
	auto next16 = bind(f, _1, 16*n);
	makeNodeOfInterval(x16, 16*n, next16);

	double Rect1 = integralRectangle(x);
	double Rect2 = integralRectangle(x2);
	double Rect16 = integralRectangle(x16);
	double G = integralGauss(x);
	double pogrRect = abs((Rect2 - Rect1)/3);
	cout<<"Rectangle method for n="<<n<<" :"<<setiosflags(ios::scientific)<<setprecision(6)<<Rect1<<endl;
	cout<<"Rectangle method for n="<<2*n<<" :"<<Rect2<<endl;
	cout<<"Ih/2 - Ih / 2^2-1= "<<pogrRect<<endl;
	cout<<"I = "<<I<<endl;
	cout<<"I* = "<<(4*Rect2-Rect1)/3<<endl;
	cout<<"p="<<log2((I-Rect1)/(I-Rect2))<<endl;
	cout<<"experemental p="<<log2((Rect16 - Rect1)/(Rect16-Rect2))<<endl;
	cout<<"Gauss's method(n=3) :"<<G<<endl;
	return 0;
}