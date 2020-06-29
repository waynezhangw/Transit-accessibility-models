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
	K=2;                   //����ֻ����·��ߺͶ������࣬�����������Ϊ2
	iterations=10;
}


KMeans::~KMeans(void)
{
}

void KMeans::run()
{
	BusPoint* busObject=new BusPoint();
	busObject->readBusStop();
	string tempStopName="��";             //������5956����ͬ��վ������������Ҫ����ֵ5956��
	busObject->add_stopName("mean to do so as a ending flag");             //�����Ϊ�˷�ֹ������i+1����������ǰ������һ����ȥ
	outfile.open("..\\result\\merge_BusStation.csv");
	for(int i=0;i<busObject->getStopSize();i++)      //�����size�Ǳ���4����δ�ϲ�վ��
	{
		if(tempStopName!=busObject->get_stopName(i))
		{
			tempStopName=busObject->get_stopName(i);       //ÿ��ִ�е������ʱ��localXӦ���ǿյ�
		}
		if(!checkRepeat(busObject->get_stopX(i),busObject->get_stopY(i)))    //�󲿷����������false
		{
			localX.push_back(busObject->get_stopX(i));
			localY.push_back(busObject->get_stopY(i));
			localLineN.push_back(busObject->get_stopLine(i));
		}

		//������Ҫһ���ж�˵�Ǵ��ڵ����������������²���
		//���ж�һ���Ƿ�ȫ��û���ظ���·
		if(busObject->get_stopName(i)==tempStopName && busObject->get_stopName(i+1)!=tempStopName)  //��ǰ���ڵ���һ��������,��������3��  
		{                    
			if(localX.size()==1)
			{
				//��outfile��������
				outfile<<tempStopName<<","<<localLineN[0]<<","<<fixed<<setprecision(6)<<localX[0]<<","<<localY[0]<<endl;
				//Ҫ���һ��loacalX�Ǽ���
				localX.clear();
				localY.clear();
				localLineN.clear();
				continue;              //continueֱ��������һ��i��ѭ��
			}
			if(localX.size()==2)
			{
				//Ԥ���������ĺ��������������
				if(sqrt((localX[1]-localX[0])*(localX[1]-localX[0])+(localY[1]-localY[0])*(localY[1]-localY[0]))>500)
				{
					cout<<"Two stops, but far away:"<<i<<endl;         //�ж�һ���쳣������������������ͬ��վ��ȴ���500�׿���
				}
				if(busObject->get_stopLine(i)==busObject->get_stopLine(i-1))      //��ʾ�պ���·���һ�����Ǳ�һ��
				{
					//ֱ��������֣���ϵ�ʱ������������
					outfile<<tempStopName+"a"<<","<<localLineN[0]<<","<<fixed<<setprecision(6)<<localX[0]<<","<<localY[0]<<endl;
					outfile<<tempStopName+"b"<<","<<localLineN[1]<<","<<fixed<<setprecision(6)<<localX[1]<<","<<localY[1]<<endl;
					//���һ��LocalX
					localX.clear();
					localY.clear();
					localLineN.clear();
					continue;
				}
				else
				{
					//���������ϲ�����ȡƽ������ֵ
					double meanX=(localX[0]+localX[1])/2;
					double meanY=(localY[0]+localY[1])/2;
					outfile<<tempStopName<<","<<localLineN[0]<<","<<fixed<<setprecision(6)<<meanX<<","<<meanY<<endl;
					//���һ��
					localX.clear();
					localY.clear();
					localLineN.clear();
					continue;
				}
			}
			else
			{
				deleteAbnormal();                       //ɾ�������ر���ŵ��쳣��
				deleteAbnormalByDBscan();               //ɾ����Щ��Ȼ��ý��������ԡ�����Ⱥ���ĵ�
				bool mergeAll=allDiffLine();            //���Ϊ�棬�Ͳ�������·����
				if(mergeAll)
				{
					//�ϲ�ȫ����һ����
					double sumX=0;                      //��ʱ�洢�ۼӵĵ������
					double sumY=0;
					for(unsigned int j=0;j<localX.size();j++)
					{
						sumX=sumX+localX[j];
						sumY=sumY+localY[j];
					}
					double meanX=sumX/localX.size();
					double meanY=sumY/localY.size();
					outfile<<tempStopName<<","<<localLineN[0]<<","<<fixed<<setprecision(6)<<meanX<<","<<meanY<<endl;   //tempStopName��localLineӦ�ö��ǵ�һ��
					//���һ��
					localX.clear();
					localY.clear();
					localLineN.clear();
				}
				else                                //�����ͬ��·վ�㣬�Ʊطֳ���·��ߺ��Ǳ�������Ӫ
				{
					int a1=0;
					int a2=0;
					findFarPoint(a1,a2); 					//�ҳ���Զ������վ��ı��,  
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
						if(tempDisA<=tempDisB)     //�����ClusterA������ôҪ��A���������
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
					//���￪ʼ�ٷ��䣬�ж�ÿ�����ڵĵ��Ƿ��뵱ǰ�����Ľ�������һ��������Զ
					for(int j=0;j<iterations;j++)              //��һ��for��������
					{
						double AcentralX=ClusA->get_central_X();
						double AcentralY=ClusA->get_central_Y();
						double BcentralX=ClusB->get_central_X();
						double BcentralY=ClusB->get_central_Y();
						vector<int> exchangeP;                  //�������һ�ε���������Ҫ�����ĵ�ı��
						vector<string> exchangeN;               //�������һ�ε���������Ҫ�����ĵ�ı�ű�����������AorB
						int kanyixia=exchangeP.size();          //��һ�²������Ż᲻����0.��һ��Ҫɾ��
						for(unsigned int k=0;k<localX.size();k++)       //��һ��forÿһ���㵽������ľ�������
						{
							double tempDisA=0;                 //��ʱ�洢�����㵽�����������ĵľ���
							double tempDisB=0;
							tempDisA=sqrt((localX[k]-AcentralX)*(localX[k]-AcentralX)+(localY[k]-AcentralY)*(localY[k]-AcentralY));
							tempDisB=sqrt((localX[k]-BcentralX)*(localX[k]-BcentralX)+(localY[k]-BcentralY)*(localY[k]-BcentralY));
							string tempAB="0";                          //�������ַ���A or B��ָʾ��ǰk�������ĸ�������
							for(int t=0;t<ClusA->get_clusterSize();t++)          //��һ��forѭ��Ϊ���ҵ�ǰ��k�����ĸ�����
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
							if(tempAB=="A" && tempDisA>tempDisB)          //��������A����ȴ��B��
							{
								exchangeP.push_back(k);
								exchangeN.push_back("A");
								continue;
							}
							if(tempAB=="B" && tempDisA<tempDisB)          //��������B����ȴ��A��
							{
								exchangeP.push_back(k);
								exchangeN.push_back("B");
							}
							//Ҫ�жϳ���ǰ�Ƿ�����Ҫ�ط���������Ȼ���k��ֵ��¼��vector�У��������vector���н�����
							//Ҫȥ����������е�ͬʱ������centralX��Ȼ������ӵ���һ������
						}
						if(exchangeP.size()==0)                     //����һ�ε�������û�ҵ��쳣��
						{
							outfile<<tempStopName+"a"<<","<<localLineN[0]<<","<<fixed<<setprecision(6)<<ClusA->get_central_X()<<","<<ClusA->get_central_Y()<<endl; 
							outfile<<tempStopName+"b"<<","<<localLineN[1]<<","<<fixed<<setprecision(6)<<ClusB->get_central_X()<<","<<ClusB->get_central_Y()<<endl; 
							break;
						}
						for(unsigned k=0;k<exchangeP.size();k++)     //��һ��forѭ��Ϊ�˽��н���
						{
							//���н���
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
						if(j=iterations-1)                     //��������һ�ε�����û�н�����͸Ͻ����
						{
							outfile<<tempStopName+"a"<<","<<localLineN[0]<<","<<fixed<<setprecision(6)<<ClusA->get_central_X()<<","<<ClusA->get_central_Y()<<endl; 
							outfile<<tempStopName+"b"<<","<<localLineN[1]<<","<<fixed<<setprecision(6)<<ClusB->get_central_X()<<","<<ClusB->get_central_Y()<<endl;
						}
						//����Ҫ���һ��exchange ��vector
						exchangeP.clear();
						exchangeN.clear();
					}

					//���һ��localX�Ǽ���
					localX.clear();
					localY.clear();
					localLineN.clear();

					delete ClusA;
					ClusA=NULL;
					delete ClusB;
					ClusB=NULL;
				}
			}
			//�ж��˽����Ļ�����ζ�ŵ�ǰվ����ӱ��ˣ���
			//1.���޳��쳣վ��
			//2.�ҳ���Զ������վ��
			//3.����Զ������վ��ֱ��������cluster��
			
		}
		
	}

	outfile.close();             //������ļ����йر�

	delete busObject;
	busObject=NULL;
}

void KMeans::deleteAbnormal()                           //����ԭʼ���������ֻ��һ���쳣��
{
	//Ӧ������Ҫ�޳���վ��ǳ��٣�����ֻҪ����޳��ˣ��͸�һ�����������̨
	for(unsigned int i=0;i<localX.size();i++)     
	{
		double tempDis=0;
		bool errorP=true;                       //��ʼ��Ϊ��ǰ�����쳣�㣬���Ը�����
		for(unsigned int j=0;j<localX.size();j++)
		{
			if(i==j)
			{
				continue;
			}
			tempDis=sqrt((localX[i]-localX[j])*(localX[i]-localX[j])+(localY[i]-localY[j])*(localY[i]-localY[j]));     //��������
			if(tempDis<1000)             //������Ϊ�棬����ǰi����Χ�Ǵ���ͬ��ģ����Բ����쳣��
			{
				errorP=false;
				break;
			}
		}
		if(errorP)      //���ִ�������������һȦ������û����i��ܽ��ĵ�
		{		
			//ȥ��λ��i���ĵ�
			localX.erase(localX.begin()+i);
			localY.erase(localY.begin()+i);
			localLineN.erase(localLineN.begin()+i);
			i--;
		}
		else            //���Ϊ�棬֤��i�����һȦ�����к���������1000�����ڵĵ�
		{
			continue;
		}
	}
}

bool KMeans::allDiffLine()
{
	map<string,int> BusStationsLineMap;            //�������Ψһ�Ե�map
	pair<map<string,int>::iterator, bool> Insert_Pair;   //���������Ƿ����ɹ�
	int j=0;                                               //������¼O�Ĳ��ظ���λ�ã�i��������
	for(unsigned int i=0;i<localLineN.size();i++,j++)   //��ΪOGridXY.size()�ķ���ֵ��unsigned int�͵ģ�����ǰ���i����һ��
	{
		Insert_Pair=BusStationsLineMap.insert(pair<string,int>(localLineN[i],j+1));   //����ʱ�õ�һ��վ���valueֵΪ1
		if(Insert_Pair.second==false)
		{
			j--;
		}
	}
	if(BusStationsLineMap.size()==localLineN.size())            //������ظ���·�������ʾ������·һ��,map���vectorһ����
	{
		return true;
	}
	else
	{
		return false;
	}
}

void KMeans::findFarPoint(int &p1,int &p2)    //������ĳ����㷽�����������һ������������Զ�ģ�Ȼ�������ҵ�����������Զ�ĵ�
{
	//����������,��������Ҫ�Ľ�
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
		//�����ֱ�������ú�����
	}
	else
	{
		//��������Ϊ3
		vector<int> outPosition;               //��¼��΢�쳣һ��ĵ��λ��
		for(unsigned int i=0;i<localX.size();i++)     
		{
			double tempDis=0;                  //��¼һ�µ�i��Χ���׶��Χ�ڵĵ����ȽϽ���������dbscan�İ뾶
			int countNear=0;                  //��¼һ�µ�i��Χ�����ж��ٸ��ȽϽ��ĵ㣬������dbscan�ĸ���
			for(unsigned int j=0;j<localX.size();j++)
			{
				if(i==j)                      //�Լ����Լ��Ⱦ���û������
				{
					continue;
				}
				tempDis=sqrt((localX[i]-localX[j])*(localX[i]-localX[j])+(localY[i]-localY[j])*(localY[i]-localY[j]));
				if(tempDis<20)               //�����i��Χ20�������е㣬��ô�Ͱ�����
				{
					countNear++;
				}
			}
			if(stopNumber>=5 && stopNumber<10 && countNear<1)                  //Ҫ����Χ��1���ٽ���Ϳ�������
			{
				outPosition.push_back(i);
			}
			if(stopNumber>=10 && stopNumber<=15 && countNear<2)                  //���2Ҳ�ǵ����ű���ͬ��վ��ĸ������仯����ֵ
			{
				outPosition.push_back(i);
			}
			if(stopNumber>15 && countNear<3)                  //���2Ҳ�ǵ����ű���ͬ��վ��ĸ������仯����ֵ
			{
				outPosition.push_back(i);
			}
		}
		if(int(outPosition.size())<=stopNumber/2)             //���Ҫȥ���ĸ���С��ԭʼ������һ��Ż����ȥ������Ϊԭ��6����������ȫ��ȥ����
		{
			int decrease=0;                      //forѭ����ÿȥ��vector��һ��ֵ��vector��size�ᶯ̬�仯
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
	//�޷���ֵ

}
bool KMeans::checkRepeat(double tempX,double tempY)
{
	bool alreadyHave=false;
	for(unsigned int i=0;i<localX.size();i++)         //���������Ѿ��Ž�ȥ�ģ�����ǰҪ�ŵĺ�������û���ظ�
	{
		if(tempX==localX[i] && tempY==localY[i])
		{
			alreadyHave=true;
			return alreadyHave;
		}
	}
	return alreadyHave;
}

