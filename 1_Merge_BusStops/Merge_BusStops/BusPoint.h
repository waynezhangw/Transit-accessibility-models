#pragma once
#include<vector>

//created time: 2018.06.29

using namespace std;          //This class is for original bus stop operation
class BusPoint
{
public:
	BusPoint(void);
	~BusPoint(void);
	void readBusStop();                            //读取坐标
	double convertStringToDouble(string str1);     //将读进来的string型坐标转化成可比较的double类型
	string get_stopName(int index);                //用在类外，可以索引到读进来的站名
	string get_stopLine(int index);                //用在类外，可以索引到读进来的站名所在的线路名
	double get_stopX(int index);
	double get_stopY(int index);
	int getStopSize();                             //类外获取读进来的站点的个数
	void add_stopName(string str1);                 //从类外为vector添加name
	void add_lineName(string str1);                 //从类外为vector添加站点name所在的线路
	void add_stopX(double X);                      //类外添加坐标
	void add_stopY(double Y);
	void delete_stopX(int index);                   //类外移除坐标
	void delete_stopY(int index);


private:
	vector<string> stopName;       //定义读进来的公交站站名
	vector<string> lineName;       //定义读进来的公交站所在的线路名，主要用于判断两类or一类，假如8个同名站点，全都不在一条线，那就一类
	vector<double> stopX;          //公交站坐标
	vector<double> stopY;
};

