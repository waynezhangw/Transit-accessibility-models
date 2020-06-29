#pragma once
#include "BusPoint.h"

//created time: 2018.07.05

class BusCluster          //This class is for clustering results operation
{
public:
	BusCluster(void);
	~BusCluster(void);

	void add_clusterPoints(double X,double Y);     //类外添加候选的点，一开始肯定是空的，最先添加进去那两个离得最远的点
	void delete_clusterPoints(int index);         //如果有不符合的点，把他移除当前的cluster
	double get_clusterX(int index);        //类外获取点的坐标
	double get_clusterY(int index);
	void add_individual(int who);          //类外添加点的编号，比如1、2、3、4、5、6、7,可能一个cluster会被添加进去1、2、3
	int get_individual(int index);         //获取当前cluster的编号
	void delete_individual(int index);     //移除当前cluster中的某一个编号
	void set_central();                   //一次性设定中心点的坐标，这个可能每添加进来一个点就要变一下
	double get_central_X();
	double get_central_Y();
	int get_clusterSize();                 //获取当前cluster中有几个点
	int transformIndex(int index);         //把localX的索引变成Cluster里的索引

private:
	BusPoint* cluster;          //用来存储每个聚类站点群的站点坐标，别调用readBusStop()，用的话就一个一个往进添加
	vector<int> individual;     //记录当前是哪几个点在一起
	double central_X;          //记录不断更新的中心点的坐标值
	double central_Y;
};

