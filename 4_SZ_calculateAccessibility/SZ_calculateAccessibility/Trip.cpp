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
					 

					ifstream finTrip2("D:\\data\\��������\\TRIP20180707\\CN\\CN2\\20170406-Trip-statistics-2CN-duration.csv");     
					cout<<"�����˵�"<<tripDay<<"��"<<"   case 2��"<<endl;
					tripDay++;
					readODTrip(finTrip2);	
					finTrip2.close();
					break;
				}
			case 3:
				{
					ifstream finTrip3("D:\\data\\��������\\TRIP20180707\\CN\\CN2\\20170407-Trip-statistics-2CN-duration.csv");      
					cout<<"�����˵�"<<tripDay<<"��"<<"   case 3��"<<endl;
					tripDay++;
					readODTrip(finTrip3);
					finTrip3.close();
					break;
				}
			case 4:
				{
					ifstream finTrip4("D:\\data\\��������\\TRIP20180707\\CN\\CN2\\20170404-Trip-statistics-2CN-duration.csv");     
					cout<<"�����˵�"<<tripDay<<"��"<<"   case 4��"<<endl;
					tripDay++;
					readODTrip(finTrip4);
					finTrip4.close();
					break;
				}
			case 5:
				{
					ifstream finTrip5("D:\\data\\��������\\TRIP20180707\\CN\\CN2\\20170409-Trip-statistics-2CN-duration.csv");       
					cout<<"�����˵�"<<tripDay<<"��"<<"   case 5��"<<endl;
					tripDay++;
					readODTrip(finTrip5);
					finTrip5.close();
					break;
				}
			case 6:
				{
					ifstream finTrip6("D:\\data\\��������\\TRIP20180707\\CN\\CN2\\20170404-Trip-statistics-2CN-duration.csv");     
					cout<<"�����˵�"<<tripDay<<"��"<<"   case 6��"<<endl;
					tripDay++;
					readODTrip(finTrip6);
					finTrip6.close();
					break;
				}
			case 7:
				{
					ifstream finTrip7("D:\\data\\��������\\TRIP20180707\\CN\\CN2\\20170403-Trip-statistics-2CN-duration.csv");         
					cout<<"�����˵�"<<tripDay<<"��"<<"   case 7��"<<endl;                                                             
					tripDay++;
					readODTrip(finTrip7);
					finTrip7.close();
					break;
				}
			default:
				{
					cout<<"������switch���ϵ��������������������"<<endl;
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
			cout<<"��"<<number<<"����ʱ���Ⱥ�����"<<endl;
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
			cout<<"tempOhour>=0&&tempOhour<=24��Ȼ���������Χ"<<endl;
		}*/

		if(number==times*100000)
		{
			cout<<number<<endl;      
			times++;
		}
		if(number>2.0*tStop)      
		{
			cout<<"��Ҫ��ǰ�������ˣ�"<<endl;
			break;
		}
	}
	countTripCardIDMost();                          

	cout<<"��ʱ����push_back��vector���ܵ�trip������"<<timeDiff.size()<<"    ������ô���У�"<<number<<endl;
	cout<<"�³�ʱ�䷴������ǰ�˵ĸ�����push����trip���ˣ�"<<countNight<<endl;
	cout<<"���³�ʱ����̫�̻�̫����push����trip���ˣ�"<<timeTooShortCount<<endl;
	cout<<"���趨��ʱ����ڣ����г�ʱ�䳤��û������������£�����ʱ�仹�������˵��ж��ٸ���"<<durationInvalid6677<<endl;
	cout<<"trip��ȡ��ϣ�������"<<endl<<endl;

	cout<<"trip�������վ�����ۻ�����ͳ����ϣ�������"<<endl<<endl;

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
	Insert_Pair=subwayLineNumber.insert(pair<string,string>("����һ����","-1"));
	if(Insert_Pair.second==false)
	{
		cout<<"������·map����ʧ���ˣ������ܣ�����"<<endl;
	}
	Insert_Pair=subwayLineNumber.insert(pair<string,string>("����������","-2"));
	if(Insert_Pair.second==false)
	{
		cout<<"������·map����ʧ���ˣ������ܣ�����"<<endl;
	}
	Insert_Pair=subwayLineNumber.insert(pair<string,string>("����������","-3"));
	if(Insert_Pair.second==false)
	{
		cout<<"������·map����ʧ���ˣ������ܣ�����"<<endl;
	}
	Insert_Pair=subwayLineNumber.insert(pair<string,string>("�����ĺ���","-4"));
	if(Insert_Pair.second==false)
	{
		cout<<"������·map����ʧ���ˣ������ܣ�����"<<endl;
	}
	Insert_Pair=subwayLineNumber.insert(pair<string,string>("���������","-5"));
	if(Insert_Pair.second==false)
	{
		cout<<"������·map����ʧ���ˣ������ܣ�����"<<endl;
	}


	Insert_Pair=subwayLineNumber.insert(pair<string,string>("�����ߺ���","-7"));
	if(Insert_Pair.second==false)
	{
		cout<<"������·map����ʧ���ˣ������ܣ�����"<<endl;
	}
	Insert_Pair=subwayLineNumber.insert(pair<string,string>("�����ź���","-9"));
	if(Insert_Pair.second==false)
	{
		cout<<"������·map����ʧ���ˣ������ܣ�����"<<endl;
	}
	Insert_Pair=subwayLineNumber.insert(pair<string,string>("����ʮһ����","-11"));
	if(Insert_Pair.second==false)
	{
		cout<<"������·map����ʧ���ˣ������ܣ�����"<<endl;
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
		cout<<"singleStopName.size()��"<<singleStopName.size()<<"butվ��Ӧ������ô��"<<numberSingle<<endl;
		cout<<"OAccumulation.size()��"<<OAccumulation.size()<<endl;
		cout<<"singleStopName.size()��OAccumulation.size()��Ȼ����ȣ���"<<endl;
	}

	ofstream outfile1;
	outfile1.open("D:\\data\\��������\\�޼�����2\\OAccumulation.csv");
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
	ifstream finBus("D:\\data\\��������\\�޼�����1\\merge_BusStation�Ľ�dbscan�ӵ���.csv");    
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
	cout<<"read���1��������"<<endl;
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
			cout<<"oneWStopNameToID��ô���ܲ����������"<<endl;
		}
	}

	int noFind=0;                                            
	int yesFind=0;                                           
	int badSubwayFind=0;                                     
	int times=1;                                             
	cout<<endl<<endl<<"�Һ����trip��ID���ȫ�ǻ���������ֵģ�����0��ʼ��Ȼ������ǣ�"<<OStopName.size()<<endl<<endl;
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
	cout<<"���trip��������ǧ�򼶣�Ӧ�ú� noFind + yesFind ��ֵ��ͬ"<<endl;
	cout<<"�ۻ���Щtrip���У�һ���վ����Ҳ�е������yesFind��ֵ�ǣ� "<<yesFind<<endl;
	cout<<"�ۻ���Щtrip���У���һ���վ����û�е������noFind��ֵ�ǣ� "<<noFind<<endl;
	cout<<"badSubwayFind��ֵ�ǣ� "<<badSubwayFind<<endl;
	cout<<"trip�������ǣ� "<<OStopName.size()<<endl;
	cout<<"�����ҵ�map��û��map����"<<oneWStopNameToID.size()<<endl;

	 
	int sumTripID=0;                                            
	for(unsigned int i=0;i<oneWStopName.size();i++)           
	{
		sumTripID=sumTripID+stopStartTripIDInclude[i].size();
		if(stopStartTripIDInclude[i].size()!=stopStartCount[i])
		{
			cout<<"push��ȥ��trip��ID�ź�ͳ�Ƶ�count��Ȼ����ȣ�����  "<<stopStartTripIDInclude[i].size()<<" --  "<<stopStartCount[i]<<endl;
		}
	}
	cout<<"������push��ȥ��tripID����û������sumTripID��"<<sumTripID<<endl;

	 

	ofstream outfile1;
	outfile1.open("D:\\data\\��������\\�޼�����2\\stopStartCount.csv");
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
			cout<<"���һ�����������ˣ��������ڶ����ֲ����ˣ�"<<str1<<endl;
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
	string zhan="վ";
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
			cout<<"��ô���ܵ����ڶ����ַ�����1��"<<str1<<endl;
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
	ifstream finBus("D:\\data\\��������\\�޼�����2\\stopNearestGrid.csv");             
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
	cout<<"read���1����վ��-�������ʸ�������"<<endl;
}
void Trip::readStopGridDis()
{
	 
	vector<double> tempSG;
	for(unsigned int i=0;i<oneWStopName.size();i++)           
	{
		stopNearestGridDis.push_back(tempSG);
	}
	ifstream finBus("D:\\data\\��������\\�޼�����2\\stopNearestGridDis.csv");             
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
	cout<<"read���1����վ��-��������ʸ�������"<<endl;
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
				cout<<"��ĸ��Ϊ0�˻������������"<<endl;
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
		cout<<"sumFraction�Ĵ�С��Ȼ�������ˣ�����������������������������"<<endl;
	}
	 
	for(unsigned int i=0;i<oneWStopName.size();i++)           
	{
		if(stopEachGridNumber[i].size()!=stopNearestGridDis[i].size())
		{
			cout<<"�Բۣ���Ȼ�����ÿ��վ���µ�size����һ���ۣ�������������������������������������"<<endl;
		}
	}
	
	 
	ofstream outfile1;
	outfile1.open("D:\\data\\��������\\�޼�����2\\stopEachGridNumber.csv");
	outfile1<<"ԭʼӵ��---��һ�η���---������"<<endl;
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
			cout<<"û���ϵø������߶�ֵø��������˱���վ���еø����ø���"<<i<<"  "<<addAndDelete<<"  "<<stopStartCount[i]<<endl;
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
			cout<<"�ֵö�����  "<<i<<"  "<<tempSum2<<"  "<<stopStartCount[i]<<endl;
		}
		if(tempSum2<stopStartCount[i])
		{
			cout<<"�ֵ�������  "<<i<<"  "<<tempSum2<<"  "<<stopStartCount[i]<<endl;
			notGive=notGive+stopStartCount[i];
		}
	}
	cout<<endl<<"��ǰվ���ܹ�����ô������Ҫ�ֵ���û����ȥ������  "<<notGive<<endl<<endl;
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
			cout<<"�Բۣ���Ȼ��һ�£���������������������������������������������������������������������"<<endl;
			cout<<i<<"  "<<stopNearestGridDis[i].size()<<"   "<<stopStartTripIDInclude[i].size()<<endl;
			system("pause");
		}
		for(unsigned int j=0;j<stopStartTripIDInclude[i].size();j++)       
		{
			if(gridPos>=stopEachGridNumber[i].size())                  
			{
				if(gridPos==0 && stopStartTripIDInclude[i].size()>0)       
				{
					cout<<"��ǰվ��û�и���������ʵ�������վ���������trip��������   "<<i<<"  "<<stopStartTripIDInclude[i].size()<<"  "<<endl;
					skipTripID=skipTripID+stopStartTripIDInclude[i].size();
				}
				cout<<"gridPos�Ӽӵ�̫���ˣ���   "<<i<<"  "<<j<<"  "<<gridPos<<"  "<<stopEachGridNumber[i].size()<<endl;
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
	cout<<"����������ǰվ���е���վ���û������û���䵽��ά������ȥ����trip��ID�ж��٣���   "<<skipTripID<<endl;

	for(unsigned int i=0;i<oneWStopName.size();i++)           
	{
		for(unsigned int j=0;j<stopNearestGrid[i].size();j++)       
		{ 
			if(stopEachGridTripID[i][j].size()!=stopEachGridNumber[i][j])     
			{
				cout<<"ʵ�ʷŽ�ȥ��tripID������֮ǰ˵�ø�����������һ��  "<<i<<"  "<<j<<"  "<<stopEachGridTripID[i][j].size()<<"  "<<stopEachGridNumber[i][j]<<endl;
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
		cout<<"��������trip��IDcard�ĺž�Ȼ���ԣ�"<<endl;
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
				cout<<"�ظ��������Ŀ����ǣ�"<<tripCardID[i]<<endl;
			}
			tempRepeat=1;
		}
		 
		 
	}
	cout<<"�ظ��������Ŀ����ǣ�"<<repeatFinal<<"��    ����λ��(��Ϊȥ�����쳣������λ�����ԭʼ�������ڵ���ƫС)�ڣ�"<<repeatPos<<endl;
	cout<<endl<<endl;
	 
}

void Trip::run()
{
	makeSubwayLineMap();                                                                                 
	ifstream finTrip("D:\\data\\��������\\TRIP20180707\\CN\\CN2\\20170405-Trip-statistics-2CN-duration.csv");          
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