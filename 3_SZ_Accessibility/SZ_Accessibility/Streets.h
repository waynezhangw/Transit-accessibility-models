#pragma once

#include<vector>
#include"Points.h"
#include<map>

using namespace std;

struct twoCombinedKey           
{
	double key_X;               
	double key_Y;
	 
	bool operator<(twoCombinedKey const& _A)const             
	{
		if(key_X<_A.key_X)
		{
			return true;
		}
		if(key_X==_A.key_X) 
		{
			if(key_Y<_A.key_Y)
			{
				return true;
			}
		}
		return false;
	}
	
};


class Streets      //This class is for storeing, indexing and calculating distance on the street
{
public:
	Streets(void);
	~Streets(void);

	void readStreets();                      
	int getStreetSize();                     
	int get_streetID(int index);             
	int get_streetType(int index);           
	double get_StartPx(int index);           
	double get_StartPy(int index);
	double get_EndPx(int index);
	double get_EndPy(int index);
	double get_MidPx(int index);
	double get_MidPy(int index);
	double get_streetLength(int index);          

	void makeGraphPointMap();                     
	int get_NodeSize();                          
	int get_GraphNodeID(double x1,double x2);    
	void makeNodeStreetIDMap();                  
	int get_GraphStreetID(int id_1,int id_2);    
	void makeDijkstra_arc();                     
	void get_arcDirection(int id,vector<int> &);  


private:
	vector<int> streetID;                    
	vector<int> streetType;                  
	Points* StartP;                          
	Points* EndP;                            
	Points* MidP;                            
	vector<double> streetLength;             

	map<twoCombinedKey,int> pointToID;       
	int Node;                                
	map<double,int> NodeIDToStreetID;        
	vector<vector<int>> arc;                 
};

