#include "CountBusStopsNumber.h"
#include<fstream>
#include<sstream>


CountBusStopsNumber::CountBusStopsNumber(void)
{
	
}


CountBusStopsNumber::~CountBusStopsNumber(void)
{
}

void CountBusStopsNumber::readBusStops_Legs()
{
	 
	 
	ifstream finBus("D:\\data\\深圳数据\\stationCSV\\20170406-Trip_0413简体中文.csv");
	 
	string line;
	int times=1;
	int number=0;
	ifstream &fin=finBus;
	while(getline(fin,line))     
	{
		istringstream sin(line);   
		string field;
		int i=1;
		while (getline(sin,field,','))    
		{
			if(i==3)           
			{
				busName=field;    
				i++;
				break;
			}	
			else
			{
				i++;
				continue;
			}	
		}
		Bus.push_back(busName);
		number++;
		if(number==times*100000)
		{
			cout<<number<<endl;
			times++;
		}
	}
	makeMap();
	readBusStops_shp();
}

int CountBusStopsNumber::makeMap()
{
	pair<map<string,int>::iterator, bool> Insert_Pair;    
	pair<map<int,string>::iterator, bool> Insert_PairTemp;    
	int j=0;                                                
	for(unsigned int i=0;i<Bus.size();i++,j++)    
	{
		Insert_Pair=BusStationsMap.insert(pair<string,int>(Bus[i],j+1));    
		if(Insert_Pair.second==false)
		{
			j--;
		}
		else
		{
			Insert_PairTemp=ReBusStationsMap.insert(pair<int,string>(j,Bus[i]));
		}
	}
	cout<<BusStationsMap.size()<<"   读的灰灰合并的那个的个数"<<endl;
	return 0;
}

void CountBusStopsNumber::readBusStops_shp()
{
	ifstream finBus("D:\\data\\深圳数据\\修剪数据\\busStopDbf.csv");    
	string line;
	ifstream &fin=finBus;
	while(getline(fin,line))     
	{
		istringstream sin(line);   
		string field;
		int i=1;
		while (getline(sin,field,','))    
		{
			if(i==1)           
			{
				busName=field;    
				i++;
				break;
			}	
			else
			{
				i++;
				continue;
			}	
		}
		shpBus.push_back(busName);        
	}
	makeShpMap();
	findStopsDiff();
}

int CountBusStopsNumber::makeShpMap()
{
	pair<map<string,int>::iterator, bool> Insert_Pair;    
	int j=0;                                                
	for(unsigned int i=0;i<shpBus.size();i++,j++)    
	{
		Insert_Pair=BusShpMap.insert(pair<string,int>(shpBus[i],j+1));    
		if(Insert_Pair.second==false)
		{
			j--;
		}
	}
	cout<<BusShpMap.size()<<"   读的shp里的个数"<<endl;
	return 0;
}

void CountBusStopsNumber::findStopsDiff()
{
	ofstream outfile;
	outfile.open("D:\\data\\深圳数据\\修剪数据\\diff_BusStation.csv");
	for(unsigned int i=0;i<ReBusStationsMap.size();i++)
	{
		if(BusShpMap.count(ReBusStationsMap[i])==0)
		{
			outfile<<ReBusStationsMap[i]<<","<<i<<endl;
		}
	}
	outfile.close();
}