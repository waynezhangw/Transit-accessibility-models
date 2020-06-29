#include<iostream>
#include<time.h>     //clock_t
#include<cstdlib>    //system("pause")
#include<vector>
#include<string>


#include "Trip.h"


#define MY_PI 3.1415926535898

using namespace std;

int main()
{
	clock_t start,end;
	start=clock();
	cout<<"This is a program for calculating accessibility from district perspective!"<<endl<<endl;

	Trip* R0405=new Trip();
	R0405->run();
	delete R0405;
	R0405=NULL;

	end=clock(); 
	cout<<"running time: "<<(double)(end-start)/CLOCKS_PER_SEC<<"s"<<endl;
	system("pause");
	return 0;
}