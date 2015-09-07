#include <map>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include <functional>

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
	for (double i = interval.first; i <= interval.last; i += step()) 
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
void out(map<string, dvec>& opts)
{
	ofstream os("task1.sce");

	if (opts.size()) 
	{
		if (!os)
		{
			cout<<"невозможно создать файл"<<endl;
			exit(1);
		}
	
		os<<"x="<<opts["x"]<<";"<<endl;
		os<<"xh="<<opts["xh"]<<";"<<endl;
	    os<<"y="<<opts["y"]<<";"<<endl;
	    os<<"yy="<<opts["yy"]<<";"<<endl;
	    os<<"yp="<<opts["yp"]<<";"<<endl;
	    os<<"plot(x,y,xh,yp,xh,yy);"<<endl;
	    //os<<"plot(x,yp);"<<endl;
	    os<<"xgrid();"<<endl;
	}
};
double polynome(double a, dvec& x, dvec& y)
{
		double r = 0;
		for (unsigned long i = 0; i < y.size();i++)
		{
			double w = 1;
			for (unsigned long j = 0; j < x.size(); j++)
			{
				if( j != i) 
				{
					//if( a == x[j]) continue;
					w *= a / (x[i] - x[j]) - x[j] / (x[i] - x[j]);
				}	
			}
			r += y[i]*w;
		}
		return r;
}

int main(int argc, char const *argv[])
{
	
	const double nodes = 10;
	const double h = 0.01;
	dvec x;
	Interval interval = {-2,2};
	auto func = [](double a)->double{return a*sin(a);};

	makeNodeOfInterval(x, interval, [&]()->double{return (interval.last-interval.first)/nodes;});
	dvec&& y = makeResultOnNode(x, func);

	using namespace std::placeholders;
	auto ff = bind(polynome, _1, x, y);
	auto step = [&h]()->double{return h;};

	dvec xh;
	makeNodeOfInterval(xh, interval,step);
	dvec&& yp = makeResultOnNode(xh, ff);
	dvec&& yy = makeResultOnNode(xh, func);

	map<string, dvec> vvecs;
	vvecs["x"] = x;
	vvecs["xh"] = xh;
	vvecs["y"] = y;
	vvecs["yy"] = yy;
	vvecs["yp"] = yp;

	out(vvecs);

	return 0;
}