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
#include <TMath.h>
//#include "TXlswriter.cpp"
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
void TLMaterial::SetEnergyGrid(vector<double> Grid)
{
	WithEnergyGrid=true;
	for(unsigned int i=0;i<Nuclides.size();i++)
	{
		Nuclides[i]->SetEnergyGrid(Grid);
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
	for(unsigned int i=0;i<Nuclides.size();i++)
	{
		Nuclides[i]->fMaterial=this;
	}
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
	ROOTOpenXLSX xlsx;
	xlsx.Open(filename,"w","General");
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
	xlsx.Close();
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

Nucleus* TLMaterial::FindNuclide(int Z, int A)
{
	for(unsigned int i=0;i<Nuclides.size();i++)
	{
		if(Nuclides[i]->Z==Z && Nuclides[i]->A==A)
		{
			return Nuclides[i];
		}
	}
	return 0;
}
Nucleus* TLMaterial::FindNuclide(string NuclName)
{
	int Z,A;
	//void GetAZ(string nucleus, int &Z, int &A);
	GetAZ(NuclName,Z,A);
	return FindNuclide(Z,A);
}

void TLMaterial::SetAbundances(vector<string> Nuclides_,vector<double> Abundances)
{
	for(unsigned int pp=0;pp<ElementsVector.size();pp++)
	{
		int ZElement; int AA=0;
		GetAZ(ElementsVector[pp],ZElement,AA);
		
		vector<Nucleus*> NuclWithoutAbundances;
		double ResAbundance=0;
		double SumAbundances=0;
		for(unsigned int j=0;j<Nuclides.size();j++)
		{
			bool Found=false;
			for(unsigned int i=0;i<Nuclides_.size();i++)
			{
				int Z,A;
				GetAZ(Nuclides_[i],Z,A);
				if((Z == Nuclides[j]->Z) && (A == Nuclides[j]->A) && (ZElement == Z))
				{
					Nucleus *Nucl=Nuclides[j];
					Nucl->Abundance=Abundances[i];
					Found=true;
					SumAbundances+=Nucl->Abundance;
				}
			}
			if(!Found)
			{
				int ZNucl=Nuclides[j]->Z;
				if(ZNucl == ZElement)
				{
					NuclWithoutAbundances.push_back(Nuclides[j]);
					ResAbundance+=Nuclides[j]->Abundance;
				}
			}
		}
		double k=(1-SumAbundances)/ResAbundance;
		for(unsigned int i=0;i<NuclWithoutAbundances.size();i++)
		{
			NuclWithoutAbundances[i]->Abundance=k*NuclWithoutAbundances[i]->Abundance;
		}
	}
	
}

string GammaPeakData::ToString(string Option)
{
	string result;
	if(Option=="short")
	{
		result=TString::Format("E=%.2f#pm%.2f, #sigma=%.2f mb",E,Sigma,EffectiveCS).Data();
	}
	else
	{
		result=TString::Format("E=%.2f#pm%.2f, #sigma=%.2f mb, NAtoms=%.2e, StCoeff=%.2f, Multipolarity=%d",E,Sigma,EffectiveCS,NAtoms,StCoeff,(int)Multipolarity).Data();
	}
	return result;
}
GammaPeakData TLMaterial::FindGammaTransitionsForInterval(vector<GammaTransition*> GT_,double EMin,double EMax,double Length,bool Add_n2n)//толщина - в см
{	
	GammaPeakData result;
	result.Multipolarity=0;
	vector<GammaTransition*> GT;
	for(unsigned int i=0;i<GT_.size();i++)
	{
		double E=GT_[i]->Energy;
		if(E>=EMin && E<=EMax)
		{
			//cout<<"FindGammaTransitionsForInterval: "<<E<<"\n";
			GT.push_back(GT_[i]);
			if(Add_n2n && GT_[i]->fLevel->fNucleus->Reaction=="(n,n')")
			{
				Nucleus* Targ2n=GT_[i]->fLevel->fNucleus->fMotherNucleus->fMaterial->FindNuclide(GT_[i]->fLevel->fNucleus->fMotherNucleus->Z,GT_[i]->fLevel->fNucleus->fMotherNucleus->A+1);
				if(Targ2n)
				{
					GammaTransition *gt2=Targ2n->GetBestTransition(GT_[i]->Energy,0.1);
					if(gt2)
					{
						GT.push_back(gt2);
					}
				}
			}
		}
	}
	if(GT.size()==0)
	{
		return result;
	}
	
	result.Gammas=GT;
	result.Sigma=(EMax-EMin)/2;
	result.E=(EMin+EMax)/2;
	result.fMaterial=GT[0]->fLevel->fNucleus->fMotherNucleus->fMaterial;
	//cout<<"Material:"<<result.fMaterial->MaterialFormula<<"\n";
	double NAtoms=result.fMaterial->Density*6.02e23/result.fMaterial->GetMolarMass()*Length;
	vector<TGraph*> Graphs;
	vector<double> Multipliers;
	double CSMax=0;
	for(unsigned int i=0;i<GT.size();i++)
	{
		
		Nucleus* Init=GT[i]->fLevel->fNucleus->fMotherNucleus;
		double Stechiometry=result.fMaterial->GetElementQuantity(Init);
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
		//cout<<"Eg: "<<GT[i]->Energy<<" "<<Init->Name<<" "<<GT[i]->fLevel->fNucleus->Reaction<<" density:"<<result.fMaterial->Density<<" length:"<<Length<<" MolarMass:"<<result.fMaterial->GetMolarMass()<<" Stechiometry:"<<Stechiometry<<" Abundance:"<<Init->Abundance<<"\n";
		Multipliers.push_back(Stechiometry*Abun);
		result.Reactions.push_back(Init->Name+GT[i]->fLevel->fNucleus->Reaction+GT[i]->fLevel->fNucleus->Name);
		result.Centroid+=GT[i]->TalysCrossSection*Stechiometry*Abun*GT[i]->Energy;
		Graphs.push_back(GT[i]->GetCSGraph());
		
	}
	for(unsigned int i=0;i<Multipliers.size();i++)
	{
		Multipliers[i]=Multipliers[i]/result.StCoeff;
	}
	if(result.fMaterial->WithEnergyGrid)
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
	result.CSGraph.SetName(TString::Format("CSPeak_%d_pm_%d",(int(result.E*10)),int(result.Sigma*10)));
	result.CSGraph.SetTitle(TString::Format("Talys-calculated #sigma for #gamma-peak %.1f#pm%.1f; E, MeV; #sigma, mb",result.E,result.Sigma));
	return result;
}

void TLMaterial::AssignPointers()
{
	for(unsigned int i=0;i<Nuclides.size();i++)
	{
		Nuclides[i]->AssignPointers();
		Nuclides[i]->fMaterial=this;
	}
}

void TLMaterial::LoadPreCalculatedMaterial(string fname)
{
	TFile ff(fname.c_str());
	TString json_str=*(TString*)ff.Get("Info");
	nlohmann::json jsn = nlohmann::json::parse(json_str.Data());
	
	std::vector<std::string> keys;
	keys.reserve(jsn.size());          // size() для объекта = число ключей

	for (auto it = jsn.begin(); it != jsn.end(); ++it)
	{
		keys.push_back(it.key());
	}
	for(unsigned int i=0;i<keys.size();i++)
	{
		string InitNuclName=(jsn[keys[i]]["Init"]);
		string ProdName=(jsn[keys[i]]["Final"]);
		Nucleus *Init=FindNuclide(InitNuclName);
		if(!Init)
		{
			continue;
		}
		Nucleus *Prod=Init->FindProductByName(ProdName);
		if(!Prod)
		{
			Init->Products.push_back(Nucleus(ProdName,jsn[keys[i]]["Reaction"]));
		}
	}
	for(unsigned int i=0;i<keys.size();i++)
	{
		string InitNuclName=(jsn[keys[i]]["Init"]);
		string ProdName=(jsn[keys[i]]["Final"]);
		Nucleus *Init=FindNuclide(InitNuclName);
		if(!Init)
		{
			continue;
		}
		Nucleus *Prod=Init->FindProductByName(ProdName);
		double LevE=jsn[keys[i]]["InitLevel"];
		Level* lvl=Prod->FindLevelByEnergy(LevE,1);
		double GamE=jsn[keys[i]]["E"];
		bool UsedGrid=false;
		if(Init->EnergyGrid.size()>0)
		UsedGrid=true;
		for(unsigned int j=0;j<lvl->Gammas.size();j++)
		{
			if(abs(lvl->Gammas[j].Energy-GamE)<1)
			{
				lvl->Gammas[j].CSGraph=*(TGraph*)ff.Get(keys[i].c_str());
				double x,y;
				int N=lvl->Gammas[j].CSGraph.GetN();
				lvl->Gammas[j].CSGraph.GetPoint(N-1,x,y);
				lvl->Gammas[j].TalysCrossSection=y;
				if(!UsedGrid)
				{
					for(int p=0;p<N;p++)
					{
						lvl->Gammas[j].CSGraph.GetPoint(p,x,y);
						Init->EnergyGrid.push_back(x);
					}
				}
			}
		}
	}
	AssignPointers();
	WithEnergyGrid=true;
	ff.Close();
}

void TLMaterial::LoadPreCalculatedMaterial(vector<string> fnames)
{
	for(unsigned int i=0;i<fnames.size();i++)
	{
		LoadPreCalculatedMaterial(fnames[i]);
	}
}

GammaPeakData TLMaterial::FindGammaTransitionsForPeak(double Energy,double Sigma,double CrossSectionThreshold, double Length,bool UseAbundancy, bool AtLeastOne,double EThr, bool Always_n2n,string SelectedElement)
{
	vector<GammaTransition*> GT;
	GammaTransition* MaxCS=0;
	double CSMax=0;
	vector<GammaTransition*> GT0=FindGammaTransitions(Energy,0,Sigma,UseAbundancy);
	//if(AtLeastOne)
	//{
		for(unsigned int i=0;i<GT0.size();i++)
		{
			double Val=GT0[i]->TalysCrossSection;
			if(WithEnergyGrid)
			{
				if(EThr>0) 
				{
					Val=GT0[i]->GetCSGraph()->Eval(EThr);
				}
				else
				{
					TGraph *CSG=GT0[i]->GetCSGraph();
					for(int pp=0;pp<CSG->GetN();pp++)
					{
						double x,y;
						CSG->GetPoint(pp,x,y);
						if(x< -EThr && y>Val)
						{
							Val=y;
						}
					}
					Val=TMath::MaxElement(GT0[i]->GetCSGraph()->GetN(),GT0[i]->GetCSGraph()->GetY()); 
				}
			}
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
		//if(GT.size()==0)
		if((GT.size()==0)&&(AtLeastOne))
		{
			GT.push_back(MaxCS);
		}
	//}
/*	else
	{
		GT=FindGammaTransitions(Energy,CrossSectionThreshold,Sigma,UseAbundancy);
	}*/
	
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
		
		if(SelectedElement.size()>0)
		{
			int ZZ,AA;
			GetAZ(SelectedElement,ZZ,AA);
			if(ZZ<=0)
			{
				cout<<"This is FindGammaTransitionsForInterval: cannot use SelectedElement="<<SelectedElement<<"\n";
			}
			else
			{
				if(ZZ!=Init->Z)
				{
					Abun=0;//зануляем распространенность для неподходящих элементов
				}
			}
		}
		
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
GammaPeakData TLMaterial::FindGammaTransitionsForInterval(double EMin,double EMax,double CrossSectionThreshold, double Length,bool UseAbundancy, bool AtLeastOne,double EThr, bool Always_n2n,string SelectedElement)//толщина - в см
{
	double E_av=(EMin+EMax)/2;
	double E_sig=(EMax-EMin)/2;
	return FindGammaTransitionsForPeak(E_av,E_sig,CrossSectionThreshold,Length,UseAbundancy,AtLeastOne,EThr,Always_n2n,SelectedElement);
}
