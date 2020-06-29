#pragma once


#include<vector>
#include<map>

using namespace std;

class Trip
{
public:
	Trip(void);
	~Trip(void);

	void makeSubwayLineMap();											 //��subwayLineNumber���map�ֶ�����
	void readODTrip(ifstream &fin);										 //��ȡ����trip�����յ�����ͳ���ʱ�䡢����ʱ�����Ϣ  
	double convertStringToDouble(string str1);							 //����������string������ת���ɿɱȽϵ�double����
	int convertTimeStringToInt(string str1);							 //��2017-04-05 19:23:38������stringת����int�͵���
	int extractTimeHour(string str1);									 //��2017-04-05 19:23:38������string�е�19��ȡ����
	string extractSubwayLine(string str1);								 //���뻻����Ϣ�ֶΣ����������Ϣ���������ŵ��Ǹ�������·��������ǵ����������
	double getTwoPointDistance(double x1,double y1,double x2,double y2); //�������ľ���

	int get_tripSize();                                  //���ض���������Ч�ķ�ʱ��ε�trip�ĸ���

	void readBusStop();                                  //��ȡ����,���һ�������
	void makeStopStartCount();                           //����һ���վ��ÿ�����׳�������
	bool isSubwayStop(string str1);                      //����һ��վ�������ǲ��ǵ���վ���Ǿͷ�����
	string extractSubwayName(string str1);               //�������վ���֣��Ѻ������·�ű�ʶ�͡�վ����ȥ������ֱ�Ӽ�����·�����ֺţ�Ȼ��map

	void makeStopEndCount();                                  //�����յ�Ϊ��������ǧ��վ��ÿ�����׵�����ٸ�


	void countTripCardIDMost();                               //��һ�µ���trip�����ظ����������Ǹ��ˣ�Ҫ�Ǻ�����Ҫ���������Ĵ������͸ĳ��з���ֵ��
	void getTripDurationTime();                               //���㶺��ʱ�䣬������������trip֮����ܼ�����
	string eraseSubwayLine(string str1);                      //����"���ڱ�-5"����������ڱ���
	void addSuitableDurationTime();                           //���䶺��ʱ�䣬��Ҫ��������trip����Щ���ؼ��¿��˸��ط���trip
	bool findSimilarTrip(int pos,vector<int> &vec);           //������posλ�ã�360���е�λ�ã���trip���Ƶ�trip���ҵ����trip��ID��360���е�λ�ã��ŵ�vec�в������棬�Ҳ�����ֱ�ӷ��ؼ�
	bool findSimilarTrip2(int pos,int wPos,vector<int> &vec); //����Ƕ���� findSimilarTrip�������������һ��1��վ����λ�õĲ���
	bool proportionTrip(int pos,double &value);               //�������ձ��������䶺��ʱ��

	void writeInTheExistingFile();                            //�Ѷ���ʱ��д�����е��ļ���

	void run();                                          //��read����д����������


private:

	map<string,string> subwayLineNumber;      //��<����������,-2>����������
	int tripDay;                              //����ָʾ���ڶ����ڼ����˵�һ��ȫ�ֱ���

	vector<string> tripCardID;                //��¼ÿ��trip�Ŀ���
	vector<string> OStopName;                 //��¼trip����վ�������վ�ǵ��������Ұѵ�������·�ż��뵽վ�������磺��Էվ-2����ʾ����ǵ��������ߵĿ�Էվ
	vector<string> DStopName;                 //��¼trip�յ�վ��
	vector<double> OGrid_X;                    //��ʼվ���������Ϣ�ֿ���
	vector<double> OGrid_Y;
	vector<double> DGrid_X;                   //��ֹվ���������Ϣ�ֿ���
	vector<double> DGrid_Y;
	vector<double> getOnTime;                 //���³�ʱ��
	vector<double> getOffTime;

	vector<double> tripDurationTime;          //trip�Ķ���ʱ�䣬��һ��ÿһ������ֵ��������ǴӼ�¼��������ģ�����Ҫһ�����㡣����Ҫ�����飬��һ�����ֱ�ӵĶ���ʱ�䣬�ڶ��������Ҫ����Ķ���ʱ��
	vector<double> tripDurationTime_v1;       //��δ����֮ǰ�Ķ���ʱ�䱣��һ�ݣ�������������䶫��

	vector<int> oneWStopID;                       //һ���վ����Ǹ�վ���ID�ţ�����·����͵�����·��ͳ��
	vector<double> oneWX;                         //һ���վ����Ǹ�վ���X��������߶ζ˵��X����
	vector<double> oneWY;                         //һ���վ����Ǹ�վ���Y��������߶ζ˵��Y����
	vector<string> oneWStopName;                  //һ���վ����Ǹ�վ�������
	map<string,int> oneWStopNameToID;             //����һ���վ�������������ڵ�ID��
	vector<int> stopStartCount;                   //�洢ÿ��վ�㣨����·����͵�����·��ͳ�ƣ��е��ۻ��������������������С���ļ�"merge_BusStation�Ľ�dbscan�ӵ���"�Ĵ�С��ͬ
	vector<vector<int>> stopStartTripIDInclude;   //��ά������������һ���һ���վ�����ֵĳ��ȣ�ÿ��վ���ӵ��һ������trip�������ֱ�Ӱ�trip�ľ�����push����

	//�����stopStartCount���������й����ģ�������Ҫ����һ���յ�
	//�о��յ㲻��������·���棬��Ϊ�յ㵽���������trip�ˣ������Ҫ�֣���·���������ֱ�Ӿ���������������ͬ�ķ����н����������岻ͬ
	vector<string> sixKStopName;                  //����ǧ��վ�����ղ���˳������ַŽ���
	map<string,int> sixKStopNameToID;             //����һ���վ�������������ڵ�ID��
	vector<int> stopEndCount;                     //��trip�����е��յ㣨���ظ��������յ�վ�㼯�ϣ����6000��,�洢ÿ���յ���ۻ��������
	vector<vector<int>> stopEndTripIDInclude;     //��ά��������������ǧ�೤�ȣ�ÿ��վ���ӵ��һ������tripʵ�ʱ��
};

