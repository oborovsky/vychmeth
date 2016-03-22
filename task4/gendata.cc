#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <map>
#include <cmath>

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
fsin ssin;
fexp eexp;
// map<string,struct func&> ff;
// ff["sin"] = ssin;
counter n = 4;
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
		os<<eexp(i);
	}
	os<<endl;
	os<<eexp(-2)<<endl<<eexp(2)<<endl;
	return 0;
}