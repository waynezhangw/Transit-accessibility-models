#pragma once

#include "District.h"

using std::vector;

class Theory     //This class is dealing with theoretical accessibility related operations
{
public:
	Theory(void);
	~Theory(void);



	void makeGaoDeXY();                                                                        
	void readTheoryPOI();                                                                      
	void readGuanNei();                                                                        

	void findTheoryInvalidTime();                                                              
	void readTheoryTime();                                                                     
	void fillInvalidTime();                                                                    
	void calculateAccessByTheory();                                                            

	void makeTheoryPOIMap();                                                                   
	void calculateDistrictToTheoryPOITime();                                                   
	void readFinalDistrictToTheoryPOITime();                                                   
	void calculateAccessRealTravelTime();                                                      

	void calculateTravelRadius();                                              
	void seeTripInfo(int tripID,int distrID);                                  

	void readRealPOI();                                                        
	void makeRealPOIMap();                                                     
	void calculateDistrictToRealPOITime();                                     
	void readFinalDistrictToRealPOITime();                                     
	void calculateAccessRealPOITravelTime();                                   

	void run();                                                                                



private:

	District* myDistrict;                                
	int selectedPOINum;                                  
	
	vector<double> myPOIVecX;                               
	vector<double> myPOIVecY;
	vector<double> myPOIWeight;                             

	vector<int> myVecID;                                 

	vector<int> invalidTimePos;                          

	vector<vector<double>> theoryTime;                   
	vector<double> accessValueByTheory;                  
	vector<double> meanTimeValue;                        

	map<double,int> theoryPOI_exist;                        
	vector<vector<double>> districtToTheoryPOITime;      
	vector<vector<int>> districtToTheoryPOINumber;       

	vector<vector<double>> finalDistrictToTheoryPOITime;      
	vector<vector<double>> finalDistrictToTheoryPOINumber;    
	vector<double> realMeanTimeValue;                         
	vector<double> realMeanTimeValueWeight;                   

	vector<int> myRealPOIDistrictID;                            
	vector<double> myRealPOIWeight;                             
	map<int,int> realPOI_exist;                                 
	vector<vector<double>> districtToRealPOITime;            
	vector<vector<int>> districtToRealPOINumber;             
	vector<vector<double>> finalDistrictToRealPOITime;       
	vector<vector<double>> finalDistrictToRealPOINumber;     
	vector<double> realPOIMeanTimeValue;                         
	
};