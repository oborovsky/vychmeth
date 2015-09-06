#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;
using dvec = vector<double>;

struct Interval
{
	double first;
	double last;
};

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
void makeNodeOfInterval(dvec& x, Interval& interval, const F& step)
{
	for (double i = interval.first; i < interval.last; i += step()) 
	{
		x.push_back(i);
	} 
}

template<typename F>
dvec makeResultOnNode(dvec& x, const F& f)
{
	dvec y(x.size());
	transform (x.begin(), x.end(), y.begin(), f);
	return y;
}

int main(int argc, char const *argv[])
{
	ofstream os("task1.sce");
	const double nodes = 10;
	dvec x;
	Interval interval = {0,1};

	auto func = [](double a)->double{return sin(a);};

	makeNodeOfInterval(x, interval, [&]()->double{return (interval.last-interval.first)/nodes;});
	dvec y = makeResultOnNode(x, func);

	if (!os)
	{
		cout<<"невозможно создать файл"<<endl;
		return 0;
	}

	os<<"x="<<x<<";"<<endl;
	os<<"y="<<y<<";"<<endl;
	os<<"plot(x,y);"<<endl;
	os<<"xgrid();"<<endl;

	return 0;
}