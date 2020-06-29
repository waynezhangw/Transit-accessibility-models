#include "Grid.h"
#include<math.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include<iomanip>

using namespace std;
Grid::Grid(void)
{
	OriginX=476499.729847;               
	OriginY=2524560.09966;
	myStreets=new Streets();
	myPoints=new Points();
	pOnSegment=0;

	 
	maxBusWalkingDis=400;                       
	maxSubwayWalkingDis=1000;                   
	busOrSubwayDivide=10427;                    
	tempIndicate=0;
}


Grid::~Grid(void)
{
	delete myStreets;
	myStreets=NULL;
	delete myPoints;
	myPoints=NULL;
}

double Grid::getGridPos(double x,double y)
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

void Grid::makeGridStreetMap()
{
	myStreets->readStreets();                        
	myStreets->makeGraphPointMap();                  
	myStreets->makeNodeStreetIDMap();                
	myStreets->makeDijkstra_arc();                   

	pair<map<double,vector<int>>::iterator, bool> Insert_Pair;    
	vector<int> tempStreetID;                                  
	double tempPosS,tempPosE,tempPosM;                         
	for(int i=0;i<myStreets->getStreetSize();i++)              
	{
		tempPosS=getGridPos(myStreets->get_StartPx(i),myStreets->get_StartPy(i));
		tempPosE=getGridPos(myStreets->get_EndPx(i),myStreets->get_EndPy(i));
		tempPosM=getGridPos(myStreets->get_MidPx(i),myStreets->get_MidPy(i));
		tempStreetID.push_back(myStreets->get_streetID(i));                           
		Insert_Pair=gridStreet.insert(pair<double,vector<int>>(tempPosS,tempStreetID));    
		if(Insert_Pair.second==false)
		{
			if(putIn(myStreets->get_streetID(i),gridStreet[tempPosS]))
			{
				gridStreet[tempPosS].push_back(myStreets->get_streetID(i));         
			}
		}
		Insert_Pair=gridStreet.insert(pair<double,vector<int>>(tempPosE,tempStreetID));    
		if(Insert_Pair.second==false)
		{
			if(putIn(myStreets->get_streetID(i),gridStreet[tempPosE]))
			{
				gridStreet[tempPosE].push_back(myStreets->get_streetID(i));         
			}
		}
		Insert_Pair=gridStreet.insert(pair<double,vector<int>>(tempPosM,tempStreetID));    
		if(Insert_Pair.second==false)
		{
			if(putIn(myStreets->get_streetID(i),gridStreet[tempPosM]))
			{
				gridStreet[tempPosM].push_back(myStreets->get_streetID(i));         
			}
		}

		tempStreetID.clear();                          
	}

	 
	 
	
}
bool Grid::putIn(int ID,vector<int> &vec)            
{
	bool temp=true;
	for(unsigned int i=0;i<vec.size();i++)
	{
		if(ID==vec[i])
		{
			temp=false;
			break;
		}
	}
	return temp;              
}

void Grid::makeStreetStopMap()
{
	myPoints->readBusStop();                                  
	pair<map<int,vector<int>>::iterator, bool> Insert_Pair;    
	vector<int> tempStopID;                                  
	int tempStreetID;                                         
	vector<double> aroundGrid;                                
	double tempStopCenter;                                    
	int times=1;                                              
	for(int i=0;i<myPoints->getStopSize();i++)                
	{
		 
		tempStopCenter=getGridPos(myPoints->get_pointX(i),myPoints->get_pointY(i));
		findAroundGrid(tempStopCenter,aroundGrid,10);                                
		bool sameOrNot=false;                                 
		if(i>0)
		{
			sameOrNot=whetherTheSameStop(myPoints->get_stopName(i-1),myPoints->get_stopName(i));      
		}

		 
		if(sameOrNot)
		{
			tempStreetID=getNearestTwoStreet(myPoints->get_stopID(i),aroundGrid,i);      
		}
		else
		{
			tempStreetID=getNearestStreet(myPoints->get_stopID(i),aroundGrid);           
		}
		

		 

		tempStopID.push_back(myPoints->get_stopID(i));
		Insert_Pair=streetStop.insert(pair<int,vector<int>>(tempStreetID,tempStopID));   
		 

		if(Insert_Pair.second==false)                                 
		{
			streetStop[tempStreetID].push_back(myPoints->get_stopID(i));         
		}
		tempStopID.clear();
		aroundGrid.clear();
		if(i==times*1000)
		{
			times++;
			cout<<i<<endl;
		}
		pOnSegment++;
	}
}

void Grid::findAroundGrid(double pos,vector<double> &vec,int Asize)
{
	if(Asize<1)                     
	{
		Asize=1;
	}
	int row,column;                 
	row=int(pos);
	column=round_double((pos-row)*1000);   
	int leftUpX,leftUpY;                   
	vec.push_back(pos);                    
	for(int i=1;i<=Asize;i++)
	{
		leftUpX=row-i;                     
		leftUpY=column-i;
		for(int j=0;j<2*i+1;j++)
		{
			leftUpY=leftUpY+j;
			if(leftUpX>=1 && leftUpX<=401 && leftUpY>=1 && leftUpY<=830)
			{
				vec.push_back(leftUpX+leftUpY/1000.0); 
			}
			leftUpY=column-i;
		}
		leftUpX=row+i;                      
		leftUpY=column-i;
		for(int j=0;j<2*i+1;j++)
		{
			leftUpY=leftUpY+j;
			if(leftUpX>=1 && leftUpX<=401 && leftUpY>=1 && leftUpY<=830)
			{
				vec.push_back(leftUpX+leftUpY/1000.0); 
			}
			leftUpY=column-i;
		}
		leftUpX=row-i;                      
		leftUpY=column-i;
		for(int j=0;j<2*i-1;j++)    
		{
			leftUpX=leftUpX+j+1;    
			if(leftUpX>=1 && leftUpX<=401 && leftUpY>=1 && leftUpY<=830)
			{
				vec.push_back(leftUpX+leftUpY/1000.0); 
			}
			leftUpX=row-i;
		}
		leftUpX=row-i;                      
		leftUpY=column+i;
		for(int j=0;j<2*i-1;j++)    
		{
			leftUpX=leftUpX+j+1;    
			if(leftUpX>=1 && leftUpX<=401 && leftUpY>=1 && leftUpY<=830)
			{
				vec.push_back(leftUpX+leftUpY/1000.0); 
			}
			leftUpX=row-i;
		}
	}
	
	 
	 
	 
}

int Grid::round_double(double temp)
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

bool Grid::whetherTheSameStop(string s1,string s2)
{
	if(s1.size()!=s2.size())
	{
		return false;
	}
	else
	{
		s1.erase(s1.end()-1);
		s2.erase(s2.end()-1);
		if(s1==s2)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

int Grid::getNearestStreet(int stopID,vector<double> &vec)         
{
	 
	double coreX,coreY;                              
	coreX=myPoints->get_pointX(stopID-1);
	coreY=myPoints->get_pointY(stopID-1);
	double shortX=OriginX;                          
	double shortY=OriginY;                          
	double shortDis=9999;                           
	int shortID=0;                                  
	int breakEarly=0;                               
	for(unsigned int i=0;i<vec.size();i++)        
	{
		if(gridStreet.count(vec[i])==0)          
		{
			continue;
		}
		for(unsigned int j=0;j<gridStreet[vec[i]].size();j++)     
		{
			int tempStreetType=myStreets->get_streetType(gridStreet[vec[i]][j]-1);    
			if(tempStreetType==1||tempStreetType==2||tempStreetType==92||tempStreetType==93||tempStreetType==94)
			{       
				continue;                                               
			}
			double segX1,segY1,segX2,segY2;                             
			double tempD;                                               
			double tempMyX,tempMyY;                                     
			segX1=myStreets->get_StartPx(gridStreet[vec[i]][j]-1);
			segY1=myStreets->get_StartPy(gridStreet[vec[i]][j]-1);
			segX2=myStreets->get_EndPx(gridStreet[vec[i]][j]-1);
			segY2=myStreets->get_EndPy(gridStreet[vec[i]][j]-1);
			tempD=pointToSegDis(coreX,coreY,segX1,segY1,segX2,segY2,tempMyX,tempMyY);   
			if(shortDis<20 && tempD>283)           
			{
				breakEarly++;         
			}                         
			if(tempD<shortDis)
			{
				shortDis=tempD;
				shortX=tempMyX;
				shortY=tempMyY;
				shortID=gridStreet[vec[i]][j];
			}
		}
		if(breakEarly>8)     
		{
			break;
		}
	}

	 
	myPoints->set_nearDis(shortDis);
	myPoints->set_nearX(shortX);
	myPoints->set_nearY(shortY);
	return shortID;
}
int Grid::getNearestTwoStreet(int stopID,vector<double> &vec,int pos)       
{
	double lastX,lastY;                              
	lastX=myPoints->get_nearX(pos-1);
	lastY=myPoints->get_nearY(pos-1); 

	double coreX,coreY;                              
	coreX=myPoints->get_pointX(stopID-1);
	coreY=myPoints->get_pointY(stopID-1);
	 
	 

	double shortX[2]={OriginX,OriginX};                          
	double shortY[2]={OriginY,OriginY};                          
	double shortDis[2]={9999,9999};                           
	int shortID[2]={0,0};                                  
	int breakEarly=0;                               
	for(unsigned int i=0;i<vec.size();i++)        
	{
		if(gridStreet.count(vec[i])==0)          
		{
			continue;
		}
		for(unsigned int j=0;j<gridStreet[vec[i]].size();j++)     
		{
			int tempStreetType=myStreets->get_streetType(gridStreet[vec[i]][j]-1);    
			if(tempStreetType==1||tempStreetType==2||tempStreetType==92||tempStreetType==93||tempStreetType==94)
			{       
				continue;                                               
			}
			double segX1,segY1,segX2,segY2;                             
			double tempD;                                               
			double tempMyX,tempMyY;                                     
			segX1=myStreets->get_StartPx(gridStreet[vec[i]][j]-1);
			segY1=myStreets->get_StartPy(gridStreet[vec[i]][j]-1);
			segX2=myStreets->get_EndPx(gridStreet[vec[i]][j]-1);
			segY2=myStreets->get_EndPy(gridStreet[vec[i]][j]-1);
			tempD=pointToSegDis(coreX,coreY,segX1,segY1,segX2,segY2,tempMyX,tempMyY);   

			 
			if(shortDis[0]<20 && tempD>283)           
			{
				breakEarly++;         
			}                         
			if(shortDis[1]<20 && tempD>283)           
			{
				breakEarly++;         
			}

			 
			if(tempD>shortDis[1])     
			{
				continue;
			}
			if(tempD<shortDis[0])    
			{
				shortDis[0]=tempD;
				shortX[0]=tempMyX;
				shortY[0]=tempMyY;
				shortID[0]=gridStreet[vec[i]][j];
				continue;
			}
			if(tempD<shortDis[1] && tempD>shortDis[0])     
			{
				shortDis[1]=tempD;
				shortX[1]=tempMyX;
				shortY[1]=tempMyY;
				shortID[1]=gridStreet[vec[i]][j];
				continue;
			}
		}
		if(breakEarly>8 && shortDis[1]<100)     
		{
			break;
		}
	}

	 
	double dis3=sqrt((shortX[1]-shortX[0])*(shortX[1]-shortX[0])+(shortY[1]-shortY[0])*(shortY[1]-shortY[0]));  
	if(dis3>20)
	{
		myPoints->set_nearDis(shortDis[0]);              
		myPoints->set_nearX(shortX[0]);
		myPoints->set_nearY(shortY[0]);
		return shortID[0];
	}
	 
	double dis1=sqrt((lastX-shortX[0])*(lastX-shortX[0])+(lastY-shortY[0])*(lastY-shortY[0]));      
	double dis2=sqrt((lastX-shortX[1])*(lastX-shortX[1])+(lastY-shortY[1])*(lastY-shortY[1]));      
	if(dis1>dis2)                                 
	{
		myPoints->set_nearDis(shortDis[0]);              
		myPoints->set_nearX(shortX[0]);
		myPoints->set_nearY(shortY[0]);
		return shortID[0];
	}
	else
	{
		myPoints->set_nearDis(shortDis[1]);
		myPoints->set_nearX(shortX[1]);
		myPoints->set_nearY(shortY[1]);
		return shortID[1];
	}
	
}

double Grid::pointToSegDis(double Cx,double Cy,double X1,double Y1,double X2,double Y2,double &VX,double &VY) 
{              
	double tempDis=0;                           
	double a,b,c;                               
	a=sqrt((Cx-X1)*(Cx-X1)+(Cy-Y1)*(Cy-Y1));
	b=sqrt((X1-X2)*(X1-X2)+(Y1-Y2)*(Y1-Y2));
	c=sqrt((X2-Cx)*(X2-Cx)+(Y2-Cy)*(Y2-Cy));
	double costheta1=(a*a+b*b-c*c)/(2*a*b);        
	double costheta2=(c*c+b*b-a*a)/(2*b*c);
	if(costheta1==1 || costheta2==1)                   
	{
		VX=Cx;
		VY=Cy;
		cout<<"there is a stop on the segment! it's: "<<pOnSegment<<endl;
		return tempDis;
	}
	if(costheta1>0 && costheta2>0)                     
	{
		 
		double portion=(a*costheta1)/b;                 
		double dx=fabs(X1-X2);                          
		double dy=fabs(Y1-Y2);                          
		tempDis=a*sqrt(1-costheta1*costheta1);          
		if(X1<X2 && Y1>Y2)                      
		{
			VX=X1+dx*portion;
			VY=Y1-dy*portion;
		}
		else if(X1<X2 && Y1<Y2)                 
		{
			VX=X1+dx*portion;
			VY=Y1+dy*portion;
		}
		else if(X1>X2 && Y1>Y2)                 
		{
			VX=X1-dx*portion;
			VY=Y1-dy*portion;
		}
		else                                   
		{
			VX=X1-dx*portion;
			VY=Y1+dy*portion;
		}
	}
	else                 
	{ 
		if(costheta1<=0)    
		{
			VX=X1;
			VY=Y1;
			tempDis=a;
		}
		else             
		{
			VX=X2;
			VY=Y2;
			tempDis=c;
		}
	}
	return tempDis;
}

void Grid::makeFileOfProjectedPoint()
{
	ofstream outfile;
	outfile.open("D:\\data\\深圳数据\\修剪数据1\\projected_busstops.csv");
	for(int i=0;i<myPoints->getStopSize();i++)
	{
		outfile<<fixed<<setprecision(6)<<myPoints->get_nearX(i)<<","<<myPoints->get_nearY(i)<<","<<myPoints->get_nearDis(i)<<endl;
	}
	outfile.close();
}




void Grid::readWaitingArray()
{
	Points* useConvert=new Points();
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
	delete useConvert;                     
	useConvert=NULL;
}

void Grid::makeGridNearestStop()
{
	vector<double> aroundGrid;                         
	double tempCombine;                                
	double GridX,GridY;                                

	vector<double> aroundGridNear;                     
	int times=1;                                       
	for(unsigned int i=0;i<waitingRow.size();i++)      
	{
		tempCombine=waitingRow[i]+waitingColumn[i]/1000.0;                           
		findAroundGrid(tempCombine,aroundGrid,10);                                   
		getGridCenterXY(tempCombine,GridX,GridY);                                    
		getNearestStreetForGrid(GridX,GridY,aroundGrid);                             
		if(nearGridStreetID.size()==0)
		{
			 
			gridNearestStop.push_back(temp_gridNearestStop);        
			temp_gridNearestStop.clear();                           
			gridNearestStopDis.push_back(temp_gridNearestStopDis);  
			temp_gridNearestStopDis.clear();
			 
			if(i==20000*times || i==waitingRow.size()-1)
			{
				times++;
				cout<<"makeGridNearestStop()"<<i<<endl;
			}
			continue;
		}
		else
		{
			for(unsigned int j=0;j<nearGridStreetID.size();j++)              
			{
				 
				tempCombine=getGridPos(nearGridStreetX[j],nearGridStreetY[j]);       
				int around=8-int(nearGridStreetDis[j]/100.0);                       
				findAroundGrid(tempCombine,aroundGridNear,around);                   
				 
				 
				makeWaitingDis(aroundGridNear,j);  





				 
			}
			 
 			gridNearestStop.push_back(temp_gridNearestStop);
			temp_gridNearestStop.clear();                                  
			gridNearestStopDis.push_back(temp_gridNearestStopDis);         
			temp_gridNearestStopDis.clear();
		}

		 


		nearGridStreetID.clear();                   
		nearGridStreetDis.clear();
		nearGridStreetX.clear();
		nearGridStreetY.clear();
		aroundGrid.clear();
		aroundGridNear.clear();                     

		/*if(i<2005 && i>2000)
		{
			break;
		}*/

		 
		if(i==20000*times || i==waitingRow.size()-1)
		{
			times++;
			cout<<"makeGridNearestStop()"<<i<<endl;
		}
	}
}
void Grid::getNearestStreetForGrid(double GX,double GY,vector<double> &vec)        
{
	double shortX=OriginX;                          
	double shortY=OriginY;                          
	double shortDis=1000;                           
	int shortID=0;                                  
	int breakEarly=0;                               
	for(unsigned int i=0;i<vec.size();i++)        
	{
		if(gridStreet.count(vec[i])==0)          
		{
			continue;
		}
		for(unsigned int j=0;j<gridStreet[vec[i]].size();j++)     
		{
			double segX1,segY1,segX2,segY2;                             
			double tempD;                                               
			double tempMyX,tempMyY;                                     
			segX1=myStreets->get_StartPx(gridStreet[vec[i]][j]-1);
			segY1=myStreets->get_StartPy(gridStreet[vec[i]][j]-1);
			segX2=myStreets->get_EndPx(gridStreet[vec[i]][j]-1);
			segY2=myStreets->get_EndPy(gridStreet[vec[i]][j]-1);
			tempD=pointToSegDis(GX,GY,segX1,segY1,segX2,segY2,tempMyX,tempMyY);   
			if(shortDis<50 && tempD>283)           
			{
				breakEarly++;         
			}                         
			if(tempD<shortDis)
			{
				shortDis=tempD;
				shortX=tempMyX;
				shortY=tempMyY;
				shortID=gridStreet[vec[i]][j];
			}
		}
		if(breakEarly>8)     
		{
			break;
		}
	}
	 
	if(shortID!=0)                    
	{
		nearGridStreetID.push_back(shortID);
		nearGridStreetDis.push_back(shortDis);
		nearGridStreetX.push_back(shortX);
		nearGridStreetY.push_back(shortY);
	}

	 
	 

}

void Grid::getGridCenterXY(double combined,double &X,double &Y)
{
	int a1,a2;
	a1=int(combined);                               
	a2=round_double((combined-a1)*1000);            
	X=OriginX+(a2-1)*100;
	Y=OriginY-(a1-1)*100;
}

void Grid::makeWaitingDis(vector<double> &vec,int nearIndex)
{
	double Nx=nearGridStreetX[nearIndex];
	double Ny=nearGridStreetY[nearIndex];
	int StID=nearGridStreetID[nearIndex];
	map<int,int> checkHowMany;                        
	vector<int> InsertNode;                           
	pair<map<int,int>::iterator,bool> Insert_Pair;   
	int Number=1;                                     
	bool isStreetNode=false;                          
	if(myStreets->get_GraphNodeID(Nx,Ny)==0)          
	{
		Insert_Pair=checkHowMany.insert(pair<int,int>(myStreets->get_NodeSize()+1,Number));    
		if(Insert_Pair.second==true)
		{
			Number++;                                                     
			InsertNode.push_back(myStreets->get_NodeSize()+1);            
		}
	}
	else
	{
		isStreetNode=true;                                                
		Insert_Pair=checkHowMany.insert(pair<int,int>(myStreets->get_GraphNodeID(Nx,Ny),Number));    
		if(Insert_Pair.second==true)
		{
			Number++;                                                     
			InsertNode.push_back(myStreets->get_GraphNodeID(Nx,Ny));            
		}
	}
	
	for(unsigned int i=0;i<vec.size();i++)
	{
		for(unsigned int j=0;j<gridStreet[vec[i]].size();j++)
		{
			double segX1,segY1,segX2,segY2;                             
			segX1=myStreets->get_StartPx(gridStreet[vec[i]][j]-1);
			segY1=myStreets->get_StartPy(gridStreet[vec[i]][j]-1);
			segX2=myStreets->get_EndPx(gridStreet[vec[i]][j]-1);
			segY2=myStreets->get_EndPy(gridStreet[vec[i]][j]-1);
			Insert_Pair=checkHowMany.insert(pair<int,int>(myStreets->get_GraphNodeID(segX1,segY1),Number));    
			if(Insert_Pair.second==true)
			{
				Number++;                                                                 
				InsertNode.push_back(myStreets->get_GraphNodeID(segX1,segY1));            
			}
			Insert_Pair=checkHowMany.insert(pair<int,int>(myStreets->get_GraphNodeID(segX2,segY2),Number));    
			if(Insert_Pair.second==true)
			{
				Number++;                                                                 
				InsertNode.push_back(myStreets->get_GraphNodeID(segX2,segY2));            
			}
		}
	}
	waitingDisSize=checkHowMany.size();                  
	waitingDis=new Dis[waitingDisSize];                  
	if(waitingDisSize==1)                                
	{
		return;
	}
	 

	 
	 

	 
	if(isStreetNode)     
	{
		vector<int> manyNode;                                  
		int startID=InsertNode[0];                             
		myStreets->get_arcDirection(startID,manyNode);
		int beingSet;                                          
		for(unsigned int i=0;i<manyNode.size();i++)
		{
			beingSet=manyNode[i];
			waitingDis[checkHowMany[beingSet]-1].cost=myStreets->get_streetLength(myStreets->get_GraphStreetID(startID,beingSet)-1);    
		}
	}
	else                     
	{
		 
		double segX1,segY1,segX2,segY2;                             
		segX1=myStreets->get_StartPx(StID-1);
		segY1=myStreets->get_StartPy(StID-1);
		segX2=myStreets->get_EndPx(StID-1);
		segY2=myStreets->get_EndPy(StID-1);
		double TomSee1=sqrt((Nx-segX1)*(Nx-segX1)+(Ny-segY1)*(Ny-segY1));
		double TomSee2=sqrt((Nx-segX2)*(Nx-segX2)+(Ny-segY2)*(Ny-segY2));
		int Steve1=checkHowMany[myStreets->get_GraphNodeID(segX1,segY1)];
		int Steve2=checkHowMany[myStreets->get_GraphNodeID(segX2,segY2)];
		if(Steve1!=0)
		{
			waitingDis[checkHowMany[myStreets->get_GraphNodeID(segX1,segY1)]-1].cost=sqrt((Nx-segX1)*(Nx-segX1)+(Ny-segY1)*(Ny-segY1));        
		}
		if(Steve2!=0)
		{
			waitingDis[checkHowMany[myStreets->get_GraphNodeID(segX2,segY2)]-1].cost=sqrt((Nx-segX2)*(Nx-segX2)+(Ny-segY2)*(Ny-segY2));        
		}
	}
	waitingDis[0].cost=0;           
	waitingDis[0].visit=true;

	 
	dijkstra(checkHowMany,InsertNode);                            
	useWaitingDis(vec,checkHowMany,nearIndex);                         
	
	delete[] waitingDis;           
	InsertNode.clear();            
}

void Grid::dijkstra(map<int,int> checkHM,vector<int> InsertN)
{
	int countLeft=1;                        
	while(countLeft!=waitingDisSize)
	{
		double tempCost=9999.0;             
		int smallPos=-1;                     
		for(int i=0;i<waitingDisSize;i++)
		{
			if(waitingDis[i].cost<tempCost && waitingDis[i].visit==false)
			{
				tempCost=waitingDis[i].cost;
				smallPos=i;
			}
		}
		if(smallPos<0)
		{
			 
			break;
		}
		waitingDis[smallPos].visit=true;
		countLeft++;

		vector<int> manyNode;                                         
		int NowStartID=InsertN[smallPos];                             
		myStreets->get_arcDirection(NowStartID,manyNode);
		int beingSet;                                          
		double tempSum;                                        
		for(unsigned int i=0;i<manyNode.size();i++)
		{
			beingSet=manyNode[i];
			tempSum=tempCost+myStreets->get_streetLength(myStreets->get_GraphStreetID(NowStartID,beingSet)-1);           
			if(checkHM[beingSet]==0)                   
			{
				continue;
			}
			if(tempSum<waitingDis[checkHM[beingSet]-1].cost)       
			{
				waitingDis[checkHM[beingSet]-1].cost=tempSum;   
			}
		}
	}
}

void Grid::useWaitingDis(vector<double> &vec,map<int,int> checkHM,int nearIndex2)
{
	double Nx=nearGridStreetX[nearIndex2];                            
	double Ny=nearGridStreetY[nearIndex2];
	int StID=nearGridStreetID[nearIndex2];
	double temp_nearGridStreetDis=nearGridStreetDis[nearIndex2];

	int number=1;
	map<int,int> dontRepeat;                                 
	pair<map<int,int>::iterator, bool> Insert_Pair;          


	vector<int> tempNearStopID;                 
	vector<double> tempNearStopDis;             
	double tempTwoSegDis;                      
	for(unsigned int i=0;i<vec.size();i++)      
	{
		for(unsigned int j=0;j<gridStreet[vec[i]].size();j++)      
		{
			if(streetStop.count(gridStreet[vec[i]][j])==0)              
			{
				continue;
			}
			Insert_Pair=dontRepeat.insert(pair<int,int>(gridStreet[vec[i]][j],number));
			if(Insert_Pair.second==false)
			{
				continue;
			}
			else
			{
				number++;
			}
			double segX1,segY1,segX2,segY2;                             
			segX1=myStreets->get_StartPx(gridStreet[vec[i]][j]-1);
			segY1=myStreets->get_StartPy(gridStreet[vec[i]][j]-1);
			segX2=myStreets->get_EndPx(gridStreet[vec[i]][j]-1);
			segY2=myStreets->get_EndPy(gridStreet[vec[i]][j]-1);
			int tempID_1,tempID_2;
			tempID_1=myStreets->get_GraphNodeID(segX1,segY1);
			tempID_2=myStreets->get_GraphNodeID(segX2,segY2);
			for(unsigned int k=0;k<streetStop[gridStreet[vec[i]][j]].size();k++)   
			{
				int nowStopID=streetStop[gridStreet[vec[i]][j]][k];         
				double nowStopX,nowStopY;                                   
				nowStopX=myPoints->get_nearX(nowStopID-1);
				nowStopY=myPoints->get_nearY(nowStopID-1);
				if(StID==gridStreet[vec[i]][j])      
				{
					tempTwoSegDis=sqrt((Nx-nowStopX)*(Nx-nowStopX)+(Ny-nowStopY)*(Ny-nowStopY));                 
				}
				else                  
				{
					if(waitingDis[checkHM[tempID_1]-1].cost<waitingDis[checkHM[tempID_2]-1].cost)
					{
						double seg=sqrt((segX1-nowStopX)*(segX1-nowStopX)+(segY1-nowStopY)*(segY1-nowStopY));    
						tempTwoSegDis=waitingDis[checkHM[tempID_1]-1].cost+seg;                                 
					}
					else
					{
						double seg=sqrt((segX2-nowStopX)*(segX2-nowStopX)+(segY2-nowStopY)*(segY2-nowStopY));    
						tempTwoSegDis=waitingDis[checkHM[tempID_2]-1].cost+seg;                                 
					}
				}
				
				if(tempTwoSegDis>maxBusWalkingDis && nowStopID<=busOrSubwayDivide)               
				{
					continue;
				}
				if(tempTwoSegDis>maxSubwayWalkingDis && nowStopID>busOrSubwayDivide)              
				{
					continue;
				}
				tempNearStopID.push_back(nowStopID);                                  
				tempNearStopDis.push_back(tempTwoSegDis);                            
			}
		}
	}
	if(tempNearStopDis.size()==0)       
	{
		return;
	}

	 
	for(unsigned int i=0;i<tempNearStopDis.size();i++)
	{
		tempNearStopDis[i]=tempNearStopDis[i] + temp_nearGridStreetDis + myPoints->get_nearDis(tempNearStopID[i]-1);    
	}

	 
	map<double,int> recordPos;                                     
	pair<map<double,int>::iterator, bool> Insert_Pair2;             
	for(unsigned int i=0;i<tempNearStopDis.size();i++)
	{
		Insert_Pair2=recordPos.insert(pair<double,int>(tempNearStopDis[i],i));
	}

	int temp_i;                                                    
	double tempRecordDis=0;                                        
	for(unsigned int i=0;i<tempNearStopDis.size()-1;i++)
	{
		temp_i=i;
		for(unsigned int j=i+1;j<tempNearStopDis.size();j++)
		{
			if(tempNearStopDis[j]<tempNearStopDis[temp_i])   
			{
				temp_i=j;
			}
		}
		if(temp_i!=i)                                 
		{
			tempRecordDis=tempNearStopDis[i];
			tempNearStopDis[i]=tempNearStopDis[temp_i];
			tempNearStopDis[temp_i]=tempRecordDis;
		}
	}
	 
	for(unsigned int i=0;i<tempNearStopDis.size();i++)
	{
		if(tempNearStopDis[i]<maxBusWalkingDis && tempNearStopID[recordPos[tempNearStopDis[i]]]<=busOrSubwayDivide)      
		{
			temp_gridNearestStop.push_back(tempNearStopID[recordPos[tempNearStopDis[i]]]);
			temp_gridNearestStopDis.push_back(tempNearStopDis[i]);
		}
		if(tempNearStopDis[i]<maxSubwayWalkingDis && tempNearStopID[recordPos[tempNearStopDis[i]]]>busOrSubwayDivide)      
		{
			temp_gridNearestStop.push_back(tempNearStopID[recordPos[tempNearStopDis[i]]]);
			temp_gridNearestStopDis.push_back(tempNearStopDis[i]);
		}
	}

}

void Grid::makeFileOfGridNearestStop()
{
	ofstream outfile;
	outfile.open("D:\\data\\深圳数据\\修剪数据1\\gridNearestStop.csv");
	ofstream outfile2;
	outfile2.open("D:\\data\\深圳数据\\修剪数据1\\gridNearestStopHistogram.csv");         
	vector<int> Hist;
	for(int i=0;i<100;i++)
	{
		Hist.push_back(0);
	}
	for(unsigned int i=0;i<gridNearestStop.size();i++)                    
	{
		Hist[gridNearestStop[i].size()]++;
		if(gridNearestStop[i].size()>100)
		{
			cout<<gridNearestStop[i].size()<<endl;
		}
		outfile<<i<<","<<gridNearestStop[i].size()<<",";
		for(unsigned j=0;j<gridNearestStop[i].size();j++)                 
		{
			outfile<<myPoints->get_stopName(gridNearestStop[i][j]-1)<<"  "<<gridNearestStopDis[i][j]<<",";       
		}
		outfile<<"  end"<<endl;
	}
	for(int i=0;i<100;i++)
	{
		outfile2<<Hist[i]<<endl;
	}
	outfile2.close();
	outfile.close();
}
void Grid::makeFileOFStopNearestGrid()
{
	vector<int> tempStopG;                               
	vector<double> tempStopGDis;
	 
	for(int i=0;i<myPoints->getStopSize();i++)           
	{
		stopNearestGrid.push_back(tempStopG);
		stopNearestGridDis.push_back(tempStopGDis);
	}
	 
	for(unsigned int i=0;i<waitingRow.size();i++)                         
	{
		int nowStopID=0;                                                  
		for(unsigned j=0;j<gridNearestStop[i].size();j++)                 
		{
			nowStopID=gridNearestStop[i][j];                                   
			stopNearestGrid[nowStopID-1].push_back(i);                           
			stopNearestGridDis[nowStopID-1].push_back(gridNearestStopDis[i][j]);    
		}
	}
	 
	ofstream outfile;
	outfile.open("D:\\data\\深圳数据\\修剪数据2\\stopNearestGrid.csv");
	ofstream outfile2;
	outfile2.open("D:\\data\\深圳数据\\修剪数据2\\stopNearestGridDis.csv");
	for(int i=0;i<myPoints->getStopSize();i++)                                
	{
		outfile<<i<<","<<myPoints->get_stopName(i)<<","<<stopNearestGrid[i].size()<<",";
		outfile2<<i<<","<<myPoints->get_stopName(i)<<","<<stopNearestGridDis[i].size()<<",";
		for(unsigned j=0;j<stopNearestGrid[i].size();j++)                     
		{
			outfile<<stopNearestGrid[i][j]<<",";                              
			outfile2<<fixed<<setprecision(6)<<stopNearestGridDis[i][j]<<",";
		}
		outfile<<"end"<<endl;
		outfile2<<"end"<<endl;
	}

}


void Grid::mergeGrid()
{
	int classLabel=0;                                  
	int *gridClassLabel=new int[waitingRow.size()];    
	for(unsigned int i=0;i<waitingRow.size();i++)
	{
		gridClassLabel[i]=-1;                          
	}

	vector<double> aroundGrid3x3;                         
	double tempCombine;                                
	double mostSimilarCombine=0;                         
	for(unsigned int i=0;i<waitingRow.size();i++)      
	{
		if(gridClassLabel[i]!=-1)                      
		{
			continue;
		}
		if(gridNearestStop[i].size()==0)               
		{
			gridClassLabel[i]=0;
			continue;
		}
		tempCombine=waitingRow[i]+waitingColumn[i]/1000.0;                             
		findAroundGrid(tempCombine,aroundGrid3x3,2);                                   
		aroundGrid3x3.erase(aroundGrid3x3.begin());                                    
		tempIndicate++;
		mostSimilarCombine=getMostSimilarGrid(tempCombine,aroundGrid3x3);              
		if(mostSimilarCombine==0 || gridID.count(mostSimilarCombine)==0)              
		{
			gridClassLabel[i]=0;
			aroundGrid3x3.clear();
			continue;
		}
		if(i!=gridID[tempCombine])
		{
			cout<<"当前的第i个格网与gridID的反索引居然不对应"<<endl;
		}
		if(gridClassLabel[gridID[mostSimilarCombine]]==0)                                   
		{
			cout<<"当前格网已经属于0类了"<<endl;
			gridClassLabel[i]=0;
		}
		if(gridClassLabel[gridID[mostSimilarCombine]]==-1)                                   
		{
			classLabel++;
			gridClassLabel[gridID[tempCombine]]=classLabel;
			gridClassLabel[gridID[mostSimilarCombine]]=classLabel;
		}
		else                                                                                
		{
			gridClassLabel[gridID[tempCombine]]=gridClassLabel[gridID[mostSimilarCombine]];
		}
		aroundGrid3x3.clear();
	}
	cout<<"classLabe已经累加到了： "<<classLabel<<"并且gridID的大小也没问题"<<gridID.size()<<endl;                        
	makeFileOfGridClassLabel(gridClassLabel,waitingRow.size());                                  
	seeClassCountDistribute(gridClassLabel,waitingRow.size(),classLabel);                

	makeFileOFDistrictOwnStops(gridClassLabel,classLabel);
	delete[] gridClassLabel;

}
double Grid::getMostSimilarGrid(double center,vector<double> vec)
{
	vector<double> tempSimilar;                           
	double smallestSimilarPos=0;                            
	for(unsigned int i=0;i<vec.size();i++)
	{
		if(gridID.count(vec[i])==0)                         
		{
			tempSimilar.push_back(2);           
			continue;
		}
		if(gridNearestStop[gridID[vec[i]]].size()==0)     
		{
			tempSimilar.push_back(2);                   
			continue;
		}
		 
		 
	    double dis_AB=0;														  
		dis_AB=getABdis(center,vec[i]);                                           
		tempSimilar.push_back(getSimilar(dis_AB,gridID[center],gridID[vec[i]]));  
	}
	if(tempSimilar.size()!=vec.size())
	{
		cout<<"出现了计算的相似值个数与周围有效格网数不相等的情况"<<endl;
	}
	for(unsigned int i=0;i<tempSimilar.size();i++)
	{
		if(tempSimilar[i]>2)                            
		{
			cout<<tempSimilar[i]<<"竟然出现了大于2的相似值"<<endl;
		}
	}
	 
	double tempSmall=2;                             
	for(unsigned int i=0;i<tempSimilar.size();i++)
	{
		if(tempSimilar[i]<=tempSmall)                       
		{
			if(tempSimilar[i]==tempSmall && gridID.count(smallestSimilarPos)!=0 && gridID.count(vec[i])!=0 && gridID[vec[i]]<gridID[smallestSimilarPos])  
			{                                   
				tempSmall=tempSimilar[i];
				smallestSimilarPos=vec[i];
				continue;
			}
			if(tempSimilar[i]<tempSmall)
			{
				tempSmall=tempSimilar[i];
				smallestSimilarPos=vec[i];
			}
		}
	}

	tempSimilar.clear();
	return smallestSimilarPos;
}
void Grid::makeGridPosToGirdID()
{
	pair<map<double,int>::iterator, bool> Insert_Pair;               
	double tempCombine;                                              
	for(unsigned int i=0;i<waitingRow.size();i++)                    
	{
		tempCombine=waitingRow[i]+waitingColumn[i]/1000.0;                           
		Insert_Pair=gridID.insert(pair<double,int>(tempCombine,i));                  
		if(Insert_Pair.second==false)
		{
			cout<<"this is impossible for outputting an Gird ID"<<endl;
		}
	}
	cout<<"makeGridPosToGirdID()"<<gridID.size()<<endl;
}
double Grid::getABdis(double A,double B)
{
	int a1,a2;                      
	a1=int(A);                      
	a2=round_double((A-a1)*1000);            
	int b1,b2;                      
	b1=int(B);                      
	b2=round_double((B-b1)*1000);            
	double edge1=abs(a1-b1);                 
	double edge2=abs(a2-b2);
	double slash=100*sqrt(edge1*edge1+edge2*edge2);
	return slash;

}
double Grid::getSimilar(double AB,int vecO,int vecS)
{
	vector<int> unionABBus;                                  
	map<int,int> unionMapBus;                                
	pair<map<int,int>::iterator, bool> Insert_PairABBus; 

	vector<int> unionABSubway;                                  
	map<int,int> unionMapSubway;                                
	pair<map<int,int>::iterator, bool> Insert_PairABSubway; 

	map<int,double> AMapDis;                              
	map<int,double> BMapDis;
	pair<map<int,double>::iterator, bool> Insert_PairA;
	pair<map<int,double>::iterator, bool> Insert_PairB;


	 
	if(gridNearestStop[vecO].size()==gridNearestStop[vecS].size())                         
	{
		bool allIsTheSame=true;
		for(unsigned int i=0;i<gridNearestStop[vecO].size();i++)                           
		{
			if(gridNearestStop[vecO][i]!=gridNearestStop[vecS][i])                         
			{
				allIsTheSame=false;
				break;
			}
		}
		if(allIsTheSame)                
		{
			return 0;
		}
	}

	

	 
	for(unsigned int i=0;i<gridNearestStop[vecO].size();i++)                            
	{
		Insert_PairA=AMapDis.insert(pair<int,double>(gridNearestStop[vecO][i],gridNearestStopDis[vecO][i]));     
		if(Insert_PairA.second==false)
		{
			cout<<"居然构建A格网的站点map距离没插入成功"<<endl;
			cout<<tempIndicate<<"  "<<vecO<<"  "<<vecS<<endl;
			system("pause");
		}

		if(gridNearestStop[vecO][i]<=busOrSubwayDivide)                                      
		{
			Insert_PairABBus=unionMapBus.insert(pair<int,int>(gridNearestStop[vecO][i],i));                        
			if(Insert_PairABBus.second==false)
			{
				cout<<"居然构建公交unionMap没插入成功"<<endl;
				cout<<tempIndicate<<"  "<<vecO<<"  "<<vecS<<endl;
				system("pause");
			}
			else
			{
				unionABBus.push_back(gridNearestStop[vecO][i]);
			}
		}
		else
		{
			Insert_PairABSubway=unionMapSubway.insert(pair<int,int>(gridNearestStop[vecO][i],i));                        
			if(Insert_PairABSubway.second==false)
			{
				cout<<"居然构建公交unionMap没插入成功"<<endl;
				cout<<tempIndicate<<"  "<<vecO<<"  "<<vecS<<endl;
				system("pause");
			}
			else
			{
				unionABSubway.push_back(gridNearestStop[vecO][i]);
			}
		}
		
	}

	 
	for(unsigned int i=0;i<gridNearestStop[vecS].size();i++)
	{
		Insert_PairB=BMapDis.insert(pair<int,double>(gridNearestStop[vecS][i],gridNearestStopDis[vecS][i]));
		if(Insert_PairB.second==false)
		{
			cout<<"居然构建B格网的站点map距离没插入成功"<<endl;
			cout<<tempIndicate<<"  "<<vecO<<"  "<<vecS<<endl;
			system("pause");
		}

		if(gridNearestStop[vecS][i]<=busOrSubwayDivide)                                          
		{
			Insert_PairABBus=unionMapBus.insert(pair<int,int>(gridNearestStop[vecS][i],i));                        
			if(Insert_PairABBus.second==true)                                                                      
			{
				unionABBus.push_back(gridNearestStop[vecS][i]);
			}
		}
		else
		{
			Insert_PairABSubway=unionMapSubway.insert(pair<int,int>(gridNearestStop[vecS][i],i));
			if(Insert_PairABSubway.second==true)                                                                      
			{
				unionABSubway.push_back(gridNearestStop[vecS][i]);
			}
		}
		
	}
	 
	   
	double sumBus=0;                              
	double sumSubway=0;                           
	 
	for(unsigned int i=0;i<unionABBus.size();i++)
	{
		double Adis=0;                            
		double Bdis=0;
		if(AMapDis.count(unionABBus[i])!=0)
		{
			Adis=AMapDis[unionABBus[i]];            
		}
		else
		{
			Adis=BMapDis[unionABBus[i]]+AB;         
		}
		if(BMapDis.count(unionABBus[i])!=0)
		{
			Bdis=BMapDis[unionABBus[i]];            
		}
		else
		{
			Bdis=AMapDis[unionABBus[i]]+AB;         
		}
		 
		sumBus=sumBus + (abs(Adis-Bdis)*abs(Adis-Bdis))*((Adis+Bdis)/(2*maxBusWalkingDis+242.84));
	}
	 
	for(unsigned int i=0;i<unionABSubway.size();i++)
	{
		double Adis=0;                            
		double Bdis=0;
		if(AMapDis.count(unionABSubway[i])!=0)
		{
			Adis=AMapDis[unionABSubway[i]];            
		}
		else
		{
			Adis=BMapDis[unionABSubway[i]]+AB;         
		}
		if(BMapDis.count(unionABSubway[i])!=0)
		{
			Bdis=BMapDis[unionABSubway[i]];            
		}
		else
		{
			Bdis=AMapDis[unionABSubway[i]]+AB;         
		}
		 
		sumSubway=sumSubway + (abs(Adis-Bdis)*abs(Adis-Bdis))*((Adis+Bdis)/(2*maxSubwayWalkingDis+242.84));
	}

	AMapDis.clear();
	BMapDis.clear();
	unionMapBus.clear();
	unionMapSubway.clear();

	double SimilarBus=0;
	if(unionABBus.size()!=0)
	{
		SimilarBus=sqrt(sumBus/unionABBus.size())/maxBusWalkingDis;
	}
	
	double SimilarSubway=0;
	if(unionABSubway.size()!=0)
	{
		SimilarSubway=sqrt(sumSubway/unionABSubway.size())/maxSubwayWalkingDis;
	}
	double sumSimilar=SimilarBus+SimilarSubway;
	if(sumSimilar>=2)
	{
		cout<<"公交的相似值和地铁的相似值加起来居然会有大于2的情况！"<<endl;
	}
	return sumSimilar;                               

}
void Grid::makeFileOfGridClassLabel(int *gridClass,int classSize)
{
	ofstream outfile;
	outfile.open("D:\\data\\深圳数据\\修剪数据1\\gridClassLabel.csv");
	for(int i=0;i<classSize;i++)                   
	{
		outfile<<gridClass[i]<<endl;
	}
	outfile.close();
	cout<<"makeFileOfGridClassLabel执行完毕"<<endl;
}
void Grid::seeClassCountDistribute(int *gridClass,int gridSize,int classCount)
{
	int *classLabel=new int[classCount+1];               
	for(int i=0;i<classCount+1;i++)
	{
		classLabel[i]=0;                               
	}
	for(int i=0;i<gridSize;i++)              
	{
		classLabel[gridClass[i]]++;                    
		if(gridClass[i]==1)
		{
			cout<<i<<endl;
		}
	}
	int seeSize=0;
	int tempSeeMax=0;                                     
	vector<int> tempSeeMin;                                    
	for(int i=1;i<classCount+1;i++)                    
	{
		if(classLabel[i]>seeSize)
		{
			seeSize=classLabel[i];
			tempSeeMax=i;
		}
		if(classLabel[i]==1)
		{
			tempSeeMin.push_back(i);                       
		}
	}
	cout<<"最大类别数的类别为："<<tempSeeMax<<endl;
	cout<<"最多格网数的那个类别的具体格网分别是："<<endl;
	for(int i=0;i<gridSize;i++)              
	{
		if(gridClass[i]==tempSeeMax)
		{
			cout<<i<<endl;
		}
	}
	cout<<"格网数为1的那个类别的具体格网分别是："<<endl;
	for(int i=0;i<gridSize;i++)              
	{
		for(unsigned int j=0;j<tempSeeMin.size();j++)
		{
			if(gridClass[i]==tempSeeMin[j])
			{
				cout<<i<<endl;
				break;
			}
		}
		
	}
	seeSize=seeSize+2;
	int *seeCount=new int[seeSize];                         
	for(int i=0;i<seeSize;i++)
	{
		seeCount[i]=0;
	}
	for(int i=0;i<classCount;i++)
	{
		int a=classLabel[i];                          
		if(a>seeSize-1)
		{
			seeCount[seeSize-1]=seeCount[seeSize-1]+a;
		}
		if(a<=seeSize-1)
		{
			seeCount[a-1]=seeCount[a-1]+a;
		}
		if(a==0)
		{
			cout<<"出现了某个类别里居然为空的情况"<<endl;
		}
	}
	ofstream outfile;
	outfile.open("D:\\data\\深圳数据\\修剪数据1\\GOC_ownNumbers.csv");

	int sum=0;
	for(int i=0;i<seeSize;i++)
	{
		if(i<seeSize-1)
		{
			cout<<i+1<<"个格网的类别数： "<<seeCount[i]/(i+1)<<"个类别"<<endl;
			outfile<<i+1<<","<<seeCount[i]/(i+1)<<endl;
			sum=sum+seeCount[i]/(i+1);
		}
		else
		{
			cout<<seeCount[i]<<"个格网"<<endl;
			sum=sum+1;
		}
		
		if(i==seeSize-1)
		{
			cout<<"这里统计的总共类别数为： "<<sum<<endl;
		}
	}
	outfile.close();
	cout<<"seeClassCountDistribute()"<<endl;

	delete[] classLabel;
}

void Grid::betterMakeGridNearestStop()
{
	int tempGridID;                                   
	int sumChange=0;                                  
	for(int i=0;i<myPoints->getStopSize();i++)        
	{
		double tempG=getGridPos(myPoints->get_pointX(i),myPoints->get_pointY(i));    
		if(gridID.count(tempG)!=0)                    
		{
			tempGridID=gridID[tempG];       
			 
			if(gridNearestStop[tempGridID].size()==0)     
			{
				gridNearestStop[tempGridID].push_back(myPoints->get_stopID(i));     
				double X1,Y1;                                                       
				getGridCenterXY(tempG,X1,Y1);
				double tempDis=sqrt((X1-myPoints->get_pointX(i))*(X1-myPoints->get_pointX(i))+(Y1-myPoints->get_pointY(i))*(Y1-myPoints->get_pointY(i)));
				gridNearestStopDis[tempGridID].push_back(tempDis);
				sumChange++;
				 
				 
				 
			}
		}
	}
	cout<<"新填充了多少个有站点但为0类的格网："<<sumChange<<endl;
}
void Grid::makeFileOFDistrictOwnStops(int *gridClass, int classCount)
{
	ofstream outfile;
	outfile.open("D:\\data\\深圳数据\\修剪数据1\\districtOwnStops.csv");
	vector<vector<string>> districtOwnStops;		
	vector<string> tempOwnStop;
	if(classCount+1 != 18109)
	{
		cout<<"看一下这个到底是多少！！！！！！是不是18109"<<classCount+1<<endl;
		system("pause");
	}
	for(int i=0; i<classCount+1; i++)
	{
		districtOwnStops.push_back(tempOwnStop);
	}

	for(unsigned int i=0;i<waitingRow.size();i++)      
	{
		for(unsigned j=0;j<gridNearestStop[i].size();j++)    
		{
			string tempS = myPoints->get_stopName(gridNearestStop[i][j]-1);
			bool have=false;
			for(unsigned k=0;k<districtOwnStops[gridClass[i]].size();k++)   
			{
				if(tempS == districtOwnStops[gridClass[i]][k])              
				{
					have=true;
					break;
				}
			}
			if(have)           
			{
				continue;
			}
			else
			{
				districtOwnStops[gridClass[i]].push_back(tempS);
			}
			
		}			
	}

	for(int i=0; i<classCount+1; i++)                  
	{
		for(unsigned j=0;j<districtOwnStops[i].size();j++)     
		{
			if(j==districtOwnStops[i].size()-1)
			{
				outfile<<districtOwnStops[i][j]<<endl;
			}
			else
			{
				outfile<<districtOwnStops[i][j]<<",";
			}
			
		}
	}

	outfile.close();
	cout<<"makeFileOFDistrictOwnStops()"<<endl;
}

void Grid::run()
{
	makeGridStreetMap();                   
	makeStreetStopMap();                   
	makeFileOfProjectedPoint();            

	readWaitingArray();                      
	makeGridPosToGirdID();                   
	makeGridNearestStop();                   
	betterMakeGridNearestStop();             
	makeFileOfGridNearestStop();             
	makeFileOFStopNearestGrid();             
	
	mergeGrid();                             
	 
}