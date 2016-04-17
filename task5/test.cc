#include <cstdlib>
#include <iostream>
#include <iomanip>

using namespace std;

int main(int argc, char const *argv[])
{
	int r  = 6;
	int c = 6;
	double** arr = new double*[r];
	for (int i = 0; i < r; ++i)
	{
		arr[i] = new double[c];
	}
	for (int i = 0; i < r; ++i)
	{
		for (int j = 0; j < c; ++j)
		{
			arr[i][j] = i*j;
		}
	}
	for (int i = 0; i < r; ++i)
	{
		for (int j = 0; j < c; ++j)
		{
			cout<<setw(4)<<arr[i][j]<<" ";
			/* code */
		}
		cout<<endl;
	}
	return 0;
}