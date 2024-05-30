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

void EvalInThreadForTLMaterial(Nucleus *Nucl,int NThread)
{
	Nucl->SetThreadNumber(NThread);
	Nucl->SetProjectileEnergy(Nucl->fMaterial->ProjectileEnergy);
	Nucl->GenerateProducts(Nucl->fMaterial->Projectile);
}
void TLMaterial::Calculate()
{
	if(EnableMultiThreading)
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
