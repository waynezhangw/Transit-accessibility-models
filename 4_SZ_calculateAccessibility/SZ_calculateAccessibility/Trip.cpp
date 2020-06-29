#include "Trip.h"

#include<iostream>

#include<math.h>
#include<iomanip>

#define MY_PI 3.1415926535898

using namespace std;

Trip::Trip(void)
{
	OriginX=476499.729847;               
	OriginY=2524560.09966;

	tripDay=2;

	maxBusWalkingDis=400;                       
	maxSubwayWalkingDis=1000;                   
	busOrSubwayDivide=10427;                    

	singleHour=7;
	durationLast=3;                             
}


Trip::~Trip(void)
{
}


void Trip::readODTrip(ifstream &fin)
{
	cout<<tripDay<<endl;

	double sOX,sOY,sDX,sDY;                                                          
	int tempOtime,tempDtime,tempOhour,tempDhour;                                     
	int stops,transfers;                                                             
	string OName,DName;                                                             
	string OSubwayLine;                                                              
	string tempTripID;                                                               
	double tempDuration;                                                             

	 
	 
	string line;
	 
	int times=1;                                                                     
	double tStop=pow(10.0,7);                                                        
	int countNight=0;                                                                
	int timeTooShortCount=0;                                                         
	int number=0;                                                                    
	int durationInvalid6677=0;                                                       
	
	
	while(getline(fin,line))     
	{
		if(line=="end,")
		{
			switch(tripDay)
			{
			case 2:
				{
					 

					ifstream finTrip2("D:\\data\\深圳数据\\TRIP20180707\\CN\\CN2\\20170406-Trip-statistics-2CN-duration.csv");     
					cout<<"换到了第"<<tripDay<<"天"<<"   case 2了"<<endl;
					tripDay++;
					readODTrip(finTrip2);	
					finTrip2.close();
					break;
				}
			case 3:
				{
					ifstream finTrip3("D:\\data\\深圳数据\\TRIP20180707\\CN\\CN2\\20170407-Trip-statistics-2CN-duration.csv");      
					cout<<"换到了第"<<tripDay<<"天"<<"   case 3了"<<endl;
					tripDay++;
					readODTrip(finTrip3);
					finTrip3.close();
					break;
				}
			case 4:
				{
					ifstream finTrip4("D:\\data\\深圳数据\\TRIP20180707\\CN\\CN2\\20170404-Trip-statistics-2CN-duration.csv");     
					cout<<"换到了第"<<tripDay<<"天"<<"   case 4了"<<endl;
					tripDay++;
					readODTrip(finTrip4);
					finTrip4.close();
					break;
				}
			case 5:
				{
					ifstream finTrip5("D:\\data\\深圳数据\\TRIP20180707\\CN\\CN2\\20170409-Trip-statistics-2CN-duration.csv");       
					cout<<"换到了第"<<tripDay<<"天"<<"   case 5了"<<endl;
					tripDay++;
					readODTrip(finTrip5);
					finTrip5.close();
					break;
				}
			case 6:
				{
					ifstream finTrip6("D:\\data\\深圳数据\\TRIP20180707\\CN\\CN2\\20170404-Trip-statistics-2CN-duration.csv");     
					cout<<"换到了第"<<tripDay<<"天"<<"   case 6了"<<endl;
					tripDay++;
					readODTrip(finTrip6);
					finTrip6.close();
					break;
				}
			case 7:
				{
					ifstream finTrip7("D:\\data\\深圳数据\\TRIP20180707\\CN\\CN2\\20170403-Trip-statistics-2CN-duration.csv");         
					cout<<"换到了第"<<tripDay<<"天"<<"   case 7了"<<endl;                                                             
					tripDay++;
					readODTrip(finTrip7);
					finTrip7.close();
					break;
				}
			default:
				{
					cout<<"出现了switch不上的情况！！！！！！！！"<<endl;
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
			if(i==1)           
			{
				tempTripID=field;                                  
				i++;
				continue;
			}
			else if(i==2)           
			{
				tempOtime=convertTimeStringToInt(field);      
				tempOhour=extractTimeHour(field);            
				i++;
				continue;
			}
			else if(i==3)
			{
				OName=field;                            
				i++;
				continue;
			}
			else if(i==4)
			{
				sOX=convertStringToDouble(field);      
				i++;
				continue;
			}
			else if(i==5)
			{
				sOY=convertStringToDouble(field);      
				i++;
				continue;
			}
			else if(i==6)
			{
				tempDtime=convertTimeStringToInt(field);      
				tempDhour=extractTimeHour(field);
				i++;
				continue;
			}
			else if(i==7)
			{
				DName=field;                            
				i++;
				continue;
			}
			else if(i==8)
			{
				sDX=convertStringToDouble(field);      
				i++;
				continue;
			}
			else if(i==9)
			{
				sDY=convertStringToDouble(field);      
				i++;
				 
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
				if(transfers>5)      
				{
					transfers=5;
				}
				i++;
				continue;
			}
			else if(i==15)
			{
				tempDuration=convertStringToDouble(field);
				i++;
				break;
			}

			else
			{
				i++;
				continue;
			}	
		}
		number++;                                                              

		if(tempDhour<tempOhour)                                                
		{
			countNight++; 
			cout<<"第"<<number<<"行有时间先后问题"<<endl;
			continue;                                                   
		}
		
		 
		 
		 
		if(tempOhour>=singleHour && tempOhour<singleHour+durationLast)                                    
		{
			if(tempDtime-tempOtime<200||tempDtime-tempOtime>12600)        
			{                                                             
				timeTooShortCount++;
				continue;
			}
			if(tempDuration==0.66 || tempDuration==0.77)
			{
				durationInvalid6677++;
				continue;
			}
			tripCardID.push_back(tempTripID);                             
			tripDurationTime.push_back(tempDuration);                     

			OStopName.push_back(OName+OSubwayLine);                       
			OGrid_X.push_back(sOX);                                          
			OGrid_Y.push_back(sOY); 
			DGridXY.push_back(getGridPos(sDX,sDY));                          
			timeDiff.push_back(tempDtime-tempOtime+tempOhour/100.0);     
			ODStopNumber.push_back(stops+transfers/10.0);
		}
		/*else
		{
			cout<<"tempOhour>=0&&tempOhour<=24居然不在这个范围"<<endl;
		}*/

		if(number==times*100000)
		{
			cout<<number<<endl;      
			times++;
		}
		if(number>2.0*tStop)      
		{
			cout<<"我要提前跳出来了！"<<endl;
			break;
		}
	}
	countTripCardIDMost();                          

	cout<<"分时段下push_back到vector中总的trip数量："<<timeDiff.size()<<"    读了这么多行："<<number<<endl;
	cout<<"下车时间反而还在前了的个数，push不到trip里了："<<countNight<<endl;
	cout<<"上下车时间间隔太短或太长，push不到trip里了："<<timeTooShortCount<<endl;
	cout<<"在设定的时间段内，且行程时间长短没有跳过的情况下，逗留时间还是跳过了的有多少个："<<durationInvalid6677<<endl;
	cout<<"trip读取完毕！！！！"<<endl<<endl;

	cout<<"trip按照起点站名的累积次数统计完毕！！！！"<<endl<<endl;

}
double Trip::convertStringToDouble(string str1)
{
	 
	double n1;
	const char* ch= str1.c_str();
	n1=atof(ch);                    

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
		if(i==1)      
		{
			istringstream sin(field);
			string field2;
			int j=0;
			while (getline(sin,field2,':'))
			{
				if(j==0)
				{
					double seeHour=convertStringToDouble(field2);                      
					if(seeHour<5 && seeHour>=0)
					{
						second=second+(convertStringToDouble(field2)+24)*3600;
					}
					else
					{
						second=second+convertStringToDouble(field2)*3600;    
					}

					j++;
					continue;
				}
				if(j==1)
				{
					second=second+convertStringToDouble(field2)*60;     
					j++;
					continue;
				}
				if(j==2)
				{
					second=second+convertStringToDouble(field2);       
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
				hour=int(convertStringToDouble(field2));    
				break;
			}
		}
		i++;
	}

	return hour;
}
double Trip::getGridPos(double x,double y)
{
	int row,column;                
	double rowC;                   
	if(y<=OriginY)                 
	{
		row=int((OriginY-y)/100.0+1);
		int yuR=int(OriginY-y)%100;
		if(yuR>=50)
		{
			row=row+1;
		}
	}
	else
	{
		row=1;
	}
	if(x>=OriginX)               
	{
		column=int((x-OriginX)/100.0+1);
		int yuC=int(x-OriginX)%100;
		if(abs(yuC)>=50)
		{
			column=column+1;
		}
	}
	else
	{
		column=1;
	}

	if(row>=401)
	{
		 
		row=401;
	}
	if(column>=830)
	{
		 
		column=830;
	}
	rowC=row+column/1000.0;
	return rowC;                    
}
int Trip::round_double(double temp)
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

int Trip::get_singleHour()
{
	return singleHour;
}
int Trip::get_durationLast()
{
	return durationLast;
}
double Trip::get_OriginX()
{
	return OriginX;
}
double Trip::get_OriginY()
{
	return OriginY;
}
int Trip::get_tripSize()
{
	return int(timeDiff.size());
}
string Trip::get_OStopName(int index)
{
	return OStopName[index];
}

double Trip::get_tripOGrid_X(int index)
{
	return OGrid_X[index];
}
double Trip::get_tripOGrid_Y(int index)
{
	return OGrid_Y[index];
}
double Trip::get_tripDGridXY(int index)
{
	return DGridXY[index];
}
double Trip::get_tripTimeDiff(int index)
{
	return timeDiff[index];
}
double Trip::get_ODStopNumber(int index)
{
	return ODStopNumber[index];
}
string Trip::get_TripCardID(int index)
{
	return tripCardID[index];
}
double Trip::get_TripDurationTime(int index)
{
	return tripDurationTime[index];
}

string Trip::extractSubwayLine(string str1)
{
	string sub;                         
	 
	istringstream sin(str1);   
	string field;
	int i=0;
	while (getline(sin,field,'-')) 
	{
		if(i==1)      
		{
			sub=field;
		}
		i++;
	}
	return sub;
}

void Trip::makeSubwayLineMap()
{
	pair<map<string,string>::iterator,bool> Insert_Pair;
	Insert_Pair=subwayLineNumber.insert(pair<string,string>("地铁一号线","-1"));
	if(Insert_Pair.second==false)
	{
		cout<<"地铁线路map插入失败了，不可能！！！"<<endl;
	}
	Insert_Pair=subwayLineNumber.insert(pair<string,string>("地铁二号线","-2"));
	if(Insert_Pair.second==false)
	{
		cout<<"地铁线路map插入失败了，不可能！！！"<<endl;
	}
	Insert_Pair=subwayLineNumber.insert(pair<string,string>("地铁三号线","-3"));
	if(Insert_Pair.second==false)
	{
		cout<<"地铁线路map插入失败了，不可能！！！"<<endl;
	}
	Insert_Pair=subwayLineNumber.insert(pair<string,string>("地铁四号线","-4"));
	if(Insert_Pair.second==false)
	{
		cout<<"地铁线路map插入失败了，不可能！！！"<<endl;
	}
	Insert_Pair=subwayLineNumber.insert(pair<string,string>("地铁五号线","-5"));
	if(Insert_Pair.second==false)
	{
		cout<<"地铁线路map插入失败了，不可能！！！"<<endl;
	}


	Insert_Pair=subwayLineNumber.insert(pair<string,string>("地铁七号线","-7"));
	if(Insert_Pair.second==false)
	{
		cout<<"地铁线路map插入失败了，不可能！！！"<<endl;
	}
	Insert_Pair=subwayLineNumber.insert(pair<string,string>("地铁九号线","-9"));
	if(Insert_Pair.second==false)
	{
		cout<<"地铁线路map插入失败了，不可能！！！"<<endl;
	}
	Insert_Pair=subwayLineNumber.insert(pair<string,string>("地铁十一号线","-11"));
	if(Insert_Pair.second==false)
	{
		cout<<"地铁线路map插入失败了，不可能！！！"<<endl;
	}
	
}

void Trip::makeOStopNameAccumulation()
{
	vector<string> singleStopName;                                    
	
	 
	vector<double> singleStopX;                                       
	vector<double> singleStopY; 
	
	
	int numberSingle=0;

	pair<map<string,int>::iterator,bool> Insert_Pair;
	for(unsigned int i=0;i<OStopName.size();i++)
	{
		Insert_Pair=OAccumulation.insert(pair<string,int>(OStopName[i],1));
		if(Insert_Pair.second==false)
		{
			OAccumulation[OStopName[i]]++;
		}
		if(Insert_Pair.second==true)
		{
			 
			numberSingle++;
			singleStopName.push_back(OStopName[i]);
			singleStopX.push_back(OGrid_X[i]);
			singleStopY.push_back(OGrid_Y[i]);
		}
	}

	if(singleStopName.size()!=OAccumulation.size())
	{
		cout<<"singleStopName.size()："<<singleStopName.size()<<"but站名应该是这么大："<<numberSingle<<endl;
		cout<<"OAccumulation.size()："<<OAccumulation.size()<<endl;
		cout<<"singleStopName.size()和OAccumulation.size()居然不相等！！"<<endl;
	}

	ofstream outfile1;
	outfile1.open("D:\\data\\深圳数据\\修剪数据2\\OAccumulation.csv");
	for(unsigned int i=0;i<OAccumulation.size();i++)
	{
		outfile1<<fixed<<setprecision(6)<<i<<","<<singleStopName[i]<<","<<OAccumulation[singleStopName[i]]<<",";
		outfile1<<fixed<<setprecision(6)<<singleStopX[i]<<","<<singleStopY[i]<<endl;
	}
	outfile1.close();

}
void Trip::readBusStop()
{
	string name;         
	int ID=0;            
	double X,Y;          
	ifstream finBus("D:\\data\\深圳数据\\修剪数据1\\merge_BusStation改进dbscan加地铁.csv");    
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
	vector<int> tempStop;                                     
	pair<map<string,int>::iterator,bool> Insert_Pair;
	for(unsigned int i=0;i<oneWStopName.size();i++)           
	{
		stopStartTripIDInclude.push_back(tempStop);           
		stopStartCount.push_back(0);												 
		Insert_Pair=oneWStopNameToID.insert(pair<string,int>(oneWStopName[i],i));    
		if(Insert_Pair.second==false)
		{
			cout<<"oneWStopNameToID怎么可能差不进来！！！"<<endl;
		}
	}

	int noFind=0;                                            
	int yesFind=0;                                           
	int badSubwayFind=0;                                     
	int times=1;                                             
	cout<<endl<<endl<<"我后面的trip的ID编号全是基于这个数字的，即从0开始，然后最大是："<<OStopName.size()<<endl<<endl;
	for(unsigned int i=0;i<OStopName.size();i++)            
	{
		 
		 
		if(isSubwayStop(OStopName[i]))                        
		{
			string tempSub=OStopName[i];                      
			tempSub=extractSubwayName(tempSub);               
			if(oneWStopNameToID.count(tempSub)!=0)            
			{
				stopStartCount[oneWStopNameToID[tempSub]]++;                        
				stopStartTripIDInclude[oneWStopNameToID[tempSub]].push_back(i);     
				yesFind++;
			}
			else
			{
				 
				badSubwayFind++;
				noFind++;
			}
		}
		else                                                  
		{
			if(oneWStopNameToID.count(OStopName[i])!=0)                
			{
				stopStartCount[oneWStopNameToID[OStopName[i]]]++;                        
				stopStartTripIDInclude[oneWStopNameToID[OStopName[i]]].push_back(i);     
				yesFind++;
			}
			else                                                       
			{
				if(oneWStopNameToID.count(OStopName[i]+"a")!=0 && oneWStopNameToID.count(OStopName[i]+"b")!=0)        
				{
					 
					double d1=getTwoPointDistance(OGrid_X[i],OGrid_Y[i],oneWX[oneWStopNameToID[OStopName[i]+"a"]],oneWY[oneWStopNameToID[OStopName[i]+"a"]]);
					double d2=getTwoPointDistance(OGrid_X[i],OGrid_Y[i],oneWX[oneWStopNameToID[OStopName[i]+"b"]],oneWY[oneWStopNameToID[OStopName[i]+"b"]]);
					if(d1<=d2)                
					{
						stopStartCount[oneWStopNameToID[OStopName[i]+"a"]]++;
						stopStartTripIDInclude[oneWStopNameToID[OStopName[i]+"a"]].push_back(i);     
						yesFind++;
					}
					else
					{
						stopStartCount[oneWStopNameToID[OStopName[i]+"b"]]++;
						stopStartTripIDInclude[oneWStopNameToID[OStopName[i]+"b"]].push_back(i);     
						yesFind++;
					}
				}
				else                              
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
	cout<<"累积那些trip里有，一万个站点里也有的情况，yesFind的值是： "<<yesFind<<endl;
	cout<<"累积那些trip里有，但一万个站点里没有的情况，noFind的值是： "<<noFind<<endl;
	cout<<"badSubwayFind的值是： "<<badSubwayFind<<endl;
	cout<<"trip的数量是： "<<OStopName.size()<<endl;
	cout<<"看看我的map有没有map坏："<<oneWStopNameToID.size()<<endl;

	 
	int sumTripID=0;                                            
	for(unsigned int i=0;i<oneWStopName.size();i++)           
	{
		sumTripID=sumTripID+stopStartTripIDInclude[i].size();
		if(stopStartTripIDInclude[i].size()!=stopStartCount[i])
		{
			cout<<"push进去的trip的ID号和统计的count居然不相等！！！  "<<stopStartTripIDInclude[i].size()<<" --  "<<stopStartCount[i]<<endl;
		}
	}
	cout<<"看看我push进去的tripID号有没有问题sumTripID："<<sumTripID<<endl;

	 

	ofstream outfile1;
	outfile1.open("D:\\data\\深圳数据\\修剪数据2\\stopStartCount.csv");
	for(unsigned int i=0;i<stopStartCount.size();i++)
	{
		outfile1<<fixed<<setprecision(6)<<i<<","<<oneWStopName[i]<<","<<stopStartCount[i]<<endl;
	}
	outfile1.close();

}
bool Trip::isSubwayStop(string str1)
{
	 
	int lastP=str1.size()-1;                              
	if(str1.size()<3)                                     
	{
		return false;
	}
	if(str1[lastP]=='1' || str1[lastP]=='2' || str1[lastP]=='3' || str1[lastP]=='4' || str1[lastP]=='5' || str1[lastP]=='7'|| str1[lastP]=='9')  
	{
		if(str1[lastP-1]=='-' || str1[lastP-1]=='1')      
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
	int lastP=str1.size()-1;                              
	string tempStr;
	string zhan="站";
	if(str1[lastP-1]=='-')
	{
		tempStr=str1.substr(str1.size()-4,2);                     
		if(tempStr==zhan)                                         
		{
			finalString=str1.substr(0,str1.size()-4);             
			return finalString+str1[lastP];                       
		}
		else                         
		{
			finalString=str1.substr(0,str1.size()-2);
			return finalString+str1[lastP]; 
		}
	}
	else                            
	{
		if(str1[lastP-1]!='1')
		{
			cout<<"怎么可能倒数第二个字符不是1："<<str1<<endl;
		}
		tempStr=str1.substr(str1.size()-5,2);                     
		if(tempStr==zhan)                                         
		{
			finalString=str1.substr(0,str1.size()-5);             
			return finalString+str1[lastP-1]+str1[lastP];         
		}
		else                         
		{
			finalString=str1.substr(0,str1.size()-3);
			return finalString+str1[lastP-1]+str1[lastP]; 
		}
	}
}
double Trip::getTwoPointDistance(double x1,double y1,double x2,double y2)
{
	return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}
void Trip::readStopGrid()
{
	 
	vector<int> tempSG;
	for(unsigned int i=0;i<oneWStopName.size();i++)           
	{
		stopNearestGrid.push_back(tempSG);
	}
	ifstream finBus("D:\\data\\深圳数据\\修剪数据2\\stopNearestGrid.csv");             
	string line;                                   
	ifstream &fin=finBus;
	int number=0;                                                                      
	while(getline(fin,line))     
	{
		istringstream sin(line);   
		string field;
		int i=1;
		while (getline(sin,field,','))   
		{
			if(i>=4)           
			{
				if(field=="end")
				{
					 
					break;
				}
				else
				{
					stopNearestGrid[number].push_back(int(convertStringToDouble(field)));
				}
				i++;
				continue;
			}
			else
			{
				i++;
				continue;
			}	
		}
		number++;                                
	}
	finBus.close();
	cout<<"read大概1万多的站点-格网编号矢量完成了"<<endl;
}
void Trip::readStopGridDis()
{
	 
	vector<double> tempSG;
	for(unsigned int i=0;i<oneWStopName.size();i++)           
	{
		stopNearestGridDis.push_back(tempSG);
	}
	ifstream finBus("D:\\data\\深圳数据\\修剪数据2\\stopNearestGridDis.csv");             
	string line;                                   
	ifstream &fin=finBus;
	int number=0;                                                                      
	while(getline(fin,line))     
	{
		istringstream sin(line);   
		string field;
		int i=1;
		while (getline(sin,field,','))   
		{
			if(i>=4)           
			{
				if(field=="end")
				{
					 
					break;
				}
				else
				{
					stopNearestGridDis[number].push_back(convertStringToDouble(field));
				}
				i++;
				continue;
			}
			else
			{
				i++;
				continue;
			}	
		}
		number++;                                
	}
	finBus.close();
	cout<<"read大概1万多的站点-格网距离矢量完成了"<<endl;
}
void Trip::getStopEachGridNumber()
{
	 
	double busWatershed=200;                                 
	double subwayWatershed=400;                              

	vector<int> temp_stopEachGridNumber;
	for(unsigned int i=0;i<oneWStopName.size();i++)           
	{
		sumFraction.push_back(0);                                  
		stopEachGridNumber.push_back(temp_stopEachGridNumber);     
		for(unsigned int j=0;j<stopNearestGridDis[i].size();j++)       
		{ 
			 

			if(i<busOrSubwayDivide)                          
			{
				if(stopNearestGridDis[i][j]>busWatershed)             
				{
					sumFraction[i]=sumFraction[i]+cos((stopNearestGridDis[i][j]-busWatershed)/(maxBusWalkingDis-150)*MY_PI/2.0);  
				}
				else                                          
				{
					sumFraction[i]=sumFraction[i]+cos((busWatershed-stopNearestGridDis[i][j])/(busWatershed+50)*MY_PI/2.0);        
				}
			}
			else                                              
			{
				if(stopNearestGridDis[i][j]>subwayWatershed)             
				{
					sumFraction[i]=sumFraction[i]+cos((stopNearestGridDis[i][j]-subwayWatershed)/(maxSubwayWalkingDis-300)*MY_PI/2.0);  
				}
				else                                          
				{
					sumFraction[i]=sumFraction[i]+cos((subwayWatershed-stopNearestGridDis[i][j])/(subwayWatershed+100)*MY_PI/2.0);      
				}
			}
			
		}

		for(unsigned int j=0;j<stopNearestGrid[i].size();j++)       
		{ 
			double tempProportion=0;                                                                 
			if(stopNearestGridDis[i][j]==0 || sumFraction[i]==0)
			{
				cout<<"分母都为0了还能输进来！！"<<endl;
			}
			 


			if(i<busOrSubwayDivide)                          
			{
				if(stopNearestGridDis[i][j]>busWatershed)             
				{
					tempProportion=stopStartCount[i]*((cos((stopNearestGridDis[i][j]-busWatershed)/(maxBusWalkingDis-150)*MY_PI/2.0))/sumFraction[i]);     
				}
				else                                          
				{
					tempProportion=stopStartCount[i]*((cos((busWatershed-stopNearestGridDis[i][j])/(busWatershed+50)*MY_PI/2.0))/sumFraction[i]);     
				}
			}
			else                                              
			{
				if(stopNearestGridDis[i][j]>subwayWatershed)             
				{
					tempProportion=stopStartCount[i]*((cos((stopNearestGridDis[i][j]-subwayWatershed)/(maxSubwayWalkingDis-300)*MY_PI/2.0))/sumFraction[i]);
				}
				else                                          
				{
					tempProportion=stopStartCount[i]*((cos((subwayWatershed-stopNearestGridDis[i][j])/(subwayWatershed+100)*MY_PI/2.0))/sumFraction[i]);
				}
			}
			stopEachGridNumber[i].push_back(round_double(tempProportion));                                      
		}
	}
	 
	if(sumFraction.size()!=oneWStopName.size())
	{
		cout<<"sumFraction的大小居然出问题了！！！！！！！！！！！！！！！"<<endl;
	}
	 
	for(unsigned int i=0;i<oneWStopName.size();i++)           
	{
		if(stopEachGridNumber[i].size()!=stopNearestGridDis[i].size())
		{
			cout<<"卧槽，居然分配得每个站点下得size都不一样哇！！！！！！！！！！！！！！！！！！！"<<endl;
		}
	}
	
	 
	ofstream outfile1;
	outfile1.open("D:\\data\\深圳数据\\修剪数据2\\stopEachGridNumber.csv");
	outfile1<<"原始拥有---第一次分完---调整后"<<endl;
	int notGive=0;                                           
	for(unsigned int i=0;i<stopStartCount.size();i++)        
	{
		int tempSum=0;
		outfile1<<fixed<<setprecision(6)<<i<<","<<oneWStopName[i]<<","<<stopStartCount[i]<<",";
		for(unsigned int j=0;j<stopEachGridNumber[i].size();j++)
		{
			tempSum=tempSum+stopEachGridNumber[i][j];
		}
		outfile1<<fixed<<setprecision(6)<<tempSum<<",";
		
		 
		unsigned int addAndDelete=abs(stopStartCount[i]-tempSum);                   
		if(addAndDelete>stopEachGridNumber[i].size())                      
		{
			cout<<"没分上得个数或者多分得个数大于了本来站点有得格网得个数"<<i<<"  "<<addAndDelete<<"  "<<stopStartCount[i]<<endl;
		}
		for(unsigned int j=0;j<addAndDelete;j++)
		{
			if(stopStartCount[i]>tempSum && j<stopEachGridNumber[i].size())                   
			{
				stopEachGridNumber[i][j]=stopEachGridNumber[i][j]+1;
			}
			if(stopStartCount[i]<tempSum && j<stopEachGridNumber[i].size())                   
			{
				if(stopEachGridNumber[i][j]!=0)
				{
					stopEachGridNumber[i][j]=stopEachGridNumber[i][j]-1;
				}
				else
				{
					addAndDelete++;
				}
				
			}
		}
		int tempSum2=0;
		for(unsigned int j=0;j<stopEachGridNumber[i].size();j++)
		{
			tempSum2=tempSum2+stopEachGridNumber[i][j];
		}
		outfile1<<fixed<<setprecision(6)<<tempSum2<<",";
		 
		for(unsigned int j=0;j<stopEachGridNumber[i].size();j++)
		{
			outfile1<<fixed<<setprecision(6)<<stopEachGridNumber[i][j]<<",";
		}
		outfile1<<"end"<<endl;

		if(tempSum2>stopStartCount[i])
		{
			cout<<"分得多了亲  "<<i<<"  "<<tempSum2<<"  "<<stopStartCount[i]<<endl;
		}
		if(tempSum2<stopStartCount[i])
		{
			cout<<"分得少了亲  "<<i<<"  "<<tempSum2<<"  "<<stopStartCount[i]<<endl;
			notGive=notGive+stopStartCount[i];
		}
	}
	cout<<endl<<"当前站点总共有这么多流量要分但是没分下去的数量  "<<notGive<<endl<<endl;
	outfile1.close();
}
void Trip::makeStopEachGridTripID()
{
	vector<vector<int>> temp_stopEachGridTripID;
	vector<int> small_temp_stopEachGridTripID;
	for(unsigned int i=0;i<oneWStopName.size();i++)           
	{
		stopEachGridTripID.push_back(temp_stopEachGridTripID);
		for(unsigned int j=0;j<stopNearestGrid[i].size();j++)       
		{ 
			stopEachGridTripID[i].push_back(small_temp_stopEachGridTripID);     
		}
	}

	 
	for(unsigned int i=0;i<OStopName.size();i++)               
	{
		tripWalkDis.push_back(0);
		tripStopOwnPos.push_back(0);
	}

	 
	int skipTripID=0;                                               
	for(unsigned int i=0;i<stopStartTripIDInclude.size();i++)       
	{
		unsigned int gridPos=0;                                              
		if(stopNearestGridDis[i].size()!=stopEachGridNumber[i].size())       
		{
			cout<<"卧槽，居然不一致！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！"<<endl;
			cout<<i<<"  "<<stopNearestGridDis[i].size()<<"   "<<stopStartTripIDInclude[i].size()<<endl;
			system("pause");
		}
		for(unsigned int j=0;j<stopStartTripIDInclude[i].size();j++)       
		{
			if(gridPos>=stopEachGridNumber[i].size())                  
			{
				if(gridPos==0 && stopStartTripIDInclude[i].size()>0)       
				{
					cout<<"当前站点没有格网，但是实际中这个站点可能又有trip的量！！   "<<i<<"  "<<stopStartTripIDInclude[i].size()<<"  "<<endl;
					skipTripID=skipTripID+stopStartTripIDInclude[i].size();
				}
				cout<<"gridPos加加的太猛了！！   "<<i<<"  "<<j<<"  "<<gridPos<<"  "<<stopEachGridNumber[i].size()<<endl;
				break;
			}
			if(stopEachGridTripID[i][gridPos].size()<unsigned(stopEachGridNumber[i][gridPos]))      
			{
				stopEachGridTripID[i][gridPos].push_back(stopStartTripIDInclude[i][j]);
				tripWalkDis[stopStartTripIDInclude[i][j]]=stopNearestGridDis[i][gridPos];          
				tripStopOwnPos[stopStartTripIDInclude[i][j]]=i+gridPos/1000.0;                     
			}
			if(unsigned(stopEachGridNumber[i][gridPos])==0)                                         
			{
				j--;
			}
			if(stopEachGridTripID[i][gridPos].size()==unsigned(stopEachGridNumber[i][gridPos]))     
			{
				gridPos++;
			}
			
		}
	}
	cout<<"被跳过（当前站点有但因站点就没格网而没分配到三维向量中去）的trip的ID有多少！！   "<<skipTripID<<endl;

	for(unsigned int i=0;i<oneWStopName.size();i++)           
	{
		for(unsigned int j=0;j<stopNearestGrid[i].size();j++)       
		{ 
			if(stopEachGridTripID[i][j].size()!=stopEachGridNumber[i][j])     
			{
				cout<<"实际放进去的tripID数量和之前说好给他的数量不一致  "<<i<<"  "<<j<<"  "<<stopEachGridTripID[i][j].size()<<"  "<<stopEachGridNumber[i][j]<<endl;
			}
		}
	}
	
}
int Trip::get_stopEachGridTripID(int i,int j,int k)
{
	return stopEachGridTripID[i][j][k];
}
int Trip::get_stop_size()
{
	return stopNearestGrid.size();
}
int Trip::get_stopNearestGrid_size(int index)
{
	return stopNearestGrid[index].size();
}
int Trip::get_stopNearestGridID_size(int ind1,int ind2)
{
	return stopEachGridNumber[ind1][ind2];
}
int Trip::get_gridID(int i,int j)
{
	return stopNearestGrid[i][j];
}
double Trip::get_oneWX(int index)
{
	return oneWX[index];
}
double Trip::get_oneWY(int index)
{
	return oneWY[index];
}
string Trip::get_oneWStopName(int index)
{
	return oneWStopName[index];
}
int Trip::get_stopStartCount(int index)
{
	return stopStartCount[index];
}
int Trip::get_busOrSubwayDivide()
{
	return int(busOrSubwayDivide);
}

double Trip::get_tripWalkDis(int index)
{
	return tripWalkDis[index];
}
double Trip::get_tripStopOwnPos(int index)
{
	return tripStopOwnPos[index];
}


 
 
void Trip::countTripCardIDMost()
{
	if(tripCardID.size()!=get_tripSize())
	{
		cout<<"读进来的trip的IDcard的号居然不对？"<<endl;
	}

	int tempRepeat=1;                                          
	int repeatPos=0;                                           
	int repeatFinal=1;
	for(unsigned int i=0;i<tripCardID.size()-1;i++)              
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
		 
		 
	}
	cout<<"重复次数最多的卡号是："<<repeatFinal<<"次    他的位置(因为去除了异常，所以位置相比原始数据所在的行偏小)在："<<repeatPos<<endl;
	cout<<endl<<endl;
	 
}

void Trip::run()
{
	makeSubwayLineMap();                                                                                 
	ifstream finTrip("D:\\data\\深圳数据\\TRIP20180707\\CN\\CN2\\20170405-Trip-statistics-2CN-duration.csv");          
	readODTrip(finTrip);																		         
	finTrip.close();
	makeOStopNameAccumulation();                                                                         
	readBusStop();                                                                                       
	makeStopStartCount();                                                                                
	readStopGrid();                                                                                      
	readStopGridDis();                                                                                   
	getStopEachGridNumber();                                                                             
	makeStopEachGridTripID();                                                                            

}

void Trip::set_SingleHour(int H)
{
	singleHour=H;
}