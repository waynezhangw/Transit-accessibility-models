#pragma once

#include<vector>
#include<map>
#include<set>

#include "Trip.h"

using std::string;
using std::vector;
using std::map;
using std::set;

class District    //This is class is for calculating positive accessibility,including attractiveness calculation, POI sorting, etc.
{
public:
	District(void);
	~District(void);
	 
	void readGridClassLabel();                                       
	void readWaitingArray();									     
	void makeGridRCtoClassMap();                                     
	void initializeClassArrive();                                    
	void countDistrictAttraction();                                  
	void makeFileOfDistrictAttraction();					         
	void sortAttraction();                                           
	void makeFileOfPOI();                                            
	void makePOIMap();                                               
	void calculateAccess();                                          
	void makeFileOfAccess();                                         

	void makeClassOwnTripID();                                       
	void calculateAccessByClass();                                   

	void makeClassOwnGridID();                                       
	void getClassCenterXY(int index,double &X,double &Y);            
	void getGridCenterXY(double combined,double &X,double &Y);       
	int round_double(double temp);							         
	double calculateDv(vector<double> sAttr,vector<int> sClass);     
	double calculateTangentLine(vector<double> sAttr,int n);         
	double calculateAverageLine(vector<double> sAttr,int n);         
	double calculateMaxRealGoingPOINum();                            

	int get_classOwnTripID(int ind_i,int ind_j);                     
	int get_classOwnTripID_rowSize(int index);                       
	int get_classCount();                                            
	int get_chosedPOInum();                                          
	double get_accessValueByClass(int index);                        
	double get_accessMeanTimeByClass(int index);                     

	double get_DGridXY(int index);                                   
	double get_timeDiff(int index);                                  
	double get_OGridXY(int index);                                   
	string get_OName(int index);                                     
	double get_ODManyStops(int index);                               
	int get_gridRCtoClass(double index);                             

	void makePOISubwayDistrictMap();                                 

	void readAnother_classArriveTimeSum(vector<double> &vec);        

	void readEraseTo17503GOG();                                      


	void run();                                                      
	void run(int H,double &MyDv,int &MyTripSize);                      


private:

	int classCount;                                
	vector<int> POI_number;                        
	vector<double> POI_weight;                     
	int chosedPOInum;                              

	vector<int> classLabel;                        
	vector<int> waitingRow;						   
	vector<int> waitingColumn;					   
	
	map<double,int> gridRCtoClass;                 
	vector<int> classArriveCount;                  
	vector<double> classArriveTimeSum;             

	 
	Trip* oneDay;                                  
	int MySingleH;                                 
	double MySingleDv;                             
	bool runMyDv;                                  

	vector<double> accessValue;                    
	map<int,int> POI_exist;                        

	map<int,int> POISubwayDistrict_exist;          

	
	vector<vector<int>> classOwnGridID;            
	 
	
	vector<int> classStartCount;                   
	vector<int> calssDistributeStartCount;         

	 
	map<int,int> tripIDToClass;                    

	 

	vector<vector<int>> classOwnTripID;             
	vector<double> accessValueByClass;              
	vector<double> accessMeanTimeByClass;           
	
	 

	set<int> eraseEasternDaPeng;                    

};

