#include "Theory.h"
#include "Trip.h"

#include<iostream>
#include<fstream>
#include<sstream>
#include<math.h>
#include<iomanip>

#include "limits.h"

using namespace std;

Theory::Theory(void)
{
	myDistrict=new District();            
	selectedPOINum=60;                    

}


Theory::~Theory(void)
{
	
	delete myDistrict;
	myDistrict=NULL;
}

void Theory::makeGaoDeXY()
{
	int claCount=myDistrict->get_classCount();           
	readTheoryPOI();                                     
	readGuanNei();                                       
	 

	 
	map<int,int> GuanNei_exist;                          
	pair<map<int,int>::iterator,bool> Insert_Pair;
	for(unsigned int i=0;i<myVecID.size();i++)           
	{
		Insert_Pair=GuanNei_exist.insert(pair<int,int>(myVecID[i],i));            
		if(Insert_Pair.second==false)
		{
			cout<<i<<"   "<<myVecID[i]<<"  关内分区居然他妈的插入失败了，不可能！！！"<<endl;
		}
	}
	 

	cout<<"他妈的看一下这个类别数到底get得对不对！！"<<claCount+1<<endl;
	 
	vector<int> temp_classPos;
	vector<int> temp_classOwnNum;
	for(int i=0;i<claCount+1;i++)
	{
		temp_classPos.push_back(i);
		temp_classOwnNum.push_back(myDistrict->get_classOwnTripID_rowSize(i));
	}
	if(temp_classPos.size()!=temp_classOwnNum.size())
	{
		cout<<"怎么可能呢安：temp_classPos.size()!=temp_classOwnNum.size()"<<endl;
	}

	int tempAttr=0;													 
	int tempClass=0;                                                 
	int temp_i;                                                      
	for(unsigned int i=0;i<temp_classPos.size()-1;i++)            
	{
		temp_i=i;
		for(unsigned int j=i+1;j<temp_classPos.size();j++)
		{
			if(temp_classOwnNum[temp_i]<temp_classOwnNum[j])
			{
				temp_i=j;
			}
		}
		if(temp_i!=i)                                 
		{
			tempClass=temp_classPos[i];
			temp_classPos[i]=temp_classPos[temp_i];
			temp_classPos[temp_i]=tempClass;

			tempAttr=temp_classOwnNum[i];
			temp_classOwnNum[i]=temp_classOwnNum[temp_i];
			temp_classOwnNum[temp_i]=tempAttr;
		}
	}
	 

	ofstream outfile1;
	ofstream outfile2;
	ofstream outfile3;
	ofstream outfile4;
	outfile1.open("D:\\data\\深圳数据\\修剪数据4\\GaoDeXY1.csv");
	outfile2.open("D:\\data\\深圳数据\\修剪数据4\\GaoDeXY2.csv");
	outfile3.open("D:\\data\\深圳数据\\修剪数据4\\GaoDeXY3.csv");
	outfile4.open("D:\\data\\深圳数据\\修剪数据4\\GaoDeXY4.csv");
	double classCenterX,classCenterY;
	int tempGNnum=0;                                                   
	for(int i=0;i<claCount+1;i++)                                            
	{
		if(GuanNei_exist.count(i)==0)                                          
		{
			continue;
		}
		 
		myDistrict->getClassCenterXY(i,classCenterX,classCenterY);                          
		 
		if(tempGNnum<1000)                                                                
		{
			for(int j=0;j<100;j++)                                       
			{
				outfile1<<fixed<<setprecision(6)<<i<<","<<classCenterX<<","<<classCenterY<<",";
				outfile1<<fixed<<setprecision(6)<<myPOIVecX[j]<<","<<myPOIVecY[j]<<endl;
			}
		}
		else if(tempGNnum>=1000 && tempGNnum<2000)
		{
			for(int j=0;j<100;j++)                                       
			{
				outfile2<<fixed<<setprecision(6)<<i<<","<<classCenterX<<","<<classCenterY<<",";
				outfile2<<fixed<<setprecision(6)<<myPOIVecX[j]<<","<<myPOIVecY[j]<<endl;
			}
		}
		else if(tempGNnum>=2000 && tempGNnum<3000)
		{
			for(int j=0;j<100;j++)                                       
			{
				outfile3<<fixed<<setprecision(6)<<i<<","<<classCenterX<<","<<classCenterY<<",";
				outfile3<<fixed<<setprecision(6)<<myPOIVecX[j]<<","<<myPOIVecY[j]<<endl;
			}
		}
		else
		{
			for(unsigned int j=0;j<100;j++)                                       
			{
				outfile4<<fixed<<setprecision(6)<<i<<","<<classCenterX<<","<<classCenterY<<",";
				outfile4<<fixed<<setprecision(6)<<myPOIVecX[j]<<","<<myPOIVecY[j]<<endl;
			}
		}
		tempGNnum++;
	}
	cout<<"跳到关内的次数是："<<tempGNnum<<endl;

	outfile1.close();
	outfile2.close();
	outfile3.close();
	outfile4.close();

}
void Theory::readTheoryPOI()
{
	Trip* oneDay;                                        
	oneDay=new Trip();                                   

	ifstream fin("D:\\data\\深圳数据\\修剪数据3\\calculateStopsBC合并站点名字.csv");          
	string line;

	int number=0;
	while(getline(fin,line))     
	{
		if(number==0)
		{
			number++;
			continue;
		}
		istringstream sin(line);   
		string field;
		int i=1;
		while (getline(sin,field,',')) 
		{
			if(i==4)
			{
				myPOIVecX.push_back(oneDay->convertStringToDouble(field));              
				i++;
			}
			else if(i==5)
			{
				myPOIVecY.push_back(oneDay->convertStringToDouble(field));   
				i++;
			}
			else if(i==6)
			{
				myPOIWeight.push_back(oneDay->convertStringToDouble(field));
				i++;
			}
			else
			{
				i++;
				continue;
			}
		}
		number++;
	}
	cout<<myPOIVecX.size()<<"   《--X数 和 Y数--》   "<<myPOIVecY.size()<<endl;
	cout<<"理论POI的权重个数myPOIWeight.size()："<<myPOIWeight.size()<<endl;
	/*for(unsigned int i=0;i<vecX.size();i++)
	{
		cout<<fixed<<setprecision(6)<<vecX[i]<<"     "<<vecY[i]<<endl;
	}*/

	delete oneDay;
	oneDay=NULL;
}
void Theory::readGuanNei()
{
	Trip* oneDay;                                        
	oneDay=new Trip();                                   

	ifstream fin("D:\\data\\深圳数据\\修剪数据3\\GuanNei.csv");                          
	string line;
	double isGuanNei=0;
	int tempID=0; 

	int number=0;
	while(getline(fin,line))     
	{
		istringstream sin(line);   
		string field;
		int i=1;
		while (getline(sin,field,',')) 
		{
			if(i==3)
			{
				isGuanNei=oneDay->convertStringToDouble(field);
				if(isGuanNei==1)
				{
					myVecID.push_back(tempID);  
				}           
				i++;
			}
			else if(i==2)
			{
				tempID=int(oneDay->convertStringToDouble(field));
				i++;
			}
			else
			{
				i++;
				continue;
			}
		}
		number++;
	}
	cout<<number<<"     《--读了的行数 和 原始的类别数--》   "<<myDistrict->get_classCount()+1<<endl;
	cout<<myVecID.size()<<"   《--读进来的ID行数是不是4439 "<<endl;

	delete oneDay;
	oneDay=NULL;
}
void Theory::findTheoryInvalidTime()
{
	ofstream outfile1;
	outfile1.open("D:\\data\\深圳数据\\修剪数据4\\API_Invalid.csv");

	string line;
	double tempTime=0;
	int tempGuanNeiPos=0;                                    
	int emptyCount=0;                                        
	int arrayCount=0;                                        
	int number=0;                                            
	bool isNeedChange=false;                                 

	for(int i=1;i<=18;i++)
	{
		ifstream fin("D:\\data\\深圳数据\\修剪数据4\\result"+to_string(long long(i))+".csv");                          
		while(getline(fin,line))     
		{
			istringstream sin(line);   
			string field;
			int j=1;
			while (getline(sin,field,',')) 
			{
				if(isNeedChange && j>4)                 
				{
					outfile1<<field<<",";
				}
				if(j==3)
				{
					if(field=="")
					{
						emptyCount++;
						isNeedChange=true;
						outfile1<<emptyCount+arrayCount<<","<<number<<",";
						invalidTimePos.push_back(number);
					}
					else if(field=="Array")
					{
						arrayCount++;
						isNeedChange=true;
						outfile1<<emptyCount+arrayCount<<","<<number<<",";
						invalidTimePos.push_back(number);
					}
					else
					{
						continue;
					}         
					j++;
				}
				else
				{
					j++;
					continue;
				}
			}
			if(isNeedChange)                          
			{
				outfile1<<i<<endl;
			}
			isNeedChange=false;
			number++;
			if(number%100==0)
			{
				tempGuanNeiPos++;
			}
		}
		cout<<i<<endl;
	}

	cout<<emptyCount<<"     《--读了空值的行数 和 array的行数--》   "<<arrayCount<<endl;
	cout<<tempGuanNeiPos<<"    到关内的第几个分区了！！"<<endl;
	cout<<"那个invalidTimePosd尺寸是不是1197："<<invalidTimePos.size()<<endl;

	outfile1.close();
}

void Theory::readTheoryTime()
{
	Trip* oneDay;                                        
	oneDay=new Trip();                                   

	vector<double> temp;
	cout<<"for得是不是4439个关内分区，输出myVecID.size()看一下： "<<myVecID.size()<<endl;
	for(unsigned int i=0;i<myVecID.size();i++)           
	 
	{
		theoryTime.push_back(temp);
	}
	
	string line;
	double tempTime=0;
	int tempGuanNeiPos=0;                                    
	int emptyCount=0;                                        
	int arrayCount=0;                                        
	int number=0;                                            
	
	for(int i=1;i<=18;i++)
	{
		ifstream fin("D:\\data\\深圳数据\\修剪数据4\\result"+to_string(long long(i))+".csv");                          
		while(getline(fin,line))     
		{
			istringstream sin(line);   
			string field;
			int j=1;
			while (getline(sin,field,',')) 
			{
				if(j==3)
				{
					if(field=="")
					{
						emptyCount++;
						tempTime=-99;                          
					}
					else if(field=="Array")
					{
						arrayCount++;
						tempTime=-88;                         
					}
					else
					{
						tempTime=oneDay->convertStringToDouble(field);
					}         
					j++;
				}
				else
				{
					j++;
					continue;
				}
			}
			theoryTime[tempGuanNeiPos].push_back(tempTime);
			number++;
			if(number%100==0)
			{
				tempGuanNeiPos++;
			}
		}
		cout<<i<<endl;
	}
	
	cout<<emptyCount<<"     《--读了空值的行数 和 array的行数--》   "<<arrayCount<<endl;
	cout<<number<<"     《--读了的行数 和 push进来的API时间--》   "<<theoryTime.size()<<endl;
	cout<<tempGuanNeiPos<<"    到关内的第几个分区了！！"<<endl;

	delete oneDay;
	oneDay=NULL;
}
void Theory::fillInvalidTime()
{
	 
	Trip* oneDay;                                                                     
	oneDay=new Trip();                                                                

	int emptyCount=0;                                                                
	int arrayCount=0;                                                                
	int hang=0;                                                                      
	for(unsigned int i=0;i<theoryTime.size();i++)
	{
		for(unsigned int j=0;j<theoryTime[i].size();j++)
		{
			hang++;
			if(theoryTime[i][j]==-99)
			{
				emptyCount++;
			}
			if(theoryTime[i][j]==-88)
			{
				arrayCount++;
			}
		}
	}
	cout<<"看一下theoryTime这个二维数组到底是不是443900这么大："<<hang<<endl;
	cout<<"看一下未填充之前为空和为array的值各是多少："<<emptyCount<<"   "<<arrayCount<<endl;

	
	ifstream fin("D:\\data\\深圳数据\\修剪数据4\\result1_18.csv");                          
	string line;
	double tempTime=0;
	int number=0;
	vector<double> temp_theoryTime;                                                         
	emptyCount=0;
	arrayCount=0;
	while(getline(fin,line))     
	{
		istringstream sin(line);   
		string field;
		int i=1;
		while (getline(sin,field,',')) 
		{
			if(i==3)
			{
				if(field=="")
				{
					emptyCount++;
					tempTime=-99;                          
				}
				else if(field=="Array")
				{
					arrayCount++;
					tempTime=-88;                         
				}
				else
				{
					tempTime=oneDay->convertStringToDouble(field);
				}         
				i++;
			}
			else
			{
				i++;
				continue;
			}
		}
		temp_theoryTime.push_back(tempTime);
		number++;
	}
	cout<<endl<<"读了是不是1197行："<<number<<"    暂时的填充结果是不是1197："<<temp_theoryTime.size()<<endl;
	cout<<"看一下填充的1197个值中为空和为array的值各是多少："<<emptyCount<<"   "<<arrayCount<<endl;

	 
	int temp_i=0;
	int temp_j=0;
	for(unsigned int i=0;i<invalidTimePos.size();i++)
	{
		temp_i=int(invalidTimePos[i]/100);
		temp_j=invalidTimePos[i]%100;
		if(theoryTime[temp_i][temp_j]==-99 || theoryTime[temp_i][temp_j]==-88)
		{
			theoryTime[temp_i][temp_j]=temp_theoryTime[i];
		}
		else
		{
			cout<<"怎么可能输出这个！！！！！！！！！！！！！！！！！！！！！！"<<endl;
		}
		if(theoryTime[temp_i][temp_j]==-88)
		{
			cout<<"在1197中的位置："<<i+1<<endl;
		}
	}

	 
	hang=0;
	emptyCount=0;
	arrayCount=0;
	for(unsigned int i=0;i<theoryTime.size();i++)
	{
		for(unsigned int j=0;j<theoryTime[i].size();j++)
		{
			hang++;
			if(theoryTime[i][j]==-99)
			{
				emptyCount++;
			}
			if(theoryTime[i][j]==-88)
			{
				arrayCount++;
				cout<<myVecID[i]<<"   "<<j<<endl;
			}
		}
	}
	cout<<endl<<endl<<"看一下theoryTime这个二维数组到底是不是443900这么大："<<hang<<endl;
	cout<<"看一下填充之后为空和为array的值各是多少："<<emptyCount<<"   "<<arrayCount<<endl;

	delete oneDay;
	oneDay=NULL;
}

void Theory::calculateAccessByTheory()
{
	selectedPOINum=myDistrict->get_chosedPOInum();                                           
	if(selectedPOINum>100)                                                                   
	{ 
		selectedPOINum=100;
	}
	double tripTimeMax=12200+1000;                                    
	double tripTimeMin=200;
	for(int i=0;i<myDistrict->get_classCount()+1;i++)                 
	{
		accessValueByTheory.push_back(0);
		meanTimeValue.push_back(0);
	}

	double theoryMaxAccessValue=0;                                        
	double temp_maxTime=(tripTimeMax-tripTimeMin)/60.0;                   
	for(int i=0;i<selectedPOINum;i++)                                
	{
		theoryMaxAccessValue+=temp_maxTime*myPOIWeight[i];
	}
	cout<<"看一下最大的理论未归一化的值："<<theoryMaxAccessValue<<endl;         
	cout<<"看一下选择得POI得个数："<<selectedPOINum<<endl;


	double temp_ableGoingTimes=0;                                                         
	double sum_POIWeight=0;                                                               
	cout<<"这里老是到最后一下断了"<<"是不是4439："<<theoryTime.size()<<endl;
	cout<<"是不是小于等于100："<<selectedPOINum<<endl;                                    
	for(unsigned int i=0;i<theoryTime.size();i++)                                          
	{
		 
		for(int j=0;j<selectedPOINum;j++)                            
		{
			if(theoryTime[i][j]==-99 || theoryTime[i][j]==-88 || theoryTime[i][j]>tripTimeMax)        
			{
				continue;
			}
			temp_ableGoingTimes++;
		}

		 
		double tempSumTime = 0;                                      
		for(int j=0;j<selectedPOINum;j++)                            
		{
			if(theoryTime[i][j]==-99 || theoryTime[i][j]==-88 || theoryTime[i][j]>tripTimeMax)        
			{
				continue;
			}
			accessValueByTheory[myVecID[i]] += ((tripTimeMax-theoryTime[i][j])/60.0)*(1.0/temp_ableGoingTimes)*myPOIWeight[j];    
			tempSumTime += theoryTime[i][j];
			sum_POIWeight+=myPOIWeight[j];
		}
		meanTimeValue[myVecID[i]]=(tempSumTime/60.0)/temp_ableGoingTimes;             
		 
		 

		sum_POIWeight=0;
		temp_ableGoingTimes=0;
	}
	cout<<"理论可达值计算完毕！！！开始把理论可达值输出"<<endl;

	ofstream outfile1;
	ofstream outfile2;
	outfile1.open("D:\\data\\深圳数据\\修剪数据5\\accessValueByTheory.csv");
	outfile2.open("D:\\data\\深圳数据\\修剪数据5\\accessValueByTheory4439.csv");                                          
	for(unsigned int i=0;i<accessValueByTheory.size();i++)                                     
	{
		outfile1<<fixed<<setprecision(6)<<i<<","<<accessValueByTheory[i]<<","<<meanTimeValue[i]<<endl;                
	}

	double mean_meanTimeValue=0;                                                               
	for(unsigned int i=0;i<myVecID.size();i++)                                                 
	{
		mean_meanTimeValue += meanTimeValue[myVecID[i]];
	}
	mean_meanTimeValue /= myVecID.size();
	cout<<"看一下实际平均出行时间的均值是不是大概71分钟："<<mean_meanTimeValue<<endl;

	for(unsigned int i=0;i<myVecID.size();i++)                                                 
	{
		outfile2<<fixed<<setprecision(6)<<i<<","<<accessValueByTheory[myVecID[i]]<<","<<meanTimeValue[myVecID[i]]<<","<<myDistrict->get_accessValueByClass(myVecID[i])<<",";
		if(meanTimeValue[myVecID[i]] > 2*mean_meanTimeValue)
		{
			outfile2<<0.0<<",";
		}
		else
		{
			outfile2<<(1-meanTimeValue[myVecID[i]]/(2*mean_meanTimeValue))<<",";
		}
		if(myDistrict->get_accessMeanTimeByClass(myVecID[i])==220)                                                    
		{
			outfile2<<fixed<<setprecision(6)<<myDistrict->get_accessMeanTimeByClass(myVecID[i])<<","<<0-myDistrict->get_accessMeanTimeByClass(myVecID[i])<<endl;
		}
		else
		{
			outfile2<<fixed<<setprecision(6)<<myDistrict->get_accessMeanTimeByClass(myVecID[i])<<","<<meanTimeValue[myVecID[i]]-myDistrict->get_accessMeanTimeByClass(myVecID[i])<<endl;
		}
	}

	outfile1.close();
	outfile2.close();
}

void Theory::makeTheoryPOIMap()
{
	Trip* oneDay;                                        
	oneDay=new Trip();                                   

	pair<map<double,int>::iterator,bool> Insert_Pair;
	for(int i=0;i<selectedPOINum;i++)                                          
	{
		Insert_Pair=theoryPOI_exist.insert(pair<double,int>(oneDay->getGridPos(myPOIVecX[i],myPOIVecY[i]),i));             
		if(Insert_Pair.second==false)
		{
			cout<<i<<"   "<<oneDay->getGridPos(myPOIVecX[i],myPOIVecY[i])<<"  理论中心性POI居然他妈的插入失败了，不可能！！！"<<endl;
		}
		 
	}

	delete oneDay;
	oneDay=NULL;
}
void Theory::calculateDistrictToTheoryPOITime()
{
	vector<double> tempTime;                                                
	vector<int> tempNumber;
	for(int i=0;i<myDistrict->get_classCount()+1;i++)                       
	{
		districtToTheoryPOITime.push_back(tempTime);
		districtToTheoryPOINumber.push_back(tempNumber);
	}
	for(int i=0;i<myDistrict->get_classCount()+1;i++)                       
	{
		for(int j=0;j<selectedPOINum;j++)                                   
		{
			districtToTheoryPOITime[i].push_back(0);
			districtToTheoryPOINumber[i].push_back(0);
		}
	}
	 

	int goToTheoryPOI=0;                                                    
	int allTrip=0;                                                          
	for(int i=0;i<myDistrict->get_classCount()+1;i++)                       
	{
		for(int j=0;j<myDistrict->get_classOwnTripID_rowSize(i);j++)              
		{
			allTrip++;
			int tempTripID=myDistrict->get_classOwnTripID(i,j);                                    
			double tempDPos=myDistrict->get_DGridXY(tempTripID);                                   
			if(theoryPOI_exist.count(tempDPos)!=0)                                                 
			{
				if(i==3724 && theoryPOI_exist[tempDPos]==95)
				{
					seeTripInfo(tempTripID,i);
				}
				districtToTheoryPOITime[i][theoryPOI_exist[tempDPos]]+=myDistrict->get_timeDiff(tempTripID);               
				districtToTheoryPOINumber[i][theoryPOI_exist[tempDPos]]++;
				goToTheoryPOI++;
			}
		}
	}
	cout<<"看一下所有分区中去了理论POI的个数是多少："<<goToTheoryPOI<<endl;
	cout<<"看一下所有分区中的trip次数共有多少："<<allTrip<<endl;
	cout<<"看一下所有分区中去了理论POI的个数占总trip次数的百分比是："<<double(goToTheoryPOI)/allTrip<<endl;

	 
	for(int i=0;i<myDistrict->get_classCount()+1;i++)                       
	{
		for(int j=0;j<selectedPOINum;j++)                                   
		{
			if(districtToTheoryPOINumber[i][j]==0)                          
			{
				continue;
			}
			districtToTheoryPOITime[i][j]/=districtToTheoryPOINumber[i][j];
		}
	}

	 

	ofstream outfile1;
	ofstream outfile2;
	outfile1.open("D:\\data\\深圳数据\\修剪数据5\\districtToTheoryPOITime.csv");
	outfile2.open("D:\\data\\深圳数据\\修剪数据5\\districtToTheoryPOINumber.csv");

	for(int i=0;i<myDistrict->get_classCount()+1;i++)                       
	{
		for(int j=0;j<selectedPOINum;j++)                                   
		{
			outfile1<<districtToTheoryPOITime[i][j];
			outfile2<<districtToTheoryPOINumber[i][j];
			if(j==selectedPOINum-1)
			{
				outfile1<<endl;
				outfile2<<endl;
			}
			else
			{
				outfile1<<",";
				outfile2<<",";
			}
		}
	}

	outfile1.close();
	outfile2.close();
}

void Theory::readFinalDistrictToTheoryPOITime()
{
	Trip* oneDay;                                        
	oneDay=new Trip();                                   

	 
	vector<vector<double>> temp_finalDistrictToTheoryPOITime;      
	vector<vector<double>> temp_finalDistrictToTheoryPOINumber;    

	vector<double> tempTime;                                                
	vector<double> tempNumber;
	for(int i=0;i<myDistrict->get_classCount()+1;i++)                       
	{
		finalDistrictToTheoryPOITime.push_back(tempTime);
		finalDistrictToTheoryPOINumber.push_back(tempNumber);
		temp_finalDistrictToTheoryPOITime.push_back(tempTime);
		temp_finalDistrictToTheoryPOINumber.push_back(tempNumber);
	}
	for(int i=0;i<myDistrict->get_classCount()+1;i++)                       
	{
		for(int j=0;j<selectedPOINum;j++)                                   
		{
			finalDistrictToTheoryPOITime[i].push_back(0);
			finalDistrictToTheoryPOINumber[i].push_back(0);
			temp_finalDistrictToTheoryPOITime[i].push_back(0);
			temp_finalDistrictToTheoryPOINumber[i].push_back(0);
		}
	}

	ifstream fin1("D:\\data\\深圳数据\\修剪数据5\\districtToTheoryPOITime工作日.csv");          
	string line;
	int number=0;
	while(getline(fin1,line))     
	{
		istringstream sin(line);   
		string field;
		int i=0;
		while (getline(sin,field,',')) 
		{
			finalDistrictToTheoryPOITime[number][i]+=oneDay->convertStringToDouble(field);
			i++;
		}
		number++;
		if(number>=18109)
		{
			break;
		}
	}
	cout<<"看是不是准确的18109："<<number<<endl;

	ifstream fin3("D:\\data\\深圳数据\\修剪数据5\\districtToTheoryPOINumber工作日.csv");          
	number=0;
	while(getline(fin3,line))     
	{
		istringstream sin(line);   
		string field;
		int i=0;
		while (getline(sin,field,',')) 
		{
			finalDistrictToTheoryPOINumber[number][i]+=oneDay->convertStringToDouble(field);
			i++;
		}
		number++;
		if(number>=18109)
		{
			break;
		}
	}
	cout<<"看是不是准确的18109："<<number<<endl;

	 
	 
	number = 0;
	for(unsigned int i=0;i<finalDistrictToTheoryPOITime.size();i++)                       
	{
		for(unsigned int j=0;j<finalDistrictToTheoryPOITime[i].size();j++)                                   
		{
			if(finalDistrictToTheoryPOITime[i][j]==0 && finalDistrictToTheoryPOINumber[i][j]==0)             
			{
				continue;
			} 
			else if(finalDistrictToTheoryPOITime[i][j]!=0 && finalDistrictToTheoryPOINumber[i][j]!=0)        
			{
				finalDistrictToTheoryPOITime[i][j] *= finalDistrictToTheoryPOINumber[i][j];
			}
			else
			{
				cout<<"出错了啊："<<i<<","<<j<<endl;
			}
		}
		number++;
	}
	cout<<"看是不是准确的18109："<<number<<endl;

	ifstream fin2("D:\\data\\深圳数据\\修剪数据5\\districtToTheoryPOITime非工作日.csv");          
	number=0;
	while(getline(fin2,line))     
	{
		istringstream sin(line);   
		string field;
		int i=0;
		while (getline(sin,field,',')) 
		{
			 
			 
			 
			 
			 
			 
			 
			 
			 
			temp_finalDistrictToTheoryPOITime[number][i]+=oneDay->convertStringToDouble(field);
			i++;
		}
		number++;
		if(number>=18109)
		{
			break;
		}
	}
	cout<<"看是不是准确的18109："<<number<<endl;

	ifstream fin4("D:\\data\\深圳数据\\修剪数据5\\districtToTheoryPOINumber非工作日.csv");          
	number=0;
	while(getline(fin4,line))     
	{
		istringstream sin(line);   
		string field;
		int i=0;
		while (getline(sin,field,',')) 
		{
			temp_finalDistrictToTheoryPOINumber[number][i]+=oneDay->convertStringToDouble(field);
			i++;
		}
		number++;
		if(number>=18109)
		{
			break;
		}
	}
	cout<<"看是不是准确的18109："<<number<<endl;

	 
	 
	number = 0;
	for(unsigned int i=0;i<finalDistrictToTheoryPOITime.size();i++)                       
	{
		for(unsigned int j=0;j<finalDistrictToTheoryPOITime[i].size();j++)                                   
		{
			if(temp_finalDistrictToTheoryPOITime[i][j]==0 && temp_finalDistrictToTheoryPOINumber[i][j]==0)             
			{
				continue;
			} 
			else if(temp_finalDistrictToTheoryPOITime[i][j]!=0 && temp_finalDistrictToTheoryPOINumber[i][j]!=0)        
			{
				finalDistrictToTheoryPOITime[i][j] += (temp_finalDistrictToTheoryPOITime[i][j]*temp_finalDistrictToTheoryPOINumber[i][j]);
				finalDistrictToTheoryPOINumber[i][j] += temp_finalDistrictToTheoryPOINumber[i][j];                                            
			}
			else
			{
				cout<<"出错了啊："<<i<<","<<j<<endl;
			}
		}
		number++;
	}
	cout<<"看是不是准确的18109："<<number<<endl;
	 
	
	fin1.close();                                     
	fin2.close();
	fin3.close();
	fin4.close();

	ofstream outfile1;
	ofstream outfile2;
	outfile1.open("D:\\data\\深圳数据\\修剪数据5\\districtToTheoryPOITime合集.csv");
	outfile2.open("D:\\data\\深圳数据\\修剪数据5\\districtToTheoryPOINumber合集.csv");
	number = 0;
	int allIsZero = 0;

	for(unsigned int i=0;i<finalDistrictToTheoryPOITime.size();i++)                       
	{
		for(unsigned int j=0;j<finalDistrictToTheoryPOITime[i].size();j++)                                   
		{
			if(finalDistrictToTheoryPOITime[i][j]!=0 && finalDistrictToTheoryPOINumber[i][j]!=0)
			{
				finalDistrictToTheoryPOITime[i][j] /= finalDistrictToTheoryPOINumber[i][j];
			}
			else if(finalDistrictToTheoryPOITime[i][j]==0 && finalDistrictToTheoryPOINumber[i][j]==0)
			{
				allIsZero++;
			}
			else
			{
				cout<<"最终算平均时间的时候出错了啊："<<i<<","<<j<<endl;
			}
			outfile1<<finalDistrictToTheoryPOITime[i][j]<<",";
			outfile2<<finalDistrictToTheoryPOINumber[i][j]<<",";
		}
		number++;
		outfile1<<endl;
		outfile2<<endl;
	}
	cout<<"看是不是准确的18109："<<number<<endl;
	cout<<"看看时间和次数同时为0的有多少："<<allIsZero<<endl;

	outfile1.close();
	outfile2.close();

	delete oneDay;
	oneDay=NULL;
}

void Theory::calculateAccessRealTravelTime()
{
	vector<double> access_realMeanTimeValue;                         

	for(int i=0;i<myDistrict->get_classCount()+1;i++)                 
	{
		access_realMeanTimeValue.push_back(0);
		realMeanTimeValue.push_back(0);
		realMeanTimeValueWeight.push_back(0);
	}
	if((myDistrict->get_classCount()+1)!=finalDistrictToTheoryPOITime.size())
	{
		cout<<"calculateAccessRealTravelTime()出错了！！！！"<<endl;
	}
	for(unsigned int i=0;i<finalDistrictToTheoryPOITime.size();i++)              
	{
		 
		double tempSumGoingNum = 0;                                             
		double tempMaxGoingTime = 0;                                            
		for(unsigned int j=0;j<finalDistrictToTheoryPOITime[i].size();j++)        
		{
			tempSumGoingNum += finalDistrictToTheoryPOINumber[i][j];
			if(finalDistrictToTheoryPOITime[i][j]>tempMaxGoingTime)               
			{
				tempMaxGoingTime = finalDistrictToTheoryPOITime[i][j];
			}
		}

		 
		tempMaxGoingTime=12200+1000;                                          

		 
		double tempGoingCostTime = 0;                                         
		for(unsigned int j=0;j<finalDistrictToTheoryPOITime[i].size();j++)       
		{
			if(finalDistrictToTheoryPOITime[i][j]!=0)                            
			{
				if(finalDistrictToTheoryPOITime[i][j] > tempMaxGoingTime)
				{
					cout<<"finalDistrictToTheoryPOITime[i][j] > tempMaxGoingTime！！！！！"<<endl;
					system("pause");
				}
				tempGoingCostTime += (tempMaxGoingTime-finalDistrictToTheoryPOITime[i][j])*(finalDistrictToTheoryPOINumber[i][j]/tempSumGoingNum);
			}
		}
		if(tempSumGoingNum != 0)
		{
			realMeanTimeValueWeight[i] = (tempMaxGoingTime-tempGoingCostTime)/60.0;                   
		}
		else
		{
			realMeanTimeValueWeight[i] = 220;
		}

		 
		double haveValue=0;                                           
		double tempSumTime=0;
		for(unsigned int j=0;j<finalDistrictToTheoryPOITime[i].size();j++)       
		{
			if(finalDistrictToTheoryPOITime[i][j]!=0)                            
			{
				haveValue++;
				tempSumTime+=finalDistrictToTheoryPOITime[i][j];
			}
		}
		if(haveValue!=0)                                                         
		{
			realMeanTimeValue[i]=tempSumTime/haveValue/60.0;                             
		}
		else
		{
			realMeanTimeValue[i]=220;
		}

		 
		for(unsigned int j=0;j<finalDistrictToTheoryPOITime[i].size();j++)       
		{
			if(finalDistrictToTheoryPOITime[i][j]!=0)                            
			{
				access_realMeanTimeValue[i] += ((tempMaxGoingTime-finalDistrictToTheoryPOITime[i][j])/60.0)*(1.0/haveValue)*myPOIWeight[j];   
			}
		}
		if(haveValue==0)                                                         
		{
			access_realMeanTimeValue[i] = 0;                             
		}

		haveValue=0;
		tempSumTime=0;
	}

	double mean_realMeanTimeValue = 0;                                           
	for(unsigned int i=0;i<myVecID.size();i++)                                                 
	{
		mean_realMeanTimeValue += realMeanTimeValue[myVecID[i]];
	}
	mean_realMeanTimeValue /= myVecID.size();
	cout<<"看一下实际平均出行时间的均值是不是大概40分钟："<<mean_realMeanTimeValue<<endl;

	ofstream outfile1;
	ofstream outfile2;
	outfile1.open("D:\\data\\深圳数据\\修剪数据5\\realMeanTimeValue.csv");                                                 
	outfile2.open("D:\\data\\深圳数据\\修剪数据5\\realMeanTimeValue4439.csv");                                             
	for(unsigned int i=0;i<realMeanTimeValue.size();i++)                                     
	{
		outfile1<<fixed<<setprecision(6)<<i<<","<<realMeanTimeValue[i]<<","<<realMeanTimeValueWeight[i]<<endl;                              
	}

	for(unsigned int i=0;i<myVecID.size();i++)                                                 
	{
		outfile2<<fixed<<setprecision(6)<<i<<","<<realMeanTimeValue[myVecID[i]]<<","<<meanTimeValue[myVecID[i]]-realMeanTimeValue[myVecID[i]]<<","<<myVecID[i]+1<<",";
		outfile2<<fixed<<setprecision(6)<<realMeanTimeValueWeight[myVecID[i]]<<","<<access_realMeanTimeValue[myVecID[i]]<<",";                                            
		if(realMeanTimeValue[myVecID[i]] > 2*mean_realMeanTimeValue)                                                      
		{
			outfile2<<0.0<<endl;
		}
		else
		{
			outfile2<<(1-realMeanTimeValue[myVecID[i]]/(2*mean_realMeanTimeValue))<<endl;
		}
	}

	outfile1.close();
	outfile2.close();
}

void Theory::calculateTravelRadius()
{
	Trip* oneDay;                                        
	oneDay=new Trip();                                   

	vector<double> tripTravelRadius;                     
	vector<double> theoryTravelRadius;                   
	vector<double> ratioTravelRadius;                    
	for(unsigned int i=0;i<myVecID.size();i++)           
	{
		tripTravelRadius.push_back(0);                   
		theoryTravelRadius.push_back(0);
		ratioTravelRadius.push_back(0);
	}

	 
	double sumRadiusDis = 0;                             
	double tempDistrictX = 0;                            
	double tempDistrictY = 0;
	for(unsigned int i=0;i<myVecID.size();i++)           
	{
		myDistrict->getClassCenterXY(myVecID[i],tempDistrictX,tempDistrictY);             
		for(int j=0;j<selectedPOINum;j++)                                                 
		{
			sumRadiusDis += oneDay->getTwoPointDistance(tempDistrictX,tempDistrictY,myPOIVecX[j],myPOIVecY[j]);    
		}
		theoryTravelRadius[i] = sumRadiusDis/selectedPOINum;                              
		sumRadiusDis = 0;                                                                 
	}

	 
	sumRadiusDis = 0;  
	double maxGoingPOIDis = 0;                           
	double tempGoingPOIAllSum = 0;                       
	for(unsigned int i=0;i<myVecID.size();i++)           
	{
		myDistrict->getClassCenterXY(myVecID[i],tempDistrictX,tempDistrictY);             

		 
		double tempDis;
		for(int j=0;j<selectedPOINum;j++)                                                 
		{
			if(finalDistrictToTheoryPOINumber[myVecID[i]][j] != 0)                        
			{
				tempDis = oneDay->getTwoPointDistance(tempDistrictX,tempDistrictY,myPOIVecX[j],myPOIVecY[j]);     
				tempGoingPOIAllSum += finalDistrictToTheoryPOINumber[myVecID[i]][j];                              
				if(tempDis > maxGoingPOIDis)                                              
				{
					maxGoingPOIDis = tempDis;
				}
				else
				{
					continue;        
				}
			}
			else
			{
				continue;        
			}
		}

		 
		for(int j=0;j<selectedPOINum;j++)                                                 
		{
			if(finalDistrictToTheoryPOINumber[myVecID[i]][j] != 0)                        
			{
				tempDis = oneDay->getTwoPointDistance(tempDistrictX,tempDistrictY,myPOIVecX[j],myPOIVecY[j]);                            
				sumRadiusDis += (maxGoingPOIDis-tempDis) * (finalDistrictToTheoryPOINumber[myVecID[i]][j]/tempGoingPOIAllSum);       
			}
			else
			{
				continue;        
			}
		}
		tripTravelRadius[i] = maxGoingPOIDis-sumRadiusDis;                                
		sumRadiusDis = 0;                                                                 
		tempGoingPOIAllSum = 0;
		maxGoingPOIDis = 0;
	}

	 
	ofstream outfile1;
	outfile1.open("D:\\data\\深圳数据\\修剪数据5\\ratioTravelRadius.csv");
	ofstream outfile2;
	outfile2.open("D:\\data\\深圳数据\\修剪数据5\\pointToLine_XY.csv");
	ofstream outfile3;
	outfile3.open("D:\\data\\深圳数据\\修剪数据5\\pointToLineWeight.csv");
	double tempDistrictAllNum = 0;                                              
	for(unsigned int i=0;i<myVecID.size();i++)           
	{
		if(tripTravelRadius[i] != 0)                                                      
		{
			ratioTravelRadius[i] = theoryTravelRadius[i]/tripTravelRadius[i];
		}
		else
		{
			ratioTravelRadius[i] = 0;
		}
		for(int j=0;j<selectedPOINum;j++) 
		{
			tempDistrictAllNum += finalDistrictToTheoryPOINumber[myVecID[i]][j];
		}
		outfile1<<fixed<<setprecision(6)<<i<<","<<ratioTravelRadius[i]<<","<<theoryTravelRadius[i]<<","<<tripTravelRadius[i]<<","<<myVecID[i]+1<<","<<tempDistrictAllNum<<endl;

		 
		double tempGo = 0;                                                         
		if(ratioTravelRadius[i]>2 && tempDistrictAllNum>1000)                      
		{
			myDistrict->getClassCenterXY(myVecID[i],tempDistrictX,tempDistrictY);                        
			for(int j=0;j<selectedPOINum;j++)                                            
			{
				if(finalDistrictToTheoryPOINumber[myVecID[i]][j] != 0)             
				{
					outfile2<<fixed<<setprecision(6)<<j<<","<<tempGo<<","<<ratioTravelRadius[i]<<","<<tempDistrictX<<","<<tempDistrictY<<","<<myPOIVecX[j]<<","<<myPOIVecY[j]<<endl;
					 
					outfile3<<fixed<<setprecision(6)<<j<<","<<tempGo<<","<<ratioTravelRadius[i]<<","<<finalDistrictToTheoryPOINumber[myVecID[i]][j]<<endl;
					tempGo++;
				}
			}
			outfile2<<tempGo<<endl;
			outfile3<<tempGo<<endl;
		}
		else
		{
			 
		}

		 
		tempGo = 0;                                                         
		if(i==206 && tempDistrictAllNum==579) 
		{
			myDistrict->getClassCenterXY(myVecID[i],tempDistrictX,tempDistrictY);                        
			for(int j=0;j<selectedPOINum;j++)                                            
			{
				if(finalDistrictToTheoryPOINumber[myVecID[i]][j] != 0)             
				{
					outfile2<<fixed<<setprecision(6)<<j<<","<<tempGo<<","<<ratioTravelRadius[i]<<","<<tempDistrictX<<","<<tempDistrictY<<","<<myPOIVecX[j]<<","<<myPOIVecY[j]<<endl;
					 
					outfile3<<fixed<<setprecision(6)<<j<<","<<tempGo<<","<<ratioTravelRadius[i]<<","<<finalDistrictToTheoryPOINumber[myVecID[i]][j]<<endl;
					tempGo++;
				}
			}
			outfile2<<tempGo<<endl;
			outfile3<<tempGo<<endl;
		}


		tempDistrictAllNum = 0;
	}

	outfile1.close();
	outfile2.close();
	outfile3.close();

	delete oneDay;
	oneDay=NULL;
}
void Theory::seeTripInfo(int tripID,int distrID)
{
	Trip* oneDay;                                        
	oneDay=new Trip();                                   

	double tempDistrictX = 0;                            
	double tempDistrictY = 0;
	myDistrict->getClassCenterXY(distrID,tempDistrictX,tempDistrictY);             

	cout<<"\nLook at this strange trip information:"<<endl;
	cout<<"看一下trip的ID，这个不一定对应："<<tripID<<endl;
	cout<<"看一下trip的时间："<<myDistrict->get_timeDiff(tripID)<<endl;
	cout<<"起点原始所在格网："<<myDistrict->get_OGridXY(tripID)<<endl;
	cout<<"终点所在格网："<<myDistrict->get_DGridXY(tripID)<<endl;
	cout<<"起点被分配到了那个格网（分区中心坐标算出来的所在格网）："<<oneDay->getGridPos(tempDistrictX,tempDistrictY)<<endl;
	cout<<"起点站的中文站名："<<myDistrict->get_OName(tripID)<<endl;
	cout<<"该trip经过了多少个站点，换乘次数（在小数部分）："<<myDistrict->get_ODManyStops(tripID)<<endl<<endl;
	
	delete oneDay;
	oneDay=NULL;
}

void Theory::readRealPOI()
{
	Trip* oneDay;                                        
	oneDay=new Trip();                                   

	ifstream fin("D:\\data\\深圳数据\\修剪数据5\\sortedAttrReal_100POI_madeByAllTrip敲定2.csv");          
	string line;

	int number=0;
	while(getline(fin,line))     
	{
		istringstream sin(line);   
		string field;
		int i=1;
		while (getline(sin,field,',')) 
		{
			if(i==2)
			{
				myRealPOIDistrictID.push_back(int(oneDay->convertStringToDouble(field)));        
				if(myRealPOIDistrictID[number]-oneDay->convertStringToDouble(field)!=0)              
				{
					cout<<"double转int出了精度问题！！"<<endl;
					system("pause");
				}
				i++;
			}
			else if(i==3)
			{
				myRealPOIWeight.push_back(oneDay->convertStringToDouble(field));   
				i++;
			}
			else
			{
				i++;
				continue;
			}
		}
		number++;
	}
	cout<<myRealPOIDistrictID.size()<<"   《--实际POI数 和 POI权重数--》   "<<myRealPOIWeight.size()<<endl;
	
	fin.close();
	delete oneDay;
	oneDay=NULL;
}
void Theory::makeRealPOIMap()
{
	pair<map<int,int>::iterator,bool> Insert_Pair;
	for(int i=0;i<selectedPOINum;i++)                                          
	{
		Insert_Pair=realPOI_exist.insert(pair<int,int>(myRealPOIDistrictID[i],i));             
		if(Insert_Pair.second==false)
		{
			cout<<i<<"   "<<myRealPOIDistrictID[i]<<"  实际POI居然他妈的插入失败了，不可能！！！"<<endl;
		}
	}
	 
	cout<<"就看一个实际POI的分区号，前三个是不是1527、1832、1690："<<myRealPOIDistrictID[0]<<","<<myRealPOIDistrictID[1]<<","<<myRealPOIDistrictID[2]<<endl;
}
void Theory::calculateDistrictToRealPOITime()
{
	vector<double> tempTime;                                                
	vector<int> tempNumber;
	for(int i=0;i<myDistrict->get_classCount()+1;i++)                       
	{
		districtToRealPOITime.push_back(tempTime);
		districtToRealPOINumber.push_back(tempNumber);
	}
	for(int i=0;i<myDistrict->get_classCount()+1;i++)                       
	{
		for(int j=0;j<selectedPOINum;j++)                                   
		{
			districtToRealPOITime[i].push_back(0);
			districtToRealPOINumber[i].push_back(0);
		}
	}
	 

	int goToRealPOI=0;                                                    
	int allTrip=0;                                                          
	for(int i=0;i<myDistrict->get_classCount()+1;i++)                       
	{
		for(int j=0;j<myDistrict->get_classOwnTripID_rowSize(i);j++)              
		{
			allTrip++;
			int tempTripID=myDistrict->get_classOwnTripID(i,j);                                    
			double tempDPos=myDistrict->get_DGridXY(tempTripID);                                   
			int tempDDistrictID=myDistrict->get_gridRCtoClass(tempDPos);                           
			if(realPOI_exist.count(tempDDistrictID)!=0)                                                 
			{
				districtToRealPOITime[i][realPOI_exist[tempDDistrictID]]+=myDistrict->get_timeDiff(tempTripID);               
				districtToRealPOINumber[i][realPOI_exist[tempDDistrictID]]++;
				goToRealPOI++;
			}
		}
	}
	cout<<"看一下所有分区中去了实际POI的个数是多少："<<goToRealPOI<<endl;
	cout<<"看一下所有分区中的trip次数共有多少："<<allTrip<<endl;
	cout<<"看一下所有分区中去了实际POI的个数占总trip次数的百分比是："<<double(goToRealPOI)/allTrip<<endl;

	 

	ofstream outfile1;
	ofstream outfile2;
	outfile1.open("D:\\data\\深圳数据\\修剪数据5\\districtToRealPOITime.csv");
	outfile2.open("D:\\data\\深圳数据\\修剪数据5\\districtToRealPOINumber.csv");

	for(int i=0;i<myDistrict->get_classCount()+1;i++)                       
	{
		for(int j=0;j<selectedPOINum;j++)                                   
		{
			outfile1<<districtToRealPOITime[i][j];
			outfile2<<districtToRealPOINumber[i][j];
			if(j==selectedPOINum-1)
			{
				outfile1<<endl;
				outfile2<<endl;
			}
			else
			{
				outfile1<<",";
				outfile2<<",";
			}
		}
	}

	outfile1.close();
	outfile2.close();
}
void Theory::readFinalDistrictToRealPOITime()
{
	Trip* oneDay;                                        
	oneDay=new Trip();                                   

	vector<double> tempTime;                                                
	vector<double> tempNumber;
	for(int i=0;i<myDistrict->get_classCount()+1;i++)                       
	{
		finalDistrictToRealPOITime.push_back(tempTime);
		finalDistrictToRealPOINumber.push_back(tempNumber);
	}
	for(int i=0;i<myDistrict->get_classCount()+1;i++)                       
	{
		for(int j=0;j<selectedPOINum;j++)                                   
		{
			finalDistrictToRealPOITime[i].push_back(0);
			finalDistrictToRealPOINumber[i].push_back(0);
		}
	}

	ifstream fin1("D:\\data\\深圳数据\\修剪数据5\\districtToRealPOITime工作日2.csv");          
	string line;
	int number=0;
	while(getline(fin1,line))     
	{
		istringstream sin(line);   
		string field;
		int i=0;
		while (getline(sin,field,',')) 
		{
			finalDistrictToRealPOITime[number][i]+=oneDay->convertStringToDouble(field);
			i++;
		}
		number++;
		if(number>=18109)
		{
			break;
		}
	}
	cout<<"Real看是不是准确的18109："<<number<<endl;

	ifstream fin3("D:\\data\\深圳数据\\修剪数据5\\districtToRealPOINumber工作日2.csv");          
	number=0;
	while(getline(fin3,line))     
	{
		istringstream sin(line);   
		string field;
		int i=0;
		while (getline(sin,field,',')) 
		{
			finalDistrictToRealPOINumber[number][i]+=oneDay->convertStringToDouble(field);
			i++;
		}
		number++;
		if(number>=18109)
		{
			break;
		}
	}
	cout<<"Real看是不是准确的18109："<<number<<endl;

	ifstream fin2("D:\\data\\深圳数据\\修剪数据5\\districtToRealPOITime非工作日2.csv");          
	number=0;
	while(getline(fin2,line))     
	{
		istringstream sin(line);   
		string field;
		int i=0;
		while (getline(sin,field,',')) 
		{
			finalDistrictToRealPOITime[number][i]+=oneDay->convertStringToDouble(field);
			i++;
		}
		number++;
		if(number>=18109)
		{
			break;
		}
	}
	cout<<"Real看是不是准确的18109："<<number<<endl;

	ifstream fin4("D:\\data\\深圳数据\\修剪数据5\\districtToRealPOINumber非工作日2.csv");          
	number=0;
	while(getline(fin4,line))     
	{
		istringstream sin(line);   
		string field;
		int i=0;
		while (getline(sin,field,',')) 
		{
			finalDistrictToRealPOINumber[number][i]+=oneDay->convertStringToDouble(field);
			i++;
		}
		number++;
		if(number>=18109)
		{
			break;
		}
	}
	cout<<"Real看是不是准确的18109："<<number<<endl;

	fin1.close();                                     
	fin2.close();
	fin3.close();
	fin4.close();

	ofstream outfile1;
	ofstream outfile2;
	outfile1.open("D:\\data\\深圳数据\\修剪数据5\\districtToRealPOITime合集.csv");
	outfile2.open("D:\\data\\深圳数据\\修剪数据5\\districtToRealPOINumber合集.csv");
	number = 0;
	int allIsZero = 0;

	for(unsigned int i=0;i<finalDistrictToRealPOITime.size();i++)                       
	{
		for(unsigned int j=0;j<finalDistrictToRealPOITime[i].size();j++)                                   
		{
			if(finalDistrictToRealPOITime[i][j]!=0 && finalDistrictToRealPOINumber[i][j]!=0)
			{
				finalDistrictToRealPOITime[i][j] /= finalDistrictToRealPOINumber[i][j];
			}
			else if(finalDistrictToRealPOITime[i][j]==0 && finalDistrictToRealPOINumber[i][j]==0)
			{
				allIsZero++;
			}
			else
			{
				cout<<"Real最终算平均时间的时候出错了啊："<<i<<","<<j<<endl;
				system("pause");
			}
			outfile1<<finalDistrictToRealPOITime[i][j]<<",";
			outfile2<<finalDistrictToRealPOINumber[i][j]<<",";
		}
		number++;
		outfile1<<endl;
		outfile2<<endl;
	}
	cout<<"Real看是不是准确的18109："<<number<<endl;
	cout<<"Real看看时间和次数同时为0的有多少："<<allIsZero<<endl;

	outfile1.close();
	outfile2.close();

	delete oneDay;
	oneDay=NULL;
}
void Theory::calculateAccessRealPOITravelTime()
{
	for(int i=0;i<myDistrict->get_classCount()+1;i++)                 
	{
		realPOIMeanTimeValue.push_back(0);
	}
	if((myDistrict->get_classCount()+1)!=finalDistrictToRealPOITime.size())
	{
		cout<<"calculateAccessRealPOITravelTime()出错了！！！！"<<endl;
		system("pause");
	}
	for(unsigned int i=0;i<finalDistrictToRealPOITime.size();i++)              
	{
		 
		double tempSumGoingNum = 0;                                             
		double tempMaxGoingTime = 0;                                            
		for(unsigned int j=0;j<finalDistrictToRealPOITime[i].size();j++)        
		{
			tempSumGoingNum += finalDistrictToRealPOINumber[i][j];
			if(finalDistrictToRealPOITime[i][j]>tempMaxGoingTime)               
			{
				tempMaxGoingTime = finalDistrictToRealPOITime[i][j];
			}
		}

		 
		tempMaxGoingTime=12200+1000;                                          

		 
		double tempGoingCostTime = 0;                                         
		for(unsigned int j=0;j<finalDistrictToRealPOITime[i].size();j++)       
		{
			if(finalDistrictToRealPOITime[i][j]!=0)                            
			{
				if(finalDistrictToRealPOITime[i][j] > tempMaxGoingTime)
				{
					cout<<"finalDistrictToRealPOITime[i][j] > tempMaxGoingTime！！！！！"<<endl;
					system("pause");
				}
				tempGoingCostTime += (tempMaxGoingTime-finalDistrictToRealPOITime[i][j])*(finalDistrictToRealPOINumber[i][j]/tempSumGoingNum);
			}
		}
		if(tempSumGoingNum != 0)
		{
			realPOIMeanTimeValue[i] = (tempMaxGoingTime-tempGoingCostTime)/60.0;        
		}
		else
		{
			realPOIMeanTimeValue[i] = 220;
		}
	}


	 
	 
	ofstream outfile3;
	outfile3.open("D:\\data\\深圳数据\\修剪数据5\\pointRealToLine_XY_withWeight.csv");
	double tempDistrictX = 0;                            
	double tempDistrictY = 0;
	double tempRealPOIX = 0;                             
	double tempRealPOIY = 0;
	double mean_realPOIMeanTimeValue = 0;                                           
	for(unsigned int i=0;i<myVecID.size();i++)                                                 
	{
		mean_realPOIMeanTimeValue += realPOIMeanTimeValue[myVecID[i]];

		double tempDistrictAllNum = 0;
		for(int j=0;j<selectedPOINum;j++) 
		{
			tempDistrictAllNum += finalDistrictToRealPOINumber[myVecID[i]][j];
		}

		int tempGo = 0;                                                         
		if(i==10 || i==17 || i==18) 
		{
			myDistrict->getClassCenterXY(myVecID[i],tempDistrictX,tempDistrictY);                        
			for(int j=0;j<selectedPOINum;j++)                                            
			{
				if(finalDistrictToRealPOINumber[myVecID[i]][j] != 0)             
				{
					myDistrict->getClassCenterXY(myRealPOIDistrictID[j],tempRealPOIX,tempRealPOIY);                        
					outfile3<<fixed<<setprecision(6)<<j<<","<<tempGo<<","<<tempDistrictX<<","<<tempDistrictY<<","<<tempRealPOIX<<","<<tempRealPOIY<<",";
					outfile3<<fixed<<setprecision(6)<<finalDistrictToRealPOINumber[myVecID[i]][j]<<endl;
					tempGo++;
				}
			}
			outfile3<<tempGo<<endl;
		}
	}
	mean_realPOIMeanTimeValue /= myVecID.size();
	cout<<"Real看一下实际平均出行时间的均值是不是大概49分钟："<<mean_realPOIMeanTimeValue<<endl;

	ofstream outfile1;
	ofstream outfile2;
	outfile1.open("D:\\data\\深圳数据\\修剪数据5\\realPOIMeanTimeValue.csv");
	outfile2.open("D:\\data\\深圳数据\\修剪数据5\\realPOIMeanTimeValue4439.csv");                                                
	for(unsigned int i=0;i<realPOIMeanTimeValue.size();i++)                                     
	{
		outfile1<<fixed<<setprecision(6)<<i<<","<<realPOIMeanTimeValue[i]<<endl;                              
	}

	double tempDistrictAllNum=0;                                                               
	for(unsigned int i=0;i<myVecID.size();i++)                                                 
	{
		outfile2<<fixed<<setprecision(6)<<i<<","<<realPOIMeanTimeValue[myVecID[i]]<<","<<myVecID[i]+1<<",";
		for(int j=0;j<selectedPOINum;j++) 
		{
			tempDistrictAllNum += finalDistrictToRealPOINumber[myVecID[i]][j];
		}
		outfile2<<fixed<<setprecision(6)<<tempDistrictAllNum<<",";
		if(realPOIMeanTimeValue[myVecID[i]] > 2*mean_realPOIMeanTimeValue)
		{
			outfile2<<0.0<<endl;
		}
		else
		{
			outfile2<<(1-realPOIMeanTimeValue[myVecID[i]]/(2*mean_realPOIMeanTimeValue))<<endl;
		}
		tempDistrictAllNum = 0;
	}

	outfile1.close();
	outfile2.close();
	outfile3.close();
}

void Theory::run()
{
	myDistrict->run();                              
	makeGaoDeXY();                                  
	findTheoryInvalidTime();                        
	readTheoryTime();                               
	fillInvalidTime();                              
	calculateAccessByTheory();                      

	makeTheoryPOIMap();                             
	calculateDistrictToTheoryPOITime();             
	readFinalDistrictToTheoryPOITime();             
	calculateAccessRealTravelTime();                
	calculateTravelRadius();                        

	readRealPOI();                                  
	makeRealPOIMap();                               
	calculateDistrictToRealPOITime();               
	readFinalDistrictToRealPOITime();               
	calculateAccessRealPOITravelTime();             

}