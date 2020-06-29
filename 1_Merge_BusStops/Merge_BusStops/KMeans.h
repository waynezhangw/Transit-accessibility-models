#pragma once
#include<vector>
#include<fstream>

//created time: 2018.07.05

using namespace std;        //This class is for running k-means clustering method
class KMeans
{
public:
	KMeans(void);
	~KMeans(void);

	void run();                                  //������ʼһ�У���ȡ����վ�㣬������cluster
	void deleteAbnormal();                       //�����ڰ�8��վ��������������ҳ��쳣��ĳ������Ȼ��ɾ��������ʱΪ7��or6��
	bool allDiffLine();                         //�����жϷŽ�ȥ��8��վ���Ƿ����ͬ��·�������ͬ��·�����Ʊ�Ҫ����·����
	void findFarPoint(int &p1,int &p2);         //��ͼ�ҵ�localX�������Զ����������vector�е�λ��
	void deleteAbnormalByDBscan();              //���������뾶�Ͱ뾶�ڸ���Ҫ�����Ƴ���Щ����ȷ�Ĳ����е�����
	bool checkRepeat(double tempX,double tempY);  //���ͬ��վ���д�������һģһ����վ�㣬����оͷ���Ϊ��



private:
	vector<double> localX;          //������1-8��ͬ��վ�㣬�ǾͰ���˸���ͳͳ�Ž���
	vector<double> localY;
	vector<string> localLineN;      //������1-8��ͬ��վ�㣬�ǾͰ���˸�վ�����ڵ���·Ҳ�Ž����������ж��Ƿ���ͬ��·��վ��
	int K;                          //�÷����·ּ����k����ʵ���зֹ���վ�Ļ�������
	int iterations;                 //k��ֵ���������������
	ofstream outfile;               //��X��Y������������csv��
};

