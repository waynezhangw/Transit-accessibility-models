#include "KMeans.h"
#include "BusPoint.h"
#include "BusCluster.h"
#include<string>
#include<cmath>
#include<iostream>
#include<map>
#include<iomanip>

using namespace std;
KMeans::KMeans(void)
{
	K=2;                   //由于只分马路这边和对面两类，所以这里分类为2
	iterations=10;
}


KMeans::~KMeans(void)
{
}

void KMeans::run()
{
	BusPoint* busObject=new BusPoint();
	busObject->readBusStop();
	string tempStopName="空";             //假如有5956个不同的站名，那它可能要被赋值5956次
	busObject->add_stopName("mean to do so as a ending flag");             //这个是为了防止遍历到i+1而出错，就提前多增加一个进去
	outfile.open("..\\result\\merge_BusStation.csv");
	for(int i=0;i<busObject->getStopSize();i++)      //这里的size是遍历4万多个未合并站点
	{
		if(tempStopName!=busObject->get_stopName(i))
		{
			tempStopName=busObject->get_stopName(i);       //每次执行到这里的时候，localX应该是空的
		}
		if(!checkRepeat(busObject->get_stopX(i),busObject->get_stopY(i)))    //大部分情况都返回false
		{
			localX.push_back(busObject->get_stopX(i));
			localY.push_back(busObject->get_stopY(i));
			localLineN.push_back(busObject->get_stopLine(i));
		}

		//这里需要一个判断说是大于等于三个点再做以下操作
		//先判断一下是否全都没有重复线路
		if(busObject->get_stopName(i)==tempStopName && busObject->get_stopName(i+1)!=tempStopName)  //当前等于但下一个不等于,且是至少3个  
		{                    
			if(localX.size()==1)
			{
				//用outfile输出这个点
				outfile<<tempStopName<<","<<localLineN[0]<<","<<fixed<<setprecision(6)<<localX[0]<<","<<localY[0]<<endl;
				//要清空一下loacalX那几个
				localX.clear();
				localY.clear();
				localLineN.clear();
				continue;              //continue直接跳到下一个i的循环
			}
			if(localX.size()==2)
			{
				//预计这里计算的很慢，这个算距离的
				if(sqrt((localX[1]-localX[0])*(localX[1]-localX[0])+(localY[1]-localY[0])*(localY[1]-localY[0]))>500)
				{
					cout<<"Two stops, but far away:"<<i<<endl;         //判断一下异常情况，输出看看，两个同名站点却相距500米开外
				}
				if(busObject->get_stopLine(i)==busObject->get_stopLine(i-1))      //表示刚好马路这边一个，那边一个
				{
					//直接输出这种，打断的时候打离它最近的
					outfile<<tempStopName+"a"<<","<<localLineN[0]<<","<<fixed<<setprecision(6)<<localX[0]<<","<<localY[0]<<endl;
					outfile<<tempStopName+"b"<<","<<localLineN[1]<<","<<fixed<<setprecision(6)<<localX[1]<<","<<localY[1]<<endl;
					//清空一下LocalX
					localX.clear();
					localY.clear();
					localLineN.clear();
					continue;
				}
				else
				{
					//将这两个合并处理，取平均坐标值
					double meanX=(localX[0]+localX[1])/2;
					double meanY=(localY[0]+localY[1])/2;
					outfile<<tempStopName<<","<<localLineN[0]<<","<<fixed<<setprecision(6)<<meanX<<","<<meanY<<endl;
					//清空一下
					localX.clear();
					localY.clear();
					localLineN.clear();
					continue;
				}
			}
			else
			{
				deleteAbnormal();                       //删除那种特别夸张的异常点
				deleteAbnormalByDBscan();               //删除那些虽然离得近，但稍稍“不合群”的点
				bool mergeAll=allDiffLine();            //如果为真，就不区分马路对面
				if(mergeAll)
				{
					//合并全部成一个点
					double sumX=0;                      //暂时存储累加的点的坐标
					double sumY=0;
					for(unsigned int j=0;j<localX.size();j++)
					{
						sumX=sumX+localX[j];
						sumY=sumY+localY[j];
					}
					double meanX=sumX/localX.size();
					double meanY=sumY/localY.size();
					outfile<<tempStopName<<","<<localLineN[0]<<","<<fixed<<setprecision(6)<<meanX<<","<<meanY<<endl;   //tempStopName和localLine应该都是第一个
					//清空一下
					localX.clear();
					localY.clear();
					localLineN.clear();
				}
				else                                //如果有同线路站点，势必分成马路这边和那边两个阵营
				{
					int a1=0;
					int a2=0;
					findFarPoint(a1,a2); 					//找出最远的两个站点的编号,  
					//cout<<a1<<"    "<<a2<<endl;
					BusCluster* ClusA=new BusCluster();
					BusCluster* ClusB=new BusCluster();
					ClusA->add_clusterPoints(localX[a1],localY[a1]);				
					ClusA->add_individual(a1);
					ClusA->set_central();
					ClusB->add_clusterPoints(localX[a2],localY[a2]);
					ClusB->add_individual(a2);
					ClusB->set_central();
					for(unsigned int j=0;j<localX.size();j++)
					{
						if(j==a1||j==a2)
						{
							continue;
						}
						double tempDisA=0;
						double tempDisB=0;
						tempDisA=sqrt((localX[j]-ClusA->get_central_X())*(localX[j]-ClusA->get_central_X())+(localY[j]-ClusA->get_central_Y())*(localY[j]-ClusA->get_central_Y()));
						tempDisB=sqrt((localX[j]-ClusB->get_central_X())*(localX[j]-ClusB->get_central_X())+(localY[j]-ClusB->get_central_Y())*(localY[j]-ClusB->get_central_Y()));
						if(tempDisA<=tempDisB)     //如果离ClusterA近，那么要往A类里面添加
						{
							ClusA->add_clusterPoints(localX[j],localY[j]);				
							ClusA->add_individual(j);
							ClusA->set_central();
						}
						else
						{
							ClusB->add_clusterPoints(localX[j],localY[j]);				
							ClusB->add_individual(j);
							ClusB->set_central();
						}
					}
					//这里开始再分配，判断每个类内的点是否离当前类中心近而离另一个类中心远
					for(int j=0;j<iterations;j++)              //这一层for迭代次数
					{
						double AcentralX=ClusA->get_central_X();
						double AcentralY=ClusA->get_central_Y();
						double BcentralX=ClusB->get_central_X();
						double BcentralY=ClusB->get_central_Y();
						vector<int> exchangeP;                  //用来存放一次迭代下来需要交换的点的编号
						vector<string> exchangeN;               //用来存放一次迭代下来需要交换的点的编号本来所属的类AorB
						int kanyixia=exchangeP.size();          //看一下不往进放会不会是0.这一句要删的
						for(unsigned int k=0;k<localX.size();k++)       //这一层for每一个点到两个类的聚类中心
						{
							double tempDisA=0;                 //暂时存储各个点到两个聚类中心的距离
							double tempDisB=0;
							tempDisA=sqrt((localX[k]-AcentralX)*(localX[k]-AcentralX)+(localY[k]-AcentralY)*(localY[k]-AcentralY));
							tempDisB=sqrt((localX[k]-BcentralX)*(localX[k]-BcentralX)+(localY[k]-BcentralY)*(localY[k]-BcentralY));
							string tempAB="0";                          //用来存字符串A or B，指示当前k点属于哪个聚类里
							for(int t=0;t<ClusA->get_clusterSize();t++)          //这一层for循环为了找当前的k点在哪个类里
							{
								if(k==ClusA->get_individual(t))
								{
									tempAB="A";
									break;
								}
								else
								{
									tempAB="B";
								}
							}
							if(tempAB=="A" && tempDisA>tempDisB)          //明明属于A，但却离B近
							{
								exchangeP.push_back(k);
								exchangeN.push_back("A");
								continue;
							}
							if(tempAB=="B" && tempDisA<tempDisB)          //明明属于B，但却离A近
							{
								exchangeP.push_back(k);
								exchangeN.push_back("B");
							}
							//要判断出当前是否发生需要重分配的情况，然后把k的值记录到vector中（后面遍历vector进行交换）
							//要去除这个类里有的同时重新算centralX；然后再添加到另一个类里
						}
						if(exchangeP.size()==0)                     //代表一次迭代下来没找到异常点
						{
							outfile<<tempStopName+"a"<<","<<localLineN[0]<<","<<fixed<<setprecision(6)<<ClusA->get_central_X()<<","<<ClusA->get_central_Y()<<endl; 
							outfile<<tempStopName+"b"<<","<<localLineN[1]<<","<<fixed<<setprecision(6)<<ClusB->get_central_X()<<","<<ClusB->get_central_Y()<<endl; 
							break;
						}
						for(unsigned k=0;k<exchangeP.size();k++)     //这一层for循环为了进行交换
						{
							//进行交换
							if(exchangeN[k]=="A")
							{
								ClusA->delete_clusterPoints(exchangeP[k]);
								ClusA->delete_individual(exchangeP[k]);
								ClusB->add_clusterPoints(localX[exchangeP[k]],localY[exchangeP[k]]);				
								ClusB->add_individual(exchangeP[k]);
								ClusB->set_central();
							}
							else
							{
								ClusB->delete_clusterPoints(exchangeP[k]);
								ClusB->delete_individual(exchangeP[k]);
								ClusA->add_clusterPoints(localX[exchangeP[k]],localY[exchangeP[k]]);				
								ClusA->add_individual(exchangeP[k]);
								ClusA->set_central();
							}
						}
						if(j=iterations-1)                     //如果到最后一次迭代还没有交换完就赶紧输出
						{
							outfile<<tempStopName+"a"<<","<<localLineN[0]<<","<<fixed<<setprecision(6)<<ClusA->get_central_X()<<","<<ClusA->get_central_Y()<<endl; 
							outfile<<tempStopName+"b"<<","<<localLineN[1]<<","<<fixed<<setprecision(6)<<ClusB->get_central_X()<<","<<ClusB->get_central_Y()<<endl;
						}
						//完了要清空一下exchange 的vector
						exchangeP.clear();
						exchangeN.clear();
					}

					//清空一下localX那几个
					localX.clear();
					localY.clear();
					localLineN.clear();

					delete ClusA;
					ClusA=NULL;
					delete ClusB;
					ClusB=NULL;
				}
			}
			//判断了进来的话，意味着当前站名添加饱了，得
			//1.先剔除异常站点
			//2.找出最远的两个站点
			//3.把最远的两个站点分别放入两个cluster中
			
		}
		
	}

	outfile.close();             //输出完文件进行关闭

	delete busObject;
	busObject=NULL;
}

void KMeans::deleteAbnormal()                           //假设原始数据中最多只有一个异常点
{
	//应该有需要剔除的站点非常少，所以只要真的剔除了，就搞一个输出到控制台
	for(unsigned int i=0;i<localX.size();i++)     
	{
		double tempDis=0;
		bool errorP=true;                       //初始认为当前点是异常点，所以给它真
		for(unsigned int j=0;j<localX.size();j++)
		{
			if(i==j)
			{
				continue;
			}
			tempDis=sqrt((localX[i]-localX[j])*(localX[i]-localX[j])+(localY[i]-localY[j])*(localY[i]-localY[j]));     //两点间距离
			if(tempDis<1000)             //如果这个为真，代表当前i点周围是存在同类的，所以不是异常点
			{
				errorP=false;
				break;
			}
		}
		if(errorP)      //如果执行这里，表明比了一圈下来都没有离i点很近的点
		{		
			//去掉位置i处的点
			localX.erase(localX.begin()+i);
			localY.erase(localY.begin()+i);
			localLineN.erase(localLineN.begin()+i);
			i--;
		}
		else            //如果为真，证明i点比了一圈下来有和它距离在1000米以内的点
		{
			continue;
		}
	}
}

bool KMeans::allDiffLine()
{
	map<string,int> BusStationsLineMap;            //定义这个唯一性的map
	pair<map<string,int>::iterator, bool> Insert_Pair;   //用来接收是否插入成功
	int j=0;                                               //用来记录O的不重复的位置，i用来遍历
	for(unsigned int i=0;i<localLineN.size();i++,j++)   //因为OGridXY.size()的返回值是unsigned int型的，所以前面的i必须一致
	{
		Insert_Pair=BusStationsLineMap.insert(pair<string,int>(localLineN[i],j+1));   //构建时让第一个站点的value值为1
		if(Insert_Pair.second==false)
		{
			j--;
		}
	}
	if(BusStationsLineMap.size()==localLineN.size())            //如果无重复线路名，则表示都在马路一侧,map会和vector一样大
	{
		return true;
	}
	else
	{
		return false;
	}
}

void KMeans::findFarPoint(int &p1,int &p2)    //或者用某个简便方法：先随机用一个点找离他最远的，然后再求找到的这个点的最远的点
{
	//先用蛮力法,后面这里要改进
	double twoDis=0;
	for(unsigned int i=0;i<localX.size();i++)
	{
		double tempDis=0;
		for(unsigned int j=0;j<localY.size();j++)
		{
			if(i==j)
			{
				continue;
			}
			tempDis=sqrt((localX[i]-localX[j])*(localX[i]-localX[j])+(localY[i]-localY[j])*(localY[i]-localY[j]));
			if(tempDis>twoDis)
			{
				twoDis=tempDis;
				p1=i;
				p2=j;
			}
		}
	}
}
void KMeans::deleteAbnormalByDBscan()
{
	int stopNumber=localX.size();
	if(stopNumber<5)
	{
		//这里就直接跳出该函数把
	}
	else
	{
		//个数设置为3
		vector<int> outPosition;               //记录稍微异常一点的点的位置
		for(unsigned int i=0;i<localX.size();i++)     
		{
			double tempDis=0;                  //记录一下点i周围到底多大范围内的点才算比较近，类似于dbscan的半径
			int countNear=0;                  //记录一下点i周围到底有多少个比较近的点，类似于dbscan的个数
			for(unsigned int j=0;j<localX.size();j++)
			{
				if(i==j)                      //自己和自己比距离没有意义
				{
					continue;
				}
				tempDis=sqrt((localX[i]-localX[j])*(localX[i]-localX[j])+(localY[i]-localY[j])*(localY[i]-localY[j]));
				if(tempDis<20)               //如果点i周围20米以内有点，那么就棒棒的
				{
					countNear++;
				}
			}
			if(stopNumber>=5 && stopNumber<10 && countNear<1)                  //要是周围有1个临近点就可以幸免
			{
				outPosition.push_back(i);
			}
			if(stopNumber>=10 && stopNumber<=15 && countNear<2)                  //这个2也是得随着本身同名站点的个数而变化的阈值
			{
				outPosition.push_back(i);
			}
			if(stopNumber>15 && countNear<3)                  //这个2也是得随着本身同名站点的个数而变化的阈值
			{
				outPosition.push_back(i);
			}
		}
		if(int(outPosition.size())<=stopNumber/2)             //如果要去除的个数小于原始个数的一半才会进行去除，因为原来6个，不可能全部去除嘛
		{
			int decrease=0;                      //for循环里每去除vector里一个值，vector的size会动态变化
			for(unsigned int i=0;i<outPosition.size();i++)
			{
				localX.erase(localX.begin()+(outPosition[i]-decrease));
				localY.erase(localY.begin()+(outPosition[i]-decrease));
				localLineN.erase(localLineN.begin()+(outPosition[i]-decrease));
				decrease++;
			}
		}
		
		outPosition.clear();
	}
	//无返回值

}
bool KMeans::checkRepeat(double tempX,double tempY)
{
	bool alreadyHave=false;
	for(unsigned int i=0;i<localX.size();i++)         //遍历所有已经放进去的，看当前要放的和里面有没有重复
	{
		if(tempX==localX[i] && tempY==localY[i])
		{
			alreadyHave=true;
			return alreadyHave;
		}
	}
	return alreadyHave;
}

