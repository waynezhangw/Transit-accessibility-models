#include "BusPoint.h"
#include<fstream>
#include<sstream>
#include<string>
#include<iostream>

using namespace std;
BusPoint::BusPoint(void)
{
}


BusPoint::~BusPoint(void)
{
}

void BusPoint::readBusStop()
{
	string name;        //��վ�����ֵ��м����
	string lineN;        //��վ�����ڵ���·���м����
	double X,Y;         //��������м����
	ifstream finBus("..\\data\\busstops.csv");       //����δ�ϲ���վ������
	string line;
	ifstream &fin=finBus;
	while(getline(fin,line))    //һ��һ�еĶ� 
	{
		istringstream sin(line);   
		string field;
		int i=1;
		while (getline(sin,field,','))  
		{
			if(i==2)          //���ƶ���һ��
			{
				name=field;    
				i++;
				continue;
			}
			else if(i==3)
			{
				lineN=field;    
				i++;
				continue;
			}
			else if(i==4)
			{
				X=convertStringToDouble(field);
				i++;
				continue;
			}
			else if(i==5)
			{
				Y=convertStringToDouble(field);
				i++;
				break;
			}
			else
			{
				i++;
				continue;
			}	
		}
		stopName.push_back(name);
		lineName.push_back(lineN);
		stopX.push_back(X);
		stopY.push_back(Y);
	}
	cout<<"read more than 40 thousand finished!"<<endl;
}

double BusPoint::convertStringToDouble(string str1)
{
	double n1;
	const char* ch= str1.c_str();
	n1=atof(ch); 
	return n1;
}

string BusPoint::get_stopName(int index)
{
	return stopName[index];
}
string BusPoint::get_stopLine(int index)
{
	return lineName[index];
}
double BusPoint::get_stopX(int index)
{
	return stopX[index];
}
double BusPoint::get_stopY(int index)
{
	return stopY[index];
}
int BusPoint::getStopSize()
{
	return int(stopX.size());          //stopX.size()������unsigned�ģ�����Ҫ����һ��
}

void BusPoint::add_stopName(string str1)
{
	stopName.push_back(str1);
}
void BusPoint::add_lineName(string str1)
{
	lineName.push_back(str1);
}
void BusPoint::add_stopX(double X)
{
	stopX.push_back(X);
}
void BusPoint::add_stopY(double Y)
{
	stopY.push_back(Y);
}
void BusPoint::delete_stopX(int index)
{
	stopX.erase(stopX.begin()+index);
}
void BusPoint::delete_stopY(int index)
{
	stopY.erase(stopY.begin()+index);
}
