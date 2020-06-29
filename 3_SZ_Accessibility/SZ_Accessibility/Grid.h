#pragma once

#include<vector>
#include<map>
#include"Streets.h"
#include"Points.h"

using namespace std;

struct Dis
{  
	double cost;          
	bool visit;
	Dis()                 
	{
		cost=9999.0;
		visit=false;
	}
};

class Grid  //This class is for calculating and merging grids based on the relation between street network and station (GOCs)
{
public:
	Grid(void);
	~Grid(void);

	double getGridPos(double x,double y);								 
	void makeGridStreetMap();											 
	bool putIn(int ID,vector<int> &vec);								 
	void makeStreetStopMap();											 
	void findAroundGrid(double pos,vector<double> &vec,int Asize);		 
	int round_double(double temp);										 
	bool whetherTheSameStop(string s1,string s2);						 
	int getNearestStreet(int stopID,vector<double> &vec);				 
	int getNearestTwoStreet(int stopID,vector<double> &vec,int pos);     
	double pointToSegDis(double Cx,double Cy,double X1,double Y1,double X2,double Y2,double &VX,double &VY); 
	void makeFileOfProjectedPoint();									 
	

	void readWaitingArray();									     
	void makeGridNearestStop();									     
	void getNearestStreetForGrid(double GX,double GY,vector<double> &vec);   
	void getGridCenterXY(double combined,double &X,double &Y);       
	void makeWaitingDis(vector<double> &vec,int nearIndex);    
	void dijkstra(map<int,int> checkHM,vector<int> InsertN);         
	void useWaitingDis(vector<double> &vec,map<int,int> checkHM,int nearIndex2);  
	void makeFileOfGridNearestStop();                                
	void makeFileOFStopNearestGrid();                                


	void mergeGrid();                                                           
	double getMostSimilarGrid(double center,vector<double> vec);                
	void makeGridPosToGirdID();                                                 
	double getABdis(double A,double B);                                         
	double getSimilar(double AB,int vecO,int vecS);                             
	void makeFileOfGridClassLabel(int *gridClass,int classSize);                
	void seeClassCountDistribute(int *gridClass,int gridSize,int classCount);   

	 
	void betterMakeGridNearestStop();                                           

	 
	void makeFileOFDistrictOwnStops(int *gridClass, int classCount);             

	void run();													 

private:
	 

	double OriginX;                         
	double OriginY;                         

	Streets* myStreets;                     
	Points* myPoints;                       

	map<double,vector<int>> gridStreet;     
	map<int,vector<int>> streetStop;         

	map<double,int> gridID;                 

	int pOnSegment;                         
	double maxBusWalkingDis;                
	double maxSubwayWalkingDis;             
	int busOrSubwayDivide;                  

	int tempIndicate;

	 
	 
	 
	 
	 
	 
	vector<int> waitingRow;						 
	vector<int> waitingColumn;					 
	vector<vector<int>> gridNearestStop;		 
	vector<int> temp_gridNearestStop;			 
	vector<vector<double>> gridNearestStopDis;   
	vector<double> temp_gridNearestStopDis;	     
	Dis *waitingDis;							 
	int waitingDisSize;							 

	vector<int> nearGridStreetID;                      
	vector<double> nearGridStreetDis;                  
	vector<double> nearGridStreetX;                    
	vector<double> nearGridStreetY;                    

	 
	 

	 
	vector<vector<int>> stopNearestGrid;                  
	vector<vector<double>> stopNearestGridDis;            

};

