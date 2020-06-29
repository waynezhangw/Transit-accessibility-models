#pragma once

#include<string>
#include<iostream>
#include<vector>
#include<fstream>
#include<map>


using namespace std;

class CountBusStopsNumber  //This class is for trial and can be ignored
{
public:
	CountBusStopsNumber(void);
	~CountBusStopsNumber(void);

	void readBusStops_Legs();          
	int makeMap();                     
	void readBusStops_shp();           
	int makeShpMap();                  
	void findStopsDiff();              

private:
	string busName;                   
	vector<string> Bus;               
	vector<string> shpBus;            

	map<string,int> BusStationsMap;             
	map<string,int> BusShpMap;                  

	map<int,string> ReBusStationsMap;           


};

