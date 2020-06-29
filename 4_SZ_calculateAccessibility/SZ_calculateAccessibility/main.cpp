#include<iostream>
#include<time.h>  
#include<cstdlib>  
#include<vector>
#include<string>

#include<fstream>
#include<sstream>
#include<iomanip>
#include "limits.h"

#include "Trip.h"
#include "District.h"
#include "Theory.h"

#define MY_PI 3.1415926535898

using namespace std;

int main()
{
	clock_t start,end;
	start=clock();
	cout<<"This is a program for calculating accessibility from district perspective!"<<endl<<endl;

	Theory* R0405=new Theory();
	R0405->run();
	delete R0405;
	R0405=NULL;

	end=clock();   
	cout<<"running time: "<<(double)(end-start)/CLOCKS_PER_SEC<<"s"<<endl;
	system("pause");
	return 0;
}