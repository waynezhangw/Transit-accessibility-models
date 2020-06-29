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
	ifstream finClass("D:\\data\\��������\\�޼�����1\\gridClassLabel.csv");             
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
	cout<<"���������"<<classCount+1<<endl;
	delete useConvert;                     
	useConvert=NULL;
}

void District::readWaitingArray()
{
	Trip* useConvert=new Trip();
	double X,Y;          
	ifstream finBus("D:\\data\\��������\\�޼�����1\\ArrayID.csv");        
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
	ifstream finClass("D:\\data\\��������\\�޼�����6\\eraseTo17503GOG.csv");             
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
			cout<<"readEraseTo17503GOG()����������"<<endl;
			system("pause");
		}
		eraseEasternDaPeng.insert(int(classL));
	}
	finClass.close();
	cout<<"ȥ������������GOG�����ǲ���17503��"<<eraseEasternDaPeng.size()<<endl;
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
			cout<<"��Ȼ����Ĳ���ʧ���ˣ������ܣ�����"<<endl;
		}
	}
	cout<<"18����������������mapȫ��������"<<endl;
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
	cout<<"2019��6��21�ռ���-Tm_num��"<<Tm_num<<"��Durm_num��"<<Durm_num<<endl;
	cout<<"2019��6��21�ռ���-Tm��"<<Tm/Tm_num<<"��Durm��"<<Durm/Durm_num<<endl;
	Tm = Tm/Tm_num;
	Durm = Durm/Durm_num;
	cout<<"2019��6��21�ռ���-Tm��"<<Tm<<"��Durm��"<<Durm<<endl;

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
			cout<<"ͳ����������������ʱ���ǵĻ�������"<<endl;
			system("pause");
		}


		if(classArriveTimeSum[tempPos]>INT_MAX)                                                  
		{
			 
			 
		}
		if(i==times*100000)
		{
			cout<<i<<"  ��Чʱ����ڵ�oneDay->get_tripSize()   "<<oneDay->get_tripSize()<<endl;     
			times++;
		}
	}

	 
	double tempArea=0;
	for(int i=0;i<classCount+1;i++)                          
	{
		if(classOwnGridID[i].size()==0)
		{
			cout<<"��Ȼ�ܳ���ĳ�����������Ϊ0����������÷���û�и�������ô����    "<<i<<endl;
			system("pause");
			continue;
		}
		tempArea=classOwnGridID[i].size();                   
		 
	}
}

void District::makeFileOfDistrictAttraction()
{
	ofstream outfile1,outfile2;
	outfile1.open("D:\\data\\��������\\�޼�����2\\classArriveCount.csv");
	outfile2.open("D:\\data\\��������\\�޼�����2\\classArriveTimeSum.csv");
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
	ifstream fin1("D:\\data\\��������\\�޼�����2\\classArriveTimeSum�ǹ�����׼���͹����պϲ�����7���µ�ʵ��POI2.csv");          
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
	cout<<"���ǲ���׼ȷ��18109��"<<number<<endl;
	cout<<"readAnother_classArriveTimeSum(vector<double> &vec)ִ�����ŶŶŶŶŶŶ"<<endl;
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
		cout<<"sortAttraction()��classArriveTimeSum.size()!=classCount+1��ը��ը�˰���"<<endl;
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
	cout<<"�������յõ��ĺ�ѡPOI�����ǣ�"<<waitingPOI<<endl<<endl;
	makePOISubwayDistrictMap();                                                            

	 
	double sumSortedAttr=0;                                                                
	ofstream outfile1;
	outfile1.open("D:\\data\\��������\\�޼�����2\\sortedAttr.csv");
	ofstream outfile3;
	outfile3.open("D:\\data\\��������\\�޼�����5\\sortedAttrReal_100POI_madeByAllTrip.csv");         
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
	cout<<endl<<endl<<"��ҿ������������Сʱ��Dvֵ�ǣ�  ��"<<oneDay->get_singleHour()<<"  Сʱ��ʼ�ģ�  "<<thisHourDv<<endl<<endl;
	MySingleDv=thisHourDv;                                                                        
	double F_Loubar=1-1.26598/(sortedAttr[0]/(10000.0*classOwnGridID[sortedClass[0]].size())/60.0);     


	cout<<endl<<endl<<"�����������ֵ�Ͻ��ǣ�  "<<F_Loubar<<endl<<endl;
	 
	double F_Loubar2=calculateTangentLine(sortedAttr,waitingPOI);
	cout<<endl<<endl<<"��������ֱ�������߼������ֵ�Ͻ��ǣ�  "<<F_Loubar2<<endl<<endl;

	double F_Loubar3=1-(sumSortedAttr/waitingPOI)/sortedAttr[0];
	cout<<endl<<endl<<"2014��ƪ�������߻ظ��Ľ���Ĺ�ʽ9���ܶȾ�ֵ�����ܶ����ֵ�õ���  "<<F_Loubar3<<"     ����������ֵ�ǣ�"<<sortedAttr[0]<<endl<<endl;

	double F_Loubar4=calculateAverageLine(sortedAttr,waitingPOI);
	cout<<endl<<endl<<"��������ֱ����б��Ϊ1�������߼������ֵ�Ͻ��ǣ�  "<<F_Loubar4<<endl<<endl;

	 
	ofstream outfile2;
	outfile2.open("D:\\data\\��������\\�޼�����2\\LorenzCurve.csv");
	double tempSumhaha=0;
	bool temp_getF=true;                                                       
	for(int i=waitingPOI-1;i>=0;i--)
	{
		tempSumhaha=tempSumhaha+sortedAttr[i];
		outfile2<<fixed<<setprecision(10)<<(waitingPOI-i)/double(waitingPOI)<<","<<tempSumhaha/sumSortedAttr<<endl;
		if((waitingPOI-i)/double(waitingPOI)>F_Loubar4 && temp_getF)
		{
			cout<<"�����������������������������������������������������������������Ͻ���ֵȡ���ˣ�  "<<i+1<<endl;
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
			cout<<number<<"      �������"<<sortedClass[number]<<"     POI��ֵ��"<<sortedAttr[number]<<endl;
			number++;
			continue;
		}
		POI_number.push_back(sortedClass[number]);
		cout<<fixed<<setprecision(2)<<sortedClass[number]<<" ��������"<<sortedAttr[number]<<endl;
		number++;
	}
	 

	cout<<endl<<"����POI�ø����ǣ�"<<POI_number.size()<<",�����   "<<chosedPOInum<<endl;
	cout<<fixed<<setprecision(5)<<"��ô��POI��ռ����trip'���������ǣ�"<<double(sum_classArriveCount/double(oneDay->get_tripSize()))<<"    ���ʱ��ε�trip�ܴ���"<<oneDay->get_tripSize()<<endl<<endl;

	for(unsigned int i=0;i<POI_number.size();i++)                         
	{
		POI_weight.push_back(sortedAttr[i]/sortedAttr[0]);       
		cout<<fixed<<setprecision(5)<<POI_weight[i]<<"   "<<POI_number[i]<<endl;
	}

}
void District::makeFileOfPOI()
{
	ofstream outfile1;
	outfile1.open("D:\\data\\��������\\�޼�����3\\POI_DistributedInMap.csv");
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
			cout<<i<<"   "<<POI_number[i]<<"  POI��Ȼ����Ĳ���ʧ���ˣ������ܣ�����"<<endl;
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
	 
	cout<<"��ǰtrip��O��0�����:"<<seeClass0<<"   "<<"��ǰtrip��D���ǵ�POI֮һ:"<<seeDIsNotPOI<<endl;

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
	cout<<"��ǰվ���������0����У���ǰվ��ĳ�������Ϊ0��"<<seeStopClass0<<endl;

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
	outfile1.open("D:\\data\\��������\\�޼�����2\\accessValue.csv");
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
	cout<<endl<<"��һ��������Ŀ�� "<<classCount+1<<endl<<endl;

	 
	cout<<"�ǲ���10626                                                        "<<oneDay->get_stop_size()<<endl;
	cout<<"���Ϊ10573��վ�����ڴ�ѧ1���ǲ�����98������                       "<<oneDay->get_stopNearestGrid_size(10573)<<endl;
	cout<<"���Ϊ10573��վ�����ڴ�ѧ1�ĵ��ĸ������ǲ��Ǳ�������991��trip      "<<oneDay->get_stopNearestGridID_size(10573,3)<<endl;
	int sumRun=0;                                                        
	for(int i=0;i<oneDay->get_stop_size();i++)                            
	{
		for(int j=0;j<oneDay->get_stopNearestGrid_size(i);j++)            
		{
			for(int k=0;k<oneDay->get_stopNearestGridID_size(i,j);k++)    
			{
				if(classLabel[oneDay->get_gridID(i,j)]>classCount || classLabel[oneDay->get_gridID(i,j)]<0)
				{
					cout<<"�����˵�ǰվ��ĸ����������Ϊ�ǳ���Χ�ˣ� "<<classLabel[oneDay->get_gridID(i,j)]<<endl;
					continue;
				}
				sumRun++;
				classOwnTripID[classLabel[oneDay->get_gridID(i,j)]].push_back(oneDay->get_stopEachGridTripID(i,j,k));
				 
				 
			}
		}
	}
	cout<<"��ʼ�����Ǹ���ά�������൱�ڰ�trip��IDȫ��ת�ƹ�����������forѭ���ܹ�ִ���˶��ٴΣ� "<<sumRun<<endl;

	 
	int sum=0;
	ofstream outfile1;
	outfile1.open("D:\\data\\��������\\�޼�����2\\classOwnTripID.csv");
	for(int i=0;i<classCount+1;i++)
	{
		outfile1<<fixed<<setprecision(6)<<i<<","<<classOwnTripID[i].size()<<endl;
		sum=sum+classOwnTripID[i].size();
	}
	cout<<"�ŵ����з����е�trip�����ܺʹ���ǣ�Ӧ�ú�����forѭ���Ĵ�����ͬ�ģ���ͬʱ���Ҳ��������Чtrip�ֵ���������֮����ܺͣ� "<<sum<<endl;
	cout<<"1.��Ϊtrip���վ���ں�ѡ��10626��վ����û�ж�ȥ��һ���֣�2.��Ϊtrip��㲻���κθ������û������ȥ"<<endl;
	if(sumRun!=sum)
	{
		cout<<"����forѭ���Ĵ�����ŵ����з����е�trip�����ܺͲ���ȣ��� "<<abs(sumRun-sum)<<endl;
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
	cout<<endl<<"�ʡ�¡����г�ʱ��" <<((tripTimeMax-tripTimeMin)/60.0)<<"   ����ЧPOI������  "<<maxRealGoingPOINum<<endl<<endl;
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
				cout<<"����ʱ���Ȼ����1000���ˣ�����  "<<walkTime<<endl;
				system("pause");
			}

			 
			/*cout<<walkTime<<"   "<<classOwnTripID[i][j]<<" վ������   "<<oneDay->get_OStopName(classOwnTripID[i][j])<<endl;
			cout<<oneDay->get_ODStopNumber(classOwnTripID[i][j])<<"  trip�ĳߴ�  "<<oneDay->get_tripSize()<<endl;
			cout<<fixed<<setprecision(3)<<"��ǰtrip�ǣ�"<<oneDay->get_oneWStopName(int(oneDay->get_tripStopOwnPos(classOwnTripID[i][j])))<<"��ǰtripOվ��ĵڼ���������"<<oneDay->get_tripStopOwnPos(classOwnTripID[i][j])<<endl;
			system("pause");*/

			timeCount[POI_exist[tempPos]]+=(oneDay->get_tripTimeDiff(classOwnTripID[i][j])+walkTime);           
			arriveCount[POI_exist[tempPos]]++;                                                                  
			wieghtCount[i]+=POI_weight[POI_exist[tempPos]];                                                     
		}
		if(wieghtCount[i]>maxRealGoingPOINum)              
		{
			cout<<"�ۻ���Ȩ�ؾ�Ȼ���ˣ�"<<wieghtCount[i]<<"  ��ô����?���Ȩ���ǣ�"<<maxRealGoingPOINum<<"    ���ǵڼ����أ�"<<i<<" ���ж��ٸ�trip���� "<<classOwnTripID[i].size()<<endl;
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
				cout<<"��"<<i<<"������������trip��ȥ��POI���Ҹ������е�trip������100  "<<tripPOIcount[i]<<endl;
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
					cout<<"�������ǰ��POI��Ȼ�г�ʱ�䳬�����������ֵ������"<<timeCount[j]<<endl;
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
			cout<<"�����ǰ������ƽ������ʱ�䳬�����������ֵ������"<<accessMeanTimeByClass[i]<<"   �÷����ǣ�   "<<i<<endl;
			system("pause");
		}
		 
		for(unsigned int j=0;j<POI_number.size();j++)               
		{
			timeCount[j]=0;                                         
			arriveCount[j]=0;
		}
	}
	cout<<"��ǰtrip��D���ǵ�POI֮һ:"<<seeDIsNotPOI<<endl;  

	 
	ofstream outfile1,outfile2;
	outfile1.open("D:\\data\\��������\\�޼�����2\\accessValueByClass.csv");
	outfile2.open("D:\\data\\��������\\�޼�����2\\accessMeanTimeByClass.csv");
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
	cout<<"���͵ľ�Ȼ�ڵڶ����ࣺ"<<whereClass<<"  ����ЧPOI������  "<<going<<endl;
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
	outfile1.open("D:\\data\\��������\\�޼�����2\\classOwnGridID.csv");
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
	cout<<"18000����������Ҫ�������Dv���У�"<<waitingPOI<<"��   ��Ҫ����ĸ����������ֵΪ��"<<sumSortedAttr<<endl;
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
	cout<<"18000����������Ҫ�������POI���������������ߵ����ߵ��У�"<<waitingPOI<<"��   ��Ҫ����ĸ����������ֵΪ��"<<sumSortedAttr<<endl;
	 
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
		cout<<"����y=kx+b��ʱ�����b�ļ����д����⣡����"<<endl;
	}

	finalThre=(0-b)/k;                          

	return finalThre;
}
double District::calculateAverageLine(vector<double> sAttr,int n)
{
	cout<<"calculateAverageLine�������б��Ϊ1������"<<endl;
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
	cout<<endl<<endl<<"�����ƶ����˵ڼ����㣺"<<times<<"    �Ҵ�ʱ����������tgX�ǲ���2����"<<tgX.size()<<endl<<endl<<endl;

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
		cout<<"get_classOwnTripSize(int index1)��index1����������ˣ�"<<endl;
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
			cout<<"������������վ��Ȼ���ڷ����  "<<tempCombined<<endl;
			system("pause");
		}
		else
		{
			Insert_Pair=POISubwayDistrict_exist.insert(pair<int,int>(gridRCtoClass[tempCombined],is199));           
			if(Insert_Pair.second==false)
			{
				cout<<oneDay->get_oneWStopName(i)<<"   ������"<<gridRCtoClass[tempCombined]<<"  ����������Ȼ����Ĳ���ʧ���ˣ��ټ�������"<<endl;
			}
		}
		is199++;
	}
	cout<<"�������ǲ���for��199�Σ�"<<is199<<endl;
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

	cout<<endl<<"��ǰ���ʱ����ǣ� "<<oneDay->get_singleHour()<<"--��--"<<oneDay->get_singleHour()+oneDay->get_durationLast()<<endl;
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