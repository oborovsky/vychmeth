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

const double nodes = 10;
const double h = 0.01;
const double pi = 3.14159265;

// auto func = [](double a)->double{return a*sin(a);};
auto func = [](double a)->double{return a*abs(a);};
Interval interval = {-2,2};
auto step = [](int i)->double{return h;};


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
void makeNodeOfInterval(dvec& x, const F& next)
{
	for (int i = 0; i < nodes; i++) 
	{
		x.push_back(next(i));
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
void out(map<string, dvec>& opts, string title)
{
	string name = title + ".sce";
	ofstream os(name);

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
	    os<<"xtitle('"<<title<<" delta="<<*delta<<"','X', 'Y');"<<endl;
	}
};

void makeGraphic(string name, dvec& x)
{
	
	dvec&& y = makeResultOnNode(x, func);

	using namespace std::placeholders;
	auto lagrange = bind(polynome, _1, x, y);
	

	dvec xh;
	for(double a = interval.first; a <= interval.last; a += h)
	{
		xh.push_back(a);
	}
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

	out(vvecs, name);
};

int main(int argc, char const *argv[])
{
	dvec x;
	auto norm = [](int i)->double{return interval.first + i*((interval.last-interval.first)/(nodes-1));};
	makeNodeOfInterval(x, norm);
	makeGraphic("norm", x);

	auto cheb = [](int i)->double
	{
		double a = interval.first;
		double b = interval.last;
		double yi = (a + b)/2 - (b - a) * cos((2*i+1)*pi/(2*nodes))/2;
		return yi; 
	};
	dvec x2;
	makeNodeOfInterval(x2, cheb);
	makeGraphic("cheb", x2);

	return 0;
}