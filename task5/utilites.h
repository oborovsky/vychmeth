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
	ifstream is(name);
	if(!is) 
	{
		cout<<"невозможно открыть файл"<<endl;
		exit(1);
	}
	counter n = 0;
	is>>n;

	for (counter i = 0; i < n; i++)
	{
		double r;
		is>>r;
		x.push_back(r);
	}

	for (counter i = 0; i < n; i++)
	{
		double r;
		is>>r;
		y.push_back(r);
	}
	
	is>>k;
    string str = "";
    is>>str;
    if( str != "") outfunc = str;
    str = "";
    while(is.good())
    {
    	is>>str;
	    if( str != "") outfunc += "\n" + str;
	    str = "";
    }
};
void out(dvec& c,dvec& x,dvec& y)
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
	os<<setiosflags(ios::scientific)<<setprecision(10)<<"y="<<y<<";"<<endl;
	os<<"p=poly("<<c<<",'k','c');"<<endl;
	if( outfunc != "") os<<outfunc<<endl;
	   // os<<"plot(x,y,'*');"<<endl;
	os<<"plot(x,y,'b*');"<<endl;
    os<<"xgrid();"<<endl;
    os<<"xtitle('"<<title<<"','X', 'Y');"<<endl;

}
#endif