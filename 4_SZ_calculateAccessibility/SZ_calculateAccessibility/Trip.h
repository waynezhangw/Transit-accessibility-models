#pragma once

#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<map>

 
using std::string;
using std::vector;
using std::map;
using std::ifstream;

class Trip         //This class is dealling with trip related information, including reading, indexing, sorting ,etc.
{
public:
	Trip(void);
	~Trip(void);

	void readODTrip(ifstream &fin);                       
	double convertStringToDouble(string str1);            
	int convertTimeStringToInt(string str1);              
	int extractTimeHour(string str1);                     
	double getGridPos(double x,double y);				  
	int round_double(double temp);						  

	int get_singleHour();                                 
	int get_durationLast();                               
	double get_OriginX();                                 
	double get_OriginY();
	int get_tripSize();                                   
	string get_OStopName(int index);                      
	double get_tripOGrid_X(int index);                    
	double get_tripOGrid_Y(int index);
	double get_tripDGridXY(int index);                    
	double get_tripTimeDiff(int index);                   
	double get_ODStopNumber(int index);                   

	string get_TripCardID(int index);                     
	double get_TripDurationTime(int index);               

	 
	 
	string extractSubwayLine(string str1);                
	void makeSubwayLineMap();                             
	void makeOStopNameAccumulation();                     
	void readBusStop();                                   
	void makeStopStartCount();                            
	bool isSubwayStop(string str1);                       
	string extractSubwayName(string str1);                
	double getTwoPointDistance(double x1,double y1,double x2,double y2);     
	
	 
	void readStopGrid();                                  
	void readStopGridDis();                               
	void getStopEachGridNumber();                         
	void makeStopEachGridTripID();                        


	int get_stopEachGridTripID(int i,int j,int k);        
	int get_stop_size();                                  
	int get_stopNearestGrid_size(int index);              
	int get_stopNearestGridID_size(int ind1,int ind2);    
	int get_gridID(int i,int j);                          
	double get_oneWX(int index);                          
	double get_oneWY(int index);                          
	string get_oneWStopName(int index);                   
	int get_stopStartCount(int index);                    
	int get_busOrSubwayDivide();                          

	double get_tripWalkDis(int index);                    
	double get_tripStopOwnPos(int index);                 

	void countTripCardIDMost();                           

	void run();                                           
	void set_SingleHour(int H);                           


private:

	int singleHour;                            
	int durationLast;                          

	double OriginX;                            
	double OriginY;                            

	 
	vector<string> tripCardID;                 
	vector<double> tripDurationTime;           
	
	vector<string> OStopName;                  
	vector<double> OGrid_X;                     
	vector<double> OGrid_Y;
	vector<double> DGridXY;                    
	vector<double> timeDiff;                   
	vector<double> ODStopNumber;               

	map<string,string> subwayLineNumber;       
	int tripDay;                               

	map<string,int> OAccumulation;               
	vector<int> stopStartCount;                  
	vector<vector<int>> stopStartTripIDInclude;  

	 
	vector<int> oneWStopID;                        
	vector<double> oneWX;                          
	vector<double> oneWY;                          
	vector<string> oneWStopName;                   
	map<string,int> oneWStopNameToID;              

	 
	vector<vector<int>> stopNearestGrid;                  
	vector<vector<double>> stopNearestGridDis;            

	vector<vector<int>> stopEachGridNumber;               
	vector<double> sumFraction;                           
	vector<vector<vector<int>>> stopEachGridTripID;       

	double maxBusWalkingDis;                              
	double maxSubwayWalkingDis;                           
	unsigned int busOrSubwayDivide;                                

	vector<double> tripWalkDis;                           
	vector<double> tripStopOwnPos;                        


};

