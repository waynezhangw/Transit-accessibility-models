#include "Streets.h"
#include<fstream>
#include<sstream>
#include<iostream>

using namespace std;
Streets::Streets(void)
{
	StartP=new Points();
	EndP=new Points();
	MidP=new Points();
}


Streets::~Streets(void)
{
	delete StartP;
	StartP=NULL;
	delete EndP;
	EndP=NULL;
	delete MidP;
	MidP=NULL;
}

void Streets::readStreets()
{
	Points* useConvert=new Points();      
	double Slength;                       
	int ID=0;                             
	int Stype;                            
	double SX,SY,EX,EY,MX,MY;             
	ifstream finBus("D:\\data\\深圳数据\\修剪数据1\\Streets_split.csv");    
	string line;
	ifstream &fin=finBus;
	int times=1;                      
	while(getline(fin,line))     
	{
		istringstream sin(line);   
		string field;
		int i=1;
		while (getline(sin,field,','))    
		{
			if(i==2)           
			{
				Stype=int(useConvert->convertStringToDouble(field));    
				i++;
				continue;
			}
			else if(i==3)
			{
				SX=useConvert->convertStringToDouble(field);
				i++;
				continue;
			}
			else if(i==4)
			{
				SY=useConvert->convertStringToDouble(field);
				i++;
				continue;
			}
			else if(i==5)
			{
				EX=useConvert->convertStringToDouble(field);
				i++;
				continue;
			}
			else if(i==6)
			{
				EY=useConvert->convertStringToDouble(field);
				i++;
				continue;
			}
			else if(i==7)
			{
				Slength=useConvert->convertStringToDouble(field);
				i++;
				continue;
			}
			else if(i==8)
			{
				MX=useConvert->convertStringToDouble(field);
				i++;
				continue;
			}
			else if(i==9)
			{
				MY=useConvert->convertStringToDouble(field);
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
		streetID.push_back(ID);
		streetType.push_back(Stype);
		StartP->set_pointX(SX);
		StartP->set_pointY(SY);
		EndP->set_pointX(EX);
		EndP->set_pointY(EY);
		MidP->set_pointX(MX);
		MidP->set_pointY(MY);
		streetLength.push_back(Slength);
		if(ID==times*50000)
		{
			times=times+1;
			cout<<ID<<endl;
		}
	}
	cout<<"read大概24万多完成了"<<endl;
	delete useConvert;                     
	useConvert=NULL;
}
int Streets::getStreetSize()
{
	return int(StartP->getStopSize());     
	 
}

int Streets::get_streetID(int index)
{
	return streetID[index];
}
int Streets::get_streetType(int index)
{
	return streetType[index];
}
double Streets::get_StartPx(int index)
{
	return StartP->get_pointX(index);
}
double Streets::get_StartPy(int index)
{
	return StartP->get_pointY(index);
}
double Streets::get_EndPx(int index)
{
	return EndP->get_pointX(index);
}
double Streets::get_EndPy(int index)
{
	return EndP->get_pointY(index);
}
double Streets::get_MidPx(int index)
{
	return MidP->get_pointX(index);
}
double Streets::get_MidPy(int index)
{
	return MidP->get_pointY(index);
}
double Streets::get_streetLength(int index)
{
	return streetLength[index];
}

void Streets::makeGraphPointMap()
{
	pair<map<twoCombinedKey,int>::iterator, bool> Insert_Pair;
	twoCombinedKey tempKey;                            
	int number=1;                                      
	for(unsigned int i=0;i<streetID.size();i++)
	{
		tempKey.key_X=StartP->get_pointX(i);            
		tempKey.key_Y=StartP->get_pointY(i);
		Insert_Pair=pointToID.insert(pair<twoCombinedKey,int>(tempKey,number));
		if(Insert_Pair.second==true)
		{
			number++;
		}
		tempKey.key_X=EndP->get_pointX(i);
		tempKey.key_Y=EndP->get_pointY(i);
		Insert_Pair=pointToID.insert(pair<twoCombinedKey,int>(tempKey,number));
		if(Insert_Pair.second==true)
		{
			number++;
		}
	}
	 
	 
	Node=pointToID.size();
}

int Streets::get_NodeSize()
{
	return Node;
}
int Streets::get_GraphNodeID(double x1,double x2)
{
	twoCombinedKey tempKey;
	tempKey.key_X=x1;                   
	tempKey.key_Y=x2;
	return pointToID[tempKey];
}

void Streets::makeNodeStreetIDMap()
{
	double combined;               
	twoCombinedKey tempKey; 
	int a1,a2;
	pair<map<double,int>::iterator,bool> Insert_Pair;
	for(unsigned int i=0;i<streetID.size();i++)
	{
		tempKey.key_X=StartP->get_pointX(i);            
		tempKey.key_Y=StartP->get_pointY(i);
		a1=pointToID[tempKey];
		tempKey.key_X=EndP->get_pointX(i);
		tempKey.key_Y=EndP->get_pointY(i);
		a2=pointToID[tempKey];
		combined=a1+a2/1000000.0;                       
		Insert_Pair=NodeIDToStreetID.insert(pair<double,int>(combined,streetID[i]));
		if(Insert_Pair.second==false)
		{
			cout<<"a1.a2这种形式的插入失败了"<<endl;
		}
		combined=a2+a1/1000000.0;                       
		Insert_Pair=NodeIDToStreetID.insert(pair<double,int>(combined,streetID[i]));
		if(Insert_Pair.second==false)
		{
			cout<<"a2.a1这种形式的插入失败了"<<endl;
		}
	}
	cout<<"全部插完了"<<endl;
}

int Streets::get_GraphStreetID(int id_1,int id_2)
{
	double temp=id_1+id_2/1000000.0;
	return NodeIDToStreetID[temp];
}

void Streets::makeDijkstra_arc()
{                            
	vector<int> tempNode;                             
	for(unsigned int i=0;i<pointToID.size()+1;i++)       
	{
		arc.push_back(tempNode);                     
	}
	twoCombinedKey tempKey;                          
	int a1,a2;										 
	for(unsigned int i=0;i<streetID.size();i++)       
	{
		tempKey.key_X=StartP->get_pointX(i);            
		tempKey.key_Y=StartP->get_pointY(i);
		a1=pointToID[tempKey];
		tempKey.key_X=EndP->get_pointX(i);
		tempKey.key_Y=EndP->get_pointY(i);
		a2=pointToID[tempKey];
		arc[a1].push_back(a2);                       
		arc[a2].push_back(a1);
	}
}

void Streets::get_arcDirection(int id,vector<int> &temp)
{
	temp=arc[id];
}