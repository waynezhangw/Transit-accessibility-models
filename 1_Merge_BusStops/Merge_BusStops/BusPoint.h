#pragma once
#include<vector>

//created time: 2018.06.29

using namespace std;          //This class is for original bus stop operation
class BusPoint
{
public:
	BusPoint(void);
	~BusPoint(void);
	void readBusStop();                            //��ȡ����
	double convertStringToDouble(string str1);     //����������string������ת���ɿɱȽϵ�double����
	string get_stopName(int index);                //�������⣬������������������վ��
	string get_stopLine(int index);                //�������⣬������������������վ�����ڵ���·��
	double get_stopX(int index);
	double get_stopY(int index);
	int getStopSize();                             //�����ȡ��������վ��ĸ���
	void add_stopName(string str1);                 //������Ϊvector���name
	void add_lineName(string str1);                 //������Ϊvector���վ��name���ڵ���·
	void add_stopX(double X);                      //�����������
	void add_stopY(double Y);
	void delete_stopX(int index);                   //�����Ƴ�����
	void delete_stopY(int index);


private:
	vector<string> stopName;       //����������Ĺ���վվ��
	vector<string> lineName;       //����������Ĺ���վ���ڵ���·������Ҫ�����ж�����orһ�࣬����8��ͬ��վ�㣬ȫ������һ���ߣ��Ǿ�һ��
	vector<double> stopX;          //����վ����
	vector<double> stopY;
};

