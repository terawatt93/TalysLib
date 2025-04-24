#include "../TalysLib.hh"
#include <sys/stat.h>
#include "TalysLibManager.cc"
#include <bits/stdc++.h>
#include <cstring>
#include <algorithm>
#include <cctype>
#include "../Parser.cpp"
#include <TLine.h>
#include <TText.h>
#include <TList.h>
#include <TKey.h>
#include "SpinParity.cc"
#include "OMP.cc"
#include "Deformations.cc"
#include "GammaTransitions.cc"

#pragma once

string GetAOption(string Source)
{
	if(Source.find("A=0")!=string::npos)
	{
		return "A=0";
	}
	if(Source.find("A>=0")!=string::npos)
	{
		return "A>=0";
	}
	//return TalysLibManager::Instance().GetAOption();
	return "";
}

ENDFFile *GetENDFFile(Nucleus *fNucleus,string Source)
{
	if(!fNucleus)
	{
		cout<<"This is GetENDFFile(Nucleus *fNucleus,string Source): fNucleus pointer is invalid. Null returned\n";
		return 0;
	}
	ENDFFile *f=0;
	Source+=TalysLibManager::Instance().GetAOption();
	//обработка случая с A=0
	if(Source.find("A=0")!=string::npos)
	{
		TString tmp(Source.c_str());
		tmp.ReplaceAll("A=0","");
		tmp.ReplaceAll(" ","");
		f=fNucleus->GetPointerToENDFBase(tmp.Data());
		if(!f)
		{
			cout<<"This is GetENDFFile(Nucleus *fNucleus,string Source): cannot find base with name"<<tmp<<" Null returned\n";
			return 0;
		}
		if(!f->Read(fNucleus->Projectile,"0"+f->fNucleus->Element))
		{
			cout<<"This is GetENDFFile(Nucleus *fNucleus,string Source): cannot find file for "<<fNucleus->Projectile<<"+"<<f->fNucleus->Element<<"-0 Null returned\n";
			return 0;
		}
	}
	else if(Source.find("A>=0")!=string::npos)
	{
		TString tmp(Source.c_str());
		tmp.ReplaceAll("A>=0","");
		tmp.ReplaceAll(" ","");
		f=fNucleus->GetPointerToENDFBase(tmp.Data());
		if(!f)
		{
			cout<<"This is GetENDFFile(Nucleus *fNucleus,string Source): cannot find base with name"<<tmp<<" Null returned\n";
			return 0;
		}
		if(!f->Read(fNucleus->Projectile,f->fNucleus->Name))
		{
			cout<<"This is GetENDFFile(Nucleus *fNucleus,string Source): cannot find file for "<<fNucleus->Projectile<<"+"<<f->fNucleus->Name<<". Try with A=0\n";
			if(!f->Read(fNucleus->Projectile,"0"+f->fNucleus->Element))
			{
				cout<<"This is GetENDFFile(Nucleus *fNucleus,string Source): cannot find file for "<<fNucleus->Projectile<<"+"<<f->fNucleus->Element<<"-0 Null returned\n";
				return 0;
			}
		}
	}
	if(!f)
	{
		f=fNucleus->GetPointerToENDFBase(Source);
		if(!f)
		{
			cout<<"This is GetENDFFile(Nucleus *fNucleus,string Source): cannot find base "<<Source<<". Use A=0 or A>=0 to try with A=0. Null returned\n";
			return 0;
		}
		if(!f->Read(fNucleus->Projectile,f->fNucleus->Name))
		{
			cout<<"This is GetENDFFile(Nucleus *fNucleus,string Source): cannot find file for "<<fNucleus->Projectile<<"+"<<f->fNucleus->Name<<". Use A=0 or A>=0 to try with A=0. Null returned\n";
			return 0;
		}
	}
	return f;
	
}

EvaluatedDataGraph* FindInList(string Source, list<EvaluatedDataGraph> &List)
{
	string AOption=GetAOption(Source);
	TString SourceForSearch(Source.c_str());
	SourceForSearch.ReplaceAll(AOption.c_str(),"");
	SourceForSearch.ReplaceAll(" ","");
	for(auto i=List.begin();i!=List.end();i++)
	{
		EvaluatedDataGraph* g=&(*i);
		
		if(g->Source==string(SourceForSearch.Data()))
		{
			if((AOption=="A=0")&&(g->A==0))
			{
				return g;
			}
			else if((AOption!="A>=0")&&(g->A>0))//Случай, когда A>0
			{
				return g;
			}
			else
			{
				return g;
			}
			return &(*i);
		}
		
	}
	return 0;
}

EvaluatedDataGraph* EvaluatedData::GetAngularDistribution(string Source)
{
	EvaluatedDataGraph* result=FindInList(Source,EvaluatedAngularDistributions);
	if(result)
	{
		return result;
	}
	if(!fLevel)
	{
		cout<<"This is EvaluatedDataGraph::GetAngularDistribution(): pointer to level is not set. Null returned\n";
		return 0;
	}
	if(!fLevel->fNucleus)
	{
		cout<<"This is EvaluatedDataGraph::GetAngularDistribution(): pointer to fLevel->fNucleus is not set. Null returned\n";
		return 0;
	}
	ENDFFile *f=GetENDFFile(fLevel->fNucleus,Source);
	if(!f)
	{
		cout<<"This is EvaluatedDataGraph::GetAngularDistribution(): pointer to ENDFFile is invalid. Null returned\n";
		return 0;
	}
	string Projectile,Outgoing;
	ParseReaction(fLevel->fNucleus->Reaction,Projectile,Outgoing);
	if(fLevel->fNucleus->Reaction=="")//упругое рассеяние
	{
		Outgoing=fLevel->fNucleus->Projectile;
	}
	EvaluatedDataGraph g=f->GetAngularDistribution(Outgoing,fLevel->Number,f->fNucleus->ProjectileEnergy);
	g.fLevel=fLevel;
	EvaluatedAngularDistributions.push_back(g);
	return &(EvaluatedAngularDistributions.back());
}
EvaluatedDataGraph* EvaluatedData::GetEnergyDistribution(string Source)
{
	if(!fLevel)
	{
		cout<<"This is EvaluatedDataGraph::GetEnergyDistribution(): pointer to level is not set. Null returned\n";
		return 0;
	}
	EvaluatedDataGraph* result=FindInList(Source,EvaluatedEnergyDistributions);
	if(result)
	{
		return result;
	}
	if(!fLevel)
	{
		cout<<"This is EvaluatedDataGraph::GetEnergyDistribution(): pointer to level is not set. Null returned\n";
		return 0;
	}
	if(!fLevel->fNucleus)
	{
		cout<<"This is EvaluatedDataGraph::GetEnergyDistribution(): pointer to fLevel->fNucleus is not set. Null returned\n";
		return 0;
	}
	ENDFFile *f=GetENDFFile(fLevel->fNucleus,Source);
	if(!f)
	{
		cout<<"This is EvaluatedDataGraph::GetEnergyDistribution(): pointer to ENDFFile is invalid. Null returned\n";
		return 0;
	}
	string Projectile,Outgoing;
	ParseReaction(fLevel->fNucleus->Reaction,Projectile,Outgoing);
	if(fLevel->fNucleus->Reaction=="")//упругое рассеяние
	{
		Outgoing=fLevel->fNucleus->Projectile;
	}
	EvaluatedDataGraph g=f->GetCrossSections(Outgoing,fLevel->Number);
	g.fLevel=fLevel;
	EvaluatedEnergyDistributions.push_back(g);
	return &(EvaluatedEnergyDistributions.back());
}


//Методы класса Level
int Level::GetIntegrityFactor()
{
	int factor=0;
	if(fNucleus)//1
	{
		factor++;
		if(fNucleus->fMotherNucleus)//2
		{
			factor++;
			if(fNucleus->fMotherNucleus->fMaterial)//3
			{
				factor++;
			}
		}
	}
	return factor;
}
/*double& LevelData::AdditionalInformation(string Key)
{
	return AI(Key);
}*/
bool Level::ReadLevel(string line,string ReadNuclName)
{
	string type;
	stringstream s(line);
	s>>Nuclide>>type;
	
	char status;
	if(type=="L")
	{
		if(ReadNuclName==Nuclide)
		{
			Energy=atof(line.substr(9,9).c_str());
			EnergyErr=atof(line.substr(19,1).c_str());
			JP=line.substr(21,17);
			JP_values=ENSDFJPToNormalJP(JP,Mark);
			HalfLife=line.substr(39,9);
			HalfLifeErr=line.substr(49,5);
			status=line.substr(79,1)[0];
			if(status=='?')
			{
				return false;
			}
			return true;
		}
		return false;
	}
	else
	{
		return false;
	}
}
void Level::ReadTransition(string line)
{
	GammaTransition transition;
	if(transition.ReadTransition(line,Nuclide,Energy))
	{
		Gammas.push_back(transition);
		Gammas[Gammas.size()-1].fLevel=this;
	}
}
void Level::Reset()
{
	//Gammas.resize(0);
	ADTot.resize(0);
	ADDirect.resize(0);
	ADCompound.resize(0);
	Angle.resize(0);
	AngleLab.resize(0);
	CSValues.resize(0);
	CSCompoundValues.resize(0);
	CSDirectValues.resize(0);
	PlottedADist=false;
}
/*void Level::Print()
{
	cout<<"Level:"<< Energy<<" "<<JP<<"\n";
	for(unsigned int i=0;i<Gammas.size();i++)
	{
		cout<<Gammas[i].GetLine()<<"\n";
	}
}*/
bool Level::CheckEnergy(float E,float Tolerancy,float intensity)
{
	bool result=false;
	for(unsigned int i=0;i<Gammas.size();i++)
	{
		result=result||Gammas[i].CheckEnergy(E,Tolerancy,intensity);
	}
	return result;
}
void Level::AddLineFromTalys(double E, double CS)
{
	GammaTransition *g=0;
	for(unsigned int i=0;i<Gammas.size();i++)
	{
		if(abs(Gammas[i].Energy-E)<0.1)
		{
			g=&Gammas[i];
		}
	}
	if(!g)
	{
		GammaTransition gg;
		gg.Energy=E;
		Gammas.push_back(gg);
		g=&(Gammas[Gammas.size()-1]);
	}
	g->TalysCrossSection=CS;
	g->Origin="Talys";
	g->fLevel=this;
	
}
void Level::AddLineFromTalys(double E, double CS, double E_i, double E_f, SpinParity JP_i, SpinParity JP_f, unsigned int InitLevelNumber, unsigned int FinalLevelNumber)
{
	//GammaTransition g;
	
	GammaTransition *g=0;
	for(unsigned int i=0;i<Gammas.size();i++)
	{
		if(abs(Gammas[i].Energy-E)<0.1)
		{
			g=&Gammas[i];
		}
	}
	if(!g)
	{
		GammaTransition gg;
		gg.Energy=E;
		Gammas.push_back(gg);
		g=&(Gammas[Gammas.size()-1]);
	}
	
	//g.Energy=E;
	g->TalysCrossSection=CS;
	g->Origin="Talys";
	g->TalysE_i=E_i;
	g->TalysE_f=E_f;
	g->TalysJP_f=JP_f;
	g->TalysJP_i=JP_i;
	g->InitLevelNumber=InitLevelNumber;
	g->FinalLevelNumber=FinalLevelNumber;
	g->EvalMultipolarity();
	//Gammas.push_back(g);
}
vector<GammaTransition*> Level::GetTransition(float E,float Tolerancy,float intensity)
{
	vector<GammaTransition*> result;
	for(unsigned int i=0;i<Gammas.size();i++)
	{
		if(Gammas[i].CheckEnergy(E,Tolerancy,intensity))
		{
			result.push_back(&Gammas[i]);
			result[result.size()-1]->fLevel=this;
		}
	}
	return result;
}
const char *Level::GetName()  const
{
	return ("level_"+to_string(Energy)).c_str();
}
void Level::AssignPointers()
{
	for(unsigned int i=0;i<Gammas.size();i++)
	{
		Gammas[i].fLevel=this;
		if(fNucleus)
		{
			if(fNucleus->Levels.size()>Gammas[i].FinalLevelNumber)
			{
				Gammas[i].fFinalLevel=&(fNucleus->Levels[Gammas[i].FinalLevelNumber]);
				//fLevel->fNucleus->Levels.size()<Gammas[i].FinalLevelNumber
			}
		}
		//Gammas[i].fFinalLevel=0;
	}
}
//Методы для работы с данными класса Level: ввод
void Level::SetEnergy(float Energy)
{
	this->Energy=Energy;
}
void Level::SetEnergyErr(float EnergyErr)
{
	this->EnergyErr=EnergyErr;
}
void Level::SetTalysCS(float TalysCS)
{
	this->TalysCS=TalysCS;
}
void Level::SetTalysSpinParity(SpinParity TalysJP)
{
	this->TalysJP=TalysJP;
}
void Level::SetOrigin(string Origin)
{
	this->Origin=Origin;
}
void Level::AddJPValue(SpinParity JPValue)
{
	JP_values.push_back(JPValue);
}
void Level::AddSimilarLevel(Level* SimilarLevel)
{
	SimilarLevels.push_back(SimilarLevel);
}
//Методы для работы с данными класса Level: вывод
float Level::GetEnergy()
{
	return Energy;
}
float Level::GetEnergyErr()
{
	return EnergyErr;
}
float Level::GetTalysCS()
{
	return TalysCS;
}
SpinParity Level::GetTalysSpinParity()
{
	return TalysJP;
}
string Level::GetOrigin()
{
	return Origin;
}
vector<SpinParity>& Level::GetJPValues()
{
	return JP_values;
}
vector<Level*>& Level::GetSimilarLevels()
{
	return SimilarLevels;
}
void Level::ErasePointers()
{
	for(unsigned int i=0;i<Gammas.size();i++)
	{
		Gammas[i].ErasePointers();
	}
	SimilarLevels.resize(0);
	fNucleus=0;
}
LevelData Level::ToLevelData()
{
	LevelData result=(LevelData)(*this);
	for(unsigned int i=0;i<Gammas.size();i++)
	{
		result.GammasData.push_back((GammaTransitionData)Gammas[i]);
	}
	return result;
}
Level::Level(LevelData ld)
{
	deformation=0;
	Nuclide=ld.Nuclide; HalfLife=ld.HalfLife; HalfLifeErr=ld.HalfLifeErr; JP=ld.JP; Origin=ld.Origin;
	JP_values=ld.JP_values;
	AI=ld.AI;
	Mark=ld.Mark;//величина, определяющая достоверность уровня: размер вектора с JP, если JP.size=0, то Mark=99,если есть неопределенность (скобки), то размер ветора*2
	Energy=ld.Energy; EnergyErr=ld.EnergyErr, TalysCS=ld.TalysCS; TalysJP=ld.TalysJP;
	ADTot=ld.ADTot; ADDirect=ld.ADDirect; ADCompound=ld.ADCompound; Angle=ld.Angle; AngleLab=ld.AngleLab; Branching=ld.Branching;
	NumbersOfFinalLevels=ld.NumbersOfFinalLevels;
	
	CSValues=ld.CSValues; CSCompoundValues=ld.CSCompoundValues; CSDirectValues=ld.CSDirectValues;
	X_Values=ld.X_Values;
	ADTotValues=ld.ADTotValues;
	ADDirectValues=ld.ADDirectValues;
	ADCompoundValues=ld.ADCompoundValues;
	AngleLabValues=ld.AngleLabValues;
	
	for(unsigned int i=0;i<ld.GammasData.size();i++)
	{
		Gammas.emplace_back(ld.GammasData[i]);
	}
	
}
TGraph* Level::GetAngularDistribution(string type,string option)//если график уже построен, выдается сохраненный, если нет, или option=="new", строится заново
{
	/*if(fNucleus->fMotherNucleus)
	{
		if((Number==0)&&(fNucleus->fMotherNucleus->Name==fNucleus->Name))
		{
			return fNucleus->fMotherNucleus->GetElasticAngularDistribution(type,option);
		}
	}*/
	
	if((!PlottedADist)||(option=="new"))
	{
		bool ToLab=false;
		if(fNucleus)
		{
			if(fNucleus->fMotherNucleus)
			{
				ToLab=fNucleus->fMotherNucleus->ConvertToLab;
			}
			else
			{
				ToLab=fNucleus->ConvertToLab;
			}
		}
		if(ToLab)
		{
			AdistTotalTalys=TGraph(Angle.size(), &AngleLab[0], &ADTot[0]);
			AdistCompoundTalys=TGraph(Angle.size(), &AngleLab[0], &ADCompound[0]);
			AdistDirectTalys=TGraph(Angle.size(), &AngleLab[0], &ADDirect[0]);
		}
		else
		{
			//cout<<"Angle.size() "<<Angle.size()<<" "<<ADTot.size()<<"\n";
			AdistTotalTalys=TGraph(Angle.size(), &Angle[0], &ADTot[0]);
			AdistCompoundTalys=TGraph(Angle.size(), &Angle[0], &ADCompound[0]);
			AdistDirectTalys=TGraph(Angle.size(), &Angle[0], &ADDirect[0]);
		}
		string TotName="ADTotalTalysL"+to_string(Number);
		string CompName="ADCompTalysL"+to_string(Number);
		string DirName="ADDirTalysL"+to_string(Number);
		string InitNucleusName="";
		if(fNucleus->fMotherNucleus)
		{
			InitNucleusName=fNucleus->fMotherNucleus->Name;
		}
		TString TotTitle=TString::Format("Total #frac{d#sigma}{d#Omega} for %s%s%s, E_{l}=%.1f, JP=%s;Angle, deg;#frac{d#sigma}{d#Omega},mb",InitNucleusName.c_str(),(fNucleus->Reaction).c_str(),(fNucleus->Name).c_str(), Energy,TalysJP.GetLine().c_str());
		TString CompTitle=TString::Format("Compound #frac{d#sigma}{d#Omega} for %s%s%s, E_{l}=%.1f, JP=%s;Angle, deg;#frac{d#sigma}{d#Omega},mb",InitNucleusName.c_str(),(fNucleus->Reaction).c_str(),(fNucleus->Name).c_str(), Energy,TalysJP.GetLine().c_str());
		TString DirTitle=TString::Format("Direct #frac{d#sigma}{d#Omega} for %s%s%s, E_{l}=%.1f, JP=%s;Angle, deg;#frac{d#sigma}{d#Omega},mb",InitNucleusName.c_str(),(fNucleus->Reaction).c_str(),(fNucleus->Name).c_str(), Energy,TalysJP.GetLine().c_str());
		AdistTotalTalys.SetName(TotName.c_str());
		AdistCompoundTalys.SetName(CompName.c_str());
		AdistDirectTalys.SetName(DirName.c_str());
		
		AdistCompoundTalys.SetLineColor(2);
		AdistDirectTalys.SetLineColor(4);
		
		AdistTotalTalys.SetTitle(TotTitle);
		AdistCompoundTalys.SetTitle(CompTitle);
		AdistDirectTalys.SetTitle(DirTitle);
	}

	if(type=="Total")
	{
		return &AdistTotalTalys;
	}
	else if(type=="Compound")
	{
		return &AdistCompoundTalys;
	}
	else if(type=="Direct")
	{
		return &AdistDirectTalys;
	}
	else if(type=="ENDF")
	{
		type="ENDF-B-VIII.0";
	}
	//else//оцененные данные
	//{
		EVData.fLevel=this;
		return EVData.GetAngularDistribution(type);
	//}
	/*	if(AdistENDF.GetN()==0)
		{
			if(fNucleus)
			{
				if(!fNucleus->fMotherNucleus)
				{
					return 0;
				}
				string Projectile,Outgoing;
				ParseReaction(fNucleus->Reaction,Projectile,Outgoing);
				fNucleus->fMotherNucleus->ReadENDF();
				AdistENDF=fNucleus->fMotherNucleus->ENDF.GetAngularDistribution(Outgoing,Number,fNucleus->fMotherNucleus->ProjectileEnergy);
				AdistENDF.SetLineColor(6);
			}
		}
		return &AdistENDF;
	}*/
	return 0;
	
}
TMultiGraph* Level::GetTMultiGraphForAngularDistributions(string graphics)
{
	TMultiGraph* AllAngularDistributions=new TMultiGraph();
	GetAngularDistribution();//AdistTotalTalys, AdistCompoundTalys, AdistDirectTalys
	if(graphics=="all")
	{
		AllAngularDistributions->Add(GetAngularDistribution("Total"));
		AllAngularDistributions->Add(GetAngularDistribution("Direct"));
		AllAngularDistributions->Add(GetAngularDistribution("Compound"));
		AllAngularDistributions->Add(GetAngularDistribution("ENDF"));
	}
	else if((graphics.find("all")!=string::npos)&&(graphics.find("eval")!=string::npos))
	{
		vector<string> Bases;
		TalysLibManager *manager=TalysLibManager::GetPointer();
		if(manager->GetAOption()=="A=0")
		{
			Bases=ENDFFile::GetListOfBases(fNucleus->fMotherNucleus->Projectile,fNucleus->fMotherNucleus->Z,0);
		}
		else 
		{
			Bases=ENDFFile::GetListOfBases(fNucleus->fMotherNucleus->Projectile,fNucleus->fMotherNucleus->Z,fNucleus->fMotherNucleus->A);
			if(manager->GetAOption()=="A>=0")
			{
				vector<string> Bases0=ENDFFile::GetListOfBases(fNucleus->fMotherNucleus->Projectile,fNucleus->fMotherNucleus->Z,0);
				Bases.insert(Bases.end(), Bases0.begin(), Bases0.end());
			}
			
		}
		for(unsigned int i=0;i<Bases.size();i++)
		{
			cout<<"Get From "<<Bases[i]<<"\n";
			if((Bases[i]!="BROND-2-2")&&(Bases[i]!="JENDL-3.2"))//зависает! будем искать
			{
				TGraph *g=GetAngularDistribution(Bases[i]);
				if(g->GetN()>0)
				AllAngularDistributions->Add(g);
			}
			
		}
		
		stringstream sstr(graphics);
	}
	else
	{
		stringstream s_inp(graphics);
		while(s_inp)
		{
			string option;
			s_inp>>option;
			AllAngularDistributions->Add(GetAngularDistribution(option));
		}
	}
	/*else
	{
		if((int)graphics.find("Total")>-1)
		{
			AllAngularDistributions->Add(GetAngularDistribution("Total"));
		}
		if((int)graphics.find("Compound")>-1)
		{
			AllAngularDistributions->Add(GetAngularDistribution("Compound"));
		}
		if((int)graphics.find("Direct")>-1)
		{
			AllAngularDistributions->Add(GetAngularDistribution("Direct"));
		}
		if((int)graphics.find("ENDF")>-1)
		{
			AllAngularDistributions->Add(GetAngularDistribution("ENDF"));
		}
	}*/
	return AllAngularDistributions;
}

TMultiGraph* Level::GetTMultiGraphForCrossSections(string graphics)
{
	TMultiGraph* AllCrossSections=new TMultiGraph();
	GetAngularDistribution();//AdistTotalTalys, AdistCompoundTalys, AdistDirectTalys
	if(graphics=="all")
	{
		AllCrossSections->Add(GetCSGraph("Total"));
		AllCrossSections->Add(GetCSGraph("Direct"));
		AllCrossSections->Add(GetCSGraph("Compound"));
		AllCrossSections->Add(GetCSGraph("ENDF"));
	}
	else if((graphics.find("all")!=string::npos)&&(graphics.find("eval")!=string::npos))
	{
		vector<string> Bases;
		TalysLibManager *manager=TalysLibManager::GetPointer();
		if(manager->GetAOption()=="A=0")
		{
			Bases=ENDFFile::GetListOfBases(fNucleus->fMotherNucleus->Projectile,fNucleus->fMotherNucleus->Z,0);
		}
		else 
		{
			Bases=ENDFFile::GetListOfBases(fNucleus->fMotherNucleus->Projectile,fNucleus->fMotherNucleus->Z,fNucleus->fMotherNucleus->A);
			if(manager->GetAOption()=="A>=0")
			{
				vector<string> Bases0=ENDFFile::GetListOfBases(fNucleus->fMotherNucleus->Projectile,fNucleus->fMotherNucleus->Z,0);
				Bases.insert(Bases.end(), Bases0.begin(), Bases0.end());
			}
			
		}
		for(unsigned int i=0;i<Bases.size();i++)
		{
			TGraph *g=GetCSGraph(Bases[i]);
			if(g->GetN()>0)
			AllCrossSections->Add(g);
		}
		
		stringstream sstr(graphics);
	}
	else
	{
		stringstream s_inp(graphics);
		while(s_inp)
		{
			string option;
			s_inp>>option;
			AllCrossSections->Add(GetCSGraph(option));
		}
	}
	return AllCrossSections;
}

void Level::SetTGraphNameAndTitle(string ValName)
{
	if(ValName=="Energy")
	{
		ValName="E, MeV";
	}
	if(ValName=="Beta")
	{
		ValName="B";
	}
	
	TString Reac=fNucleus->ReactionInTLatexFormat();
	CSGraph.SetName(TString::Format("LVExTot_%s_%d",ValName.c_str(),Number));
	CSCompoundGraph.SetName(TString::Format("LVExComp_%s_%d",ValName.c_str(),Number));
	CSDirectGraph.SetName(TString::Format("LVExDir_%s_%d",ValName.c_str(),Number));
	CSGraph.SetTitle(TString::Format("#sigma_{ex}(%s) total,E_{level}=%.1f, %s;%s;#sigma,mb",ValName.c_str(),Energy,Reac.Data(),ValName.c_str()));
	CSCompoundGraph.SetTitle(TString::Format("#sigma_{ex}(%s) compound,E_{level}=%.1f, %s;%s;#sigma,mb",ValName.c_str(),Energy,Reac.Data(),ValName.c_str()));
	CSDirectGraph.SetTitle(TString::Format("#sigma_{ex}(%s) direct,E_{level}=%.1f, %s;%s;#sigma,mb",ValName.c_str(),Energy,Reac.Data(),ValName.c_str()));
	
	AdistTotalTalys2D.SetName(TString::Format("LVExTotAngle_%s_%d",ValName.c_str(),Number));
	AdistCompoundTalys2D.SetName(TString::Format("LVExCompAngle_%s_%d",ValName.c_str(),Number));
	AdistDirectTalys2D.SetName(TString::Format("LVExDirAngle_%s_%d",ValName.c_str(),Number));
	AdistTotalTalys2D.SetTitle(TString::Format("#frac{d #sigma_{ex}(%s)}{d #Omega} total,E_{level}=%.1f, %s;%s;Angle, deg;#frac{d #sigma_{ex}}{d #Omega},mb/str",ValName.c_str(),Energy,Reac.Data(),ValName.c_str()));
	AdistCompoundTalys2D.SetTitle(TString::Format("#frac{d #sigma_{ex}(%s)}{d #Omega} compound,E_{level}=%.1f, %s;%s;Angle, deg;#frac{d #sigma_{ex}}{d #Omega},mb/str",ValName.c_str(),Energy,Reac.Data(),ValName.c_str()));
	AdistDirectTalys2D.SetTitle(TString::Format("#frac{d #sigma_{ex}(%s)}{d #Omega} direct,E_{level}=%.1f, %s;%s;Angle, deg;#frac{d #sigma_{ex}}{d #Omega},mb/str",ValName.c_str(),Energy,Reac.Data(),ValName.c_str()));
	
	for(unsigned int i=0;i<Gammas.size();i++)
	{
		Gammas[i].SetTGraphNameAndTitle(ValName);
	}
}

void Level::SetDeformation(char LevT, int BandN, int BandL, int MagN, int NPhon, vector<double> *Def)
{
	if(deformation!=0)
	{
		deformation->NumberOfBand=BandN;
		deformation->TypeOfLevel=LevT;
		deformation->NumberOfLevel=Number;
		deformation->LOfBand=BandL;
		deformation->NumberOfPhonons=NPhon;
		deformation->MagneticNumber=MagN;
		
		if(Def!=0)
		{
			deformation->Beta.resize(0);
			for(unsigned int i=0;i<Def->size(); i++)
			{
				deformation->Beta.push_back(Def->at(i));
			}
		}
		deformation->fLevel=this;
	}
	else
	{
		if(!fNucleus)
		{
			cout<<"Error: deformation cannot be assigned to standalone level! (fNucleus does not set). Returned\n";
			return ;
		}
		LevelDeformation d;
		d.NumberOfBand=BandN;
		d.TypeOfLevel=LevT;
		d.NumberOfLevel=Number;
		d.LOfBand=BandL;
		d.NumberOfPhonons=NPhon;
		d.MagneticNumber=MagN;
		d.fLevel=this;
		if(Def)
		{
			d.Beta=*Def;
		}
		fNucleus->Def.LevelDeformations.push_back(d);
		deformation=&(fNucleus->Def.LevelDeformations[fNucleus->Def.LevelDeformations.size()]);
		//fNucleus->Def.AssignPointers();
		fNucleus->Def.Sort();
	}
}

vector<double> Level::GetDeformationBeta()
{//Level->LevelDeformation->Beta
	vector<double> result;
	if(deformation!=0)
	{
		return deformation->Beta;
	}
	else
	{
		cout<<"Level::GetDeformationBeta() error: level deformation is not defined. Return empty vector! \n";
		return result;
	}
}

void Level::AddPoint(double x_value,Level *level)
{
	//cout<<"AddPoint: "<<x_value<<"\n";
	if(!level)
	{
		//cout<<"AddPoint: "<<x_value<<"\n";
		return ;
	}
	
	if(Number!=level->Number)
	{
		//cout<<"AddPoint: "<<x_value<<" "<<level->Number<<"\n";
		return ;
	}
	
	for(unsigned int i=0;i<Gammas.size();i++)
	{
		for(unsigned int j=0;j<level->Gammas.size();j++)
		{
			Gammas[i].AddPoint(x_value,&(level->Gammas[j]));
		}
	}
	//int N=CSGraph.GetN();
	//cout<<"AddPoint: "<<level->fNucleus->fMotherNucleus->ProjectileEnergy<<"\n";
	CSValues.push_back(level->TalysCS);
	CSCompoundValues.push_back(level->TalysCSCompound);
	CSDirectValues.push_back(level->TalysCSDirect);
	X_Values.push_back(x_value);
	
	for(unsigned int i=0;i<level->Angle.size();i++)
	{
		//int N2=AdistTotalTalys2D.GetN();
		AddPointToTGraph(&AdistTotalTalys2D, x_value,level->Angle[i],level->ADTot[i]);
		AddPointToTGraph(&AdistCompoundTalys2D, x_value,level->Angle[i],level->ADCompound[i]);
		AddPointToTGraph(&AdistDirectTalys2D, x_value,level->Angle[i],level->ADDirect[i]);
	}

	IsGraphGenerated=false;
	AddPointToTGraph(&CSGraph, x_value,level->TalysCS); 
	AddPointToTGraph(&CSCompoundGraph, x_value,level->TalysCSCompound);
	AddPointToTGraph(&CSDirectGraph, x_value,level->TalysCSDirect);
}

void Level::AddPoint(Level *level)
{
	//cout<<"AddPoint1:\n";
	if(!level)
	{
	//	cout<<"AddPoint2:\n";
		return ;
	}
	
	if(Number!=level->Number)
	{
	//	cout<<"AddPoint3:"<<level->Number<<"\n";
		return ;
	}
	
	for(unsigned int i=0;i<Gammas.size();i++)
	{
		for(unsigned int j=0;j<level->Gammas.size();j++)
		{
			Gammas[i].AddPoint(&(level->Gammas[j]));
		}
	}
	//cout<<"AddPoint4:"<<level->Number<<"\n";
	int N=CSGraph.GetN();
	CSValues.push_back(level->TalysCS);
	CSCompoundValues.push_back(level->TalysCSCompound);
	CSDirectValues.push_back(level->TalysCSDirect);
	//cout<<"AddPoint5:"<<level->ADTot.size()<<" "<<level->Angle.size()<<"\n";
	ADTotValues.push_back(level->ADTot); ADDirectValues.push_back(level->ADDirect); ADCompoundValues.push_back(level->ADCompound);
	Angle=level->Angle;
	double ProjEnergy=0;
	if(level->GetIntegrityFactor()>1)
	{
		//IsGraphGenerated=false;
		ProjEnergy=level->fNucleus->fMotherNucleus->ProjectileEnergy;
		CSGraph.SetPoint(N,ProjEnergy,level->TalysCS); 
		CSCompoundGraph.SetPoint(N,ProjEnergy,level->TalysCSCompound);
		CSDirectGraph.SetPoint(N,ProjEnergy,level->TalysCSDirect);
		for(unsigned int i=0;i<level->Angle.size();i++)
		{
			int N2=AdistTotalTalys2D.GetN();
			AdistTotalTalys2D.SetPoint(N2,ProjEnergy,level->Angle[i],level->ADTot[i]);
			AdistCompoundTalys2D.SetPoint(N2,ProjEnergy,level->Angle[i],level->ADCompound[i]);
			AdistDirectTalys2D.SetPoint(N2,ProjEnergy,level->Angle[i],level->ADDirect[i]);
		}
	}
	
}


TGraph* Level::GetCSGraph(string type)
{
	TGraph* result = 0;
	
	if(type=="Total")
	{
		if((Energy==0)&&(fNucleus->IsProduct()))
		{
			return fNucleus->fMotherNucleus->GetCrossSectionGraph("Elastic");
		}
		result=&CSGraph;
	}
	if(type=="Compound")
	{
		result=&CSCompoundGraph;
	}
	if(type=="Direct")
	{
		result=&CSDirectGraph;
	}
	else if(type=="ENDF")
	{
		type="ENDF-B-VIII.0";
	}
	if(result)
	{
		return result;
	}
	EVData.fLevel=this;
	return EVData.GetEnergyDistribution(type);
	/*if(type=="ENDF")
	{
		if(CSENDFGraph.GetN()==0)
		{
			if(fNucleus)
			{
				if(!fNucleus->fMotherNucleus)
				{
					return 0;
				}
				string Projectile,OutgoingParticle;
				ParseReaction(fNucleus->Reaction,Projectile,OutgoingParticle);
				fNucleus->fMotherNucleus->ReadENDF();
				CSENDFGraph=fNucleus->fMotherNucleus->ENDF.GetCrossSections(OutgoingParticle,Number);
				result=&CSENDFGraph;
			}
		}
	}*/
	return result;
}
TGraph2D* Level::GetAngularDistribution2D(string type,string option)//если график уже построен, выдается сохраненный, если нет, или option=="new", строится заново
{
	bool ToLab=false;
	if((!PlottedADist2D)||(option=="new"))
	{
		if(fNucleus)
		{
			if(fNucleus->fMotherNucleus)
			{
				ToLab=fNucleus->fMotherNucleus->ConvertToLab;
			}
			else
			{
				ToLab=fNucleus->ConvertToLab;
			}
		}
		int PointIterator=0;
		vector<double> *x=0;
		if(X_Values.size()!=0)
		{
			x=&X_Values;
		}
		else
		{
			x=&(fNucleus->fMotherNucleus->EnergyGrid);
		}
		if(ToLab)
		{
			for(unsigned int i=0;i<x->size();i++)
			{
				for(unsigned int j=0;j<AngleLabValues[i].size();j++)
				{
					if(AngleLabValues.size()>i)
					{
						if(AngleLabValues[i].size()>j)
						{
							AdistTotalTalys2D.SetPoint(PointIterator,x->at(i),AngleLabValues[i][j],ADTotValues[i][j]);
							AdistCompoundTalys2D.SetPoint(PointIterator,x->at(i),AngleLabValues[i][j],ADDirectValues[i][j]);
							AdistDirectTalys2D.SetPoint(PointIterator,x->at(i),AngleLabValues[i][j],ADCompoundValues[i][j]);
							PointIterator++;
						}
					}
				}
			}
		}
		else
		{
			for(unsigned int i=0;i<x->size();i++)
			{
				for(unsigned int j=0;j<Angle.size();j++)
				{
					if(AngleLabValues.size()>i)
					{
						if(AngleLabValues[i].size()>j)
						{
							AdistTotalTalys2D.SetPoint(PointIterator,x->at(i),Angle[j],ADTotValues[i][j]);
							AdistCompoundTalys2D.SetPoint(PointIterator,x->at(i),Angle[j],ADDirectValues[i][j]);
							AdistDirectTalys2D.SetPoint(PointIterator,x->at(i),Angle[j],ADCompoundValues[i][j]);
							PointIterator++;
						}
					}
				}
			}
		}
		string TotName="ADTotalTalysL2D"+to_string(Number);
		string CompName="ADCompTalysL2D"+to_string(Number);
		string DirName="ADDirTalysL2D"+to_string(Number);
		TString TotTitle=TString::Format("Total #frac{d#sigma}{d#Omega} for %s%s%s, E_{l}=%.1f, JP=%s; E, MeV;Angle, deg;#frac{d#sigma}{d#Omega},mb",(fNucleus->fMotherNucleus->Name).c_str(),(fNucleus->Reaction).c_str(),(fNucleus->Name).c_str(), Energy,TalysJP.GetLine().c_str());
		TString CompTitle=TString::Format("Compound #frac{d#sigma}{d#Omega} for %s%s%s, E_{l}=%.1f, JP=%s; E, MeV; Angle, deg;#frac{d#sigma}{d#Omega},mb",(fNucleus->fMotherNucleus->Name).c_str(),(fNucleus->Reaction).c_str(),(fNucleus->Name).c_str(), Energy,TalysJP.GetLine().c_str());
		TString DirTitle=TString::Format("Direct #frac{d#sigma}{d#Omega} for %s%s%s, E_{l}=%.1f, JP=%s; E, MeV; Angle, deg;#frac{d#sigma}{d#Omega},mb",(fNucleus->fMotherNucleus->Name).c_str(),(fNucleus->Reaction).c_str(),(fNucleus->Name).c_str(), Energy,TalysJP.GetLine().c_str());
		AdistTotalTalys2D.SetName(TotName.c_str());
		AdistCompoundTalys2D.SetName(CompName.c_str());
		AdistDirectTalys2D.SetName(DirName.c_str());
		
		AdistCompoundTalys2D.SetLineColor(2);
		AdistDirectTalys2D.SetLineColor(4);
		AdistENDF.SetLineColor(6);
		
		AdistTotalTalys2D.SetTitle(TotTitle);
		AdistCompoundTalys2D.SetTitle(CompTitle);
		AdistDirectTalys2D.SetTitle(DirTitle);
	}

	if(type=="Total")
	{
		return &AdistTotalTalys2D;
	}
	if(type=="Compound")
	{
		return &AdistCompoundTalys2D;
	}
	if(type=="Direct")
	{
		return &AdistDirectTalys2D;
	}
	
	return 0;
	
}
TGraph* Level::GetAngularDistributionAtEnergy(float PrEnergy,string type,string option)
{
	if(fNucleus->fMotherNucleus->ProjectileEnergy==PrEnergy)
	{
		return GetAngularDistribution();
	}
	TGraph2D *refGraph=GetAngularDistribution2D(type,option);
	if((PrEnergy>=fNucleus->fMotherNucleus->MinEnergy)&&(PrEnergy<=fNucleus->fMotherNucleus->MaxEnergy))
	{
		TGraph result;
		for(unsigned int i=0;i<Angle.size();i++)
		{
			result.SetPoint(i,Angle[i],refGraph->Interpolate(PrEnergy,Angle[i]));
		}
		result.SetName(TString::Format("Inelastic_at_E%.1f_E_level_%.1f",PrEnergy,Energy));
		TString Title=TString::Format("%s #frac{d#sigma_{%s}}{d#Omega} for E_{%s}=%.1f MeV, E_{l}=%.1f keV; #theta, deg; #frac{d#sigma}{d#Omega}, mb/str",fNucleus->Reaction.c_str(),type.c_str(),fNucleus->fMotherNucleus->Projectile.c_str(),PrEnergy,Energy);
		result.SetTitle(Title);
		GeneratedGraphsList.push_back(result);
		return &(GeneratedGraphsList.back());
	}
	else//пока не работает из-за того, что GenerateProducts все очищает. Переделать потом
	{
		if(fNucleus->fMotherNucleus->EnergyGrid.size()==0)
		{
			fNucleus->fMotherNucleus->EnergyGrid.push_back(fNucleus->fMotherNucleus->ProjectileEnergy);
		}
		if(fNucleus->fMotherNucleus->EnergyGrid.size()>0)
		{
			fNucleus->fMotherNucleus->EnergyGrid.push_back(PrEnergy);
			fNucleus->fMotherNucleus->MainNucleusFlag=0;
			
			fNucleus->fMotherNucleus->GenerateProducts(fNucleus->fMotherNucleus->Projectile);
			return GetAngularDistributionAtEnergy(PrEnergy,type,option);
		}
	}
	return 0;
}

vector<TGraphErrors*> Level::GetEXFORAngularDistributions(double Emin,double Emax, bool GenerateHLink)
{
	vector<TGraphErrors*> result;
	cout<<"TalysLibManager::Instance().GetEXFORSource() "<<TalysLibManager::Instance().GetEXFORSource()<<"\n";
	if(TalysLibManager::Instance().GetEXFORSource()==0)
	{
		if(Number>40)//потом разобраться с MT!
		{
			return result;
		}
		if(GetIntegrityFactor()>1)
		{
			EXFORManager m;
			string Projectile;
			int Z=fNucleus->fMotherNucleus->Z;
			int A=fNucleus->fMotherNucleus->A;
			string OutgoingParticle;
			ParseReaction(fNucleus->Reaction,Projectile,OutgoingParticle);
			EXFORAngularDistributions=m.GetEXFORAngularDistributions(Projectile,Z,A,OutgoingParticle,Number);
			int MarkerStyle=20;
			int MarkerColor=1;
			for(unsigned int i=0;i<EXFORAngularDistributions.size();i++)
			{
				if(!TalysLibManager::Instance().IsInExcludedAuthors(EXFORAngularDistributions[i].Author))
				{
					if(((EXFORAngularDistributions[i].ProjectileEnergy>Emin)&&(EXFORAngularDistributions[i].ProjectileEnergy<Emax))||((Emin==0)&&(Emax==0)))
					{
						TGraphErrors *gr=EXFORAngularDistributions[i].GetTGraph();
						
						MarkerColor++;
						if(MarkerColor==5)
						{
							MarkerColor++;
						}
						if(MarkerColor==9)
						{
							MarkerStyle++;
							MarkerColor=1;
						}
						if(gr)
						{
							gr->SetMarkerStyle(MarkerStyle);
							gr->SetMarkerColor(MarkerColor);
							result.push_back(gr);
						}
					}
				}
			}
		}
	}
	if(TalysLibManager::Instance().GetEXFORSource()==1)
	{
		TalysLibManager *manager=TalysLibManager::GetPointer();
		if(!manager->GetC4Flag())
		{
			if(GetIntegrityFactor()>=2)
			{
				fNucleus->fMotherNucleus->ReadC4();
			}
		}
		if(GenerateHLink)
		{
			HyperlinksTMP.resize(0);
		}
		Level *PointerToLevel=this;
		if((fNucleus->OutgoingParticle==fNucleus->Projectile)&&(Energy==0))
		{
			if(GetIntegrityFactor()<2)
			{
				cout<<"This is Level::GetEXFORAngularDistributions(): attempt to retrieve data for elastic scattering failed because fMotherNucleus is invalid!\n";
			}
			else
			{
				PointerToLevel=&(fNucleus->fMotherNucleus->Levels[0]);
			}
		}
		for(unsigned int i=0;i<PointerToLevel->C4AngularData.size();i++)
		{
			//cout<<"C4AngularData[i].ProjectileEnergy/1e6 "<<C4AngularData[i].ProjectileEnergy/1e6<<"\n";
			
			bool Add=true;
			if((manager->ThereAreIncludedSubentries())||(manager->ThereAreIncludedAuthors()))
			{
				Add=false;
				if(manager->IsInIncludedAuthors(PointerToLevel->C4AngularData[i].Author1)||manager->IsInIncludedSubEntries(PointerToLevel->C4AngularData[i].DataSet))
				{
					Add=true;
				}
			}
			if((manager->IsInExcludedAuthors(PointerToLevel->C4AngularData[i].Author1))||(manager->IsInExcludedSubEntries(PointerToLevel->C4AngularData[i].DataSet)))
			{
				Add=false;
			}
			if((((PointerToLevel->C4AngularData[i].ProjectileEnergy/1e6>Emin)&&(PointerToLevel->C4AngularData[i].ProjectileEnergy/1e6<Emax))||((Emax==0)&&(Emin==0)))&&Add)
			{
				if(GenerateHLink)
				{
					HyperlinksTMP.push_back(string(PointerToLevel->C4AngularData[i].GetTitle())+";"+PointerToLevel->C4AngularData[i].DOI);
				}
				result.push_back(&(PointerToLevel->C4AngularData[i]));
			}
		}
	}
	return result;
}
vector<TGraphErrors*> Level::GetEXFORCrossSections(double Emin,double Emax, bool GenerateHLink)
{
	vector<TGraphErrors*> result;
	if(TalysLibManager::Instance().GetEXFORSource()==0)
	{
		if(Number>40)
		{
			return result;
		}
		if(GetIntegrityFactor()>1)
		{
			EXFORManager m;
			int Z=fNucleus->fMotherNucleus->Z;
			int A=fNucleus->fMotherNucleus->A;
			string OutgoingParticle;
			string Projectile;
			ParseReaction(fNucleus->Reaction,Projectile,OutgoingParticle);
			EXFORCrossSections=m.GetEXFORCrossSections(Projectile,Z,A,OutgoingParticle,Number);
			int MarkerStyle=20;
			int MarkerColor=1;
			for(unsigned int i=0;i<EXFORCrossSections.size();i++)
			{
				if(!TalysLibManager::Instance().IsInExcludedAuthors(EXFORCrossSections[i].Author))
				{
					if(((EXFORCrossSections[i].Emax>Emin)&&(EXFORCrossSections[i].Emin<Emax))||((Emin==0)&&(Emax==0)))
					{
						TGraphErrors *gr=EXFORCrossSections[i].GetTGraph();
						MarkerColor++;
						if(MarkerColor==5)
						{
							MarkerColor++;
						}
						if(MarkerColor==9)
						{
							MarkerStyle++;
							MarkerColor=1;
						}
						if(gr)
						{
							gr->SetMarkerStyle(MarkerStyle);
							gr->SetMarkerColor(MarkerColor);
							result.push_back(gr);
						}
					}
				}
			}
		}
	}
	if(TalysLibManager::Instance().GetEXFORSource()==1)
	{
		if(GenerateHLink)
		{
			HyperlinksTMP.resize(0);
		}
		Level *PointerToLevel=this;
		if((fNucleus->OutgoingParticle==fNucleus->Projectile)&&(Energy==0))
		{
			if(GetIntegrityFactor()<2)
			{
				cout<<"This is Level::GetEXFORCrossSections(): attempt to retrieve data for elastic scattering failed because fMotherNucleus is invalid!\n";
			}
			else
			{
				PointerToLevel=&(fNucleus->fMotherNucleus->Levels[0]);
			}
		}
		for(unsigned int i=0;i<PointerToLevel->C4EnergyData.size();i++)
		{
			//if(((C4EnergyData[i].ProjectileEnergy/1e3>Emin)&&(C4EnergyData[i].ProjectileEnergy/1e3<Emax))||((Emax==0)&&(Emin==0)))
			{
				TalysLibManager *manager=TalysLibManager::GetPointer();
				bool Add=true;
				if((manager->ThereAreIncludedSubentries())||(manager->ThereAreIncludedAuthors()))
				{
					Add=false;
					if(manager->IsInIncludedAuthors(PointerToLevel->C4EnergyData[i].Author1)||manager->IsInIncludedSubEntries(PointerToLevel->C4EnergyData[i].DataSet))
					{
						Add=true;
					}
				}
				if((manager->IsInExcludedAuthors(PointerToLevel->C4EnergyData[i].Author1))||(manager->IsInExcludedSubEntries(PointerToLevel->C4EnergyData[i].DataSet)))
				{
					Add=false;
				}
				if(Add)
				{
					if(GenerateHLink)
					{
						HyperlinksTMP.push_back(string(PointerToLevel->C4EnergyData[i].GetTitle())+";"+PointerToLevel->C4EnergyData[i].DOI);
					}
					result.push_back(&(PointerToLevel->C4EnergyData[i]));
				}
			}
		}
	}
	return result;
}
TMultiGraph* Level::GetEXFORTMultiGraphForAngularDistributions(double Emin,double Emax,string Option)
{
	TMultiGraph* mgr=new TMultiGraph();
	vector<TGraphErrors*> Graphs=GetEXFORAngularDistributions(Emin,Emax);
	for(unsigned int i=0;i<Graphs.size();i++)
	{
		if((Option.find("LAB")!=string::npos)||(Option.find("CM")!=string::npos))
		{
			C4Graph *gr=(C4Graph*)Graphs[i];
			if(Option.find("LAB")!=string::npos)
			{
				if(!gr->CM)
				{
					mgr->Add(Graphs[i],"p");
				}
			}
			if(Option.find("CM")!=string::npos)
			{
				if(gr->CM)
				{
					mgr->Add(Graphs[i],"p");
				}
			}
		}
		else
		{
			mgr->Add(Graphs[i],"p");
		}
		
	}
	return mgr;
}
TMultiGraph* Level::GetEXFORTMultiGraphForCrossSections(double Emin,double Emax,string Option)
{
	TMultiGraph* mgr=new TMultiGraph();
	vector<TGraphErrors*> Graphs=GetEXFORCrossSections(Emin,Emax);
	for(unsigned int i=0;i<Graphs.size();i++)
	{
		if((Option.find("LAB")!=string::npos)||(Option.find("CM")!=string::npos))
		{
			C4Graph *gr=(C4Graph*)Graphs[i];
			if(Option.find("LAB")!=string::npos)
			{
				if(!gr->CM)
				{
					mgr->Add(Graphs[i],"p");
				}
			}
			if(Option.find("CM")!=string::npos)
			{
				if(gr->CM)
				{
					mgr->Add(Graphs[i],"p");
				}
			}
		}
		else
		{
			mgr->Add(Graphs[i],"p");
		}
	}
	return mgr;
}

void Level::EvalAlternativeAdist()
{
	//Полина!
	CalculatedAlternativeAdist=true;
	if(GetIntegrityFactor()>=2)//есть начальное ядро
	{
		ST_Matrix s_mat=fNucleus->fMotherNucleus->s_mat;
		if(!s_mat.WasRead)
		{
			Gammas[0].TalysAngularDistribution=TF1(TString::Format("ADist_g%.d",int(10*Gammas[0].Energy)),"0",0,180);
			AlternativeAdist=TF1(TString::Format("ADist_n%.d",int(Energy)),"0",0,180);
		}
		map<tuple<int, int, int>, double> D; // write results of coefficients to map


		for (int Q = 0; Q < 6; Q += 2){
			for (int lam1 = 0; lam1 < 7; lam1++) {
				for (int lam = abs(Q - lam1); lam <= Q + lam1; lam++) {
				
					Dlam dl(lam, lam1, Q);
	              
					dl.addS(s_mat);
					//dl.addT(s_mat);
					if (dl.pr_result() != 0) { 
					    D[make_tuple(lam, lam1, Q)] = dl.pr_result(); 
						//fprintf(tf,"%d %d %d %f %f\n",lam,lam1,Q, dl.pr_result(),dl.pr_result()*(2*lam+1));
					}
				}
			}
		}
		TString neutron; 
		TString gamma;
		
		double ProjEnergy=fNucleus->fMotherNucleus->ProjectileEnergy;
		double ProjMass=fNucleus->fMotherNucleus->ProjectileMass;
		double CMenergy = 12.01;
		double k2=2*ProjMass*CMenergy/pow(197.3,2)/10.0;
		
		for(auto &i: D)
		{	
			auto j = i.first;
			int lam = get<0>(j),
				lam1 = get<1>(j),
				Q = get<2>(j);
				//для расчета сечений!!
			
			if(Q == 0)
			{
				if(i.second>0) neutron+="+";
				neutron+=TString::Format("%f*legendre(%d,cos(3.14*x/180))",1.0/(k2*4)*i.second*(2*lam+1),lam);

			}
			if(lam1 == 0)
			{	
				if(i.second>0) gamma+="+";
				gamma+=TString::Format("%f*legendre(%d,cos(3.14*x/180))",1.0/(k2*4)*i.second*(2*Q+1),Q);
			}
			//модификация закончена
		}
		char c {'+'};
		neutron.Remove(TString::kLeading,c);
		gamma.Remove(TString::kLeading,c);
		//cout<<"k2="<<k2<<"\n";
		//cout<<gamma<<endl;
		//cout<<"neutron "<<endl;
		//cout<<neutron<<endl;

		if(Gammas.size()>0)
		{
			Gammas[0].TalysAngularDistribution=TF1(TString::Format("ADist_g%.d",int(10*Gammas[0].Energy)),gamma,0,180);
		}
		AlternativeAdist=TF1(TString::Format("ADist_n%.d",int(Energy)),neutron,0,180);
	}
}

void ExtractHyperlinkAndTitle(string inp, string &title,string &href)
{
	int titleLength=inp.find(";");
	if(titleLength!=-1)
	{
		title=inp.substr(0,titleLength);
		href=inp.substr(titleLength+1);
	}
}
void Level::AddHyperlinksToTeX(string &filename,string href_addition)
{
	vector<string> FileContent;
	string line;
	bool WillWriteToFile=true;
	if((filename.find("\"")==string::npos)&&(filename.find(".tex")==string::npos))//в качестве аргумента передано содержание .tex файла
	{
		WillWriteToFile=false;
		stringstream s(filename);
		while(getline(s,line))
		{
			FileContent.push_back(line);
		}
	}
	else//заменяется текст в файле
	{
		WillWriteToFile=true;
		ifstream ifs(filename);
		while(getline(ifs,line))
		{
			FileContent.push_back(line);
		}
		ifs.close();
	}
	
	ofstream ofs;
	if(WillWriteToFile)
	{
		ofs.open(filename);
		ofs<<"\\documentclass[class=minimal,border=0pt]{standalone}\n\\usepackage{hyperref}\n\\hypersetup{\ncolorlinks=true,\nurlcolor=cyan}\n\\usepackage{tikz}\n\\begin{document}\n";
	}
	
	for(unsigned int i=0;i<FileContent.size();i++)
	{
		if(FileContent[i].find("]{")!=string::npos)
		{
			for(unsigned int j=0;j<HyperlinksTMP.size();j++)
			{
				string title,href;
				ExtractHyperlinkAndTitle(HyperlinksTMP[j],title,href);
				if(href.size()>0)
				{
					if(FileContent[i].find(title)!=string::npos)
					{
						TString ts(FileContent[i].c_str());
						if(href.size()>1)
						{
							ts.ReplaceAll(title.c_str(),("\\href{"+href_addition+href+"}{"+title+"}").c_str());
							FileContent[i]=string(ts.Data());
						}
						
					}
				}
			}
			
		}
	}
	if(!WillWriteToFile)
	{
		filename="";
	}
	for(unsigned int i=0;i<FileContent.size();i++)
	{
		if(WillWriteToFile)
		{
			ofs<<FileContent[i]<<"\n";
		}
		else
		{
			filename+=(FileContent[i]+"\n");
		}
	}
	if(WillWriteToFile)
	{
		ofs<<"\\end{document}";
		ofs.close();
	}
}
int Level::GetMT()
{
	if(GetIntegrityFactor()>1)
	{
		if(fNucleus->IsProduct())
		{
			string Projectile,Outgoing;
			ParseReaction(fNucleus->Reaction,Projectile,Outgoing);
			if(Number<49)
			{
				return GetAdditionIndex(Projectile,Outgoing,Number);
			}
			return -6;
		}
	}
	return 0;
}

/*
vector<EnergyDistribution> Level::GetEnergyDistributionInRange(double emin, double emax)
{
	vector<EnergyDistribution> result;
	for(EnergyDistribution ed: C5EnergyDistribution){
		if(ed.InRange(emin, emax))
			result.push_back(ed);
	}
	return result;
}
*/

/*
vector<TGraphErrors*> Level::GetEnergyDistributionGraph(double Emin, double Emax)
{
	vector<TGraphErrors*> result;
	TalysLibManager *manager=TalysLibManager::GetPointer();
	for(unsigned int j=0;j<C5EnergyDistribution.size();j++)
	{
		bool InRange=false;
		bool Add=true;
		for(int i=0;i<C5EnergyDistribution[j]->GetN();i++)
		{
			if(C5EnergyDistribution[j]->GetPointX(i) >= Emin && C5EnergyDistribution[j]->GetPointX(i) <= Emax)
			{
				if(manager->IsInExcludedSubEntries(C5EnergyDistribution[j]->fSubent->SubentID))
				{
					Add = false;
				}
				InRange=true;
				break;
			}
		}
		if(InRange == true && Add == true)
		{
			result.push_back(C5EnergyDistribution[j]);
		}
		
	}
	return result;
} 

vector<TGraphErrors*> Level::GetAngularDistributionGraph(double Emin, double Emax)
{
	vector<TGraphErrors*> result;
	TalysLibManager *manager=TalysLibManager::GetPointer();
	for(unsigned int i=0;i<C5AngularDistribution.size();i++)
	{
		if(C5AngularDistribution[i]->En >= Emin && C5AngularDistribution[i]->En <= Emax)
		{
			bool Add = true;
			if(manager->IsInExcludedSubEntries(C5AngularDistribution[i]->fSubent->SubentID))
			{
				Add = false;
			}
			if(Add)
			{
				result.push_back(C5AngularDistribution[i]);
			}
		}
	}
	return result;
} 
*/

vector<AngularDistribution*> Level::GetAngularDistribution_v2(double E_min, double E_max)
{
	vector<AngularDistribution*> result;
	for(size_t i=0; i<C5AngularDistribution.size(); i++)
	{
		for(auto& point: C5AngularDistribution[i].data_points)
		{
			if(point[0] >= E_min && point[0] <= E_max)
			{
				double n = C5AngularDistribution[i].graph.GetN();
				C5AngularDistribution[i].graph.SetPoint(n, point[1], point[2]);
				C5AngularDistribution[i].graph.SetPointError(n, point[3], point[4]);
			}
		}
		if(C5AngularDistribution[i].graph.GetN() != 0)
		{
			result.push_back(&C5AngularDistribution[i]);
		}
	}
	return result;
}

