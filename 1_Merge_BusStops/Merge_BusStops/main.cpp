#include<iostream>
#include<time.h>     //clock_t
#include<cstdlib>    //system("pause")
#include<vector>
#include "KMeans.h"

//created time: 2018.06.27

using namespace std;

int main()
{
	clock_t start,end;
	start=clock();
	
	KMeans* tom=new KMeans();
	tom->run();

	delete tom;
	tom=NULL;

	end=clock();
	cout<<"running time: "<<(double)(end-start)/CLOCKS_PER_SEC<<"s"<<endl;
	system("pause");
	return 0;
}