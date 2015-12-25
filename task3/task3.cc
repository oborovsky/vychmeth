#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;
struct Interval
{
	double a;
	double b;
	double length() { return b - a;};
};
auto f = [](double x)->double {return (x*x - sin(x) -1);};
auto f1 = [](double x)->double {return (2*x - cos(x));};
const double E = 10e-10;
Interval interval = {1,2};
// auto f = [](double x)->double {return x*x*x + 3*x*x - 1;};
// Interval interval = {0,1};
// const double E = 5e-5;
// auto f = [](double x)->double {return x*x +x -2;};
// Interval interval = {0,3};
// const double E = 5e-5;

inline double sgn(double x) 
{
	if (x > 0) return 1;
	if (x < 0) return -1;
	return 0;
}

void bisection()
{
	double a = interval.a;
	double b = interval.b;
    double h = (b-a);
    double x = a + h/2;

	unsigned long n = log2(interval.length()/E) + 1;
	cout<<"bisection---------------------------------------------"<<endl;
	cout<<setiosflags(ios::scientific)<<setprecision(10)<<"n="<<n<<endl;
    // cout<<"x="<<x<<", h="<<h<<endl;
	for (unsigned long i = 0; i < n; i++)
	{
		x += sgn(f(a)) * sgn(f(x))*h/pow(2,i+2);
		//cout<<"x="<<x<<", h="<<h<<endl;
	}

	cout<<"x="<<x<<endl;
	cout<<"f(x)="<<f(x)<<endl;
	cout<<"E="<<E<<endl;
}
void methodNewton()
{	
	// double a = 1;
	double b = 1.5;
	double x = b;
	double m1 = 2 - cos(1);
	unsigned long n = 0;
	cout<<"Newton's method ---------------------------------------------------"<<endl;
	//cout<<"x="<<x<<endl;
	while(fabs(f(x))/m1 > E)
	{
	// for (unsigned long i = 0; i < n; i++)
	// {
		x -= f(x)/f1(x);
	n++;
		//cout<<"x="<<x<<endl;
	}
	cout<<setiosflags(ios::scientific)<<setprecision(10)<<"n="<<n<<endl;
	cout<<"x="<<x<<endl;
	cout<<"f(x)="<<f(x)<<endl;
	cout<<"E="<<E<<endl;

}
void methodChord()
{
	// double a = 1;
	double b = 1.5;
	double x0 = b;
	double x = 1;
	double m1 = 2 - cos(1);
	unsigned long n = 0;
	cout<<"method's Chord ---------------------------------------------------"<<endl;
	//cout<<"x="<<x<<endl;

	while(fabs(f(x))/m1 > E)
	{
		x -= (x-x0)*f(x)/(f(x)-f(x0));
		n++;
		//cout<<"x="<<x<<endl;
	}
	cout<<setiosflags(ios::scientific)<<setprecision(10)<<"n="<<n<<endl;
	cout<<"x="<<x<<endl;
	cout<<"f(x)="<<f(x)<<endl;
	cout<<"E="<<E<<endl;	
}
void methodSecant()
{
	// double a = 1;
	double b = 1.5;
	double x0 = b;
	double x = x0 - 0.001;
	double m1 = 2 - cos(1);
	unsigned long n = 0;
	cout<<"method's Secant ---------------------------------------------------"<<endl;
	//cout<<"x="<<x<<endl;

	while(fabs(f(x))/m1 > E)
	{
		 double tmp = x - (x-x0)*f(x)/(f(x)-f(x0));
		 x0 = x;
		 x = tmp;
		n++;
		//cout<<"x="<<x<<endl;
	}
	cout<<setiosflags(ios::scientific)<<setprecision(10)<<"n="<<n<<endl;
	cout<<"x="<<x<<endl;
	cout<<"f(x)="<<f(x)<<endl;
	cout<<"E="<<E<<endl;	
}
void iteration()
{
	// double a = 1;
	// double b = 1.5;
	double x0 = 1.5;
	double x = x0;
	double m1 = 2 - cos(1);
	double M1 = 3 -cos(1.5);
	double l = 2/(M1 + m1);
	// double q = (M1-m1)/(M1+m1);
	auto fi = [l](double x)->double{return (x - l*f(x));};

	unsigned long n = 0;
	cout<<"method of iteration ---------------------------------------------------"<<endl;
	do
	{ 
		x0 = x;  
		x = fi(x);
		n++;
	// cout<<"x="<<x<<endl;
	}while(fabs(x-x0)>E);
	cout<<setiosflags(ios::scientific)<<setprecision(10)<<"n="<<n<<endl;
	cout<<"x="<<x<<endl;
	cout<<"f(x)="<<f(x)<<endl;
	cout<<"E="<<E<<endl;	
}
void methodChebyshova()
{
	// double a = 1;
	auto f2 = [](double a)->double{return (2+sin(a));};
	double b = 1.4;
	double x = b;
	double m1 = 2 - cos(1);
	double M2 = 2 + sin(1.5);
	unsigned long n = 0;
	cout<<"Chebyshov's method ---------------------------------------------------"<<endl;
	cout<<setiosflags(ios::scientific)<<setprecision(10);
	do
	{
		x -= f(x)/f1(x) - f2(x)*pow(f(x),2)/(2*pow(f1(x),3));
	n++;
		// cout<<"x="<<x<<endl;
	} while(fabs(f(x)/m1 - M2*pow(f(x),2)/(2*pow(m1,3))) > E);
	cout<<setiosflags(ios::scientific)<<setprecision(10)<<"n="<<n<<endl;
	cout<<"x="<<x<<endl;
	cout<<"f(x)="<<f(x)<<endl;
	cout<<"E="<<E<<endl;
}
int main(int argc, char const *argv[])
{
	 bisection();
	 methodNewton();
     methodChord();
	 methodSecant();
	 iteration();
	 methodChebyshova();
	return 0;
}

