#ifndef UTILITES_H
#define UTILITES_H 1

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>

using namespace std;
using dvec=vector<double>;
using counter = unsigned int;
string outfunc = "";
dvec result;
string name = "msq.txt";


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
void loadData(dvec& x, dvec& y, int& k)
{
	// string name = "msq.txt";
	ifstream is(name);
	if(!is) 
	{
		cout<<"невозможно открыть файл"<<endl;
		exit(1);
	}
	double a, b;
	is>>a;
	// cout<<"a="<<a<<endl;
	is>>b;
	// cout<<"b="<<b<<endl;
	counter n;
	is>>n;
	// cout<<"n="<<n<<endl;
	double h = (b - a)/ (n-1);
	for (counter i = 0; i < n-1; i++)
	{
		x.push_back(a + i*h);
	}
	x.push_back(b);
	 // cout<<"x="<<x<<endl;
	for (counter i = 0; i < n; i++)
	{
		double r;
		is>>r;
		y.push_back(r);
	}
	 // cout<<"y="<<y<<endl;
	is>>k;
    // cout<<"l0="<<l0<<endl<<"ln="<<ln<<endl;
    string str = "";
    is>>str;
    // cout<<str<<endl;
    if( str != "") outfunc = str;
   
    while(is.good())
    {
    	double r=0;
    	is>>r;
    	result.push_back(r);
    }
	// cout<<"x="<<result<<endl;
}
#endif