#include <iostream>
#include "C4.hh"
#include "../Parser.cpp"
#include "../TalysLib.hh"
#pragma once
/*double ENDFAtof(string s)//костыль для устранения проблемы с представлением экспоненциальной части числа: по умолчанию 1.000000-5 читается как 1
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
}*/

double *C4String::GetField(string colname)
{
	if(colname=="Data")
	{
		return &Data;
	}
	if(colname=="dData")
	{
		return &dData;
	}
	if(colname=="Energy")
	{
		return &Energy;
	}
	if(colname=="dEnergy")
	{
		return &dEnergy;
	}
	if(colname=="Cos")
	{
		return &Cos_LO;
	}
	if(colname=="dCos")
	{
		return &dCos_LO;
	}
	if(colname=="ELV_HL")
	{
		return &ELV_HL;
	}
	if(colname=="dELV_HL")
	{
		return &dELV_HL;
	}
	return 0;
}

void C4String::GetFromString(string str)
{
	if(str.size()<20)
	{
		cout<<"Err:"<<str<<"\n";
	}
	Prj=atoi(str.substr(0,5).c_str());
	Targ=atoi(str.substr(5,6).c_str());
	M=atoi(str.substr(11,1).c_str());
	MF=atoi(str.substr(12,3).c_str());
	MT=atoi(str.substr(15,4).c_str());
	PXC=str.substr(19,1);
	Energy=ENDFAtof(str.substr(22,9));
	dEnergy=ENDFAtof(str.substr(31,9));
	Data=ENDFAtof(str.substr(40,9));
	dData=ENDFAtof(str.substr(49,9));
	Cos_LO=ENDFAtof(str.substr(58,9));
	dCos_LO=ENDFAtof(str.substr(67,9));
	ELV_HL=ENDFAtof(str.substr(76,9));
	dELV_HL=ENDFAtof(str.substr(85,9));
	I78=atoi(str.substr(94,3).c_str());
	Reference=str.substr(97,23);
	Sub=atoi(str.substr(127,3).c_str());
	
	
	/*cout<<str.substr(0,5)<<"\n";
	cout<<str.substr(5,6)<<"\n";
	cout<<str.substr(11,1)<<"\n";
	cout<<str.substr(12,3)<<"\n";
	cout<<str.substr(16,3)<<"\n";
	cout<<str.substr(19,3)<<"\n";
	cout<<str.substr(22,9)<<"\n";
	cout<<str.substr(31,9)<<"\n";
	cout<<str.substr(40,9)<<"\n";
	cout<<str.substr(49,9)<<"\n";
	cout<<str.substr(58,9)<<"\n";
	cout<<str.substr(67,9)<<"\n";
	cout<<str.substr(76,9)<<"\n";
	cout<<str.substr(85,9)<<"\n";
	cout<<str.substr(94,3)<<"\n";
	cout<<str.substr(97,23)<<"\n";
	cout<<str.substr(127,3)<<"\n";*/	
}

void C4DataSet::Read(ifstream &ifs, string _DataSet)
{
	//bool IsDataBlock=false;
	bool Reading=true;
	if(_DataSet.size()>0)
	{
		stringstream s(_DataSet);
		string key;
		s>>key;
	}
	while(Reading)
	{
		if(ifs)
		{
			string line;
			getline(ifs,line);
			if(line.find("#/DATASET")!=string::npos)
			{
				Reading=false;
				return ;
			}
			if(line.find("#")!=string::npos)
			{
				stringstream s(line);
				string key;
				s>>key;
				if(key=="#DATASET")
				{
					s>>DataSet;
				}
				if(key=="#DATE")
				{
					s>>Date;
				}
				if(key=="#MF")
				{
					s>>MF;
				}//MF, MT, Proj, Targ
				if(key=="#MT")
				{
					s>>MT;
				}
				if(key=="#PROJ")
				{
					s>>Proj;
				}
				if(key=="#TARG")
				{
					string str;
					s>>str;
					Targ=atoi(str.c_str());
					if(str.size()<5)
					{
						str="00"+str;
					}
					if(str.size()<6)
					{
						str="0"+str;
					}
					//первые 3 числа-заряд, вторые-масса
					ZTarg=atoi((str.substr(0,3)).c_str());
					ATarg=atoi((str.substr(3)).c_str());
					
				}
				if(key=="#REACTION")
				{
					s>>Reaction;
				}
				if(key=="#/ENTRY")
				{
					Reading=false;
				}
			}
			else
			{
				C4String c4s;
				c4s.GetFromString(line);
				Table.push_back(c4s);
			}
		}
	}
}
vector<double> C4DataSet::GetVectorOfValues(string colname,string RefColName,double RefValue,double Difference)
{
	vector<double> result;
	bool Select=false;
	if(RefColName.size()>0)
	{
		Select=true;
	}
	for(unsigned int i=0;i<Table.size();i++)
	{
		double *value=Table[i].GetField(colname);
		if(value)
		{
			if(Select)
			{
				double *RValue=Table[i].GetField(RefColName);
				if(RefValue)
				{
					double rv=*RValue;
					if(abs(rv-RefValue)<=Difference)
					{
						result.push_back(*value);
					}
				}
			}
			else
			{
				result.push_back(*value);
			}
		}
	}
	return result;
}

vector<double> C4DataSet::GetVectorOfPossibleValues(string colname)//возвращает вектор значений, которые принимает соответствующая колонка
{
	vector<double> values=GetVectorOfValues(colname);
	sort(values.begin(),values.end());
	values.erase(unique(values.begin(),values.end()),values.end());
	return values;
}
int C4DataSet::GetZTarg()
{
	return ZTarg;
}
int C4DataSet::GetATarg()
{
	return ATarg;
}
void C4Entry::Read(ifstream &ifs)
{
	string line;
	bool ConutneTitle=false;
	bool ConutneAuthor=false;
	bool ConutneReference=false;
	while(getline(ifs,line))
	{
		stringstream s(line);
		string key;
		s>>key;
		if(key=="#ENTRY")
		{
			s>>Entry;
		}
		if(key=="#/ENTRY")
		{
			return;
		}
		if(key=="#AUTHOR1")
		{
			s>>Author1;
		}
		if(key=="#YEAR")
		{
			s>>Year;
		}
		if(key=="#TITLE")
		{
			if(line.size()>12)
			{
				Title+=line.substr(12);
				ConutneTitle=true;
			}
		}
		if(key=="#AUTHOR(S)")
		{
			ConutneTitle=false;
			ConutneAuthor=true;
			while(s)
			{
				string a_tmp;
				s>>a_tmp;
				if(a_tmp.size()>1)
				{
					TString ts(a_tmp.c_str());
					ts.ReplaceAll(",","");
					Authors.push_back(ts.Data());
				}
				
			}
		}
		if(key=="#REF-CODE")
		{
			ConutneAuthor=false;
			s>>RefCode;
		}
		if(key=="#REFERENCE")
		{
			ConutneReference=true;
			if(line.size()>12)
			Reference+=line.substr(12);
		}
		if(key=="#DATASETS")
		{
			ConutneReference=false;
			DataSet.Read(ifs);
		}
		if(key=="#+")
		{
			if(ConutneTitle)
			{
				if(line.size()>12)
				Title+=line.substr(12);
			}
			if(ConutneAuthor)
			{
				while(s)
				{
					string a_tmp;
					s>>a_tmp;
					if(a_tmp.size()>1)
					{
						TString ts(a_tmp.c_str());
						ts.ReplaceAll(",","");
						Authors.push_back(ts.Data());
					}
				}
			}
			if(ConutneReference)
			{
				if(line.size()>12)
				Reference+=" "+line.substr(12);
			}
		}
	}
}

const char *C4Entry::GetName() const
{
	return DataSet.DataSet.c_str();
}

void C4Graph::CopyData()
{
	DataSet=fEntry->DataSet.DataSet; Reaction=fEntry->DataSet.Reaction;
	Date=fEntry->DataSet.Date; MF=fEntry->DataSet.MF; MT=fEntry->DataSet.MT; Proj=fEntry->DataSet.Proj; Targ=fEntry->DataSet.Targ; ZTarg=fEntry->DataSet.ZTarg; ATarg=fEntry->DataSet.ATarg;
	Entry=fEntry->Entry; Author1=fEntry->Author1; RefCode=fEntry->RefCode; Reference=fEntry->Reference; Title=fEntry->Title; DOI=fEntry->DOI;
	vector<string> Authors=fEntry->Authors;
	Year=fEntry->Year;
	//cout<<" "<<MT<<" "<<fEntry->DataSet.MT<<"\n";
}

/*void C4AngularDistribution::Draw(string Option)
{
	Graph.Draw(Option.c_str());
}*/

vector<C4EnergyDistribution> ExtractEnergyDistributions(C4Entry *Entry)
{
	vector<double> LevelEnergyValues=Entry->DataSet.GetVectorOfPossibleValues("ELV_HL");
	vector<C4EnergyDistribution> result;
	for(unsigned int j=0;j<LevelEnergyValues.size();j++)
	{
		C4EnergyDistribution ED;
		ED.fEntry=Entry;
		ED.CopyData();
		ED.ID=ED.DataSet+"_"+to_string(j);
		//бегаем по таблице и собираем нужные данные, это не особо эффективно
		for(unsigned int k=0;k<Entry->DataSet.Table.size();k++)
		{
			double LVLEnergy=*(Entry->DataSet.Table[k].GetField("ELV_HL"));
			if(LevelEnergyValues[j]==LVLEnergy)
			{
				ED.LevelEnergy=LVLEnergy;
				double Energy=*(Entry->DataSet.Table[k].GetField("Energy"));
				double EnergyErr=*(Entry->DataSet.Table[k].GetField("dEnergy"));
				double Data=*(Entry->DataSet.Table[k].GetField("Data"));
				double DataErr=*(Entry->DataSet.Table[k].GetField("dData"));
				ED.SetPoint(ED.GetN(),Energy/1e6,Data*1000);
				ED.SetPointError(ED.GetN()-1,EnergyErr/1e6,DataErr*1000);
			}
		}
		ED.SetTitle((ED.Author1+" "+to_string(ED.Year)).c_str());
		ED.GetXaxis()->SetTitle("E, MeV");
		ED.GetYaxis()->SetTitle("#sigma, mb");
		result.push_back(ED);
	}
	return result;
}
vector<C4AngularDistribution> ExtractAngularDistributions(C4Entry *Entry)
{
	vector<double> ProjectileEnergyValues=Entry->DataSet.GetVectorOfPossibleValues("Energy");
	vector<double> LevelEnergyValues=Entry->DataSet.GetVectorOfPossibleValues("ELV_HL");
	vector<C4AngularDistribution> result;
	for(unsigned int i=0;i<ProjectileEnergyValues.size();i++)
	{
		for(unsigned int j=0;j<LevelEnergyValues.size();j++)
		{
			C4AngularDistribution AD;
			AD.fEntry=Entry;
			AD.CopyData();
			AD.ID=AD.DataSet+"_"+to_string(i)+"_"+to_string(j);
			//бегаем по таблице и собираем нужные данные, это не особо эффективно
			for(unsigned int k=0;k<Entry->DataSet.Table.size();k++)
			{
				//"Data dData Energy dEnergy Cos dCos"
				double Energy=*(Entry->DataSet.Table[k].GetField("Energy"));
				double LVLEnergy=*(Entry->DataSet.Table[k].GetField("ELV_HL"));
				if((ProjectileEnergyValues[i]==Energy)&&(LevelEnergyValues[j]==LVLEnergy))
				{
					AD.ProjectileEnergy=Energy;
					AD.LevelEnergy=LVLEnergy;
					double Angle=*(Entry->DataSet.Table[k].GetField("Cos"));
					double AngleErr=*(Entry->DataSet.Table[k].GetField("dCos"));
					double Data=*(Entry->DataSet.Table[k].GetField("Data"));
					double DataErr=*(Entry->DataSet.Table[k].GetField("dData"));
					AD.SetPoint(AD.GetN(),acos(Angle)/3.1416*180,Data*1000);
					
					AngleErr=abs(acos(Angle+AngleErr)-acos(Angle-AngleErr))/3.1416*180;
					AD.SetPointError(AD.GetN()-1,AngleErr,DataErr*1000);
				}
			}
			AD.SetTitle((AD.Author1+" "+to_string(AD.Year)).c_str());
			AD.GetXaxis()->SetTitle("#theta, deg");
			AD.GetYaxis()->SetTitle("#frac{d#sigma}{d#Omega}, mb/str");	
			result.push_back(AD);
		}
	}
	return result;
}
int GetParticleID(string PartName)
{
	if(PartName== "n")
		return 1;
	if(PartName== "p")
		return 1001;
	if(PartName== "a")
		return 2004;
	if(PartName== "d")
		return 1002;
	if(PartName== "t")
		return 1003;
	if(PartName== "3He")
		return 2003;
	
	return -1;
}
int GetC4MT(string reaction,string prj)
{
	if((reaction=="")||(reaction=="elastic")||(reaction=="2"))
	{
		return 2;
	}
	if((reaction=="1")||(reaction=="total"))
	{
		return 1;
	}
	if((reaction=="3")||(reaction=="nonel"))
	{
		return 3;
	}
	bool InelasticScat=false;
	if(reaction.find("'")!=string::npos)
	{
		InelasticScat=true;
	}
	TString r(reaction.c_str());
	r.ReplaceAll(","," ");
	r.ReplaceAll("(","");
	r.ReplaceAll("'"," ");
	r.ReplaceAll(")","");
	stringstream tmp(r.Data());
	string incomingParticle,OutgoingParticle;
	tmp>>incomingParticle>>OutgoingParticle;
	if((!InelasticScat)&&(OutgoingParticle==incomingParticle))//случай вроде reaction=(n,n)
	{
		return 2;
	}
	if(OutgoingParticle=="n")
	{
		return 51;
	}
	if(OutgoingParticle=="p")
	{
		return 601;
	}
	if(OutgoingParticle=="d")
	{
		return 651;
	}
	if(OutgoingParticle=="t")
	{
		return 701;
	}
	if(OutgoingParticle=="3He")
	{
		return 751;
	}
	if(OutgoingParticle=="a")
	{
		return 801;
	}
	return -1;
}

vector<string> GetListOfTables(sqlite3 *db, string Template="")
{
	vector<string> result;
    sqlite3_stmt *stmt;
    if(Template.size()>0)
    {
		Template=" AND name LIKE '"+Template+"'";
	}
    sqlite3_prepare_v2(db,("SELECT name FROM sqlite_master WHERE type = \"table\""+Template+";").c_str(), -1, &stmt, NULL);
    while (1) 
    {
        int s;
        s = sqlite3_step (stmt);
        if (s == SQLITE_ROW) 
        {
            result.push_back(string((char*)sqlite3_column_text (stmt, 0)));
        }
        else if (s == SQLITE_DONE) 
        {
            break;
        }
        else 
        {
            cout<<"GetListOfTables: Failed.\n";
            break;
        }
    }
    return result;
}

void C4Container::AddData(C4Entry *Entry)
{
	if(!Entry)
	{
		return ;
	}
	int Index=-1;
	for(unsigned int i=0;i<MF_values.size();i++)
	{
		if(MF_values[i]==Entry->DataSet.MF)
		{
			Index=i;
			break;
		}
	}
	if(Index<0)
	{
		MF_values.push_back(Entry->DataSet.MF);
		Data.resize(MF_values.size());
		Index=MF_values.size()-1;
	}
	Data[Index].push_back(*Entry);
}
vector<C4Entry> *C4Container::GetData(int MF)
{
	int Index=-1;
	for(unsigned int i=0;i<MF_values.size();i++)
	{
		if(MF_values[i]==MF)
		{
			Index=i;
			break;
		}
	}
	if(Index<0)
	{
		return 0;
	}
	return &Data[Index];
}

double C4Graph::EvalChi2(TObject *InpObj)
{
	double result=0;
	if(InpObj->InheritsFrom("TGraph"))
	{
		TGraph* g=(TGraph*)InpObj;
		for(int k=0;k<GetN();k++)
		{
			double x,y,x_err,y_err;
			GetPoint(k,x,y);
			x_err=GetErrorX(k);
			y_err=GetErrorY(k);
			if(x_err>0||y_err>0)
			{
				result+=pow(y-g->Eval(x),2)/(pow(x_err,2)+pow(y_err,2));
			}
			else
			{
				result+=pow(y-g->Eval(x),2);
			}
		}
	}
	else if(InpObj->InheritsFrom("Nucleus"))
	{
		Nucleus *Nucl=((Nucleus*)InpObj)->FindProductByMT(MT);
		if(Nucl)
		{
			if(SumForLevels.size()>0)
			{
				EvaluatedDataGraph* g=(EvaluatedDataGraph*)(Nucl->Levels[SumForLevels[0]].GetAngularDistribution());
				for(unsigned int i=0;i<SumForLevels.size();i++)
				{
					if(this->InheritsFrom("C4AngularDistribution"))
					{
						g->Add(Nucl->Levels[SumForLevels[i]].GetAngularDistributionAtEnergy(ProjectileEnergy*1e-6));
					}
					else if(this->InheritsFrom("C4EnergyDistribution"))
					{
						g->Add(Nucl->Levels[SumForLevels[i]].GetCSGraph());
					}
				}
				result+=EvalChi2(g);
			}
			else
			{
				if(MT==2)
				{
					if(this->InheritsFrom("C4AngularDistribution"))
					{
						return EvalChi2(Nucl->GetElasticAngularDistributionAtEnergy(ProjectileEnergy*1e-6));
					}
					else if(this->InheritsFrom("C4EnergyDistribution"))
					{
						return EvalChi2(Nucl->GetCrossSectionGraph("Elastic"));
					}
				}
				else
				{
					if(this->InheritsFrom("C4AngularDistribution"))
					{
						return EvalChi2(Nucl->Levels[LevNumber].GetAngularDistributionAtEnergy(ProjectileEnergy*1e-6));
					}
					else if(this->InheritsFrom("C4EnergyDistribution"))
					{
						return EvalChi2(Nucl->Levels[LevNumber].GetCSGraph());
					}
				}
			}
		}
	}
	return result;
}
void C4Graph::DrawWithCalculationResult(string Option,TObject *InpObj)
{
	EvaluatedDataGraph* g;
	if(InpObj->InheritsFrom("TGraph"))
	{
		g=(EvaluatedDataGraph*)InpObj;
		Draw(Option.c_str());
		g->DrawClone("l");
	}
	else if(InpObj->InheritsFrom("Nucleus"))
	{
		Nucleus *Nucl=((Nucleus*)InpObj)->FindProductByMT(MT);
		if(Nucl)
		{
			if(SumForLevels.size()>0)
			{
				g=(EvaluatedDataGraph*)(Nucl->Levels[SumForLevels[0]].GetAngularDistribution());
				for(unsigned int i=0;i<SumForLevels.size();i++)
				{
					if(this->InheritsFrom("C4AngularDistribution"))
					{
						g->Add(Nucl->Levels[SumForLevels[i]].GetAngularDistributionAtEnergy(ProjectileEnergy*1e-6));
					}
					else if(this->InheritsFrom("C4EnergyDistribution"))
					{
						g->Add(Nucl->Levels[SumForLevels[i]].GetCSGraph());
					}
				}
				Draw(Option.c_str());
				g->DrawClone("l");
			}
			else
			{
				if(MT==2)
				{
					if(this->InheritsFrom("C4AngularDistribution"))
					{
						g=(EvaluatedDataGraph*)(Nucl->GetElasticAngularDistributionAtEnergy(ProjectileEnergy*1e-6));
					}
					else if(this->InheritsFrom("C4EnergyDistribution"))
					{
						g=(EvaluatedDataGraph*)(Nucl->GetCrossSectionGraph("Elastic"));
					}
					Draw(Option.c_str());
					g->DrawClone("l");
				}
				else
				{
					if(this->InheritsFrom("C4AngularDistribution"))
					{
						g=(EvaluatedDataGraph*)(Nucl->Levels[LevNumber].GetAngularDistributionAtEnergy(ProjectileEnergy*1e-6));
					}
					else if(this->InheritsFrom("C4EnergyDistribution"))
					{
						g=(EvaluatedDataGraph*)(Nucl->Levels[LevNumber].GetCSGraph());
					}
					Draw(Option.c_str());
					g->DrawClone("l");
				}
			}
		}
	}
}


vector<C4AngularDistribution> C4Container::GetAngularDistributions()
{
	vector<C4AngularDistribution> result;
	vector<C4Entry> *Entries=GetData(4);
	if(!Entries)
	{
		cout<<"Cannot get Data with MF=4. Empty vector returnrd\n";
		return result;
	}
	for(unsigned int i=0;i<Entries->size();i++)
	{
		vector<C4AngularDistribution> tmp=ExtractAngularDistributions(&(Entries->at(i)));
		result.insert(result.end(), tmp.begin(), tmp.end());
	}
	return result;
}
vector<C4EnergyDistribution>  C4Container::GetEnergyDistributions()
{
	vector<C4EnergyDistribution> result;
	vector<C4Entry> *Entries=GetData(3);
	if(!Entries)
	{
		cout<<"Cannot get Data with MF=3. Empty vector returnrd\n";
		return result;
	}
	for(unsigned int i=0;i<Entries->size();i++)
	{
		vector<C4EnergyDistribution> tmp=ExtractEnergyDistributions(&(Entries->at(i)));
		result.insert(result.end(), tmp.begin(), tmp.end());
	}
	return result;
}

void C4Container::GenerateBaseSummaryAndSaveToXLSX(string Filename,string Template)
{
	TXlsxwriter xl;
	xl.Open(Filename);
	GenerateBaseSummaryAndSaveToXLSX(xl,Template);
}

void C4Container::GenerateBaseSummaryAndSaveToXLSX(TXlsxwriter &xl,string Template)
{
	if(Data.size()==0)
	{
		cout<<"This is C4Container::GenerateBaseSummaryAndSaveToXLSX(): Data container is empty\n";
		return;
	}
	vector<string> RawKeywords=SplitString(Template,' ');
	string Addition;
	vector<string> Keywords;
	for(unsigned int i=0;i<RawKeywords.size();i++)
	{
		if(RawKeywords[i].find("WSAddition=")!=string::npos)
		{
			TString ts(RawKeywords[i].c_str());
			ts.ReplaceAll("WSAddition=","");
			Addition=string(ts.Data());
		}
		else
		{
			Keywords.push_back(RawKeywords[i]);
		}
	}
	xl.GoToWorksheet("Angular Distributions "+Addition);
	for(unsigned int i=0;i<Keywords.size();i++)
	{
		xl<<Keywords[i];
	}
	xl<<"\n";
	vector<C4AngularDistribution> Ang=GetAngularDistributions();
	vector<C4EnergyDistribution> ED=GetEnergyDistributions();
	for(unsigned int i=0;i<Ang.size();i++)
	{
		for(unsigned int j=0;j<Keywords.size();j++)
		{
			if(Keywords[j]=="MF")
			{
				xl<<Ang[i].MF;
			}
			if(Keywords[j]=="MT")
			{
				xl<<Ang[i].MT;
			}
			if(Keywords[j]=="PrjE")
			{
				xl<<Ang[i].ProjectileEnergy;
			}
			if(Keywords[j]=="LevE")
			{
				xl<<Ang[i].LevelEnergy;
			}
			if(Keywords[j]=="Author")
			{
				xl<<Ang[i].Author1;
			}
			if(Keywords[j]=="Year")
			{
				xl<<Ang[i].Year;
			}
			if(Keywords[j]=="Reference")
			{
				xl<<Ang[i].Reference;
			}
		}
		xl<<"\n";
	}
	xl.GoToWorksheet("Cross sections "+Addition);
	for(unsigned int i=0;i<Keywords.size();i++)
	{
		if(Keywords[i]!="PrjE")
		xl<<Keywords[i];
	}
	xl<<"\n";
	for(unsigned int i=0;i<ED.size();i++)
	{
		for(unsigned int j=0;j<Keywords.size();j++)
		{
			if(Keywords[j]=="MF")
			{
				xl<<ED[i].MF;
			}
			if(Keywords[j]=="MT")
			{
				xl<<ED[i].MT;
			}
			if(Keywords[j]=="LevE")
			{
				xl<<ED[i].LevelEnergy;
			}
			if(Keywords[j]=="Author")
			{
				xl<<ED[i].Author1;
			}
			if(Keywords[j]=="Year")
			{
				xl<<ED[i].Year;
			}
			if(Keywords[j]=="Reference")
			{
				xl<<ED[i].Reference;
			}
		}
		xl<<"\n";
	}
	//xl.Close();
}

C4Container RequestC4DataSubentVector(sqlite3 *db, TFile *BaseROOT,string reaction,string projectile,int Z, int A,string Option)//запрашивает все данные C4, определяя MT из reaction и все возможные MF. Если reaction=="", запрашивается упругое рассеяние
{
	C4Container result;
	string filename;
	bool CloseBase=false;
	bool CloseROOT=false;
	//cout<<"reaction "<<reaction<<" "<<projectile<<"\n";
	if(getenv("C4Base"))
	{
		filename=string(getenv("C4Base"));
	}
	
	if(filename.size()>0)
	{
		if(filename[filename.size()-1]!='/')
		{
			filename+='/';
		}
	}
	string filenameROOT=filename+"Base.root";
	filename+="C4Base.db";
	
	if(projectile.size()==0)
	{
		cout<<"This is RequestC4DataSubentVector: projectile field is mandatory. Empty vector returned\n";
	}
	int PrjIndex=GetParticleID(projectile),MT=GetC4MT(reaction,projectile);
	if(PrjIndex==-1)
	{
		cout<<"This is RequestC4DataSubentVector: projectile is invalid: "<<projectile<<". Empty vector returned\n";
		return result;
	}
	if(MT==-1)
	{
		cout<<"This is RequestC4DataSubentVector: reaction is invalid: "<<reaction<<". Empty vector returned\n";
		return result;
	}
	if(!db)
	{
		sqlite3_open(filename.c_str(), &db); 
		CloseBase=true;
		
	}
	if(!BaseROOT)
	{
		BaseROOT=new TFile(filenameROOT.c_str());
		if(!BaseROOT)
		{
			cout<<"This is RequestC4DataSubentVector: cannot open root file base "<<filenameROOT<<"\n";
		}
	}
	//получим список возможных MF
	sqlite3_stmt *stmt;
	vector<string> TableList=GetListOfTables(db,"C%_"+to_string(MT)+"_"+to_string(PrjIndex));
	for(unsigned int i=0;i<TableList.size();i++)
	{
		TString Command;
		if(Option.find("A=0")!=string::npos)
		{
			Command=TString::Format(("SELECT SubEntry, DOI FROM "+TableList[i]+" WHERE Z=%d AND A=0").c_str(),Z);
		}
		else if(Option.find("A>=0")!=string::npos)
		{
			Command=TString::Format(("SELECT SubEntry, DOI FROM "+TableList[i]+" WHERE Z=%d AND ( A=%d OR A=0 )").c_str(),Z,A);
		}
		else
		{
			Command=TString::Format(("SELECT SubEntry, DOI FROM "+TableList[i]+" WHERE Z=%d AND A=%d").c_str(),Z,A);
		}
		sqlite3_prepare_v2(db,Command.Data(), -1, &stmt, NULL);
		while (1) 
		{
			int s;
			s = sqlite3_step (stmt);
			if (s == SQLITE_ROW) 
			{
				string Entry((char*)sqlite3_column_text (stmt, 0));
				string DOI((char*)sqlite3_column_text (stmt, 1));
				C4Entry *ent=(C4Entry*)BaseROOT->Get(Entry.c_str());
				if(ent)
				{
					ent->DOI=DOI;
					result.AddData(ent);
				}
			}
			else if (s == SQLITE_DONE) 
			{
				break;
			}
			else 
			{
				cout<<"GetListOfTables: Failed.\n";
				break;
			}
		}
	}
	if(CloseBase)
	{
		sqlite3_close(db);
	}
	if(CloseROOT)
	{
		BaseROOT->Close();
	}
	return result;
}
vector<double> C4Graph::GetProjectileEnergies()
{
	vector<double> result;
	if(this->InheritsFrom("C4EnergyDistribution"))
	{
		for(int i=0;i<GetN();i++)
		{
			double x,y;
			GetPoint(i,x,y);
			result.push_back(x);
		}
	}
	else if(this->InheritsFrom("C4AngularDistribution"))
	{
		result.push_back(ProjectileEnergy);
		return result;
	}
	sort( result.begin(), result.end() );
	result.erase( unique( result.begin(), result.end() ), result.end() );
	return result;
}
