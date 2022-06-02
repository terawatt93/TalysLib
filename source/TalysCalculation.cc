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
#include "LevelProperties.cc"
#include "NucleiProperties.cc"


#pragma once

void TalysCalculation::ReadParametersFromFile(string filename)
{
	ifstream ifs(filename.c_str());
	string line;
	while(getline(ifs,line))
	{
		if(line.find("#")==string::npos)
		{
			if(line.find("Target:")!=string::npos)
			{
				stringstream s(line);
				s>>line>>Target;
			}
			if(line.find("Variation:")!=string::npos)// Например, Variation: Energy 0 15 1
			{
				stringstream s(line);
				double min, max, step,v=0;
				s>>line>>Variable>>min>>max>>step;
				v=min;
				while(v<=max)
				{
					VarValues.push_back(v);
					v+=step;
				}
			}
			if(line.find("Energy:")!=string::npos)
			{
				stringstream s(line);
				s>>line>>ProjectileEnergy;
			}
			if(line.find("Projectile:")!=string::npos)
			{
				stringstream s(line);
				s>>line>>Proj;
			}
			if(line.find("ProjectileEnergy:")!=string::npos)
			{
				stringstream s(line);
				s>>line>>ProjectileEnergy;
			}
			if(line.find("Option:")!=string::npos)
			{
				TalysOptions.push_back(line.substr(7,line.size()-7));
			}
		}
	}
}

void TalysCalculation::SetVarValues(double min,double max,double step)
{
	VarValues.resize(0);
	double value=min;
	if(step==0)
	{
		cout<<"This is TalysCalculation::SetVarValues(): step should be > 0\n";
		return ;
	}
	while(value<max)
	{
		VarValues.push_back(value);
		value+=step;
	}
}

void TalysCalculation::ExecuteCalculation()
{
	if(VarValues.size()>0)
	{
		Nucleus Nucl(Target);
		Nucl.Projectile=Proj;
		Nucl.TalysOptions=TalysOptions;
		for(unsigned int i=0;i<VarValues.size();i++)
		{
			if(Variable=="Energy")
			{
				Nucl.SetProjectileEnergy(VarValues[i]);
				Results.push_back(Nucl);
			}else if(Variable.find("Beta")!=string::npos)
			{
				TString ts(Variable);
				ts.ReplaceAll("_"," ");
				stringstream s(ts.Data());
				string tmp; int LevNumber, BetaIndex;
				s>>tmp>>LevNumber>>BetaIndex;
				
			}
			//позже тут будут и другие параметры
		}
		for(unsigned int i=0;i<Results.size();i++)
		{
			Results[i].GenerateProducts(Proj);
		}
	}
}

void EvalInThread(TalysCalculation *c,unsigned int index)
{
	c->Results[index].GenerateProducts(c->Results[index].Projectile);
}

void TalysCalculation::ExecuteCalculation(void (*VarChangeFunction)(Nucleus *Nuclide,double value))
{
	if(EnableMultiThreading)
	{
		ROOT::EnableThreadSafety();
	}
	if(VarValues.size()>0)
	{
		Nucleus Nucl(Target);
		Nucl.Projectile=Proj;
		Nucl.TalysOptions=TalysOptions;
		Nucl.ProjectileEnergy=ProjectileEnergy;
		//Nucl.GenerateProducts(Proj);
		Nucl.fTalysCalculation=this;
		for(unsigned int i=0;i<VarValues.size();i++)
		{
			VarChangeFunction(&Nucl,VarValues[i]);
			if(EnableMultiThreading)
			{
				Nucl.SetThreadNumber(i);
			}
			Results.push_back(Nucl);
		}
		if(EnableMultiThreading)
		{
			vector<thread> threads;
			for(unsigned int i=0;i<Results.size();i++)
			{
				threads.emplace_back(EvalInThread,this,i);
			}
			for(unsigned int i=0;i<Results.size();i++)
			{
				threads[i].join();
			}
		}
		else
		{
			for(unsigned int i=0;i<Results.size();i++)
			{
				Results[i].GenerateProducts(Proj);
			}
		}
	}
}

void TalysCalculation::ExecuteCalculation(void (*VarChangeFunction)(Nucleus *Nuclide,vector<double> &value),vector<vector<double> > &VariableValues)
{
	Results.resize(0);
	VarValues.resize(0);
	for(unsigned int i=0;i<VariableValues.size();i++)
	{
		Nucleus Nucl(Target);
		Nucl.Projectile=Proj;
		Nucl.TalysOptions=TalysOptions;
		Nucl.ProjectileEnergy=ProjectileEnergy;
		Nucl.fTalysCalculation=this;
		VarChangeFunction(&Nucl,VariableValues[i]);
		Results.push_back(Nucl);
		VarValues.push_back(i);
	}
	for(unsigned int i=0;i<Results.size();i++)
	{
		Results[i].GenerateProducts(Proj);
	}
}


void TalysCalculation::GenerateGraphs()
{
	if(Results.size()==0)
	{
		cout<<"TalysCalculation::GenerateGraphs() error: size of Results vector = 0; execute ReadParametersFromFile first\n";
		return ;
	}
	FinalResult=&Results[Results.size()-1];
	FinalResult->SetTGraphNameAndTitle(Variable);
	for(unsigned int i=0;i<Results.size();i++)
	{
		FinalResult->AddPoint(VarValues[i],&Results[i]);
	}
	GeneratedGraphs=true;
}

TGraph* TalysCalculation::GetLevelExcitationCrossSection(double LevelEnergy,string NucleusName,string Option)
{
	if(!GeneratedGraphs)
	{
		GenerateGraphs();
	}
	Nucleus* PointerToNucleus=FinalResult->FindProductByName(NucleusName);
	if(!PointerToNucleus)
	{
		cout<<"TalysCalculation::GetLevelExcitationCrossSection(...) error: Nucleus "<<NucleusName<<" not found in Products! 0 returned\n";
		return 0;
	}
	Level* l=PointerToNucleus->FindLevelByEnergy(LevelEnergy,0.5);
	if(!l)
	{
		cout<<"TalysCalculation::GetLevelExcitationCrossSection(...) error: Level with energy "<<LevelEnergy<<" not found in "<<PointerToNucleus->Name<<", 0 returned\n";
		return 0;
	}
	return l->GetCSGraph(Option);
}

TGraph* TalysCalculation::GetGammaTransitionCrossSction(double GammaEnergy,string NucleusName)
{
	if(!GeneratedGraphs)
	{
		GenerateGraphs();
	}
	Nucleus* PointerToNucleus=FinalResult->FindProductByName(NucleusName);
	if(!PointerToNucleus)
	{
		cout<<"TalysCalculation::GetGammaTransitionCrossSction(...) error: Nucleus "<<NucleusName<<" not found in Products! 0 returned\n";
		return 0;
	}
	GammaTransition *g=PointerToNucleus->GetBestTransition(GammaEnergy,0.5);
	if(!g)
	{
		cout<<"GetGammaTransitionCrossSction(...) error: Gamma with energy "<<GammaEnergy<<" not found in "<<PointerToNucleus->Name<<", 0 returned\n";
		return 0;
	}
	return g->GetCSGraph();
}
TMultiGraph* TalysCalculation::GetAngularDistributionsForLevel(double LevelEnergy,string NucleusName,string type,string option,TLegend *leg)
{
	TMultiGraph* result=0;
	if(!GeneratedGraphs)
	{
		GenerateGraphs();
	}
	Nucleus* PointerToNucleus=FinalResult->FindProductByName(NucleusName);
	if(!PointerToNucleus)
	{
		cout<<"TalysCalculation::GetAngularDistributionsForLevel(...) error: Nucleus "<<NucleusName<<" not found in Products! 0 returned\n";
		return 0;
	}
	Level *l=PointerToNucleus->FindLevelByEnergy(LevelEnergy,0.5);
	if(!l)
	{
		cout<<"TalysCalculation::GetAngularDistributionsForLevel(...) error: Level with energy "<<LevelEnergy<<" not found in "<<PointerToNucleus->Name<<", 0 returned\n";
		return 0;
	}
	
	if(Results.size()>0)
	{
		TGraph *g=l->GetAngularDistribution(type,option);
		result=new TMultiGraph();
		result->SetName(g->GetName());
		result->SetTitle(g->GetTitle());
	}
	for(unsigned int i=0;i<Results.size();i++)
	{
		Nucleus* PTN=Results[i].FindProductByName(NucleusName);
		Level *li=PTN->FindLevelByEnergy(LevelEnergy,0.5);
		TGraph *g=li->GetAngularDistribution(type,option);
		if(type=="Total")
		{
			g->SetLineColor(kViolet-9+i);
		}
		if(type=="Compound")
		{
			g->SetLineColor(kAzure-9+i);
		}
		if(type=="Direct")
		{
			g->SetLineColor(kOrange-9+i);
		}
		result->Add(g);
		if(leg)
		{
			leg->AddEntry(g,TString::Format("%s=%f",Variable.c_str(),VarValues[i]));
		}
	}
	return result;
}
TMultiGraph* TalysCalculation::GetElasticAngularDistributions(string type,string option,TLegend *leg)//выдает TMultiGraph с угловыми распределениями, соответствующими значениям VarValues
{
	TMultiGraph* result=0;
	if(!GeneratedGraphs)
	{
		GenerateGraphs();
	}
	if(Results.size()==0)
	{
		cout<<"TalysCalculation::GetElasticAngularDistributions(...) error! Vector of Results is empty, Execute ExecuteCalculation(...) first! 0 returned \n";
		return 0;
	}
	TGraph *g=Results[0].GetElasticAngularDistribution(type,option);
	result=new TMultiGraph();
	result->SetName(g->GetName());
	result->SetTitle(g->GetTitle());
	for(unsigned int i=0;i<Results.size();i++)
	{
		TGraph *gi=Results[i].GetElasticAngularDistribution(type,option);
		if(type=="Total")
		{
			gi->SetLineColor(kViolet-9+i);
		}
		if(type=="Compound")
		{
			gi->SetLineColor(kAzure-9+i);
		}
		if(type=="Direct")
		{
			gi->SetLineColor(kOrange-9+i);
		}
		result->Add(gi);
		if(leg)
		{
			leg->AddEntry(gi,TString::Format("%s=%f",Variable.c_str(),VarValues[i]));
		}
	}
	return result;
}
/*
void TalysCalculation::ExecuteCalculation()
{
	for(unsigned int i=0;i<Results.size();i++)
	{
		Results[i].GenerateProducts(Proj);
	}
	ElasticOnE=TGraph("ElasticOnE","#sigma_{el}(E);E,MeV;#sigma");
	InelasticOnE=TGraph("InelasticOnE","#sigma_{inl}(E);E,MeV;#sigma");
	for(unsigned int i=0;i<Energies.size();i++)
	{
		//ElasticOnE.SetPoint(i,Energies[i],
	}
}*/
