#include "District.h"

#include<iostream>
#include<fstream>
#include<sstream>
#include<math.h>
#include<iomanip>

#include "limits.h"

using namespace std;

District::District(void)
{
	classCount=1000;                      
	oneDay=new Trip();                    
	MySingleH=4;                          
	MySingleDv=-0.99;                     
	runMyDv=false;                        
	 
	chosedPOInum=100;                       
}


District::~District(void)
{
	delete oneDay;
	oneDay=NULL;
	/*delete myTheory;
	myTheory=NULL;*/
}

void District::readGridClassLabel()
{
	Trip* useConvert=new Trip();
	ifstream finClass("D:\\data\\深圳数据\\修剪数据1\\gridClassLabel.csv");             
	string line;                                   
	ifstream &fin=finClass;
	double classL;               
	while(getline(fin,line))     
	{
		istringstream sin(line);   
		string field;
		int i=0;
		while (getline(sin,field,','))    
		{
			if(i==0)
			{
				classL=useConvert->convertStringToDouble(field);
				i++;
				continue;
			}
			else
			{
				i++;
				continue;
			}	
		}

		if(int(classL)>classCount)             
		{
			classCount=int(classL);
		}
		classLabel.push_back(int(classL));
	}
	finClass.close();
	cout<<"类别总数："<<classCount+1<<endl;
	delete useConvert;                     
	useConvert=NULL;
}

void District::readWaitingArray()
{
	Trip* useConvert=new Trip();
	double X,Y;          
	ifstream finBus("D:\\data\\深圳数据\\修剪数据1\\ArrayID.csv");        
	string line;                                   
	ifstream &fin=finBus;
	while(getline(fin,line))     
	{
		istringstream sin(line);   
		string field;
		int i=1;
		while (getline(sin,field,','))    
		{
			if(i==1)
			{
				X=useConvert->convertStringToDouble(field);
				i++;
				continue;
			}
			else if(i==2)
			{
				Y=useConvert->convertStringToDouble(field);
				i++;
				break;
			}
			else
			{
				i++;
				continue;
			}	
		}
		this->waitingRow.push_back(int(X));
		this->waitingColumn.push_back(int(Y));
	}
	finBus.close();
	delete useConvert;                     
	useConvert=NULL;
}
void District::readEraseTo17503GOG()
{
	Trip* useConvert=new Trip();
	ifstream finClass("D:\\data\\深圳数据\\修剪数据6\\eraseTo17503GOG.csv");             
	string line;                                   
	ifstream &fin=finClass;
	double classL;               
	while(getline(fin,line))     
	{
		istringstream sin(line);   
		string field;
		int i=0;
		while (getline(sin,field,','))    
		{
			if(i==0)
			{
				classL=useConvert->convertStringToDouble(field);
				i++;
				continue;
			}
			else
			{
				i++;
				continue;
			}	
		}

		if(int(classL)>classCount || int(classL)<1)             
		{
			cout<<"readEraseTo17503GOG()函数出错！！"<<endl;
			system("pause");
		}
		eraseEasternDaPeng.insert(int(classL));
	}
	finClass.close();
	cout<<"去掉大鹏新区的GOG总数是不是17503："<<eraseEasternDaPeng.size()<<endl;
	delete useConvert;                                                     
	useConvert=NULL;
}

void District::makeGridRCtoClassMap()
{
	double combined=0;                                  
	pair<map<double,int>::iterator,bool> Insert_Pair;
	for(unsigned int i=0;i<classLabel.size();i++)
	{
		combined=waitingRow[i]+waitingColumn[i]/1000.0;                           
		Insert_Pair=gridRCtoClass.insert(pair<double,int>(combined,classLabel[i]));
		if(Insert_Pair.second==false)
		{
			cout<<"居然他妈的插入失败了，不可能！！！"<<endl;
		}
	}
	cout<<"18万个格网的类别所属map全部插完了"<<endl;
}

void District::initializeClassArrive()
{
	for(int i=0;i<classCount+1;i++)                          
	{
		classArriveCount.push_back(0);                       
		classArriveTimeSum.push_back(0);
	}
}

void District::countDistrictAttraction()
{	
	if(runMyDv)
	{
		oneDay->set_SingleHour(MySingleH);                                                           
	}
	oneDay->run();                                                                               

	int tempPos=0;                                                                               
	 
	double Tm = 0;                                                                               
	double Durm = 0;                                                                             
	int Tm_num = 0;                                                                              
	int Durm_num = 0;                                                                            
	for(int i=0;i<oneDay->get_tripSize();i++)													 
	{
		tempPos=gridRCtoClass[oneDay->get_tripDGridXY(i)];                                       
		Tm_num++;							                                                     
		Tm += oneDay->get_tripTimeDiff(i)/60.0;                                                  
		if(oneDay->get_TripDurationTime(i)>1)
		{
			Durm_num++;
			Durm += oneDay->get_TripDurationTime(i)/60.0;
		}
	}
	cout<<"2019年6月21日加入-Tm_num："<<Tm_num<<"，Durm_num："<<Durm_num<<endl;
	cout<<"2019年6月21日加入-Tm："<<Tm/Tm_num<<"，Durm："<<Durm/Durm_num<<endl;
	Tm = Tm/Tm_num;
	Durm = Durm/Durm_num;
	cout<<"2019年6月21日加入-Tm："<<Tm<<"，Durm："<<Durm<<endl;

	double tempTripTime=0;																	     
	double tempTripDuration=0;                                                                   
	
	int times=1;                                                                                 
	for(int i=0;i<oneDay->get_tripSize();i++)													 
	{
		tempPos=gridRCtoClass[oneDay->get_tripDGridXY(i)];                                       
		classArriveCount[tempPos]++;							                                 
		tempTripTime=oneDay->get_tripTimeDiff(i);												 
		tempTripDuration=oneDay->get_TripDurationTime(i);                                        

		 
		if(tempTripDuration>1)                           
		{
			if(tempTripDuration==180.6)                  
			{
				classArriveTimeSum[tempPos] += (double(int(tempTripTime))/60.0)/Tm + Durm/15.0;       
			}
			else
			{
				classArriveTimeSum[tempPos] += (double(int(tempTripTime))/60.0)/Tm + Durm/(tempTripDuration/60.0);  
			}
		}
		else if(tempTripDuration<=1)
		{
			classArriveTimeSum[tempPos] += (double(int(tempTripTime))/60.0)/Tm;                   
		}
		else
		{
			cout<<"统计吸引力出错，逗留时间惹的祸！！！"<<endl;
			system("pause");
		}


		if(classArriveTimeSum[tempPos]>INT_MAX)                                                  
		{
			 
			 
		}
		if(i==times*100000)
		{
			cout<<i<<"  有效时间段内的oneDay->get_tripSize()   "<<oneDay->get_tripSize()<<endl;     
			times++;
		}
	}

	 
	double tempArea=0;
	for(int i=0;i<classCount+1;i++)                          
	{
		if(classOwnGridID[i].size()==0)
		{
			cout<<"居然能出现某个分区的面积为0的情况，即该分区没有格网，怎么可能    "<<i<<endl;
			system("pause");
			continue;
		}
		tempArea=classOwnGridID[i].size();                   
		 
	}
}

void District::makeFileOfDistrictAttraction()
{
	ofstream outfile1,outfile2;
	outfile1.open("D:\\data\\深圳数据\\修剪数据2\\classArriveCount.csv");
	outfile2.open("D:\\data\\深圳数据\\修剪数据2\\classArriveTimeSum.csv");
	for(unsigned int i=0;i<classArriveCount.size();i++)
	{
		outfile1<<fixed<<setprecision(6)<<i<<","<<classArriveCount[i]<<endl;
		outfile2<<fixed<<setprecision(6)<<i<<","<<classArriveTimeSum[i]<<endl;
	}
	outfile1.close();
	outfile2.close();
}
void District::readAnother_classArriveTimeSum(vector<double> &vec)
{
	ifstream fin1("D:\\data\\深圳数据\\修剪数据2\\classArriveTimeSum非工作日准备和工作日合并来算7天下的实际POI2.csv");          
	string line;
	int number=0;
	while(getline(fin1,line))     
	{
		istringstream sin(line);   
		string field;
		int i=1;
		while (getline(sin,field,',')) 
		{
			if(i==2)
			{
				vec[number]=oneDay->convertStringToDouble(field);
				i++;
				
			}
			else
			{
				i++;
				continue;
			}
			
		}
		number++;
		if(number>=18109)
		{
			break;
		}
	}
	cout<<"看是不是准确的18109："<<number<<endl;
	cout<<"readAnother_classArriveTimeSum(vector<double> &vec)执行完毕哦哦哦哦哦哦"<<endl;
	fin1.close();                                                             
}

void District::sortAttraction()
{
	 
 
	vector<double> temp_classArriveTimeSum;
	for(int i=0;i<classCount+1;i++)                          
	{
		temp_classArriveTimeSum.push_back(0);                                    
	}

	vector<double> sortedAttr;                                          
	if(classArriveTimeSum.size()!=classCount+1)
	{
		cout<<"sortAttraction()的classArriveTimeSum.size()!=classCount+1，炸了炸了啊！"<<endl;
		system("pause");
	}
	for(unsigned int i=0;i<classArriveTimeSum.size();i++)
	{
		sortedAttr.push_back(classArriveTimeSum[i]+temp_classArriveTimeSum[i]);
	}

	vector<int> sortedClass;									     
	for(unsigned int i=0;i<classArriveTimeSum.size();i++)
	{
		sortedClass.push_back(i);                                    
	}

	double tempAttr=0;													 
	int tempClass=0;                                                 
	int temp_i;                                                      
	for(unsigned int i=0;i<classArriveTimeSum.size()-1;i++)            
	{
		temp_i=i;
		for(unsigned int j=i+1;j<classArriveTimeSum.size();j++)
		{
			if(sortedAttr[temp_i]<sortedAttr[j])
			{
				temp_i=j;
			}
		}
		if(temp_i!=i)                                 
		{
			tempClass=sortedClass[i];
			sortedClass[i]=sortedClass[temp_i];
			sortedClass[temp_i]=tempClass;

			tempAttr=sortedAttr[i];
			sortedAttr[i]=sortedAttr[temp_i];
			sortedAttr[temp_i]=tempAttr;
		}
	}
	 

	 
	int waitingPOI=0;
	for(unsigned int i=0;i<classArriveCount.size();i++)                                    
	{
		if(classArriveCount[i]>0)               
		{
			waitingPOI++;
		}
	}
	cout<<"所以最终得到的候选POI个数是："<<waitingPOI<<endl<<endl;
	makePOISubwayDistrictMap();                                                            

	 
	double sumSortedAttr=0;                                                                
	ofstream outfile1;
	outfile1.open("D:\\data\\深圳数据\\修剪数据2\\sortedAttr.csv");
	ofstream outfile3;
	outfile3.open("D:\\data\\深圳数据\\修剪数据5\\sortedAttrReal_100POI_madeByAllTrip.csv");         
	for(unsigned int i=0;i<sortedAttr.size();i++)
	{
		int tempDistr=1;                                                                     
		if(POISubwayDistrict_exist.count(sortedClass[i])==0)                                 
		{
			tempDistr=0;
		}
		else
		{
			tempDistr=1;
		}
		if(i<300)                         
		{
			double meX,meY;
			getClassCenterXY(sortedClass[i],meX,meY);        
			outfile3<<fixed<<setprecision(6)<<i<<","<<sortedClass[i]<<","<<sortedAttr[i]/sortedAttr[0]<<","<<meX<<","<<meY<<endl;
		}
		outfile1<<fixed<<setprecision(6)<<i<<","<<sortedClass[i]<<","<<sortedAttr[i]<<","<<tempDistr<<endl;
		if(i<unsigned int(waitingPOI))
		{
			sumSortedAttr+=sortedAttr[i];                                                   
		}
		
	}
	outfile1.close();
	outfile3.close();
	 

	 
	double thisHourDv=calculateDv(sortedAttr,sortedClass);
	cout<<endl<<endl<<"大家快来看啊，这个小时的Dv值是：  第"<<oneDay->get_singleHour()<<"  小时开始的：  "<<thisHourDv<<endl<<endl;
	MySingleDv=thisHourDv;                                                                        
	double F_Loubar=1-1.26598/(sortedAttr[0]/(10000.0*classOwnGridID[sortedClass[0]].size())/60.0);     


	cout<<endl<<endl<<"那我这里的阈值上界是：  "<<F_Loubar<<endl<<endl;
	 
	double F_Loubar2=calculateTangentLine(sortedAttr,waitingPOI);
	cout<<endl<<endl<<"那我这里直接用切线计算的阈值上界是：  "<<F_Loubar2<<endl<<endl;

	double F_Loubar3=1-(sumSortedAttr/waitingPOI)/sortedAttr[0];
	cout<<endl<<endl<<"2014那篇文章作者回复改进后的公式9用密度均值除以密度最大值得到：  "<<F_Loubar3<<"     最大的吸引力值是："<<sortedAttr[0]<<endl<<endl;

	double F_Loubar4=calculateAverageLine(sortedAttr,waitingPOI);
	cout<<endl<<endl<<"那我这里直接用斜率为1处得切线计算的阈值上界是：  "<<F_Loubar4<<endl<<endl;

	 
	ofstream outfile2;
	outfile2.open("D:\\data\\深圳数据\\修剪数据2\\LorenzCurve.csv");
	double tempSumhaha=0;
	bool temp_getF=true;                                                       
	for(int i=waitingPOI-1;i>=0;i--)
	{
		tempSumhaha=tempSumhaha+sortedAttr[i];
		outfile2<<fixed<<setprecision(10)<<(waitingPOI-i)/double(waitingPOI)<<","<<tempSumhaha/sumSortedAttr<<endl;
		if((waitingPOI-i)/double(waitingPOI)>F_Loubar4 && temp_getF)
		{
			cout<<"哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈上界阈值取到了：  "<<i+1<<endl;
			chosedPOInum=i+1;
			temp_getF=false;
		}
	}
	outfile2.close();
	 

	 
	int sum_classArriveCount=0;                                           
	int number=0;                                                         
	 
	 
	while(POI_number.size()<unsigned int(chosedPOInum))                                 
	{
		 
		sum_classArriveCount=sum_classArriveCount+classArriveCount[sortedClass[number]];     
		if(sortedClass[number]==0)                     
		{
			cout<<number<<"      类别数："<<sortedClass[number]<<"     POI得值："<<sortedAttr[number]<<endl;
			number++;
			continue;
		}
		POI_number.push_back(sortedClass[number]);
		cout<<fixed<<setprecision(2)<<sortedClass[number]<<" 吸引力："<<sortedAttr[number]<<endl;
		number++;
	}
	 

	cout<<endl<<"所以POI得个数是："<<POI_number.size()<<",相等吗？   "<<chosedPOInum<<endl;
	cout<<fixed<<setprecision(5)<<"这么多POI所占到的trip'次数比例是："<<double(sum_classArriveCount/double(oneDay->get_tripSize()))<<"    这个时间段的trip总次数"<<oneDay->get_tripSize()<<endl<<endl;

	for(unsigned int i=0;i<POI_number.size();i++)                         
	{
		POI_weight.push_back(sortedAttr[i]/sortedAttr[0]);       
		cout<<fixed<<setprecision(5)<<POI_weight[i]<<"   "<<POI_number[i]<<endl;
	}

}
void District::makeFileOfPOI()
{
	ofstream outfile1;
	outfile1.open("D:\\data\\深圳数据\\修剪数据3\\POI_DistributedInMap.csv");
	for(unsigned int i=0;i<POI_number.size();i++)
	{
		double tempX=0;                                                                               
		double tempY=0;
		getClassCenterXY(POI_number[i],tempX,tempY);
		outfile1<<fixed<<setprecision(6)<<i<<","<<POI_number[i]<<","<<classOwnGridID[POI_number[i]].size()<<",";                
		outfile1<<fixed<<setprecision(8)<<tempX<<","<<tempY<<","<<classArriveTimeSum[POI_number[i]]<<",";                       
		outfile1<<fixed<<setprecision(6)<<classArriveTimeSum[POI_number[i]]/double(classOwnGridID[POI_number[i]].size())<<",";  
		outfile1<<fixed<<setprecision(6)<<POI_weight[i]<<endl;                                                                  
	}
	outfile1.close();
}
void District::makePOIMap()
{
	pair<map<int,int>::iterator,bool> Insert_Pair;
	for(unsigned int i=0;i<POI_number.size();i++)
	{
		Insert_Pair=POI_exist.insert(pair<int,int>(POI_number[i],i));             
		if(Insert_Pair.second==false)
		{
			cout<<i<<"   "<<POI_number[i]<<"  POI居然他妈的插入失败了，不可能！！！"<<endl;
		}
	}
}

void District::calculateAccess()
{
	vector<vector<double>> accessTimeCount;          
	vector<vector<int>> accessArriveCount;           

	vector<double> tempTimeCount;                    
	vector<int> tempArriveCount;
	for(unsigned int i=0;i<POI_number.size();i++)            
	{
		tempTimeCount.push_back(0);
		tempArriveCount.push_back(0);
	}
	for(unsigned int i=0;i<classArriveTimeSum.size();i++)    
	{
		accessTimeCount.push_back(tempTimeCount);
		accessArriveCount.push_back(tempArriveCount);
	}
	 

	int tempPos=0;                                                                               
	int tempStart=0;                                                                             
	int seeClass0=0;
	int seeDIsNotPOI=0;                   
	for(int i=0;i<oneDay->get_tripSize();i++)
	{
		tempStart=gridRCtoClass[oneDay->getGridPos(oneDay->get_tripOGrid_X(i),oneDay->get_tripOGrid_Y(i))];
		if(tempStart==0)                                                                         
		{
			seeClass0++;
			continue;
		}
		tempPos=gridRCtoClass[oneDay->get_tripDGridXY(i)];                                       
		if(POI_exist.count(tempPos)==0)                                                          
		{
			seeDIsNotPOI++;
			continue;
		}
		accessTimeCount[tempStart][POI_exist[tempPos]]+=oneDay->get_tripTimeDiff(i);             
		accessArriveCount[tempStart][POI_exist[tempPos]]++;                                      
	}
	 
	cout<<"当前trip的O在0类别中:"<<seeClass0<<"   "<<"当前trip的D不是到POI之一:"<<seeDIsNotPOI<<endl;

	int seeStopClass0=0;                                                  
	for(int i=0;i<oneDay->get_stop_size();i++)                            
	{
		tempStart=gridRCtoClass[oneDay->getGridPos(oneDay->get_oneWX(i),oneDay->get_oneWY(i))];
		if(tempStart==0 && oneDay->get_stopStartCount(i)!=0)                                     
		{
			seeStopClass0++;
			cout<<i<<"   "<<oneDay->get_oneWStopName(i)<<endl;
		}
	}
	cout<<"当前站点的坐标在0类别中，当前站点的出发量不为0："<<seeStopClass0<<endl;

	for(unsigned int i=0;i<classArriveTimeSum.size();i++)        
	{ 
		accessValue.push_back(0);
		int tempPOI=0;                                           
		for(unsigned int j=0;j<accessTimeCount[i].size();j++)    
		{
			if(accessArriveCount[i][j]!=0)             
			{
				tempPOI++;                                                                      
				accessTimeCount[i][j]/=accessArriveCount[i][j];                                 
				accessValue[i]+=((1.0/accessTimeCount[i][j])*POI_weight[j]);                      
			}
		}
		accessValue[i]*=tempPOI;                                 
	}


}

void District::makeFileOfAccess()
{
	ofstream outfile1;
	outfile1.open("D:\\data\\深圳数据\\修剪数据2\\accessValue.csv");
	for(unsigned int i=0;i<classArriveCount.size();i++)
	{
		outfile1<<fixed<<setprecision(6)<<i<<","<<accessValue[i]<<endl;
	}
	outfile1.close();
}

void District::makeClassOwnTripID()
{
	vector<int> temp;                              
	for(int i=0;i<classCount+1;i++)                  
	{
		classOwnTripID.push_back(temp);
	}
	cout<<endl<<"看一下类别的数目： "<<classCount+1<<endl<<endl;

	 
	cout<<"是不是10626                                                        "<<oneDay->get_stop_size()<<endl;
	cout<<"编号为10573得站点深圳大学1，是不是有98个格网                       "<<oneDay->get_stopNearestGrid_size(10573)<<endl;
	cout<<"编号为10573得站点深圳大学1的第四个格网是不是被分配了991个trip      "<<oneDay->get_stopNearestGridID_size(10573,3)<<endl;
	int sumRun=0;                                                        
	for(int i=0;i<oneDay->get_stop_size();i++)                            
	{
		for(int j=0;j<oneDay->get_stopNearestGrid_size(i);j++)            
		{
			for(int k=0;k<oneDay->get_stopNearestGridID_size(i,j);k++)    
			{
				if(classLabel[oneDay->get_gridID(i,j)]>classCount || classLabel[oneDay->get_gridID(i,j)]<0)
				{
					cout<<"出现了当前站点的格网的类别被认为是超范围了： "<<classLabel[oneDay->get_gridID(i,j)]<<endl;
					continue;
				}
				sumRun++;
				classOwnTripID[classLabel[oneDay->get_gridID(i,j)]].push_back(oneDay->get_stopEachGridTripID(i,j,k));
				 
				 
			}
		}
	}
	cout<<"开始遍历那个三维向量，相当于把trip的ID全部转移过来，即三重for循环总共执行了多少次： "<<sumRun<<endl;

	 
	int sum=0;
	ofstream outfile1;
	outfile1.open("D:\\data\\深圳数据\\修剪数据2\\classOwnTripID.csv");
	for(int i=0;i<classCount+1;i++)
	{
		outfile1<<fixed<<setprecision(6)<<i<<","<<classOwnTripID[i].size()<<endl;
		sum=sum+classOwnTripID[i].size();
	}
	cout<<"放到所有分区中的trip量的总和大概是（应该和三重for循环的次数相同的），同时这个也是所有有效trip分到各个分区之后得总和： "<<sum<<endl;
	cout<<"1.因为trip起点站名在候选的10626个站点里没有而去掉一部分；2.因为trip起点不在任何格网里而没被分下去"<<endl;
	if(sumRun!=sum)
	{
		cout<<"三重for循环的次数与放到所有分区中的trip量的总和不相等，相差： "<<abs(sumRun-sum)<<endl;
	}
	outfile1.close();

}
void District::calculateAccessByClass()
{
	vector<double> timeCount;                    
	vector<int> arriveCount;                     
	vector<double> wieghtCount;                  
	vector<int> tripPOIcount;                    
	for(unsigned int i=0;i<POI_number.size();i++)            
	{
		timeCount.push_back(0);
		arriveCount.push_back(0);
	}
	 
	int tempPos=0;                                                    
	int seeDIsNotPOI=0;                                               
	double tripTimeMax=12200+1000;                                    
	double tripTimeMin=200;

	double maxRealGoingPOINum=calculateMaxRealGoingPOINum();          
	cout<<endl<<"最”省事“的行程时间" <<((tripTimeMax-tripTimeMin)/60.0)<<"   最有效POI次数：  "<<maxRealGoingPOINum<<endl<<endl;
	double tehoryMaxAccessValue=((tripTimeMax-tripTimeMin)/60.0)*maxRealGoingPOINum;               

	for(unsigned int i=0;i<classOwnTripID.size();i++)                 
	{
		accessValueByClass.push_back(0);                              
		accessMeanTimeByClass.push_back(0);                           
		wieghtCount.push_back(0);                                     
		tripPOIcount.push_back(0);                                    

		 
		for(unsigned int j=0;j<classOwnTripID[i].size();j++)          
		{
			tempPos=gridRCtoClass[oneDay->get_tripDGridXY(classOwnTripID[i][j])];                    
			if(POI_exist.count(tempPos)==0)                                                          
			{
				seeDIsNotPOI++;
				continue;
			}
			double walkTime=oneDay->get_tripWalkDis(classOwnTripID[i][j])/1;                                    
			if(walkTime>1000)
			{
				cout<<"步行时间居然大于1000秒了？？？  "<<walkTime<<endl;
				system("pause");
			}

			 
			/*cout<<walkTime<<"   "<<classOwnTripID[i][j]<<" 站点名字   "<<oneDay->get_OStopName(classOwnTripID[i][j])<<endl;
			cout<<oneDay->get_ODStopNumber(classOwnTripID[i][j])<<"  trip的尺寸  "<<oneDay->get_tripSize()<<endl;
			cout<<fixed<<setprecision(3)<<"当前trip是："<<oneDay->get_oneWStopName(int(oneDay->get_tripStopOwnPos(classOwnTripID[i][j])))<<"当前tripO站点的第几个格网："<<oneDay->get_tripStopOwnPos(classOwnTripID[i][j])<<endl;
			system("pause");*/

			timeCount[POI_exist[tempPos]]+=(oneDay->get_tripTimeDiff(classOwnTripID[i][j])+walkTime);           
			arriveCount[POI_exist[tempPos]]++;                                                                  
			wieghtCount[i]+=POI_weight[POI_exist[tempPos]];                                                     
		}
		if(wieghtCount[i]>maxRealGoingPOINum)              
		{
			cout<<"累积的权重居然超了："<<wieghtCount[i]<<"  怎么会呢?最大权重是："<<maxRealGoingPOINum<<"    这是第几个呢："<<i<<" 它有多少个trip次数 "<<classOwnTripID[i].size()<<endl;
			for(unsigned int j=0;j<classOwnTripID[i].size();j++)          
			{
				tempPos=gridRCtoClass[oneDay->get_tripDGridXY(classOwnTripID[i][j])];                    
				if(POI_exist.count(tempPos)==0)                                                          
				{
					seeDIsNotPOI++;
					continue;
				}
				cout<<POI_weight[POI_exist[tempPos]]<<endl;
			}
			system("pause");
		}

		 
		for(unsigned int j=0;j<POI_number.size();j++)            
		{
			tripPOIcount[i]+=arriveCount[j];
		}
		if(tripPOIcount[i]==classOwnTripID[i].size() && tripPOIcount[i]!=0)         
		{
			if(tripPOIcount[i]>100)
			{
				cout<<"第"<<i<<"个类别里的所有trip都去了POI！且该类别的中的trip数大于100  "<<tripPOIcount[i]<<endl;
			}
		}

		 
		int tempPOI=0;                                           
		double finalAverageGoingTime = 0;                        
		for(unsigned int j=0;j<POI_number.size();j++)            
		{
			if(arriveCount[j]!=0)                                
			{
				tempPOI++;                                                                      
				timeCount[j]/=arriveCount[j];                                                   
				if(timeCount[j]>tripTimeMax)
				{
					cout<<"算出到当前的POI居然行程时间超过了理论最大值！！！"<<timeCount[j]<<endl;
					system("pause");
				}

				double goOutWeight=arriveCount[j]/double(tripPOIcount[i]);                                  

				 
				accessValueByClass[i]+=((tripTimeMax-timeCount[j])/60.0)*goOutWeight*POI_weight[j];      

				finalAverageGoingTime += (tripTimeMax-timeCount[j])*goOutWeight;                         


				 
			}
		}
		  
		accessMeanTimeByClass[i]=(tripTimeMax-finalAverageGoingTime)/60.0;                        

		if(accessMeanTimeByClass[i]>tripTimeMax/60.0)
		{
			cout<<"算出当前分区的平均出行时间超过了理论最大值！！！"<<accessMeanTimeByClass[i]<<"   该分区是：   "<<i<<endl;
			system("pause");
		}
		 
		for(unsigned int j=0;j<POI_number.size();j++)               
		{
			timeCount[j]=0;                                         
			arriveCount[j]=0;
		}
	}
	cout<<"当前trip的D不是到POI之一:"<<seeDIsNotPOI<<endl;  

	 
	ofstream outfile1,outfile2;
	outfile1.open("D:\\data\\深圳数据\\修剪数据2\\accessValueByClass.csv");
	outfile2.open("D:\\data\\深圳数据\\修剪数据2\\accessMeanTimeByClass.csv");
	for(unsigned int i=0;i<accessValueByClass.size();i++)                       
	{
		if(eraseEasternDaPeng.count(i)==0 && i>0)                                     
		{
			continue;
		}
		double tempArea=classOwnGridID[i].size();                                                                                                       
		outfile1<<fixed<<setprecision(6)<<i<<","<<accessValueByClass[i]<<","<<classOwnTripID[i].size()<<","<<tempArea<<","<<classOwnTripID[i].size()/tempArea*100<<endl;
		outfile2<<fixed<<setprecision(6)<<i<<","<<accessMeanTimeByClass[i]<<","<<classOwnTripID[i].size()<<","<<tripPOIcount[i]<<",";
		outfile2<<fixed<<setprecision(6)<<wieghtCount[i]<<","<<wieghtCount[i]/double(tripPOIcount[i])<<endl;
	}
	outfile1.close();
	outfile2.close();
}
double District::calculateMaxRealGoingPOINum()
{
	double going=0;
	int whereClass=0;           
	for(unsigned int i=0;i<classOwnTripID.size();i++)                 
	{
		double tempGoing=0;
		for(unsigned int j=0;j<classOwnTripID[i].size();j++)          
		{
			int tempPos=gridRCtoClass[oneDay->get_tripDGridXY(classOwnTripID[i][j])];                    
			if(POI_exist.count(tempPos)!=0)                                                                 
			{
				tempGoing++;
			}
		}
		if(tempGoing>going)                                   
		{
			whereClass=i;
			going=tempGoing;
		}
	}
	cout<<"最猛的居然在第多少类："<<whereClass<<"  最有效POI次数：  "<<going<<endl;
	return going;
}


void District::makeClassOwnGridID()
{
	vector<int> temp;                                        
	for(int i=0;i<classCount+1;i++)                          
	{
		classOwnGridID.push_back(temp);                      
	}

	for(unsigned int i=0;i<classLabel.size();i++)            
	{
		classOwnGridID[classLabel[i]].push_back(i);
	}

	ofstream outfile1;
	outfile1.open("D:\\data\\深圳数据\\修剪数据2\\classOwnGridID.csv");
	for(unsigned int i=0;i<classOwnGridID.size();i++)                       
	{
		outfile1<<i<<",";
		for(unsigned int j=0;j<classOwnGridID[i].size();j++)                    
		{
			outfile1<<classOwnGridID[i][j]<<",";
		}
		outfile1<<endl;
	}
	outfile1.close();
}
void District::getClassCenterXY(int index,double &X,double &Y)
{
	double combined=0;                                  
	double meanX=0;                                                        
	double meanY=0;
	for(unsigned int i=0;i<classOwnGridID[index].size();i++)               
	{
		double rX=0;
		double rY=0;
		combined=waitingRow[classOwnGridID[index][i]]+waitingColumn[classOwnGridID[index][i]]/1000.0;                           
		getGridCenterXY(combined,rX,rY);
		meanX=meanX+rX;
		meanY=meanY+rY;
	}
	X=meanX/double(classOwnGridID[index].size());                 
	Y=meanY/double(classOwnGridID[index].size());
}
void District::getGridCenterXY(double combined,double &X,double &Y)
{
	int a1,a2;
	a1=int(combined);                               
	a2=round_double((combined-a1)*1000);            
	X=oneDay->get_OriginX()+(a2-1)*100;
	Y=oneDay->get_OriginY()-(a1-1)*100;
}
int District::round_double(double temp)
{
	double a;
	if(temp>0.0)
	{
		a=floor(temp+0.5);       
	}
	else
	{
		a=ceil(temp-0.5);        
	}
	return int(a);
}
double District::calculateDv(vector<double> sAttr,vector<int> sClass)
{
	double finalDv=0;                                              

	 
	int waitingPOI=0;
	for(unsigned int i=0;i<classArriveCount.size();i++)                                    
	{
		if(classArriveCount[i]!=0)               
		{
			waitingPOI++;
		}
	}
	 
	double sumSortedAttr=0;                                                                
	for(unsigned int i=0;i<sAttr.size();i++)                                               
	{
		sumSortedAttr+=sAttr[i];                                                            
	}
	cout<<"18000个分区中需要参与计算Dv的有："<<waitingPOI<<"个   需要做分母的吸引力总值为："<<sumSortedAttr<<endl;
	if(sumSortedAttr==0)                
	{
		return 0;
	}
	 
	double sum_sisjdij=0;                                                      
	double sum_sisj=0;
	for(int i=0;i<waitingPOI;i++)                                              
	{
		for(int j=i+1;j<waitingPOI;j++)                                        
		{
			double si=sAttr[i]/sumSortedAttr;                                                          
			double sj=sAttr[j]/sumSortedAttr;                                                          
			double iX=0;                                                                               
			double iY=0;
			double jX=0;                                                                               
			double jY=0;
			getClassCenterXY(sClass[i],iX,iY);
			getClassCenterXY(sClass[j],jX,jY); 
			double dij=oneDay->getTwoPointDistance(iX,iY,jX,jY);                                      
			 
			
			sum_sisjdij+=(si*sj*dij);                                                                 
			sum_sisj+=(si*sj);                                                                        
		}
		 
	}
	finalDv=sum_sisjdij/sum_sisj;
	return finalDv;
}
double District::calculateTangentLine(vector<double> sAttr,int n)
{
	cout<<"calculateTangentLine"<<endl;
	double finalThre=0;                                              

	 
	int waitingPOI=n;
	 
	double sumSortedAttr=0;                                                                
	for(unsigned int i=0;i<sAttr.size();i++)                                               
	{
		if(i<unsigned int(waitingPOI))
		{
			sumSortedAttr+=sAttr[i];                                                            
		}
	}
	cout<<"18000个分区中需要参与计算POI个数下洛伦兹曲线的切线的有："<<waitingPOI<<"个   需要做分母的吸引力总值为："<<sumSortedAttr<<endl;
	 
	double tempSumhaha=0;
	bool temp_getF=true;                                                       
	vector<double> tgX;
	vector<double> tgY;
	for(int i=waitingPOI-1;i>=0;i--)
	{
		tempSumhaha=tempSumhaha+sAttr[i];
		if(i<2)                                                               
		{
			tgX.push_back((waitingPOI-i)/double(waitingPOI));
			tgY.push_back(tempSumhaha/sumSortedAttr);
		}
	}
	 
	for(unsigned int i=0;i<tgX.size();i++)
	{
		cout<<tgX[i]<<"    "<<tgY[i]<<endl;
	}
	 
	double k=0;
	double b=0;
	k=abs(tgY[1]-tgY[0])/abs(tgX[1]-tgX[0]);
	b=tgY[1]-k*tgX[1];
	if(b!=tgY[0]-k*tgX[0])
	{
		cout<<"算算y=kx+b的时候，这个b的计算有大问题！！！"<<endl;
	}

	finalThre=(0-b)/k;                          

	return finalThre;
}
double District::calculateAverageLine(vector<double> sAttr,int n)
{
	cout<<"calculateAverageLine这个是算斜率为1得切线"<<endl;
	double finalThre=0;                                              

	 
	int waitingPOI=n;
	 
	double sumSortedAttr=0;                                                                
	for(unsigned int i=0;i<sAttr.size();i++)                                               
	{
		if(i<unsigned int(waitingPOI))
		{
			sumSortedAttr+=sAttr[i];                                                            
		}
	}
	 
	double tempSumhaha=0;
	bool temp_getF=true;                                                       
	vector<double> tgX;
	vector<double> tgY;
	double k=100;
	double b=0;
	int times=2;                                                               

	while(k>=1)                                                                
	{
		for(int i=waitingPOI-1;i>=0;i--)
		{
			tempSumhaha=tempSumhaha+sAttr[i];
			if(i<times && i>=times-2)                                                               
			{
				tgX.push_back((waitingPOI-i)/double(waitingPOI));
				tgY.push_back(tempSumhaha/sumSortedAttr);
			}
		}
		 
		k=abs(tgY[1]-tgY[0])/abs(tgX[1]-tgX[0]);
		times++;                                                                
		tgX.clear();
		tgY.clear();
		tempSumhaha=0;
	}
	cout<<endl<<endl<<"往回移动到了第几个点："<<times<<"    且此时放入得坐标点tgX是不是2个："<<tgX.size()<<endl<<endl<<endl;

	for(int i=waitingPOI-1;i>=0;i--)
	{
		tempSumhaha=tempSumhaha+sAttr[i];
		if(i<times-2 && i>=times-4)                                                               
		{
			tgX.push_back((waitingPOI-i)/double(waitingPOI));
			tgY.push_back(tempSumhaha/sumSortedAttr);
		}
	}
	 
	for(unsigned int i=0;i<tgX.size();i++)
	{
		cout<<tgX[i]<<"    "<<tgY[i]<<endl;
	}
	 

	finalThre=tgX[0];
	return finalThre;
}


int District::get_classOwnTripID(int ind_i,int ind_j)
{
	return classOwnTripID[ind_i][ind_j];                            
}
int District::get_classOwnTripID_rowSize(int index)
{
	if(index>=18109)
	{
		cout<<"get_classOwnTripSize(int index1)的index1超过类别数了！"<<endl;
		system("pause");
	}
	return int(classOwnTripID[index].size());
}
int District::get_classCount()
{
	return classCount;
}
int District::get_chosedPOInum()
{
	return chosedPOInum;
}
double District::get_accessValueByClass(int index)
{
	return accessValueByClass[index];
}
double District::get_accessMeanTimeByClass(int index)
{
	return accessMeanTimeByClass[index];
}

double District::get_DGridXY(int index)
{
	return oneDay->get_tripDGridXY(index);                     
}
double District::get_timeDiff(int index)
{
	return oneDay->get_tripTimeDiff(index);                    
}
double District::get_OGridXY(int index)
{
	return oneDay->getGridPos(oneDay->get_tripOGrid_X(index),oneDay->get_tripOGrid_Y(index));
}
string District::get_OName(int index)
{
	return oneDay->get_OStopName(index);
}
double District::get_ODManyStops(int index)
{
	return oneDay->get_ODStopNumber(index);
}
int District::get_gridRCtoClass(double index)
{
	if(gridRCtoClass.count(index)!=0)
	{
		return gridRCtoClass[index];
	}
	else
	{
		return -99;
	}
}


void District::makePOISubwayDistrictMap()
{
	 
	int is199 = 0;                                                                                                     
	pair<map<int,int>::iterator,bool> Insert_Pair;
	for(int i=oneDay->get_busOrSubwayDivide();i<oneDay->get_stop_size();i++)                                   
	{
		double tempCombined = oneDay->getGridPos(oneDay->get_oneWX(i),oneDay->get_oneWY(i));
		if(gridRCtoClass.count(tempCombined) == 0)
		{
			cout<<"他妈的这个地铁站居然不在分区里？  "<<tempCombined<<endl;
			system("pause");
		}
		else
		{
			Insert_Pair=POISubwayDistrict_exist.insert(pair<int,int>(gridRCtoClass[tempCombined],is199));           
			if(Insert_Pair.second==false)
			{
				cout<<oneDay->get_oneWStopName(i)<<"   分区："<<gridRCtoClass[tempCombined]<<"  地铁分区居然他妈的插入失败了，少见！！！"<<endl;
			}
		}
		is199++;
	}
	cout<<"看看我是不是for了199次："<<is199<<endl;
}

void District::run()
{
	readGridClassLabel();                           
	readWaitingArray();                             
	readEraseTo17503GOG();                          
	makeGridRCtoClassMap();                         
	makeClassOwnGridID();                           
	initializeClassArrive();                        
	countDistrictAttraction();                      
	makeFileOfDistrictAttraction();                 
	sortAttraction();                               
	makeFileOfPOI();                                

	makePOIMap();                                   
	calculateAccess();                              
	makeFileOfAccess();                             
	makeClassOwnTripID();                           
	calculateAccessByClass();                       

	cout<<endl<<"当前算的时间段是： "<<oneDay->get_singleHour()<<"--到--"<<oneDay->get_singleHour()+oneDay->get_durationLast()<<endl;
}
void District::run(int H,double &MyDv,int &MyTripSize)
{
	runMyDv=true;
	MySingleH=H;                                    
	readGridClassLabel();                           
	readWaitingArray();                             
	makeGridRCtoClassMap();                         
	makeClassOwnGridID();                           
	initializeClassArrive();                        
	countDistrictAttraction();                      
	makeFileOfDistrictAttraction();                 
	sortAttraction();                               
	MyDv=MySingleDv;                                
	MyTripSize=oneDay->get_tripSize();              

	makePOIMap();                                   
	calculateAccess();                              
	makeFileOfAccess();                             
	makeClassOwnTripID();                           
	calculateAccessByClass();                       
}