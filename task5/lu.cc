#include <iostream>
#include <cstdlib>
#include "matrix.h"
#include <vector>

using namespace std;

int main(int argc, char const *argv[])
{
	try
	{
		matrix<3> m("1,0,0,0,1,0,0,0,1") ;
		matrix<3> m2("1,1,1,2,2,2,3,3,3");
		// m.set(0,0,1);
		// m.set(0,1,0);
		// m.set(1,0,0);
		// m.set(1,1,1);
		// m[0][0] = 1;
		// m[0][1] = 0;
		// m[1][0] = 0;
		// m[1][1] = 1;
		// m2[0][0] = 0;
		// m2[0][1] = 1;
		// m2[1][0] = 1;
		// m2[1][1] = 0;
		// mm = m + m2;
		 matrix<3> m3 = m.makeR(0,1,2);
		 cout<<m3<<endl;
		 cout<<m<<endl;
		 cout<<m3*m<<endl;
		 cout<<m2*m3<<endl;
		 double** arr = m.toArray();
		 matrix<3> m4(arr);
		 m4[0][0] = 4;
		 cout<<m4<<endl;

	}
	catch(string e)
	{
		cout<<e<<endl;
	}
	catch(char* e)
	{
		cout<<e<<endl;
	}
	catch(...)
	{
		cout<<"error"<<endl;
	}
	return 0;
}