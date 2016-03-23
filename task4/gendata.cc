#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <map>
#include <cmath>
#include <cstdlib>

using namespace std;
using counter = unsigned int;
struct func 
{
	double operator()(double a) const{return a;};
};
struct fsin:func
{
	double operator()(double a) const{return sin(a);};
};
struct fexp:func
{
	double operator()(double a) const{return exp(a);};

};
struct cub:func
{
	double operator()(double a) const{return pow(a,3);};

};
fsin ssin;
fexp eexp;
cub ccub;
// map<string,struct func&> ff;
// ff["sin"] = ssin;
counter n = 5;
const double pi = 3.14159265359;
double a = -2;
double b = 2;
string f = "sin";

int main(int argc, char const *argv[])
{
	string name = "spline_gen.txt";
	if(argc > 1)
	{
		name = string(argv[1]);
	}
	ofstream os(name);
	if (!os)
	{
		cout<<"невозможно создать файл"<<endl;
		exit(1);
	} 
	
	double h = (b-a)/n;
	// cout<<"h="<<h<<endl;
	for(double i = a; i <= b; i+= h)
	{
		if( i != a) os<<" ";
		os<<ccub(i);
	}
	os<<endl;
	os<<eexp(-2)<<endl<<eexp(2)<<endl;
	return 0;
}