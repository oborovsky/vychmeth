#include <iostream>
#include <cmath>


using namespace std;
using dvec = vector<double>;
struct Interval
{
	double first;
	double last;
};

const int n = 10;

auto func = [](double a)->double {return sqrt(a);};
Intervak interval = {0,3};

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

int main(int argc, char const *argv[])
{
	/* code */
	return 0;
}