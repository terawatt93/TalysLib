#pragma once
#include "Parser.hh"
#include <stdio.h>
#include <vector>
#include <cstring>
#include <sstream>
#include <iostream>
#include <fstream>
#include <cmath>
#include <TString.h>
#include "Constants.cpp"
#include <stdarg.h> 
#include <cstdlib>
#include <dirent.h>
#include <TPad.h>
#include <TGraph.h>
#include <TGraph2D.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TKey.h>
#include <sys/stat.h>
#include <iomanip>

#define AngularMomentumSize 7
using namespace std;
const int Z_number[]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118};
const string Atomic_symbols[]={"H","He","Li","Be","B","C","N","O","F","Ne","Na","Mg","Al","Si","P","S","Cl","Ar","K","Ca","Sc","Ti","V","Cr","Mn","Fe","Co","Ni","Cu","Zn","Ga","Ge","As","Se","Br","Kr","Rb","Sr","Y","Zr","Nb","Mo","Tc","Ru","Rh","Pd","Ag","Cd","In","Sn","Sb","Te","I","Xe","Cs","Ba","La","Ce","Pr","Nd","Pm","Sm","Eu","Gd","Tb","Dy","Ho","Er","Tm","Yb","Lu","Hf","Ta","W","Re","Os","Ir","Pt","Au","Hg","Tl","Pb","Bi","Po","At","Rn","Fr","Ra","Ac","Th","Pa","U","Np","Pu","Am","Cm","Bk","Cf","Es","Fm","Md","No","Lr","Rf","Db","Sg","Bh","Hs","Mt","Ds","Rg","Cn","Nh","Fl","Mc","Lv","Ts","Og"};

const char AngularMomentum[]={'s','p','d','f','g','h','i'};

class kGrPoint_s//вспомогательный класс, позволяющий хранить точки графика совместно с указателем на график
{
	public:
	double x=0,y=0;
	TGraph *fGraph=0;
	double MinX=0, MaxX=0;
};

vector<kGrPoint_s> Get_kGrPoint_s(vector<TGraph*> &gr)
{
	vector<kGrPoint_s> result;
	for(unsigned int i=0;i<gr.size();i++)
	{
		double Min=TMath::MinElement(gr[i]->GetN(),gr[i]->GetX()),Max=TMath::MaxElement(gr[i]->GetN(),gr[i]->GetX());
		for(int j=0;j<gr[i]->GetN();j++)
		{
			double x,y;
			gr[i]->GetPoint(j,x,y);
			kGrPoint_s p;
			p.x=x; p.y=y; p.fGraph=gr[i];
			p.MinX=Min; p.MaxX=Max;
			result.push_back(p);
		}
	}
	std::sort(result.begin(), result.end(), [](kGrPoint_s a, kGrPoint_s b)
	{
		return a.x < b.x;
	});
	return result;
}

bool IsExsistedPath(const std::string& input)
{
	try 
	{
		fs::path pathObj(input);
		if (fs::exists(pathObj)) 
		{
			return true;
		}
		return false;
	}
	catch (const std::exception&) 
	{
		return false; // If path construction fails, it's likely not a valid path
	}
	return false;
}

TGraph SumTGraphs(vector<TGraph*> Graphs, vector<double> Multipliers)
{
	vector<kGrPoint_s> Points=Get_kGrPoint_s(Graphs);
	TGraph result;
	for(unsigned int i=0;i<Points.size();i++)
	{
		double y=0;
		for(unsigned int j=0;j<Graphs.size();j++)
		{
			double Min=TMath::MinElement(Graphs[j]->GetN(),Graphs[j]->GetX()),Max=TMath::MaxElement(Graphs[j]->GetN(),Graphs[j]->GetX());
			if(Points[i].x>=Min && Points[i].x<=Max)
			{
				y+=Graphs[j]->Eval(Points[i].x,0,"S")*Multipliers[j];
			}
		}
		result.SetPoint(result.GetN(),Points[i].x,y);
	}
	return result;
}

double EvalPoverForScientificNotation(double inp)//функция, возвращающая показатель для эксп. записи
{
	if(inp==0)
	{
		return 0;
	}
	return pow(10,-floor(log10(abs(inp))));
}

vector<double> RoundError(vector<double> inp)//http://genphys.phys.msu.ru/rus/ofp/CanYouRound.pdf стр 5
{
	double Val=inp[0];
	double Err=abs(inp[1]);
	double Multiplier=EvalPoverForScientificNotation(Err);
	
	Val=Val*Multiplier;
	Err=Err*Multiplier;
	
	
	string Err_str=to_string(Err);
	int PointerToLast=0;
	stringstream sstr;
	if(Err_str[0]>'2')
	{
		sstr<<round(Err)<<std::setprecision(0);
		PointerToLast=0;
	}
	else
	{
		sstr<<(round(Err*10)/10)<<std::setprecision(1);
		PointerToLast=1;
	}
	Val=round(Val*pow(10,PointerToLast))/pow(10,PointerToLast)/Multiplier;
	Err_str=sstr.str();
	double Err_rounded=atof(Err_str.c_str())/Multiplier;
	return {Val,Err_rounded};
}

inline bool IsFileExsists (const std::string& name)
{
	struct stat buffer;   
	return (stat (name.c_str(), &buffer) == 0); 
}

void CopyFileContentToBuffer(ifstream &t,string &buff)
{
	if(t.is_open())
	{
		t.seekg(0, std::ios::end);
		size_t SizeOfStr = t.tellg();
		buff=string(SizeOfStr,' ');
		t.seekg(0);
		t.read(&buff[0], SizeOfStr); 
	}
}
void CopyFileContentToBuffer(string Filename,string &buff)
{
	ifstream t(Filename);
	if(t.is_open())
	{
		t.seekg(0, std::ios::end);
		size_t SizeOfStr = t.tellg();
		buff=string(SizeOfStr,' ');
		t.seekg(0);
		t.read(&buff[0], SizeOfStr); 
	}
	t.close();
}
//void ChangeParNumeration(string &init, string &result, vector<pair<int,int> > &Combinations)
string ChangeParNumeration(string &init, int MinIndex)
{
	string result;
	vector<pair<int,int> > Combinations;
	vector<int> ParNumbers_square;//из квадратных скобок
	vector<int> ParNumbers_round;//из круглых скобок
	vector<int> ParNumbers_square_new;//из квадратных скобок
	vector<int> ParNumbers_round_new;//из круглых скобок
	//выделяем данные из строки
	bool ReadNumber=false;
	string num;
	for(unsigned int i=0;i<init.size();i++)
	{
		if(init[i]=='[')
		{
			ReadNumber=true;
			num="";
			i++;
		}
		if((init[i]==']')&&ReadNumber)
		{
			ReadNumber=false;
			ParNumbers_square.push_back(atoi(num.c_str()));
		}
		if(ReadNumber)
		{
			num+=init[i];
		}
	}
	for(unsigned int i=0;i<init.size();i++)
	{
		if((init[i]=='(')&&(i>0))
		{
			if((init[i-1]>='a' && init[i-1]<='z')||(init[i-1]>='0' && init[i-1]<='9'))
			{
				ReadNumber=true;
				num="";
				i++;
			}
		}
		if((init[i]==')')&&ReadNumber)
		{
			ReadNumber=false;
			ParNumbers_round.push_back(atoi(num.c_str()));
			num="";
		}
		if(ReadNumber)
		{
			if((init[i]>='0')&&(init[i]<='9'))
			{
				num+=init[i];
			}
			else
			{
				num="";
				ReadNumber=false;
			}
		}
	}
	std::sort(ParNumbers_square.begin(), ParNumbers_square.end());
	std::sort(ParNumbers_round.begin(), ParNumbers_round.end());
	
	if(ParNumbers_square.size()==0&&ParNumbers_round.size()==0)
	{
		return init;
	}
	int MinParIndex=2147483647;
	
	if(ParNumbers_square.size()>0)
	{
		MinParIndex=ParNumbers_square[0];
	}
	if(ParNumbers_round.size()>0)
	{
		if(MinParIndex>ParNumbers_round[0])
		{
			MinParIndex=ParNumbers_round[0];
		}
	}
	
	TString tts(init.c_str());
	
	//vector<int> ParNumbers_square_new;//из квадратных скобок
	//vector<int> ParNumbers_round_new;//из круглых скобок
	for(unsigned int i=0;i<ParNumbers_square.size();i++)
	{
		ParNumbers_square_new.push_back(ParNumbers_square[i]-MinParIndex+MinIndex);
		tts.ReplaceAll(TString::Format("[%d]",ParNumbers_square[i]),TString::Format("[%d]",ParNumbers_square[i]-MinParIndex+MinIndex));
	}
	for(unsigned int i=0;i<ParNumbers_round.size();i++)
	{
		ParNumbers_round_new.push_back(ParNumbers_round[i]-MinParIndex+MinIndex);
		tts.ReplaceAll(TString::Format("(%d)",ParNumbers_round[i]),TString::Format("(%d)",ParNumbers_round[i]-MinParIndex+MinIndex));
	}
	result=string(tts.Data());
	return result;
}
bool IsNumber(const std::string& s) 
{
	std::istringstream iss(s);
	double val;
	iss >> val;
	// Проверяем, что чтение прошло успешно и достигли конца строки
	return !iss.fail();// && iss.eof();
}
bool IsFloat(const std::string& s) 
{
	std::istringstream iss(s);
	double val;
	iss >> val;
	// Проверяем, что чтение прошло успешно и достигли конца строки
	if(!iss.fail())
	{
		if((s.find(".")!=string::npos)||(s.find("e")!=string::npos)||(s.find("E")!=string::npos))
		{
			return true;
		}
	}
	return false;
}

vector<string> GetListOfObjectNames(TFile *f)
{
	vector<string> result;
	for (TObject* keyAsObj : *f->GetListOfKeys())
	{
    	auto key = dynamic_cast<TKey*>(keyAsObj);
    	result.push_back(key->GetName());
    }
    return result;
}

vector<TPad*> GeneratePadsOnCanvas(double x1, double y1, double x2, double y2,int nx, int ny,TCanvas *c)
{
	vector<TPad*> result;
	if(!c)
	{
		if(gPad)
		{
			c=gPad->GetCanvas();
		}
		else
		{
			c=new TCanvas();
		}
	}
	double dx=(x2-x1)/nx;
	double dy=(y2-y1)/ny;
	double currx=x1, curry=y1;
	for(int i=0;i<ny;i++)
	{
		for(int j=0;j<nx;j++)
		{
			TPad *p=new TPad(TString::Format("p_%d_%d",j,i),TString::Format("p_%d_%d",j,i),currx,curry,currx+dx,curry+dy);
			p->Draw();
			result.push_back(p);
			currx+=dx;
		}
		currx=x1;
		curry+=dy;
	}
	return result;
}

void AddPointToTGraph(TGraph* gr, double x_value, double y_value)
{
	int N=gr->GetN();
	vector<double> x_values, y_values;
	x_values.resize(N); y_values.resize(N);
	for(int i=1;i<N;i++)
	{
		double x,y;
		gr->GetPoint(i,x,y);
		x_values[i]=x; y_values[i]=y;
	}
	if(N==1)
	{
		if(x_values[0]<x_value)
		{
			gr->SetPoint(1,x_value,y_value);
		}
		else
		{
			gr->SetPoint(0,x_value,y_value);
			gr->SetPoint(1,x_values[0],y_values[0]);
		}
	}
	else
	{
		bool AddPoint=false;
		for(int i=1;i<N;i++)
		{
			if((x_values[i-1]<x_value)&&(x_values[i]>=x_value))
			{
				gr->SetPoint(i,x_value,y_value);
				AddPoint=true;
			}
			if(AddPoint)
			{
				gr->SetPoint(i+1,x_values[i],y_values[i]);
			}
		}
		if(!AddPoint)
		{
			gr->SetPoint(N,x_value,y_value);
		}
	}
}

void AddPointToTGraph(TGraph2D* gr, double x_value, double y_value, double z_value)
{
	int N=gr->GetN();
	vector<double> x_values, y_values, z_values;
	x_values.resize(N); y_values.resize(N); z_values.resize(N);
	for(int i=1;i<N;i++)
	{
		double x,y,z;
		gr->GetPoint(i,x,y,z);
		x_values[i]=x; y_values[i]=y; z_values[i]=z;
	}
	if(N==1)
	{
		if(x_values[0]<x_value)
		{
			gr->SetPoint(1,x_value,y_value,z_value);
		}
		else
		{
			gr->SetPoint(0,x_value,y_value,z_value);
			gr->SetPoint(1,x_values[0],y_values[0],z_values[0]);
		}
	}
	else
	{
		bool AddPoint=false;
		for(int i=1;i<N;i++)
		{
			if((x_values[i-1]<x_value)&&(x_values[i]>=x_value)&&(y_values[i-1]<y_value)&&(y_values[i]>=y_value))
			{
				gr->SetPoint(i,x_value,y_value,z_value);
				AddPoint=true;
			}
			if(AddPoint)
			{
				gr->SetPoint(i+1,x_values[i],y_values[i],z_values[i]);
			}
		}
		if(!AddPoint)
		{
			gr->SetPoint(N,x_value,y_value,z_value);
		}
	}
}


bool IsDirectoryAlreadyExsisted(string Name)//функция проверяет, существует ли директория с данным именем. Нужна для решения конфликтов, возникающих при одновременном расчете двух ядер с однинаковым именем
{
	DIR *dir;
	dir = opendir(Name.c_str());
	if (!dir) 
	{
		return false;
	};
	return true;
}

std::vector<std::string> SplitString(const std::string &s, char delim, bool MergeDelimeters) 
{
	std::vector<std::string> result;
	std::stringstream ss (s);
	std::string item;
	while (getline (ss, item, delim)) 
	{
		if(!MergeDelimeters)
		{
			result.push_back (item);
		}
		else if (item.size()>0)
		{
			result.push_back (item);
		}
	}

	return result;
}

bool SatisfyPrimitiveRegexp(string s, string reg)
{
	vector<string> splitted_s=SplitString(s,'_');
	vector<string> splitted_r=SplitString(reg,'_');
	if(splitted_s.size()!=splitted_r.size())
	{
		return false;
	}
	int Matches=0;
	for(unsigned int i=0;i<splitted_r.size();i++)
	{
		TString sp_r(splitted_r[i].c_str());
		if(splitted_r[i].find("[")==string::npos)
		{
			if(i<splitted_s.size())
			{
				if(splitted_s[i]==splitted_r[i])
				{
					Matches++;
				}
			}
		}
		else
		{
			sp_r.ReplaceAll("[","");
			sp_r.ReplaceAll("]","");
			vector<string> sp_dash=SplitString(sp_r.Data(),'-');
			vector<string> sp_comma=SplitString(sp_r.Data(),',');
			//if(sp_dash)
			if(sp_dash.size()>1&&sp_comma.size()>1)
			{
				cout<<"This is SatisfyPrimitiveRegexp: expressions like [a,b-c] are not implemented now! False returned\n";
				return false;
			}
			else if(sp_r=="*")
			{
				Matches++;
			}
			if(sp_dash.size()==2)
			{
				double Min=atof(sp_dash[0].c_str());
				double Max=atof(sp_dash[1].c_str());
				if(IsNumber(splitted_s[i]))
				{
					double val=atof(splitted_s[i].c_str());
					if((Min<=val)&&(Max>=val))
					{
						Matches++;
					}
				}
				else
				{
					return false;
				}
			}
			else
			{
				for(unsigned int j=0;j<sp_comma.size();j++)
				{
					if(sp_comma[j]==splitted_s[i])
					{
						Matches++;
					}
				}
			}
		}
	}
	if(int(splitted_r.size())==Matches)
	return true;
	
	return false;
}

vector<string> GetValuesS(vector<string> &strings,string reg,bool Unique)
{
	vector<string> result;
	for(unsigned int j=0;j<strings.size();j++)
	{
		vector<string> splitted_s=SplitString(strings[j],'_');
		vector<string> splitted_r=SplitString(reg,'_');
		int Match=0;
		if(splitted_s.size()!=splitted_r.size())
		{
			return result;
		}
		string str;
		for(unsigned int i=0;i<splitted_r.size();i++)
		{
			
			TString sp_r(splitted_r[i].c_str());
			if(splitted_r[i].find("[")!=string::npos)
			{
				sp_r.ReplaceAll("[","");
				sp_r.ReplaceAll("]","");
				if(i<splitted_s.size())
				{
					if(sp_r=="?")
					{
						if(Unique)
						{
							if(!InVector(result,splitted_s[i]))
							{
								str=(splitted_s[i]);
								Match++;
							}
						}
						else
						{
							str=(splitted_s[i]);
							Match++;
						}
					}
				}
			}
			else
			{
				if(splitted_r[i]==splitted_s[i])
				{
					Match++;
				}
			}
		}
		if(Match==(int)splitted_s.size())
		{
			result.push_back(str);
		}
	}
	return result;
}

vector<double> GetValuesD(vector<string> &strings, string reg,bool Unique,double Scale)
{
	vector<string> v_i=GetValuesS(strings,reg,Unique);
	vector<double> result;
	for(unsigned int i=0;i<v_i.size();i++)
	{
		if(IsNumber(v_i[i]))
		{
			result.push_back(atof(v_i[i].c_str())*Scale);
		}
	}
	return result;
}
vector<int> GetValuesI(vector<string> &strings, string reg,bool Unique,int Scale)
{
	vector<string> v_i=GetValuesS(strings,reg,Unique);
	vector<int> result;
	for(unsigned int i=0;i<v_i.size();i++)
	{
		if(IsNumber(v_i[i]))
		{
			result.push_back(atoi(v_i[i].c_str())*Scale);
		}
	}
	return result;
}

std::vector<std::string> FromFortranFormat(string str,string Format)
{
	//упрощенный вариант, скобки внутри формата пока не поддерживаются!
	vector<string> result;
	TString fr(Format.c_str());
	fr.ReplaceAll("(","");
	fr.ReplaceAll(")","");
	int str_iter=0;
	vector<string> Formats=SplitString(fr.Data(),',');
	for(unsigned int i=0;i<Formats.size();i++)
	{
		int Nrepeat=1,length=0;
		string NrepeatStr="";
		string LengthStr="";
		char FormatDescriptor=0;
		bool FoundFormatDescriptor=false;
		for(unsigned int j=0;j<Formats[i].size();j++)
		{
			if((!FoundFormatDescriptor)&&((Formats[i][j]>='0')&&(Formats[i][j]<='9')))
			{
				NrepeatStr+=Formats[i][j];
			}
			else if((Formats[i][j]>='A')&&(Formats[i][j]<='z'))
			{
				FoundFormatDescriptor=true;
				FormatDescriptor=Formats[i][j];
				Nrepeat=atoi(NrepeatStr.c_str());
			}
			else if(FoundFormatDescriptor&&((Formats[i][j]>='0')&&(Formats[i][j]<='9')))
			{
				LengthStr+=Formats[i][j];
			}
			else if(Formats[i][j]=='.')
			{
				break;
			}
		}
		length=atoi(LengthStr.c_str());
		if(Nrepeat==0)
		{
			Nrepeat=1;
		}
		if((length==0)&&(FormatDescriptor>0))
		{
			length=1;
		}
		for(int rep=0; rep<Nrepeat;rep++)
		{
			string sub;
			for(int l=0;l<length;l++)
			{
				if(str_iter>=str.size())
				{
					break;
				}
				sub+=str[str_iter];
				str_iter++;
			}
			result.push_back(sub);
		}
	}
	return result;
}

string GetPotential(ifstream &ifs)//функция, считывающая блок с оптическим потенциалом
{
	string result;
	for(unsigned int i=0;i<4;i++)
	{
		string tmp;
		getline(ifs,tmp);
		result+=tmp;
		result+="\n";
	}
	return result;
}

void EscapeNextNLines(ifstream &ifs,unsigned int N)
{
	string line;
	if(N==0)
	{
		return;
	}
	for(unsigned int i=0;i<N;i++)
	{
		getline(ifs,line);
	}
}
string GetPathToTalysData()
{
	return getenv("TALYSDIR");
}

int sgn(int val) 
{
    if(val<0)
    {
		return -1;
	}
	else
	{
		return 1;
	}
    return 0;
}

bool CompareBeginOfString(string s1, string s2)//функция, выполняющая сравнение начала строки (s1) с маской (s2)
{
	if(s1.size()<s2.size())
	{
		return false;
	}
	for(unsigned int i=0;i<s2.size();i++)
	{
		if(s1[i]!=s2[i])
		{
			return false;
		}
	}
	return true;
}

vector<double> QuantumSum(float A, float B)
{
	float Min=abs(abs(A)-abs(B));
	float Max=abs(abs(A)+abs(B));
	vector<double> result;
	while(Min<=Max)
	{
		result.push_back(Min);
		Min+=1;
	}
	return result;
}
vector<double> Multipolarities(float JPf,float JPi)
{
	vector<double> Results=QuantumSum(JPf,JPi);
	int Parity=sgn(JPf)*sgn(JPi);
	for(unsigned int i=0;i<Results.size();i++)
	{
		Results[i]=Results[i]*Parity;
	}
	return Results;
}

string GetField(string input, int FieldNumber)
{
	stringstream ss(input);
	string tmp;
	for(int i=0;i<FieldNumber;i++)
	{
		string tmp1;
		ss>>tmp1;
		tmp=tmp1;
	}
	return tmp;
}

int FindInVector(int element,vector<int> v)
{
	for(unsigned int i=0;i<v.size();i++)
	{
		if(v[i]==element)
		{
			return i;
		}
	}
	return -1;
}

void ParseReaction(string reaction, string &Projectile, string &OutgoingParticle)
{
	TString ts(reaction.c_str());
	ts.ReplaceAll("(","");
	ts.ReplaceAll("'","");
	ts.ReplaceAll(")","");
	ts.ReplaceAll(","," ");
	ts.ReplaceAll("_"," ");
	stringstream s(ts.Data());
	s>>Projectile>>OutgoingParticle;
}
string NLJToString(int n, int L, float J)
{
	string result;
	J=abs(J);
	L=abs(L);
	if(abs(L-J)!=0.5)
	{
		result=string(TString::Format("Error!n=%d l=%d j=%d/2",n,L,(int)(J*2)));
		return result;
	}
	else
	{
		if((L>6)||(L<0))
		{
			result=string(TString::Format("Unknown L!n=%d l=%d j=%d/2",n,L,(int)(J*2)));
		}
		else
		{
			result=string(TString::Format("%d%c%d/2",n,AngularMomentum[L],(int)(J*2)));
		}
		return result;
	}
}

int StringToNLJ(string s, int &n, int &l, float &JP)
{
	if(s.size()>4)
	{
		if(s[0]>='1'&&s[0]<='9')
		{
			n=atoi(&s[0]);
		}
		else
		{
			return 0;
		}
		for(unsigned int i=0;i<7;i++)
		{
			if(s[1]==AngularMomentum[i])
			{
				l=i;
			}
		}
		s.erase(0,2);
		if((s[2]>='1'&&s[2]<='9')&&(s[4]>='1'&&s[4]<='9'))
		{
			JP=((float)atoi(&s[0]))/((float)atoi(&s[2]));
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 1;
	}
	
}

string LToString(int L)
{
	string result;
	L=abs(L);
	if((L>6)||(L<0))
	{
		result=string(TString::Format("Unknown L! l=%d",L));
	}
	else
	{
		result+=AngularMomentum[L];
	}
	return result;
}

vector<int> StringLToInt(string L_string)
{
	vector<int> result;
	for(unsigned int i=0;i<L_string.size();i++)
	{
		for(unsigned int j=0;j<AngularMomentumSize;j++)
		{
			if(L_string[i]==AngularMomentum[j])
			{
				result.push_back(j);
			}
		}
	}
	return result;
}

string GetNucleusName(int Z)
{
	if((Z>0)&&(Z<119))
	{
		return Atomic_symbols[Z-1];
	}
	return "";
}
string GetNucleusName(string Name)
{
	string result;
	for(unsigned int i=0;i<Name.size();i++)
	{
		if(Name[i]>='A'&&Name[i]<='z')
		result+=Name[i];
	}
	return result;
}

string GetParticleName(int Z, int A)
{
	if((Z==0)&&(A==1))
	{
		return "n";
	}
	if((Z==0)&&(A==0))
	{
		return "g";
	}
	if((Z==0)&&(A==2))
	{
		return "2n";
	}
	if((Z==1)&&(A==1))
	{
		return "p";
	}
	if((Z==1)&&(A==2))
	{
		return "d";
	}
	if((Z==1)&&(A==3))
	{
		return "t";
	}
	if((Z==2)&&(A==4))
	{
		return "a";
	}
	if((Z==2)&&(A==5))
	{
		return "na";
	}
	return to_string(A)+GetNucleusName(Z);
}

double TalysJPToNormalJP(string TalysJP)
{
	double result;
	if(TalysJP[TalysJP.size()-1]=='+')
	{
		result=1;
	}
	else if(TalysJP[TalysJP.size()-1]=='-')
	{
		result=-1;
	}
	else
	{
		return NAN;
	}
	return result*atof(TalysJP.substr(0,TalysJP.size()-1).c_str());
}


void GetAZ(string nucleus, int &Z, int &A)
{
	string mass;
	string name;
	if(nucleus.size()==0)
	{
		cout<<"This is GetAZ(string nucleus, int &Z, int &A): Fatal error: nucleus Z="<<Z<<" A="<<A<<" is not defined!\n";
		return ;
	}
	
	if(nucleus=="p")
	{
		Z=1;A=1; return;
	}
	if(nucleus=="n")
	{
		Z=0;A=1; return;
	}
	if(nucleus=="d")
	{
		Z=1;A=2; return;
	}
	if(nucleus=="t")
	{
		Z=1;A=3; return;
	}
	if(nucleus=="a")
	{
		Z=2;A=4; return;
	}
	if(nucleus=="g")
	{
		Z=0;A=0; return;
	}
	if(nucleus=="h")
	{
		Z=2;A=3; return;
	}
	for(unsigned int i=0;i<nucleus.size();i++)
	{
		if((nucleus[i]>='A')&&(nucleus[i]<='z'))
		{
			name+=nucleus[i];
		}
		if((nucleus[i]>='0')&&(nucleus[i]<='9'))
		{
			mass+=nucleus[i];
		}
	}
	A=atoi(mass.c_str());
	for(unsigned int i=0;i<111;i++)
	{
		string symbol=Atomic_symbols[i];
		
		if(symbol==name)
		{
			Z=Z_number[i];
			return ;
		}
		transform(symbol.begin(), symbol.end(), symbol.begin(), ::toupper);
		if(symbol==name)
		{
			Z=Z_number[i];
			return ;
		}
		transform(symbol.begin(), symbol.end(), symbol.begin(), ::tolower);
		if(symbol==name)
		{
			Z=Z_number[i];
			return ;
		}
	}
	Z=-1;
	return ;
}

int GetTalysVersion()
{
	if(getenv("TALYSVERSION"))
	{
		return atoi(getenv("TALYSVERSION"));
	}
	return 0;
}

double GetNuclearMass(string nucleus)
{
	int A,Z;
	GetAZ(nucleus,Z,A);
	if(nucleus=="n")
	{
		return 939.565;
	}
	if(nucleus=="p")
	{
		return 938.272;
	}
	if(nucleus=="g")
	{
		return 0;
	}
	TString MassFileName;
	if(GetTalysVersion()>=2)
	{
		MassFileName=TString::Format((GetPathToTalysData()+"/structure/masses/ame2020/%s.mass").c_str(),GetNucleusName(Z).c_str());
	}
	else
	{
		MassFileName=TString::Format((GetPathToTalysData()+"/structure/masses/audi/%s.mass").c_str(),GetNucleusName(Z).c_str());
	}
	ifstream MassFile(MassFileName.Data());
	string str;
	while(getline(MassFile,str))
	{
		int a=atoi(GetField(str,2).c_str());
		if(a==A)
		{
			return atof(GetField(str,3).c_str())*u;
		}
	}
	return -1;
}
void GetAbundance(string nucleus,vector<int> &A_values, vector<double> &Abundances)
{
	int A,Z;
	GetAZ(nucleus,Z,A);
	ifstream AbundanceFile(string(TString::Format((GetPathToTalysData()+"/structure/abundance/z%03d").c_str(),Z)).c_str());
	if(!AbundanceFile)
	{
		AbundanceFile.open(string(TString::Format((GetPathToTalysData()+"/structure/abundance/%s.abun").c_str(),GetNucleusName(Z).c_str())).c_str());
		//cout<<"Error:file \""+string(TString::Format((GetPathToTalysData()+"/structure/abundance/z%03d").c_str(),Z))+"\" not found, nucleus_name:"<<nucleus<<" \n"; 
	}
	string str;
	while(getline(AbundanceFile,str))
	{
		A=atoi(GetField(str,2).c_str());
		double abundance=atof(GetField(str,3).c_str());
		A_values.push_back(A);
		Abundances.push_back(abundance/100);
	}
}
double GetAbundance(string nucleus)
{
	int A,Z;
	GetAZ(nucleus,Z,A);
	ifstream AbundanceFile(string(TString::Format((GetPathToTalysData()+"/structure/abundance/z%03d").c_str(),Z)).c_str());
	if(!AbundanceFile)
	{
		AbundanceFile.open(string(TString::Format((GetPathToTalysData()+"/structure/abundance/%s.abun").c_str(),GetNucleusName(Z).c_str())).c_str());
		//cout<<"Error:file \""+string(TString::Format((GetPathToTalysData()+"/structure/abundance/z%03d").c_str(),Z))+"\" not found, nucleus_name:"<<nucleus<<" \n"; 
	}
	string str;
	while(getline(AbundanceFile,str))
	{
		int A_value=atoi(GetField(str,2).c_str());
		double abundance=atof(GetField(str,3).c_str());
		if(A==A_value)
		{
			return abundance/100;
		}
	}
	return 0;
}

double GetAverageMass(string nucleus)
{
	vector<int> A;
	vector<double> Abundances;
	GetAbundance(nucleus,A,Abundances);
	double result=0;
	for(unsigned int i=0;i<Abundances.size();i++)
	{
		result+=GetNuclearMass(to_string(A[i])+nucleus)*Abundances[i]/u;
	}
	return result;
}

double GetNuclearMass(int Z, int A)
{
	if((Z==0)&&(A==1))
	{
		return 939.565;
	}
	TString MassFileName;
	if(GetTalysVersion()>=2)
	{
		MassFileName=TString::Format((GetPathToTalysData()+"/structure/masses/ame2020/%s.mass").c_str(),GetNucleusName(Z).c_str());
	}
	else
	{
		MassFileName=TString::Format((GetPathToTalysData()+"/structure/masses/audi/%s.mass").c_str(),GetNucleusName(Z).c_str());
	}
	string str;
	ifstream MassFile(MassFileName.Data());
	while(getline(MassFile,str))
	{
		int a=atoi(GetField(str,2).c_str());
		if(a==A)
		{
			return atof(GetField(str,3).c_str())*u;
		}
	}
	return -1;
}
double GetSeparationEnergy(string nucleus, string particle)
{
	double nucleus_mass, particle_mass, product_mass;
	
	cout<<"1"<<nucleus<<"\n";
	
	int nucleus_A, nucleus_Z, product_A, product_Z, particle_A, particle_Z;
	if(particle=="n")
	{
		particle_mass=Mn;
		particle_A=1;
		particle_Z=0;
	}
	if(particle=="p")
	{
		particle_mass=Mp;
		particle_A=1;
		particle_Z=1;
	}
	if((particle!="p")&&(particle!="n"))
	{
		GetAZ(particle, particle_Z, particle_A);
		particle_mass=GetNuclearMass(particle_Z, particle_A)-particle_Z*Me;
	}
	GetAZ(nucleus, nucleus_Z, nucleus_A);
	nucleus_mass=GetNuclearMass(nucleus_Z, nucleus_A)-nucleus_Z*Me;
	product_Z=nucleus_Z-particle_Z;
	product_A=nucleus_A-particle_A;
	if((product_Z<0)||(product_A<0))
	{
		cout<<"This is GetSeparationEnergy(string nucleus, string particle=\"n\"): Error: product characteristics are not physical: product_Z="<<product_Z<<" product_A="<<product_A<<"\n";
		return 0;
	}
	product_mass=GetNuclearMass(product_Z, product_A)-product_Z*Me;
	return product_mass-nucleus_mass+particle_mass;
}

double GetSeparationEnergy(int nucleus_Z, int nucleus_A, int particle_Z, int particle_A)
{
	double nucleus_mass, particle_mass, product_mass;
	int product_A, product_Z;
	particle_mass=GetNuclearMass(particle_Z, particle_A)-particle_Z*Me;
	nucleus_mass=GetNuclearMass(nucleus_Z, nucleus_A)-nucleus_Z*Me;
	product_Z=nucleus_Z-particle_Z;
	product_A=nucleus_A-particle_A;
	if((product_Z<0)||(product_A<0))
	{
		cout<<"This is GetSeparationEnergy(int nucleus_Z, int nucleus_A, int particle_Z, int particle_A): Error: product characteristics are not physical: product_Z="<<product_Z<<" product_A="<<product_A<<"\n";
		return 0;
	}
	product_mass=GetNuclearMass(product_Z, product_A)-product_Z*Me;
	return product_mass-nucleus_mass+particle_mass;
}

void ParceReaction(string reaction, string &type, int &ParticleType)
{
	string particles[2];
	int iterator=0;
	for(unsigned int i=0;i<reaction.size();i++)
	{
		if(((reaction[i]>='0')&&(reaction[i]<='9'))||((reaction[i]>='A')&&(reaction[i]<='z')))
		{
			particles[iterator]+=reaction[i];
		}
		else
		{
			if((reaction[i]=='.')||(reaction[i]==','))
			{
				iterator++;
				if(iterator>1)
				{
					return;
				}
			}
		}
	}
	int Z_projectile,A_projectile,Z_product, A_product;
	GetAZ(particles[0],Z_projectile,A_projectile);
	GetAZ(particles[1],Z_product,A_product);
	if(A_projectile-A_product>0)
	{
		type="stripping";
	}
	else
	{
		type="pickup";
	}
	if(Z_projectile-Z_product!=0)
	{
		ParticleType=1;
	}
	else
	{
		ParticleType=0;
	}
}
double DopplerBroading(double E,double MNucl)
{
	double E_n=14.1;
	return E*sqrt(1-2*E_n/MNucl)*(1/(1-sqrt(2*E_n/MNucl)*cos(75*deg))-1/(1+sqrt(2*E_n/MNucl)*cos(75*deg)));//в предположении, что от дальнего края образца до детектора 11 см, толщина образца 6 см
}
double HPGeSigma(double E,string Nucleus)
{
	double m=GetNuclearMass(Nucleus);
	//return 0.45*pow(E,0.2788)+DopplerBroading(E,m)/2;
	return 0.7*pow(E,0.189)+DopplerBroading(E,m)/2;
}

double RefSigmaForDet(double E, TString Det)
{
	Det.ToLower();
	if(Det=="hpge")
	{
		return 0.7*pow(E,0.189);
	}
	if(Det=="labr")
	{
		return 0.32*sqrt(E);
	}
	return 0;
}

double HPGeSigmaOSGI(double E)
{
	return 0.7*pow(E,0.189);
}
double HPGeSigma(double E,int Z, int A)
{
	double m=GetNuclearMass(Z,A);
	return 0.45*pow(E,0.2788)+DopplerBroading(E,m)/2;
}
double RecoilEnergyFromGammaEmission(double Egamma, string nuclide)
{
	double NuclearMass=GetNuclearMass(nuclide);
	return pow(Egamma,2)/(2*NuclearMass*1000);
}
int Nproc()
{
	string s;
	FILE* fp;
	fp = popen("nproc","r");
	int ReadFlag=1;
	while(ReadFlag==1)
	{
		char c;
		ReadFlag=fread(&c,1,1,fp);
		s+=c;
	}
	stringstream ss(s);
	int result=0;
	ss>>result;
	return result;
}
vector<string> ListFiles(string mask, string PathTo)
{
	vector<string> FileNames;
	string s;
	FILE* fp;
	if(PathTo.size()==0)
	{
		fp = popen(("ls "+mask).c_str(),"r");
	}
	else
	{
		fp = popen(("cd "+PathTo+"; ls "+mask).c_str(),"r");
	}
	
	int ReadFlag=1;
	while(ReadFlag==1)
	{
		char c;
		ReadFlag=fread(&c,1,1,fp);
		s+=c;
	}
	stringstream ss(s);
	while(ss)
	{
		ss>>s;
		if(s.size()>1)
		{
			if((s[0]>='!')&&(s[0]<='z'))
			{
				if(FileNames.size()>0)
				{
					if(FileNames[FileNames.size()-1]!=s)
					FileNames.push_back(s);
				}
				else
				{
					FileNames.push_back(s);
				}
				
			}
		}
	}
	return FileNames;
}

vector<string> FindFile(vector<string> Paths, string Mask)
{
	cout<<"This is FindFile, Paths.size()="<<Paths.size()<<"\n";
	cout<<"This is FindFile, mask "<<Mask<<"\n";
	vector<string> Masks;
	vector<string> Result;
	string m_tmp;
	for(unsigned int i=0;i<Mask.size();i++)
	{
		if(Mask[i]!='*')
		{
			m_tmp+=Mask[i];
		}
		else
		{
			Masks.push_back(m_tmp);
			m_tmp="";
		}
	}
	if(m_tmp!="")
	{
		Masks.push_back(m_tmp);
	}
	
	if(Paths.size()==0)
	{
		Paths.push_back("");
	}
	for(unsigned int i=0;i<Paths.size();i++)
	{
	//	cout<<"Paths["<<i<<"] "<<Paths[i]<<"\n";
		if(Paths[i]!="")
		{
			if(Paths[i][Paths[i].size()-1]!='/')
			{
				Paths[i]+="/";
			}
		}
		vector<string> FileList=ListFiles(Paths[i]);
	//	cout<<"This is FindFile, found:"<<FileList.size()<<"\n";
		for(unsigned int j=0;j<FileList.size();j++)
		{
			//int FoundIterator=0;
			unsigned int FoundIterator=0;
			int Position=-1;
		//	cout<<"This is FindFile, found:"<<FileList[j]<<"\n";
			if((int)Mask.find('*')==-1)
			{
				if((FileList[j]==Mask))
				Result.push_back(Paths[i]+FileList[j]);
			}
			else
			{
				if(Mask[0]!='*')
				{
					if(Mask[0]!=FileList[j][0])
					{
						FoundIterator--;//костыль, выкидывающий несовпадение первых букв 
					}
				}
				for(unsigned int k=0;k<Masks.size();k++)
				{
					Position=(int)FileList[j].find(Masks[k]);
					if(Position>-1)
					{
						FoundIterator++;
					}
				}
				if(FoundIterator==Masks.size())
				{
					Result.push_back(Paths[i]+FileList[j]);
				}
			}
		}
	}
	return Result;
}

void GenerateListOfElements(string composition, vector<string> &Elements, vector<int> &Quantity)
{
	Elements.resize(0);
	Quantity.resize(0);
	string tmpElement;
	vector<string> Q_values;
	for(unsigned int i=0;i<composition.size();i++)
	{
		if((composition[i]>='A')&&(composition[i]<='Z'))
		{
			tmpElement+=composition[i];
			if(i<composition.size()-1)
			{
				if(((composition[i+1]>='0')&&(composition[i+1]<='9'))||((composition[i+1]>='A')&&(composition[i+1]<='Z')))
				{
					if(tmpElement.size()>0)
					Elements.push_back(tmpElement);
					tmpElement.resize(0);
				}
			}
			else
			{
				if(tmpElement.size()>0)
				Elements.push_back(tmpElement);
				tmpElement.resize(0);
			}
		}
		else if((composition[i]>='a')&&(composition[i]<='z'))
		{
			tmpElement+=composition[i];
			if(tmpElement.size()>0)
			Elements.push_back(tmpElement);
			tmpElement.resize(0);
		}
	}
	for(unsigned int i=0;i<Elements.size();i++)
	{
		if(i<Elements.size()-1)
		{
			unsigned int p1,p2;
			p1=composition.find(Elements[i])+Elements[i].size();
			p2=composition.find(Elements[i+1]);
			Q_values.push_back(composition.substr(p1,p2-p1));
			composition=composition.substr(p1);
		}
		if(i==Elements.size()-1)
		{
			unsigned int le=composition.find(Elements[i])+Elements[i].size();
			Q_values.push_back(composition.substr(le,composition.size()-le));
		}
		
	}
	for(unsigned int i=0;i<Q_values.size();i++)
	{
		if(Q_values[i]=="")
		{
			Quantity.push_back(1);
		}
		else
		{
			Quantity.push_back(atoi(Q_values[i].c_str()));
		}
	}
	vector<string> Elements_tmp;
	vector<int> Quantity_tmp;
	
	for(unsigned int i=0;i<Elements.size();i++)
	{
		int Q=Quantity[i];
		for(unsigned int j=i+1;j<Elements.size();j++)
		{
			if((Elements[i]==Elements[j])&&(Elements[i]!="*"))
			{
				Q+=Quantity[j];
				Elements[j]="*";
			}
		}
		if(Elements[i]!="*")
		{
			Elements_tmp.push_back(Elements[i]);
			Quantity_tmp.push_back(Q);
		}
	}
	Quantity=Quantity_tmp;
	Elements=Elements_tmp;
}
double GetMolarMass(string Composition)
{
	double MolarMass=0;
	vector<string> Elements;
	vector<int> Q;
	GenerateListOfElements(Composition,Elements,Q);
	for(unsigned int i=0;i<Elements.size();i++)
	{
		MolarMass+=GetAverageMass(Elements[i])*Q[i];
	}
	return MolarMass;
}

vector<double> GetMolarMassFractions(string Composition)
{
	vector<double> MolarMass;
	vector<string> Elements;
	vector<int> Q;
	GenerateListOfElements(Composition,Elements,Q);
	for(unsigned int i=0;i<Elements.size();i++)
	{
		MolarMass.push_back(GetAverageMass(Elements[i])*Q[i]);
	}
	return MolarMass;
}

string InvertString(string line)
{
	string line2;
	stringstream s;
	for(unsigned int i=0;i<line.size();i++)
	{
		s<<line[line.size()-i-1];	
	}
	s>>line2;
	return line2;
}

string GetFileType(string line)
{
	string type;
	stringstream s;
	for(unsigned int i=0;i<line.size();i++)
	{
		if(line[line.size()-i-1]!='.')
		{
			s<<line[line.size()-i-1];
		}
		else
		{
			s>>type;
			return InvertString(type);
		}
	}
	return "";
}

float GetEnergyFromFileName(string line)
{
	float E=0;
	stringstream s;
	int flag=0;
	for(unsigned int i=0;i<line.size();i++)
	{
		if(i>1)
		{
			if(line[i-1]=='_')
			{
				if((line[i]>='0')&&(line[i]<='9'))
				{
					flag++;
				}
			}
		}

		if(flag==1)
		{
			s<<line[i];
		}	
	}
	s>>E;
	return E*1000;
}

string GetPath(string line)
{
	stringstream s;
	string path;
	int flag_slash=0;
	for(unsigned int i=0;i<line.size();i++)
	{
		if(line[line.size()-i-1]=='/')
		{
			flag_slash=1;
		}
		if(flag_slash==1)
		{
			s<<line[line.size()-i-1];
		}
	}
	s>>path;
	return InvertString(path);
}
string GetFileName(string line)
{
	stringstream s;
	string name;
	unsigned int flag_dot=0;
	unsigned int dot_iterator=0;
	unsigned int first_dot_iterator=0;
	for(unsigned int i=0;i<line.size();i++)
	{
		if(line[line.size()-i-1]=='.')
		{
			flag_dot=1;
			if(dot_iterator==0)
			{
				first_dot_iterator=i;
			}
			dot_iterator++;
		}
		if(line[line.size()-i-1]=='/')
		{
			s>>name;
			return InvertString(name);
		}
		if((flag_dot==1)&&(i!=first_dot_iterator))
		{
			s<<line[line.size()-i-1];
		}
	}
	s>>name;
	return InvertString(name);
}
float EvalKineticEnergy(float ma,float mA,float mb,float mB,float Ta,float angle,float Q)//reference: http://nuclphys.sinp.msu.ru/reactions/cinem.htm
{
	angle=angle/180*3.1416;
	float v1=(mb+mB)*((mB-ma)*Ta+mB*Q)/(ma*mb*Ta);
	  
	int sign=0;
	if(v1>=0)
	{
		sign=1;
	}
	else
	{
		sign=-1;
		float thetaMAX=acos(sqrt(-v1));
			
		if(thetaMAX<angle)
		{
			cout<<"angle "<<angle/3.1416*180<<"deg is not valid, maximal angle is "<<thetaMAX/3.1416*180<<"deg\n";
			return -1;
		}
	
	}

	double res = ma*mb*Ta/pow(mb+mB,2)*pow(cos(angle)+sign*sqrt(pow(cos(angle),2)+v1),2);

	return res;
}
float EvalKineticEnergy(string a,string A,string b,string B,float Ta,float angle)//reference: http://nuclphys.sinp.msu.ru/reactions/cinem.htm
{
	double ma,mA,mb,mB,Q;
	ma=GetNuclearMass(a);
	mA=GetNuclearMass(A);
	mb=GetNuclearMass(b);
	mB=GetNuclearMass(B);
	Q=ma+mA-mb-mB;
	//cout<<"ma: "<<ma<<" mA: "<<mA<<" mb: "<<mb<<" mB: "<<mB<<" Q: "<<Q<<"\n";
	return EvalKineticEnergy(ma,mA,mb,mB,Ta,angle,Q);
}
float EvalKineticEnergy(string a,string A,string b,string B,float Ta,float angle,double Q)//reference: http://nuclphys.sinp.msu.ru/reactions/cinem.htm
{
	double ma,mA,mb,mB;
	ma=GetNuclearMass(a);
	mA=GetNuclearMass(A);
	mb=GetNuclearMass(b);
	mB=GetNuclearMass(B);
	//cout<<"ma: "<<ma<<" mA: "<<mA<<" mb: "<<mb<<" mB: "<<mB<<" Q: "<<Q<<"\n";
	return EvalKineticEnergy(ma,mA,mb,mB,Ta,angle,Q);
}
double RelKineticEnergy(float ma,float mA,float mb,float mB,float Ta,float angle)//релятивистская формула для кинетической энергии. Для расчета энергий неупруго рассеянных нейтронов нужно добавить Q к mB при вызове
{
	angle=angle/180.0*3.1416;
	double Ep=ma+mA+Ta;
	double P1=sqrt(2*ma*Ta+pow(Ta,2));
	double A=Ep*Ep-pow(P1,2)+pow(mb,2)-pow(mB,2);
	double Eb=(A*Ep+P1*cos(angle)*sqrt(pow(A,2)-4*mb*mb*(pow(Ep,2)-pow(P1*cos(angle),2))))/(2*(Ep*Ep-pow(P1*cos(angle),2)));
	double T=Eb-mb;
	return T;
}
int GetColor(int nCol)
{
	if((nCol>4)&&(nCol<9))
	{
		nCol+=1;
	}else if((nCol>9)&&(nCol<19))
	{
		nCol+=2;
	}
	else if((nCol>18))
	{
		nCol+=3;
	}
	return nCol;
}
