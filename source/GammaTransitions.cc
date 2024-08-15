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

#pragma once

//Методы класса GammaTransition
/*double& GammaTransitionData::AdditionalInformation(string Key)
{
	return AI(Key);
}*/
GammaTransition::GammaTransition(GammaTransitionData d)
{
	Energy=d.Energy; EnergyErr=d.EnergyErr; Intensity=d.Intensity; CrossSection=d.CrossSection; E_in=d.E_in; Tolerancy=d.Tolerancy;
	Rel_Cs=d.Rel_Cs; TalysCrossSection=d.TalysCrossSection; TalysE_i=d.TalysE_i; TalysE_f=d.TalysE_f;
	TalysJP_i=d.TalysJP_i; TalysJP_f=d.TalysJP_f;
	TalysMultipolarity=d.TalysMultipolarity;
	Multipolarity=d.Multipolarity; nuclide=d.nuclide; reaction=d.reaction;
	AI=d.AI;
	TalysCrossSections=d.TalysCrossSections;
	X_Values=d.X_Values;
}
bool GammaTransition::ReadTransition(string line,string ReadNuclName, float E_in)
{
	this->E_in=E_in;
	//123SB G 381.4 4 100 8 [M1] 0.0170
	string nuclide; string type;
	stringstream s(line);
	s>>nuclide>>type;
	if(type=="G")
	{
		if(ReadNuclName==nuclide)
		{
			Energy=atof(line.substr(9,9).c_str());
			EnergyErr=atof(line.substr(19,1).c_str());
			Intensity=atof(line.substr(21,7).c_str());
			Multipolarity=line.substr(31,9);
			if(Intensity>100)
			{
				Intensity=0;
			}
			Origin="ENSDF";
			return true;
		}
		return false;
	}
	else
	{
		return false;
	}
}
string GammaTransition::GetLine(string option)
{
	if(Multipolarity=="")
	{
		Multipolarity="unknown";
	}
	if(option=="brief")
	{
		return (to_string(Energy)+" "+to_string(Intensity)+" "+to_string(CrossSection)+" "+to_string(TalysCrossSection));
	}
	else if(option=="full")
	{
		string result;
		result=to_string(Energy)+" "+to_string(TalysCrossSection)+" "+fLevel->fNucleus->fMotherNucleus->Name+fLevel->fNucleus->Reaction+fLevel->fNucleus->Name+" "+to_string(TalysE_i)+"("+TalysJP_i.GetLine()+"->"+TalysJP_f.GetLine()+")"+to_string(TalysE_f);
		return result;
	}
	else if(option.find("custom")!=string::npos)
	{
		stringstream sstr(option);
		string tmp;
		sstr>>tmp;
		string result;
		while(sstr)
		{
			string tmp_opt;
			sstr>>tmp_opt;
			if(tmp_opt=="E")
			{
				result+=string(TString::Format("%.2f",Energy).Data())+" ";
			}
			if(tmp_opt=="CS")
			{
				result+="#sigma:"+string(TString::Format("%.2f",TalysCrossSection).Data())+" mb ";
			}
			if(tmp_opt=="REACTION")
			{
				if(fLevel)
				{
					if(fLevel->fNucleus)
					{
						if(fLevel->fNucleus->fMotherNucleus)
						{
							result+=string((fLevel->fNucleus->ReactionInTLatexFormat("short")).Data())+" ";
						}
					}
				}
			}
			if(tmp_opt=="CS*ABUN")
			{
				if(fLevel)
				{
					if(fLevel->fNucleus)
					{
						if(fLevel->fNucleus->fMotherNucleus)
						{
							result+="#sigma*AB:"+string(TString::Format("%.2f",TalysCrossSection*fLevel->fNucleus->fMotherNucleus->Abundance).Data())+" mb ";
						}
					}
				}
			}
			if(tmp_opt=="CS*ABUN*SHARE")
			{
				if(fLevel)
				{
					if(fLevel->fNucleus)
					{
						if(fLevel->fNucleus->fMotherNucleus)
						{
							if(fLevel->fNucleus->fMotherNucleus->fMaterial)
							{
								result+="#sigma*AB*%:"+string(TString::Format("%.2f",TalysCrossSection*fLevel->fNucleus->fMotherNucleus->Abundance*fLevel->fNucleus->fMotherNucleus->fMaterial->GetMoleFraction(fLevel->fNucleus->fMotherNucleus)).Data())+" mb ";
							}
						}
					}
				}
			}
			if(tmp_opt=="LEV")
			{
				result+=string(TString::Format("%.1f",TalysE_i))+"("+TalysJP_i.GetLine()+"->"+TalysJP_f.GetLine()+")"+string(TString::Format("%.1f",TalysE_f))+" ";
			}
		}
		return result;
	}
	
	return ("E:"+to_string(Energy)+" Mult:"+Multipolarity+"Int:"+to_string(Intensity)+" CS:"+to_string(CrossSection)+" Talys:"+to_string(TalysCrossSection));
}
bool GammaTransition::CheckEnergy(float E,float Tolerancy,float intensity)
{
	this->Tolerancy=Tolerancy;
	if((abs(Energy-E)<=Tolerancy)&&((Intensity>intensity)||(Intensity==0)))
	{
		return true;
	}
	return false;
}
const char *GammaTransition::GetName()  const
{
//	return ("line_"+to_string(Energy)).c_str();
	string Name("line_"+TString::Format("%.2f",Energy));
	return Name.c_str();
}

void GammaTransition::SetInformationExtractedFromTalys(float TalysE_f, float TalysE_i, SpinParity JP_f, SpinParity JP_i)
{
	this->TalysE_f=TalysE_f;
	this->TalysE_i=TalysE_i;
	this->TalysJP_f=JP_f;
	this->TalysJP_i=JP_i;
	EvalMultipolarity();
}
double GammaTransition::GetEnergy()
{
	return Energy;
}
double GammaTransition::GetIntensity()
{
	return Intensity;
}
double GammaTransition::GetRelativeIntensity()
{
	Radionuclide *Nucl=(Radionuclide*)fLevel->fNucleus;
	double BranchRatio=1;
	if(Nucl)
	{
		while((((Radionuclide*)Nucl->fMotherNucleus)->BranchRatio)>0)
		{			
		//	cout<<"GetRelativeIntensity():"<<Nucl->fMotherNucleus->Name<<" "<<Energy<<" "<<BranchRatio<<" "<<((Radionuclide*)Nucl->fMotherNucleus)->BranchRatio<<"\n";
			Nucl=Nucl->fMotherNucleus;
			BranchRatio=BranchRatio*Nucl->BranchRatio;
		}
	}
	return Intensity*BranchRatio;
}
void GammaTransition::FindFinalLevel(double Tolerancy)
{
	if(!fLevel)
	{
		return ;
	}
	
	if(Origin=="Talys")
	{
		if(fLevel->fNucleus)
		{
			for(unsigned int i=0;i<fLevel->fNucleus->Levels.size();i++)
			{
				if((fLevel->fNucleus->Levels[i].Origin=="Talys")||(fLevel->fNucleus->Levels[i].Energy==0))
				{
					if(fLevel->Energy>fLevel->fNucleus->Levels[i].Energy)
					{
						//cout<<"This is GammaTransition::FindFinalLevel("<<Tolerancy<<")\n";
						//cout<<"fLevel->Energy="<<fLevel->Energy<<" fNucleus->Levels[i].Energy="<<fLevel->fNucleus->Levels[i].Energy<<" Energy="<<Energy<<" abs="<<abs(fLevel->Energy-fLevel->fNucleus->Levels[i].Energy-Energy)<<"\n";
						double E_distance=fLevel->Energy-fLevel->fNucleus->Levels[i].Energy;
						if(abs(E_distance-Energy)<Tolerancy)
						{
							fFinalLevel=&(fLevel->fNucleus->Levels[i]);
							//cout<<"Final level found!\n";
							return;
						}
					}
				}
			}
		}
	}
	
	/*
	if(TalysCrossSection>10e-3)
	{
		fFinalLevel=0;
		if(fLevel->JP_values.size()>0)
		{
			fLevel->JP_values[0]=TalysJP_i;
		}
		else
		{
			fLevel->JP_values.push_back(TalysJP_i);
		}		
		if(fLevel->fNucleus)
		{
			Nucleus *Nucl=fLevel->fNucleus;
			for(unsigned int i=0;i<Nucl->LevelsFromTalys.size();i++)
			{
				if(fLevel->GetOrigin()=="Talys")
				{
					if(abs(fLevel->GetEnergy()-Nucl->LevelsFromTalys[i]->GetEnergy())<1)
					{
						fFinalLevel=Nucl->LevelsFromTalys[i];
						fFinalLevel->JP_values[0]=TalysJP_f;
						return ;
					}
				}
			}
			
			
			for(unsigned int i=0;i<Nucl->LevelsFromENSDF.size();i++)
			{
				if((abs(Nucl->LevelsFromENSDF[i]->GetEnergy()-Energy)<Tolerancy)&&(Nucl->Levels[i].GetJPValues().size()>0))
				{
					fFinalLevel=Nucl->LevelsFromENSDF[i];
				}
			}
		}
		if(fFinalLevel)
		{
			fFinalLevel->JP_values[0]=TalysJP_f;
		}
	}
	else
	{
		if(fLevel->fNucleus)
		{
			Nucleus *Nucl=fLevel->fNucleus;
			double E_final=fLevel->Energy-Energy;
			cout<<Energy<<" "<<E_final<<" "<<fLevel->JP_values.size()<<"\n";
			fFinalLevel=0;
			unsigned int iterator=0;
			while((!fFinalLevel)&&(iterator<fLevel->JP_values.size()))
			{
				fFinalLevel=Nucl->FindBestLevelByEJP(Energy,fLevel->JP_values[iterator],3);
				iterator++;
			}
		}
	}*/
}
void GammaTransition::EvalMultipolarity()
{
	SpinParity GammaMP(1,-1);
	TalysMultipolarity=SpinParity::QSum(TalysJP_i,TalysJP_f,GammaMP);
}
void GammaTransition::ErasePointers()
{
	fLevel=0;
	fFinalLevel=0;
}
void GammaTransition::SetTGraphNameAndTitle(string ValName)
{
	if(ValName=="Energy")
	{
		ValName="E";
	}
	if(ValName=="Beta")
	{
		ValName="B";
	}
	CSGraph.SetName(("GTCS_"+ValName).c_str());
	CSGraph.SetTitle(TString::Format("#sigma_{#gamma}(%s),E_{#gamma}=%.1f;%s;#sigma,mb",ValName.c_str(),Energy,ValName.c_str()));
}
void GammaTransition::AddPoint(double x_value, double y_value)
{
	//int N=CSGraph.GetN();
	//CSGraph.SetPoint(N,x_value,y_value);
	TalysCrossSections.push_back(y_value);
	X_Values.push_back(x_value);
	IsCSGraphGenerated=false;
}
void GammaTransition::AddPoint(double x_value, GammaTransition *g)
{
	if(!g)
	return;
	if((g->InitLevelNumber==InitLevelNumber)&&(g->FinalLevelNumber==FinalLevelNumber))
	{
		AddPoint(x_value,g->TalysCrossSection);
		IsCSGraphGenerated=false;
	}
}
void GammaTransition::AddPoint(GammaTransition *g)
{
	if((g->InitLevelNumber==InitLevelNumber)&&(g->FinalLevelNumber==FinalLevelNumber))
	{
		TalysCrossSections.push_back(g->TalysCrossSection);
		IsCSGraphGenerated=false;
	}
}
SpinParity GammaTransition::GetMostProbableMultipolarity()
{
	if(TalysMultipolarity.size()>0)
	{
		if(pow(-1,TalysMultipolarity[0].J)==TalysMultipolarity[0].Parity)//EJ
		{
			return TalysMultipolarity[0];
		}
		else//MJ
		{
			if(TalysMultipolarity.size()>1)
			{
				return TalysMultipolarity[1];
			}
			else
			{
				return TalysMultipolarity[0];
			}
		}
	}
	return 0;
}
void GammaTransition::GenerateGraphs()
{
	if(X_Values.size()!=TalysCrossSections.size())
	{
		if(!fLevel)
		{
			cout<<"This is GammaTransition::GenerateGraphs(): Graph generation error. Cannot access fLevel because pointer is invalid\n";
			return;
		}
		if(!fLevel->fNucleus)
		{
			cout<<"This is GammaTransition::GenerateGraphs(): Graph generation error. Cannot access fLevel->fNucleus because pointer fNucleus is invalid\n";
			return;
		}
		if(!fLevel->fNucleus->fMotherNucleus)
		{
			cout<<"This is GammaTransition::GenerateGraphs(): Graph generation error. Cannot access fLevel->fNucleus->fMotherNucleus because pointer fMotherNucleus is invalid\n";
			return;
		}
		if(!IsCSGraphGenerated)
		{
			for(unsigned int i=0;i<TalysCrossSections.size();i++)
			{
				AddPointToTGraph(&CSGraph,fLevel->fNucleus->fMotherNucleus->EnergyGrid[i],TalysCrossSections[i]);
			}
		}
	}
	else
	{
		for(unsigned int i=0;i<TalysCrossSections.size();i++)
		{
			AddPointToTGraph(&CSGraph,X_Values[i],TalysCrossSections[i]);
		}
	}
}
TGraph* GammaTransition::GetCSGraph()
{
	if(CSGraph.GetN()==0)
	{
		GenerateGraphs();
	}
	return &CSGraph;
}
int GammaTransition::GetIntegrityFactor()
{
	int factor=0;
	if(fLevel)
	{
		factor++;
		if(fLevel->fNucleus)
		{
			factor++;
			if(fLevel->fNucleus->fMotherNucleus)
			{
				factor++;
				if(fLevel->fNucleus->fMotherNucleus->fMaterial)
				{
					factor++;
				}
			}
		}
	}
	return factor;
	
}
double GammaTransition::GetTalysYield()
{
	if(GetIntegrityFactor()==4)
	{
		GammaTransition *MostIntense=fLevel->fNucleus->fMotherNucleus->fMaterial->GetMostIntenseGammaTransition();
		if(!MostIntense)
		{
			return 0;
		}
		vector<GammaTransition*> MostIntenseGammas=fLevel->fNucleus->fMotherNucleus->fMaterial->FindGammaTransitions(MostIntense->Energy);
		double NormFactor=0;
		for(unsigned int i=0;i<MostIntenseGammas.size();i++)
		{
			NormFactor+=MostIntenseGammas[i]->TalysCrossSection*MostIntenseGammas[i]->fLevel->fNucleus->fMotherNucleus->fMaterial->GetMoleFraction(MostIntenseGammas[i]->fLevel->fNucleus->fMotherNucleus);
		}
		return TalysCrossSection*fLevel->fNucleus->fMotherNucleus->fMaterial->GetMoleFraction(fLevel->fNucleus->fMotherNucleus)/NormFactor;
		//vector<GammaTransition*> Gammas=fLevel->fNucleus->fMotherNucleus->fMaterial->Get
	}
	return 0;
}
TGraph* GammaTransition::GetENDFAngularDistribution()
{
	if(GetIntegrityFactor()==3)
	{
		if(AdistENDF.GetN()==0)
		{
			if(fLevel->fNucleus->fMotherNucleus->Projectile=="n")
			{
				fLevel->fNucleus->fMotherNucleus->ReadENDF();
				AdistENDF=fLevel->fNucleus->fMotherNucleus->ENDF.GetGammaAngularDistribution(Energy,fLevel->fNucleus->fMotherNucleus->ProjectileEnergy);
			}
		}
	}
	if(AdistENDF.GetN()==0)
	{
		return 0;
	}
	return &AdistENDF;
}

vector<TGraphErrors*> GammaTransition::GetEnergyDistributionGraph(double Emin, double Emax)
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

vector<TGraphErrors*> GammaTransition::GetAngularDistributionGraph(double Emin, double Emax)
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
