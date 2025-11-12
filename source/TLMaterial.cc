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
#include <TVector3.h>
#include "TXlswriter.cpp"
#include <algorithm>
#pragma once

void TLMaterial::SetDensity(double _Density)
{
	Density=_Density;
}

void TLMaterial::SetProjectile(string _Projectile)
{
	Projectile=_Projectile;
}

void TLMaterial::SetProjectileEnergy(double _Energy)
{
	ProjectileEnergy=_Energy;
}

double TLMaterial::GetDensity()
{
	return Density;
}

void TLMaterial::GenerateEnergyGrid(double min, double step,double max)
{
	WithEnergyGrid=true;
	for(unsigned int i=0;i<Nuclides.size();i++)
	{
		Nuclides[i]->GenerateEnergyGrid(min,step,max);
	}
}

void EvalInThreadForTLMaterial(Nucleus *Nucl,int NThread)
{
	Nucl->SetThreadNumber(NThread);
	Nucl->SetProjectileEnergy(Nucl->fMaterial->ProjectileEnergy);
	Nucl->GenerateProducts(Nucl->fMaterial->Projectile);
}
void TLMaterial::Calculate()
{
	if(EnableMultiThreading && !WithEnergyGrid)
	{
		vector<thread> threads;
		unsigned int CurrIndex=0;
		for(unsigned int p=0;p<Nuclides.size();p++)
		{
			if(CurrIndex<Nuclides.size())
			{
				threads.emplace_back(EvalInThreadForTLMaterial,Nuclides[CurrIndex],p);
				CurrIndex++;
			}
		}
		for(unsigned int p=0;p<threads.size();p++)
		{
			threads[p].join();
		}
	}
	else
	{
		for(unsigned int p=0;p<Nuclides.size();p++)
		{
			EvalInThreadForTLMaterial(Nuclides[p],0);
		}
	}
	for(unsigned int p=0;p<Nuclides.size();p++)
	{
		Nuclides[p]->AssignPointers();
		Nuclides[p]->fMaterial=this;
	}
}

int TLMaterial::GetElementQuantity(string Element)
{
	for(unsigned int i=0;i<ElementsVector.size();i++)
	{
		if(Element==ElementsVector[i])
		{
			return QVector[i];
		}
	}
	return 0;
}
int TLMaterial::GetElementQuantity(Nucleus *Nucl)
{
	string ElementName=GetNucleusName(Nucl->Z);
	return GetElementQuantity(ElementName);
}

TLMaterial::TLMaterial(string _MaterialFormula)
{
	MaterialFormula=_MaterialFormula;
	vector<string> Elements;
	vector<int> Q;
	GenerateListOfElements(MaterialFormula,Elements,Q);
	for(unsigned int i=0;i<Elements.size();i++)
	{
		MolarMass+=GetAverageMass(Elements[i])*Q[i];
		AddElement(Elements[i],Q[i]);
		NAtoms+=Q[i];
	}
	
	ElementsVector=Elements;
	QVector=Q;
	//Calculate();

}
double TLMaterial::GetMolarMass()
{
	return MolarMass;
}
void TLMaterial::AddElement(string Element, int Q)
{
	vector<int> A_values;
	vector<double> Abundances;
	GetAbundance(Element,A_values,Abundances);
	for(unsigned int j=0;j<A_values.size();j++)
	{
		Nucleus *N=new Nucleus(to_string(A_values[j])+Element);
		N->fMaterial=this;
		//N->Projectile=Projectile;
		N->ProjectileEnergy=ProjectileEnergy;
		//N->GenerateProducts(Projectile);
		Nuclides.push_back(N);
		Quantities.push_back(Q);
		Shares.push_back(Q*Abundances[j]);
		MassShares.push_back(Q*Abundances[j]*N->GetMass());
	}
}
void TLMaterial::AddBackground(string PathToBackground)
{
	Nucleus* bkg=new Nucleus("BKG "+PathToBackground);
	Nuclides.push_back(bkg);
	Quantities.push_back(0);
}
void TLMaterial::SaveToXLSX(string filename)
{
	TXlsxwriter xlsx;
	xlsx.Open(filename);
	xlsx.GoToWorksheet("General");
	xlsx<<"Composition:"<<MaterialFormula<<"\n";
	xlsx<<"Molar mass:"<<MolarMass<<"\n";
	xlsx<<"Nucleus"<<"Abundancy"<<"\n";
	for(unsigned int i=0;i<Nuclides.size();i++)
	{
		xlsx<<Nuclides[i]->Name<<Nuclides[i]->Abundance<<"\n";
	}
	xlsx.GoToWorksheet("Gammas");
	GetGammaTransitions(0,true);
	xlsx<<"E_gamma"<<"E_i"<<"JPi"<<"E_f"<<"JPf"<<"Target"<<"Reaction"<<"Product"<<"CS"<<"Abun*CS"<<"\n";
	for(unsigned int i=0;i<Gammas.size();i++)
	{
		xlsx<<Gammas[i]->Energy<<Gammas[i]->TalysE_i<<Gammas[i]->TalysJP_i.GetLine()<<Gammas[i]->TalysE_f<<Gammas[i]->TalysJP_f.GetLine()<<Gammas[i]->fLevel->fNucleus->fMotherNucleus->Name<<Gammas[i]->fLevel->fNucleus->Reaction<<Gammas[i]->fLevel->fNucleus->Name<<Gammas[i]->TalysCrossSection<<Gammas[i]->TalysCrossSection*(Gammas[i]->fLevel->fNucleus->fMotherNucleus->Abundance)<<"\n";
	}
}
void TLMaterial::PrintGammas(double CrossSectionThreshold,bool UseAbundancy)
{
	GetGammaTransitions(CrossSectionThreshold,UseAbundancy);
	cout<<"E_gamma E_i JPi E_f JPf Target Reaction Product CS Abun*CS \n";
	for(unsigned int i=0;i<Gammas.size();i++)
	{
		cout<<Gammas[i]->Energy<<" "<<Gammas[i]->TalysE_i<<" "<<Gammas[i]->TalysJP_i.GetLine()<<" "<<Gammas[i]->TalysE_f<<" "<<Gammas[i]->TalysJP_f.GetLine()<<" "<<Gammas[i]->fLevel->fNucleus->fMotherNucleus->Name<<" "<<Gammas[i]->fLevel->fNucleus->Reaction<<" "<<Gammas[i]->fLevel->fNucleus->Name<<" "<<Gammas[i]->TalysCrossSection<<" "<<Gammas[i]->TalysCrossSection*(Gammas[i]->fLevel->fNucleus->fMotherNucleus->Abundance)<<" "<<"\n";
	}
}
double TLMaterial::GetMoleFraction(string _Name)
{
	double Norm=0;
	double Share=0;
	for(unsigned int i=0;i<Shares.size();i++)
	{
		if(_Name==Nuclides[i]->Name)
		{
			Share=Shares[i];
		}
		Norm+=Shares[i];
	}
	return Share/Norm;
}
double TLMaterial::GetMoleFraction(Nucleus *Nucl)
{
	string _Name=Nucl->Name;
	return GetMoleFraction(_Name);
}
double TLMaterial::GetMassFraction(string _Name)
{
	double Norm=0;
	double Share=0;
	for(unsigned int i=0;i<Shares.size();i++)
	{
		if(_Name==Nuclides[i]->Name)
		{
			Share=MassShares[i];
		}
		Norm+=MassShares[i];
	}
	return Share/Norm;
}
double TLMaterial::GetMassFraction(Nucleus *Nucl)
{
	string _Name=Nucl->Name;
	return GetMassFraction(_Name);
}

vector<GammaTransition*> TLMaterial::GetGammaTransitions(double CrossSectionThreshold,bool UseAbundancy)
{
	vector<GammaTransition*> result;
	for(unsigned int i=0;i<Nuclides.size();i++)
	{
		vector<GammaTransition*> GT;
		if(Nuclides[i]->Name.find("BKG")!=string::npos)
		{
			for(unsigned int p=0;p<Nuclides[i]->Levels[0].Gammas.size();p++)
			{
				GT.push_back(&Nuclides[i]->Levels[0].Gammas[p]);
			}
		}
		//cout<<"Nuclides["<<i<<"] "<<Nuclides[i]->Name<<"\n";
		for(unsigned int j=0;j<Nuclides[i]->Products.size();j++)
		{
			//cout<<"Nuclides["<<i<<"]->Products["<<j<<"]"<<Nuclides[i]->Products[j].Name<<"\n";
			for(unsigned int k=0;k<Nuclides[i]->Products[j].Levels.size();k++)
			{
				//cout<<"Nuclides["<<i<<"]->Products["<<j<<"].Levels.size()"<<Nuclides[i]->Products[j].Levels.size()<<"\n";
				for(unsigned int p=0;p<Nuclides[i]->Products[j].Levels[k].Gammas.size();p++)
				{
					//cout<<"Nuclides["<<i<<"]->Products["<<j<<"].Levels["<<k<<"].Gammas["<<p<<"]:E"<<Nuclides[i]->Products[j].Levels[k].Gammas[p].Energy<<"\n";
					GT.push_back(&Nuclides[i]->Products[j].Levels[k].Gammas[p]);
				}
			}
		}
		for(unsigned int j=0;j<GT.size();j++)
		{
			double Threshold=CrossSectionThreshold;
			if(UseAbundancy)
			{
				Threshold=Threshold/GT[j]->fLevel->fNucleus->fMotherNucleus->Abundance;
			}
			if((GT[j]->TalysCrossSection>Threshold)||(GT[j]->fLevel->fNucleus->Name.find("BKG")!=string::npos))
			{
				result.push_back(GT[j]);
			}
		}
	}
	GeneratedLineList=true;
	if(result.size()<2)
	{
		Gammas=result;
		return result;
	}
	for(unsigned int i=0;i<result.size()-1;i++)
	{
		for (unsigned int j = 0; j <result.size()-i-1; j++)
		{
			//cout<<Levels.size()<<" "<<i<<" "<<j<<"\n";
			if(result[j]->Energy>result[j+1]->Energy)
			{
				swap(result[j],result[j+1]);
			}
		}
	}
	Gammas=result;
	for(unsigned int i=0;i<result.size();i++)
	{
		if(!InVector(Nuclides,result[i]->fLevel->fNucleus->fMotherNucleus))
		{
			cout<<"Pointer Error\n";
		}
	}
	return result;
}

vector<GammaTransition*> TLMaterial::GetGammaTransitionsE(double EnergyThreshold,double CrossSectionThreshold,bool UseAbundancy)
{
	vector<GammaTransition*> result;
	vector<GammaTransition*> v=GetGammaTransitions(CrossSectionThreshold,UseAbundancy);
	for(unsigned int i=0;i<v.size();i++)
	{
		if(v[i]->Energy>EnergyThreshold)
		{
			result.push_back(v[i]);
		}
	}
	return result;
}
TH1F *TLMaterial::GenerateGammaSpectrum(string DetectorType,TF1 *ResolutionFunction)
{
	for(unsigned int i=0;i<Nuclides.size();i++)
	{
		TH1F* h=(Nuclides[i]->GenerateGammaSpectrum(DetectorType,ResolutionFunction));
		if(h)
		{
			TH1F hist_tmp=*h;
			hist_tmp.Scale(GetMoleFraction(Nuclides[i]));
			hist_tmp.SetName((Nuclides[i]->Name).c_str());
			hist_tmp.SetTitle((Nuclides[i]->Name+"; E,keV; Counts").c_str());
			GammaSpectraPerNuclei.push_back(hist_tmp);
			if(GammaSpectrum.Integral()==0)
			{
				GammaSpectrum=hist_tmp;
			}
			else
			{
				GammaSpectrum.Add(&hist_tmp);
			}
		}
	}
	GammaSpectrum.SetName((MaterialFormula+"_"+DetectorType).c_str());
	GammaSpectrum.SetTitle((MaterialFormula+":"+DetectorType+";E, keV; Counts").c_str());
	return &GammaSpectrum;
}
vector<GammaTransition*> TLMaterial::FindGammaTransitions(double Energy,double CrossSectionThreshold,double Tolerancy,bool UseAbundancy)
{
	vector<GammaTransition*> GammasTMP=GetGammaTransitions(CrossSectionThreshold,UseAbundancy);
	vector<GammaTransition*> result;
	for(unsigned int i=0;i<GammasTMP.size();i++)
	{
		if(abs(GammasTMP[i]->Energy-Energy)<Tolerancy)
		{
			result.push_back(GammasTMP[i]);
		}
	}
	return result;
}
GammaTransition* TLMaterial::FindBestTransition(double Energy,double CrossSectionThreshold,double Tolerancy,bool UseAbundancy)
{
	vector<GammaTransition*> gt=FindGammaTransitions(Energy,CrossSectionThreshold,Tolerancy,UseAbundancy);
	GammaTransition* result=0;
	if(gt.size()==0)
	{
		return 0;
	}
	result=gt[0];
	for(unsigned int i=0;i<gt.size();i++)
	{
		double CSF=gt[i]->TalysCrossSection;
		double CSF1=result->TalysCrossSection;
		if(UseAbundancy)
		{
			CSF=CSF*gt[i]->fLevel->fNucleus->fMotherNucleus->Abundance;
			CSF1=CSF1*result->fLevel->fNucleus->fMotherNucleus->Abundance;
		}
		if(CSF>CSF1)
		{
			result=gt[i];
		}
	}
	return result;
}

GammaTransition* TLMaterial::GetMostIntenseGammaTransition()
{
	GammaTransition* t=0;
	for(unsigned int i=0;i<Nuclides.size();i++)
	{
		if(!t)
		{
			t=Nuclides[i]->GetMostIntenseGammaTransition();
		}
		if(t)
		{
			GammaTransition* t2=Nuclides[i]->GetMostIntenseGammaTransition();
			if(t2)
			{
				if(t2->TalysCrossSection*GetMoleFraction(Nuclides[i])>t->TalysCrossSection*GetMoleFraction(t->fLevel->fNucleus->fMotherNucleus))
				{
					t=t2;
				}
			}
			
		}
	}
	return t;
}

void Find_nn_n2n_gammas(vector<GammaTransition*> &GT,vector<GammaTransition*> &Gamma_n,vector<GammaTransition*> &Gamma_2n,string reaction)//строка "reaction" соответствует реакциям в векторе Gamma_2n
{
	//теперь проверим наличие n,2n 
	for(unsigned int i=0;i<Gamma_n.size();i++)
	{
		bool Found_n2n=false;
		string Nucl_n=Gamma_n[i]->fLevel->fNucleus->Name;
		double Energy_n=Gamma_n[i]->Energy;
		for(unsigned int j=0;j<Gamma_2n.size();j++)
		{
			string Nucl_2n=Gamma_2n[j]->fLevel->fNucleus->Name;
			double Energy_2n=Gamma_n[i]->Energy;
			if(abs(Energy_n-Energy_2n)<0.01 && (Nucl_n==Nucl_2n))
			{
				Found_n2n=true;
				//cout<<"Found_n2n!\n";
				break;
			}
		}
		if(!Found_n2n)
		{
			//cout<<"Not Found_n2n!\n";
			TLMaterial *mat=Gamma_n[i]->fLevel->fNucleus->fMotherNucleus->fMaterial;
			Nucleus *Nucl_2n=0;
			if(reaction=="(n,n')")
			{
				for(unsigned int j=0;j<mat->Nuclides.size();j++)
				{
					if(mat->Nuclides[j]->Name==Nucl_n)
					{
						Nucl_2n=mat->Nuclides[j];
					}
				}
			}
			else if(reaction=="(n,2n)")
			{
				for(unsigned int j=0;j<mat->Nuclides.size();j++)
				{
					if(mat->Nuclides[j]->Z==Gamma_n[i]->fLevel->fNucleus->Z && mat->Nuclides[j]->A==Gamma_n[i]->fLevel->fNucleus->A+1)
					{
						Nucl_2n=mat->Nuclides[j];
					}
				}
			}
			if(!Nucl_2n)
			{
				continue;
			}
			//cout<<"Find Nucl_2n:"<<reaction<<Nucl_2n->Name<<"\n";
			GammaTransition *gt_2n=Nucl_2n->GetBestTransition(Energy_n,0.1);
			if(!gt_2n)
			{
				continue;
			}
			//cout<<"Find gt_2n:"<<gt_2n->Energy<<"\n";
			if(gt_2n->TalysCrossSection>0)
			{
				Gamma_2n.push_back(gt_2n);
				GT.push_back(gt_2n);
			}
		}
	}
}

GammaPeakData TLMaterial::FindGammaTransitionsForPeak(double Energy,double Sigma,double CrossSectionThreshold, double Length,bool UseAbundancy, bool AtLeastOne, bool Always_n2n)
//GammaPeakData TLMaterial::FindGammaTransitionsForPeak(double Energy,double Sigma,double CrossSectionThreshold, double Length,bool UseAbundancy, bool AtLeastOne)
{
	vector<GammaTransition*> GT;
	GammaTransition* MaxCS=0;
	double CSMax=0;
	
	if(AtLeastOne)
	{
		vector<GammaTransition*> GT0=FindGammaTransitions(Energy,0,Sigma,UseAbundancy);
		for(unsigned int i=0;i<GT0.size();i++)
		{
			double Val=GT0[i]->TalysCrossSection;
			if(UseAbundancy)
			{
				Val=Val*GT0[i]->fLevel->fNucleus->fMotherNucleus->Abundance;
			}
			if(i==0)
			{
				CSMax=Val;
				MaxCS=GT0[i];
			}
			else if (CSMax<Val)
			{
				CSMax=Val;
				MaxCS=GT0[i];
			}
			if(Val>CrossSectionThreshold)
			{
				GT.push_back(GT0[i]);
			}
		}
		if(GT.size()==0)
		{
			GT.push_back(MaxCS);
		}
	}
	else
	{
		GT=FindGammaTransitions(Energy,CrossSectionThreshold,Sigma,UseAbundancy);
	}
	
	if(Always_n2n && Projectile=="n")
	{
		//cout<<"Always_n2n!\n";
		//сначала заполним векторы с (n,n') и (n,2n)
		vector<GammaTransition*> Gamma_n;
		vector<GammaTransition*> Gamma_2n;
		for(unsigned int i=0;i<GT.size();i++)
		{
			if(GT[i]->fLevel->fNucleus->Reaction=="(n,n')")
			{
				Gamma_n.push_back(GT[i]);
			}
			if(GT[i]->fLevel->fNucleus->Reaction=="(n,2n)")
			{
				Gamma_2n.push_back(GT[i]);
			}
		}
		//cout<<"Gamma_n.size: "<<Gamma_n.size()<<"\n";
		//cout<<"Gamma_2n.size: "<<Gamma_2n.size()<<"\n";
		Find_nn_n2n_gammas(GT,Gamma_n,Gamma_2n,"(n,2n)");
		Find_nn_n2n_gammas(GT,Gamma_2n,Gamma_n,"(n,n')");
	}
	
	GammaPeakData result;
	result.Multipolarity=0;
	result.Gammas=GT;
	result.Sigma=Sigma;
	result.E=Energy;
	result.fMaterial=this;
	double NAtoms=Density*6.02e23/GetMolarMass()*Length;
	vector<TGraph*> Graphs;
	vector<double> Multipliers;
	CSMax=0;
	for(unsigned int i=0;i<GT.size();i++)
	{
		Nucleus* Init=GT[i]->fLevel->fNucleus->fMotherNucleus;
		double Stechiometry=GetElementQuantity(Init);
		double Abun=Init->Abundance;
		
		if(!InVector(result.InitNuclei,Init))
		{
			result.StCoeff+=Stechiometry*Abun;
			result.NAtoms+=NAtoms*Stechiometry*Abun;
			result.InitNuclei.push_back(Init);
		}
		result.EffectiveCS+=GT[i]->TalysCrossSection*Stechiometry*Abun;
		if(result.Multipolarity<GT[i]->GetMostProbableMultipolarity().J)
		{
			result.Multipolarity=GT[i]->GetMostProbableMultipolarity().J;
		}
		/*if(CSMax<GT[i]->TalysCrossSection*Stechiometry*Abun)
		{
			CSMax=GT[i]->TalysCrossSection*Stechiometry*Abun;
			Multipolarity=GT[i]->GetMostProbableMultipolarity().J;
		}*/
		Multipliers.push_back(Stechiometry*Abun);
		result.Reactions.push_back(Init->Name+GT[i]->fLevel->fNucleus->Reaction+GT[i]->fLevel->fNucleus->Name);
		result.Centroid+=GT[i]->TalysCrossSection*Stechiometry*Abun*GT[i]->Energy;
		Graphs.push_back(GT[i]->GetCSGraph());
		
	}
	for(unsigned int i=0;i<Multipliers.size();i++)
	{
		Multipliers[i]=Multipliers[i]/result.StCoeff;
	}
	if(WithEnergyGrid)
	{
		result.CSGraph=SumTGraphs(Graphs,Multipliers);
	}
	result.Centroid=result.Centroid/result.EffectiveCS;
	result.EffectiveCS=result.EffectiveCS/result.StCoeff;
	result.NAtoms_mb=result.NAtoms*1e-27;
	
	for(unsigned int i=0;i<result.Reactions.size();i++)
	{
		if(i==0)
		{
			result.Reacstr+=result.Reactions[i];
		}
		else
		{
			result.Reacstr+=("; "+result.Reactions[i]);
		}
	}
	result.CSGraph.SetName(TString::Format("CSPeak_%d_pm_%d",(int(Energy*10)),int(Sigma*10)));
	result.CSGraph.SetTitle(TString::Format("Talys-calculated #sigma for #gamma-peak %.1f#pm%.1f; E, MeV; #sigma, mb",Energy,Sigma));
	return result;
}
