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
	// double a, b;
//	is>>a;
	// cout<<"a="<<a<<endl;
	// is>>b;
	// cout<<"b="<<b<<endl;
	counter n = 0;
	is>>n;
	// cout<<"n="<<n<<endl;
	// double h = (b - a)/ (n-1);
	for (counter i = 0; i < n; i++)
	{
		double r;
		is>>r;
		x.push_back(r);
	}
	// for (counter i = 0; i < n-1; i++)
	// {
	// 	x.push_back(a + i*h);
	// }
	// x.push_back(b);
	 // cout<<"x="<<x<<endl;
	for (counter i = 0; i < n; i++)
	{
		double r;
		is>>r;
		y.push_back(r);
	}
	 // cout<<"y="<<y<<endl;
	is>>k;
    string str = "";
    is>>str;
    // cout<<str<<endl;
    if( str != "") outfunc = str;
    str = "";
    while(is.good())
    {
    	is>>str;
	    if( str != "") outfunc += "\n" + str;
	    str = "";
    }
	// cout<<"x="<<result<<endl;
};
void out(dvec& c,dvec& x)
{
	string title = "lu";
	string name = "lu";
	name = name + ".sce";
	ofstream os(name);
	if (!os)
	{
		cout<<"невозможно создать файл"<<endl;
		exit(1);
	}
	os<<setiosflags(ios::scientific)<<setprecision(10)<<"x="<<x<<";"<<endl;
	os<<"p=poly("<<c<<",'k','c');"<<endl;
	if( outfunc != "") os<<outfunc<<endl;
	   // os<<"plot(x,y,'*');"<<endl;
	    os<<"xgrid();"<<endl;
	    os<<"xtitle('"<<title<<"','X', 'Y');"<<endl;

}
#endif