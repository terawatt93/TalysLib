#include "../TalysLib.hh"
#include <sys/stat.h>

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

//Методы класса Level
double& LevelData::AdditionalInformation(string Key)
{
	return AI(Key);
}
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
	Gammas.resize(0);
	ADTot.resize(0);
	ADDirect.resize(0);
	ADCompound.resize(0);
	Angle.resize(0);
	AngleLab.resize(0);
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
	GammaTransition g;
	g.Energy=E;
	g.TalysCrossSection=CS;
	g.Origin="Talys";
	Gammas.push_back(g);
	Gammas[Gammas.size()-1].fLevel=this;
	
}
void Level::AddLineFromTalys(double E, double CS, double E_i, double E_f, SpinParity JP_i, SpinParity JP_f, unsigned int InitLevelNumber, unsigned int FinalLevelNumber)
{
	GammaTransition g;
	g.Energy=E;
	g.TalysCrossSection=CS;
	g.Origin="Talys";
	g.TalysE_i=E_i;
	g.TalysE_f=E_f;
	g.TalysJP_f=JP_f;
	g.TalysJP_i=JP_i;
	g.InitLevelNumber=InitLevelNumber;
	g.FinalLevelNumber=FinalLevelNumber;
	Gammas.push_back(g);
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
		Gammas[i].fFinalLevel=0;
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
	
	float Energy, EnergyErr, TalysCS, TalysCSCompound, TalysCSDirect, OutgoingParticleEnergy; SpinParity TalysJP;
	ADTot=ld.ADTot; ADDirect=ld.ADDirect; ADCompound=ld.ADCompound; Angle=ld.Angle; AngleLab=ld.AngleLab; Branching=ld.Branching;
	NumbersOfFinalLevels=ld.NumbersOfFinalLevels;
	for(unsigned int i=0;i<ld.GammasData.size();i++)
	{
		Gammas.emplace_back(ld.GammasData[i]);
	}
}
TGraph* Level::GetAngularDistribution(string type,string option)//если график уже построен, выдается сохраненный, если нет, или option=="new", строится заново
{
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
			AdistTotalTalys=TGraph(Angle.size(), &Angle[0], &ADTot[0]);
			AdistCompoundTalys=TGraph(Angle.size(), &Angle[0], &ADCompound[0]);
			AdistDirectTalys=TGraph(Angle.size(), &Angle[0], &ADDirect[0]);
		}
		string TotName="ADTotalTalysL"+to_string(Number);
		string CompName="ADCompTalysL"+to_string(Number);
		string DirName="ADDirTalysL"+to_string(Number);
		TString TotTitle=TString::Format("Total #frac{d#sigma}{d#Omega} for %s%s%s, E_{l}=%.1f, JP=%s;Angle, deg;#frac{d#sigma}{d#Omega},mb",(fNucleus->fMotherNucleus->Name).c_str(),(fNucleus->Reaction).c_str(),(fNucleus->Name).c_str(), Energy,TalysJP.GetLine().c_str());
		TString CompTitle=TString::Format("Compound #frac{d#sigma}{d#Omega} for %s%s%s, E_{l}=%.1f, JP=%s;Angle, deg;#frac{d#sigma}{d#Omega},mb",(fNucleus->fMotherNucleus->Name).c_str(),(fNucleus->Reaction).c_str(),(fNucleus->Name).c_str(), Energy,TalysJP.GetLine().c_str());
		TString DirTitle=TString::Format("Direct #frac{d#sigma}{d#Omega} for %s%s%s, E_{l}=%.1f, JP=%s;Angle, deg;#frac{d#sigma}{d#Omega},mb",(fNucleus->fMotherNucleus->Name).c_str(),(fNucleus->Reaction).c_str(),(fNucleus->Name).c_str(), Energy,TalysJP.GetLine().c_str());
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
	if(type=="Compound")
	{
		return &AdistCompoundTalys;
	}
	if(type=="Direct")
	{
		return &AdistDirectTalys;
	}
	return 0;
	
}
TMultiGraph* Level::GetTMultiGraphForAngularDistributions(string graphics)
{
	TMultiGraph* AllAngularDistributions=new TMultiGraph();
	GetAngularDistribution();//AdistTotalTalys, AdistCompoundTalys, AdistDirectTalys
	TGraph* elastic;
	if(fNucleus->fMotherNucleus)
	{
		elastic=fNucleus->fMotherNucleus->GetElasticAngularDistribution("Total");
	}
	else if(fNucleus)
	{
		elastic=fNucleus->GetElasticAngularDistribution("Total");
	}
	if(graphics=="all")
	{
		AllAngularDistributions->Add(&AdistTotalTalys);
		AllAngularDistributions->Add(&AdistCompoundTalys);
		AllAngularDistributions->Add(&AdistDirectTalys);
		/*if(elastic)
		{
			AllAngularDistributions->Add(elastic);
		}*/
	}
	else
	{
		if((int)graphics.find("Total")>-1)
		{
			AllAngularDistributions->Add(&AdistTotalTalys);
		}
		if((int)graphics.find("Compound")>-1)
		{
			AllAngularDistributions->Add(&AdistCompoundTalys);
		}
		if((int)graphics.find("Direct")>-1)
		{
			AllAngularDistributions->Add(&AdistDirectTalys);
		}
		if((int)graphics.find("Elastic")>-1)
		{
			AllAngularDistributions->Add(elastic);
		}
	}
	return AllAngularDistributions;
}

void Level::SetTGraphNameAndTitle(string ValName)
{
	if(ValName=="Energy")
	{
		ValName="E";
	}
	if(ValName=="Beta")
	{
		ValName="B";
	}
	CSGraph.SetName(TString::Format("LVExTot_%s_%d",ValName.c_str(),Number));
	CSCompoundGraph.SetName(TString::Format("LVExComp_%s_%d",ValName.c_str(),Number));
	CSDirectGraph.SetName(TString::Format("LVExDir_%s_%d",ValName.c_str(),Number));
	CSGraph.SetTitle(TString::Format("#sigma_{ex}(%s) total,E_{level}=%.1f;%s;#sigma,mb",ValName.c_str(),Energy,ValName.c_str()));
	CSCompoundGraph.SetTitle(TString::Format("#sigma_{ex}(%s) compound,E_{level}=%.1f;%s;#sigma,mb",ValName.c_str(),Energy,ValName.c_str()));
	CSDirectGraph.SetTitle(TString::Format("#sigma_{ex}(%s) direct,E_{level}=%.1f;%s;#sigma,mb",ValName.c_str(),Energy,ValName.c_str()));
	for(unsigned int i=0;i<Gammas.size();i++)
	{
		Gammas[i].SetTGraphNameAndTitle(ValName);
	}
}

void Level::SetDeformation(char LevT, int BandN, int BandL, int NPhon, int MagN, vector<float> *Def)
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

void Level::AddPoint(double x_value,Level *level)
{
	if(!level)
	return ;
	if(Number!=level->Number)
	return ;
	for(unsigned int i=0;i<Gammas.size();i++)
	{
		for(unsigned int j=0;j<level->Gammas.size();j++)
		{
			Gammas[i].AddPoint(x_value,&(level->Gammas[j]));
		}
	}
	int N=CSGraph.GetN();
	CSGraph.SetPoint(N,x_value,level->TalysCS); 
	CSCompoundGraph.SetPoint(N,x_value,level->TalysCSCompound);
	CSDirectGraph.SetPoint(N,x_value,level->TalysCSDirect);
}

TGraph* Level::GetCSGraph(string type)
{
	TGraph* result = 0;
	if(type=="Total")
	{
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
	return result;
}
