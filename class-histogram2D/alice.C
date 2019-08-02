#include <iostream>
#include <string>

#include "Histogram2D.hh"

using namespace std;

int main()
{
	cout<<"Hello "<<endl;

	Histogram2D h1("test",2, 1., 2.,10,-100,100);

	h1.Fill(1,2,100);
	h1.Show();


	return 1;
}
