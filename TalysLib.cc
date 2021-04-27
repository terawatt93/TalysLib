#include "TalysLib.hh"
#include <sys/stat.h>

#include <bits/stdc++.h>
#include <cstring>
#include <algorithm>
#include <cctype>
#include "Parser.cpp"
#include <TLine.h>
#include <TText.h>
#include <TList.h>
#include <TKey.h>
#include "source/SpinParity.cc" //contains SpinParity class methods
#include "source/OMP.cc" //contains OpticalModelParameters class methods
#include "source/Deformations.cc" //contains LevelDeformation and Deformation classes methods
#include "source/GammaTransitions.cc" //contains GammaTransition class methods
#include "source/LevelProperties.cc" //contains Level class methods
#include "source/NucleiProperties.cc" //contains Nucleus class methods
#include "source/TalysCalculation.cc" //contains TalysCalculation class methods
#include "source/TalysFitter.cc" 
#include "source/TalysFitterMT.cc" 
#include "source/AdditionalInformation.cc"

GammaTransition* GetBestTransitionFromVector(float Energy, float Tolerancy,vector<Nucleus> &Nuclei)
{
	vector<GammaTransition*> Transitions;
	GammaTransition* BestTransition=0;
	cout<<"GetBestTransitionFromVector started: "<<Energy<<"\n";
	for(unsigned int i=0;i<Nuclei.size();i++)
	{
		for(unsigned int j=0;j<Nuclei[i].Products.size();j++)
		{
			cout<<"Nuclei[i]:"<<Nuclei[i].Name<<":"<<Nuclei[i].Products[j].Name<<" "<<Nuclei[i].Products[j].Levels.size()<<"\n";
		}
		GammaTransition *gm_tmp=Nuclei[i].GetBestTransition(Energy,Tolerancy);
		if(gm_tmp)
		{
			cout<<"GammaTransition E:"<<Energy<<" gm_tmp_energy:"<<gm_tmp->Energy<<" "<<gm_tmp->fLevel->fNucleus->Name<<"\n";
			Transitions.push_back(gm_tmp);
		}
	}
	if(Transitions.size()>0)
	{
		BestTransition=Transitions[0];
	}
	else
	{
		return 0;
	}
	for(unsigned int i=0;i<Transitions.size();i++)
	{
		if(BestTransition&&Transitions[i])
		{
			double BestCS=BestTransition->TalysCrossSection;
			double BestAbundance=BestTransition->fLevel->fNucleus->fMotherNucleus->Abundance;
			double CurrentCS=Transitions[i]->TalysCrossSection;
			double CurrentAbundance=Transitions[i]->fLevel->fNucleus->fMotherNucleus->Abundance;
			//cout<<Energy<<" BestCS:"<<BestCS<<" BestAbundance:"<<BestAbundance<<" CurrentCS:"<<CurrentCS<<" CurrentAbundance:"<<CurrentAbundance<<"\n";
			if(BestCS*BestAbundance<CurrentCS*CurrentAbundance)
			{
				BestTransition=Transitions[i];
			}
		}
	}
	return BestTransition;
}
int CheckGammaTransitionIntegrality(GammaTransition* gt)
{
	if(gt)
	{
		if(gt->fLevel)
		{
			if(gt->fLevel->fNucleus)
			{
				if(gt->fLevel->fNucleus->fMotherNucleus)
				{
					if(gt->fFinalLevel)
					{
						return 5;
					}
					return 4;
					
				}
				return 3;
			}
			return 2;
		}
		return 1;
	}
	return 0;
}
void ReadNucleiFromRootFile(vector<Nucleus> &Nuclei,TFile *f)
{
	if(!f)
	{
		cout<<"This is ReadNucleiFromRootFile: Cannot read a root file!\n";
		return ;
	}
	TList* list = f->GetListOfKeys();
	if(!list)
	{
		cout<<"This isReadNucleiFromRootFile: List cannot be created\n";
		return ;
	}
	TIter next(list);
	TKey* key=(TKey*)next();
	while(key)
	{
		TObject* obj = key->ReadObj();
		if(obj)
		{
			if((obj->InheritsFrom("NucleusData")))
			{
				Nuclei.emplace_back(*((NucleusData*)obj));
			}
		}
		key=(TKey*)next();
	}
	for(unsigned int i=0;i<Nuclei.size();i++)
	{
		Nuclei[i].AssignPointers();
	}
}
void TLMaterial::SetDensity(double _Density)
{
	Density=_Density;
}
double TLMaterial::GetDensity()
{
	return Density;
}

void EvalInThreadForTLMaterial(Nucleus *Nucl,int NThread)
{
	Nucl->SetThreadNumber(NThread);
	Nucl->GenerateProducts();
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
	}
	
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
		
		
		/*bool Calculated=false;
		while(!Calculated)
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
			if(CurrIndex==Nuclides.size())
			{
				return;
			}
		}*/
	}
	else
	{
		for(unsigned int p=0;p<Nuclides.size();p++)
		{
			EvalInThreadForTLMaterial(Nuclides[p],0);
		}
	}

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
		N->GenerateProducts();
		Nuclides.push_back(N);
		Quantities.push_back(Q);
	}
}
void TLMaterial::AddBackground(string PathToBackground)
{
	Nucleus* bkg=new Nucleus("BKG "+PathToBackground);
	Nuclides.push_back(bkg);
	Quantities.push_back(0);
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
		for(unsigned int j=0;j<Nuclides[i]->Products.size();j++)
		{
			for(unsigned int k=0;k<Nuclides[i]->Products[j].Levels.size();k++)
			{
				for(unsigned int p=0;p<Nuclides[i]->Products[j].Levels[k].Gammas.size();p++)
				{
					
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
		for (int j = 0; j <result.size()-i-1; j++)
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

