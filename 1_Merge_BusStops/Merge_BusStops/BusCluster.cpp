#include "BusCluster.h"
#include<iostream>

using namespace std;
BusCluster::BusCluster(void)
{
	central_X=0;
	central_Y=0;
	cluster=new BusPoint();
}


BusCluster::~BusCluster(void)
{
	delete cluster;
	cluster=NULL;
}

void BusCluster::add_clusterPoints(double X,double Y)
{
	cluster->add_stopX(X);
	cluster->add_stopY(Y);
}
void BusCluster::delete_clusterPoints(int index)
{
	index=transformIndex(index);     //输入的是index是localX里的索引，输出的index是cluster里的索引，前者大于等于后者
	cluster->delete_stopX(index);
	cluster->delete_stopY(index);
}
double BusCluster::get_clusterX(int index)
{
	return cluster->get_stopX(index);
}
double BusCluster::get_clusterY(int index)
{
	return cluster->get_stopY(index);
}
void BusCluster::add_individual(int who)
{
	individual.push_back(who);
}
int BusCluster::get_individual(int index)
{
	return individual[index];
}
void BusCluster::delete_individual(int index)
{
	index=transformIndex(index);  
	individual.erase(individual.begin()+index);
}
void BusCluster::set_central()
{
	double sumX=0;                             //用于累加当前横坐标的总值
	double sumY=0;
	int N=cluster->getStopSize();              //用于判断当前cluster添加进来几个点的座标了
	for(int i=0;i<N;i++)
	{
		sumX=sumX+cluster->get_stopX(i);
		sumY=sumY+cluster->get_stopY(i);
	}
	this->central_X=sumX/N;
	this->central_Y=sumY/N;
	
}
double BusCluster::get_central_X()
{
	return central_X;
}

double BusCluster::get_central_Y()
{
	return central_Y;
}
int BusCluster::get_clusterSize()
{
	return int(cluster->getStopSize());
}
int BusCluster::transformIndex(int index)            //输入localX的索引，输出在cluster中的索引
{
	for(unsigned int i=0;i<individual.size();i++)      //这个for循环把localX的索引变成Cluster里的索引，即原来18里的15变换成cluster的7
	{
		if(individual[i]==index)              //如果找到就跳出
		{
			return i;
		}
	}
	cout<<"There might be some issues, cannot find index at current cluster"<<endl;
	return 0;
}