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

	void run();                                  //用来开始一切，读取所有站点，并进行cluster
	void deleteAbnormal();                       //类似于把8个站点坐标读进来，找出异常的某个坐标然后删除，返回时为7个or6个
	bool allDiffLine();                         //用来判断放进去的8个站点是否存在同线路，如果有同线路，那势必要分马路对面
	void findFarPoint(int &p1,int &p2);         //试图找到localX里相聚最远的两个点在vector中的位置
	void deleteAbnormalByDBscan();              //假如搜索半径和半径内个数要求来移除那些不精确的不集中的坐标
	bool checkRepeat(double tempX,double tempY);  //检查同名站点中存在坐标一模一样的站点，如果有就返回为真



private:
	vector<double> localX;          //假如有1-8个同名站点，那就把这八个的统统放进来
	vector<double> localY;
	vector<string> localLineN;      //假如有1-8个同名站点，那就把这八个站点所在的线路也放进来，用于判断是否有同线路的站点
	int K;                          //该方法下分几类的k，本实验中分公交站的话即两类
	int iterations;                 //k均值聚类的最大迭代次数
	ofstream outfile;               //把X和Y坐标进行输出到csv中
};

