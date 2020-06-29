#include "Trip.h"

#include<iostream>
#include<fstream>
#include<sstream>
#include<math.h>
#include<iomanip>

#define MY_PI 3.1415926535898
using namespace std;

Trip::Trip(void)
{
	tripDay=2;
}

Trip::~Trip(void)
{
}

void Trip::makeSubwayLineMap()
{
	pair<map<string,string>::iterator,bool> Insert_Pair;
	Insert_Pair=subwayLineNumber.insert(pair<string,string>("地铁一号线","-1"));
	if(Insert_Pair.second==false)
	{
		cout<<"Subway line map insert failed, impossible!!!"<<endl;
	}
	Insert_Pair=subwayLineNumber.insert(pair<string,string>("地铁二号线","-2"));
	if(Insert_Pair.second==false)
	{
		cout<<"Subway line map insert failed, impossible!!!"<<endl;
	}
	Insert_Pair=subwayLineNumber.insert(pair<string,string>("地铁三号线","-3"));
	if(Insert_Pair.second==false)
	{
		cout<<"Subway line map insert failed, impossible!!!"<<endl;
	}
	Insert_Pair=subwayLineNumber.insert(pair<string,string>("地铁四号线","-4"));
	if(Insert_Pair.second==false)
	{
		cout<<"Subway line map insert failed, impossible!!!"<<endl;
	}
	Insert_Pair=subwayLineNumber.insert(pair<string,string>("地铁五号线","-5"));
	if(Insert_Pair.second==false)
	{
		cout<<"Subway line map insert failed, impossible!!!"<<endl;
	}

	Insert_Pair=subwayLineNumber.insert(pair<string,string>("地铁七号线","-7"));
	if(Insert_Pair.second==false)
	{
		cout<<"Subway line map insert failed, impossible!!!"<<endl;
	}
	Insert_Pair=subwayLineNumber.insert(pair<string,string>("地铁九号线","-9"));
	if(Insert_Pair.second==false)
	{
		cout<<"Subway line map insert failed, impossible!!!"<<endl;
	}
	Insert_Pair=subwayLineNumber.insert(pair<string,string>("地铁十一号线","-11"));
	if(Insert_Pair.second==false)
	{
		cout<<"Subway line map insert failed, impossible!!!"<<endl;
	}
}

void Trip::readODTrip(ifstream &fin)
{
	double sOX,sOY,sDX,sDY;                                          //为了与vector的名字区别出来，前面全部加了s，这些都是在读信息的时候用的中间值
	int tempOtime,tempDtime,tempOhour,tempDhour;                     //分别存储转换后的上下车秒数和小时数
	int stops,transfers;                                             //存储这次trip跨了多少个站点和换乘次数
	string OName,DName;                                              //存储trip起点和终点的名字
	string OSubwayLine;                                              //为了读取换乘信息的中间变量，为了确定出起点所在的地铁的线路号
	string tempTripID;                                               //暂时存trip的卡号
	
	string line;
	int times=1;                                                                    //看程序运行的速度
	double tStop=pow(10.0,7);                                                       //控制读多少行
	int countNight=0;                                                               //存储跨凌晨的trip次数
	int timeTooShortCount=0;                                                        //时间间隔太短或太长
	int number=0;                                                                   //累积行数
	while(getline(fin,line))    //一行一行的读 
	{
		if(line=="end,")
		{
			switch(tripDay)
			{
			case 2:
				{
					ifstream finTrip2("D:\\data\\深圳数据\\TRIP20180707\\CN\\20170406-Trip-statistics-2CN.csv");
					cout<<"now is the"<<tripDay<<"天"<<endl;
					tripDay++;
					//readODTrip(finTrip2);	
					finTrip2.close();
					break;
				}
			case 3:
				{
					ifstream finTrip3("D:\\data\\深圳数据\\TRIP20180707\\CN\\20170407-Trip-statistics-2CN.csv");     //4月7号是星期五
					cout<<"now is the"<<tripDay<<"day"<<endl;
					tripDay++;
					//readODTrip(finTrip3);
					finTrip3.close();
					break;
				}
			case 4:
				{
					ifstream finTrip4("D:\\data\\深圳数据\\TRIP20180707\\CN\\20170408-Trip-statistics-2CN.csv");    //4月8号是星期六
					cout<<"now is the"<<tripDay<<"day"<<endl;
					tripDay++;
					//readODTrip(finTrip4);
					finTrip4.close();
					break;
				}
			case 5:
				{
					ifstream finTrip5("D:\\data\\深圳数据\\TRIP20180707\\CN\\20170409-Trip-statistics-2CN.csv");
					cout<<"now is the"<<tripDay<<"day"<<endl;
					tripDay++;
					//readODTrip(finTrip5);
					finTrip5.close();
					break;
				}
			case 6:
				{
					ifstream finTrip6("D:\\data\\深圳数据\\TRIP20180707\\CN\\20170404-Trip-statistics-2CN.csv");
					cout<<"now is the"<<tripDay<<"day"<<endl;
					tripDay++;
					//readODTrip(finTrip6);
					finTrip6.close();
					break;
				}
			case 7:
				{
					ifstream finTrip7("D:\\data\\深圳数据\\TRIP20180707\\CN\\20170403-Trip-statistics-2CN.csv");//一次性读七天数据内存可能放不下
					cout<<"now is the"<<tripDay<<"day"<<endl;
					tripDay++;
					//readODTrip(finTrip7);
					finTrip7.close();
					break;
				}
			default:
				{
					cout<<"reading trip switch fails!!!!!!!!"<<endl;
					break;
				}
			}
			continue;
		}

		istringstream sin(line);   
		string field;
		int i=1;
		while (getline(sin,field,',')) 
		{
			if(i==1)          //只读第row列的数据，然后push_back到vector里
			{
				tempTripID=field;                                 //放trip的卡号进来， 
				i++;
				continue;
			}
			else if(i==2)          //只读第row列的数据，然后push_back到vector里
			{
				tempOtime=convertTimeStringToInt(field);     //放Otime进来
				tempOhour=extractTimeHour(field);            
				i++;
				continue;
			}
			else if(i==3)
			{
				OName=field;                           //放起点的站名进来
				i++;
				continue;
			}
			else if(i==4)
			{
				sOX=convertStringToDouble(field);     //放OX进来
				i++;
				continue;
			}
			else if(i==5)
			{
				sOY=convertStringToDouble(field);     //放OY进来
				i++;
				continue;
			}
			else if(i==6)
			{
				tempDtime=convertTimeStringToInt(field);     //放Dtime进来
				tempDhour=extractTimeHour(field);
				i++;
				continue;
			}
			else if(i==7)
			{
				DName=field;                           //放终点的站名进来
				i++;
				continue;
			}
			else if(i==8)
			{
				sDX=convertStringToDouble(field);     //放DX进来
				i++;
				continue;
			}
			else if(i==9)
			{
				sDY=convertStringToDouble(field);     //放DY进来
				i++;
				//break;
				continue;
			}
			else if(i==11)
			{
				OSubwayLine=field;    
				OSubwayLine=extractSubwayLine(OSubwayLine);
				OSubwayLine=subwayLineNumber[OSubwayLine];
				i++;
				continue;
			}
			else if(i==13)
			{
				stops=int(convertStringToDouble(field));     
				i++;
				continue;
			}
			else if(i==14)
			{
				transfers=int(convertStringToDouble(field));
				if(transfers>5)     //消除异常换乘次数，如果换乘了超过5次，就默认他换了5次，不能再大了
				{
					transfers=5;
				}
				i++;
				break;
			}
			else
			{
				i++;
				continue;
			}	
		}
		number++;                                                             //累积行数

		if(tempDhour<tempOhour)                                               //要是有下车时间早于上车时间的trip，就跳过吧，这个还是有一定数量的
		{
			countNight++; 
			cout<<"第"<<number<<"行有时间先后问题"<<endl;
			continue;                                                   
		}
		
		//这里是控制读取进来的数据的时间段
		if(tempOhour>=0&&tempOhour<=24)                                   //这里分时段push_back到vector中,不想分时段就改一下阈值就好
		{
			if(tempDtime-tempOtime<200||tempDtime-tempOtime>12600)       //如果是小于0的时间间隔或者是极短（200s）的时间间隔就不要输进来了
			{                                                            //如果起终点时间超过3.5h那也不要了
				timeTooShortCount++;
				//continue;
			}
			tripCardID.push_back(tempTripID);                            //把trip的卡号放进来 
			DStopName.push_back(DName); //把终点站名加进来，但不加线路号，后面判断trip的O和下个trip的D是否相同的时候，把O名字后面的线路号去掉再比较
			DGrid_X.push_back(sDX);                                      //把终点的坐标放进来
			DGrid_Y.push_back(sDY); 
			getOnTime.push_back(tempOtime);                              //上下车的时间push进来
			getOffTime.push_back(tempDtime);

			OStopName.push_back(OName+OSubwayLine);                      //把站名也放进来,并且后面加个线路号
			OGrid_X.push_back(sOX);                                         //把起始站点的坐标放进来
			OGrid_Y.push_back(sOY); 
		}

		if(number==times*100000)
		{
			cout<<number<<endl;     //到360w的时候就出问题?
			times++;
		}
		if(number>2.0*tStop)     //如果number过大就                                                           
		{
			cout<<"break in advance"<<endl;
			break;
		}
	}
	cout<<"分时段下push_back到vector中总的trip数量："<<tripCardID.size()<<"    读了这么多行："<<number<<endl;
	cout<<"下车时间反而还在前了的个数，push不到trip里了："<<countNight<<endl;
	cout<<"上下车时间间隔太短或太长，push不到trip里了："<<timeTooShortCount<<endl;
	cout<<"trip读取完毕！！！！"<<endl<<endl;

	cout<<"trip按照起点站名的累积次数统计完毕！！！！"<<endl<<endl;

	countTripCardIDMost();                         //看一下到底卡号最多是重复多少次
	getTripDurationTime();                         //计算一下逗留时间
}

double Trip::convertStringToDouble(string str1)
{
	//尝试string转double
	double n1;
	const char* ch= str1.c_str();
	n1=atof(ch);                   //如果是英文字符串，转过来就是0，而不是一个double的数
	return n1;
}

int Trip::convertTimeStringToInt(string str1)
{
	double second=0;
	istringstream sin(str1);   
	string field;
	int i=0;
	while (getline(sin,field,' ')) 
	{
		if(i==1)     //因为时间在第二个位置，第一个位置是年月日
		{
			istringstream sin(field);
			string field2;
			int j=0;
			while (getline(sin,field2,':'))
			{
				if(j==0)
				{
					double seeHour=convertStringToDouble(field2);                     //初步判断读进来的小时数
					if(seeHour<5 && seeHour>=0)
					{
						second=second+(convertStringToDouble(field2)+24)*3600;
					}
					else
					{
						second=second+convertStringToDouble(field2)*3600;   //先读到小时，换算成秒进行累加
					}

					j++;
					continue;
				}
				if(j==1)
				{
					second=second+convertStringToDouble(field2)*60;    //二读分钟，换算成秒进行累加
					j++;
					continue;
				}
				if(j==2)
				{
					second=second+convertStringToDouble(field2);      //直接读到秒
					j++; 
					break;
				}
			}
		}
		i++;
	}
	return int(second);
}

int Trip::extractTimeHour(string str1)
{
	int hour;
	istringstream sin(str1);   
	string field;
	int i=0;
	while (getline(sin,field,' ')) 
	{
		if(i==1)
		{
			istringstream sin(field);
			string field2;
			while (getline(sin,field2,':'))
			{		
				hour=int(convertStringToDouble(field2));   //先读到小时，
				break;
			}
		}
		i++;
	}

	return hour;
}

string Trip::extractSubwayLine(string str1)
{
	string sub;                        //存储最后输出的地铁名字字段
	//参考读时间的方法
	istringstream sin(str1);   
	string field;
	int i=0;
	while (getline(sin,field,'-')) 
	{
		if(i==1)     //因为时间在第二个位置，第一个位置是年月日
		{
			sub=field;
		}
		i++;
	}
	return sub;
}

double Trip::getTwoPointDistance(double x1,double y1,double x2,double y2)
{
	return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

int Trip::get_tripSize()
{
	return int(tripCardID.size());
}

void Trip::readBusStop()
{
	string name;        //存站点名字的中间变量
	int ID=0;           //存站点的ID号，这里待读取的数据中没有，一条一条累加即可
	double X,Y;         //存坐标的中间变量
	ifstream finBus("D:\\data\\深圳数据\\修剪数据1\\merge_BusStation改进dbscan加地铁.csv");   //存有合并后的站点数据
	string line;                                   //当然这里的合并后的站点也存在一定问题：站点在研究区外等
	ifstream &fin=finBus;
	while(getline(fin,line))    //一行一行的读 
	{
		istringstream sin(line);   
		string field;
		int i=1;
		while (getline(sin,field,','))   //用vector读取时，这个CSV文件的字段超过5个时可能会出错
		{
			if(i==1)          //控制读哪一列
			{
				name=field;    
				i++;
				continue;
			}
			else if(i==3)
			{
				X=convertStringToDouble(field);
				i++;
				continue;
			}
			else if(i==4)
			{
				Y=convertStringToDouble(field);
				i++;
				break;
			}
			else
			{
				i++;
				continue;
			}	
		}
		ID++;
		oneWStopID.push_back(ID);
		oneWStopName.push_back(name);
		oneWX.push_back(X);
		oneWY.push_back(Y);
	}
	finBus.close();
	cout<<"read大概1万多完成了"<<endl;
}

void Trip::makeStopStartCount()
{
	vector<int> tempStop;                                    //为了初始化stopStartTripIDInclude使用的
	pair<map<string,int>::iterator,bool> Insert_Pair;
	for(unsigned int i=0;i<oneWStopName.size();i++)          //for的是一万个站点
	{
		stopStartTripIDInclude.push_back(tempStop);          //先push一个空的进来
		stopStartCount.push_back(0);												//先初始化为0，后面累加用
		Insert_Pair=oneWStopNameToID.insert(pair<string,int>(oneWStopName[i],i));   //构建利用站点名字索引其所在的位置号，从0开始的
		if(Insert_Pair.second==false)
		{
			cout<<"oneWStopNameToID怎么可能差不进来！！！"<<endl;
		}
	}

	int noFind=0;                                           //累积那些trip里有但一万个站点里没有的情况
	int yesFind=0;                                          //累积那些trip里有一万个站点里也有的情况
	int badSubwayFind=0;                                    //累积那些trip里有的地铁站点但一万个里没有的，主要是trip里这些地铁站点可能是坏的（线路错了）
	int times=1;                                            //看执行的速度
	for(unsigned int i=0;i<OStopName.size();i++)           //for的所有的trip，这个就很大了
	{
		//先判断是不是地铁站点，是就去掉后面“-数字”和“站”字并加一个线路数来用map匹配
		//如果不是地铁站点，那就直接map，map不到就加a和b来map
		if(isSubwayStop(OStopName[i]))                       //如果是地铁站点的名字
		{
			string tempSub=OStopName[i];                     //后面输到函数里去要改变它,存去了“-数字”和“站”字的地铁名字
			tempSub=extractSubwayName(tempSub);              //把地铁站名去掉了站字，并加上了不带-的数字
			if(oneWStopNameToID.count(tempSub)!=0)           //再判断此时那个一万站点的map中有没有这个站点存在
			{
				stopStartCount[oneWStopNameToID[tempSub]]++;                       //类似：用 益田3访问到是一万个中的第几，然后在stopStartCount上累加
				stopStartTripIDInclude[oneWStopNameToID[tempSub]].push_back(i);    //把trip的编号添加进来
				yesFind++;
			}
			else
			{
				//cout<<"出现了明明是trip的地铁站，但是一万个里没有的情况："<<tempSub<<endl;
				badSubwayFind++;
				noFind++;
			}
		}
		else                                                 //如果是公交站点的名字
		{
			if(oneWStopNameToID.count(OStopName[i])!=0)               //先在不加a和b的情况下，直接判断一万个站点里有没有这个站点名
			{
				stopStartCount[oneWStopNameToID[OStopName[i]]]++;                       //类似：用 益田3访问到是一万个中的第几，然后在stopStartCount上累加
				stopStartTripIDInclude[oneWStopNameToID[OStopName[i]]].push_back(i);    //把trip的编号添加进来
				yesFind++;
			}
			else                                                      //如果直接map没有，那就加个a和b来判断
			{
				if(oneWStopNameToID.count(OStopName[i]+"a")!=0 && oneWStopNameToID.count(OStopName[i]+"b")!=0)       //理论上来说，+a有，+b肯定也有
				{
					//分别求trip的坐标到名字为站点a的距离和到名字为站点b的距离
					double d1=getTwoPointDistance(OGrid_X[i],OGrid_Y[i],oneWX[oneWStopNameToID[OStopName[i]+"a"]],oneWY[oneWStopNameToID[OStopName[i]+"a"]]);
					double d2=getTwoPointDistance(OGrid_X[i],OGrid_Y[i],oneWX[oneWStopNameToID[OStopName[i]+"b"]],oneWY[oneWStopNameToID[OStopName[i]+"b"]]);
					if(d1<=d2)               //如果离名字为站点a更近
					{
						stopStartCount[oneWStopNameToID[OStopName[i]+"a"]]++;
						stopStartTripIDInclude[oneWStopNameToID[OStopName[i]+"a"]].push_back(i);    //把trip的编号添加进来
						yesFind++;
					}
					else
					{
						stopStartCount[oneWStopNameToID[OStopName[i]+"b"]]++;
						stopStartTripIDInclude[oneWStopNameToID[OStopName[i]+"b"]].push_back(i);    //把trip的编号添加进来
						yesFind++;
					}
				}
				else                             //加a和加b后都没有，表示这个站点可能就在一万站点里没有，可能是比较新的站点
				{
					noFind++;
				}
			}
		}
		if(i==times*100000)
		{
			times++;
			cout<<i<<endl;
		}
	}
	cout<<"最后trip的数量（千万级）应该和 noFind + yesFind 的值相同"<<endl;
	cout<<"yesFind的值是： "<<yesFind<<endl;
	cout<<"noFind的值是： "<<noFind<<endl;
	cout<<"badSubwayFind的值是： "<<badSubwayFind<<endl;
	cout<<"trip的数量是： "<<OStopName.size()<<endl;
	cout<<"看看我的map有没有map坏："<<oneWStopNameToID.size()<<endl;

	//检查push进去的tripID号有没有问题
	int sumTripID=0;                                           //看一下每个站点push进来的总的次数与yesFind是否一致
	for(unsigned int i=0;i<oneWStopName.size();i++)          //for的是一万个站点
	{
		sumTripID=sumTripID+stopStartTripIDInclude[i].size();
		if(stopStartTripIDInclude[i].size()!=stopStartCount[i])
		{
			cout<<"push进去的trip的ID号和统计的count居然不相等！！！  "<<stopStartTripIDInclude[i].size()<<" --  "<<stopStartCount[i]<<endl;
		}
	}
	cout<<"看看我push进去的tripID号有没有问题sumTripID："<<sumTripID<<endl;
}

bool Trip::isSubwayStop(string str1)
{
	//先判断长度够不够，要不然后面会出错
	int lastP=str1.size()-1;                             //定义这个字符串的最后一个位置
	if(str1.size()<3)                                    //如果这个字符串长度过小，下面的就不用考虑了
	{
		return false;
	}
	if(str1[lastP]=='1' || str1[lastP]=='2' || str1[lastP]=='3' || str1[lastP]=='4' || str1[lastP]=='5' || str1[lastP]=='7'|| str1[lastP]=='9') //先判断最后一个是不是数字
	{
		if(str1[lastP-1]=='-' || str1[lastP-1]=='1')     //在最后一个是数字的情况下，倒数第二个还是 - 或者 1 ，那么肯定就是地铁站点了
		{
			return true;
		}
		else
		{
			cout<<"最后一个都是数字了，但倒数第二个又不是了："<<str1<<endl;
			return false;
		}
	}
	else
	{
		return false;
	}
}

string Trip::extractSubwayName(string str1)
{
	string finalString;
	int lastP=str1.size()-1;                             //定义这个字符串的最后一个位置
	string tempStr;
	string zhan="站";
	if(str1[lastP-1]=='-')
	{
		tempStr=str1.substr(str1.size()-4,2);                    //提取那个字看是不是“站”字
		if(tempStr==zhan)                                        //如果是站字，那就去掉它
		{
			finalString=str1.substr(0,str1.size()-4);            //保留“站”字之前的内容
			return finalString+str1[lastP];                      //加上那个数字，最后可能从   益田站-3  变成  益田3
		}
		else                        //如果不是站字，那就直接加上线路号后输出
		{
			finalString=str1.substr(0,str1.size()-2);
			return finalString+str1[lastP]; 
		}
	}
	else                           //这里默认不是‘-’就是‘1’，因为前面已经千真万确判断出来这是个地铁站点名字了
	{
		if(str1[lastP-1]!='1')
		{
			cout<<"怎么可能倒数第二个字符不是1："<<str1<<endl;
		}
		tempStr=str1.substr(str1.size()-5,2);                    //提取那个字看是不是“站”字
		if(tempStr==zhan)                                        //如果是站字，那就去掉它
		{
			finalString=str1.substr(0,str1.size()-5);            //保留“站”字之前的内容
			return finalString+str1[lastP-1]+str1[lastP];        //加上那个数字，最后可能从   益田站-11  变成  益田11
		}
		else                        //如果不是站字，那就直接加上线路号后输出
		{
			finalString=str1.substr(0,str1.size()-3);
			return finalString+str1[lastP-1]+str1[lastP]; 
		}
	}
}

void Trip::makeStopEndCount()
{
	int number=0;                                           //指示到底插了多少个
	vector<int> tempStop;                                    //为了初始化stopStartTripIDInclude使用的
	pair<map<string,int>::iterator,bool> Insert_Pair;
	for(unsigned int i=0;i<tripCardID.size();i++)          //for的是360万条trip
	{
													//先初始化为0，后面累加用
		Insert_Pair=sixKStopNameToID.insert(pair<string,int>(DStopName[i],number));   //构建利用站点名字索引其所在的位置号，从0开始的
		if(Insert_Pair.second==true)
		{
			sixKStopName.push_back(DStopName[i]);              //如果插入了站名，那就也push进来
			stopEndTripIDInclude.push_back(tempStop);          //先push一个空的进来
			stopEndCount.push_back(0);	
			number++;
		}
	}
	cout<<"二者应该要相同     number是："<<number<<"    stopEndCount的尺寸："<<stopEndCount.size()<<"    sixKStopName的尺寸："<<sixKStopName.size()<<endl;

	for(unsigned int i=0;i<tripCardID.size();i++)                              //for的是360万条trip
	{
		if(sixKStopNameToID.count(DStopName[i])!=0)                            //如果trip里的确有这个终点名字
		{
			stopEndCount[sixKStopNameToID[DStopName[i]]]++;                    //这个名字处的ID号的位置++
			stopEndTripIDInclude[sixKStopNameToID[DStopName[i]]].push_back(i); //把实际的trip的ID号放进来
		}
		else
		{
			cout<<"草泥马居然没有是什么鬼！！"<<endl;
		}
	}

	//输出小看一下对不对
	int sumEnd=0;
	ofstream outfile1;
	outfile1.open("D:\\data\\深圳数据\\修剪数据3\\stopEndCount.csv");
	for(unsigned int i=0;i<stopEndCount.size();i++)
	{
		outfile1<<fixed<<setprecision(6)<<i<<","<<sixKStopName[i]<<","<<stopEndCount[i]<<","<<stopEndTripIDInclude[i].size()<<endl;
		sumEnd+=stopEndCount[i];
	}
	outfile1.close();
	cout<<sumEnd<<"   总共的trip是： "<<tripCardID.size()<<endl;
}

void Trip::countTripCardIDMost()   //下面这几个函数是用来求逗留时间的
{
	if(tripCardID.size()!=get_tripSize())
	{
		cout<<"读进来的trip的IDcard的号居然不对?"<<endl;
	}

	int tempRepeat=1;                                         //暂时定义卡号重复的次数为1
	int repeatPos=0;                                          //记录众数卡号的位置
	int repeatFinal=1;
	for(unsigned int i=0;i<tripCardID.size()-1;i++)             //for一遍trip的card的个数
	{
		if(tripCardID[i]==tripCardID[i+1])
		{
			tempRepeat++;
		}
		else
		{
			if(tempRepeat>repeatFinal)
			{
				repeatFinal=tempRepeat;
				repeatPos=i;
				cout<<"重复次数最多的卡号是："<<tripCardID[i]<<endl;
			}
			tempRepeat=1;
		}
		//cout<<i<<"  当前的repeatFinal："<<repeatFinal<<"次    当前的tempRepeat："<<tempRepeat<<endl;
		//system("pause");
	}
	cout<<"重复次数最多的卡号是："<<repeatFinal<<"次    他的位置(因为去除了异常，所以位置相比原始数据所在的行偏小)在："<<repeatPos<<endl;
	cout<<endl<<endl;
}

void Trip::getTripDurationTime()
{
	//先初始化一波逗留时间数组
	for(unsigned int i=0;i<tripCardID.size();i++)
	{
		tripDurationTime.push_back(0);                                //先把每个逗留时间全弄成0
	}

	//开始第一遍直接计算时间差逗留时间的，需要分配的换到第二遍计算
	for(unsigned int i=0;i<tripCardID.size();i++)                       //for的是所有trip
	{
		if(i<tripCardID.size()-1 && tripCardID[i]==tripCardID[i+1])                              //如果当前卡号与下一条卡号相同
		{
			if(DStopName[i]==eraseSubwayLine(OStopName[i+1]))                              //如果当前trip的D和下趟trip的O相同，那么直接算时间差
			{
				tripDurationTime[i]=getOnTime[i+1]-getOffTime[i];
			}
			else if(getTwoPointDistance(DGrid_X[i],DGrid_Y[i],OGrid_X[i+1],OGrid_Y[i+1])<2000)      //如果当前trip的D和下趟trip的O其实相距不远，那也可以直接算时间差
			{
				tripDurationTime[i]=getOnTime[i+1]-getOffTime[i];
				if(tripDurationTime[i]>2000)                                                //如果直接时间差大于2000，证明他还是在这个地方停留了的，逛街啥了的
				{
					tripDurationTime[i]=tripDurationTime[i]-getTwoPointDistance(DGrid_X[i],DGrid_Y[i],OGrid_X[i+1],OGrid_Y[i+1])/1.0;    //减去他步行到另一个站点的时间
					tripDurationTime[i]=int(tripDurationTime[i])+0.2;                       //相当于给它后面标记一个0.2，后面就知道哪些是这一个类别算出的逗留时间
				}
			}
			else                                                                  //如果卡号相同，但当前trip的D和下趟trip的O还相差的比较远，说明他硬走过去？或者打的过去的或者共享单车过去的
			{
				//这里是要计算，这里可能要考虑个行车距离的时间估计?
				tripDurationTime[i]=getOnTime[i+1]-getOffTime[i];                                      //他的逗留时间死都不会超过上次trip的D与下次trip的O的时间间隔，后面要进一步减去一部分时间                                           
				double tempDis=getTwoPointDistance(DGrid_X[i],DGrid_Y[i],OGrid_X[i+1],OGrid_Y[i+1]);   //得到上次trip的D与下次trip的O的直线距离
				tripDurationTime[i]=tripDurationTime[i]-(tempDis*1.5)/8.0;                             //假设公交运行速度为8米/s，即28.8km/h，假设直线距离乘以1.2变为路网距离
				if(tripDurationTime[i]<0)
				{
					tripDurationTime[i]=180.6;                                                          //如果上面减得成了负值，下面就给他弄成停留了3分钟吧
				}
			}
		}
		else                                                             //如果当前卡号与下一条不同，那可能它是单独的一条或者它是多条相同的最后一条,以及整个trip的最后一条也会跳到这里来
		{
			if(i>=1 && tripCardID[i-1]==tripCardID[i])                    //如果当前卡号与上一条卡号相同，则证明是多条trip的最后一条
			{
				int back_i=i;
				while(tripCardID[back_i-1]==tripCardID[back_i])          //回溯找到多条trip的第一条的卡号的i
				{
					back_i--;
				}
				if(DStopName[i]==eraseSubwayLine(OStopName[back_i]))   //如果当前卡号的最后一条trip的D与第一条的O相同，证明他回家了，就不计算这次trip的逗留了
				{
					tripDurationTime[i]=0.01;                            //赋值0.01与0区别开来
				}
				else if(getTwoPointDistance(DGrid_X[i],DGrid_Y[i],OGrid_X[back_i],OGrid_Y[back_i])<2000)   //回家的终点和之前出发的起点虽然名字不同，但离得很近也可以说他回家了
				{
					tripDurationTime[i]=0.02;                            //赋值0.02与0和0.01区别开来
				}
				else                                                      //回家的终点和之前出发的起点相差较远，说明他可能没回家，开始了新的trip
				{
					//这个trip就相当于那种没提示的trip了，可能要单独处理，即判断它与其trip的相似性，给他分配一个逗留时间
					tripDurationTime[i]=0.66;
				}
			}
			else                                                         //如果卡号与上一条不同且也与下一条不同，那就是单独的（总trip第一条单独和最后一条单独都在这里）
			{
				//这个trip就相当于那种没提示的trip了，可能要单独处理，即判断它与其trip的相似性，给他分配一个逗留时间
				tripDurationTime[i]=0.77;
			}
		}
	}

	//上面算完了所有的逗留时间，下面把他们输出到文件中看看
	int cMe9=0;
	int cMe1=0;
	int cMe2=0;
	int cMe66=0;
	int cMe77=0;
	int cMe=0;                          //分别看一下每类里有多少
	int cMe0=0;
	ofstream outfile1;
	outfile1.open("D:\\data\\深圳数据\\修剪数据3\\tripDurationTime.csv");
	for(unsigned int i=0;i<tripDurationTime.size();i++)                      //for的是类别的数目
	{
		if(tripDurationTime[i]<0)
		{
			cMe0++;
			tripDurationTime[i]=0.985;                                       //把减的太小的赋值为0.985
		}
		else if(tripDurationTime[i]==180.6)
		{
			cMe9++;
		}
		else if(tripDurationTime[i]==0.01)
		{
			cMe1++;
		}
		else if(tripDurationTime[i]==0.02)
		{
			cMe2++;
		}
		else if(tripDurationTime[i]==0.66)
		{
			cMe66++;
		}
		else if(tripDurationTime[i]==0.77)
		{
			cMe77++;
		}
		else
		{
			cMe++;
		}
		outfile1<<fixed<<setprecision(6)<<i<<","<<tripCardID[i]<<","<<tripDurationTime[i]<<endl;
	}
	outfile1.close();
	cout<<"重复次数小于0的："<<cMe0<<"次"<<endl;
	cout<<"重复次数180.6："<<cMe9<<"次"<<endl;
	cout<<"重复次数0.01："<<cMe1<<"次"<<endl;
	cout<<"重复次数0.02："<<cMe2<<"次"<<endl;
	cout<<"重复次数0.66："<<cMe66<<"次"<<endl;
	cout<<"重复次数0.77："<<cMe77<<"次"<<endl;
	cout<<"重复次数正常的："<<cMe<<"次"<<endl;
	cout<<"合计： "<<cMe9+cMe1+cMe2+cMe66+cMe77+cMe<<endl;
}

string Trip::eraseSubwayLine(string str1)
{
	string sub;                        //存储最后输出的地铁名字字段
	//参考读时间的方法
	istringstream sin(str1);   
	string field;
	int i=0;
	while (getline(sin,field,'-')) 
	{
		if(i==0)     //“深圳北-5”，将“深圳北”提取出来
		{
			sub=field;
		}
		i++;
	}
	return sub;
}

void Trip::addSuitableDurationTime()
{
	if(tripDurationTime.size()!=tripCardID.size())
	{
		cout<<"曹尼玛还玩个鬼"<<endl;
		system("pause");
	}
	//由于下面的tripDurationTime会慢慢改变，所以把最初的tripDurationTime保留一份
	for(unsigned int i=0;i<tripDurationTime.size();i++) 
	{
		tripDurationTime_v1.push_back(tripDurationTime[i]);
	}
	if(tripDurationTime.size()!=tripDurationTime_v1.size())
	{
		cout<<"曹尼玛还玩个鬼"<<endl;
		system("pause");
	}
	cout<<"看看逗留时间数组的大小"<<tripDurationTime_v1.size()<<endl;

	//下面开始正式分配
	int chao66=0;                      //分别看一下66和77两个分支中超过理论最大逗留时间的个数
	int chao77=0;
	int noProportion66=0;                //看一下按比例都他妈分配不下去的有多少
	int noProportion77=0;
	for(unsigned int i=0;i<tripDurationTime.size();i++)                  //for的是所有trip,也就是所有的逗留时间
	{
		if(tripDurationTime[i]!=0.66 && tripDurationTime[i]!=0.77)                    //如果既不是单独卡号的trip也不是不回家的trip，那后面其实不用分配，跳过就好           
		{
			continue;
		}
		if(tripDurationTime[i]==0.66)                              //如果是不回家的卡号，一般可能是下午或晚上的trip，逗留时间可以用他到达的时间和晚上12点卡一下
		{
			vector<int> similarTripID;                             //用find函数找一下相似的trip，能找到就直接分配，找不到就按终点的相似性来分配
			if(findSimilarTrip(i,similarTripID))                   //运行findSimilarTrip函数来找
			{
				double sumDuration=0;                              //把找到的完全相似的trip的逗留时间累加起来，后面平均
				for(unsigned int j=0;j<similarTripID.size();j++)
				{
					sumDuration=sumDuration+tripDurationTime_v1[similarTripID[j]];  //相似的逗留时间累加起来
				}
				tripDurationTime[i]=sumDuration/double(similarTripID.size()); //用相似trip平均逗留时间，给i次trip分一个合理逗留时间
				double maxDurationTime=24*3600-getOffTime[i];                 //作为检查，假如下午到那个地方，他的逗留时间最多不会到晚上12点
				if(tripDurationTime[i]>maxDurationTime)                       //如果超过了这个理论最大逗留时间，可能就有问题了
				{
					cout<<"他妈的超了，下午到，逗留时间还能到凌晨？   "<<i<<"   "<<tripDurationTime[i]<<"     "<<0.66<<endl;
					cout<<"相似的有多少个   "<<similarTripID.size()<<"   总："<<sumDuration<<"     "<<0.66<<endl;
					//system("pause");
					tripDurationTime[i]=maxDurationTime;
					chao66++;
				}
			}
			else
			{
				//如果没找到完全相似的，可能要以终点逗留时间比例来分配
				double tempDuration=0;
				if(proportionTrip(i,tempDuration))
				{
					tripDurationTime[i]=tempDuration;
				}
				else
				{
					//连比例都没有他妈的
					noProportion66++;
				}
			}
		}
		else                                                       //如果是卡号只有一次的trip
		{
			vector<int> similarTripID;                             //用find函数找一下相似的trip，能找到就直接分配，找不到就按终点的相似性来分配
			if(findSimilarTrip(i,similarTripID))                   //运行findSimilarTrip函数来找
			{
				double sumDuration=0;                              //把找到的完全相似的trip的逗留时间累加起来，后面平均
				for(unsigned int j=0;j<similarTripID.size();j++)
				{
					sumDuration=sumDuration+tripDurationTime_v1[similarTripID[j]];  //相似的逗留时间累加起来
				}
				tripDurationTime[i]=sumDuration/double(similarTripID.size()); //用相似trip平均逗留时间，给i次trip分一个合理逗留时间
				double maxDurationTime=24*3600-getOffTime[i];                 //作为检查，假如下午到那个地方，他的逗留时间最多不会到晚上12点
				if(tripDurationTime[i]>maxDurationTime)                       //如果超过了这个理论最大逗留时间，可能就有问题了
				{
					cout<<"他妈的超了，下午到，逗留时间还能到凌晨？   "<<i<<"   "<<tripDurationTime[i]<<"     "<<0.77<<endl;
					cout<<"相似的有多少个   "<<similarTripID.size()<<"   总："<<sumDuration<<"     "<<0.77<<endl;
					//system("pause");
					tripDurationTime[i]=maxDurationTime;
					chao77++;
				}
			}
			else
			{
				//如果没找到完全相似的，可能要以终点逗留时间比例来分配
				double tempDuration=0;
				if(proportionTrip(i,tempDuration))
				{
					tripDurationTime[i]=tempDuration;
				}
				else
				{
					//连比例都没有他妈的
					noProportion77++;
				}
			}
		}
	}
	//上面就分配完毕了，下面输出检查一波
	int cMe9=0;
	int cMe1=0;
	int cMe2=0;
	int cMe66=0;
	int cMe77=0;
	int cMe=0;                          //分别看一下每类里有多少
	int cMe0=0;
	ofstream outfile1;
	outfile1.open("D:\\data\\深圳数据\\修剪数据3\\tripDurationTime2.csv");
	for(unsigned int i=0;i<tripDurationTime.size();i++)                      //for的是类别的数目
	{
		if(tripDurationTime[i]<0)
		{
			cMe0++;
			tripDurationTime[i]=0.985;                                       //把减的太小的赋值为0.985
		}
		else if(tripDurationTime[i]==180.6)
		{
			cMe9++;
		}
		else if(tripDurationTime[i]==0.01)
		{
			cMe1++;
		}
		else if(tripDurationTime[i]==0.02)
		{
			cMe2++;
		}
		else if(tripDurationTime[i]==0.66)
		{
			cMe66++;
		}
		else if(tripDurationTime[i]==0.77)
		{
			cMe77++;
		}
		else
		{
			cMe++;
		}
		outfile1<<fixed<<setprecision(6)<<i<<","<<tripCardID[i]<<","<<tripDurationTime[i]<<endl;
	}
	outfile1.close();
	cout<<"重复次数小于0的："<<cMe0<<"次"<<endl;
	cout<<"重复次数180.6："<<cMe9<<"次"<<endl;         //之所以会变多，是因为二次分配的时候会分配到
	cout<<"重复次数0.01："<<cMe1<<"次"<<endl;
	cout<<"重复次数0.02："<<cMe2<<"次"<<endl;
	cout<<"重复次数0.66："<<cMe66<<"次"<<endl;
	cout<<"重复次数0.77："<<cMe77<<"次"<<endl;
	cout<<"重复次数正常的："<<cMe<<"次"<<endl;
	cout<<"合计： "<<cMe9+cMe1+cMe2+cMe66+cMe77+cMe<<endl;    //这里没加cMe0，上面的统计也是
	cout<<"超66的："<<chao66<<"    超77的："<<chao77<<endl;
	cout<<"noProportion66的："<<noProportion66<<"    noProportion77的："<<noProportion77<<endl;

	int A[5];                                                                      //初始化5个逗留时间分类：0-2h，2-4h，4-8h，8-12h，12-24h；
	for(int i=0;i<5;i++)
	{
		A[i]=0;
	}
	for(unsigned int i=0;i<tripDurationTime.size();i++)
	{
		if(tripDurationTime[i]==3600.123)
		{
			A[0]++;
		}
		else if(tripDurationTime[i]==10800.123)
		{
			A[1]++;
		}
		else if(tripDurationTime[i]==21600.123)
		{
			A[2]++;
		}
		else if(tripDurationTime[i]==36000.123)
		{
			A[3]++;
		}
		else if(tripDurationTime[i]==64800.123)
		{
			A[4]++;
		}
		else
		{
			continue;
		}
	}
	for(int i=0;i<5;i++)
	{
		cout<<A[i]<<endl;
	}
}

bool Trip::findSimilarTrip(int pos,vector<int> &vec)
{
	if(isSubwayStop(OStopName[pos]))                       //看这pos次trip的起点是哪里,如果是地铁站点的名字
	{
		string tempSub=OStopName[pos];                     //后面输到函数里去要改变它,存去了“-数字”和“站”字的地铁名字
		tempSub=extractSubwayName(tempSub);              //把地铁站名去掉了站字，并加上了不带-的数字
		if(oneWStopNameToID.count(tempSub)!=0)           //再判断此时那个一万站点的map中有没有这个站点存在
		{
			int tripStartID=oneWStopNameToID[tempSub];                       //类似：用 益田3访问到是一万个中的第几，然后在stopStartTripIDInclude中进一步找相似的
			return findSimilarTrip2(pos,tripStartID,vec);                    //严格按照相似性（时间段相同，出发位置相同）来找，找完返回真或假
		}
		else                                              //表示没找到这个地铁站名字
		{
			return false;
		}
	}
	else                                                 //如果是公交站点的名字
	{
		if(oneWStopNameToID.count(OStopName[pos])!=0)               //先在不加a和b的情况下，直接判断一万个站点里有没有这个站点名
		{
			int tripStartID=oneWStopNameToID[OStopName[pos]];                       //类似：用 益田3访问到是一万个中的第几，然后在stopStartTripIDInclude中进一步找相似的
			return findSimilarTrip2(pos,tripStartID,vec);
		}
		else                                                      //如果直接map没有，那就加个a和b来判断
		{
			if(oneWStopNameToID.count(OStopName[pos]+"a")!=0 && oneWStopNameToID.count(OStopName[pos]+"b")!=0)       //理论上来说，+a有，+b肯定也有
			{
				//分别求trip的坐标到名字为站点a的距离和到名字为站点b的距离
				double d1=getTwoPointDistance(OGrid_X[pos],OGrid_Y[pos],oneWX[oneWStopNameToID[OStopName[pos]+"a"]],oneWY[oneWStopNameToID[OStopName[pos]+"a"]]);
				double d2=getTwoPointDistance(OGrid_X[pos],OGrid_Y[pos],oneWX[oneWStopNameToID[OStopName[pos]+"b"]],oneWY[oneWStopNameToID[OStopName[pos]+"b"]]);
				if(d1<=d2)               //如果离名字为站点a更近
				{
					int tripStartID=oneWStopNameToID[OStopName[pos]+"a"];
					return findSimilarTrip2(pos,tripStartID,vec);
				}
				else
				{
					int tripStartID=oneWStopNameToID[OStopName[pos]+"b"];
					return findSimilarTrip2(pos,tripStartID,vec);
				}
			}
			else                             //加a和加b后都没有，表示这个站点可能就在一万站点里没有，可能是比较新的站点
			{
				return false;;
			}
		}
	}
}

bool Trip::findSimilarTrip2(int pos,int wPos,vector<int> &vec)
{
	for(unsigned int i=0;i<stopStartTripIDInclude[wPos].size();i++)   //for的是pos处trip起点站点拥有的出发量trip次数
	{
		double timePeriod1=abs(getOffTime[i]-getOffTime[pos]);                                   //计算这些trip的下车相隔时间，越小表示和pos的trip越相似
		double timePeriod2=abs(getOnTime[i]-getOnTime[pos]);                                     //计算这些trip的上车相隔时间，越小表示和pos的trip越相似
		double DSimilar=getTwoPointDistance(DGrid_X[i],DGrid_Y[i],DGrid_X[pos],DGrid_Y[pos]);    //计算这些trip的D与pos的trip的D的距离，越小表示和pos的trip越相似
		if(timePeriod1<2400 && timePeriod2<2400 && DSimilar<1000 && tripDurationTime_v1[i]>1) //如果同时间段，去的D也和pos的相同，并且原始也有逗留时间，  阈值40mins，1000米以内
		{
			vec.push_back(i);
		}
	}
	if(vec.size()>0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Trip::proportionTrip(int pos,double &value)
{
	int A[5];                                                                      //初始化5个逗留时间分类：0-2h，2-4h，4-8h，8-12h，12-24h；
	double A5Duration[5]={3600.123,10800.123,21600.123,36000.123,64800.123};       //把五个分类的时间间隔的中间值写出来
	for(int i=0;i<5;i++)
	{
		A[i]=0;
	}
	for(unsigned i=0;i<stopEndTripIDInclude[sixKStopNameToID[DStopName[pos]]].size();i++)        //for的是当前trip的D所在的那个站点当天含有的所有trip
	{
		double timePeriod1=abs(getOffTime[i]-getOffTime[pos]);                                   //计算这些trip的下车相隔时间，越小表示和pos的trip越相似
		if(timePeriod1<3600 && tripDurationTime_v1[i]>1)    //如果当前trip的D所在的那个站点当天含有的所有trip中相似的时间段下，以及拥有真正的逗留时间才计算
		{
			if(tripDurationTime_v1[i]<7200)
			{
				A[0]++;
			}
			else if(tripDurationTime_v1[i]>=7200 && tripDurationTime_v1[i]<14400)
			{
				A[1]++;
			}
			else if(tripDurationTime_v1[i]>=14400 && tripDurationTime_v1[i]<28800)
			{
				A[2]++;
			}
			else if(tripDurationTime_v1[i]>=28800 && tripDurationTime_v1[i]<43200)
			{
				A[3]++;
			}
			else
			{
				A[4]++;
			}
		}
	}
	int maxA=A[0];
	int maxI=0;
	for(int i=1;i<5;i++)             //找出5个值中最大的那个，当然也可以按照比例来分配，但这里暂时用最大值给它
	{
		if(A[i]>maxA)
		{
			maxA=A[i];
			maxI=i;
		}
	}
	if(maxA==0)
	{
		//cout<<"这个站的终点很寒酸，五个逗留时间段没有一个符合的"<<endl;
		return false;
	}
	else
	{
		value=A5Duration[maxI];
		return true;
	}
}

void Trip::writeInTheExistingFile()
{
	ifstream finTrip("D:\\data\\深圳数据\\TRIP20180707\\CN\\20170408-Trip-statistics-2CN.csv");         //存有所有trip的数据，大概360万条
	string line;
	int times=1;                                                                    //看程序运行的速度
	double tStop=pow(10.0,7);                                                       //控制读多少行
	int number=0;                                                                   //累积行数
	//ifstream &fin=finTrip;

	ofstream outfile1;
	outfile1.open("D:\\data\\深圳数据\\修剪数据3\\20170408-Trip-statistics-2CN-duration.csv");      //写入逗留时间

	while(getline(finTrip,line))    //一行一行的读 
	{
		istringstream sin(line);   
		string field;
		int i=0;
		while (getline(sin,field,','))   //用vector读取时，这个CSV文件的字段超过5个时可能会出错
		{
			outfile1<<field<<",";
			i++;
			if(i==14)          //只读第row列的数据，然后push_back到vector里
			{
				outfile1<<fixed<<setprecision(6)<<tripDurationTime[number]<<endl;
				break;;
			}
		}
		number++;                                                             //累积行数

		if(number==times*100000)
		{
			cout<<number<<endl;     //到360w的时候就出问题?
			times++;
		}
		if(number>2.0*tStop)     //如果number过大就                                                           
		{
			cout<<"我要提前跳出来了！"<<endl;
			break;
		}
	}
	if(number-1!=tripDurationTime.size())
	{
		cout<<"卧槽出错了！！   "<<number<<"   但是  tripDurationTime.size()是 "<<tripDurationTime.size()<<endl;
	}
	finTrip.close();
	outfile1.close();
}

void Trip::run()
{
	makeSubwayLineMap();                                              //把那个可以根据string索引的map制作好
	ifstream finTrip("D:\\data\\深圳数据\\TRIP20180707\\CN\\20170408-Trip-statistics-2CN.csv");         //存有所有trip的数据，大概360万条
	readODTrip(finTrip);											  //读取完trip
	finTrip.close();
	readBusStop();                                                    //把合并后的一万个站点读进来，为了匹配他们每一个的流量分别是多少
	makeStopStartCount();                                             //统计出每个站点的次数，这个站点个数是1万的那个站点
	makeStopEndCount();                                               //为了按终点逗留时间的比例来分配

	addSuitableDurationTime();                                        //进行分配逗留时间
	writeInTheExistingFile();                                         //把逗留时间写到已有的文件中
}