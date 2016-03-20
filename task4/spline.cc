#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cmath>
#include <fstream>
#include <string>
#include <map>
#include <functional>
#include <cstdlib>
#include <exception>

using namespace std;
using dvec=vector<double>;
using matrix = vector<dvec>;
using counter = unsigned int;
string name = "spline.txt";
string outfunc = "";

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
ostream& operator<< (ostream &os, matrix& m)
{
	dvec a = m[0], b = m[1], c = m[2];
	os<<"a="<<a<<endl;
	os<<"b="<<b<<endl;
	os<<"c="<<c<<endl;
	
	return os;
}
dvec makeH(dvec& x)
{
	dvec h(x.size());
	h[0] = 0;
	for(counter i = 1; i < x.size(); i++)
	{
		h[i]= x[i] - x[i-1];
	}
	h.push_back(0);
	return h;
}
dvec makeB(dvec& y, dvec& h, double l0, double ln)
{
	dvec b;
	const counter n = y.size();
	double r = 0;
	counter i = 0;

	for (; i < n - 1; i++)
	{
			switch(i)
		{
			case 0: r = 6*(y[i+1] - y[i])/h[i+1] - 6*l0; break;
			default: r  = 6*(y[i+1] - y[i])/h[i+1] - 6*(y[i] - y[i-1])/h[i];
	 	}
		b.push_back(r);
	}
	i--;
	r = 6*ln - 6*(y[i+1] - y[i])/h[i+1];
	b.push_back(r);
	return b;

}
matrix makeMatrix(dvec& h)
{
	matrix m;
	// m[0] = ai, m[1]= bi, m[2]=ci;s
	counter n = h.size();
	dvec a,b,c;

	for (counter i = 0; i < n-1; i++)
	{
		a.push_back(h[i]);
		b.push_back(2*(h[i] + h[i+1]));
		c.push_back(h[i+1]);
	}
	m.push_back(a);
	m.push_back(b);
	m.push_back(c);
	return m;
}
dvec shuttle(matrix &m, dvec& d)
{
	dvec l(d.size() + 1);
	dvec e(l.size());
	dvec n(l.size());
    //cout<<m.size()<<endl;

	fill(begin(l), begin(l) + m.size() + 1, 0);

	dvec a = m[0];
	dvec b = m[1];
	dvec c = m[2];
	//cout<<a<<endl<<b<<endl<<c<<endl;
	// cout<<e<<endl<<n<<endl;

	for( counter i = 0; i < l.size() -1; i++)
	{
		double k = (a[i]*e[i] + b[i]);
		e[i+1] = -c[i] / k;
		n[i+1] = (d[i] - a[i]*n[i]) / k;
	}
	cout<<"e="<<e<<endl<<"n="<<n<<endl;
	for (counter i = l.size()-1; i > 0; i--)
	{
		l[i-1] = e[i]*l[i] + n[i];
	}
	l.pop_back();
	return l;
}
double Spline(dvec& x, dvec&y, dvec& h, dvec& l, double a)
{
	counter i = 1;
	counter n = x.size();

	if( a < x[0] || x[n-1] < a) throw "out of range";

	for(; i < n; i++)
	{
		if(x[i] > a ) break;
	}
	if ( i == n) i--;

	// cout<<"i="<<i<<endl;
	double r = (l[i-1]*pow((x[i]-a),3) - l[i-1]*(x[i]-a)*h[i]*h[i])/(6*h[i]) + \
	(l[i]*pow(a-x[i-1],3) - l[i]*(a-x[i-1])*h[i]*h[i])/(6*h[i]) +\
	y[i-1]*(x[i]-a)/h[i] + y[i]*(a-x[i-1])/h[i];
	return r;
}
void loadData(dvec& x, dvec& y, double& l0, double& ln)
{
	//string name = "spline1.txt";
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
	double h = (b - a)/ (n);
	for (counter i = 0; i < n; i++)
	{
		x.push_back(a + i*h);
	}
	x.push_back(b);
	 cout<<"x="<<x<<endl;
	for (counter i = 0; i < n + 1; i++)
	{
		double r;
		is>>r;
		y.push_back(r);
	}
	 cout<<"y="<<y<<endl;
	is>>l0;
	is>>ln;
    // cout<<"l0="<<l0<<endl<<"ln="<<ln<<endl;
    string str = "";
    is>>str;
    cout<<str<<endl;
    if( str != "") outfunc = str;

}
// находим значение фукции f по точкам
template<typename F>
dvec makeResultOnNode(dvec& x, const F& f)
{
	dvec y(x.size());
	transform (x.begin(), x.end(), y.begin(), f);
	return move(y);
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
		
		//cout<<"delta="<<*delta<<endl;
		os<<setiosflags(ios::scientific)<<setprecision(10);
		os<<setiosflags(ios::scientific)<<setprecision(10)<<"xh="<<opts["xh"]<<";"<<endl;
	    os<<setiosflags(ios::scientific)<<setprecision(10)<<"yy="<<opts["yy"]<<";"<<endl;
	    os<<"plot(xh,yy,'r');"<<endl;
	    if( outfunc != "") os<<outfunc<<endl;
	   // os<<"plot(x,y,'*');"<<endl;
	    os<<"xgrid();"<<endl;
	    os<<"xtitle('"<<title<<"','X', 'Y');"<<endl;
	}
};
void makeGraphic(string name, dvec& x, dvec& y, dvec& h, dvec& l)
{
	const double hh = 0.01;
	dvec xh;
	for(double a = x[0]; a <= x[x.size()-1]; a += hh)
	{
		xh.push_back(a);
	};
	xh.push_back(x[x.size()-1]);
	auto func = [&x,&y,&h,&l](double aa)->double{return Spline(x, y, h, l, aa);};
	dvec&& yy = makeResultOnNode(xh, func);

	map<string, dvec> vvecs;
	vvecs["x"] = x;
	vvecs["y"] = y;
	vvecs["xh"] = xh;
    vvecs["yy"] = yy;
    // cout<<endl;
	out(vvecs, name);
};

int main(int argc, char const *argv[])
{
	if (argc > 1) 
	{
		name = string(argv[1]);
		cout<<name<<endl;
	}
	dvec x;
	dvec y;
	double l0=0,ln=0;

	loadData(x, y, l0, ln);
    cout<<"l0="<<l0<<",ln="<<ln<<endl;
	dvec&& h = makeH(x);
	cout<<"h="<<h<<endl;
	matrix&& m = makeMatrix(h);
	 cout<<"m="<<endl<<m<<endl;
	dvec&& d = makeB(y, h, l0, ln);// {12, 23/2};
	 cout<<"d="<<d<<endl;

	dvec&& l = shuttle(m, d);
	cout<<"l="<<l<<endl;
	try {
		 makeGraphic("spline",x,y,h,l);
		string a = ""; 
		do{
			cout<<"input "<<x[0]<<"<x<"<<x[x.size()-1]<<":";
			cin>>a;
			//if ( a != "e") cout<<endl<<"S("<<a<<")="<<Spline(x, y, h, l, stod(a))<<endl;
			if ( a != "e") cout<<endl<<"S("<<a<<")="<<Spline(x, y, h, l, atof(a.c_str()))<<endl;
		} while (a != "e");
	}
	catch(const char* err)
	{
		cout<<err<<endl;
	}
	catch(exception &e)
	{
		cout<<"error:"<<e.what()<<endl;
	}
	return 0;
}