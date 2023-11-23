#include "ENDFLib.hh"
#include "../Parser.cpp"
#include "Math/IFunction.h"
#include "Math/SpecFuncMathMore.h"
#include <cmath>
//#include <curl/curl.h>
#pragma once
//нужен пакет libzip-dev
//substr(a,b) возвращает строку, начинающуюся с а длиной b символов

double EvaluatedDataGraph::EvalChi2(TObject *InpObj)
{
	double result=0;
	if(InpObj->InheritsFrom("TMultiGraph"))
	{
		TList* GraphList=((TMultiGraph*)InpObj)->GetListOfGraphs();
		int NumberOfGraphs=GraphList->GetEntries();
		cout<<"NumberOfGraphs:"<<NumberOfGraphs<<"\n";
		for(int j=0;j<NumberOfGraphs;j++)
		{
			TObject* obj=GraphList->At(j);
			if(obj->InheritsFrom("TGraphErrors"))
			{
				TGraphErrors* g=(TGraphErrors*)obj;
				for(int k=0;k<g->GetN();k++)
				{
					double x,y,ex,ey;
					g->GetPoint(k,x,y);
					ex=g->GetErrorX(k);
					ey=g->GetErrorY(k);
					result+=pow(y-this->Eval(x),2)/(pow(ex,2)+pow(ey,2));
				}
			}
			else if(obj->InheritsFrom("TGraph"))
			{
				TGraph* g=(TGraph*)obj;
				for(int k=0;k<g->GetN();k++)
				{
					double x,y;
					g->GetPoint(k,x,y);
					result+=pow(y-this->Eval(x),2);
				}
			}
		}
	}
	else if(InpObj->InheritsFrom("TGraphErrors"))
	{
		TGraphErrors* g=(TGraphErrors*)InpObj;
		for(int k=0;k<g->GetN();k++)
		{
			double x,y,ex,ey;
			g->GetPoint(k,x,y);
			ex=g->GetErrorX(k);
			ey=g->GetErrorY(k);
			result+=pow(y-this->Eval(x),2)/(pow(ex,2)+pow(ey,2));
		}
	}
	else if(InpObj->InheritsFrom("TGraph"))
	{
		TGraph* g=(TGraph*)InpObj;
		for(int k=0;k<g->GetN();k++)
		{
			double x,y;
			g->GetPoint(k,x,y);
			result+=pow(y-this->Eval(x),2);
		}
	}
	return result;
}

void EvaluatedDataGraph::Add(TGraph *gr)
{
	if(!gr)
	{
		cout<<"This is valuatedDataGraph::Add(TGraph *gr): pointer to TGraph is empty!\n";
	}
	EvaluatedDataGraph *g1=0,*g2=0;
	if(GetN()>gr->GetN())
	{
		g1=this; g2=(EvaluatedDataGraph*)gr;
	}
	else
	{
		g2=this; g1=(EvaluatedDataGraph*)gr;
	}
	vector<double> x,y;
	for(int i=0;i<g1->GetN();i++)
	{
		double x_val,y_val;
		g1->GetPoint(i,x_val,y_val);
		x.push_back(x_val);
		y.push_back(y_val);
	}
	for(unsigned int i=0;i<x.size();i++)
	{
		y[i]+=g2->Eval(x[i]);
	}
	Set(0);
	for(unsigned int i=0;i<x.size();i++)
	{
		SetPoint(i,x[i],y[i]);
	}
}

double ENDFAtof(string s)//костыль для устранения проблемы с представлением экспоненциальной части числа: по умолчанию 1.000000-5 читается как 1
{
	string s2;
	if(s.find("E")==string::npos)
	{
		for(unsigned int i=0;i<s.size();i++)
		{
			if(((s[i]=='+')||(s[i]=='-'))&&(i>0))
			{
				int s_m=i-1;
				int s_p=i+1;
				if(s_p<(int)s.size())
				{
					if(((s[s_m]>='0')&&(s[s_m]<='9'))&&((s[s_p]>='0')&&(s[s_p]<='9')))
					{
						s2+='E';
						s2+=s[i];
					}
				}
			}
			else
			{
				s2+=s[i];
			}
		}
	}
	else
	{
		s2=s;
	}
	return atof(s2.c_str());
}

bool GetNextString(zip *z,zip_file *f, string &result)
{
	result.resize(0);
	int Iterator=0;
    char c=0;
    while(zip_fread(f,&c,1)>0)
    {
		if((c!='\r')&&(c!='\n'))
		{
			//if(c!='\n')
			result+=c;
		}
		else
		{
			return true;
		}
		Iterator++;
	}
	if(Iterator>0)
	return true;
	return false;
}

void GetMAT_MF_MT_NSTR(string inp, int &MAT, int &MF, int&MT, int &NSTR)
{
	if(inp.size()<75)
	{
		return;
	}
	MAT=atoi(inp.substr(66,4).c_str());
	MT=atoi(inp.substr(72,3).c_str());
	MF=atoi(inp.substr(70,2).c_str());
	NSTR=atoi(inp.substr(75,5).c_str());
//	cout<<MAT<<" "<<MT<<" "<<MF<<" "<<NSTR<<"\n";
}

MTEntry::MTEntry(string inp)
{
	GetFromString(inp);
}
void MTEntry::GetFromString(string inp)
{
	stringstream s(inp);
	s>>MT>>Reaction;
	getline(s,EntryDescription);
}
void ENDFDictonary::ReadMTDictonary()
{
	string PathToDictonaries=getenv("TALYSLIBDIR");
	PathToDictonaries+="/ENDFReader/";
	ifstream ifs(PathToDictonaries+"MT_Codes.txt");
	string line;
	while(getline(ifs,line))
	{
		MTEntry MT(line);
		MTDictonary[MT.MT]=MT;
	}
	ifs.close();
	line="";
	ifs.open(PathToDictonaries+"MF_Codes.txt");
	while(getline(ifs,line))
	{
		stringstream s(line);
		int MF=0;
		s>>MF;
		getline(s,line);
		MFDictonary[MF]=line;
	}
}

string ENDFDictonary::GetMFDescription(int MF)
{
	map<int,string>::iterator it;
	it=MFDictonary.find(MF);
	if (it != MFDictonary.end())
	{
		return it->second;
	}
	return "";
}

MTEntry* ENDFDictonary::GetEntryByMT(int MT)
{
	map<int,MTEntry>::iterator it;
	it=MTDictonary.find(MT);
	if (it != MTDictonary.end())
	{
		return &(it->second);
	}
	return 0;
}
string ENDFDictonary::GetMTDescription(int MT)
{
	MTEntry* m=GetEntryByMT(MT);
	if(!m)
	{
		return "MT entry "+to_string(MT)+" not found!";
	}
	return m->EntryDescription;
}
void ENDFDescription::AddFromString(string inp)
{
	if(inp.size()<75)
	{
		return;
	}
	Content+=(inp.substr(0,66)+"\n");
}

/*void ENDFDescription::GetZA(int &Z,int &A)
{
	stringstream str(Content);
	int value=0;
	str>>value;
	Z=value/1000;
	A=value%1000;
}*/

bool ENDFContentEntry::GetFromString(string inp)
{
	if(inp.size()<75)
	{
		return false;
	}
	if(inp.find("                          ")!=string::npos)
	{
		//cout<<inp<<"\n";
		FileNumber=atoi(inp.substr(31,2).c_str());
		int MT=atoi(inp.substr(41,3).c_str());
		NRows=atoi(inp.substr(50,5).c_str());
		//cout<<FileNumber<<" "<<MT<<" "<<NRows<<"\n";
		MTEntry *mte=ENDFDictonary::Instance()->GetEntryByMT(MT);
		if(mte)
		{
			Entry_MT=*mte;
		}
		return true;
	}
	return false;
	
}
void ENDFContent::GetFromString(string inp)
{
	if(inp.size()<75)
	{
		return;
	}
	ENDFContentEntry entr;
	if(entr.GetFromString(inp))
	Entries.push_back(entr);
}

TString ENDFContent::GetEntriesInTLatexFormat()
{
	TString result;
	for(unsigned int i=0;i<Entries.size();i++)
	{
		string Row=to_string(i+1)+" "+to_string(Entries[i].FileNumber)+" "+Entries[i].Entry_MT.Reaction+" "+Entries[i].Entry_MT.EntryDescription;
		result+=TString(Row.c_str())+"\n";
	}
	return result;
}

double& ENDFBasicTable::at(unsigned int Column, unsigned int Row)
{
	if(Table.size()<Column+1)
	{
		Table.resize(Column+1);
	}
	if(Table[Column].size()<Row+1)
	{
		Table[Column].resize(Row+1);
	}
	return Table[Column][Row];
}
double* ENDFBasicTable::Get(unsigned int Column, unsigned int Row)
{
	if(Table.size()<Column+1)
	{
		return 0;
	}
	if(Table[Column].size()<Row+1)
	{
		return 0;
	}
	return &Table[Column][Row];
}
void ENDFBasicTable::GetFromStringBase(string inp)
{
	if(inp.size()<75)
	{
		return;
	}
	if(Table.size()<6)
	{
		Table.resize(6);
	}
	for(unsigned int i=0;i<6;i++)
	{
		Table[i].push_back(ENDFAtof(inp.substr(i*11,11).c_str()));
	}
	
}

vector<double> ENDFBasicTable::GetColumn(unsigned int Column)
{
	if(Table.size()<6)
	{
		vector<double> tmp;
		return tmp;
	}
	return Table[Column];
}
vector<double> ENDFBasicTable::GetRow(unsigned int Row)
{
	vector<double> result;
	for(unsigned int i=0;i<Table.size();i++)
	{
		if(Table[i].size()>Row)
		result.push_back(Table[i][Row]);
	}
	return result;
}

int ENDFBasicTable::GetNRows()
{
	if(Table.size()<6)
	{
		return 0;
	}
	return Table[0].size();
}
void ENDFBasicTable::GetSizes(unsigned int &NColumns,unsigned int &NRows)
{
	if(Table.size()<6)
	{
		NRows=0;
	}
	else
	{
		NColumns=Table.size();
		NRows=Table[0].size();
	}
}

vector<double> ENDFBasicTable::GetSequence(unsigned int Column,unsigned int Row,unsigned int Length,unsigned int *NextColumn,unsigned int *NextRow)
{
	vector<double> result;
	if(Column>=Table.size())
	{
		return result;
	}
	if(Row>=Table[Column].size())
	{
		return result;
	}
	int CurrentColumn=Column;
	int CurrentRow=Row;
	for(unsigned int i=0;i<Length;i++)
	{
		if(CurrentColumn>=(int)Table.size())
		{
			CurrentColumn=0;
			CurrentRow++;
		}
		if(CurrentRow>=(int)Table[CurrentColumn].size())
		{
			return result;
		}
		result.push_back(Table[CurrentColumn][CurrentRow]);
		CurrentColumn++;
		if(NextColumn&&NextRow)
		{
			*NextColumn=CurrentColumn;
			*NextRow=CurrentRow;
		}
	}
	return result;
}

void ENDFBasicTable::GetSequence2(vector<double> &x,vector<double> &y,unsigned int Column,unsigned int Row,unsigned int Length,unsigned int *NextColumn,unsigned int *NextRow)
{
	if(Column>=Table.size())
	{
		return;
	}
	if(Row>=Table[Column].size())
	{
		return;
	}
	int CurrentColumn=Column;
	int CurrentRow=Row;
	for(unsigned int i=0;i<Length;i++)
	{
		if(CurrentColumn>=(int)Table.size())
		{
			CurrentColumn=0;
			CurrentRow++;
		}
		if(CurrentRow>=(int)Table[CurrentColumn].size())
		{
			return;
		}
		x.push_back(Table[CurrentColumn][CurrentRow]);
		y.push_back(Table[CurrentColumn+1][CurrentRow]);
		CurrentColumn+=2;
		if(NextColumn&&NextRow)
		{
			*NextColumn=CurrentColumn;
			*NextRow=CurrentRow;
		}
	}
}

TGraph* ENDFAngularDistribution::GetAngularDistribution(string _Type,int NPoints)
{
	vector<double> DegVector;
	vector<double> CosVector;
	vector<double> Y;
	if(ADistGraph.GetN()>0)
	{
		return &ADistGraph;
	}
	if(Type==1)//Лежандры
	{
		if(_Type=="Deg")
		{
			double Step=180.0/NPoints;
			double Deg=0;
			while(Deg<180)
			{
				DegVector.push_back(Deg);
				CosVector.push_back(cos(Deg/180.0*3.1416));
				Deg+=Step;
			}
		}
		else if(_Type=="Cos")
		{
			double Step=2/NPoints;
			double Cos=-1;
			while(Cos<1)
			{
				CosVector.push_back(Cos);
				Cos+=Step;
			}
		}
		for(unsigned int i=0;i<CosVector.size();i++)
		{
			double result=1;
			for(unsigned int j=0;j<LegendreCoefficients.size();j++)
			{
				result+=(2*(j+1)+1)*LegendreCoefficients[j]*ROOT::Math::legendre((j+1),CosVector[i]);
			}
			Y.push_back(result);
		}
	}
	else if(Type==2)//таблица
	{
		CosVector=XValues;
		Y=YValues;
		for(unsigned int i=0;i<CosVector.size();i++)
		{
			DegVector.push_back(acos(CosVector[i])*180/3.1416);
		}
	}
	if(_Type=="Deg")
	{
		//ADistGraph=TGraph(DegVector.size(),&DegVector[0],&Y[0]);
		for(unsigned int i=0;i<DegVector.size();i++)
		{
			if(Y[i]>0)
			ADistGraph.SetPoint(ADistGraph.GetN(),DegVector[i],Y[i]);
		}
		
	}
	else if(_Type=="Cos")
	{
		for(unsigned int i=0;i<CosVector.size();i++)
		{
			if(Y[i]>0)
			ADistGraph.SetPoint(ADistGraph.GetN(),CosVector[i],Y[i]);
		}
	}
	return &ADistGraph;
}

vector<double> ENDFTable::GetX()
{
	vector<double> result;
	if(Table.size()<6)
	{
		return result;
	}
	if(Type==1)
	{
		result.resize(Table[0].size()*3);
		int iterator=0;
		for(unsigned int j=0;j<Table[0].size();j++)
		{
			for(unsigned int i=0;i<6;i+=2)
			{
				if(Table[i][j]!=0)
				{
					result[iterator]=Table[i][j];
					iterator++;
				}
			}
		}
		result.resize(iterator);
	}
	return result;
}
vector<double> ENDFTable::GetY()
{
	vector<double> result;
	if(Table.size()<6)
	{
		return result;
	}
	if(Type==1)
	{
		result.resize(Table[0].size()*3);
		int iterator=0;
		for(unsigned int j=0;j<Table[0].size();j++)
		{
			
			for(unsigned int i=1;i<6;i+=2)
			{
				if(Table[i][j]!=0)
				{
					result[iterator]=Table[i][j];
					iterator++;
				}
			}
		}
		result.resize(iterator);
	}
	return result;
}
vector<double> ENDFTable::GetZ()
{
	vector<double> result;
	if((Table.size()<6)||(Type==1))
	{
		return result;
	}
	return result;
}

void ENDFTable::GetFromString(string inp,int *_MF,int *_MT)
{
	
	if(_MF&&_MT)
	{
		if((MF!=*_MF)||(MT!=*_MT))
		{
			return;
		}
	}
	//видимо, в будущем надо будет добавить возможность подгружать правила чтения из текстового файла
	if(MF==3)
	{
		if(Header.GetNRows()<3)
		{
			//cout<<"Header:"<<inp<<"\n";
			Header.GetFromStringBase(inp);
		}
		else
		{
			//cout<<"Body:"<<inp<<"\n";
			GetFromStringBase(inp);
		}
	}
	if(MF==4)
	{
		if(Header.GetNRows()<4)
		{
			//cout<<"Header:"<<inp<<"\n";
			Header.GetFromStringBase(inp);//заголовок содержит 4 строки, в которых записана информация о типе распределения
		}
		else
		{
			GetFromStringBase(inp);
		}
	}
	if(MF==14)
	{
		if(Header.GetNRows()<1)
		{
			Header.GetFromStringBase(inp);
		}
		else
		{
			GetFromStringBase(inp);
		}
	}
	if((MT==451))
	{
		if(Header.GetNRows()<5)
		{
			Header.GetFromStringBase(inp);
		}
		else
		{
			if(inp.size()>=75)
			{
				if(atoi(inp.substr(41,3).c_str())==451)
				IsContentSection=true;
			}
			if(IsContentSection)
			{
				GetFromStringBase(inp);
			}
		}
	}
	
}

void ENDFTable::GenerateAngularDistributions4()
{
	if(MF!=4)
	{
		return;
	}
	int LTT=Header.at(3,0);
	int LI=Header.at(2,1);
	if(LTT==1&&LI==0)//When LTT=1 (angular distributions given in terms of Legendre polynomial coefficients), the structure of the section is
	{
		unsigned int NColumns=0, NRows=0;
		GetSizes(NColumns,NRows);
		unsigned int CurrentRow=0;
		while(CurrentRow<NRows)
		{
			ENDFAngularDistribution ADist;
			ADist.Type=1;
			ADist.Energy=at(1,CurrentRow);
			unsigned int NL=at(4,CurrentRow);
			unsigned int CurrentColumn;
			unsigned int NextRow=0;
			CurrentRow++;
			ADist.LegendreCoefficients=GetSequence(0,CurrentRow,NL,&CurrentColumn,&NextRow);
			//cout<<"Energy "<<ADist.Energy<<" "<<NL<<" "<<ADist.LegendreCoefficients.size()<<"\n";
			ADist.fTable=this;
			if(ADist.LegendreCoefficients.size()>0)
			ADist4.push_back(ADist);
			CurrentRow++;
		}
	}
	if(LTT==2&&LI==0)//Tabulated Probability Distributions (LTT=2, LI=0), найдем пример, тогда и сделаем//Упругое на 31P, смотреть описание на английском стр 109 или стр 100 на русском (https://www.ippe.ru/images/oyarit/reactor-constants-datacenter/ENDF-6format.pdf)
	{
		
	}
	if(LTT==3&&LI==0)//Angular Distribution Over Two Energy Ranges (LTT=3,LI=0)
	{
		unsigned int NColumns=0, NRows=0;
		GetSizes(NColumns,NRows);
		unsigned int CurrentRow=0;
		bool IsTableNow=false;
		while(CurrentRow<NRows)
		{
			if(Table[0][CurrentRow]==0&&Table[1][CurrentRow]==0)
			{
				IsTableNow=true;
				break;
			}
			ENDFAngularDistribution ADist;
			ADist.Type=1;
			ADist.Energy=at(1,CurrentRow);
			unsigned int NL=at(4,CurrentRow);
			unsigned int CurrentColumn;
			unsigned int NextRow=0;
			//cout<<"Energy "<<ADist.Energy<<" "<<NL<<"\n";
			//if(ADist.Energy==2.5600000)
			//{
				
			//}
			CurrentRow++;
			ADist.LegendreCoefficients=GetSequence(0,CurrentRow,NL,&CurrentColumn,&NextRow);
			CurrentRow=NextRow;
			ADist.fTable=this;
			if(ADist.LegendreCoefficients.size()>0)
			ADist4.push_back(ADist);
			CurrentRow++;
		}
		CurrentRow+=2;
		while(IsTableNow)
		{
			unsigned int CurrentColumn;
			double *Energy_p=Get(1,CurrentRow);
			double *NPoints_p=Get(5,CurrentRow);
			if(!Energy_p||!NPoints_p)
			{
				break;
			}
			ENDFAngularDistribution ADist;
			ADist.Type=2;
			ADist.Energy=*Energy_p;
			CurrentRow+=2;
			unsigned int NextRow=0;
			GetSequence2(ADist.XValues,ADist.YValues,0,CurrentRow,*NPoints_p,&CurrentColumn,&NextRow);
			ADist.fTable=this;
			CurrentRow=NextRow;
			ADist4.push_back(ADist);
			CurrentRow++;
		}
	}
}

void ENDFTable::GenerateAngularDistributions14()
{
	if((MF!=14)||(Table.size()<6))
	{
		return;
	}
	unsigned int CurrentRow=0;
	while(CurrentRow<Table[0].size())
	{
		double* EnergyGamma_p=Get(0,CurrentRow);
		double* LI_p=Get(1,CurrentRow);
		unsigned int CurrentColumn=0;
		if(EnergyGamma_p&&LI_p)
		{
			double GammaEnergy=*EnergyGamma_p;
			unsigned int NumberOfEntries=*Get(5,CurrentRow);
			for(unsigned int i=0;i<NumberOfEntries;i++)
			{
				if(i==0)
				{
					CurrentRow+=2;
				}
				double *Energy_p=Get(1,CurrentRow);
				double *NL_p=Get(4,CurrentRow);
				if(!Energy_p||!NL_p)
				{
					break;
				}
				ENDFAngularDistribution ADist;
				ADist.Type=1;
				unsigned int NL=*NL_p;
				ADist.Energy=*Energy_p;
				ADist.SecondaryEnergy=GammaEnergy;
				//cout<<"Eg:"<<GammaEnergy<<" En:"<<ADist.Energy/1e6<<" NL:"<<NL<<" ADist14.size:"<<ADist14.size()<<"\n";
				ADist.LegendreCoefficients=GetSequence(0,CurrentRow+1,NL,&CurrentColumn,&CurrentRow);
				/*for(unsigned int i=0;i<ADist.LegendreCoefficients.size();i++)
				{
					cout<<" CurrentRow: "<<ADist.LegendreCoefficients[i]<<"\n";
				}
				CurrentRow++;*/
				ADist.fTable=this;
				ADist14.push_back(ADist);
			}
			/*if(NumberOfEntries==0)
			{
				ENDFAngularDistribution ADist;
				ADist.Type=1;
				ADist.Energy=0;
				ADist.SecondaryEnergy=GammaEnergy;
				ADist.fTable=this;
				cout<<"Eg:"<<GammaEnergy<<" ADist14.size:"<<ADist14.size()<<"\n";
				ADist14.push_back(ADist);
			}*/
		}
		else
		{
			break;
		}
		CurrentRow++;
	}
}

TGraph* ENDFTable::GetTGraph()
{
	if(MF==3)
	{
		if(TableGraph.GetN()==0)
		{
			vector<double> x,y;
			x=GetX();
			y=GetY();
			for(unsigned int i=0;i<x.size();i++)
			{
				x[i]=x[i]/1e6;//в МэВ
				y[i]=y[i]*1e3;//в мб
			}
			TableGraph=TGraph(x.size(),&x[0],&y[0]);
			ENDFDictonary* ed=ENDFDictonary::Instance();
			TableGraph.SetTitle((ed->GetEntryByMT(MT)->Reaction+" "+ed->GetMFDescription(MF)).c_str());
		}
	}
	return &TableGraph;
}
string ENDFTable::GetRawTable()
{
	string result="Header\n";
	if(Header.Table.size()<6)
	{
		result+="Header is invalid\n";
	}
	else
	{
		for(unsigned int i=0;i<Header.Table[0].size();i++)
		{
			for(unsigned int j=0;j<Header.Table.size();j++)
			{
				result+=to_string(Header.Table[j][i])+"\t";
			}
			result+="\n";
		}
	}
	
	result+="Table:\n";
	if(Table.size()<6)
	{
		result+="Table is invalid\n";
	}
	else
	{
		for(unsigned int i=0;i<Table[0].size();i++)
		{
			for(unsigned int j=0;j<Table.size();j++)
			{
				result+=to_string(Table[j][i])+"\t";
			}
			result+="\n";
		}
	}
	return result;
}

ENDFTable* ENDFFile::GetENDFTable(int MF,int MT)
{
	if(LastENDFTable)
	{
		if((LastENDFTable->MF==MF)&&(LastENDFTable->MT==MT))
		{
			LastENDFTable->fFile=this;
			return LastENDFTable;
		}
	}
	int ID=MF*1000+MT;//генерируем новую таблицу
	ENDFTables[ID];
	LastENDFTable=&ENDFTables[ID];
	LastENDFTable->MF=MF;
	LastENDFTable->MT=MT;
	LastENDFTable->fFile=this;
	return LastENDFTable;
}

ENDFTable* ENDFFile::FindENDFTable(int MF,int MT)
{
	if(MT<-5)//ошибочный MT
	{
		return 0;
	}
	if(LastENDFTable)
	{
		if((LastENDFTable->MF==MF)&&(LastENDFTable->MT==MT))
		{
			return LastENDFTable;
		}
	}
	map<int,ENDFTable>::iterator it;
	it=ENDFTables.find(MF*1000+MT);
	if (it != ENDFTables.end())
	{
		return &(it->second);
	}
	return 0;
}

void ENDFFile::ReadRaw(string filename)
{
	if(filename.find(".zip")!=string::npos)
	{
		int err = 0;
		zip *z = zip_open(filename.c_str(), 0, &err);	
		TString InpFileName(filename.substr(filename.find_last_of("/\\") + 1).c_str());
		InpFileName.ReplaceAll(".zip",".dat");
		zip_file *f = zip_fopen(z,InpFileName.Data(), 0);
		string line;
		while(GetNextString(z,f,line))
		{
			RawOutput+=line+"\n";
		}
	}
	else
	{
		ifstream ifs(filename);
		string line;
		while(getline(ifs,line))
		{
			RawOutput+=line+"\n";
		}
	}
}

bool ENDFFile::Read(string filename)
{
	if(WasRead)
	{
		return true;
	}
	ReadRaw(filename);
	/*int err = 0;
	Filename=filename;
	zip *z = zip_open(filename.c_str(), 0, &err);	
	TString InpFileName(filename.substr(filename.find_last_of("/\\") + 1).c_str());
	InpFileName.ReplaceAll(".zip",".dat");
	// cout<<"Filename:"<<filename<<"\n";
	zip_file *f = zip_fopen(z,InpFileName.Data(), 0);*/
	string line;
	bool ContentsFlag=false;
	stringstream sstr(RawOutput);
	while(getline(sstr,line))
	{
		int MAT=0,MT=0,MF=0, NSTR=0;
		GetMAT_MF_MT_NSTR(line,MAT,MF,MT,NSTR);
		//cout<<"line:"<<line<<"\n";
		//cout<<MAT<<" "<<MT<<" "<<MF<<" "<<NSTR<<"\n";
		if(MT==451)//описание файла и содержание
		{
			ENDFTable* table=GetENDFTable(MF,MT);
			table->GetFromString(line,&MF,&MT);
			WasRead=true;
			if(line.find("************************ C O N T E N T S ***********************")!=string::npos)
			{
				ContentsFlag=true;
			}
			if(ContentsFlag)
			{
				if((NSTR==99999)||(MT==0))
				{
					ContentsFlag=false;
				}
				else
				{
					//cout<<line<<"\n";
					Content.GetFromString(line);
				}
			}
			else
			{
				Description.AddFromString(line);
			}
		}
		else if((NSTR!=99999)||(MT!=0))//не конец блока
		{
			ENDFTable* table=GetENDFTable(MF,MT);
			table->GetFromString(line,&MF,&MT);
			/*if(MF==3&&MT==1&&table->GetColumn(0).size()>1)
			{
				return;
			}*/
		}
		
	}
	if(RawOutput.size()>0)
	{
		if(Projectile=="")
		{
			ENDFTable *t=GetENDFTable(1,451);//берем самую первую таблицу в файле (описание-ENDF-6 format manual, стр 4, стр 40)
			if(t)
			{
				vector<double> Row=t->Header.GetRow(2);//берем третью строку
				vector<double> Row0=t->Header.GetRow(0);//берем первую строку
				
				if(Row0.size()>1)
				{
					int ZA=Row0[0];
					Z=ZA/1000;
					A=ZA%1000;
				}
				
				if(Row.size()>4)
				{
					int NSUB=Row[4];
					int IPART=NSUB/10;
					int ZProjectile=IPART/1000;
					int AProjectile=IPART%1000;
					if(NSUB<=3)
					{
						Projectile="g";
					}
					else if((AProjectile==1)&&(ZProjectile==0))
					{
						Projectile="n";
					}
					else if(ZProjectile==1)
					{
						if(AProjectile==1)
						Projectile="p";
						if(AProjectile==2)
						Projectile="d";
						if(AProjectile==3)
						Projectile="t";
					}
					else if((AProjectile==2)&&(ZProjectile==4))
					{
						Projectile="a";
					}
					else
					{
						Projectile=to_string(AProjectile)+GetNucleusName(Z);
					}
				}
				
			}
		}
		return true;
	}
	return false;
}
vector<ENDFAngularDistribution*> ENDFFile::GetGammaAngularDistributions(double GammaEnergy,double Thr)
{
	vector<ENDFAngularDistribution*> result;
	GammaEnergy=GammaEnergy*1e3;
	Thr=Thr*1e3;
	//угловые распределения гамма имеют MF 14
	vector<ENDFTable*> PointersToTables;//сюда складываются указатели на таблицы с подходящим MF, т.е. 4-107
	for(int i=4;i<108;i++)
	{
		ENDFTable* t=FindENDFTable(14,i);
		if(t)
		{
			//cout<<"before GenerateAngularDistributions14 "<<i<<"\n";
			t->GenerateAngularDistributions14();
			//cout<<"after GenerateAngularDistributions14\n";
			for(unsigned int j=0;j<t->ADist14.size();j++)
			{
				if(abs(t->ADist14[j].SecondaryEnergy-GammaEnergy)<Thr)
				{
					//cout<<"ADist14:"<<t->ADist14[j].SecondaryEnergy<<" "<<GammaEnergy<<" "<<abs(t->ADist14[j].SecondaryEnergy-GammaEnergy)/1e3<<"\n";
					result.push_back(&(t->ADist14[j]));
				}
			}
		}
	}
	return result;
}
vector<ENDFAngularDistribution*> ENDFFile::GetNeutronAngularDistributions(int LevelNum)
{
	vector<ENDFAngularDistribution*> result;
	if(LevelNum==0)
	{
		ENDFTable* t=FindENDFTable(4,2);
		if(t)
		{
			t->GenerateAngularDistributions4();
			for(unsigned int i=0;i<t->ADist4.size();i++)
			{
				result.push_back(&(t->ADist4[i]));
			}
		}
	}
	else if(LevelNum>0&&LevelNum<41)
	{
		ENDFTable* t=FindENDFTable(4,50+LevelNum);
		if(t)
		{
			t->GenerateAngularDistributions4();
			for(unsigned int i=0;i<t->ADist4.size();i++)
			{
				result.push_back(&(t->ADist4[i]));
			}
		}
	}
	return result;
}

int GetAdditionIndex(string Projectile,string OutgoingParticle,int LevelNum)
{
	if(LevelNum<-5)
	{
		return -1;//если ошибка в mt
	}
	if(LevelNum==-1)//Total
	{
		return 1;
	}
	if(LevelNum==-2)//Nonelastic
	{
		return 3;
	}
	if(LevelNum==-3)//Inelastic
	{
		if(OutgoingParticle=="n")
		{
			return 4;
		}
		if(OutgoingParticle=="p")
		{
			return 103;
		}
		if(OutgoingParticle=="d")
		{
			return 104;
		}
		if(OutgoingParticle=="t")
		{
			return 105;
		}
		if(OutgoingParticle=="3He")
		{
			return 106;
		}
		if(OutgoingParticle=="a")
		{
			return 107;
		}
	}
	if(Projectile==OutgoingParticle)
	{
		if(LevelNum==0)
		{
			return 2;
		}
	}
	if(OutgoingParticle=="n")
	{
		return 50+LevelNum;
	}
	else if(OutgoingParticle=="p")
	{
		return 600+LevelNum;
	}
	else if(OutgoingParticle=="d")
	{
		return 650+LevelNum;
	}
	else if(OutgoingParticle=="t")
	{
		return 700+LevelNum;
	}
	else if(OutgoingParticle=="3He")
	{
		return 750+LevelNum;
	}
	else if(OutgoingParticle=="a")
	{
		return 800+LevelNum;
	}
	return 0;
}

vector<ENDFAngularDistribution*> ENDFFile::GetAngularDistributions(string OutgoingParticle,int LevelNum)
{
	vector<ENDFAngularDistribution*> result;
	int Addition=GetAdditionIndex(Projectile,OutgoingParticle,LevelNum);
	
	ENDFTable* t=FindENDFTable(4,Addition);
	if(t)
	{
		t->GenerateAngularDistributions4();
		for(unsigned int i=0;i<t->ADist4.size();i++)
		{
			result.push_back(&(t->ADist4[i]));
		}
	}
	return result;
}

TGraph2D ENDFFile::GetTGraph2DGammaAngularDistributions(double GammaEnergy,double Thr,string _Type,int NPoints)
{
	TGraph2D result;
	vector<ENDFAngularDistribution*> ADistVector=GetGammaAngularDistributions(GammaEnergy,Thr);
	for(unsigned int i=0;i<ADistVector.size();i++)
	{
		TGraph *gr=ADistVector[i]->GetAngularDistribution(_Type,NPoints);
		for(int j=0;j<gr->GetN();j++)
		{
			double x=0,y=0,z=0;
			x=ADistVector[i]->Energy;
			gr->GetPoint(j,y,z);
			result.SetPoint(result.GetN(),x,y,z);
		}
	}
	return result;
}

TGraph2D ENDFFile::GetTGraph2DNeutronAngularDistributions(int LevelNum,string _Type,int NPoints)
{
	TGraph2D result;
	vector<ENDFAngularDistribution*> ADistVector=GetNeutronAngularDistributions(LevelNum);
	for(unsigned int i=0;i<ADistVector.size();i++)
	{
		//cout<<"Energy:"<<ADistVector[i]->Energy<<"\n";
		TGraph *gr=ADistVector[i]->GetAngularDistribution(_Type,NPoints);
		for(int j=0;j<gr->GetN();j++)
		{
			double x=0,y=0,z=0;
			x=ADistVector[i]->Energy/1e6;
			gr->GetPoint(j,y,z);
			result.SetPoint(result.GetN(),x,y,z);
		}
	}
	return result;
}

EvaluatedDataGraph ENDFFile::GetGammaAngularDistribution(double GammaEnergy,double NeutronEnergy,double Thr,string _Type,int NPoints)
{
	TGraph2D Gr2D=GetTGraph2DGammaAngularDistributions(GammaEnergy,Thr,_Type,NPoints);
	EvaluatedDataGraph result;
	if(Gr2D.GetN()==0)
	{
		return result;
	}
	vector<double> X;
	NeutronEnergy=NeutronEnergy*1e6;
	if(_Type=="Deg")
	{
		double Step=180.0/NPoints;
		double Deg=0;
		while(Deg<180)
		{
			X.push_back(Deg);
			Deg+=Step;
		}
	}
	else if(_Type=="Cos")
	{
		double Step=2/NPoints;
		double Cos=-1;
		while(Cos<1)
		{
			X.push_back(Cos);
			Cos+=Step;
		}
	}
	result.SetName(TString::Format("ADist_Gamma_En_%.1f_Eg_%.1f",NeutronEnergy/1e6,GammaEnergy));
	result.SetTitle(TString::Format("#gamma angular distribution %s (En=%.1fMeV, Eg=%.1fkeV);%s;W",Source.c_str(), NeutronEnergy/1e6,GammaEnergy,_Type.c_str()));
	for(unsigned int i=0;i<X.size();i++)
	{
		//cout<<"Interp:"<<X[i]<<" "<<Gr2D.Interpolate(NeutronEnergy,X[i])<<"\n";
		if(Gr2D.Interpolate(NeutronEnergy,X[i])!=0)
		result.SetPoint(result.GetN(),X[i],Gr2D.Interpolate(NeutronEnergy,X[i]));
	}
	result.fFile=this;
	return result;
}

EvaluatedDataGraph ENDFFile::GetNeutronCrossSections(int LevelNum)
{
	EvaluatedDataGraph result;
	result.LevelNum=LevelNum;
	ENDFTable *CSTable=0;
	if(LevelNum==-1)//Total
	{
		CSTable=FindENDFTable(3,1);
		if(CSTable)
		{
			result=*((EvaluatedDataGraph*)CSTable->GetTGraph());
		}
	}
	if(LevelNum==-2)//Nonelastic
	{
		CSTable=FindENDFTable(3,3);
		if(CSTable)
		{
			result=*((EvaluatedDataGraph*)CSTable->GetTGraph());
		}
	}
	if(LevelNum==0)
	{
		CSTable=FindENDFTable(3,2);
		if(CSTable)
		{
			result=*((EvaluatedDataGraph*)CSTable->GetTGraph());
		}
	}
	if(LevelNum>0)
	{
		CSTable=FindENDFTable(3,50+LevelNum);
		if(CSTable)
		{
			result=*((EvaluatedDataGraph*)CSTable->GetTGraph());
		}
	}
	result.fFile=this;
	return result;
}

EvaluatedDataGraph ENDFFile::GetNeutronAngularDistribution(int LevelNum,double NeutronEnergy,string _Type,int NPoints)
{
	TGraph2D Gr2D=GetTGraph2DNeutronAngularDistributions(LevelNum,_Type,NPoints);
	EvaluatedDataGraph result;
	result.LevelNum=LevelNum;
	if(Gr2D.GetN()==0)
	{
		return result;
	}
	ENDFTable *CSTable=0;
	double Norm=1;
	if(LevelNum==0)
	{
		CSTable=FindENDFTable(3,2);
	}
	else
	{
		CSTable=FindENDFTable(3,50+LevelNum);
	}
	if(CSTable)
	{
		TGraph* ReferenceCS=CSTable->GetTGraph();
		Norm=ReferenceCS->Eval(NeutronEnergy)/(4*3.1416);
	}
	vector<double> X;
	if(_Type=="Deg")
	{
		double Step=180.0/NPoints;
		double Deg=0;
		while(Deg<180)
		{
			X.push_back(Deg);
			Deg+=Step;
		}
	}
	else if(_Type=="Cos")
	{
		double Step=2/NPoints;
		double Cos=-1;
		while(Cos<1)
		{
			X.push_back(Cos);
			Cos+=Step;
		}
	}
	result.SetName(TString::Format("ADist_Neutron_En_%.1f_Lev_%d",NeutronEnergy,LevelNum));
	result.SetTitle(TString::Format("n angular distribution %s (En=%.1fMeV, Level=%d);%s;#frac{d#sigma}{d#Omega}, mb",Source.c_str(),NeutronEnergy,LevelNum,_Type.c_str()));
	for(unsigned int i=0;i<X.size();i++)
	{
		//cout<<"Interp:"<<X[i]<<" "<<Norm<<" "<<Gr2D.Interpolate(NeutronEnergy,X[i])<<" "<<NeutronEnergy<<"\n";
		if(Gr2D.Interpolate(NeutronEnergy,X[i])>0)
		result.SetPoint(result.GetN(),X[i],Norm*Gr2D.Interpolate(NeutronEnergy,X[i]));
	}
	result.fFile=this;
	return result;
}

TGraph2D ENDFFile::GetTGraph2DAngularDistributions(string OutgoingParticle,int LevelNum,string _Type,int NPoints)
{
	TGraph2D result;
	vector<ENDFAngularDistribution*> ADistVector=GetAngularDistributions(OutgoingParticle,LevelNum);
	for(unsigned int i=0;i<ADistVector.size();i++)
	{
		//cout<<"Energy:"<<ADistVector[i]->Energy<<"\n";
		TGraph *gr=ADistVector[i]->GetAngularDistribution(_Type,NPoints);
		for(int j=0;j<gr->GetN();j++)
		{
			double x=0,y=0,z=0;
			x=ADistVector[i]->Energy/1e6;
			gr->GetPoint(j,y,z);
			result.SetPoint(result.GetN(),x,y,z);
		}
	}
	return result;
}
EvaluatedDataGraph ENDFFile::GetAngularDistribution(string OutgoingParticle,int LevelNum,double NeutronEnergy,string _Type,int NPoints)
{
	TGraph2D Gr2D=GetTGraph2DAngularDistributions(OutgoingParticle,LevelNum,_Type,NPoints);
	EvaluatedDataGraph result;
	if(Gr2D.GetN()==0)
	{
		return result;
	}
	double Norm=1;
	TGraph ReferenceCS=GetCrossSections(OutgoingParticle,LevelNum);
	if(ReferenceCS.GetN()>0)
	{
		Norm=ReferenceCS.Eval(NeutronEnergy)/(4*3.1416);
	}
	vector<double> X;
	if(_Type=="Deg")
	{
		double Step=180.0/NPoints;
		double Deg=0;
		while(Deg<180)
		{
			X.push_back(Deg);
			Deg+=Step;
		}
	}
	else if(_Type=="Cos")
	{
		double Step=2/NPoints;
		double Cos=-1;
		while(Cos<1)
		{
			X.push_back(Cos);
			Cos+=Step;
		}
	}
	result.SetName(TString::Format("ADist_E_%.1f_Lev_%d",NeutronEnergy,LevelNum));
	result.SetTitle(TString::Format("%s %s angular distribution (En=%.1fMeV, Level=%d);%s;#frac{d#sigma}{d#Omega}, mb",Source.c_str(),OutgoingParticle.c_str(),NeutronEnergy,LevelNum,_Type.c_str()));
	for(unsigned int i=0;i<X.size();i++)
	{
		//cout<<"Interp:"<<X[i]<<" "<<Norm<<" "<<Gr2D.Interpolate(NeutronEnergy,X[i])<<" "<<NeutronEnergy<<"\n";
		if(Gr2D.Interpolate(NeutronEnergy,X[i])>0)
		result.SetPoint(result.GetN(),X[i],Norm*Gr2D.Interpolate(NeutronEnergy,X[i]));
	}
	result.fFile=this;
	result.Source=Source;
	result.A=A;
	return result;
}
EvaluatedDataGraph ENDFFile::GetCrossSections(string OutgoingParticle,int LevelNum)
{
	EvaluatedDataGraph result;
	result.LevelNum=LevelNum;
	ENDFTable *CSTable=0;
	if(LevelNum==-1)//Total
	{
		CSTable=FindENDFTable(3,1);
		if(CSTable)
		{
			result=*((EvaluatedDataGraph*)CSTable->GetTGraph());
		}
	}
	if(LevelNum==-2)//Nonelastic
	{
		CSTable=FindENDFTable(3,3);
		if(CSTable)
		{
			result=*((EvaluatedDataGraph*)CSTable->GetTGraph());
		}
	}
	if(LevelNum>=0)
	{
		CSTable=FindENDFTable(3,GetAdditionIndex(Projectile,OutgoingParticle,LevelNum));
		if(CSTable)
		{
			result=*((EvaluatedDataGraph*)CSTable->GetTGraph());
		}
	}
	result.SetName(TString::Format("CS_Lev_%d",LevelNum));
	result.SetTitle(TString::Format("%s %s cross section (Level=%d);#sigma, mb",Source.c_str(),OutgoingParticle.c_str(),LevelNum));
	result.fFile=this;
	result.Source=Source;
	result.A=A;
	return result;
}

string GetLoadedFileName(string Projectile,string Nuclide)
{
	string PathToLinkDB=getenv("TALYSLIBDIR");
	PathToLinkDB+="/ENDFReader/ENDFFlieLists/"+Projectile+".txt";
	int A,Z;
	GetAZ(Nuclide,Z,A);
	string Mask=string(TString::Format("%d-%s-%d.zip",Z,GetNucleusName(Z).c_str(),A).Data());
	ifstream ifs(PathToLinkDB);
	string line;
	string OutputFileName="/dev/shm/";
	while(getline(ifs,line))
	{
		if(line.find(Mask)!=string::npos)
		{
			OutputFileName+=line.substr(line.find_last_of("/\\") + 1);
			return OutputFileName;
		}
	}
	return "";
}

string ENDFFile::GetBaseNameInTable(string Name)
{
	if(!ENDFBASE)
	{
		string PathToLinkDB=getenv("TALYSLIBDIR");
		PathToLinkDB+="/ENDFReader/ENDFFlieLists/ENDFBASE.db";
		sqlite3_open((PathToLinkDB).c_str(), &ENDFBASE); 
	}
	sqlite3_stmt *stmt;
	
	sqlite3_prepare_v2(ENDFBASE,("SELECT InThisBase from TablesList WHERE BaseName == \""+Name+"\"").c_str(), -1, &stmt, NULL);
	string BaseName;
	sqlite3_step(stmt);
	const unsigned char* requestRes=sqlite3_column_text(stmt, 0);
	if(requestRes)
	{
		return string(reinterpret_cast<const char*>(requestRes));
	}
	return "";
}

string GetBaseNameInTable(string Name)
{
	sqlite3* ENDFBASE;
	string PathToLinkDB=getenv("TALYSLIBDIR");
	PathToLinkDB+="/ENDFReader/ENDFFlieLists/ENDFBASE.db";
	sqlite3_open((PathToLinkDB).c_str(), &ENDFBASE); 
	
	sqlite3_stmt *stmt;
	
	sqlite3_prepare_v2(ENDFBASE,("SELECT InThisBase from TablesList WHERE BaseName == \""+Name+"\"").c_str(), -1, &stmt, NULL);
	string BaseName;
	sqlite3_step(stmt);
	const unsigned char* requestRes=sqlite3_column_text(stmt, 0);
	if(requestRes)
	{
		 sqlite3_close_v2(ENDFBASE);
		return string(reinterpret_cast<const char*>(requestRes));
	}
	sqlite3_close_v2(ENDFBASE);
	return "";
}

string ENDFFile::GetENDFFileName(string Projectile,string Nuclide,string _Source)
{
	string BaseName=GetBaseNameInTable(_Source);
	sqlite3_stmt *stmt;
	if(BaseName.size()==0)
	{
		cout<<"This is ENDFFile::GetENDFFileName(string Projectile,string Nuclide,string _Source): cannot find database with name "<<_Source<<". Empty string returned\n";
		return "";
	}
	//теперь ищем в таблице нужный файл
	int A,Z;
	GetAZ(Nuclide,Z,A);
	sqlite3_prepare_v2(ENDFBASE, ("SELECT Filename from "+BaseName+" WHERE Projectile == \""+Projectile+"\" AND Z =="+to_string(Z)+" AND A == "+to_string(A)).c_str(), -1, &stmt, NULL);
	sqlite3_step(stmt);
	const unsigned char* requestRes=sqlite3_column_text(stmt, 0);
	if(requestRes)
	{
		return string(reinterpret_cast<const char*>(requestRes));
	}
	sqlite3_finalize(stmt);
	return "";
}

bool ENDFFile::DownloadFromOnlineENDF(string Projectile,string Nuclide,string _Source)
{
	string FName=GetENDFFileName(Projectile,Nuclide,_Source);
	string Link;
	if(FName.size()==0)
	{
		cout<<"This is ENDFFile::DownloadFromOnlineENDF(string Projectile,string Nuclide,string _Source): File not found\n";
		return false;
	}
	Link="http://159.93.100.133:85/"+FName;
	string OutputFileName="/dev/shm/";
	OutputFileName+=FName.substr(FName.find_last_of("/\\") + 1);
	Filename=OutputFileName;
	LoadedFileName=OutputFileName;
	system(("wget --user-agent=\"Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/51.0.2704.103 Safari/537.36\" -O "+OutputFileName+" "+Link).c_str());
	return true;
}

bool DownloadFromOnlineENDF(string FName)
{
	
}

bool ENDFFile::Read(string _Projectile,string Nuclide)
{
	if(WasRead)
	{
		return true;
	}
	GetAZ(Nuclide,Z,A);
	Projectile=_Projectile;
	string PathToENDF;
	if(getenv("ENDFDIR"))
	{
		PathToENDF=getenv("ENDFDIR");
	}
	int A,Z;
	GetAZ(Nuclide,Z,A);
	string Addition=string(TString::Format("%d-%s-%d.zip",Z,GetNucleusName(Z).c_str(),A).Data());
	if(PathToENDF.size()==0)
	{
		cout<<"This is ENDFFile::Read(string Projectile,string Nuclide): enviroment variable \"ENDFDIR\" does not set. The nessesary file will be downloaded\n";
		if(DownloadFromOnlineENDF(Projectile,Nuclide,Source))
		{
			if(Read(LoadedFileName))
			{
				IsLoaded=true;
				return true;
			}
			
		}
		//return;
	}
	PathToENDF+=GetENDFFileName(Projectile,Nuclide,Source);
	return Read(PathToENDF);
}

void ENDFFile::SetName(string _Name)
{
	Name=_Name;
}
const char *ENDFFile::GetName() const
{
	return Name.c_str();
}
void ENDFFile::GenerateName()
{
	TString BaseName(Source.c_str());
	BaseName.ReplaceAll("-","_");
	BaseName.ReplaceAll(".","_");
	BaseName+=TString::Format("_%d_%d",Z,A);
	Name=Projectile+"_"+BaseName.Data();
}
ENDFFile::~ENDFFile()
{
	if(IsLoaded)
	{
		system(("rm "+LoadedFileName).c_str());
	}
}
vector<string> ENDFFile::GetListOfBases(string Projectile,int Z, int A)
{
	vector<string> Bases;
	vector<string> BaseNames;
	vector<string> result;
	sqlite3* BASE=0;//!
	string PathToLinkDB=getenv("TALYSLIBDIR");
	PathToLinkDB+="/ENDFReader/ENDFFlieLists/ENDFBASE.db";
	sqlite3_open((PathToLinkDB).c_str(), &BASE); 
	sqlite3_stmt *stmt;
	
	sqlite3_prepare_v2(BASE,"SELECT * from TablesList", -1, &stmt, NULL);
	while(SQLITE_ROW==sqlite3_step(stmt))
	{
		const unsigned char* requestRes=sqlite3_column_text(stmt, 0);
		Bases.push_back(reinterpret_cast<const char*>(requestRes));
		requestRes=sqlite3_column_text(stmt, 1);
		BaseNames.push_back(reinterpret_cast<const char*>(requestRes));
	}
	sqlite3_finalize(stmt);
	
	for(unsigned int i=0;i<Bases.size();i++)
	{
		sqlite3_prepare_v2(BASE,("SELECT * from "+BaseNames[i]+" WHERE Projectile == \""+Projectile+"\" AND Z=="+to_string(Z)+" AND A=="+to_string(A)+";").c_str(), -1, &stmt, NULL);
		sqlite3_step(stmt);
		const unsigned char* requestRes=sqlite3_column_text(stmt, 0);
		if(requestRes)
		{
			result.push_back(Bases[i]);
		}
	}
	sqlite3_finalize(stmt);
	return result;
}


vector<vector<TH2F> > ENDFAnalyser::GetNZDistributionForTables(string Projectile,vector<int> MT, vector<int> MF,string _Source,int Zinit,int Zfin,int Ninit, int Nfin)
{
	_Source=GetBaseNameInTable(_Source);
	if(_Source.size()==0)
	{
		cout<<"This is ENDFAnalyser::GetNZDistributionForTables: cannot find base!\n";
	}
	vector<vector<TH2F> > result;
	result.resize(MT.size());
	for(int i=0;i<(int)MT.size();i++)
	{
		for(int j=0;j<(int)MF.size();j++)
		{
			result[i].emplace_back(TString::Format("%s_%d_%d",Projectile.c_str(),MT[i],MF[j]),TString::Format("NZ diag for data %s_%d_%d",Projectile.c_str(),MT[i],MF[j]),Nfin-Ninit+1,Ninit,Nfin,Zfin-Zinit+1,Zinit,Zfin);
			cout<<"Zfin-Zinit+1 "<<Zfin-Zinit+1<<" "<<Zinit<<" "<<Zfin<<"\n";;
		}
	}
	SQLLib sql;
	string PathToLinkDB=getenv("TALYSLIBDIR");
	PathToLinkDB+="/ENDFReader/ENDFFlieLists/ENDFBASE.db";
	if(!sql.Open(PathToLinkDB))
	{
		cout<<"This is ENDFAnalyser::GetNZDistributionForTables(): cannot open db!\n";
		return result;
	}
	for(int k=Zinit;k<=Zfin;k++)
	{
		if(sql.Request("SELECT * from "+_Source+" WHERE Projectile == \""+Projectile+"\" AND Z=="+to_string(k)+";"))
		{
			vector<string> AStr=sql.GetColumn(2);
			for(unsigned int p=0;p<AStr.size();p++)
			{
				cout<<"AStr[p]:"<<AStr[p]<<"\n";
				if(stoi(AStr[p])>0)
				{
					ENDFFile f;
					string NuclName=AStr[p]+GetNucleusName(k);
					cout<<"NuclName:"<<NuclName<<"\n";
					f.Read(Projectile,NuclName);
					for(unsigned int i=0;i<MT.size();i++)
					{
						for(unsigned int j=0;j<MF.size();j++)
						{
							if(f.FindENDFTable(MF[j],MT[i]))
							{
								result[i][j].Fill(stoi(AStr[p])-k,k);
							}
						}
					}
				}
			}
			
		}
	}
	return result;
}

bool SQLLib::Open(string _Filename)
{
	Filename=_Filename;
	if(!Opened)
	{
		sqlite3_close(Base);
	}
	if (sqlite3_open(Filename.c_str(), &Base) != SQLITE_OK) 
	{
		cout << "This is SQLLib::Open: Could not open database:"<<Filename<<"\n";
		Opened=false;
		return false;
	}
	Opened=true;
	return true;
	
}
string SQLLib::GetElement(int column,int row)
{
	if(column<(int)Table.size())
	{
		if(row<(int)Table[column].size())
		{
			return Table[column][row];
		}
		else
		{
			cout<<"This is SQLLib:: GetElement("<<column<<","<<row<<"): index row is out of range. Actual size of Table["<<column<<"] is "<<Table[column].size()<<"\n";
			return "";
		}
	}
	else
	{
		cout<<"This is SQLLib:: GetElement("<<column<<","<<row<<"): index column is out of range. Actual size of Table is "<<Table.size()<<"\n";
		return "";
	}
	return "";
}

int select_callback(void *p_data, int num_fields, char **p_fields, char **p_col_names)
{
	vector<vector<string> >* records = static_cast<vector<vector<string> >* >(p_data);
	try 
	{
		records->emplace_back(p_fields, p_fields + num_fields);
	}
	catch (...) 
	{
		// abort select on failure, don't let exception propogate thru sqlite3 call-stack
		return 1;
	}
	return 0;
}

vector<vector<string> > select_stmt(sqlite3* db,const char* stmt, int &status)
{
	vector<vector<string> > records;  
	char *errmsg;
	int ret = sqlite3_exec(db, stmt, select_callback, &records, &errmsg);
	if (ret != SQLITE_OK)
	{
		std::cerr << "Error in select statement " << stmt << "[" << errmsg << "]\n";
		status=0;
	}
	status=1;
	return records;
}

bool SQLLib::Request(string Request)
{
	int Status=0;
	Table=select_stmt(Base,Request.c_str(),Status);
	if(Status==1)
	{
		return true;
	}
	return false;
}
vector<string> SQLLib::GetRow(int row)
{
	vector<string> result;
	if(row<(int)Table.size())
	{
		for(unsigned int i=0;i<Table[row].size();i++)
		{
			result.push_back(Table[row][i]);
		}
	}
	else
	{
		cout<<"This is SQLLib::GetRow("<<row<<"): column is out of range\n";
	}
	return result;
}
vector<string> SQLLib::GetColumn(int column)
{
	vector<string> result;
	for(unsigned int i=0;i<Table.size();i++)
	{
		if(column<(int)Table[i].size())
		{
			result.push_back(Table[i][column]);
		}
	}
	return result;
}
