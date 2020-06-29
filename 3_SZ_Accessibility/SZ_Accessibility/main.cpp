#include<iostream>
#include<time.h>      
#include<cstdlib>     
#include<vector>

#include "CountBusStopsNumber.h"
#include "Grid.h"

using namespace std;

int main()
{
	clock_t start,end;
	start=clock();     
	 
	 
	 

	Grid* myGrid=new Grid();
	myGrid->run();
	

	delete myGrid;
	myGrid=NULL;
	

	end=clock();      
	cout<<"running time: "<<(double)(end-start)/CLOCKS_PER_SEC<<"s"<<endl;
	system("pause");
	return 0;
}