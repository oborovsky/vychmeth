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
	// double cur{first};
	// double operator++() 
	// {
	// 	return cur += m_step();
	// };
	// double operator*(){return cur;};
	// double (*m_step)() = {[]()->double {return 0.01;}};
	// //Interval() = default;
	// Interval(double (*step)()):m_step{step} {};
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
	return move(y);
}
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
				w *= a / (x[i] - x[j]) - x[j] / (x[i] - x[j]);
			}	
		}
		r += y[i]*w;
	}
	return r;
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
		dvec delts = opts["delts"];
		auto delta = max_element(begin(delts), end(delts));
		//cout<<"delta="<<*delta<<endl;
		os<<"x="<<opts["x"]<<";"<<endl;
		os<<"xh="<<opts["xh"]<<";"<<endl;
	    os<<"y="<<opts["y"]<<";"<<endl;
	    os<<"yy="<<opts["yy"]<<";"<<endl;
	    os<<"yp="<<opts["yp"]<<";"<<endl;
	    os<<"plot(xh,yy,'m--');"<<endl;
	    os<<"plot(xh,yp,'r');"<<endl;
	    os<<"plot(x,y,'*');"<<endl;
	    os<<"xgrid();"<<endl;
	    os<<"xtitle('delta="<<*delta<<"','X', 'Y');"<<endl;
	}
};

int main(int argc, char const *argv[])
{
	
	const double nodes = 5;
	const double h = 0.01;
	dvec x;
	Interval interval = {-2,2};
	auto func = [](double a)->double{return a*sin(a);};

	makeNodeOfInterval(x, interval, [&]()->double{return (interval.last-interval.first)/(nodes-1);});
	dvec&& y = makeResultOnNode(x, func);

	using namespace std::placeholders;
	auto lagrange = bind(polynome, _1, x, y);
	auto step = [&h]()->double{return h;};

	dvec xh;
	makeNodeOfInterval(xh, interval,step);
	dvec&& yp = makeResultOnNode(xh, lagrange);
	dvec&& yy = makeResultOnNode(xh, func);

	map<string, dvec> vvecs;
	vvecs["x"] = x;
	vvecs["xh"] = xh;
	vvecs["y"] = y;
	vvecs["yy"] = yy;
	vvecs["yp"] = yp;
    dvec delts;
    auto i = begin(yp);
    auto j = begin(yy);
    for(; i != end(yp) && j != end(yy) ; ++i, ++j) 
    {
    	double delta = abs(*i - *j);
    	// cout << delta<<',';
    	delts.push_back( delta );
    }
    // cout<<endl;
    vvecs["delts"] = delts;


	out(vvecs);

	return 0;
}