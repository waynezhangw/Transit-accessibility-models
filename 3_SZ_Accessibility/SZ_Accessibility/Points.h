#pragma once
#include<vector>

using namespace std;
//This class is not only used to store the coordinate information of all the stations, 
//but also used as the coordinate information of the end points of the road network segment
class Points           
{
public:
	Points(void);
	~Points(void);

	void readBusStop();                             
	double convertStringToDouble(string str1);      
	int get_stopID(int index);                      
	string get_stopName(int index);                 
	double get_pointX(int index);
	double get_pointY(int index);
	int getStopSize();                              
	void set_pointX(double X);                      
	void set_pointY(double Y);

	void set_nearDis(double Dis);                   
	void set_nearX(double X);                       
	void set_nearY(double Y);
	double get_nearDis(int index);                  
	double get_nearX(int index);
	double get_nearY(int index);

private:
	vector<int> stopID;            
	vector<double> X;              
	vector<double> Y;              
	vector<string> stopName;       

	 
	vector<double> nearestDis;        
	vector<double> nearestX;          
	vector<double> nearestY;




};

