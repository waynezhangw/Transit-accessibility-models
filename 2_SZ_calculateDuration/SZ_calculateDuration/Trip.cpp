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
	Insert_Pair=subwayLineNumber.insert(pair<string,string>("����һ����","-1"));
	if(Insert_Pair.second==false)
	{
		cout<<"Subway line map insert failed, impossible!!!"<<endl;
	}
	Insert_Pair=subwayLineNumber.insert(pair<string,string>("����������","-2"));
	if(Insert_Pair.second==false)
	{
		cout<<"Subway line map insert failed, impossible!!!"<<endl;
	}
	Insert_Pair=subwayLineNumber.insert(pair<string,string>("����������","-3"));
	if(Insert_Pair.second==false)
	{
		cout<<"Subway line map insert failed, impossible!!!"<<endl;
	}
	Insert_Pair=subwayLineNumber.insert(pair<string,string>("�����ĺ���","-4"));
	if(Insert_Pair.second==false)
	{
		cout<<"Subway line map insert failed, impossible!!!"<<endl;
	}
	Insert_Pair=subwayLineNumber.insert(pair<string,string>("���������","-5"));
	if(Insert_Pair.second==false)
	{
		cout<<"Subway line map insert failed, impossible!!!"<<endl;
	}

	Insert_Pair=subwayLineNumber.insert(pair<string,string>("�����ߺ���","-7"));
	if(Insert_Pair.second==false)
	{
		cout<<"Subway line map insert failed, impossible!!!"<<endl;
	}
	Insert_Pair=subwayLineNumber.insert(pair<string,string>("�����ź���","-9"));
	if(Insert_Pair.second==false)
	{
		cout<<"Subway line map insert failed, impossible!!!"<<endl;
	}
	Insert_Pair=subwayLineNumber.insert(pair<string,string>("����ʮһ����","-11"));
	if(Insert_Pair.second==false)
	{
		cout<<"Subway line map insert failed, impossible!!!"<<endl;
	}
}

void Trip::readODTrip(ifstream &fin)
{
	double sOX,sOY,sDX,sDY;                                          //Ϊ����vector���������������ǰ��ȫ������s����Щ�����ڶ���Ϣ��ʱ���õ��м�ֵ
	int tempOtime,tempDtime,tempOhour,tempDhour;                     //�ֱ�洢ת��������³�������Сʱ��
	int stops,transfers;                                             //�洢���trip���˶��ٸ�վ��ͻ��˴���
	string OName,DName;                                              //�洢trip�����յ������
	string OSubwayLine;                                              //Ϊ�˶�ȡ������Ϣ���м������Ϊ��ȷ����������ڵĵ�������·��
	string tempTripID;                                               //��ʱ��trip�Ŀ���
	
	string line;
	int times=1;                                                                    //���������е��ٶ�
	double tStop=pow(10.0,7);                                                       //���ƶ�������
	int countNight=0;                                                               //�洢���賿��trip����
	int timeTooShortCount=0;                                                        //ʱ����̫�̻�̫��
	int number=0;                                                                   //�ۻ�����
	while(getline(fin,line))    //һ��һ�еĶ� 
	{
		if(line=="end,")
		{
			switch(tripDay)
			{
			case 2:
				{
					ifstream finTrip2("D:\\data\\��������\\TRIP20180707\\CN\\20170406-Trip-statistics-2CN.csv");
					cout<<"now is the"<<tripDay<<"��"<<endl;
					tripDay++;
					//readODTrip(finTrip2);	
					finTrip2.close();
					break;
				}
			case 3:
				{
					ifstream finTrip3("D:\\data\\��������\\TRIP20180707\\CN\\20170407-Trip-statistics-2CN.csv");     //4��7����������
					cout<<"now is the"<<tripDay<<"day"<<endl;
					tripDay++;
					//readODTrip(finTrip3);
					finTrip3.close();
					break;
				}
			case 4:
				{
					ifstream finTrip4("D:\\data\\��������\\TRIP20180707\\CN\\20170408-Trip-statistics-2CN.csv");    //4��8����������
					cout<<"now is the"<<tripDay<<"day"<<endl;
					tripDay++;
					//readODTrip(finTrip4);
					finTrip4.close();
					break;
				}
			case 5:
				{
					ifstream finTrip5("D:\\data\\��������\\TRIP20180707\\CN\\20170409-Trip-statistics-2CN.csv");
					cout<<"now is the"<<tripDay<<"day"<<endl;
					tripDay++;
					//readODTrip(finTrip5);
					finTrip5.close();
					break;
				}
			case 6:
				{
					ifstream finTrip6("D:\\data\\��������\\TRIP20180707\\CN\\20170404-Trip-statistics-2CN.csv");
					cout<<"now is the"<<tripDay<<"day"<<endl;
					tripDay++;
					//readODTrip(finTrip6);
					finTrip6.close();
					break;
				}
			case 7:
				{
					ifstream finTrip7("D:\\data\\��������\\TRIP20180707\\CN\\20170403-Trip-statistics-2CN.csv");//һ���Զ����������ڴ���ܷŲ���
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
			if(i==1)          //ֻ����row�е����ݣ�Ȼ��push_back��vector��
			{
				tempTripID=field;                                 //��trip�Ŀ��Ž����� 
				i++;
				continue;
			}
			else if(i==2)          //ֻ����row�е����ݣ�Ȼ��push_back��vector��
			{
				tempOtime=convertTimeStringToInt(field);     //��Otime����
				tempOhour=extractTimeHour(field);            
				i++;
				continue;
			}
			else if(i==3)
			{
				OName=field;                           //������վ������
				i++;
				continue;
			}
			else if(i==4)
			{
				sOX=convertStringToDouble(field);     //��OX����
				i++;
				continue;
			}
			else if(i==5)
			{
				sOY=convertStringToDouble(field);     //��OY����
				i++;
				continue;
			}
			else if(i==6)
			{
				tempDtime=convertTimeStringToInt(field);     //��Dtime����
				tempDhour=extractTimeHour(field);
				i++;
				continue;
			}
			else if(i==7)
			{
				DName=field;                           //���յ��վ������
				i++;
				continue;
			}
			else if(i==8)
			{
				sDX=convertStringToDouble(field);     //��DX����
				i++;
				continue;
			}
			else if(i==9)
			{
				sDY=convertStringToDouble(field);     //��DY����
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
				if(transfers>5)     //�����쳣���˴�������������˳���5�Σ���Ĭ��������5�Σ������ٴ���
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
		number++;                                                             //�ۻ�����

		if(tempDhour<tempOhour)                                               //Ҫ�����³�ʱ�������ϳ�ʱ���trip���������ɣ����������һ��������
		{
			countNight++; 
			cout<<"��"<<number<<"����ʱ���Ⱥ�����"<<endl;
			continue;                                                   
		}
		
		//�����ǿ��ƶ�ȡ���������ݵ�ʱ���
		if(tempOhour>=0&&tempOhour<=24)                                   //�����ʱ��push_back��vector��,�����ʱ�ξ͸�һ����ֵ�ͺ�
		{
			if(tempDtime-tempOtime<200||tempDtime-tempOtime>12600)       //�����С��0��ʱ���������Ǽ��̣�200s����ʱ�����Ͳ�Ҫ�������
			{                                                            //������յ�ʱ�䳬��3.5h��Ҳ��Ҫ��
				timeTooShortCount++;
				//continue;
			}
			tripCardID.push_back(tempTripID);                            //��trip�Ŀ��ŷŽ��� 
			DStopName.push_back(DName); //���յ�վ���ӽ�������������·�ţ������ж�trip��O���¸�trip��D�Ƿ���ͬ��ʱ�򣬰�O���ֺ������·��ȥ���ٱȽ�
			DGrid_X.push_back(sDX);                                      //���յ������Ž���
			DGrid_Y.push_back(sDY); 
			getOnTime.push_back(tempOtime);                              //���³���ʱ��push����
			getOffTime.push_back(tempDtime);

			OStopName.push_back(OName+OSubwayLine);                      //��վ��Ҳ�Ž���,���Һ���Ӹ���·��
			OGrid_X.push_back(sOX);                                         //����ʼվ�������Ž���
			OGrid_Y.push_back(sOY); 
		}

		if(number==times*100000)
		{
			cout<<number<<endl;     //��360w��ʱ��ͳ�����?
			times++;
		}
		if(number>2.0*tStop)     //���number�����                                                           
		{
			cout<<"break in advance"<<endl;
			break;
		}
	}
	cout<<"��ʱ����push_back��vector���ܵ�trip������"<<tripCardID.size()<<"    ������ô���У�"<<number<<endl;
	cout<<"�³�ʱ�䷴������ǰ�˵ĸ�����push����trip���ˣ�"<<countNight<<endl;
	cout<<"���³�ʱ����̫�̻�̫����push����trip���ˣ�"<<timeTooShortCount<<endl;
	cout<<"trip��ȡ��ϣ�������"<<endl<<endl;

	cout<<"trip�������վ�����ۻ�����ͳ����ϣ�������"<<endl<<endl;

	countTripCardIDMost();                         //��һ�µ��׿���������ظ����ٴ�
	getTripDurationTime();                         //����һ�¶���ʱ��
}

double Trip::convertStringToDouble(string str1)
{
	//����stringתdouble
	double n1;
	const char* ch= str1.c_str();
	n1=atof(ch);                   //�����Ӣ���ַ�����ת��������0��������һ��double����
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
		if(i==1)     //��Ϊʱ���ڵڶ���λ�ã���һ��λ����������
		{
			istringstream sin(field);
			string field2;
			int j=0;
			while (getline(sin,field2,':'))
			{
				if(j==0)
				{
					double seeHour=convertStringToDouble(field2);                     //�����ж϶�������Сʱ��
					if(seeHour<5 && seeHour>=0)
					{
						second=second+(convertStringToDouble(field2)+24)*3600;
					}
					else
					{
						second=second+convertStringToDouble(field2)*3600;   //�ȶ���Сʱ�������������ۼ�
					}

					j++;
					continue;
				}
				if(j==1)
				{
					second=second+convertStringToDouble(field2)*60;    //�������ӣ������������ۼ�
					j++;
					continue;
				}
				if(j==2)
				{
					second=second+convertStringToDouble(field2);      //ֱ�Ӷ�����
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
				hour=int(convertStringToDouble(field2));   //�ȶ���Сʱ��
				break;
			}
		}
		i++;
	}

	return hour;
}

string Trip::extractSubwayLine(string str1)
{
	string sub;                        //�洢�������ĵ��������ֶ�
	//�ο���ʱ��ķ���
	istringstream sin(str1);   
	string field;
	int i=0;
	while (getline(sin,field,'-')) 
	{
		if(i==1)     //��Ϊʱ���ڵڶ���λ�ã���һ��λ����������
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
	string name;        //��վ�����ֵ��м����
	int ID=0;           //��վ���ID�ţ��������ȡ��������û�У�һ��һ���ۼӼ���
	double X,Y;         //��������м����
	ifstream finBus("D:\\data\\��������\\�޼�����1\\merge_BusStation�Ľ�dbscan�ӵ���.csv");   //���кϲ����վ������
	string line;                                   //��Ȼ����ĺϲ����վ��Ҳ����һ�����⣺վ�����о������
	ifstream &fin=finBus;
	while(getline(fin,line))    //һ��һ�еĶ� 
	{
		istringstream sin(line);   
		string field;
		int i=1;
		while (getline(sin,field,','))   //��vector��ȡʱ�����CSV�ļ����ֶγ���5��ʱ���ܻ����
		{
			if(i==1)          //���ƶ���һ��
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
	vector<int> tempStop;                                    //Ϊ�˳�ʼ��stopStartTripIDIncludeʹ�õ�
	pair<map<string,int>::iterator,bool> Insert_Pair;
	for(unsigned int i=0;i<oneWStopName.size();i++)          //for����һ���վ��
	{
		stopStartTripIDInclude.push_back(tempStop);          //��pushһ���յĽ���
		stopStartCount.push_back(0);												//�ȳ�ʼ��Ϊ0�������ۼ���
		Insert_Pair=oneWStopNameToID.insert(pair<string,int>(oneWStopName[i],i));   //��������վ���������������ڵ�λ�úţ���0��ʼ��
		if(Insert_Pair.second==false)
		{
			cout<<"oneWStopNameToID��ô���ܲ����������"<<endl;
		}
	}

	int noFind=0;                                           //�ۻ���Щtrip���е�һ���վ����û�е����
	int yesFind=0;                                          //�ۻ���Щtrip����һ���վ����Ҳ�е����
	int badSubwayFind=0;                                    //�ۻ���Щtrip���еĵ���վ�㵫һ�����û�еģ���Ҫ��trip����Щ����վ������ǻ��ģ���·���ˣ�
	int times=1;                                            //��ִ�е��ٶ�
	for(unsigned int i=0;i<OStopName.size();i++)           //for�����е�trip������ͺܴ���
	{
		//���ж��ǲ��ǵ���վ�㣬�Ǿ�ȥ�����桰-���֡��͡�վ���ֲ���һ����·������mapƥ��
		//������ǵ���վ�㣬�Ǿ�ֱ��map��map�����ͼ�a��b��map
		if(isSubwayStop(OStopName[i]))                       //����ǵ���վ�������
		{
			string tempSub=OStopName[i];                     //�����䵽������ȥҪ�ı���,��ȥ�ˡ�-���֡��͡�վ���ֵĵ�������
			tempSub=extractSubwayName(tempSub);              //�ѵ���վ��ȥ����վ�֣��������˲���-������
			if(oneWStopNameToID.count(tempSub)!=0)           //���жϴ�ʱ�Ǹ�һ��վ���map����û�����վ�����
			{
				stopStartCount[oneWStopNameToID[tempSub]]++;                       //���ƣ��� ����3���ʵ���һ����еĵڼ���Ȼ����stopStartCount���ۼ�
				stopStartTripIDInclude[oneWStopNameToID[tempSub]].push_back(i);    //��trip�ı����ӽ���
				yesFind++;
			}
			else
			{
				//cout<<"������������trip�ĵ���վ������һ�����û�е������"<<tempSub<<endl;
				badSubwayFind++;
				noFind++;
			}
		}
		else                                                 //����ǹ���վ�������
		{
			if(oneWStopNameToID.count(OStopName[i])!=0)               //���ڲ���a��b������£�ֱ���ж�һ���վ������û�����վ����
			{
				stopStartCount[oneWStopNameToID[OStopName[i]]]++;                       //���ƣ��� ����3���ʵ���һ����еĵڼ���Ȼ����stopStartCount���ۼ�
				stopStartTripIDInclude[oneWStopNameToID[OStopName[i]]].push_back(i);    //��trip�ı����ӽ���
				yesFind++;
			}
			else                                                      //���ֱ��mapû�У��ǾͼӸ�a��b���ж�
			{
				if(oneWStopNameToID.count(OStopName[i]+"a")!=0 && oneWStopNameToID.count(OStopName[i]+"b")!=0)       //��������˵��+a�У�+b�϶�Ҳ��
				{
					//�ֱ���trip�����굽����Ϊվ��a�ľ���͵�����Ϊվ��b�ľ���
					double d1=getTwoPointDistance(OGrid_X[i],OGrid_Y[i],oneWX[oneWStopNameToID[OStopName[i]+"a"]],oneWY[oneWStopNameToID[OStopName[i]+"a"]]);
					double d2=getTwoPointDistance(OGrid_X[i],OGrid_Y[i],oneWX[oneWStopNameToID[OStopName[i]+"b"]],oneWY[oneWStopNameToID[OStopName[i]+"b"]]);
					if(d1<=d2)               //���������Ϊվ��a����
					{
						stopStartCount[oneWStopNameToID[OStopName[i]+"a"]]++;
						stopStartTripIDInclude[oneWStopNameToID[OStopName[i]+"a"]].push_back(i);    //��trip�ı����ӽ���
						yesFind++;
					}
					else
					{
						stopStartCount[oneWStopNameToID[OStopName[i]+"b"]]++;
						stopStartTripIDInclude[oneWStopNameToID[OStopName[i]+"b"]].push_back(i);    //��trip�ı����ӽ���
						yesFind++;
					}
				}
				else                             //��a�ͼ�b��û�У���ʾ���վ����ܾ���һ��վ����û�У������ǱȽ��µ�վ��
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
	cout<<"yesFind��ֵ�ǣ� "<<yesFind<<endl;
	cout<<"noFind��ֵ�ǣ� "<<noFind<<endl;
	cout<<"badSubwayFind��ֵ�ǣ� "<<badSubwayFind<<endl;
	cout<<"trip�������ǣ� "<<OStopName.size()<<endl;
	cout<<"�����ҵ�map��û��map����"<<oneWStopNameToID.size()<<endl;

	//���push��ȥ��tripID����û������
	int sumTripID=0;                                           //��һ��ÿ��վ��push�������ܵĴ�����yesFind�Ƿ�һ��
	for(unsigned int i=0;i<oneWStopName.size();i++)          //for����һ���վ��
	{
		sumTripID=sumTripID+stopStartTripIDInclude[i].size();
		if(stopStartTripIDInclude[i].size()!=stopStartCount[i])
		{
			cout<<"push��ȥ��trip��ID�ź�ͳ�Ƶ�count��Ȼ����ȣ�����  "<<stopStartTripIDInclude[i].size()<<" --  "<<stopStartCount[i]<<endl;
		}
	}
	cout<<"������push��ȥ��tripID����û������sumTripID��"<<sumTripID<<endl;
}

bool Trip::isSubwayStop(string str1)
{
	//���жϳ��ȹ�������Ҫ��Ȼ��������
	int lastP=str1.size()-1;                             //��������ַ��������һ��λ��
	if(str1.size()<3)                                    //�������ַ������ȹ�С������ľͲ��ÿ�����
	{
		return false;
	}
	if(str1[lastP]=='1' || str1[lastP]=='2' || str1[lastP]=='3' || str1[lastP]=='4' || str1[lastP]=='5' || str1[lastP]=='7'|| str1[lastP]=='9') //���ж����һ���ǲ�������
	{
		if(str1[lastP-1]=='-' || str1[lastP-1]=='1')     //�����һ�������ֵ�����£������ڶ������� - ���� 1 ����ô�϶����ǵ���վ����
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
	int lastP=str1.size()-1;                             //��������ַ��������һ��λ��
	string tempStr;
	string zhan="վ";
	if(str1[lastP-1]=='-')
	{
		tempStr=str1.substr(str1.size()-4,2);                    //��ȡ�Ǹ��ֿ��ǲ��ǡ�վ����
		if(tempStr==zhan)                                        //�����վ�֣��Ǿ�ȥ����
		{
			finalString=str1.substr(0,str1.size()-4);            //������վ����֮ǰ������
			return finalString+str1[lastP];                      //�����Ǹ����֣������ܴ�   ����վ-3  ���  ����3
		}
		else                        //�������վ�֣��Ǿ�ֱ�Ӽ�����·�ź����
		{
			finalString=str1.substr(0,str1.size()-2);
			return finalString+str1[lastP]; 
		}
	}
	else                           //����Ĭ�ϲ��ǡ�-�����ǡ�1������Ϊǰ���Ѿ�ǧ����ȷ�жϳ������Ǹ�����վ��������
	{
		if(str1[lastP-1]!='1')
		{
			cout<<"��ô���ܵ����ڶ����ַ�����1��"<<str1<<endl;
		}
		tempStr=str1.substr(str1.size()-5,2);                    //��ȡ�Ǹ��ֿ��ǲ��ǡ�վ����
		if(tempStr==zhan)                                        //�����վ�֣��Ǿ�ȥ����
		{
			finalString=str1.substr(0,str1.size()-5);            //������վ����֮ǰ������
			return finalString+str1[lastP-1]+str1[lastP];        //�����Ǹ����֣������ܴ�   ����վ-11  ���  ����11
		}
		else                        //�������վ�֣��Ǿ�ֱ�Ӽ�����·�ź����
		{
			finalString=str1.substr(0,str1.size()-3);
			return finalString+str1[lastP-1]+str1[lastP]; 
		}
	}
}

void Trip::makeStopEndCount()
{
	int number=0;                                           //ָʾ���ײ��˶��ٸ�
	vector<int> tempStop;                                    //Ϊ�˳�ʼ��stopStartTripIDIncludeʹ�õ�
	pair<map<string,int>::iterator,bool> Insert_Pair;
	for(unsigned int i=0;i<tripCardID.size();i++)          //for����360����trip
	{
													//�ȳ�ʼ��Ϊ0�������ۼ���
		Insert_Pair=sixKStopNameToID.insert(pair<string,int>(DStopName[i],number));   //��������վ���������������ڵ�λ�úţ���0��ʼ��
		if(Insert_Pair.second==true)
		{
			sixKStopName.push_back(DStopName[i]);              //���������վ�����Ǿ�Ҳpush����
			stopEndTripIDInclude.push_back(tempStop);          //��pushһ���յĽ���
			stopEndCount.push_back(0);	
			number++;
		}
	}
	cout<<"����Ӧ��Ҫ��ͬ     number�ǣ�"<<number<<"    stopEndCount�ĳߴ磺"<<stopEndCount.size()<<"    sixKStopName�ĳߴ磺"<<sixKStopName.size()<<endl;

	for(unsigned int i=0;i<tripCardID.size();i++)                              //for����360����trip
	{
		if(sixKStopNameToID.count(DStopName[i])!=0)                            //���trip���ȷ������յ�����
		{
			stopEndCount[sixKStopNameToID[DStopName[i]]]++;                    //������ִ���ID�ŵ�λ��++
			stopEndTripIDInclude[sixKStopNameToID[DStopName[i]]].push_back(i); //��ʵ�ʵ�trip��ID�ŷŽ���
		}
		else
		{
			cout<<"�������Ȼû����ʲô����"<<endl;
		}
	}

	//���С��һ�¶Բ���
	int sumEnd=0;
	ofstream outfile1;
	outfile1.open("D:\\data\\��������\\�޼�����3\\stopEndCount.csv");
	for(unsigned int i=0;i<stopEndCount.size();i++)
	{
		outfile1<<fixed<<setprecision(6)<<i<<","<<sixKStopName[i]<<","<<stopEndCount[i]<<","<<stopEndTripIDInclude[i].size()<<endl;
		sumEnd+=stopEndCount[i];
	}
	outfile1.close();
	cout<<sumEnd<<"   �ܹ���trip�ǣ� "<<tripCardID.size()<<endl;
}

void Trip::countTripCardIDMost()   //�����⼸����������������ʱ���
{
	if(tripCardID.size()!=get_tripSize())
	{
		cout<<"��������trip��IDcard�ĺž�Ȼ����?"<<endl;
	}

	int tempRepeat=1;                                         //��ʱ���忨���ظ��Ĵ���Ϊ1
	int repeatPos=0;                                          //��¼�������ŵ�λ��
	int repeatFinal=1;
	for(unsigned int i=0;i<tripCardID.size()-1;i++)             //forһ��trip��card�ĸ���
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
		//cout<<i<<"  ��ǰ��repeatFinal��"<<repeatFinal<<"��    ��ǰ��tempRepeat��"<<tempRepeat<<endl;
		//system("pause");
	}
	cout<<"�ظ��������Ŀ����ǣ�"<<repeatFinal<<"��    ����λ��(��Ϊȥ�����쳣������λ�����ԭʼ�������ڵ���ƫС)�ڣ�"<<repeatPos<<endl;
	cout<<endl<<endl;
}

void Trip::getTripDurationTime()
{
	//�ȳ�ʼ��һ������ʱ������
	for(unsigned int i=0;i<tripCardID.size();i++)
	{
		tripDurationTime.push_back(0);                                //�Ȱ�ÿ������ʱ��ȫŪ��0
	}

	//��ʼ��һ��ֱ�Ӽ���ʱ����ʱ��ģ���Ҫ����Ļ����ڶ������
	for(unsigned int i=0;i<tripCardID.size();i++)                       //for��������trip
	{
		if(i<tripCardID.size()-1 && tripCardID[i]==tripCardID[i+1])                              //�����ǰ��������һ��������ͬ
		{
			if(DStopName[i]==eraseSubwayLine(OStopName[i+1]))                              //�����ǰtrip��D������trip��O��ͬ����ôֱ����ʱ���
			{
				tripDurationTime[i]=getOnTime[i+1]-getOffTime[i];
			}
			else if(getTwoPointDistance(DGrid_X[i],DGrid_Y[i],OGrid_X[i+1],OGrid_Y[i+1])<2000)      //�����ǰtrip��D������trip��O��ʵ��಻Զ����Ҳ����ֱ����ʱ���
			{
				tripDurationTime[i]=getOnTime[i+1]-getOffTime[i];
				if(tripDurationTime[i]>2000)                                                //���ֱ��ʱ������2000��֤��������������ط�ͣ���˵ģ����ɶ�˵�
				{
					tripDurationTime[i]=tripDurationTime[i]-getTwoPointDistance(DGrid_X[i],DGrid_Y[i],OGrid_X[i+1],OGrid_Y[i+1])/1.0;    //��ȥ�����е���һ��վ���ʱ��
					tripDurationTime[i]=int(tripDurationTime[i])+0.2;                       //�൱�ڸ���������һ��0.2�������֪����Щ����һ���������Ķ���ʱ��
				}
			}
			else                                                                  //���������ͬ������ǰtrip��D������trip��O�����ıȽ�Զ��˵����Ӳ�߹�ȥ�����ߴ�Ĺ�ȥ�Ļ��߹�������ȥ��
			{
				//������Ҫ���㣬�������Ҫ���Ǹ��г������ʱ�����?
				tripDurationTime[i]=getOnTime[i+1]-getOffTime[i];                                      //���Ķ���ʱ���������ᳬ���ϴ�trip��D���´�trip��O��ʱ����������Ҫ��һ����ȥһ����ʱ��                                           
				double tempDis=getTwoPointDistance(DGrid_X[i],DGrid_Y[i],OGrid_X[i+1],OGrid_Y[i+1]);   //�õ��ϴ�trip��D���´�trip��O��ֱ�߾���
				tripDurationTime[i]=tripDurationTime[i]-(tempDis*1.5)/8.0;                             //���蹫�������ٶ�Ϊ8��/s����28.8km/h������ֱ�߾������1.2��Ϊ·������
				if(tripDurationTime[i]<0)
				{
					tripDurationTime[i]=180.6;                                                          //���������ó��˸�ֵ������͸���Ū��ͣ����3���Ӱ�
				}
			}
		}
		else                                                             //�����ǰ��������һ����ͬ���ǿ������ǵ�����һ���������Ƕ�����ͬ�����һ��,�Լ�����trip�����һ��Ҳ������������
		{
			if(i>=1 && tripCardID[i-1]==tripCardID[i])                    //�����ǰ��������һ��������ͬ����֤���Ƕ���trip�����һ��
			{
				int back_i=i;
				while(tripCardID[back_i-1]==tripCardID[back_i])          //�����ҵ�����trip�ĵ�һ���Ŀ��ŵ�i
				{
					back_i--;
				}
				if(DStopName[i]==eraseSubwayLine(OStopName[back_i]))   //�����ǰ���ŵ����һ��trip��D���һ����O��ͬ��֤�����ؼ��ˣ��Ͳ��������trip�Ķ�����
				{
					tripDurationTime[i]=0.01;                            //��ֵ0.01��0������
				}
				else if(getTwoPointDistance(DGrid_X[i],DGrid_Y[i],OGrid_X[back_i],OGrid_Y[back_i])<2000)   //�ؼҵ��յ��֮ǰ�����������Ȼ���ֲ�ͬ������úܽ�Ҳ����˵���ؼ���
				{
					tripDurationTime[i]=0.02;                            //��ֵ0.02��0��0.01������
				}
				else                                                      //�ؼҵ��յ��֮ǰ�������������Զ��˵��������û�ؼң���ʼ���µ�trip
				{
					//���trip���൱������û��ʾ��trip�ˣ�����Ҫ�����������ж�������trip�������ԣ���������һ������ʱ��
					tripDurationTime[i]=0.66;
				}
			}
			else                                                         //�����������һ����ͬ��Ҳ����һ����ͬ���Ǿ��ǵ����ģ���trip��һ�����������һ�������������
			{
				//���trip���൱������û��ʾ��trip�ˣ�����Ҫ�����������ж�������trip�������ԣ���������һ������ʱ��
				tripDurationTime[i]=0.77;
			}
		}
	}

	//�������������еĶ���ʱ�䣬���������������ļ��п���
	int cMe9=0;
	int cMe1=0;
	int cMe2=0;
	int cMe66=0;
	int cMe77=0;
	int cMe=0;                          //�ֱ�һ��ÿ�����ж���
	int cMe0=0;
	ofstream outfile1;
	outfile1.open("D:\\data\\��������\\�޼�����3\\tripDurationTime.csv");
	for(unsigned int i=0;i<tripDurationTime.size();i++)                      //for����������Ŀ
	{
		if(tripDurationTime[i]<0)
		{
			cMe0++;
			tripDurationTime[i]=0.985;                                       //�Ѽ���̫С�ĸ�ֵΪ0.985
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
	cout<<"�ظ�����С��0�ģ�"<<cMe0<<"��"<<endl;
	cout<<"�ظ�����180.6��"<<cMe9<<"��"<<endl;
	cout<<"�ظ�����0.01��"<<cMe1<<"��"<<endl;
	cout<<"�ظ�����0.02��"<<cMe2<<"��"<<endl;
	cout<<"�ظ�����0.66��"<<cMe66<<"��"<<endl;
	cout<<"�ظ�����0.77��"<<cMe77<<"��"<<endl;
	cout<<"�ظ����������ģ�"<<cMe<<"��"<<endl;
	cout<<"�ϼƣ� "<<cMe9+cMe1+cMe2+cMe66+cMe77+cMe<<endl;
}

string Trip::eraseSubwayLine(string str1)
{
	string sub;                        //�洢�������ĵ��������ֶ�
	//�ο���ʱ��ķ���
	istringstream sin(str1);   
	string field;
	int i=0;
	while (getline(sin,field,'-')) 
	{
		if(i==0)     //�����ڱ�-5�����������ڱ�����ȡ����
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
		cout<<"�����껹�����"<<endl;
		system("pause");
	}
	//���������tripDurationTime�������ı䣬���԰������tripDurationTime����һ��
	for(unsigned int i=0;i<tripDurationTime.size();i++) 
	{
		tripDurationTime_v1.push_back(tripDurationTime[i]);
	}
	if(tripDurationTime.size()!=tripDurationTime_v1.size())
	{
		cout<<"�����껹�����"<<endl;
		system("pause");
	}
	cout<<"��������ʱ������Ĵ�С"<<tripDurationTime_v1.size()<<endl;

	//���濪ʼ��ʽ����
	int chao66=0;                      //�ֱ�һ��66��77������֧�г������������ʱ��ĸ���
	int chao77=0;
	int noProportion66=0;                //��һ�°�������������䲻��ȥ���ж���
	int noProportion77=0;
	for(unsigned int i=0;i<tripDurationTime.size();i++)                  //for��������trip,Ҳ�������еĶ���ʱ��
	{
		if(tripDurationTime[i]!=0.66 && tripDurationTime[i]!=0.77)                    //����Ȳ��ǵ������ŵ�tripҲ���ǲ��ؼҵ�trip���Ǻ�����ʵ���÷��䣬�����ͺ�           
		{
			continue;
		}
		if(tripDurationTime[i]==0.66)                              //����ǲ��ؼҵĿ��ţ�һ���������������ϵ�trip������ʱ��������������ʱ�������12�㿨һ��
		{
			vector<int> similarTripID;                             //��find������һ�����Ƶ�trip�����ҵ���ֱ�ӷ��䣬�Ҳ����Ͱ��յ��������������
			if(findSimilarTrip(i,similarTripID))                   //����findSimilarTrip��������
			{
				double sumDuration=0;                              //���ҵ�����ȫ���Ƶ�trip�Ķ���ʱ���ۼ�����������ƽ��
				for(unsigned int j=0;j<similarTripID.size();j++)
				{
					sumDuration=sumDuration+tripDurationTime_v1[similarTripID[j]];  //���ƵĶ���ʱ���ۼ�����
				}
				tripDurationTime[i]=sumDuration/double(similarTripID.size()); //������tripƽ������ʱ�䣬��i��trip��һ��������ʱ��
				double maxDurationTime=24*3600-getOffTime[i];                 //��Ϊ��飬�������絽�Ǹ��ط������Ķ���ʱ����಻�ᵽ����12��
				if(tripDurationTime[i]>maxDurationTime)                       //���������������������ʱ�䣬���ܾ���������
				{
					cout<<"����ĳ��ˣ����絽������ʱ�仹�ܵ��賿��   "<<i<<"   "<<tripDurationTime[i]<<"     "<<0.66<<endl;
					cout<<"���Ƶ��ж��ٸ�   "<<similarTripID.size()<<"   �ܣ�"<<sumDuration<<"     "<<0.66<<endl;
					//system("pause");
					tripDurationTime[i]=maxDurationTime;
					chao66++;
				}
			}
			else
			{
				//���û�ҵ���ȫ���Ƶģ�����Ҫ���յ㶺��ʱ�����������
				double tempDuration=0;
				if(proportionTrip(i,tempDuration))
				{
					tripDurationTime[i]=tempDuration;
				}
				else
				{
					//��������û�������
					noProportion66++;
				}
			}
		}
		else                                                       //����ǿ���ֻ��һ�ε�trip
		{
			vector<int> similarTripID;                             //��find������һ�����Ƶ�trip�����ҵ���ֱ�ӷ��䣬�Ҳ����Ͱ��յ��������������
			if(findSimilarTrip(i,similarTripID))                   //����findSimilarTrip��������
			{
				double sumDuration=0;                              //���ҵ�����ȫ���Ƶ�trip�Ķ���ʱ���ۼ�����������ƽ��
				for(unsigned int j=0;j<similarTripID.size();j++)
				{
					sumDuration=sumDuration+tripDurationTime_v1[similarTripID[j]];  //���ƵĶ���ʱ���ۼ�����
				}
				tripDurationTime[i]=sumDuration/double(similarTripID.size()); //������tripƽ������ʱ�䣬��i��trip��һ��������ʱ��
				double maxDurationTime=24*3600-getOffTime[i];                 //��Ϊ��飬�������絽�Ǹ��ط������Ķ���ʱ����಻�ᵽ����12��
				if(tripDurationTime[i]>maxDurationTime)                       //���������������������ʱ�䣬���ܾ���������
				{
					cout<<"����ĳ��ˣ����絽������ʱ�仹�ܵ��賿��   "<<i<<"   "<<tripDurationTime[i]<<"     "<<0.77<<endl;
					cout<<"���Ƶ��ж��ٸ�   "<<similarTripID.size()<<"   �ܣ�"<<sumDuration<<"     "<<0.77<<endl;
					//system("pause");
					tripDurationTime[i]=maxDurationTime;
					chao77++;
				}
			}
			else
			{
				//���û�ҵ���ȫ���Ƶģ�����Ҫ���յ㶺��ʱ�����������
				double tempDuration=0;
				if(proportionTrip(i,tempDuration))
				{
					tripDurationTime[i]=tempDuration;
				}
				else
				{
					//��������û�������
					noProportion77++;
				}
			}
		}
	}
	//����ͷ�������ˣ�����������һ��
	int cMe9=0;
	int cMe1=0;
	int cMe2=0;
	int cMe66=0;
	int cMe77=0;
	int cMe=0;                          //�ֱ�һ��ÿ�����ж���
	int cMe0=0;
	ofstream outfile1;
	outfile1.open("D:\\data\\��������\\�޼�����3\\tripDurationTime2.csv");
	for(unsigned int i=0;i<tripDurationTime.size();i++)                      //for����������Ŀ
	{
		if(tripDurationTime[i]<0)
		{
			cMe0++;
			tripDurationTime[i]=0.985;                                       //�Ѽ���̫С�ĸ�ֵΪ0.985
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
	cout<<"�ظ�����С��0�ģ�"<<cMe0<<"��"<<endl;
	cout<<"�ظ�����180.6��"<<cMe9<<"��"<<endl;         //֮���Ի��࣬����Ϊ���η����ʱ�����䵽
	cout<<"�ظ�����0.01��"<<cMe1<<"��"<<endl;
	cout<<"�ظ�����0.02��"<<cMe2<<"��"<<endl;
	cout<<"�ظ�����0.66��"<<cMe66<<"��"<<endl;
	cout<<"�ظ�����0.77��"<<cMe77<<"��"<<endl;
	cout<<"�ظ����������ģ�"<<cMe<<"��"<<endl;
	cout<<"�ϼƣ� "<<cMe9+cMe1+cMe2+cMe66+cMe77+cMe<<endl;    //����û��cMe0�������ͳ��Ҳ��
	cout<<"��66�ģ�"<<chao66<<"    ��77�ģ�"<<chao77<<endl;
	cout<<"noProportion66�ģ�"<<noProportion66<<"    noProportion77�ģ�"<<noProportion77<<endl;

	int A[5];                                                                      //��ʼ��5������ʱ����ࣺ0-2h��2-4h��4-8h��8-12h��12-24h��
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
	if(isSubwayStop(OStopName[pos]))                       //����pos��trip�����������,����ǵ���վ�������
	{
		string tempSub=OStopName[pos];                     //�����䵽������ȥҪ�ı���,��ȥ�ˡ�-���֡��͡�վ���ֵĵ�������
		tempSub=extractSubwayName(tempSub);              //�ѵ���վ��ȥ����վ�֣��������˲���-������
		if(oneWStopNameToID.count(tempSub)!=0)           //���жϴ�ʱ�Ǹ�һ��վ���map����û�����վ�����
		{
			int tripStartID=oneWStopNameToID[tempSub];                       //���ƣ��� ����3���ʵ���һ����еĵڼ���Ȼ����stopStartTripIDInclude�н�һ�������Ƶ�
			return findSimilarTrip2(pos,tripStartID,vec);                    //�ϸ��������ԣ�ʱ�����ͬ������λ����ͬ�����ң����귵������
		}
		else                                              //��ʾû�ҵ��������վ����
		{
			return false;
		}
	}
	else                                                 //����ǹ���վ�������
	{
		if(oneWStopNameToID.count(OStopName[pos])!=0)               //���ڲ���a��b������£�ֱ���ж�һ���վ������û�����վ����
		{
			int tripStartID=oneWStopNameToID[OStopName[pos]];                       //���ƣ��� ����3���ʵ���һ����еĵڼ���Ȼ����stopStartTripIDInclude�н�һ�������Ƶ�
			return findSimilarTrip2(pos,tripStartID,vec);
		}
		else                                                      //���ֱ��mapû�У��ǾͼӸ�a��b���ж�
		{
			if(oneWStopNameToID.count(OStopName[pos]+"a")!=0 && oneWStopNameToID.count(OStopName[pos]+"b")!=0)       //��������˵��+a�У�+b�϶�Ҳ��
			{
				//�ֱ���trip�����굽����Ϊվ��a�ľ���͵�����Ϊվ��b�ľ���
				double d1=getTwoPointDistance(OGrid_X[pos],OGrid_Y[pos],oneWX[oneWStopNameToID[OStopName[pos]+"a"]],oneWY[oneWStopNameToID[OStopName[pos]+"a"]]);
				double d2=getTwoPointDistance(OGrid_X[pos],OGrid_Y[pos],oneWX[oneWStopNameToID[OStopName[pos]+"b"]],oneWY[oneWStopNameToID[OStopName[pos]+"b"]]);
				if(d1<=d2)               //���������Ϊվ��a����
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
			else                             //��a�ͼ�b��û�У���ʾ���վ����ܾ���һ��վ����û�У������ǱȽ��µ�վ��
			{
				return false;;
			}
		}
	}
}

bool Trip::findSimilarTrip2(int pos,int wPos,vector<int> &vec)
{
	for(unsigned int i=0;i<stopStartTripIDInclude[wPos].size();i++)   //for����pos��trip���վ��ӵ�еĳ�����trip����
	{
		double timePeriod1=abs(getOffTime[i]-getOffTime[pos]);                                   //������Щtrip���³����ʱ�䣬ԽС��ʾ��pos��tripԽ����
		double timePeriod2=abs(getOnTime[i]-getOnTime[pos]);                                     //������Щtrip���ϳ����ʱ�䣬ԽС��ʾ��pos��tripԽ����
		double DSimilar=getTwoPointDistance(DGrid_X[i],DGrid_Y[i],DGrid_X[pos],DGrid_Y[pos]);    //������Щtrip��D��pos��trip��D�ľ��룬ԽС��ʾ��pos��tripԽ����
		if(timePeriod1<2400 && timePeriod2<2400 && DSimilar<1000 && tripDurationTime_v1[i]>1) //���ͬʱ��Σ�ȥ��DҲ��pos����ͬ������ԭʼҲ�ж���ʱ�䣬  ��ֵ40mins��1000������
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
	int A[5];                                                                      //��ʼ��5������ʱ����ࣺ0-2h��2-4h��4-8h��8-12h��12-24h��
	double A5Duration[5]={3600.123,10800.123,21600.123,36000.123,64800.123};       //����������ʱ�������м�ֵд����
	for(int i=0;i<5;i++)
	{
		A[i]=0;
	}
	for(unsigned i=0;i<stopEndTripIDInclude[sixKStopNameToID[DStopName[pos]]].size();i++)        //for���ǵ�ǰtrip��D���ڵ��Ǹ�վ�㵱�캬�е�����trip
	{
		double timePeriod1=abs(getOffTime[i]-getOffTime[pos]);                                   //������Щtrip���³����ʱ�䣬ԽС��ʾ��pos��tripԽ����
		if(timePeriod1<3600 && tripDurationTime_v1[i]>1)    //�����ǰtrip��D���ڵ��Ǹ�վ�㵱�캬�е�����trip�����Ƶ�ʱ����£��Լ�ӵ�������Ķ���ʱ��ż���
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
	for(int i=1;i<5;i++)             //�ҳ�5��ֵ�������Ǹ�����ȻҲ���԰��ձ��������䣬��������ʱ�����ֵ����
	{
		if(A[i]>maxA)
		{
			maxA=A[i];
			maxI=i;
		}
	}
	if(maxA==0)
	{
		//cout<<"���վ���յ�ܺ��ᣬ�������ʱ���û��һ�����ϵ�"<<endl;
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
	ifstream finTrip("D:\\data\\��������\\TRIP20180707\\CN\\20170408-Trip-statistics-2CN.csv");         //��������trip�����ݣ����360����
	string line;
	int times=1;                                                                    //���������е��ٶ�
	double tStop=pow(10.0,7);                                                       //���ƶ�������
	int number=0;                                                                   //�ۻ�����
	//ifstream &fin=finTrip;

	ofstream outfile1;
	outfile1.open("D:\\data\\��������\\�޼�����3\\20170408-Trip-statistics-2CN-duration.csv");      //д�붺��ʱ��

	while(getline(finTrip,line))    //һ��һ�еĶ� 
	{
		istringstream sin(line);   
		string field;
		int i=0;
		while (getline(sin,field,','))   //��vector��ȡʱ�����CSV�ļ����ֶγ���5��ʱ���ܻ����
		{
			outfile1<<field<<",";
			i++;
			if(i==14)          //ֻ����row�е����ݣ�Ȼ��push_back��vector��
			{
				outfile1<<fixed<<setprecision(6)<<tripDurationTime[number]<<endl;
				break;;
			}
		}
		number++;                                                             //�ۻ�����

		if(number==times*100000)
		{
			cout<<number<<endl;     //��360w��ʱ��ͳ�����?
			times++;
		}
		if(number>2.0*tStop)     //���number�����                                                           
		{
			cout<<"��Ҫ��ǰ�������ˣ�"<<endl;
			break;
		}
	}
	if(number-1!=tripDurationTime.size())
	{
		cout<<"�Բ۳����ˣ���   "<<number<<"   ����  tripDurationTime.size()�� "<<tripDurationTime.size()<<endl;
	}
	finTrip.close();
	outfile1.close();
}

void Trip::run()
{
	makeSubwayLineMap();                                              //���Ǹ����Ը���string������map������
	ifstream finTrip("D:\\data\\��������\\TRIP20180707\\CN\\20170408-Trip-statistics-2CN.csv");         //��������trip�����ݣ����360����
	readODTrip(finTrip);											  //��ȡ��trip
	finTrip.close();
	readBusStop();                                                    //�Ѻϲ����һ���վ���������Ϊ��ƥ������ÿһ���������ֱ��Ƕ���
	makeStopStartCount();                                             //ͳ�Ƴ�ÿ��վ��Ĵ��������վ�������1����Ǹ�վ��
	makeStopEndCount();                                               //Ϊ�˰��յ㶺��ʱ��ı���������

	addSuitableDurationTime();                                        //���з��䶺��ʱ��
	writeInTheExistingFile();                                         //�Ѷ���ʱ��д�����е��ļ���
}