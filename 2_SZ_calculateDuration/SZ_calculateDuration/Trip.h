#pragma once


#include<vector>
#include<map>

using namespace std;

class Trip
{
public:
	Trip(void);
	~Trip(void);

	void makeSubwayLineMap();											 //把subwayLineNumber这个map手动填满
	void readODTrip(ifstream &fin);										 //读取出行trip的起终点坐标和出发时间、到达时间等信息  
	double convertStringToDouble(string str1);							 //将读进来的string型坐标转化成可比较的double类型
	int convertTimeStringToInt(string str1);							 //将2017-04-05 19:23:38这样的string转化成int型的秒
	int extractTimeHour(string str1);									 //将2017-04-05 19:23:38这样的string中的19提取出来
	string extractSubwayLine(string str1);								 //输入换乘信息字段，输出换乘信息中起点紧接着的那个地铁线路，如果不是地铁就输出空
	double getTwoPointDistance(double x1,double y1,double x2,double y2); //求两点间的距离

	int get_tripSize();                                  //返回读进来的有效的分时间段的trip的个数

	void readBusStop();                                  //读取坐标,大概一万个坐标
	void makeStopStartCount();                           //看那一万个站点每个到底出发多少
	bool isSubwayStop(string str1);                      //输入一个站名，看是不是地铁站，是就返回真
	string extractSubwayName(string str1);               //输入地铁站名字，把后面的线路号标识和“站”字去掉，并直接加上线路的数字号，然后map

	void makeStopEndCount();                                  //看以终点为结束的六千个站点每个到底到达多少个


	void countTripCardIDMost();                               //数一下当天trip卡号重复次数最多的那个人，要是后面需要卡号众数的次数，就改成有返回值的
	void getTripDurationTime();                               //计算逗留时间，基本读完所有trip之后就能计算了
	string eraseSubwayLine(string str1);                      //输入"深圳北-5"，输出“深圳北”
	void addSuitableDurationTime();                           //分配逗留时间，主要给单独的trip和那些不回家新开了个地方的trip
	bool findSimilarTrip(int pos,vector<int> &vec);           //用来找pos位置（360万中的位置）的trip相似的trip，找到后把trip的ID（360万中的位置）放到vec中并返回真，找不到就直接返回假
	bool findSimilarTrip2(int pos,int wPos,vector<int> &vec); //用来嵌套在 findSimilarTrip函数里，函数多了一个1万站点中位置的参数
	bool proportionTrip(int pos,double &value);               //用来按照比例给分配逗留时间

	void writeInTheExistingFile();                            //把逗留时间写到已有的文件中

	void run();                                          //把read函数写在这个里面吧


private:

	map<string,string> subwayLineNumber;      //用<地铁二号线,-2>这样来索引
	int tripDay;                              //用来指示现在读到第几天了的一个全局变量

	vector<string> tripCardID;                //记录每条trip的卡号
	vector<string> OStopName;                 //记录trip起点的站名，起点站是地铁，并且把地铁的线路号加入到站名后面如：科苑站-2，表示起点是地铁二号线的科苑站
	vector<string> DStopName;                 //记录trip终点站名
	vector<double> OGrid_X;                    //起始站点的坐标信息分开存
	vector<double> OGrid_Y;
	vector<double> DGrid_X;                   //终止站点的坐标信息分开存
	vector<double> DGrid_Y;
	vector<double> getOnTime;                 //上下车时间
	vector<double> getOffTime;

	vector<double> tripDurationTime;          //trip的逗留时间，不一定每一个都有值。这个不是从记录里读出来的，后面要一下下算。可能要算两遍，第一遍算出直接的逗留时间，第二遍算必须要分配的逗留时间
	vector<double> tripDurationTime_v1;       //把未分配之前的逗留时间保存一份，后面用它来填充东西

	vector<int> oneWStopID;                       //一万个站点的那个站点的ID号，分马路对面和地铁线路的统计
	vector<double> oneWX;                         //一万个站点的那个站点的X坐标或是线段端点的X坐标
	vector<double> oneWY;                         //一万个站点的那个站点的Y坐标或是线段端点的Y坐标
	vector<string> oneWStopName;                  //一万个站点的那个站点的名字
	map<string,int> oneWStopNameToID;             //根据一万个站名来索引其所在的ID号
	vector<int> stopStartCount;                   //存储每个站点（分马路对面和地铁线路的统计）中的累积出发次数，这个向量大小和文件"merge_BusStation改进dbscan加地铁"的大小相同
	vector<vector<int>> stopStartTripIDInclude;   //二维向量，长度是一万多一点的站点名字的长度，每个站点会拥有一定量的trip，这里就直接把trip的具体编号push进来

	//上面的stopStartCount是以起点进行构建的，下面需要构建一波终点
	//感觉终点不用区分马路对面，因为终点到了他就完成trip了，但起点要分，马路对面和这面直接决定着他往两个不同的方向行进，出行意义不同
	vector<string> sixKStopName;                  //这六千个站名按照插入顺序把名字放进来
	map<string,int> sixKStopNameToID;             //根据一万个站名来索引其所在的ID号
	vector<int> stopEndCount;                     //以trip中所有的终点（不重复）构成终点站点集合，大概6000个,存储每个终点的累积到达次数
	vector<vector<int>> stopEndTripIDInclude;     //二维向量，长度是六千多长度，每个站点会拥有一定量的trip实际编号
};

