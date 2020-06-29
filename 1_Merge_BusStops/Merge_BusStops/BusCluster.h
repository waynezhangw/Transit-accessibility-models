#pragma once
#include "BusPoint.h"

//created time: 2018.07.05

class BusCluster          //This class is for clustering results operation
{
public:
	BusCluster(void);
	~BusCluster(void);

	void add_clusterPoints(double X,double Y);     //������Ӻ�ѡ�ĵ㣬һ��ʼ�϶��ǿյģ�������ӽ�ȥ�����������Զ�ĵ�
	void delete_clusterPoints(int index);         //����в����ϵĵ㣬�����Ƴ���ǰ��cluster
	double get_clusterX(int index);        //�����ȡ�������
	double get_clusterY(int index);
	void add_individual(int who);          //������ӵ�ı�ţ�����1��2��3��4��5��6��7,����һ��cluster�ᱻ��ӽ�ȥ1��2��3
	int get_individual(int index);         //��ȡ��ǰcluster�ı��
	void delete_individual(int index);     //�Ƴ���ǰcluster�е�ĳһ�����
	void set_central();                   //һ�����趨���ĵ�����꣬�������ÿ��ӽ���һ�����Ҫ��һ��
	double get_central_X();
	double get_central_Y();
	int get_clusterSize();                 //��ȡ��ǰcluster���м�����
	int transformIndex(int index);         //��localX���������Cluster�������

private:
	BusPoint* cluster;          //�����洢ÿ������վ��Ⱥ��վ�����꣬�����readBusStop()���õĻ���һ��һ���������
	vector<int> individual;     //��¼��ǰ���ļ�������һ��
	double central_X;          //��¼���ϸ��µ����ĵ������ֵ
	double central_Y;
};

