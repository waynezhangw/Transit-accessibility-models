#include "Points.h"
#include<fstream>
#include<sstream>
#include<string>
#include<iostream>

Points::Points(void)
{
}


Points::~Points(void)
{
}

void Points::readBusStop()
{
	string name;         
	int ID=0;            
	double X,Y;          
	ifstream finBus("D:\\data\\深圳数据\\修剪数据1\\merge_BusStation改进dbscan加地铁.csv");    
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
				name=field;    
				i++;
				continue;
			}
			else if(i==3)
			{
				X=convertStringToDouble(field);
				i++;
				continue;
			}
			else if(i==4)
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
		ID++;
		stopID.push_back(ID);
		stopName.push_back(name);
		this->X.push_back(X);
		this->Y.push_back(Y);
	}
	cout<<"read大概1万多完成了"<<endl;
}
double Points::convertStringToDouble(string str1)
{
	 
	double n1;
	const char* ch= str1.c_str();
	n1=atof(ch);                    

	return n1;
}

int Points::get_stopID(int index)
{
	return stopID[index];
}
string Points::get_stopName(int index)     
{
	return stopName[index];
}
double Points::get_pointX(int index)
{
	return X[index];
}
double Points::get_pointY(int index)
{
	return Y[index];
}
int Points::getStopSize()
{
	return int(X.size());                 
}
void Points::set_pointX(double X)
{
	this->X.push_back(X);
}
void Points::set_pointY(double Y)
{
	this->Y.push_back(Y);
}

void Points::set_nearDis(double Dis)
{
	nearestDis.push_back(Dis);
}
void Points::set_nearX(double X)
{
	nearestX.push_back(X);
}
void Points::set_nearY(double Y)
{
	nearestY.push_back(Y);
}
double Points::get_nearDis(int index)
{
	return nearestDis[index];
}
double Points::get_nearX(int index)
{
	return nearestX[index];
}
double Points::get_nearY(int index)
{
	return nearestY[index];
}